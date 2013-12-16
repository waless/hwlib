#include "hwgm/texture.h"

void hwgm_texture_initialize(hwgm_texture_t* texture)
{
    texture->index  = 0;
    texture->format = HWG_PIXEL_FORMAT_UNKNOWN;
    texture->wrap   = HWG_TEXTURE_WRAP_CLAMP;
    texture->blend  = HWG_TEXTURE_BLEND_OP_MULTIPLY;
    texture->filter = HWG_TEXTURE_FILTER_NONE;
}

