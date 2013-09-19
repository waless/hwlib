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

static hwm_vector3_t* create_vector3_array(const struct aiVector3D* source, hwu32 count);

void reader_node_initialize(reader_node_t* node)
{
    node->meshes     = NULL;
    node->mesh_count = 0;
    hwm_matrix44_identity(&node->local_transform);
}

void reader_node_finalize(reader_node_t* node)
{
    HW_SAFE_FREE(node->meshes);
    node->mesh_count = 0;
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

void reader_material_initialize(reader_material_t* material)
{
    material->textures      = NULL;
    material->texture_count = 0;
}

void reader_texture_initialize(reader_texture_t* texture)
{
    texture->path = "";
}

void reader_initialize(reader_t* reader)
{
    reader_node_initialize(&reader->root);
}

void reader_finalize(reader_t* reader)
{
    (void)reader;
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
                reader_mesh_initialize(out->meshes + 1);
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

    index_count = input->mNumVertices * 3;
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

