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
    HWFW_ERROR_WIN_END,
} hwfw_error_win_t;

#endif

#ifdef __cplusplus
}
#endif

#endif

