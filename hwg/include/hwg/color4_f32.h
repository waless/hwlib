#ifndef HWG_COLOR4_F32_H_
#define HWG_COLOR4_F32_H_

#include <hw/types.h>
#include "hwg/color4_u8.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwg_color4_f32_t {
    hwf32 r;
    hwf32 g;
    hwf32 b;
    hwf32 a;
} hwg_color4_f32_t;

extern const hwg_color4_f32_t HWG_COLOR4_F32_ZERO;
extern const hwg_color4_f32_t HWG_COLOR4_F32_ONE;

extern void hwg_color4_f32_set_scaler(hwg_color4_f32_t* out, hwf32 scaler);
extern void hwg_color4_f32_set_color4_u8(hwg_color4_f32_t* out, hwg_color4_u8_t input);

extern void hwg_color4_f32_to_color4_u8(hwg_color4_u8_t* out, hwg_color4_f32_t* color);

#ifdef __cplusplus
}
#endif

#endif

