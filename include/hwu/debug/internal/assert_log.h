#ifndef HWU_DEBUG_INTERNAL_ASSERT_LOG_H_
#define HWU_DEBUG_INTERNAL_ASSERT_LOG_H_

#include "hwu/platform.h"

#ifdef HWU_DEBUG
extern void hwu_assert_put_message(const char* exp, const char* file, const int line, const char* format, ...);
#endif

#endif  /* HWU_DEBUG_INTERNAL_ASSERT_LOG_H_ */
