#ifndef HW_DEBUG_ASSERT_
#define HW_DEBUG_ASSERT_

#include <stdlib.h>
#include "hw/platform.h"
#include "hw/types.h"
#include "hw/debug/internal/assert_log.h"

#ifdef HW_PLATFORM_MSVC
#   include <Windows.h>
#endif

#ifdef HW_DEBUG

#   ifdef HW_PLATFORM_MSVC
#      define HW_ABORT() DebugBreak()
#   elif defined(HW_PLATFORM_GCC)
#      define HW_ABORT() exit(0)
#   else
#      error // 未対応なのでエラーにする
#   endif

#   define HW_ASSERT_MESSAGE(exp, message)							\
	   if((exp) == FALSE){hw_assert_put_message(#exp, __FILE__, __LINE__, message); HW_ABORT();}

#   define HW_ASSERT(exp) HW_ASSERT_MESSAGE(exp, "");
#   define HW_NULL_ASSERT(exp) HW_ASSERT_MESSAGE(exp, "null pointer");

#   define __CTSTR0(str0, str1) str0##str1
#   define __CTSTR1(str0, str1) __CTSTR0(str0, str1)
#   define HW_STATIC_ASSERT_MESSAGE(exp, message) typedef struct{int __CTSTR1(static_assert_failed_,message) : !!(exp); } __CTSTR1(static_assert_failed_,__COUNTER__)
#   define HW_STATIC_ASSERT(exp) HW_STATIC_ASSERT_MESSAGE(exp, exp)

#   define HW_VEFITY(exp) HW_ASSERT(exp)
#   define HW_VEFITY_MESSAGE(exp, message) HW_ASSERT_MESSAGE(exp,message)

#   define HW_TRY(exp) HW_ASSERT(exp)
#   define HW_TRY_VRETURN(exp, ret) HW_ASSERT(exp)
#else
#   define HW_ABORT() exit(1)
#   define HW_ASSERT(exp)
#   define HW_ASSERT_MESSAGE(exp, message)
#   define HW_NULL_ASSERT(exp)
#   define HW_STATIC_ASSERT(exp)
#   define HW_STATIC_ASSERT_MESSAGE(exp, message)
#   define HW_VEFITY(exp) exp
#   define HW_VEFITY_MESSAGE(exp,message) exp
#   define HW_TRY_VRETURN(exp, ret) if((exp) == FALSE) {return ret;}
#   define HW_TRY(exp) HW_TRY_VRETURN(exp,)
#endif

#endif  /* HW_DEBUG_ASSERT_ */

