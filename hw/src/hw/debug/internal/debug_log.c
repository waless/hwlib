#include "hw/platform.h"
#include "hw/debug/internal/debug_log.h"
#include <stddef.h>
#include <stdio.h>

#ifdef HW_PLATFORM_MSVC
#   include <Windows.h>
#else
#   include <stdarg.h>
#endif

#if !defined(HW_RELEASE)

void hw_debug_print_format(const char* format, ...) {
    char out[256] = {0};
    va_list args;
    va_start(args, format);
    vsprintf(out, format, args);
    va_end(args);
    hw_debug_print(out);
}

void hw_debug_print(const char* string) {
    if(string != NULL) {
#if defined(HW_PLATFORM_MSVC)
	  OutputDebugStringA(string);
#elif defined(HW_PLATFORM_GCC)
	  printf(string);
#else
#   error /* 未対応なのでエラー出すように */
#endif
    }
}

#endif /* !defined(HW_RELEASE) */
