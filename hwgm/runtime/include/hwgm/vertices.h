#ifndef HWGM_VERTICES_H_
#define HWGM_VERTICES_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwgm_vertices_t {
    /* 頂点数 */
    hwu16  vertex_count;

    /* 頂点配列 */
    hws16* vertices;
    
    /* テクスチャ座標 */
    hwu16* uvs;

    /* 法線 */
    hws16* normals;
} hwgm_vertices_t;

extern void hwgm_vertices_initialize(hwgm_vertices_t* vertices);

#ifdef __cplusplus
}
#endif

#endif

