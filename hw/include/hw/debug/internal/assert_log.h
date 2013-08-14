#ifndef HW_DEBUG_INTERNAL_ASSERT_LOG_H_
#define HW_DEBUG_INTERNAL_ASSERT_LOG_H_

#include "hw/platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(HW_RELEASE)
extern void hw_assert_put_message(const char* exp, const char* file, const int line, const char* format, ...);
#endif

#ifdef __cplusplus
}
#endif

#endif  /* HW_DEBUG_INTERNAL_ASSERT_LOG_H_ */
