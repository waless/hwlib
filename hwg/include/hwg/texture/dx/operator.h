#ifndef HWG_TEXTURE_DX_H_
#define HWG_TEXTURE_DX_H_

#include "hwg/dx.h"

typedef enum hwg_surface_format_t {
    HWG_SURFACE_FORMAT_UNKNOWN = -1,
    HWG_SURFACE_FORMAT_R8G8B8,
    HWG_SURFACE_FORMAT_R8G8B8A8,
    HWG_SURFACE_FORMAT_D24S8,
    HWG_SURFACE_FORMAT_R5G6B5,
    HWG_SURFACE_FORMAT_R4G4B4A4,
    HWG_SURFACE_FORMAT_D16,
    HWG_SURFACE_FORMAT_A8,
    HWG_SURFACE_DXT1,
    HWG_SURFACE_DXT3,
    HWG_SURFACE_DXT5,
    HWG_SURFACE_ETC1,
    HWG_SURFACE_ETC2,
} hwg_surface_format_t;

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

