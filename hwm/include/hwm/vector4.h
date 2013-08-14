#ifndef HWM_VECTOR4_H_
#define HWM_VECTOR4_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwm_vector4_t {
    hwf32 x;
    hwf32 y;
    hwf32 z;
    hwf32 w;
} hwm_vector4_t;

extern const hwm_vector4_t k_hwm_vector4_one;
extern const hwm_vector4_t k_hwm_vector4_zero;
extern const hwm_vector4_t k_hwm_vector4_unit_x;
extern const hwm_vector4_t k_hwm_vector4_unit_y;
extern const hwm_vector4_t k_hwm_vector4_unit_z;
extern const hwm_vector4_t k_hwm_vector4_unit_w;

extern void hwm_vector4_set_zero(hwm_vector4_t* out);
extern void hwm_vector4_set_one(hwm_vector4_t* out);
extern void hwm_vector4_set_unix_x(hwm_vector4_t* out);
extern void hwm_vector4_set_unix_y(hwm_vector4_t* out);
extern void hwm_vector4_set_unix_z(hwm_vector4_t* out);
extern void hwm_vector4_set_unix_w(hwm_vector4_t* out);
extern void hwm_vector4_set_scaler(hwm_vector4_t* out, hwf32 scaler);

extern void hwm_vector4_add(hwm_vector4_t* out, const hwm_vector4_t* lhs, const hwm_vector4_t* rhs);
extern void hwm_vector4_add_scaler(hwm_vector4_t* out, const hwm_vector4_t* v, hwf32 scaler);
extern void hwm_vector4_sub(hwm_vector4_t* out, const hwm_vector4_t* lhs, const hwm_vector4_t* rhs);
extern void hwm_vector4_sub_scaler(hwm_vector4_t* out, const hwm_vector4_t* v, hwf32 scaler);
extern void hwm_vector4_mul(hwm_vector4_t* out, const hwm_vector4_t* lhs, const hwm_vector4_t* rhs);
extern void hwm_vector4_mul_scaler(hwm_vector4_t* out, const hwm_vector4_t* v, hwf32 scaler);
extern void hwm_vector4_div(hwm_vector4_t* out, const hwm_vector4_t* lhs, const hwm_vector4_t* rhs);
extern void hwm_vector4_div_scaler(hwm_vector4_t* out, const hwm_vector4_t* v, hwf32 scaler);
extern hwf32 hwm_vector4_length(const hwm_vector4_t* v);
extern hwf32 hwm_vector4_length_squared(const hwm_vector4_t* v);
extern void hwm_vector4_normalize(hwm_vector4_t* out, const hwm_vector4_t* v);
extern void hwm_vector4_abs(hwm_vector4_t* out, const hwm_vector4_t* v);
extern hwf32 hwm_vector4_distance(const hwm_vector4_t* v1, const hwm_vector4_t* v2);
extern hwf32 hwm_vector4_distance_squared(const hwm_vector4_t* v1, const hwm_vector4_t* v2);
extern hwf32 hwm_vector4_dot(const hwm_vector4_t* v1, const hwm_vector4_t* v2);
extern void hwm_vector4_min(hwm_vector4_t* out, const hwm_vector4_t* v1, const hwm_vector4_t* v2);
extern void hwm_vector4_max(hwm_vector4_t* out, const hwm_vector4_t* v1, const hwm_vector4_t* v2);
extern void hwm_vector4_clamp(hwm_vector4_t* out, const hwm_vector4_t* v, const hwm_vector4_t* min, const hwm_vector4_t* max);
extern void hwm_vector4_repeat(hwm_vector4_t* out, const hwm_vector4_t* v, const hwm_vector4_t* min, const hwm_vector4_t* max);
extern void hwm_vector4_lerp(hwm_vector4_t* out, const hwm_vector4_t* v1, const hwm_vector4_t* v2, hwf32 pos);
extern void hwm_vector4_move_to(hwm_vector4_t* out, const hwm_vector4_t* v1, const hwm_vector4_t* v2, hwf32 length);

extern hwbool hwm_vector4_is_unit(const hwm_vector4_t* v, hwf32 epsilon);
extern hwbool hwm_vector4_is_zero(const hwm_vector4_t* v);
extern hwbool hwm_vector4_is_one(const hwm_vector4_t* v);
extern hwbool hwm_vector4_is_nan(const hwm_vector4_t* v);

#ifdef __cplusplus
}
#endif::

#endif

