#include "reader.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <hw/memory/allocator.h>
#include <hw/debug/assert.h>

static void read_node(reader_node_t* out, const struct aiScene* scene, const struct aiNode* node);
static void read_mesh(reader_mesh_t* out, const struct aiMesh* input);

void reader_node_initialize(reader_node_t* node)
{
    node->meshes     = NULL;
    node->mesh_count = 0;
    hwm_matrix44_identity(&node->local_transform);
}

void reader_mesh_initialize(reader_mesh_t* mesh)
{
    mesh->vertices       = NULL;
    mesh->normals        = NULL;
    mesh->texcoords      = NULL;
    mesh->vertex_count   = 0;
    mesh->materials      = NULL;
    mesh->material_count = 0;
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
    reader_node_t         root;
    hwbool                result = HW_FALSE;
    int                   i;

    if(input_path != NULL) {
        scene = aiImportFile(input_path, 0);
        if(scene != NULL) {
            reader_node_initialize(&root);
            read_node(&root, scene, scene->mRootNode);
            aiReleaseImport(scene);
        }
    }

    return result;
}

void read_node(reader_node_t* out, const struct aiScene* scene, const struct aiNode* node)
{
    hwu32 i;

    HW_NULL_ASSERT(out);

    if(node != NULL) {
        if(node->mNumMeshs > 0) {
            out->meshes = (reader_mesh_t*)hw_malloc(sizeof(reader_mesh_t) * node->mNumMeshs);
            for(i = 0; i < node->mNumMeshs; ++i) {
                read_mesh(out->meshes + i, scene->mMeshes[node->mMeshes[i]]);
            }
            out->mesh_count = node->mNumMeshs;
        }
    }
}

void read_mesh(reader_mesh_t* out, const struct aiMesh* input)
{
}

