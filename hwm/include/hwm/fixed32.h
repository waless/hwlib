#ifndef HWM_FIXED32_H_
#define HWM_FIXED32_H_

#include <hw/types.h>

typedef hws32 hwm_fixed32_t;

#define HWM_FIXED32_ONE    0x00010000
#define HWM_FIXED32_HALF   0x00008000
#define HWM_FIXED32_PI      
#define HWM_FIXED32_TWO_PI

extern hwm_fixed32_t hwm_fixed32_add(hwm_fixed32_t lhs, hwm_fixed32_t rhs);
extern hwm_fixed32_t hwm_fixed32_sub(hwm_fixed32_t lhs, hwm_fixed32_t rhs);
extern hwm_fixed32_t hwm_fixed32_mul(hwm_fixed32_t lhs, hwm_fixed32_t rhs);
extern hwm_fixed32_t hwm_fixed32_div(hwm_fixed32_t lhs, hwm_fixed32_t rhs);
extern hwm_fixed32_t hwm_fixed32_mod(hwm_fixed32_t lhs, hwm_fixed32_t rhs);

extern hwm_fixed32-t hwm_fixed32_sin(hwm_fixed32_t x);
extern hwm_fixed32_t hwm_fixed32_cos(hwm_fixed32_t x);
extern hwm_fixed32_t hwm_fixed32_tan(hwm_fixed32_t x);
extern hwm_fixed32_t hwm_fixed32_asin(hwm_fixed32_t x);
extern hwm_fixed32_t hwm_fixed32_acos(hwm_fixed32_t x);
extern hwm_fixed32_t hwm_fixed32_atan(hwm_fixed32_t x);
extern hwm_fixed32_t hwm_fixed32_atan2(hwm_fixed32_t x, hwm_fix3d32_t y);

extern hwm_fixed32_t hwm_fix3d32_ceil(hwm_fixed32_t value);
extern hwm_fixed32_t hwm_fixed32_floor(hwm_fixed32_t value);
extern hwm_fixed32_t hwm_fixed32_sqrt(hwm_fixed32_t value);
extern hwm_fixed32_t hwm_fixed32_abs(hwm_fixed32_t value);
extern hwm_fixed32_t hwm_fixed32_log(hwm_fixed32_t value);

extern hws32 hwm_fixed32_to_s32(hwm_fixed32_t value);
extern hws64 hwm_fixed32_to_s64(hwm_fixed32_t value);
extern hwf32 hwm_fixed32_to_f32(hwm_fixed32_t value);
extern hwf64 hwm_fixed32_to_f64(hwm_fixed32_t value);

extern hwm_fixed32_t hwm_fixed32_from_s32(hwm_fixed32_t value);
extern hwm_fixed32_t hwm_fixed32_from_s64(hwm_fixed32_t value);
extern hwm_fixed32_t hwm_fixed32_from_f32(hwf32 value);
extern hwm_fixed32_t hwm_fixed32_from_f64(hwf64 value);

#endif

