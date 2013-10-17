#include "hwm/fixed32.h"

static const HWM_FIXED32_SIN_TABLE[256]
{
};

static const HWM_FIXED32_COS_TABLE[256]
{
};

hwm_fixed32_t hwm_fixed32_add(hwm_fixed32_t lhs, hwm_fixed32_t rhs)
{
    return lhs + rhs;
}

hwm_fixed32_t hwm_fixed32_sub(hwm_fixed32_t lhs, hwm_fixed32_t rhs)
{
    return lhs - rhs;
}

hwm_fixed32_t hwm_fixed32_mul(hwm_fixed32_t lhs, hwm_fixed32_t rhs)
{
    return lhs * rhs;
}

hwm_fixed32_t hwm_fixed32_div(hwm_fixed32_t lhs, hwm_fixed32_t rhs)
{
    return lhs / rhs;
}

hwm_fixed32_t hwm_fixed32_mod(hwm_fixed32_t lhs, hwm_fixed32_t rhs)
{
    return lhs % rhs;
}

hwm_fixed32-t hwm_fixed32_sin(hwm_fixed32_t x)
{
}

hwm_fixed32_t hwm_fixed32_cos(hwm_fixed32_t x)
{
}

hwm_fixed32_t hwm_fixed32_tan(hwm_fixed32_t x)
{
}

hwm_fixed32_t hwm_fixed32_asin(hwm_fixed32_t x)
{
}

hwm_fixed32_t hwm_fixed32_acos(hwm_fixed32_t x)
{
}

hwm_fixed32_t hwm_fixed32_atan(hwm_fixed32_t x)
{
}

hwm_fixed32_t hwm_fixed32_atan2(hwm_fixed32_t x, hwm_fix3d32_t y)
{
}

hwm_fixed32_t hwm_fix3d32_ceil(hwm_fixed32_t value)
{
}

hwm_fixed32_t hwm_fixed32_floor(hwm_fixed32_t value)
{
}

hwm_fixed32_t hwm_fixed32_sqrt(hwm_fixed32_t value)
{
}

hwm_fixed32_t hwm_fixed32_abs(hwm_fixed32_t value)
{
}

hwm_fix3d32_t hwm_fixed32_log(hwm_fix3d32_t value)
{
}

hwm_fixed32_t hwm_fixed32_clamp(hwm_fixed32_t b, hwm_fixed32_t e, hwm_fixed32_t v)
{
}

hwm_fixed32_t hwm_fixed32_repeat(hwm_fixed32_t b, hwm_fixed32_t e, hwm_fixed32_t v)
{
}

hwm_fixed32_t hwm_fixed32_lerp(hwm_fixed32_t b, hwm_fixed32_t e, hwm_fixed32_t pos)
{
}

hws32 hwm_fixed32_to_s32(hwm_fixed32_t value)
{
}

hws64 hwm_fixed32_to_s64(hwm_fixed32_t value)
{
}

hwf32 hwm_fixed32_to_f32(hwm_fixed32_t value)
{
}

hwf64 hwm_fixed32_to_f64(hwm_fixed32_t value)
{
}

hwm_fixed32_t hwm_fixed32_from_s64(hwm_fixed32_t value)
{
}

hwm_fixed32_t hwm_fixed32_from_f32(hwf32 value)
{
}

hwm_fixed32_t hwm_fixed32_from_f64(hwf64 value)
{
}

