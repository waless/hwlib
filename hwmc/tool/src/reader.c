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
static void read_mesh(reader_mesh_t* out, const struct aiMesh* input);

static hwm_vector3_t*  create_vertex_array(const struct aiVector3D* source, hwu32 vertex_num);
static hwm_vector3_t*  create_normal_array(const struct aiVector3D* source, hwu32 vertex_num);
static hwm_vector4_t** create_color_set_array(const struct aiColor4D* const * source, hwu32 vertex_num);
static hwm_vector3_t** create_texcoord_set_array(const struct aiVector3D* const * source, hwu32 vertex_num);

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
                read_mesh(out->meshes + i, scene->mMeshes[input->mMeshes[i]]);
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

void read_mesh(reader_mesh_t* out, const struct aiMesh* input)
{
    hwu32 counter = 0;
    hwu32 i,j;

    HW_NULL_ASSERT(out);

    if(input != NULL) {
        if(input->mNumVertices > 0) {
            HW_ASSERT(input->mNumFaces > 0);
            HW_NULL_ASSERT(input->mVertices);

            out->vertices  = create_vertex_array(input->mVertices, input->mNumVertices);
            out->normals   = create_normal_array(input->mNormals, input->mNumVertices);
            out->colors    = create_color_array(input->mColors, input->mNumVertices);
            out->texcoords = create_texcoord_array(input->mTextureCoords, input->mNumVertices);

            out->vertex_count = input->mNumVertices;
            out->index_count  = input->mNumVertices * 3;

            out->indices = (hwu32*)hw_malloc(sizeof(hwu32) * out->index_count);
            for(i = 0; i < input->mNumFaces; ++i) {
                for(j = 0; j < input->mFaces[i].mNumIndices; ++j) {
                    out->indices[counter++] = input->mFaces[i].mIndices[j];
                }
            }
        }
    }
}

hwm_vector3_t* create_vertex_array(const struct aiVector3D* source, hwu32 vertex_num)
{
    hwm_vector3_t* out = NULL;
    hwu32          i;

    if(source != NULL && vertex_num > 0) { 
        out = (hwm_vector3_t*)hw_malloc(sizeof(hwm_vector3_t) * vertex_num);
        for(i = 0; i < vertex_num; ++i) {
            const struct aiVector3D* v = source + i;

            out[i].x = v->x;
            out[i].y = v->y;
            out[i].z = v->z;
        }
    }

    return out;
}

hwm_vector3_t* create_normal_array(const struct aiVector3D* source, hwu32 vertex_num)
{
    return create_vertex_array(source, vertex_num);
}

hwm_vector4_t** create_color_set_array(const struct aiColor4D* const * source, hwu32 vertex_num)
{
    hwm_vector4_t** out = NULL;
    hwu32           set_count = 0;
    hwu32           i,j;

    if(source != NULL && vertex_num > 0) {
        for(i = 0; i < AI_MAX_NUMBER_OF_COLOR_SETS; ++i) {
            ++set_count;
        }

        if(set_count > 0) {
            out = (hwm_vector4_t**)hw_malloc(sizeof(hwm_vector4_t*) * set_count);
        }

        out = (hwm_vector4_t*)hw_malloc(sizeof(hwm_vector4_t) * vertex_num);
        for(i = 0; i < vertex_num; ++i) {
            const struct aiColor4D* c = source[i];

            if(c != NULL) {
                out[i].x = c->r;
                out[i].y = c->g;
                out[i].z = c->b;
                out[i].w = c->a;
            }
        }
    }

    return out;
}

hwm_vector3_t** create_texcoord_set_array(const struct aiVector3D* const * source, hwu32 vertex_num)
{
    hwm_vector3_t* out = NULL;
    hwu32          i;

    if(source != NULL && vertex_num > 0) {
        out = (hwm_vector3_t*)hw_malloc(sizeof(hwm_vector3_t) * vertex_num);
        for(i = 0; i < vertex_num; ++i) {
            const struct aiVector3D* v = source[i];

            if(v != NULL) {
                out[i].x = v->x;
                out[i].y = v->y;
                out[i].z = v->z;
            }
        }
    }

    return out;
}

