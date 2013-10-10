#ifndef HWM_MATH_H_
#define HWM_MATH_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HWM_PI
#   undef HWM_PI
#endif
#define HWM_PI (3.1415926535897932384626433832795f)

#ifdef HWM_TWO_PI
#   undef HWM_TWO_PI
#endif
#define HWM_TWO_PI (6.283185307179586476925286766559f)

#ifdef HWM_TO_RAD_VALUE
#   undef HWM_TO_RAD_VALUE
#endif
#define HWM_TO_RAD_VALUE (0.01745329251994329576923690768489f)

#ifdef HWM_TO_DEG_VALUE
#   undef HWM_TO_DEG_VALUE
#endif
#define HWM_TO_DEG_VALUE (57.295779513082320876798154814105f)

#ifdef HWM_TO_RAD
#   undef HWM_TO_RAD
#endif
#define HWM_TO_RAD(deg) ((deg) * HWM_TO_RAD_VALUE)

#ifdef HWM_TO_DEG
#   undef HWM_TO_DEG
#endif
#define HWM_TO_DEG(rad) ((rad) * HWM_TO_DEG_VALUE)

extern hwf32 hwm_sinf(hwf32 rad);
extern hwf32 hwm_asinf(hwf32 rad);
extern hwf32 hwm_cosf(hwf32 rad);
extern hwf32 hwm_acosf(hwf32 rad);
extern hwf32 hwm_tanf(hwf32 rad);
extern hwf32 hwm_atanf(hwf32 rad);
extern hwf32 hwm_atan2f(hwf32 y, hwf32 x);
extern hwf32 hwm_cotf(hwf32 rad);
extern hwf32 hwm_absf(hwf32 value);
extern hwf32 hwm_sqrtf(hwf32 value);
extern hwf32 hwm_fmodf(hwf32 value1, hwf32 value2);
extern hwf32 hwm_clamp(hwf32 value, hwf32 min, hwf32 max);
extern hwf32 hwm_repeat(hwf32 value, hwf32 min, hwf32 max);
extern hwf32 hwm_lerp(hwf32 begin, hwf32 end, hwf32 pos);
extern hwbool hwm_is_nan(hwf32 value);

#ifdef __cplusplus
}
#endif

#endif

