#ifndef HWGM_WRITER_H_
#define HWGM_WRITER_H_

#if defined(HWG_GL)
#elif defined(HWG_DX)
#elif defined(HWG_MANTLE)
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwgm_model_t {
    hwgm_node_t root;
} hwgm_model_t;

typedef struct hwgm_node_t {
    hwm_matrix44_t transform;
} hwgm_node_t;

typedef struct hwgm_mesh_t {
} hwgm_mesh_t;

typedef struct hwgm_material_t {
} hwgm_material_t;

#ifdef __cplusplus
}
#endif

#endif

