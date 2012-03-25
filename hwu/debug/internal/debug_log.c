#include "hwu/platform.h"
#include "hwu/debug/internal/debug_log.h"
#include <stddef.h>
#include <stdio.h>

#ifdef HWU_PLATFORM_MSVC
#   include <Windows.h>
#endif

#if !defined(HWU_RELEASE)

void hwu_debug_print_format(const char* format, ...) {
    char out[256] = {0};
    va_list args;
    va_start(args, format);
    vsprintf(out, format, args);
    va_end(args);
    hwu_debug_print(out);
}

void hwu_debug_print(const char* string) {
    if(string != NULL) {
#if defined(HWU_PLATFORM_MSVC)
	  OutputDebugStringA(string);
#elif defined(HWU_PLATFORM_GCC)
	  printf(string);
#else
#   error /* 未対応なのでエラー出すように */
#endif
    }
}

#endif /* !defined(HWU_RELEASE) */
