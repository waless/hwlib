#include "hwm/vector3.h"
#include <string.h>
#include "hwm/math.h"
#include "hwm/matrix44.h"
#include "hwm/vector2.h"

const hwm_vector3_t HWM_VECTOR3_ONE    = {1.0f, 1.0f, 1.0f};
const hwm_vector3_t HWM_VECTOR3_ZERO   = {0.0f, 0.0f, 0.0f};
const hwm_vector3_t HWM_VECTOR3_UNIT_X = {1.0f, 0.0f, 0.0f};
const hwm_vector3_t HWM_VECTOR3_UNIT_Y = {0.0f, 1.0f, 0.0f};
const hwm_vector3_t HWM_VECTOR3_UNIT_Z = {0.0f, 0.0f, 1.0f};

void hwm_vector3_set_zero(hwm_vector3_t* out)
{
    *out = HWM_VECTOR3_ZERO;
}

void hwm_vector3_set_one(hwm_vector3_t* out)
{
    *out = HWM_VECTOR3_ONE;
}

void hwm_vector3_set_unix_x(hwm_vector3_t* out)
{
    *out = HWM_VECTOR3_UNIT_X;
}

void hwm_vector3_set_unix_y(hwm_vector3_t* out)
{
    *out = HWM_VECTOR3_UNIT_Y;
}

void hwm_vector3_set_unix_z(hwm_vector3_t* out)
{
    *out = HWM_VECTOR3_UNIT_Z;
}

void hwm_vector3_set_scaler(hwm_vector3_t* out, hwf32 scaler)
{
    out->x = scaler;
    out->y = scaler;
    out->z = scaler;
}

void hwm_vector3_add(hwm_vector3_t* out, const hwm_vector3_t* lhs, const hwm_vector3_t* rhs)
{
    out->x = lhs->x + rhs->x;
    out->y = lhs->y + rhs->y;
    out->z = lhs->z + rhs->z;
}

void hwm_vector3_add_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 scaler)
{
    out->x = v->x + scaler;
    out->y = v->y + scaler;
    out->z = v->z + scaler;
}

void hwm_vector3_sub(hwm_vector3_t* out, const hwm_vector3_t* lhs, const hwm_vector3_t* rhs)
{
    out->x = lhs->x - rhs->x;
    out->y = lhs->y - rhs->y;
    out->z = lhs->z - rhs->z;
}

void hwm_vector3_sub_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 scaler)
{
    out->x = v->x - scaler;
    out->y = v->y - scaler;
    out->z = v->z - scaler;
}

void hwm_vector3_mul(hwm_vector3_t* out, const hwm_vector3_t* lhs, const hwm_vector3_t* rhs)
{
    out->x = lhs->x * rhs->x;
    out->y = lhs->y * rhs->y;
    out->z = lhs->z * rhs->z;
}

void hwm_vector3_mul_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 scaler)
{
    out->x = v->x * scaler;
    out->y = v->y * scaler;
    out->z = v->z * scaler;
}

void hwm_vector3_div(hwm_vector3_t* out, const hwm_vector3_t* lhs, const hwm_vector3_t* rhs)
{
    out->x = lhs->x / rhs->x;
    out->y = lhs->y / rhs->y;
    out->z = lhs->z / rhs->z;
}

void hwm_vector3_div_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 scaler)
{
    out->x = v->x / scaler;
    out->y = v->y / scaler;
    out->z = v->z / scaler;
}

hwf32 hwm_vector3_length(const hwm_vector3_t* v)
{
    return hwm_sqrtf(hwm_vector3_length_squared(v));
}

hwf32 hwm_vector3_length_squared(const hwm_vector3_t* v)
{
    return hwm_vector3_dot(v, v);
}

void hwm_vector3_normalize(hwm_vector3_t* out, const hwm_vector3_t* v)
{
    hwf32 length = hwm_vector3_length(v);
    
    if(length > 0.0f) {
        hwm_vector3_div_scaler(out, v, length);
    }
}

void hwm_vector3_abs(hwm_vector3_t* out, const hwm_vector3_t* v)
{
    out->x = hwm_absf(v->x);
    out->y = hwm_absf(v->y);
    out->z = hwm_absf(v->z);
}

void hwm_vector3_perpendicular(hwm_vector3_t* out, const hwm_vector3_t* v)
{
    hwf32 value1 = v->x * v->x;
    hwf32 value2 = v->y * v->y;
    hwf32 value3 = v->z * v->z;

    if(value1 < value2) {
        if(value1 < value3) {
            out->x = 0.0f;
            out->y = -v->z;
            out->z = v->y;
        }
        else {
            out->x = -v->y;
            out->y = v->z;
            out->z = 0.0f;
        }
    }
    else {
        if(value2 < value3) {
            out->x = v->z;
            out->y = 0.0f;
            out->z = -v->x;
        }
        else {
            out->x = -v->y;
            out->y = v->x;
            out->z = 0.0f;
        }
    }
}

hwf32 hwm_vector3_distance(const hwm_vector3_t* v1, const hwm_vector3_t* v2)
{
    hwm_vector3_t diff;

    hwm_vector3_sub(&diff, v2, v1);
    return hwm_vector3_length(&diff);
}

hwf32 hwm_vector3_distance_squared(const hwm_vector3_t* v1, const hwm_vector3_t* v2)
{
    hwm_vector3_t diff;

    hwm_vector3_sub(&diff, v2, v1);
    return hwm_vector3_length_squared(&diff);
}

hwf32 hwm_vector3_dot(const hwm_vector3_t* v1, const hwm_vector3_t* v2)
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

void hwm_vector3_cross(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2)
{
    out->x = v1->y * v2->z - v1->z * v2->y;
    out->y = v1->z * v2->x - v1->x * v2->z;
    out->z = v1->x * v2->y - v1->y * v2->x;
}

void hwm_vector3_min(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2)
{
    out->x = v1->x < v2->x ? v1->x : v2->x;
    out->y = v1->y < v2->y ? v1->y : v2->y;
    out->z = v1->z < v2->z ? v1->z : v2->z;
}

void hwm_vector3_max(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2)
{
    out->x = v1->x > v2->x ? v1->x : v2->x;
    out->y = v1->y > v2->y ? v1->y : v2->y;
    out->z = v1->z > v2->z ? v1->z : v2->z;
}

void hwm_vector3_clamp(hwm_vector3_t* out, const hwm_vector3_t* v, const hwm_vector3_t* min, const hwm_vector3_t* max)
{
    hwm_vector3_min(out, v, max);
    hwm_vector3_max(out, out, min);
}

void hwm_vector3_repeat(hwm_vector3_t* out, const hwm_vector3_t* v, const hwm_vector3_t* min, const hwm_vector3_t* max)
{
    out->x = hwm_repeat(v->x, min->x, max->x);
    out->y = hwm_repeat(v->y, min->y, max->y);
    out->z = hwm_repeat(v->z, min->z, max->z);
}

void hwm_vector3_lerp(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2, hwf32 pos)
{
    hwf32 ratio1 = 1.0f - pos;
    hwf32 ratio2 = pos;

    out->x = v1->x * ratio1 + v2->x * ratio2;
    out->y = v1->y * ratio1 + v2->y * ratio2;
    out->z = v1->z * ratio1 + v2->z * ratio2;
}

void hwm_vector3_slerp(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2, hwf32 pos)
{
    hwf32 length1 = hwm_vector3_length(v1);
    hwf32 length2 = hwm_vector3_length(v2);
    hwf32 angle   = hwm_vector3_angle(v1, v2) * pos;
    hwf32 lerp    = 0.0f;
    hwm_vector3_t  cross;
    hwm_matrix44_t rotate;
    hwm_vector3_t  trans;

    hwm_vector3_cross(&cross, v1, v2);
    hwm_matrix44_set_rotate_axis(&rotate, cross.x, cross.y, cross.z, angle);
    hwm_matrix44_transform_vector3(&trans, &rotate, v1);

    lerp = hwm_lerp(1.0f, length2 / length1, pos);
    hwm_vector3_mul_scaler(out, &trans, pos);
}

void hwm_vector3_move_to(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2, hwf32 length)
{
    hwf32 d = hwm_vector3_distance(v1, v2);

    if(length >= d) {
        *out = *v1;
    }
    else {
        hwm_vector3_lerp(out, v1, v2, length / d);
    }
}

void hwm_vector3_turn_to(hwm_vector3_t* out, const hwm_vector3_t* v1, const hwm_vector3_t* v2, hwf32 angle)
{
    hwf32 current_angle = hwm_vector3_angle(v1, v2);
    if(current_angle < 0.0f) {
        current_angle = -current_angle;
    }

    if(angle >= current_angle) {
        *out = *v1;
    }
    else {
        hwm_vector3_slerp(out, v1, v2, angle / current_angle);
    }
}

hwf32 hwm_vector3_angle(const hwm_vector3_t* v1, const hwm_vector3_t* v2)
{
    hwf32 length1 = hwm_vector3_length(v1);
    hwf32 length2 = hwm_vector3_length(v2);
    hwf32 d       = hwm_vector3_dot(v1, v2);
    hwf32 c       = hwm_clamp(d / (length1 * length2), -1.0f, 1.0f);
    hwf32 c2      = hwm_acosf(c);

    return (v1->x * v2->y - v1->y * v2->x) >= 0.0f ? c2 : -c2;
}

void hwm_vector3_rotate_x_vector(hwm_vector3_t* out, const hwm_vector3_t* v, const struct hwm_vector2_t* rotation)
{
    out->x = v->x;
    out->y = rotation->x * v->y - rotation->y * v->z;
    out->z = rotation->x * v->z + rotation->y * v->y;
}

void hwm_vector3_rotate_x_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 angle)
{
    hwm_vector2_t rotation;

    hwm_vector2_rotate(&rotation, angle);
    hwm_vector3_rotate_x_vector(out, v, &rotation);
}

void hwm_vector3_rotate_y_vector(hwm_vector3_t* out, const hwm_vector3_t* v, const struct hwm_vector2_t* rotation)
{
    out->x = rotation->x * v->x + rotation->y * v->z;
    out->y = v->y;
    out->z = rotation->x * v->z - rotation->y * v->x;
}

void hwm_vector3_rotate_y_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 angle)
{
    hwm_vector2_t rotation;

    hwm_vector2_rotate(&rotation, angle);
    hwm_vector3_rotate_y_vector(out, v, &rotation);
}

void hwm_vector3_rotate_z_vector(hwm_vector3_t* out, const hwm_vector3_t* v, const struct hwm_vector2_t* rotation)
{
    out->x = rotation->x * v->x - rotation->y * v->y;
    out->y = rotation->x * v->y + rotation->y * v->x;
    out->z = v->z;
}

void hwm_vector3_rotate_z_scaler(hwm_vector3_t* out, const hwm_vector3_t* v, hwf32 angle)
{
    hwm_vector2_t rotation;

    hwm_vector2_rotate(&rotation, angle);
    hwm_vector3_rotate_z_vector(out, v, &rotation);
}

void hwm_vector3_reflect(hwm_vector3_t* out, const hwm_vector3_t* v, const hwm_vector3_t* normal)
{
    hwf32 dot;
    hwf32 len;
    hwf32 c;
    hwm_vector3_t tmp;
    
    dot = hwm_vector3_dot(v, normal);
    len = hwm_vector3_length_squared(normal);
    c   = dot / len;

    hwm_vector3_mul_scaler(&tmp, normal, c * 2.0f);
    hwm_vector3_sub(out, v, &tmp);
}

void hwm_vector3_project_on_line(hwm_vector3_t* out, const hwm_vector3_t* v, const hwm_vector3_t* point, const hwm_vector3_t* direction)
{
    hwm_vector3_t diff;
    hwf32 dot;
    hwf32 len;
    hwf32 f;

    hwm_vector3_sub(&diff, v, point);
    dot = hwm_vector3_dot(direction, &diff);
    len = hwm_vector3_length_squared(direction);
    f   = dot / len;

    hwm_vector3_mul_scaler(out, direction, f);
    hwm_vector3_add(out, out, point);
}

hwbool hwm_vector3_is_unit(const hwm_vector3_t* v, hwf32 epsilon)
{
    return hwm_absf(hwm_vector3_length(v) - 1.0f) <= epsilon ? HW_TRUE : HW_FALSE;
}

hwbool hwm_vector3_is_zero(const hwm_vector3_t* v)
{
    return memcmp(v, &HWM_VECTOR3_ZERO, sizeof(hwm_vector3_t)) == 0 ? HW_TRUE : HW_FALSE;
}

hwbool hwm_vector3_is_one(const hwm_vector3_t* v)
{
    return memcmp(v, &HWM_VECTOR3_ONE, sizeof(hwm_vector3_t)) == 0 ? HW_TRUE : HW_FALSE;
}

hwbool hwm_vector3_is_nan(const hwm_vector3_t* v)
{
    return hwm_is_nan(v->x) || hwm_is_nan(v->y) || hwm_is_nan(v->z) ? HW_TRUE : HW_FALSE;
}

