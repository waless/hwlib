#ifndef HWU_DEBUG_ASSERT_
#define HWU_DEBUG_ASSERT_

#include <stdlib.h>
#include "hwu/platform.h"
#include "hwu/types.h"
#include "hwu/debug/internal/assert_log.h"

#ifdef HWU_PLATFORM_MSVC
#   include <Windows.h>
#endif

#ifdef HWU_DEBUG

#   ifdef HWU_PLATFORM_MSVC
#      define HWU_ABORT() DebugBreak()
#   elif defined(HWU_PLATFORM_GCC)
#      define HWU_ABORT() exit(0)
#   else
#      error // 未対応なのでエラーにする
#   endif

#   define HWU_ASSERT_MESSAGE(exp, message)							\
	   if((exp) == FALSE){hwu_assert_put_message(#exp, __FILE__, __LINE__, message); HWU_ABORT();}

#   define HWU_ASSERT(exp) HWU_ASSERT_MESSAGE(exp, "");
#   define HWU_NULL_ASSERT(exp) HWU_ASSERT_MESSAGE(exp, "null pointer");

#   define __CTSTR0(str0, str1) str0##str1
#   define __CTSTR1(str0, str1) __CTSTR0(str0, str1)
#   define HWU_STATIC_ASSERT_MESSAGE(exp, message) typedef struct{int __CTSTR1(static_assert_failed_,message) : !!(exp); } __CTSTR1(static_assert_failed_,__COUNTER__)
#   define HWU_STATIC_ASSERT(exp) HWU_STATIC_ASSERT_MESSAGE(exp, exp)

#   define HWU_VEFITY(exp) HWU_ASSERT(exp)
#   define HWU_VEFITY_MESSAGE(exp, message) HWU_ASSERT_MESSAGE(exp,message)

#   define HWU_TRY(exp) HWU_ASSERT(exp)
#   define HWU_TRY_VRETURN(exp, ret) HWU_ASSERT(exp)
#else
#   define HWU_ABORT() exit(1)
#   define HWU_ASSERT(exp)
#   define HWU_ASSERT_MESSAGE(exp, message)
#   define HWU_NULL_ASSERT(exp)
#   define HWU_STATIC_ASSERT(exp)
#   define HWU_STATIC_ASSERT_MESSAGE(exp, message)
#   define HWU_VEFITY(exp) exp
#   define HWU_VEFITY_MESSAGE(exp,message) exp
#   define HWU_TRY_VRETURN(exp, ret) if((exp) == FALSE) {return ret;}
#   define HWU_TRY(exp) HWU_TRY_VRETURN(exp,)
#endif

#endif  /* HWU_DEBUG_ASSERT_ */

