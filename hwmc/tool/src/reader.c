#include "reader.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/vector3.h>
#include <assimp/color4.h>
#include <hw/utility.h>
#include <hw/memory/allocator.h>
#include <hw/debug/assert.h>

static void read_node(reader_node_t* out, const struct aiScene* scene, const struct aiNode* input);
static void read_mesh(reader_mesh_t* out, const struct aiScene* scene, const struct aiMesh* input);

static void read_vertices(reader_mesh_t* out, const struct aiMesh* input);
static void read_normals(reader_mesh_t* out, const struct aiMesh* input);
static void read_colors(reader_mesh_t* out, const struct aiMesh* input);
static void read_texcoords(reader_mesh_t* out, const struct aiMesh* input);
static void read_indices(reader_mesh_t* out, const struct aiMesh* input);
static void read_material(reader_mesh_t* out, const struct aiScene* scene, const struct aiMesh* input);
static void read_material_colors(reader_material_t* out, const struct aiMaterial* input);
static void read_textures(reader_material_t* out, const struct aiMaterial* material);

static hwu32 get_index_count(const struct aiMesh* mesh);
static hwm_vector3_t* create_vector3_array(const struct aiVector3D* source, hwu32 count);
static hwbool get_material_color(hwg_color4_f32_t* out, const struct aiMaterial* material, const char* key, hwuint type, hwuint index);

static hwg_texture_mapping_t to_hw_texture_mapping(enum aiTextureMapping mapping);
static hwg_texture_wrap_t    to_hw_texture_wrap(enum aiTextureMapMode wrap);
static hwg_texture_op_t      to_hw_texture_op(enum aiTextureOp op);

void reader_node_initialize(reader_node_t* node)
{
    node->meshes      = NULL;
    node->mesh_count  = 0;
    node->children    = NULL;
    node->child_count = 0;
    hwm_matrix44_identity(&node->local_transform);
}

void reader_node_finalize(reader_node_t* node)
{
    hwu32 i;

    for(i = 0; i < node->mesh_count; ++i) {
        reader_mesh_finalize(node->meshes + i);
    }
    HW_SAFE_FREE(node->meshes);

    for(i = 0; i < node->child_count; ++i) {
        reader_node_finalize(node->children + i);
    }

    reader_node_initialize(node);
}

void reader_mesh_initialize(reader_mesh_t* mesh)
{
    mesh->vertices             = NULL;
    mesh->normals              = NULL;
    mesh->texcoords            = NULL;
    mesh->vertex_count         = 0;
    mesh->index_count          = 0;
    mesh->texcoord_layer_count = 0;
    mesh->color_layer_count    = 0;
    reader_material_initialize(&mesh->material);
}

void reader_mesh_finalize(reader_mesh_t* mesh)
{
    hwu32 i;

    reader_material_finalize(&mesh->material);

    if(mesh->colors != NULL) {
        for(i = 0; i < mesh->color_layer_count; ++i) {
            HW_SAFE_FREE(mesh->colors[i]);
        }
        HW_SAFE_FREE(mesh->colors);
    }

    if(mesh->texcoords != NULL) {
        for(i = 0; i < mesh->texcoord_layer_count; ++i) {
            HW_SAFE_FREE(mesh->texcoords[i]);
        }
        HW_SAFE_FREE(mesh->texcoords);
    }

    HW_SAFE_FREE(mesh->normals);
    HW_SAFE_FREE(mesh->indices);
    HW_SAFE_FREE(mesh->vertices);

    reader_mesh_initialize(mesh);
}

void reader_material_initialize(reader_material_t* material)
{
    hwg_color4_f32_set_scaler(&material->diffuse_color, 0xFF);
    hwg_color4_f32_set_scaler(&material->specular_color, 0xFF);
    hwg_color4_f32_set_scaler(&material->ambient_color, 0xFF);
    hwg_color4_f32_set_scaler(&material->emissive_color, 0xFF);
    material->diffuse_textures      = NULL;
    material->diffuse_texture_count = 0;
}

void reader_material_finalize(reader_material_t* material)
{
    hwu32 i;

    for(i = 0; i < material->diffuse_texture_count; ++i) {
        reader_texture_finalize(material->diffuse_textures + i);
    }
    HW_SAFE_FREE(material->diffuse_textures);

    reader_material_initialize(material);
}

void reader_texture_initialize(reader_texture_t* texture)
{
    memset(texture->path, 0, sizeof(texture->path));
    texture->type         = HWG_TEXTURE_TYPE_NONE;
    texture->mapping      = HWG_TEXTURE_MAPPING_UV;
    texture->wrap         = HWG_TEXTURE_WRAP_REPEAT;
    texture->op           = HWG_TEXTURE_OP_MULTIPLY;
    texture->blend_factor = 1.0f;
    texture->flags        = 0;
}

void reader_texture_finalize(reader_texture_t* texture)
{
    reader_texture_initialize(texture);
}

void reader_initialize(reader_t* reader)
{
    reader_node_initialize(&reader->root);
}

void reader_finalize(reader_t* reader)
{
    reader_node_finalize(&reader->root);
}

hwbool reader_read(reader_t* reader, const char* input_path)
{
    const struct aiScene* scene  = NULL;
    hwbool                result = HW_FALSE;

    if(input_path != NULL) {
        scene = aiImportFile(input_path, 0);
        if(scene != NULL) {
            read_node(&reader->root, scene, scene->mRootNode);
            aiReleaseImport(scene);
        }
    }

    return result;
}

void read_node(reader_node_t* out, const struct aiScene* scene, const struct aiNode* input)
{
    hwu32 i;

    HW_NULL_ASSERT(out);

    if(input != NULL) {
        if(input->mNumMeshes > 0) {
            out->meshes = (reader_mesh_t*)hw_malloc(sizeof(reader_mesh_t) * input->mNumMeshes);
            for(i = 0; i < input->mNumMeshes; ++i) {
                reader_mesh_initialize(out->meshes + i);
                read_mesh(out->meshes + i, scene, scene->mMeshes[input->mMeshes[i]]);
            }
            out->mesh_count = input->mNumMeshes;
        }
        memcpy(&out->local_transform, &input->mTransformation, sizeof(out->local_transform));

        if(input->mNumChildren > 0) {
            out->children = (reader_node_t*)hw_malloc(sizeof(reader_node_t) * input->mNumChildren);
            for(i = 0; i < input->mNumChildren; ++i) {
                reader_node_initialize(out->children + i);
                read_node(out->children + i, scene, input->mChildren[i]);
            }
            out->child_count = input->mNumChildren;
        }
    }
}

void read_mesh(reader_mesh_t* out, const struct aiScene* scene, const struct aiMesh* input)
{
    HW_NULL_ASSERT(out);
    HW_NULL_ASSERT(scene);

    if(input != NULL) {
        if(input->mNumVertices > 0) {
            HW_ASSERT(input->mNumFaces > 0);
            HW_NULL_ASSERT(input->mVertices);

            read_vertices(out, input);
            read_normals(out, input);
            read_colors(out, input);
            read_texcoords(out, input);
            read_indices(out, input);
            read_material(out, scene, input);
        }
    }
}

void read_vertices(reader_mesh_t* out, const struct aiMesh* input)
{
    out->vertices = create_vector3_array(input->mVertices, input->mNumVertices);
    if(out->vertices != NULL) {
        out->vertex_count = input->mNumVertices;
    }
}

void read_normals(reader_mesh_t* out, const struct aiMesh* input)
{
    out->normals = create_vector3_array(input->mNormals, input->mNumVertices);
}

void read_colors(reader_mesh_t* out, const struct aiMesh* input)
{
    hwm_vector4_t** colors    = NULL;
    hwu32           set_count = 0;
    hwu32           i,j;

    if(input != NULL && input->mNumVertices > 0) {
        for(i = 0; i < AI_MAX_NUMBER_OF_COLOR_SETS; ++i) {
            if(input->mColors[i] != NULL) {
                ++set_count;
            }
            else {
                break;
            }
        }

        if(set_count > 0) {
            colors = (hwm_vector4_t**)hw_malloc(sizeof(hwm_vector4_t*) * set_count);

            for(i = 0; i < set_count; ++i) {
                colors[i] = (hwm_vector4_t*)hw_malloc(sizeof(hwm_vector4_t) * input->mNumVertices);
                
                for(j = 0; j < input->mNumVertices; ++j) {
                                 hwm_vector4_t* o = &colors[i][j];
                    const struct aiColor4D*     c = &input->mColors[i][j];

                    o->x = c->r;
                    o->y = c->g;
                    o->z = c->b;
                    o->w = c->a;
                }
            }
        }
    }

    out->colors = colors;
}

void read_texcoords(reader_mesh_t* out, const struct aiMesh* input)
{
    hwm_vector3_t** texcoords = NULL;
    hwu32           set_count = 0;
    hwu32           i,j;

    if(input != NULL && input->mNumVertices > 0) {
        for(i = 0; i < AI_MAX_NUMBER_OF_TEXTURECOORDS; ++i) {
            if(input->mTextureCoords[i] != NULL) {
                ++set_count;
            }
            else {
                break;
            }
        }

        if(set_count > 0) {
            texcoords = (hwm_vector3_t**)hw_malloc(sizeof(hwm_vector3_t*) * set_count);

            for(i = 0; i < set_count; ++i) {
                texcoords[i] = (hwm_vector3_t*)hw_malloc(sizeof(hwm_vector3_t) * input->mNumVertices);

                for(j = 0; j < input->mNumVertices; ++j) {
                                 hwm_vector3_t* o = &texcoords[i][j];
                    const struct aiVector3D*    v = &input->mTextureCoords[i][j];

                    o->x = v->x;
                    o->y = v->y;
                    o->z = v->z;
                }
            }
        }
    }

    out->texcoords = texcoords;
}

void read_indices(reader_mesh_t* out, const struct aiMesh* input)
{
    hwu32  index_count = 0;
    hwu32* indices     = NULL;
    hwu32  counter     = 0;
    hwu32  i,j;

    index_count = get_index_count(input);
    if(index_count > 0) {
        indices = (hwu32*)hw_malloc(sizeof(hwu32) * index_count);
        for(i = 0; i < input->mNumFaces; ++i) {
            for(j = 0; j < input->mFaces[i].mNumIndices; ++j) {
                HW_ASSERT(counter < index_count);

                indices[counter++] = input->mFaces[i].mIndices[j];
            }
        }
    }

    out->indices     = indices;
    out->index_count = index_count;
}

void read_material(reader_mesh_t* out, const struct aiScene* scene, const struct aiMesh* input)
{
    const struct aiMaterial* material = NULL;

    if(scene->mNumMaterials > 0 && (scene->mMaterials != NULL)) {
        material = scene->mMaterials[input->mMaterialIndex];
        if(material != NULL) {
            read_textures(&out->material, material);
            read_material_colors(&out->material, material);
        }
    }
}

void read_material_colors(reader_material_t* out, const struct aiMaterial* input)
{
    get_material_color(&out->diffuse_color, input, AI_MATKEY_COLOR_DIFFUSE);
    get_material_color(&out->specular_color, input, AI_MATKEY_COLOR_SPECULAR);
    get_material_color(&out->ambient_color, input, AI_MATKEY_COLOR_AMBIENT);
    get_material_color(&out->emissive_color, input, AI_MATKEY_COLOR_EMISSIVE);
}

void read_textures(reader_material_t* out, const struct aiMaterial* material)
{
    struct aiString            path;
    enum   aiTextureMapping    mapping       = aiTextureMapping_UV;
    enum   aiTextureOp         op            = aiTextureOp_Multiply;
    enum   aiTextureMapMode    wrap          = aiTextureMapMode_Wrap;
    reader_texture_t*          diffuses      = NULL;
    hwuint                     uv_index      = 0;
    hwf32                      blend_factor  = 1.0f;
    hwuint                     flags         = 0;
    hwu32                      diffuse_count = 0;
    hwu32                      i;

    diffuse_count = aiGetMaterialTextureCount(material, aiTextureType_DIFFUSE);
    diffuses      = (reader_texture_t*)hw_malloc(sizeof(reader_texture_t) * diffuse_count);
    for(i = 0; i < diffuse_count; ++i) {
        enum aiReturn result = aiGetMaterialTexture(material, aiTextureType_DIFFUSE, i, &path, &mapping, &uv_index, &blend_factor, &op, &wrap, &flags);
        if(result == aiReturn_SUCCESS) {
            reader_texture_t* diffuse = diffuses + i;
            diffuse->type         = HWG_TEXTURE_TYPE_DIFFUSE;
            diffuse->mapping      = to_hw_texture_mapping(mapping);
            diffuse->wrap         = to_hw_texture_wrap(wrap);
            diffuse->op           = to_hw_texture_op(op);
            diffuse->blend_factor = blend_factor;
            diffuse->flags        = flags;
        }
    }

    out->diffuse_textures      = diffuses;
    out->diffuse_texture_count = diffuse_count;
}

hwm_vector3_t* create_vector3_array(const struct aiVector3D* source, hwu32 count)
{
    hwm_vector3_t* out = NULL;
    hwu32          i;

    if(source != NULL && count > 0) { 
        out = (hwm_vector3_t*)hw_malloc(sizeof(hwm_vector3_t) * count);
        for(i = 0; i < count; ++i) {
            const struct aiVector3D* v = source + i;

            out[i].x = v->x;
            out[i].y = v->y;
            out[i].z = v->z;
        }
    }

    return out;
}

hwg_texture_mapping_t to_hw_texture_mapping(enum aiTextureMapping mapping)
{
    switch(mapping) {
        case aiTextureMapping_UV:
            return HWG_TEXTURE_MAPPING_UV;

        case aiTextureMapping_SPHERE:
            return HWG_TEXTURE_MAPPING_SPHERE;

        case aiTextureMapping_CYLINDER:
            return HWG_TEXTURE_MAPPING_CYLINDER;

        case aiTextureMapping_BOX:
            return HWG_TEXTURE_MAPPING_BOX;

        case aiTextureMapping_PLANE:
            return HWG_TEXTURE_MAPPING_PLANE;
    }

    return HWG_TEXTURE_MAPPING_UNKOWN;
}

hwg_texture_wrap_t to_hw_texture_wrap(enum aiTextureMapMode wrap)
{
    switch(wrap) {
        case aiTextureMapMode_Wrap:
            return HWG_TEXTURE_WRAP_REPEAT;

        case aiTextureMapMode_Clamp:
            return HWG_TEXTURE_WRAP_CLAMP;

        case aiTextureMapMode_Decal:
            return HWG_TEXTURE_WRAP_DECAL;

        case aiTextureMapMode_Mirror:
            return HWG_TEXTURE_WRAP_MIRROR;
    }

    return HWG_TEXTURE_WRAP_UNKOWN;
}

hwu32 get_index_count(const struct aiMesh* mesh)
{
    return mesh->mNumFaces * 3;
}

hwg_texture_op_t to_hw_texture_op(enum aiTextureOp op)
{
    switch(op) {
        case aiTextureOp_Multiply:
            return HWG_TEXTURE_OP_MULTIPLY;

        case aiTextureOp_Add:
            return HWG_TEXTURE_OP_ADD;

        case aiTextureOp_Subtract:
            return HWG_TEXTURE_OP_SUBTRACT;

        case aiTextureOp_Divide:
            return HWG_TEXTURE_OP_DIVIDE;

        case aiTextureOp_SmoothAdd:
            return HWG_TEXTURE_OP_SMOOTH_ADD;

        case aiTextureOp_SignedAdd:
            return HWG_TEXTURE_OP_SIGNED_ADD;
    }

    return HWG_TEXTURE_OP_SIGNED_ADD;
}

hwbool get_material_color(hwg_color4_f32_t* out, const struct aiMaterial* material, const char* key, hwuint type, hwuint index)
{
    struct aiColor4D color;
    
    if(aiGetMaterialColor(material, key, type, index, &color) == AI_SUCCESS) {
        out->r = color.r;
        out->g = color.g;
        out->b = color.b;
        out->a = color.a;

        return HW_TRUE;
    }
    else {
        return HW_FALSE;
    }
}

