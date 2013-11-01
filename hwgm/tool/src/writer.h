#ifndef HWGM_WRITER_H_
#define HWGM_WRITER_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HWGM_ITEM_NAME_MAX 64
#define HWGM_NODE_NAME_MAX 64

typedef struct hwgm_vertices_t {
    hwu16 vertex_count;
    hws16 vertices[];
    hwu16 uvs[];
    hws16 normals[];
} hwgm_vertex_t;

typedef struct hwgm_material_t {
    hwu32 shader_index;
    hwu32 jj
} hwgm_material_t;

typedef struct hwgm_mesh_t {
    hwgm_vertex_t* vertices_ptr;
} hwgm_mesh_t;

typedef struct hwgm_node_t {
    hwm_matrix44_t transform;
    hwu16          radius;
    hwu16          mesh_count;
    hwgm_mesh_t*   mesh_ptrs[];
    hwu8           name[HWGM_NODE_NAME_MAX];
} hwgm_node_t;

typedef struct hwgm_model_t {
    hws8  code[4];
    hwu8  major_version;
    hwu8  minor_version;
    
    hwu16 vertex_count;

    hwgm_node_t* root_ptr;

    hwgm_vertexx_t vertices[];
} hwgm_model_t;

#ifdef __cplusplus
}
#endif

#endif

