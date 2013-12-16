#ifndef HWGM_MODEL_H_
#define HWGM_MODEL_H_

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
    hwu32 node_count;
    hwu32 mesh_count;
    hwu32 material_count;
    hwu32 texture_count;
    hwu32 vertices_count;
    
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

