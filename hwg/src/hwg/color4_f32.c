#include "hwg/color4_f32.h"

const hwg_color4_f32_t HWG_COLOR4_F32_ZERO = {0.0f, 0.0f, 0.0f, 0.0f};
const hwg_color4_f32_t HWG_COLOR4_F32_ONE  = {1.0f, 1.0f, 1.0f, 1.0f};

void hwg_color4_f32_set_scaler(hwg_color4_f32_t* out, hwf32 scaler)
{
    out->r = scaler;
    out->g = scaler;
    out->b = scaler;
    out->a = scaler;
}

void hwg_color4_f32_set_color4_u8(hwg_color4_f32_t* out, hwg_color4_u8_t input)
{
    out->r = (hwf32)input.elements.r / 255.0f;
    out->g = (hwf32)input.elements.g / 255.0f;
    out->b = (hwf32)input.elements.b / 255.0f;
    out->a = (hwf32)input.elements.a / 255.0f;
}

void hwg_color4_f32_to_color4_u8(hwg_color4_u8_t* out, hwg_color4_f32_t* input)
{
    out->elements.r = (hwu8)(input->r * 255.0f);
    out->elements.g = (hwu8)(input->g * 255.0f);
    out->elements.b = (hwu8)(input->b * 255.0f);
    out->elements.a = (hwu8)(input->a * 255.0f);
}

