#ifndef HWGM_WRITER_H_
#define HWGM_WRITER_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwgm_vertex_t {
    hwu16 vertex_count;
    hwf32 vertices[];
} hwgm_vertex_t;

typedef struct hwgm_mesh_t {
    hwu16 index_count;
    hwu16 indices_offset;
} hwgm_mesh_t;

typedef struct hwgm_node_t {
    hwm_matrix44_t transform;
    hwu16          mesh_count;
    hwu32          mesh_offsets[];
} hwgm_node_t;

typedef struct hwgm_model_t {
    hws8  code[4];
    hwu8  major_version;
    hwu8  minor_version;

    hwu16 node_count;
    hwu32 node_offset;

    hwu16 mesh_count;
    hwu32 mesh_offset;
    
    hwu16 vertex_count;
    hwu32 vertex_offset;

    hwgm_node_t   nodes[];
    hwgm_mesh_t   meshes[];
    hwgm_vertex_t vertices[];
} hwgm_model_t;

#ifdef __cplusplus
}
#endif

#endif

