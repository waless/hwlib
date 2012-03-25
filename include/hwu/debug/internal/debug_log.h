#ifndef HWU_DEBUG_INTERNAL_DEBUG_LOG_H_
#define HWU_DEBUG_INTERNAL_DEBUG_LOG_H_

#include "platform.h"

#if !defined(HWU_RELEASE)

extern void hwu_debug_print_formatt(const char* format, ...);
extern void hwu_debug_print(const char* string);

#endif  /* !defined(HWU_RELEASE) */

#endif  /* HWU_DEBUG_INTERNAL_DEBUG_LOG_H_ */
