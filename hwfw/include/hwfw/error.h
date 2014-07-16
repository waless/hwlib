#ifndef HWFW_ERROR_H_
#define HWFW_ERROR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum hwfw_error_t
{
    HWFW_ERROR_NUM,
} hwfw_error_t;

#if defined(HW_PLATFORM_WINDOWS_DESKTOP)
#   include "hwfw/win/error.h"
#elif defined(HW_PLATFORM_WINDOWS_PHONE)
#   error /* not support */
#elif defined(HW_PLATFORM_IOS)
#   error /* not support */
#elif defined(HW_PLATFORM_ANDROID)
#   error /* not support */
#else
#   error /* invalid platform */
#endif

#ifdef __cplusplus
}
#endif

#endif

