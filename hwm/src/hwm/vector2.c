#include "hwm/vector2.h"
#include <string.h>
#include "hwm/math.h"

const hwm_vector2_t HWM_VECTOR2_ZERO = {0.0f, 0.0f};
const hwm_vector2_t HWM_VECTOR2_ONE  = {1.0f, 1.0f};

void hwm_vector2_set_zero(hwm_vector2_t* out)
{
    *out = HWM_VECTOR2_ZERO;
}

void hwm_vector2_set_one(hwm_vector2_t* out)
{
    *out = HWM_VECTOR2_ONE;
}

void hwm_vector2_set_scaler(hwm_vector2_t* out, hwf32 scaler)
{
    out->x = scaler;
    out->y = scaler;
}

void hwm_vector2_add(hwm_vector2_t* out, const hwm_vector2_t* lhs, const hwm_vector2_t* rhs)
{
    out->x = lhs->x + rhs->x;
    out->y = lhs->y + rhs->y;
}

void hwm_vector2_add_scaler(hwm_vector2_t* out, const hwm_vector2_t* v, hwf32 scaler)
{
    out->x = v->x + scaler;
    out->y = v->x + scaler;
}

void hwm_vector2_sub(hwm_vector2_t* out, const hwm_vector2_t* lhs, const hwm_vector2_t* rhs)
{
    out->x = lhs->x - rhs->x;
    out->y = lhs->y - rhs->y;
}

void hwm_vector2_sub_scaler(hwm_vector2_t* out, const hwm_vector2_t* v, hwf32 scaler)
{
    out->x = v->x - scaler;
    out->y = v->y - scaler;
}

void hwm_vector2_mul(hwm_vector2_t* out, const hwm_vector2_t* lhs, const hwm_vector2_t* rhs)
{
    out->x = lhs->x * rhs->x;
    out->y = lhs->y * rhs->y;
}

void hwm_vector2_mul_scaler(hwm_vector2_t* out, const hwm_vector2_t* v, hwf32 scaler)
{
    out->x = v->x * scaler;
    out->y = v->y * scaler;
}

void hwm_vector2_div(hwm_vector2_t* out, const hwm_vector2_t* lhs, const hwm_vector2_t* rhs)
{
    out->x = lhs->x / rhs->x;
    out->y = lhs->y / rhs->y;
}

void hwm_vector2_div_scaler(hwm_vector2_t* out, const hwm_vector2_t* v, hwf32 scaler)
{
    out->x = v->x / scaler;
    out->y = v->y / scaler;
}

hwf32 hwm_vector2_length(const hwm_vector2_t* v)
{
    return hwm_sqrtf(hwm_vector2_length_squared(v));
}

hwf32 hwm_vector2_length_squared(const hwm_vector2_t* v)
{
    return hwm_vector2_dot(v, v);
}

void hwm_vector2_normalize(hwm_vector2_t* out, const hwm_vector2_t* v)
{
    hwf32 length = hwm_vector2_length(v);

    if(length > 0.0f) {
        hwm_vector2_div_scaler(out, v, length);
    }
}

void hwm_vector2_abs(hwm_vector2_t* out, const hwm_vector2_t* v)
{
    out->x = hwm_absf(v->x);
    out->y = hwm_absf(v->y);
}

void hwm_vector2_perpendicular(hwm_vector2_t* out, const hwm_vector2_t* v)
{
    out->x = -v->y;
    out->y =  v->x;
}

hwf32 hwm_vector2_distance(const hwm_vector2_t* v1, const hwm_vector2_t* v2)
{
    hwm_vector2_t diff;

    hwm_vector2_sub(&diff, v1, v2);
    return hwm_vector2_length(&diff);
}

hwf32 hwm_vector2_distance_squared(const hwm_vector2_t* v1, const hwm_vector2_t* v2)
{
    hwm_vector2_t diff;

    hwm_vector2_sub(&diff, v1, v2);
    return hwm_vector2_length_squared(&diff);
}

hwf32 hwm_vector2_dot(const hwm_vector2_t* v1, const hwm_vector2_t* v2)
{
    return v1->x * v2->x + v1->y * v2->y;
}

hwf32 hwm_vector2_determinant(const hwm_vector2_t* v1, const hwm_vector2_t* v2)
{
    return v1->x * v2->y - v1->y * v2->x;
}

void hwm_vector2_min(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2)
{
    out->x = v1->x < v2->x ? v1->x : v2->x;
    out->y = v1->y < v2->y ? v1->y : v2->y;
}

void hwm_vector2_max(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2)
{
    out->x = v1->x > v2->x ? v1->x : v2->x;
    out->y = v1->y > v2->y ? v1->y : v2->y;
}

void hwm_vector2_clamp(hwm_vector2_t* out, const hwm_vector2_t* v, const hwm_vector2_t* min, const hwm_vector2_t* max)
{
    hwm_vector2_min(out, v, max);
    hwm_vector2_max(out, out, min);
}

void hwm_vector2_repeat(hwm_vector2_t* out, const hwm_vector2_t* v, const hwm_vector2_t* min, const hwm_vector2_t* max)
{
    out->x = hwm_repeat(v->x, min->x, max->x);
    out->y = hwm_repeat(v->y, min->y, max->y);
}

void hwm_vector2_lerp(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2, hwf32 pos)
{
    hwf32 ratio1 = 1.0f - pos;
    hwf32 ratio2 = pos;

    out->x = v1->x * ratio1 + v2->x * ratio2;
    out->y = v1->y * ratio1 + v2->y * ratio2;
}

void hwm_vector2_slerp(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2, hwf32 pos)
{
    hwf32 length1 = hwm_vector2_length(v1);
    hwf32 length2 = hwm_vector2_length(v2);
    hwf32 angle   = hwm_vector2_angle(v1, v2) * pos;

    hwm_vector2_rotate(out, angle);
    hwm_vector2_mul_scaler(out, out, hwm_lerp(1.0f, length2 / length1, pos));
}

void hwm_vector2_move_to(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2, hwf32 length)
{
    hwf32 distance = hwm_vector2_distance(v1, v2);

    if(length >= distance) {
        *out = *v1;
    }
    else {
        hwm_vector2_lerp(out, v1, v2, length / distance);
    }
}

void hwm_vector2_turn_to(hwm_vector2_t* out, const hwm_vector2_t* v1, const hwm_vector2_t* v2, hwf32 angle)
{
    hwf32 current_angle = hwm_vector2_angle(v1, v2);
    if(current_angle < 0.0f) {
        current_angle = -current_angle;
    }

    if(angle >= current_angle) {
        *out = *v1;
    }
    else {
        hwm_vector2_slerp(out, v1, v2, angle / current_angle);
    }
}

hwf32 hwm_vector2_angle(const hwm_vector2_t* v1, const hwm_vector2_t* v2)
{
    hwf32 length1 = hwm_vector2_length(v1);
    hwf32 length2 = hwm_vector2_length(v2);
    hwf32 d       = hwm_vector2_dot(v1, v2);
    hwf32 c       = d / (length1 * length2);
    hwf32 c2      = hwm_acosf(c);

    return (v1->x * v2->y - v1->y * v2->x) >= 0.0f ? c2 : -c2;
}

void hwm_vector2_rotate_vector(hwm_vector2_t* out, const hwm_vector2_t* v, const hwm_vector2_t* rotation)
{
    out->x = rotation->x * v->x - rotation->y * v->y;
    out->y = rotation->x * v->y + rotation->y * v->x;
}

void hwm_vector2_rotate_scaler(hwm_vector2_t* out, const hwm_vector2_t* v, hwf32 angle)
{
    hwm_vector2_t rotation;

    hwm_vector2_rotate(&rotation, angle);
    hwm_vector2_rotate_vector(out, v, &rotation);
}

void hwm_vector2_rotate(hwm_vector2_t* out, hwf32 angle)
{
    out->x = hwm_cosf(angle);
    out->y = hwm_sinf(angle);
}

void hwm_vector2_reflect(hwm_vector2_t* out, const hwm_vector2_t* v, const hwm_vector2_t* normal)
{
    hwf32 dot;
    hwf32 len;
    hwf32 c;
    hwm_vector2_t tmp;

    dot = hwm_vector2_dot(v, normal);
    len = hwm_vector2_length_squared(normal);
    c   = dot / len;

    hwm_vector2_mul_scaler(&tmp, normal, c * 2.0f);
    hwm_vector2_sub(out, v, &tmp);
}

void hwm_vector2_project_on_line(hwm_vector2_t* out, const hwm_vector2_t* v, const hwm_vector2_t* point, const hwm_vector2_t* direction)
{
    hwm_vector2_t diff;
    hwf32 len;
    hwf32 dot;
    hwf32 f;

    hwm_vector2_sub(&diff, v, point);
    dot = hwm_vector2_dot(direction, &diff);
    len = hwm_vector2_length_squared(direction);
    f   = dot / len;

    hwm_vector2_mul_scaler(out, direction, f);
    hwm_vector2_add(out, out, point);
}

hwbool hwm_vector2_is_unit(const hwm_vector2_t* v, hwf32 epsilon)
{
    return hwm_absf(hwm_vector2_length(v) - 1.0f) <= epsilon;
}

hwbool hwm_vector2_is_zero(const hwm_vector2_t* v)
{
    return memcmp(v, &HWM_VECTOR2_ZERO, sizeof(hwm_vector2_t)) == 0;
}

hwbool hwm_vector2_is_one(const hwm_vector2_t* v)
{
    return memcmp(v, &HWM_VECTOR2_ONE, sizeof(hwm_vector2_t)) == 0;
}

hwbool hwm_vector2_is_nan(const hwm_vector2_t* v)
{
    return hwm_is_nan(v->x) || hwm_is_nan(v->y);
}

