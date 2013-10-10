#ifndef HWM_VECTOR3_H_
#define HWM_VECTOR3_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct hwm_vector2_t;

typedef struct hwm_vector3_t {
    hwf32 x;
    hwf32 y;
    hwf32 z;
} hwm_vector3_t;

extern const hwm_vector3_t HWM_VECTOR3_ONE;
extern const hwm_vector3_t HWM_VECTOR3_ZERO;
extern const hwm_vector3_t HWM_VECTOR3_UNIT_X;
extern const hwm_vector3_t HWM_VECTOR3_UNIT_Y;
extern const hwm_vector3_t HWM_VECTOR3_UNIT_Z;

extern void hwm_vector3_set_zero(hwm_vector3_t* out);
extern void hwm_vector3_set_one(hwm_vector3_t* out);
extern void hwm_vector3_set_unix_x(hwm_vector3_t* out);
extern void hwm_vector3_set_unix_y(hwm_vector3_t* out);
extern void hwm_vector3_set_unix_z(hwm_vector3_t* out);
extern void hwm_vector3_set_scaler(hwm_vector3_t* out, hwf32 scaler);

extern void hwm_vector3_add(hwm_vector3_t* out, const hwm_vector3_t* lhs, const hwm_vector3_t* rhs);
extern void hwm_vector3_add_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 scaler);
extern void hwm_vector3_sub(hwm_vector3_t* out, const hwm_vector3_t* lhs, const hwm_vector3_t* rhs);
extern void hwm_vector3_sub_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 scaler);
extern void hwm_vector3_mul(hwm_vector3_t* out, const hwm_vector3_t* lhs, const hwm_vector3_t* rhs);
extern void hwm_vector3_mul_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 scaler);
extern void hwm_vector3_div(hwm_vector3_t* out, const hwm_vector3_t* lhs, const hwm_vector3_t* rhs);
extern void hwm_vector3_div_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 scaler);
extern hwf32 hwm_vector3_length(const hwm_vector3_t* v);
extern hwf32 hwm_vector3_length_squared(const hwm_vector3_t* v);
extern void hwm_vector3_normalize(hwm_vector3_t* out, const hwm_vector3_t* v);
extern void hwm_vector3_abs(hwm_vector3_t* out, const hwm_vector3_t* v);
extern void hwm_vector3_perpendicular(hwm_vector3_t* out, const hwm_vector3_t* v);
extern hwf32 hwm_vector3_distance(const hwm_vector3_t* v1, const hwm_vector3_t* v2);
extern hwf32 hwm_vector3_distance_squared(const hwm_vector3_t* v1, const hwm_vector3_t* v2);
extern hwf32 hwm_vector3_dot(const hwm_vector3_t* v1, const hwm_vector3_t* v2);
extern void hwm_vector3_cross(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2);
extern void hwm_vector3_min(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2);
extern void hwm_vector3_max(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2);
extern void hwm_vector3_clamp(hwm_vector3_t* out, const hwm_vector3_t* v, const hwm_vector3_t* min, const hwm_vector3_t* max);
extern void hwm_vector3_repeat(hwm_vector3_t* out, const hwm_vector3_t* v, const hwm_vector3_t* min, const hwm_vector3_t* max);
extern void hwm_vector3_lerp(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2, hwf32 pos);
extern void hwm_vector3_slerp(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2, hwf32 pos);
extern void hwm_vector3_move_to(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2, hwf32 length);
extern void hwm_vector3_turn_to(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2, hwf32 angle);
extern hwf32 hwm_vector3_angle(const hwm_vector3_t* v1, const hwm_vector3_t* v2);
extern void hwm_vector3_rotate_x_vector(hwm_vector3_t* out, const hwm_vector3_t* v, const struct hwm_vector2_t* rotation);
extern void hwm_vector3_rotate_x_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 angle);
extern void hwm_vector3_rotate_y_vector(hwm_vector3_t* out, const hwm_vector3_t* v, const struct hwm_vector2_t* rotation);
extern void hwm_vector3_rotate_y_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 angle);
extern void hwm_vector3_rotate_z_vector(hwm_vector3_t* out, const hwm_vector3_t* v, const struct hwm_vector2_t* rotation);
extern void hwm_vector3_rotate_z_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 angle);
extern void hwm_vector3_reflect(hwm_vector3_t* out, const hwm_vector3_t* v, const hwm_vector3_t* normal);
extern void hwm_vector3_project_on_line(hwm_vector3_t* out, const hwm_vector3_t* v, const hwm_vector3_t* point, const hwm_vector3_t* direction);

extern hwbool hwm_vector3_is_unit(const hwm_vector3_t* v, hwf32 epsilon);
extern hwbool hwm_vector3_is_zero(const hwm_vector3_t* v);
extern hwbool hwm_vector3_is_one(const hwm_vector3_t* v);
extern hwbool hwm_vector3_is_nan(const hwm_vector3_t* v);

#ifdef __cplusplus
}
#endif

#endif

