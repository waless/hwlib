#include "reader.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>

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
    hwbool result = HW_FALSE;

    if(input_path != NULL) {
        const struct aiScene* scene = aiImportFile(input_path, 0);
        if(scene != NULL) {
            aiReleaseImport(scene);
        }
    }

    return result;
}

