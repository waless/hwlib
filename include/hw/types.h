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

#ifdef HW_PLATFORM_32BIT

typedef signed char        hws8;
typedef signed short       hws16;
typedef signed long        hws32;
typedef unsigned char      hw8;
typedef unsigned short     hw16;
typedef unsigned long      hw32;
typedef unsigned long long hw64;
typedef hws32              hwsptr_t;
typedef hw32              hwptr_t;
typedef float              hwf32;
typedef double             hwf64;

#endif  /* HW_PLATFORM_32BIT */

typedef int hwbool;

#ifndef hwtrue
#    define hwtrue 1
#endif /* hwtrue */

#ifndef hwfalse
#    define hwfalse 0
#endif /* hwfalse */

#endif  /* HW_TYPES_H_  */

