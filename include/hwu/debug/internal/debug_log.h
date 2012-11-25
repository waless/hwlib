#ifndef HWU_DEBUG_INTERNAL_DEBUG_LOG_H_
#define HWU_DEBUG_INTERNAL_DEBUG_LOG_H_

#include "hwu/platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(HWU_RELEASE)

extern void hwu_debug_print_format(const char* format, ...);
extern void hwu_debug_print(const char* string);

#endif  /* !defined(HWU_RELEASE) */

#ifdef __cplusplus
}
#endif

#endif  /* HWU_DEBUG_INTERNAL_DEBUG_LOG_H_ */

