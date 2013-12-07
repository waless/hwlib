#ifndef HWG_TEXTURE_DX_H_
#define HWG_TEXTURE_DX_H_

#include "hwg/dx.h"

/* @enum 色フォーマット列挙型
 *
 * @brief 色の構成要素の識別子です
 *        この識別子は環境別ではなく
 *        ライブラリが認識する識別子です
 */
typedef enum hwg_color_format_t {
    HWG_COLOR_FORMAT_UNKNOWN = -1,
    HWG_COLOR_FORMAT_R8G8B8,
    HWG_COLOR_FORMAT_R8G8B8A8,
    HWG_COLOR_FORMAT_D24S8,
    HWG_COLOR_FORMAT_R5G6B5,
    HWG_COLOR_FORMAT_R4G4B4A4,
    HWG_COLOR_FORMAT_D16,
    HWG_COLOR_FORMAT_A8,
    HWG_COLOR_FORMAT_P8,
    HWG_COLOR_FORMAT_DXT1,
    HWG_COLOR_FORMAT_DXT3,
    HWG_COLOR_FORMAT_DXT5,
    HWG_COLOR_FORMAT_ETC1,
    HWG_COLOR_FORMAT_ETC2,
} hwg_color_format_t;

/* @enum テクスチャフォーマット列挙型
 *
 * @brief テクスチャフォーマット識別子です
 *        この識別子は抽象化されてもので、
 *        ライブラリが環境差を吸収する意図で
 *        指定されるものです
 *        詳細な指定はhwg_color_format_tを
 *        使用します
 */
typedef enum hwg_texture_format_t {
    HWG_TEXTURE_FORMAT_UNKNOWN = -1,
    HWG_TEXTURE_FORMAT_FULL_COLOR,
    HWG_TEXTURE_FORMAT_TRUE_COLOR,
    HWG_TEXTURE_FORMAT_COMPRESS_NONE_ALPHA,
    HWG_TEXTURE_FORMAT_COMPRESS_WITH_ALPHA,
    HWG_TEXTURE_FORMAT_DEPTH,
    HWG_TEXTURE_FORMAT_DEPTH_WITH_STENSIL,
} hwg_texture_format_t;

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

#endif

