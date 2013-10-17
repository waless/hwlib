#ifndef HWM_FIXED32_H_
#define HWM_FIXED32_H_

#include <hw/types.h>

typedef hws32 hwm_fixed32_t;

#define HWM_FIXED32_ONE    (0x00010000)
#define HWM_FIXED32_HALF   (0x00008000)
#define HWM_FIXED32_PI     (0x00031415)
#define HWM_FIXED32_TWO_PI (0x00062831)
#define HWM_FIXED32_TO_RAD_VALUE
#define HWM_FIXED32_TO_DEG_VALUE
#define HWM_FIXED32_TO_RAD(deg) hwm_fixed32_mul(deg, HWM_FIXED32_TO_RAD)
#define HWM_FIXED32_TO_DEG(rad) hwm_fixed32_mul(rad, HWM_FIXED32_TO_DEG)

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

extern hwm_fixed32_t hwm_fixed32_clamp(hwm_fixed32_t b, hwm_fixed32_t e, hwm_fixed32_t v);
extern hwm_fixed32_t hwm_fixed32_repeat(hwm_fixed32_t b, hwm_fixed32_t e, hwm_fixed32_t v);
extern hwm_fixed32_t hwm_fixed32_lerp(hwm_fixed32_t b, hwm_fixed32_t e, hwm_fixed32_t pos);

extern hws32 hwm_fixed32_to_s32(hwm_fixed32_t value);
extern hws64 hwm_fixed32_to_s64(hwm_fixed32_t value);
extern hwf32 hwm_fixed32_to_f32(hwm_fixed32_t value);
extern hwf64 hwm_fixed32_to_f64(hwm_fixed32_t value);

extern hwm_fixed32_t hwm_fixed32_from_s32(hwm_fixed32_t value);
extern hwm_fixed32_t hwm_fixed32_from_s64(hwm_fixed32_t value);
extern hwm_fixed32_t hwm_fixed32_from_f32(hwf32 value);
extern hwm_fixed32_t hwm_fixed32_from_f64(hwf64 value);

#endif

