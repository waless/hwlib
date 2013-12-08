#ifndef HWG_TEXTURE_DX_H_
#define HWG_TEXTURE_DX_H_

#include "hwg/dx.h"

#ifdef __cplusplus
extern "C" {
#endif

/* @enum 色フォーマット列挙型
 *
 * @brief 色の構成要素の識別子です
 *        この識別子は環境別ではなく
 *        ライブラリが認識する識別子です
 */
typedef enum hwg_pixel_format_t {
    HWG_PIXEL_FORMAT_UNKNOWN,
    HWG_PIXEL_FORMAT_R8G8B8,
    HWG_PIXEL_FORMAT_R8G8B8A8,
    HWG_PIXEL_FORMAT_R5G6B5,
    HWG_PIXEL_FORMAT_R4G4B4A4,
    HWG_PIXEL_FORMAT_D24S8,
    HWG_PIXEL_FORMAT_D16,
    HWG_PIXEL_FORMAT_A8,
    HWG_PIXEL_FORMAT_P8,
    HWG_PIXEL_FORMAT_DXT1,
    HWG_PIXEL_FORMAT_DXT3,
    HWG_PIXEL_FORMAT_DXT5,
    HWG_PIXEL_FORMAT_ETC1,
    HWG_PIXEL_FORMAT_ETC2,
    HWG_PIXEL_FORMAT_NUM,
} hwg_pixel_format_t;

typedef enum hwg_texture_wrap_t {
    HWG_TEXTURE_ADDRESS_REPEAT,
    HWG_TEXTURE_ADDRESS_MIRROR,
    HWG_TEXTURE_ADDRESS_CLAMP,
} hwg_texture_wrap_t;

typedef enum hwg_texture_blend_op_t {
    HWG_TEXTURE_BLEND_OP_MULTIPLY,
    HWG_TEXTURE_BLEND_OP_ADD,
    HWG_TEXTURE_BLEND_OP_SUBTRACT,
} hwg_texture_blend_op_t;

typedef enum hwg_texture_filter_t {
    HWG_TEXTURE_FILTER_NONE,
    HWG_TEXTURE_FILTER_POINT,
    HWG_TEXTURE_FILTER_LINEAR,
} hwg_texture_filter_t;

#ifdef __cplusplus
}
#endif

#endif

