#ifndef HWU_DEBUG_LOG_H_
#define HWU_DEBUG_LOG_H_

#include <stdarg.h>
#include "hwu/platform.h"
#include "hwu/debug/internal/debug_log.h"

#if defined(HWU_RELEASE)
#   define HWU_PRINT(string)
#   define HWU_PRINTF(format, ...)
#else
#   define HWU_PRINT(string) hwu_debug_print(string)
#   define HWU_PRINTF(format, ...) hwu_debug_print_format(__VA_ARGS__)
#endif

#endif  // HWU_DEBUG_LOG_H_
