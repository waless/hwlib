#ifndef HWFW_WIN_ERROR_H_
#define HWFW_WIN_ERROR_H_

#include <hw/platform.h>
#include "hwfw/error.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(HW_PLATFORM_WINDOWS_DESKTOP)

typedef enum hwfw_error_win_t {
    HWFW_ERROR_WIN_BEGIN = HWFW_ERROR_BEGIN,
    HWFW_ERROR_WIN_NOTFOUND_INSTANCE,
    HWFW_ERROR_WIN_,
    HWFW_ERROR_WIN_END,
} hwfw_error_win_t;

extern void hwfw_error_push(int kind, const char* message, const char* file, int line);

#if !defined(HWFW_ERROR)
#   define HWFW_ERROR(kind, message) hwfw_error_push(kind, message, __FILE__, __LINE__);
#else
#   error /* defined HWFW_ERROR */
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif

