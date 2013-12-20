#ifndef HWGM_WRITER_H_
#define HWGM_WRITER_H_

#include <hw/types.h>
#include <hwcp/type.h>
#include "hwgm/node.h"
#include "reader.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct writer_t {
    hwu32 node_count;
    hwu32 mesh_count;
    hwu32 material_count;
    hwu32 texture_count;
    hwu32 vertices_count;

    hwgm_node_t*     nodes;
    hwgm_mesh_t*     meshes;
    hwgm_material_t* materials;
    hwgm_texture_t*  textures;
    hwgm_vetices_t*  vertices;
} writer_t;

extern void writer_initialize(writer_t* writer);
extern void writer_finalize(writer_t* writer);
extern void writer_run(writer_t* writer, const reader_t* reader);

#ifdef __cplusplus
}
#endif

#endif

