#ifndef HW_DEBUG_INTERNAL_DEBUG_LOG_H_
#define HW_DEBUG_INTERNAL_DEBUG_LOG_H_

#include "hw/platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(HW_RELEASE)

extern void hw_debug_print_format(const char* format, ...);
extern void hw_debug_print(const char* string);

#endif  /* !defined(HW_RELEASE) */

#ifdef __cplusplus
}
#endif

#endif  /* HW_DEBUG_INTERNAL_DEBUG_LOG_H_ */

