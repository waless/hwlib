#ifndef HW_DEBUG_LOG_H_
#define HW_DEBUG_LOG_H_

#include <stdarg.h>
#include "hw/platform.h"
#include "hw/debug/internal/debug_log.h"

#if defined(HW_RELEASE)
#   define HW_PRINT(string)
#   define HW_PRINTF(format, ...)
#else
#   define HW_PRINT(string) hw_debug_print(string)
#   define HW_PRINTF(format, ...) hw_debug_print_format(__VA_ARGS__)
#endif

#endif  // HW_DEBUG_LOG_H_

