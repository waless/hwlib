#include "hwm/matrix44.h"
#include <string.h>
#include "hwm/vector2.h"
#include "hwm/vector3.h"
#include "hwm/vector4.h"
#include "hwm/math.h"

const hwm_matrix44_t HWM_MATRIX44_ZERO =
{
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
};

const hwm_matrix44_t HWM_MATRIX44_IDENTITY =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f,
};

void hwm_matrix44_identity(hwm_matrix44_t* m)
{
    *m = HWM_MATRIX44_IDENTITY;
}

void hwm_matrix44_set_scale(hwm_matrix44_t* m, hwf32 x, hwf32 y, hwf32 z)
{
    m->elements[0][0] = x;
    m->elements[1][1] = y;
    m->elements[2][2] = z;
}

void hwm_matrix44_set_rotate_x(hwm_matrix44_t* out, hwf32 rad)
{
    hwf32 sin = hwm_sinf(rad);
    hwf32 cos = hwm_cosf(rad);

    out->elements[0][0] = 1.0f; out->elements[1][0] = 0.0f; out->elements[2][0] = 0.0f; out->elements[3][0] = 0.0f;
    out->elements[0][1] = 0.0f; out->elements[1][1] = cos;  out->elements[2][1] = -sin; out->elements[3][1] = 0.0f;
    out->elements[0][2] = 0.0f; out->elements[1][2] = sin;  out->elements[2][2] = cos;  out->elements[3][2] = 0.0f;
    out->elements[0][3] = 0.0f; out->elements[1][3] = 0.0f; out->elements[2][3] = 0.0f; out->elements[3][3] = 1.0f;
}

void hwm_matrix44_set_rotate_y(hwm_matrix44_t* out, hwf32 rad)
{
    hwf32 sin = hwm_sinf(rad);
    hwf32 cos = hwm_cosf(rad);

    out->elements[0][0] = cos;  out->elements[1][0] = 0.0f; out->elements[2][0] = sin;  out->elements[3][0] = 0.0f;
    out->elements[0][1] = 0.0f; out->elements[1][1] = 1.0f; out->elements[2][1] = 0.0f; out->elements[3][1] = 0.0f;
    out->elements[0][2] = -sin; out->elements[1][2] = 0.0f; out->elements[2][2] = cos;  out->elements[3][2] = 0.0f;
    out->elements[0][3] = 0.0f; out->elements[1][3] = 0.0f; out->elements[2][3] = 0.0f; out->elements[3][3] = 1.0f;
}

void hwm_matrix44_set_rotate_z(hwm_matrix44_t* out, hwf32 rad)
{
    hwf32 sin = hwm_sinf(rad);
    hwf32 cos = hwm_cosf(rad);

    out->elements[0][0] = cos;  out->elements[1][0] = -sin; out->elements[2][0] = 0.0f; out->elements[3][0] = 0.0f;
    out->elements[0][1] = sin;  out->elements[1][1] = cos;  out->elements[2][1] = 0.0f; out->elements[3][1] = 0.0f;
    out->elements[0][2] = 0.0f; out->elements[1][2] = 0.0f; out->elements[2][2] = 1.0f; out->elements[3][2] = 0.0f;
    out->elements[0][3] = 0.0f; out->elements[1][3] = 0.0f; out->elements[2][3] = 0.0f; out->elements[3][3] = 1.0f;
}

void hwm_matrix44_set_rotate_axis(hwm_matrix44_t* out, hwf32 axis_x, hwf32 axis_y, hwf32 axis_z, hwf32 rad)
{
    hwf32 sin = hwm_sinf(rad);
    hwf32 cos = hwm_cosf(rad);
    hwm_vector3_t axis;

    axis.x = axis_x;
    axis.y = axis_y;
    axis.z = axis_z;
    hwm_vector3_normalize(&axis, &axis);

    out->elements[0][0] = cos + (1.0f - cos) * axis.x * axis.x;
    out->elements[0][1] = (1.0f - cos) * axis.x * axis.y + sin * axis.z;
    out->elements[0][2] = (1.0f - cos) * axis.x * axis.z - sin * axis.y;
    out->elements[0][3] = 0.0f;

    out->elements[1][0] = (1.0f - cos) * axis.y * axis.x - sin * axis.z;
    out->elements[1][1] = cos + (1.0f - cos) * axis.y * axis.y;
    out->elements[1][2] = (1.0f - cos) * axis.y * axis.z + sin * axis.x;
    out->elements[1][3] = 0.0f;

    out->elements[2][0] = (1.0f - cos) * axis.z * axis.x + sin * axis.y;
    out->elements[2][1] = (1.0f - cos) * axis.z * axis.y - sin * axis.x;
    out->elements[2][2] = cos + (1.0f - cos) * axis.z * axis.z;
    out->elements[2][3] = 0.0f;

    out->elements[3][0] = 0.0f;
    out->elements[3][1] = 0.0f;
    out->elements[3][2] = 0.0f;
    out->elements[3][3] = 1.0f;
}

void hwm_matrix44_set_translate(hwm_matrix44_t* out, hwf32 x, hwf32 y, hwf32 z)
{
    out->elements[0][0] = 1.0f; out->elements[1][0] = 0.0f; out->elements[2][0] = 0.0f; out->elements[3][0] = x;
    out->elements[0][1] = 0.0f; out->elements[1][1] = 1.0f; out->elements[2][1] = 0.0f; out->elements[3][1] = y;
    out->elements[0][2] = 0.0f; out->elements[1][2] = 0.0f; out->elements[2][2] = 1.0f; out->elements[3][2] = z;
    out->elements[0][3] = 0.0f; out->elements[1][3] = 0.0f; out->elements[2][3] = 0.0f; out->elements[3][3] = 1.0f;
}

void hwm_matrix44_set_lookat(hwm_matrix44_t* out, hwf32 eye_x, hwf32 eye_y, hwf32 eye_z, hwf32 center_x, hwf32 center_y, hwf32 center_z, hwf32 up_x, hwf32 up_y, hwf32 up_z)
{
    hwm_vector3_t e;
    hwm_vector3_t c;
    hwm_vector3_t u;
    hwm_vector3_t f;
    hwm_vector3_t s;

    e.x = eye_x;
    e.y = eye_y;
    e.z = eye_z;
    c.x = center_x;
    c.y = center_y;
    c.z = center_z;
    u.x = up_x;
    u.y = up_y;
    u.z = up_z;

    hwm_vector3_sub(&f, &e, &c);
    hwm_vector3_normalize(&f, &f);
    hwm_vector3_normalize(&u, &u);

    hwm_vector3_cross(&s, &u, &f);
    hwm_vector3_normalize(&s, &s);

    hwm_vector3_cross(&u, &f, &s);

    out->elements[0][0] = s.x;  out->elements[1][0] = s.y;  out->elements[2][0] = s.z;  out->elements[3][0] = -hwm_vector3_dot(&s, &e);
    out->elements[0][1] = u.x;  out->elements[1][1] = u.y;  out->elements[2][1] = u.z;  out->elements[3][1] = -hwm_vector3_dot(&u, &e);
    out->elements[0][2] = f.x;  out->elements[1][2] = f.y;  out->elements[2][2] = f.z;  out->elements[3][2] = -hwm_vector3_dot(&f, &e);
    out->elements[0][3] = 0.0f; out->elements[1][3] = 0.0f; out->elements[2][3] = 0.0f; out->elements[3][3] = 1.0f;
}

void hwm_matrix44_set_frustum(hwm_matrix44_t* out, hwf32 left, hwf32 right, hwf32 top ,hwf32 bottom, hwf32 near, hwf32 far)
{
    hwf32 width  = right - left;
    hwf32 height = top - bottom;
    hwf32 depth  = far - near;
    hwf32 near2  = near * 2.0f;

    out->elements[0][0] = near2 / width;
    out->elements[1][0] = 0.0f;
    out->elements[2][0] = (right + left) / width;
    out->elements[3][0] = 0.0f;

    out->elements[0][1] = 0.0f;
    out->elements[1][1] = near2 / height;
    out->elements[2][1] = (top + bottom) / height;
    out->elements[3][1] = 0.0f;

    out->elements[0][2] = 0.0f;
    out->elements[1][2] = 0.0f;
    out->elements[2][2] = -(far + near) / depth;
    out->elements[3][2] = -(far * near2) / depth;

    out->elements[0][3] = 0.0f;
    out->elements[1][3] = 0.0f;
    out->elements[2][3] = -1.0f;
    out->elements[3][3] = 0.0f;
}

void hwm_matrix44_set_perspective(hwm_matrix44_t* out, hwf32 fov, hwf32 aspect, hwf32 near, hwf32 far)
{
    hwf32 fovf  = hwm_cotf(HWM_TO_RAD(fov * 0.5f));
    hwf32 depth = near - far;

    out->elements[0][0] = fovf / aspect;
    out->elements[1][0] = 0.0f;
    out->elements[2][0] = 0.0f;
    out->elements[3][0] = 0.0f;

    out->elements[0][1] = 0.0f;
    out->elements[1][1] = fovf;
    out->elements[2][1] = 0.0f;
    out->elements[3][1] = 0.0f;

    out->elements[0][2] = 0.0f;
    out->elements[1][2] = 0.0f;
    out->elements[2][2] = (far + near) / depth;
    out->elements[3][2] = (far * near * 2.0f) / depth;

    out->elements[0][3] = 0.0f;
    out->elements[1][3] = 0.0f;
    out->elements[2][3] = -1.0f;
    out->elements[3][3] = 0.0f;
}

void hwm_matrix44_set_ortho(hwm_matrix44_t* out, hwf32 left, hwf32 right, hwf32 top, hwf32 bottom, hwf32 near, hwf32 far)
{
    hwf32 width  = right - left;
    hwf32 height = top - bottom;
    hwf32 depth  = far - near;

    out->elements[0][0] = 2.0f / width;
    out->elements[1][0] = 0.0f;
    out->elements[2][0] = 0.0f;
    out->elements[3][0] = 0.0f;

    out->elements[0][1] = 0.0f;
    out->elements[1][1] = 2.0f / height;
    out->elements[2][1] = 0.0f;
    out->elements[3][1] = 0.0f;

    out->elements[0][2] = 0.0f;
    out->elements[1][2] = 0.0f;
    out->elements[2][2] = -2.0f / depth;
    out->elements[3][2] = 0.0f;

    out->elements[0][3] = -((right + left) / width);
    out->elements[1][3] = -((top + bottom) / height);
    out->elements[2][3] = -((far + near) / depth);
    out->elements[3][3] = 1.0f;
}

void hwm_matrix44_set_screen(hwm_matrix44_t* out, hwf32 width, hwf32 height)
{
    out->elements[0][0] = width; out->elements[1][0] = 0.0f;    out->elements[2][0] = 0.0f; out->elements[3][0] = width;
    out->elements[0][1] = 0.0f;  out->elements[1][1] = -height; out->elements[2][1] = 0.0f; out->elements[3][1] = height;
    out->elements[0][2] = 0.0f;  out->elements[1][2] = 0.0f;    out->elements[2][2] = 1.0f; out->elements[3][2] = 0.0f;
    out->elements[0][3] = 0.0f;  out->elements[1][3] = 0.0f;    out->elements[2][3] = 0.0f; out->elements[3][3] = 1.0f;
}


void hwm_matrix44_get_axis_x(struct hwm_vector3_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[0][0];
    out->y = m->elements[0][1];
    out->z = m->elements[0][2];
}

void hwm_matrix44_get_axis_y(struct hwm_vector3_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[1][0];
    out->y = m->elements[1][1];
    out->z = m->elements[1][2];
}

void hwm_matrix44_get_axis_z(struct hwm_vector3_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[2][0];
    out->y = m->elements[2][1];
    out->z = m->elements[2][2];
}

void hwm_matrix44_get_axis_w(struct hwm_vector3_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[3][0];
    out->y = m->elements[3][1];
    out->z = m->elements[3][2];
}

void hwm_matrix44_get_column_x(struct hwm_vector4_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[0][0];
    out->y = m->elements[0][1];
    out->z = m->elements[0][2];
    out->w = m->elements[0][3];
}

void hwm_matrix44_get_column_y(struct hwm_vector4_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[1][0];
    out->y = m->elements[1][1];
    out->z = m->elements[1][2];
    out->w = m->elements[1][3];
}

void hwm_matrix44_get_column_z(struct hwm_vector4_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[2][0];
    out->y = m->elements[2][1];
    out->z = m->elements[2][2];
    out->w = m->elements[2][3];
}

void hwm_matrix44_get_column_w(struct hwm_vector4_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[3][0];
    out->y = m->elements[3][1];
    out->z = m->elements[3][2];
    out->w = m->elements[3][3];
}

void hwm_matrix44_get_row_x(struct hwm_vector4_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[0][0];
    out->y = m->elements[1][0];
    out->z = m->elements[2][0];
    out->w = m->elements[3][0];
}

void hwm_matrix44_get_row_y(struct hwm_vector4_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[0][1];
    out->y = m->elements[1][1];
    out->z = m->elements[2][1];
    out->w = m->elements[3][1];
}

void hwm_matrix44_get_row_z(struct hwm_vector4_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[0][2];
    out->y = m->elements[1][2];
    out->z = m->elements[2][2];
    out->w = m->elements[3][2];
}

void hwm_matrix44_get_row_w(struct hwm_vector4_t* out, const hwm_matrix44_t* m)
{
    out->x = m->elements[0][3];
    out->y = m->elements[1][3];
    out->z = m->elements[2][3];
    out->w = m->elements[3][3];
}

void hwm_matrix44_add(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs)
{
    int i;
    int j;

    for(i = 0; i < 4; ++i) {
        for(j = 0; j < 4; ++j) {
            out->elements[i][j] = lhs->elements[i][j] + rhs->elements[i][j];
        }
    }
}

void hwm_matrix44_add_scaler(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, hwf32 scaler)
{
    int i;
    int j;

    for(i = 0; i < 4; ++i) {
        for(j = 0; j < 4; ++j) {
            out->elements[i][j] = lhs->elements[i][j] + scaler;
        }
    }
}

void hwm_matrix44_sub(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs)
{
    int i;
    int j;

    for(i = 0; i < 4; ++i) {
        for(j = 0; j < 4; ++j) {
            out->elements[i][j] = lhs->elements[i][j] - rhs->elements[i][j];
        }
    }
}

void hwm_matrix44_sub_scaler(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, hwf32 scaler)
{
    int i;
    int j;

    for(i = 0; i < 4; ++i) {
        for(j = 0; j < 4; ++j) {
            out->elements[i][j] = lhs->elements[i][j] - scaler;
        }
    }
}

void hwm_matrix44_mul(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs)
{
    int i;
    int j;

    for(i = 0; i < 4; ++i) {
        for(j = 0; j < 4; ++j) {
            out->elements[i][j] = lhs->elements[i][j] * rhs->elements[i][j];
        }
    }
}

void hwm_matrix44_mul_scaler(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, hwf32 scaler)
{
    int i;
    int j;

    for(i = 0; i < 4; ++i) {
        for(j = 0; j < 4; ++j) {
            out->elements[i][j] = lhs->elements[i][j] * scaler;
        }
    }
}

void hwm_matrix44_div(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs)
{
    int i;
    int j;

    for(i = 0; i < 4; ++i) {
        for(j = 0; j < 4; ++j) {
            out->elements[i][j] = lhs->elements[i][j] / rhs->elements[i][j];
        }
    }
}

void hwm_matrix44_div_scaler(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, hwf32 scaler)
{
    int i;
    int j;

    for(i = 0; i < 4; ++i) {
        for(j = 0; j < 4; ++j) {
            out->elements[i][j] = lhs->elements[i][j] / scaler;
        }
    }
}

void hwm_matrix44_multiply(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs)
{
    hwm_matrix44_t tmp;
    int i;

    for(i = 0; i < 4; ++i) {
        tmp.elements[i][0] = lhs->elements[i][0] * rhs->elements[0][0] +
                             lhs->elements[i][1] * rhs->elements[1][0] +
                             lhs->elements[i][2] * rhs->elements[2][0] +
                             lhs->elements[i][3] * rhs->elements[3][0];

        tmp.elements[i][1] = lhs->elements[i][0] * rhs->elements[0][1] +
                             lhs->elements[i][1] * rhs->elements[1][1] +
                             lhs->elements[i][2] * rhs->elements[2][1] +
                             lhs->elements[i][3] * rhs->elements[3][1];

        tmp.elements[i][2] = lhs->elements[i][0] * rhs->elements[0][2] +
                             lhs->elements[i][1] * rhs->elements[1][2] +
                             lhs->elements[i][2] * rhs->elements[2][2] +
                             lhs->elements[i][3] * rhs->elements[3][2];

        tmp.elements[i][3] = lhs->elements[i][0] * rhs->elements[0][3] +
                             lhs->elements[i][1] * rhs->elements[1][3] +
                             lhs->elements[i][2] * rhs->elements[2][3] +
                             lhs->elements[i][3] * rhs->elements[3][3];
    }

    *out = tmp;
}

void hwm_matrix44_multiply_affine(hwm_matrix44_t* out, const hwm_matrix44_t* lhs, const hwm_matrix44_t* rhs)
{
    hwm_matrix44_t tmp;
    int i = 0;

    for(i = 0; i < 4; ++i) {
        tmp.elements[i][0] = lhs->elements[i][0] * rhs->elements[0][0] +
                             lhs->elements[i][1] * rhs->elements[1][0] +
                             lhs->elements[i][2] * rhs->elements[2][0] +
                             lhs->elements[i][3] * rhs->elements[3][0];

        tmp.elements[i][1] = lhs->elements[i][0] * rhs->elements[0][1] +
                             lhs->elements[i][1] * rhs->elements[1][1] +
                             lhs->elements[i][2] * rhs->elements[2][1] +
                             lhs->elements[i][3] * rhs->elements[3][1];

        tmp.elements[i][2] = lhs->elements[i][0] * rhs->elements[0][2] +
                             lhs->elements[i][1] * rhs->elements[1][2] +
                             lhs->elements[i][2] * rhs->elements[2][2] +
                             lhs->elements[i][3] * rhs->elements[3][2];
    }

    tmp.elements[0][3] = 0.0f;
    tmp.elements[1][3] = 0.0f;
    tmp.elements[2][3] = 0.0f;
    tmp.elements[3][3] = 1.0f;

    *out = tmp;
}

hwf32 hwm_matrix44_determinant(const hwm_matrix44_t* m)
{
    hwf32 sub_factor00 = m->elements[2][2] * m->elements[3][3] - m->elements[3][2] * m->elements[2][3];
    hwf32 sub_factor01 = m->elements[2][1] * m->elements[3][3] - m->elements[3][1] * m->elements[2][3];
    hwf32 sub_factor02 = m->elements[2][1] * m->elements[3][2] - m->elements[3][1] * m->elements[2][2];
    hwf32 sub_factor03 = m->elements[2][0] * m->elements[3][3] - m->elements[3][0] * m->elements[2][3];
    hwf32 sub_factor04 = m->elements[2][0] * m->elements[3][2] - m->elements[3][0] * m->elements[2][2];
    hwf32 sub_factor05 = m->elements[2][0] * m->elements[3][1] - m->elements[3][0] * m->elements[2][1];
    
    hwm_vector4_t det_cof;
    det_cof.x =  (m->elements[1][1] * sub_factor00 - m->elements[1][2] * sub_factor01 + m->elements[1][3] * sub_factor02);
    det_cof.y = -(m->elements[1][0] * sub_factor00 - m->elements[1][2] * sub_factor03 + m->elements[1][3] * sub_factor04);
    det_cof.z =  (m->elements[1][0] * sub_factor01 - m->elements[1][1] * sub_factor03 + m->elements[1][3] * sub_factor05);
    det_cof.w = -(m->elements[1][0] * sub_factor02 - m->elements[1][1] * sub_factor04 + m->elements[1][2] * sub_factor05);

    return m->elements[0][0] * det_cof.x + 
           m->elements[0][1] * det_cof.y + 
           m->elements[0][2] * det_cof.z + 
           m->elements[0][3] * det_cof.w;
}

void hwm_matrix44_transpose(hwm_matrix44_t* out, const hwm_matrix44_t* m)
{
    out->elements[0][0] = m->elements[0][0]; out->elements[0][1] = m->elements[1][0]; out->elements[0][2] = m->elements[2][0]; out->elements[0][3] = m->elements[3][0];
    out->elements[1][0] = m->elements[0][1]; out->elements[1][1] = m->elements[1][1]; out->elements[1][2] = m->elements[2][1]; out->elements[1][3] = m->elements[3][1];
    out->elements[2][0] = m->elements[0][2]; out->elements[2][1] = m->elements[1][2]; out->elements[2][2] = m->elements[2][2]; out->elements[2][3] = m->elements[3][2];
    out->elements[3][0] = m->elements[0][3]; out->elements[3][1] = m->elements[1][3]; out->elements[3][2] = m->elements[2][3]; out->elements[3][3] = m->elements[3][3];
}

void hwm_matrix44_inverse(hwm_matrix44_t* out, const hwm_matrix44_t* m)
{
    if(m->elements[3][0] == 0.0f && m->elements[3][1] == 0.0f && m->elements[3][2] == 0.0f && m->elements[3][3] == 1.0f) {
        hwm_matrix44_inverse_affine(out, m);
    }
    else {
        hwf32 value1  = m->elements[0][0] * m->elements[1][1] - m->elements[0][1] * m->elements[1][0];
        hwf32 value2  = m->elements[0][0] * m->elements[1][2] - m->elements[0][2] * m->elements[1][0];
        hwf32 value3  = m->elements[0][0] * m->elements[1][3] - m->elements[0][3] * m->elements[1][0];
        hwf32 value4  = m->elements[1][0] * m->elements[1][2] - m->elements[0][2] * m->elements[1][1];
        hwf32 value5  = m->elements[1][0] * m->elements[1][3] - m->elements[0][3] * m->elements[1][1];
        hwf32 value6  = m->elements[2][0] * m->elements[1][3] - m->elements[0][3] * m->elements[1][2];
        hwf32 value7  = m->elements[0][2] * m->elements[3][1] - m->elements[2][1] * m->elements[3][0];
        hwf32 value8  = m->elements[0][2] * m->elements[3][2] - m->elements[2][2] * m->elements[3][0];
        hwf32 value9  = m->elements[0][2] * m->elements[3][3] - m->elements[2][3] * m->elements[3][0];
        hwf32 value10 = m->elements[1][2] * m->elements[3][2] - m->elements[2][2] * m->elements[3][1];
        hwf32 value11 = m->elements[1][2] * m->elements[3][3] - m->elements[2][3] * m->elements[3][1];
        hwf32 value12 = m->elements[2][2] * m->elements[3][3] - m->elements[2][3] * m->elements[3][2];
        hwf32 value13 = 1.0f / (value1 * value12 - value2 * value11 + value3 * value10 + value4 * value9 - value5 * value8 + value6 * value7);

        out->elements[0][0] = ( m->elements[1][1] * value12 - m->elements[1][2] * value11 + m->elements[1][3] * value10) * value13;
        out->elements[0][1] = (-m->elements[0][1] * value12 + m->elements[0][2] * value11 - m->elements[0][3] * value10) * value13;
        out->elements[0][2] = ( m->elements[3][1] * value6  - m->elements[3][2] * value5  + m->elements[3][3] * value4)  * value13;
        out->elements[0][3] = (-m->elements[2][1] * value6  + m->elements[2][2] * value5  - m->elements[2][3] * value4)  * value13;
        out->elements[1][0] = (-m->elements[1][0] * value12 + m->elements[1][2] * value9  - m->elements[1][3] * value8)  * value13;
        out->elements[1][1] = ( m->elements[0][0] * value12 - m->elements[0][2] * value9  + m->elements[0][3] * value8)  * value13;
        out->elements[1][2] = (-m->elements[3][0] * value6  + m->elements[3][2] * value3  - m->elements[3][3] * value2)  * value13;
        out->elements[1][3] = ( m->elements[2][0] * value6  - m->elements[2][2] * value3  + m->elements[2][3] * value2)  * value13;
        out->elements[2][0] = ( m->elements[1][0] * value11 - m->elements[1][1] * value9  + m->elements[1][3] * value7)  * value13;
        out->elements[2][1] = (-m->elements[0][0] * value11 + m->elements[0][1] * value9  - m->elements[0][3] * value7)  * value13;
        out->elements[2][2] = ( m->elements[3][0] * value5  - m->elements[3][1] * value3  + m->elements[3][3] * value1)  * value13;
        out->elements[2][3] = (-m->elements[2][0] * value5  + m->elements[2][1] * value3  - m->elements[2][3] * value1)  * value13;
        out->elements[3][0] = (-m->elements[1][0] * value10 + m->elements[1][1] * value8  - m->elements[1][2] * value7)  * value13;
        out->elements[3][1] = ( m->elements[0][0] * value10 - m->elements[0][1] * value8  + m->elements[0][2] * value7)  * value13;
        out->elements[3][2] = (-m->elements[3][0] * value4  + m->elements[3][1] * value2  - m->elements[3][2] * value1)  * value13;
        out->elements[3][3] = ( m->elements[2][0] * value4  - m->elements[2][1] * value2  + m->elements[2][2] * value1)  * value13;
    }
}

void hwm_matrix44_inverse_affine(hwm_matrix44_t* out, const hwm_matrix44_t* m)
{
    hwf32 value1 = m->elements[1][1] * m->elements[2][2] - m->elements[1][2] * m->elements[2][1];
    hwf32 value2 = m->elements[0][2] * m->elements[2][1] - m->elements[0][1] * m->elements[2][2];
    hwf32 value3 = m->elements[0][1] * m->elements[1][2] - m->elements[0][2] * m->elements[1][1];
    hwf32 value4 = 1.0f / (m->elements[0][0] * value1 + m->elements[1][0] * value2 + m->elements[2][0] * value3);

    out->elements[0][0] = value1 * value4;
    out->elements[0][1] = value2 * value4;
    out->elements[0][2] = value3 * value4;
    out->elements[0][3] = 0.0f;
    out->elements[1][0] = (m->elements[1][2] * m->elements[2][0] - m->elements[1][0] * m->elements[2][2]) * value4;
    out->elements[1][1] = (m->elements[0][0] * m->elements[2][2] - m->elements[0][2] * m->elements[2][0]) * value4;
    out->elements[1][2] = (m->elements[0][2] * m->elements[1][0] - m->elements[0][0] * m->elements[1][2]) * value4;
    out->elements[1][3] = 0.0f;
    out->elements[2][0] = (m->elements[1][0] * m->elements[2][1] - m->elements[1][1] * m->elements[2][0]) * value4;
    out->elements[2][1] = (m->elements[0][1] * m->elements[2][0] - m->elements[0][0] * m->elements[2][1]) * value4;
    out->elements[2][2] = (m->elements[0][0] * m->elements[1][1] - m->elements[0][1] * m->elements[1][0]) * value4;
    out->elements[2][3] = 0.0f;
    out->elements[3][0] = -(out->elements[0][0] * m->elements[3][0] + out->elements[1][0] * m->elements[3][1] + out->elements[2][0] * m->elements[3][2]);
    out->elements[3][1] = -(out->elements[0][1] * m->elements[3][0] + out->elements[1][1] * m->elements[3][1] + out->elements[2][1] * m->elements[3][2]);
    out->elements[3][2] = -(out->elements[0][2] * m->elements[3][0] + out->elements[1][2] * m->elements[3][1] + out->elements[2][2] * m->elements[3][2]);
    out->elements[3][3] = 1.0f;
}

void hwm_matrix44_inverse_orthonormal(hwm_matrix44_t* out, const hwm_matrix44_t* m)
{
    out->elements[0][0] = m->elements[0][0];
    out->elements[1][0] = m->elements[0][1];
    out->elements[2][0] = m->elements[0][2];
    out->elements[3][0] = 0.0f;
    out->elements[0][1] = m->elements[1][0];
    out->elements[1][1] = m->elements[1][1];
    out->elements[2][1] = m->elements[1][2];
    out->elements[3][1] = 0.0f;
    out->elements[0][2] = m->elements[2][0];
    out->elements[1][2] = m->elements[2][1];
    out->elements[2][2] = m->elements[2][1];
    out->elements[3][2] = 0.0f;
    out->elements[0][3] = -(m->elements[0][0] * m->elements[0][3] + m->elements[1][0] * m->elements[1][3] + m->elements[2][0] * m->elements[2][3]);
    out->elements[1][3] = -(m->elements[0][1] * m->elements[0][3] + m->elements[1][1] * m->elements[1][3] + m->elements[2][1] * m->elements[2][3]);
    out->elements[2][3] = -(m->elements[0][2] * m->elements[0][3] + m->elements[1][2] * m->elements[1][3] + m->elements[2][2] * m->elements[2][3]);
    out->elements[3][3] = 1.0f;
}

void hwm_matrix44_orthonormalize(hwm_matrix44_t* out, const hwm_matrix44_t* m)
{
    hwm_vector3_t v1;
    hwm_vector3_t v2;
    hwm_vector3_t v3;
    hwm_vector3_t v4;

    hwm_matrix44_get_axis_z(&v1, m);
    hwm_vector3_normalize(&v2, &v1);

    hwm_matrix44_get_axis_y(&v1, m);
    hwm_vector3_cross(&v3, &v1, &v2);
    hwm_vector3_normalize(&v3, &v3);
    hwm_vector3_cross(&v4, &v2, &v3);

    out->elements[0][0] = v3.x;       out->elements[1][0] = v3.y;       out->elements[2][0] = v3.z;       out->elements[3][0] = 0.0f;
    out->elements[0][1] = v4.x;       out->elements[1][1] = v4.y;       out->elements[2][1] = v4.z;       out->elements[3][1] = 0.0f;
    out->elements[0][2] = v2.x;       out->elements[1][2] = v2.y;       out->elements[2][2] = v2.z;       out->elements[3][2] = 0.0f;
    out->elements[0][3] = m->elements[0][3]; out->elements[1][3] = m->elements[1][3]; out->elements[2][3] = m->elements[3][2]; out->elements[3][3] = 1.0f;
}

void hwm_matrix44_negate(hwm_matrix44_t* out, const hwm_matrix44_t* m)
{
    hwm_matrix44_mul_scaler(out, m, -1.0f);
}

void hwm_matrix44_transform_vector2(struct hwm_vector2_t* out, const hwm_matrix44_t* m, const struct hwm_vector2_t* v)
{
    out->x = m->elements[0][0] * v->x + m->elements[0][1] * v->y;
    out->y = m->elements[1][0] * v->x + m->elements[1][1] * v->y;
}

void hwm_matrix44_transform_vector3(struct hwm_vector3_t* out, const hwm_matrix44_t* m, const struct hwm_vector3_t* v)
{
    out->x = m->elements[0][0] * v->x + m->elements[0][1] * v->y + m->elements[0][2] * v->z;
    out->y = m->elements[1][0] * v->x + m->elements[1][1] * v->y + m->elements[1][2] * v->z;
    out->z = m->elements[2][0] * v->x + m->elements[2][1] * v->y + m->elements[2][2] * v->z;
}

void hwm_matrix44_transform_vector4(struct hwm_vector4_t* out, const hwm_matrix44_t* m, const struct hwm_vector4_t* v)
{
    out->x = m->elements[0][0] * v->x + m->elements[0][1] * v->y + m->elements[0][2] * v->z + m->elements[0][3] * v->w;
    out->y = m->elements[1][0] * v->x + m->elements[1][1] * v->y + m->elements[1][2] * v->z + m->elements[1][3] * v->w;
    out->z = m->elements[2][0] * v->x + m->elements[2][1] * v->y + m->elements[2][2] * v->z + m->elements[2][3] * v->w;
    out->w = m->elements[3][0] * v->x + m->elements[3][1] * v->y + m->elements[3][2] * v->z + m->elements[3][3] * v->w;
}

void hwm_matrix44_transform_point2(struct hwm_vector2_t* out, const hwm_matrix44_t* m, const struct hwm_vector2_t* v)
{
    hwm_matrix44_transform_vector2(out, m, v);
    out->x += m->elements[0][3];
    out->y += m->elements[1][3];
}

void hwm_matrix44_transform_point3(struct hwm_vector3_t* out, const hwm_matrix44_t* m, const struct hwm_vector3_t* v)
{
    hwm_matrix44_transform_vector3(out, m, v);
    out->x += m->elements[0][3];
    out->y += m->elements[1][3];
    out->z += m->elements[2][3];
}

void hwm_matrix44_transform_point4(struct hwm_vector4_t* out, const hwm_matrix44_t* m, const struct hwm_vector4_t* v)
{
    hwm_matrix44_transform_vector4(out, m, v);
    out->x += m->elements[0][3];
    out->y += m->elements[1][3];
    out->z += m->elements[2][3];
}

void hwm_matrix44_transform_projection2(struct hwm_vector2_t* out, const hwm_matrix44_t* m, const struct hwm_vector2_t* v)
{
    hwf32 value = 1.0f / (m->elements[3][0] * v->x + m->elements[3][1] * v->y + m->elements[3][3]);
    
    out->x = (m->elements[0][0] * v->x + m->elements[0][1] * v->y + m->elements[0][3]) * value;
    out->y = (m->elements[1][0] * v->x + m->elements[1][1] * v->y + m->elements[1][3]) * value;
}

void hwm_matrix44_transform_projection3(struct hwm_vector3_t* out, const hwm_matrix44_t* m, const struct hwm_vector3_t* v)
{
    hwf32 value = 1.0f / (m->elements[3][0] * v->x + m->elements[3][1] * v->y + m->elements[3][2] * v->z + m->elements[3][3]);
    
    out->x = (m->elements[0][0] * v->x + m->elements[0][1] * v->y + m->elements[0][2] * v->z + m->elements[0][3]) * value;
    out->y = (m->elements[1][0] * v->x + m->elements[1][1] * v->y + m->elements[1][2] * v->z + m->elements[1][3]) * value;
    out->z = (m->elements[2][0] * v->x + m->elements[2][1] * v->y + m->elements[2][2] * v->z + m->elements[2][3]) * value;
}

void hwm_matrix44_transform_projection4(struct hwm_vector4_t* out, const hwm_matrix44_t* m, const struct hwm_vector4_t* v)
{
    out->w = (m->elements[3][0] * v->x + m->elements[3][1] * v->y + m->elements[3][2] * v->z + m->elements[3][3] * v->w);
    out->x = (m->elements[0][0] * v->x + m->elements[0][1] * v->y + m->elements[0][2] * v->z + m->elements[0][3] * v->w) / out->w;
    out->y = (m->elements[1][0] * v->x + m->elements[1][1] * v->y + m->elements[1][2] * v->z + m->elements[1][3] * v->w) / out->w;
    out->z = (m->elements[2][0] * v->x + m->elements[2][1] * v->y + m->elements[2][2] * v->z + m->elements[2][3] * v->w) / out->w;
}

void hwm_matrix44_scale(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 x, hwf32 y, hwf32 z)
{
    out->elements[0][0] = m->elements[0][0] * x;
    out->elements[0][1] = m->elements[0][1] * x;
    out->elements[0][2] = m->elements[0][2] * x;
    out->elements[0][3] = m->elements[0][3] * x;

    out->elements[1][0] = m->elements[1][0] * y;
    out->elements[1][1] = m->elements[1][1] * y;
    out->elements[1][2] = m->elements[1][2] * y;
    out->elements[1][3] = m->elements[1][3] * y;

    out->elements[2][0] = m->elements[2][0] * z;
    out->elements[2][1] = m->elements[2][1] * z;
    out->elements[2][2] = m->elements[2][2] * z;
    out->elements[2][3] = m->elements[2][3] * z;

    out->elements[3][0] = m->elements[3][0];
    out->elements[3][1] = m->elements[3][1];
    out->elements[3][2] = m->elements[3][2];
    out->elements[3][3] = m->elements[3][3];
}

void hwm_matrix44_rotate_x(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 rad)
{
    hwm_matrix44_rotate_axis(out, m, 1.0f, 0.0f, 0.0f, rad);
}

void hwm_matrix44_rotate_y(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 rad)
{
    hwm_matrix44_rotate_axis(out, m, 0.0f, 1.0f, 0.0f, rad);
}

void hwm_matrix44_rotate_z(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 rad)
{
    hwm_matrix44_rotate_axis(out, m, 0.0f, 0.0f, 1.0f, rad);
}

void hwm_matrix44_rotate_axis(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 axis_x, hwf32 axis_y, hwf32 axis_z, hwf32 rad)
{
    hwm_matrix44_t rotation;

    hwm_matrix44_set_rotate_axis(&rotation, axis_x, axis_y, axis_z, rad);
    hwm_matrix44_multiply(out, &rotation, m);
}

void hwm_matrix44_translate(hwm_matrix44_t* out, const hwm_matrix44_t* m, hwf32 x, hwf32 y, hwf32 z)
{
    out->elements[3][0] = m->elements[0][0] * x + m->elements[1][0] * y + m->elements[2][0] * z + m->elements[3][0];
    out->elements[3][1] = m->elements[0][1] * x + m->elements[1][1] * y + m->elements[2][1] * z + m->elements[3][1];
    out->elements[3][2] = m->elements[0][2] * x + m->elements[1][2] * y + m->elements[2][2] * z + m->elements[3][2];
    out->elements[3][3] = m->elements[0][3] * x + m->elements[1][3] * y + m->elements[2][3] * z + m->elements[3][3];
}

hwbool hwm_matrix44_is_orthonormal(const hwm_matrix44_t* m, hwf32 epsilon)
{
    hwm_vector3_t v;
    hwm_vector3_t axis_x;
    hwm_vector3_t axis_y;
    hwm_vector3_t axis_z;
    hwm_vector4_t column_x;
    hwm_vector4_t column_y;
    hwm_vector4_t column_z;
    hwm_vector4_t column_w;

    hwm_matrix44_get_column_x(&column_x, m);
    hwm_matrix44_get_column_y(&column_y, m);
    hwm_matrix44_get_column_z(&column_z, m);
    hwm_matrix44_get_column_w(&column_w, m);

    if(hwm_vector4_is_nan(&column_x) == HW_FALSE) {
        return HW_FALSE;
    }

    if(hwm_vector4_is_nan(&column_y) == HW_FALSE) {
        return HW_FALSE;
    }

    if(hwm_vector4_is_nan(&column_z) == HW_FALSE) {
        return HW_FALSE;
    }

    if(hwm_vector4_is_nan(&column_w) == HW_FALSE) {
        return HW_FALSE;
    }

    hwm_matrix44_get_axis_x(&axis_x, m);
    hwm_matrix44_get_axis_y(&axis_y, m);
    hwm_matrix44_get_axis_z(&axis_z, m);
    hwm_vector3_cross(&v, &axis_x, &axis_y);
    if(hwm_vector3_dot(&v, &axis_z) <= 0.0f) {
        return HW_FALSE;
    }

    if(hwm_vector4_is_unit(&column_x, epsilon) == HW_FALSE) {
        return HW_FALSE;
    }

    if(hwm_vector4_is_unit(&column_y, epsilon) == HW_FALSE) {
        return HW_FALSE;
    }

    if(hwm_vector4_is_unit(&column_z, epsilon) == HW_FALSE) {
        return HW_FALSE;
    }

    if(hwm_absf(hwm_vector4_dot(&column_x, &column_y)) >= epsilon) {
        return HW_FALSE;
    }

    if(hwm_absf(hwm_vector4_dot(&column_y, &column_z)) >= epsilon) {
        return HW_FALSE;
    }

    if(hwm_absf(hwm_vector4_dot(&column_z, &column_x)) >= epsilon) {
        return HW_FALSE;
    }

    return HW_TRUE;
}

hwbool hwm_matrix44_is_identity(const hwm_matrix44_t* m)
{
    return memcmp(m, &HWM_MATRIX44_IDENTITY, sizeof(hwm_matrix44_t)) == 0 ? HW_TRUE : HW_FALSE;
}

