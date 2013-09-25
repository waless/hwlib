#ifndef HWG_COLOR4_U8_H_
#define HWG_COLOR4_U8_H_

#include <hw/types.h>
#include "hwg/color4_f32.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef union hwg_color4_u8_t {
    struct elements {
        hwu8 a;
        hwu8 b;
        hwu8 g;
        hwu8 r;
    };

    hwu32 value;
} hwg_color4_u8_t;

#define k_hwg_color4_u8_zero 0
#define k_hwg_color4_u8_one  0xFFFFFFFF

extern void hwg_color4_u8_set_scaler(union hwg_color4_u8_t* out, hwu8 scaler);

extern void hwg_color4_u8_to_color4_f32(struct hwg_color4_f32_t* out, union hwg_color4_u8_t input);

#ifdef __cplusplus
}
#endif

#endif

