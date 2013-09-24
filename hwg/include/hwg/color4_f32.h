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

extern const hwg_color4_f32_t k_hwg_color4_f32_zero;
extern const hwg_color4_f32_t k_hwg_color4_f32_one;

extern void hwg_color4_f32_set_scaler(hwg_color4_f32_t* out, hwf32 scaler);

extern hwg_color4_u8_t hwg_color4_f32_to_color4_u8(hwg_color4_f32_t* color);

#ifdef __cplusplus
}
#endif

#endif

