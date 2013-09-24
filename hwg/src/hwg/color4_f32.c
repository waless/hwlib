#include "hwg/color4_f32.h"

const hwg_color4_f32_t k_hwg_color4_f32_zero = {0.0f, 0.0f, 0.0f, 0.0f};
const hwg_color4_f32_t k_hwg_color4_f32_one  = {1.0f, 1.0f, 1.0f, 1.0f};

void hwg_color4_f32_set_scaler(hwg_color4_f32_t* out, hwf32 scaler)
{
    out->r = scaler;
    out->g = scaler;
    out->b = scaler;
    out->a = scaler;
}

hwg_color4_u8_t hwg_color4_f32_to_color4_u8(hwg_color4_f32_t* color)
{
    hwg_color4_u8_t out;

    out.elements.r = (hwu8)(color->r * 255.0f);
}

