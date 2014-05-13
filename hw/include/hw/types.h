/*
    Copyright okanishi_kazuki
    Lisence
    初版 2011/08/01 okanishi_kazuki

    @file HWライブラリの基本型を定義します
          HWライブラリ全般で使用されており、
	  変数のビット数を明確にする目的があります。
	  例外としてint型は整数のほとんどの用途で使用されます。
*/

#ifndef HW_TYPES_H_
#define HW_TYPES_H_

#include <stddef.h>
#include "hw/platform.h"

#if defined(HW_PLATFORM_MSVC)

typedef signed __int8    hws8;
typedef signed __int16   hws16;
typedef signed __int32   hws32;
typedef signed __int64   hws64;
typedef unsigned __int8  hwu8;
typedef unsigned __int16 hwu16;
typedef unsigned __int32 hwu32;
typedef unsigned __int64 hwu64;

#else

#include <stdint.h>

typedef int8_t   hws8;
typedef int16_t  hws16;
typedef int32_t  hws32;
typedef int64_t  hws64;
typedef uint8_t  hwu8;
typedef uint16_t hwu16;
typedef uint32_t hwu32;
typedef uint64_t hwu64;

#endif

typedef hws32            hwsptr_t;
typedef hwu32            hwptr_t;
typedef float            hwf32;
typedef double           hwf64;
typedef signed int       hwsint;
typedef unsigned int     hwuint;
typedef int hwbool;

#ifndef HW_TRUE
#    define HW_TRUE 1
#endif /* HW_TRUE */

#ifndef HW_FALSE
#    define HW_FALSE 0
#endif /* HW_FALSE */

#endif  /* HW_TYPES_H_  */

