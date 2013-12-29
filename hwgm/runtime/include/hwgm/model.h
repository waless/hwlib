#ifndef HWGM_MODEL_H_
#define HWGM_MODEL_H_

#include <hw/types.h>
#include "node.h"
#include "mesh.h"
#include "material.h"
#include "texture.h"
#include "vertices.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwgm_model_t {
    /* マジックコード */
    hws8 code[4];

    /* バージョン情報 */
    hws8 version[8];

    /* ルートノード*/
    hwgm_node_t* root;

    /* 各データ数 */
    hwu16 node_count;
    hwu16 mesh_count;
    hwu16 material_count;
    hwu16 texture_count;
    hwu16 vertices_count;
    
    hwu8 padding[2];
    
    /* 各データへのポインタ */
    hwgm_node_t**     nodes;
    hwgm_mesh_t**     meshes;
    hwgm_material_t** materials;
    hwgm_texture_t**  textures;
    hwgm_vertices_t** vertices;

    /* 以下バイナリ的にはデータが続く
     * 全てサイズが可変であるため
     * メンバとしては持たない */
} hwgm_model_t;

extern void hwgm_model_initialize(hwgm_model_t* model);

#ifdef __cplusplus
}
#endif

#endif

