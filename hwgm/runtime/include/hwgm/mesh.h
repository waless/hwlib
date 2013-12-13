#ifndef HWGM_MESH_H_
#define HWGM_MESH_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwgm_mesh_t {
    /* 頂点情報へのポインタ */
    hwgm_vertex_t*   vertices;

    /* マテリアルへのポインタ */
    hwgm_material_t* material;
} hwgm_mesh_t;

extern void hwgm_mesh_initialize(hwgm_mesh_t* mesh);

#ifdef __cplusplus
}
#endif

#endif

