#ifndef HMM_FIXED16ONE_H_
#define HWM_FIXED16ONE_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef s16 hwm_sfixed16_1_14_t;
typedef s16 hwm_ufixed16_1_15_t;

enum {
    HWM_SFIXED16_1_14_SHIFT        = 14,
    HWM_SFIXED16_1_14_ONE          = (1 << HWM_SFIXED16_1_14_SHIFT),
    HWM_SFIXED16_1_14_HALF         = (1 << (HWM_SFIXED16_1_14_SHIFT - 1)),
    HWM_SFIXED16_1_14_SIGN_MASK    = (0x8000),
    HWM_SFIXED16_1_14_INTEGER_MASK = (HWM_SFIXED16_1_14_SIGN_MASK | 
    HWM_SFIXED16_1_14_DECIMAL_MASK = 

    HWM_UFIXED16_1_15_SHIFT = 15,
    HWM_UFIXED16_1_15_ONE   = (1 << HWM_UFIXED16_1_15_SHIFT),
    HWM_UFIXED16_1_15_HALF  = (1 << (HWM_UFIXED16_1_15_SHIFT - 1)),
};

#ifdef __cplusplus
}
#endif

#endif

