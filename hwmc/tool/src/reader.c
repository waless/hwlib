#include "reader.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <hw/memory/allocator.h>
#include <hw/debug/assert.h>

static void read_node(reader_node_t* out, const struct aiScene* scene, const struct aiNode* input);
static void read_mesh(reader_mesh_t* out, const struct aiMesh* input);
static hwm_vector3_t* create_vector3_array(const struct aiVector3D* source);

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
    reader_node_t         root;
    hwbool                result = HW_FALSE;

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

void read_node(reader_node_t* out, const struct aiScene* scene, const struct aiNode* input)
{
    hwu32 i;

    HW_NULL_ASSERT(out);

    if(input != NULL) {
        if(input->mNumMeshes > 0) {
            out->meshes = (reader_mesh_t*)hw_malloc(sizeof(reader_mesh_t) * input->mNumMeshes);
            for(i = 0; i < input->mNumMeshes; ++i) {
                read_mesh(out->meshes + i, scene->mMeshes[input->mMeshes[i]]);
            }
            out->mesh_count = input->mNumMeshes;
        }
        memcpy(&out->local_transform, &input->mTransformation, sizeof(out->local_transform));

        if(input->mNumChildren > 0) {
            out->children = (reader_node_t*)hw_malloc(sizeof(reader_node_t) * input->mNumChildren);
            for(i = 0; i < input->mNumChildren; ++i) {
                read_node(out->children + i, scene, input->mChildren[i]);
            }
            out->child_count = input->mNumChildren;
        }
    }
}

void read_mesh(reader_mesh_t* out, const struct aiMesh* input)
{
                 hwu32       vertex_count = 0;
                 hwu32       index_count  = 0;
                 hwu32       index        = 0;
                 hwu32       counter      = 0;
    const struct aiFace*     face         = NULL;
    const struct aiVector3D* vertex       = NULL;
    const struct aiVector3D* normal       = NULL;
    const struct aiColor4D*  color        = NULL;
    const struct aiVector3D* texcoord     = NULL;
                 hwu32       i;
                 hwu32       j;

    HW_NULL_ASSERT(out);

    if(input != NULL) {
        if(input->mNumVertices > 0) {
            HW_ASSERT(input->mNumFaces > 0);
            HW_NULL_ASSERT(input->mVertices);

            out->vertices = create_vector3_array(input->mVertices, input->mNumVertices);
            out->normals = create_vector3_array(input->mNormals, input->mNumVertices);
            out->colors = ;
            out->texcoords = ;

            out->vertex_count = input->mNumVertices;


            out->indices     = (hwu32*)hw_malloc(sizeof(hwu32) * index_count);
            out->index_count = input->mNumVertices * 3;
            for(i = 0; i < input->mNumFaces; ++i) {
                face = input->mFaces + i;
                for(j = 0; j < face->mNumIndices; ++j) {
                    out->indices[counter++] = face->mIndices[j];
                }
            }
        }
    }
}

hwm_vector3_t* create_vector3_array(const struct aiVector3D* source, hwu32 count)
{
    hwm_vector3_t* out = NULL;
    hwu32          i;

    if(source != NULL && count > 0) { 
        hwm_vector3_t* out = (hwm_vector3_t*)hw_malloc(sizeof(hwm_vector3_t) * count);
        for(i = 0; i < count; ++i) {
            out[i].x = source[i].x;
            out[i].y = source[i].y;
            out[i].z = source[i].z;
        }
    }

    return out;
}

