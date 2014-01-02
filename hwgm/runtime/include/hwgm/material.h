#ifndef HWGM_MATERIAL_H_
#define HWGM_MATERIAL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwgm_material_t {
    /* シェーダへの外部参照インデックス */
    hwu32 shader_index;

    /* テクスチャ数 */
    hwu16 texture_count;

    hwu8  padding[2];

    /* テクスチャへのポインタの配列 */
    hwgm_texture_t** textures;
} hwgm_material_t;

extern void hwgm_material_initialize(hwgm_material_t* material);

#ifdef __cplusplus
}
#endif

#endif

