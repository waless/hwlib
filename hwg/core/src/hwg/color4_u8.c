#include "hwg/color4_u8.h"

void hwg_color4_u8_set_scaler(hwg_color4_u8_t* out, hwu8 scaler)
{
    out->elements.r = scaler;
    out->elements.g = scaler;
    out->elements.b = scaler;
    out->elements.a = scaler;
}

void hwg_color4_u8_set_color4_f32(hwg_color4_u8_t* out, const struct hwg_color4_f32_t* input)
{
    hwg_color4_f32_to_color4_u8(out, input);
}

void hwg_color4_u8_to_color4_f32(struct hwg_color4_f32_t* out, hwg_color4_u8_t input)
{
    hwg_color4_f32_set_color4_u8(out, input);
}

