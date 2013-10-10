#ifndef HWM_VECTOR2_H_
#define HWM_VECTOR2_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwm_vector2_t {
    hwf32 x;
    hwf32 y;
} hwm_vector2_t;

extern const hwm_vector2_t HWM_VECTOR2_ZERO;
extern const hwm_vector2_t HWM_VECTOR2_ONE;

extern void hwm_vector2_set_zero(hwm_vector2_t* out);
extern void hwm_vector2_set_one(hwm_vector2_t* out);
extern void hwm_vector2_set_scaler(hwm_vector2_t* out, hwf32 scaler);

extern void hwm_vector2_add(hwm_vector2_t* out, const hwm_vector2_t* lhs, const hwm_vector2_t* rhs);
extern void hwm_vector2_add_scaler(hwm_vector2_t* out, const hwm_vector2_t* v, hwf32 scaler);
extern void hwm_vector2_sub(hwm_vector2_t* out, const hwm_vector2_t* lhs, const hwm_vector2_t* rhs);
extern void hwm_vector2_sub_scaler(hwm_vector2_t* out, const hwm_vector2_t* v, hwf32 scaler);
extern void hwm_vector2_mul(hwm_vector2_t* out, const hwm_vector2_t* lhs, const hwm_vector2_t* rhs);
extern void hwm_vector2_mul_scaler(hwm_vector2_t* out, const hwm_vector2_t* v, hwf32 scaler);
extern void hwm_vector2_div(hwm_vector2_t* out, const hwm_vector2_t* lhs, const hwm_vector2_t* rhs);
extern void hwm_vector2_div_scaler(hwm_vector2_t* out, const hwm_vector2_t* v, hwf32 scaler);
extern hwf32 hwm_vector2_length(const hwm_vector2_t* v);
extern hwf32 hwm_vector2_length_squared(const hwm_vector2_t* v);
extern void hwm_vector2_normalize(hwm_vector2_t* out, const hwm_vector2_t* v);
extern void hwm_vector2_abs(hwm_vector2_t* out, const hwm_vector2_t* v);
extern void hwm_vector2_perpendicular(hwm_vector2_t* out, const hwm_vector2_t* v);
extern hwf32 hwm_vector2_distance(const hwm_vector2_t* v1, const hwm_vector2_t* v2);
extern hwf32 hwm_vector2_distance_squared(const hwm_vector2_t* v1, const hwm_vector2_t* v2);
extern hwf32 hwm_vector2_dot(const hwm_vector2_t* v1, const hwm_vector2_t* v2);
extern hwf32 hwm_vector2_determinant(const hwm_vector2_t* v1, const hwm_vector2_t* v2);
extern void hwm_vector2_min(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2);
extern void hwm_vector2_max(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2);
extern void hwm_vector2_clamp(hwm_vector2_t* out, const hwm_vector2_t* v, const hwm_vector2_t* min, const hwm_vector2_t* max);
extern void hwm_vector2_repeat(hwm_vector2_t* out, const hwm_vector2_t* v, const hwm_vector2_t* min, const hwm_vector2_t* max);
extern void hwm_vector2_lerp(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2, hwf32 pos);
extern void hwm_vector2_slerp(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2, hwf32 pos);
extern void hwm_vector2_move_to(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2, hwf32 length);
extern void hwm_vector2_turn_to(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2, hwf32 angle);
extern hwf32 hwm_vector2_angle(const hwm_vector2_t* v1, const hwm_vector2_t* v2);
extern void hwm_vector2_rotate_vector(hwm_vector2_t* out, const hwm_vector2_t* v, const hwm_vector2_t* rotation);
extern void hwm_vector2_rotate_scaler(hwm_vector2_t* out, const hwm_vector2_t* v, hwf32 angle);
extern void hwm_vector2_rotate(hwm_vector2_t* out, hwf32 angle);
extern void hwm_vector2_reflect(hwm_vector2_t* out, const hwm_vector2_t* v, const hwm_vector2_t* normal);
extern void hwm_vector2_project_on_line(hwm_vector2_t* out, const hwm_vector2_t* v, const hwm_vector2_t* point, const hwm_vector2_t* direction);

extern hwbool hwm_vector2_is_unit(const hwm_vector2_t* v, hwf32 epsilon);
extern hwbool hwm_vector2_is_zero(const hwm_vector2_t* v);
extern hwbool hwm_vector2_is_one(const hwm_vector2_t* v);
extern hwbool hwm_vector2_is_nan(const hwm_vector2_t* v);

#ifdef __cplusplus
}
#endif

#endif

