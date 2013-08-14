#include "hwm/vector4.h"
#include <string.h>
#include "hwm/math.h"

const hwm_vector4_t k_hwm_vector4_one    = {1.0f, 1.0f, 1.0f, 1.0f};
const hwm_vector4_t k_hwm_vector4_zero   = {0.0f, 0.0f, 0.0f, 0.0f};
const hwm_vector4_t k_hwm_vector4_unit_x = {1.0f, 0.0f, 0.0f, 0.0f};
const hwm_vector4_t k_hwm_vector4_unit_y = {0.0f, 1.0f, 0.0f, 0.0f};
const hwm_vector4_t k_hwm_vector4_unit_z = {0.0f, 0.0f, 1.0f, 0.0f};
const hwm_vector4_t k_hwm_vector4_unit_w = {0.0f, 0.0f, 0.0f, 1.0f};

void hwm_vector4_set_zero(hwm_vector4_t* out)
{
    *out = k_hwm_vector4_zero;
}

void hwm_vector4_set_one(hwm_vector4_t* out)
{
    *out = k_hwm_vector4_one;
}

void hwm_vector4_set_unix_x(hwm_vector4_t* out)
{
    *out = k_hwm_vector4_unit_x;
}

void hwm_vector4_set_unix_y(hwm_vector4_t* out)
{
    *out = k_hwm_vector4_unit_y;
}

void hwm_vector4_set_unix_z(hwm_vector4_t* out)
{
    *out = k_hwm_vector4_unit_z;
}

void hwm_vector4_set_unix_w(hwm_vector4_t* out)
{
    *out = k_hwm_vector4_unit_w;
}

void hwm_vector4_set_scaler(hwm_vector4_t* out, hwf32 scaler)
{
    out->x = scaler;
    out->y = scaler;
    out->z = scaler;
    out->w = scaler;
}

void hwm_vector4_add(hwm_vector4_t* out, const hwm_vector4_t* lhs, const hwm_vector4_t* rhs)
{
    out->x = lhs->x + rhs->x;
    out->y = lhs->y + rhs->y;
    out->z = lhs->z + rhs->z;
    out->w = lhs->w + rhs->w;
}

void hwm_vector4_add_scaler(hwm_vector4_t* out, const hwm_vector4_t* v, hwf32 scaler)
{
    out->x = v->x + scaler;
    out->y = v->y + scaler;
    out->z = v->z + scaler;
    out->w = v->w + scaler;
}

void hwm_vector4_sub(hwm_vector4_t* out, const hwm_vector4_t* lhs, const hwm_vector4_t* rhs)
{
    out->x = lhs->x - rhs->x;
    out->y = lhs->y - rhs->y;
    out->z = lhs->z - rhs->z;
    out->w = lhs->w - rhs->w;
}

void hwm_vector4_sub_scaler(hwm_vector4_t* out, const hwm_vector4_t* v, hwf32 scaler)
{
    out->x = v->x - scaler;
    out->y = v->y - scaler;
    out->z = v->z - scaler;
    out->w = v->w - scaler;
}

void hwm_vector4_mul(hwm_vector4_t* out, const hwm_vector4_t* lhs, const hwm_vector4_t* rhs)
{
    out->x = lhs->x * rhs->x;
    out->y = lhs->y * rhs->y;
    out->z = lhs->z * rhs->z;
    out->w = lhs->w * rhs->w;
}

void hwm_vector4_mul_scaler(hwm_vector4_t* out, const hwm_vector4_t* v, hwf32 scaler)
{
    out->x = v->x * scaler;
    out->y = v->y * scaler;
    out->z = v->z * scaler;
    out->w = v->w * scaler;
}

void hwm_vector4_div(hwm_vector4_t* out, const hwm_vector4_t* lhs, const hwm_vector4_t* rhs)
{
    out->x = lhs->x / rhs->x;
    out->y = lhs->y / rhs->y;
    out->z = lhs->z / rhs->z;
    out->w = lhs->w / rhs->w;
}

void hwm_vector4_div_scaler(hwm_vector4_t* out, const hwm_vector4_t* v, hwf32 scaler)
{
    out->x = v->x / scaler;
    out->y = v->y / scaler;
    out->z = v->z / scaler;
    out->w = v->w / scaler;
}

hwf32 hwm_vector4_length(const hwm_vector4_t* v)
{
    return hwm_sqrtf(hwm_vector4_length_squared(v));
}

hwf32 hwm_vector4_length_squared(const hwm_vector4_t* v)
{
    return hwm_vector4_dot(v, v);
}

void hwm_vector4_normalize(hwm_vector4_t* out, const hwm_vector4_t* v)
{
    hwf32 length = hwm_vector4_length(v);
    if(length > 0.0f) {
        out->x = v->x / length;
        out->y = v->y / length;
        out->z = v->z / length;
        out->w = v->w / length;
    }
}

void hwm_vector4_abs(hwm_vector4_t* out, const hwm_vector4_t* v)
{
    out->x = hwm_absf(v->x);
    out->y = hwm_absf(v->y);
    out->z = hwm_absf(v->z);
    out->w = hwm_absf(v->w);
}

hwf32 hwm_vector4_distance(const hwm_vector4_t* v1, const hwm_vector4_t* v2)
{
    hwm_vector4_t diff;

    hwm_vector4_sub(&diff, v2, v1);
    return hwm_vector4_length(&diff);
}

hwf32 hwm_vector4_distance_squared(const hwm_vector4_t* v1, const hwm_vector4_t* v2)
{
    hwm_vector4_t diff;

    hwm_vector4_sub(&diff, v2, v1);
    return hwm_vector4_length_squared(&diff);
}

hwf32 hwm_vector4_dot(const hwm_vector4_t* v1, const hwm_vector4_t* v2)
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z + v1->w * v2->w;
}

void hwm_vector4_min(hwm_vector4_t* out, const hwm_vector4_t* v1, const hwm_vector4_t* v2)
{
    out->x = v1->x < v2->x ? v1->x : v2->x;
    out->y = v1->y < v2->y ? v1->y : v2->y;
    out->z = v1->z < v2->z ? v1->z : v2->z;
    out->w = v1->w < v2->w ? v1->w : v2->w;
}

void hwm_vector4_max(hwm_vector4_t* out, const hwm_vector4_t* v1, const hwm_vector4_t* v2)
{
    out->x = v1->x > v2->x ? v1->x : v2->x;
    out->y = v1->y > v2->y ? v1->y : v2->y;
    out->z = v1->z > v2->z ? v1->z : v2->z;
    out->w = v1->w > v2->w ? v1->w : v2->w;
}

void hwm_vector4_clamp(hwm_vector4_t* out, const hwm_vector4_t* v, const hwm_vector4_t* min, const hwm_vector4_t* max)
{
    hwm_vector4_min(out, v, max);
    hwm_vector4_max(out, out, min);
}

void hwm_vector4_repeat(hwm_vector4_t* out, const hwm_vector4_t* v, const hwm_vector4_t* min, const hwm_vector4_t* max)
{
    out->x = hwm_repeat(v->x, min->x, max->x);
    out->y = hwm_repeat(v->y, min->x, max->y);
    out->z = hwm_repeat(v->z, min->x, max->z);
    out->w = hwm_repeat(v->w, min->x, max->w);
}

void hwm_vector4_lerp(hwm_vector4_t* out, const hwm_vector4_t* v1, const hwm_vector4_t* v2, hwf32 pos)
{
    hwf32 ratio1 = 1.0f - pos;
    hwf32 ratio2 = pos;

    out->x = v1->x * ratio1 + v2->x * ratio2;
    out->y = v1->y * ratio1 + v2->y * ratio2;
    out->z = v1->z * ratio1 + v2->z * ratio2;
    out->w = v1->w * ratio1 + v2->w * ratio2;
}

void hwm_vector4_move_to(hwm_vector4_t* out, const hwm_vector4_t* v1, const hwm_vector4_t* v2, hwf32 length)
{
    hwf32 distance = hwm_vector4_distance(v1, v2);

    if(length >= distance) {
        *out = *v1;
    }
    else {
        hwm_vector4_lerp(out, v1, v2, length / distance);
    }
}

hwbool hwm_vector4_is_unit(const hwm_vector4_t* v, hwf32 epsilon)
{
    return hwm_absf(hwm_vector4_length(v) - 1.0f) <= epsilon ? HW_TRUE : HW_FALSE;
}

hwbool hwm_vector4_is_zero(const hwm_vector4_t* v)
{
    return memcmp(v, &k_hwm_vector4_zero, sizeof(hwm_vector4_t)) == 0 ? HW_TRUE : HW_FALSE;
}

hwbool hwm_vector4_is_one(const hwm_vector4_t* v)
{
    return memcmp(v, &k_hwm_vector4_one, sizeof(hwm_vector4_t)) == 0 ? HW_TRUE : HW_FALSE;
}

hwbool hwm_vector4_is_nan(const hwm_vector4_t* v)
{
    return (hwm_is_nan(v->x) || hwm_is_nan(v->y) || hwm_is_nan(v->z) || hwm_is_nan(v->w)) ? HW_TRUE : HW_FALSE;
}

