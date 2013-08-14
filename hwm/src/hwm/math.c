#include "hwm/math.h"
#include <math.h>
#include <stdlib.h>

hwf32 hwm_sinf(hwf32 rad)
{
    return (hwf32)sin(rad);
}

hwf32 hwm_asinf(hwf32 rad)
{
    return (hwf32)asin(rad);
}

hwf32 hwm_cosf(hwf32 rad)
{
    return (hwf32)cos(rad);
}

hwf32 hwm_acosf(hwf32 rad)
{
    return (hwf32)acos(rad);
}

hwf32 hwm_tanf(hwf32 rad)
{
    return (hwf32)tan(rad);
}

hwf32 hwm_atanf(hwf32 rad)
{
    return (hwf32)atan(rad);
}

hwf32 hwm_atan2f(hwf32 y, hwf32 x)
{
    return (hwf32)atan2(y, x);
}

hwf32 hwm_cotf(hwf32 rad)
{
    return 1.0f / hwm_tanf(rad);
}

hwf32 hwm_absf(hwf32 value)
{
    return (hwf32)fabs(value);
}

hwf32 hwm_sqrtf(hwf32 value)
{
    return (hwf32)sqrt(value);
}

hwf32 hwm_fmodf(hwf32 value1, hwf32 value2)
{
    return (hwf32)fmodf(value1, value2);
}

hwf32 hwm_clamp(hwf32 value, hwf32 min, hwf32 max)
{
    if(value < min) {
        return min;
    }
    else if(value > max) {
        return max;
    }
    else {
        return value;
    }
}

hwf32 hwm_repeat(hwf32 value, hwf32 min, hwf32 max)
{
    hwf32 diff = max - min;
    hwf32 v    = (diff == 0.0f) ? 0.0f : hwm_fmodf((value - min), diff);

    return min + ((v >= 0.0f) ? v : (v + diff));
}

hwf32 hwm_lerp(hwf32 begin, hwf32 end, hwf32 pos)
{
    return (end - begin) * pos + begin;
}

hwbool hwm_is_nan(hwf32 value)
{
    return (value != value) ? HW_TRUE : HW_FALSE;
}

