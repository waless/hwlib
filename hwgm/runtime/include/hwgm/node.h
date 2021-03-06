#ifndef HWGM_NODE_H_
#define HWGM_NODE_H_

#include <hw/types.h>
#include <hwm/matrix44.h>
#include "mesh.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HWGM_NODE_NAME_MAX 64

typedef struct hwgm_node_t {
    /* ノード名 */
    hwu8           name[HWGM_NODE_NAME_MAX];

    /* ローカル変換行列 */
    hwm_matrix44_t transform;

    /* バウンディング球 */
    hwf32          radius;

    /* 使用するメッシュ数 */
    hwu16          mesh_count;

    /* 子供の数 */
    hwu16          child_count;

    /* 使用するメッシュへのポインタの配列 */
    hwgm_mesh_t**  meshes;

    /* 子のノードへのポインタの配列 */
    hwgm_node_t**  children;
} hwgm_node_t;

extern void hwgm_node_initialize(hwgm_node_t* node);

#ifdef __cplusplus
}
#endif

#endif

