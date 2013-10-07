#ifndef HWGM_WRITER_H_
#define HWGM_WRITER_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwgm_model_t {
    hws8  code[4];
    hwu8  major_version;
    hwu8  minor_version;

    hwu32 node_count;
    hwu32 node_offset;

    hwu32 mesh_count;
    hwu32 mesh_offset;
    
    hwu32 vertex_count;
    hwu32 vertex_offset;

    hwgm_node_t   nodes[];
    hwgm_mesh_t   meshes[];
    hwgm_vertex_t vertices[];
} hwgm_model_t;

typedef struct hwgm_node_t {
} hwgm_node_t;

typedef struct hwgm_mesh_t {
} hwgm_mesh_t;

#ifdef __cplusplus
}
#endif

#endif

