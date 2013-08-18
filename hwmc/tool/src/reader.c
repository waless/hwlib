#include "reader.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>

static void read_mesh(reader_mesh_t* out, const struct aiMesh* input);

void reader_initialize(reader_t* reader)
{
    reader->meshs      = NULL;
    reader->mesh_count = 0;
}

void reader_finalize(reader_t* reader)
{
    (void)reader;
}

hwbool reader_read(reader_t* reader, const char* input_path)
{
    hwbool                result = HW_FALSE;
    const struct aiScene* scene  = NULL;
    int                   i;

    if(input_path != NULL) {
        scene = aiImportFile(input_path, 0);
        if(scene != NULL) {
            for(i = 0; i < scene->mNumMeshs; ++i) {
                read_mesh(scene->meshs[i]);
            }
            aiReleaseImport(scene);
        }
    }

    return result;
}

void read_mesh(reader_mesh_t* out, const struct aiMesh* input)
{
}

