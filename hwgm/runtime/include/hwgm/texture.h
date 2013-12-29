#ifndef HWGM_TEXTURE_H_
#define HWGM_TEXTURE_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwgm_texture_t {
    /* テクスチャへの外部参照インデックス */
    hwu32 index;

    /* テクスチャのピクセルフォーマット 
     * hwg_pixel_format_t */
    hwu8  format;

    /* アドレス動作定義識別子
     * hwg_texture_wrap_t */
    hwu8  wrap;

    /* ブレンド動作定義識別子
     * hwg_texture_blend_op_t */
    hwu8  blend;

    /* フィルタ動作定義識別子
     * hwg_texture_filter_t */
    hwu8  filter;
} hwgm_texture_t;

extern void hwgm_texture_initialize(hwgm_texture_t* texture);

#ifdef __cplusplus
}
#endif

#endif

