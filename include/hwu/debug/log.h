#ifndef HWU_DEBUG_LOG_H_
#define HWU_DEBUG_LOG_H_

#include <stdarg.h>
#include "platform.h"
#include "debug/internal/debug_log.h"

#if defined(HWU_RELEASE)
#   define HWU_PRINTF(format, ...)
#else
#   define HWU_PRINTF(format, ...) hwu_debug_print_format(__VA_ARGS__)
#endif

#endif  // HWU_DEBUG_LOG_H_
