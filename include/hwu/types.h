/*
    Copyright okanishi_kazuki
    Lisence
    初版 2011/08/01 okanishi_kazuki

    @file HWUライブラリの基本型を定義します
          HWUライブラリ全般で使用されており、
	  変数のビット数を明確にする目的があります。
	  例外としてint型は整数のほとんどの用途で使用されます。
*/

#ifndef HWU_TYPES_H_
#define HWU_TYPES_H_

#include <stddef.h>
#include "hwu/platform.h"

#ifdef HWU_PLATFORM_32BIT

typedef signed char        hws8;
typedef signed short       hws16;
typedef signed long        hws32;
typedef unsigned char      hwu8;
typedef unsigned short     hwu16;
typedef unsigned long      hwu32;
typedef unsigned long long hwu64;
typedef hws32              hwsptr_t;
typedef hwu32              hwuptr_t;
typedef float              hwf32;
typedef double             hwf64;

#endif  /* HWU_PLATFORM_32BIT */

typedef int BOOL;

#ifndef TRUE
#    define TRUE  1;
#endif  /* TRUE */

#ifndef FALSE
#    define FALSE 0;
#endif  /* FALSE */

#endif  /* HWU_TYPES_H_  */
