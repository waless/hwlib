#ifndef HWM_MATRIX44_H_
#define HWM_MATRIX44_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

struct hwm_vector2_t;
struct hwm_vector3_t;
struct hwm_vector4_t;

typedef struct hwm_matrix44_t {
    hwf32 elements[4][4];
} hwm_matrix44_t;

/* constant value */
extern const hwm_matrix44_t k_hwm_matrix44_zero;
extern const hwm_matrix44_t k_hwm_matrix44_identity;

/* set function */
extern void hwm_matrix44_identity(hwm_matrix44_t* out);
extern void hwm_matrix44_set_scale(hwm_matrix44_t* out, hwf32 x, hwf32 y, hwf32 z);
extern void hwm_matrix44_set_rotate_x(hwm_matrix44_t* out, hwf32 rad);
extern void hwm_matrix44_set_rotate_y(hwm_matrix44_t* out, hwf32 rad);
extern void hwm_matrix44_set_rotate_z(hwm_matrix44_t* out, hwf32 rad);
extern void hwm_matrix44_set_rotate_axis(hwm_matrix44_t* out, hwf32 axis_x, hwf32 axis_y, hwf32 axis_z, hwf32 rad);
extern void hwm_matrix44_set_translate(hwm_matrix44_t* out, hwf32 x, hwf32 y, hwf32 z);
extern void hwm_matrix44_set_lookat(hwm_matrix44_t* out, hwf32 eye_x, hwf32 eye_y, hwf32 eye_z, hwf32 center_x, hwf32 center_y, hwf32 center_z, hwf32 up_x, hwf32 up_y, hwf32 up_z);
extern void hwm_matrix44_set_frustum(hwm_matrix44_t* out, hwf32 left, hwf32 right, hwf32 top ,hwf32 bottom, hwf32 near, hwf32 far);
extern void hwm_matrix44_set_perspective(hwm_matrix44_t* out, hwf32 fov, hwf32 aspect, hwf32 near, hwf32 far);
extern void hwm_matrix44_set_ortho(hwm_matrix44_t* out, hwf32 left, hwf32 right, hwf32 top, hwf32 bottom, hwf32 near, hwf32 far);
extern void hwm_matrix44_set_screen(hwm_matrix44_t* out, hwf32 width, hwf32 height);

/* get function */
extern void hwm_matrix44_get_axis_x(struct hwm_vector3_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_get_axis_y(struct hwm_vector3_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_get_axis_z(struct hwm_vector3_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_get_axis_w(struct hwm_vector3_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_get_column_x(struct hwm_vector4_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_get_column_y(struct hwm_vector4_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_get_column_z(struct hwm_vector4_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_get_column_w(struct hwm_vector4_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_get_row_x(struct hwm_vector4_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_get_row_y(struct hwm_vector4_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_get_row_z(struct hwm_vector4_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_get_row_w(struct hwm_vector4_t* out, const hwm_matrix44_t* m);

/* calculate function */
extern void hwm_matrix44_add(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs);
extern void hwm_matrix44_add_scaler(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, hwf32 scaler);
extern void hwm_matrix44_sub(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs);
extern void hwm_matrix44_sub_scaler(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, hwf32 scaler);
extern void hwm_matrix44_mul(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs);
extern void hwm_matrix44_mul_scaler(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, hwf32 scaler);
extern void hwm_matrix44_div(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs);
extern void hwm_matrix44_div_scaler(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, hwf32 scaler);
extern void hwm_matrix44_multiply(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs);
extern void hwm_matrix44_multiply_affine(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs);
extern hwf32 hwm_matrix44_determinant(const hwm_matrix44_t* m);
extern void hwm_matrix44_transpose(hwm_matrix44_t* out, const hwm_matrix44_t* im);
extern void hwm_matrix44_inverse(hwm_matrix44_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_inverse_affine(hwm_matrix44_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_inverse_orthonormal(hwm_matrix44_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_orthonormalize(hwm_matrix44_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_negate(hwm_matrix44_t* out, const hwm_matrix44_t* m);
extern void hwm_matrix44_transform_vector2(struct hwm_vector2_t* out, const hwm_matrix44_t* m, const struct hwm_vector2_t* v);
extern void hwm_matrix44_transform_vector3(struct hwm_vector3_t* out, const hwm_matrix44_t* m, const struct hwm_vector3_t* v);
extern void hwm_matrix44_transform_vector4(struct hwm_vector4_t* out, const hwm_matrix44_t* m, const struct hwm_vector4_t* v);
extern void hwm_matrix44_transform_point2(struct hwm_vector2_t* out, const hwm_matrix44_t* m, const struct hwm_vector2_t* v);
extern void hwm_matrix44_transform_point3(struct hwm_vector3_t* out, const hwm_matrix44_t* m, const struct hwm_vector3_t* v);
extern void hwm_matrix44_transform_point4(struct hwm_vector4_t* out, const hwm_matrix44_t* m, const struct hwm_vector4_t* v);
extern void hwm_matrix44_transform_projection2(struct hwm_vector2_t* out, const hwm_matrix44_t* m, const struct hwm_vector2_t* v);
extern void hwm_matrix44_transform_projection3(struct hwm_vector3_t* out, const hwm_matrix44_t* m, const struct hwm_vector3_t* v);
extern void hwm_matrix44_transform_projection4(struct hwm_vector4_t* out, const hwm_matrix44_t* m, const struct hwm_vector4_t* v);
extern void hwm_matrix44_scale(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 x, hwf32 y, hwf32 z);
extern void hwm_matrix44_rotate_x(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 rad);
extern void hwm_matrix44_rotate_y(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 rad);
extern void hwm_matrix44_rotate_z(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 rad);
extern void hwm_matrix44_rotate_axis(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 axis_x, hwf32 axis_y, hwf32 axis_z, hwf32 rad);
extern void hwm_matrix44_translate(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 x, hwf32 y, hwf32 z);

/* check function */
extern hwbool hwm_matrix44_is_orthonormal(const hwm_matrix44_t* m, hwf32 epsilon);
extern hwbool hwm_matrix44_is_identity(const hwm_matrix44_t* m);

#ifdef __cplusplus
}
#endif

#endif

