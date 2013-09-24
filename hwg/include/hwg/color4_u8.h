#ifndef HWG_COLOR4_U8_H_
#define HWG_COLOR4_U8_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef union hwg_color4_u32_t {
    struct elements {
        hwu8 a;
        hwu8 b;
        hwu8 g;
        hwu8 r;
    };

    hwu32 value;
} hwg_color4_u8_t;

#define k_hwg_color4_u32_zero 0
#define k_hwg_color4_u32_one  0xFFFFFFFF

extern void hwg_color4_u8_set_scaler(hwg_color4_u8_t* out, hwu8 scaler);

#ifdef __cplusplus
}
#endif

#endif

