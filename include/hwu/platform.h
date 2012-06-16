/*
    Copyright 2011 okanishi_kazuki
    Lisence:TODO
    初版 2011/07/08 okanishi_kazuki

    @file このファイルでは環境別プリプロセッサ定義を定義する
          環境別に必ず以下の定義を行わなければならない

	  HWU_DEBUG   : デバッグコンパイル
	  HWU_PROFILE : プロファイルコンパイル
	  HWU_RELEASE : 出荷コンパイル
	                これはユーザーが明示的に定義すること
					定義されていない場合、HWU_PROFILEを定義する

      HWU_PLATFORM_32BIT  : 32bit環境
	  HWU_PLATFORM_64BIT  : 64bit環境

	  HWU_PLATFORM_MSVC   : MicrosoftVisualStudioC++環境
	  HWU_PLATFORM_MSVC32 : MicrosoftVisualStudioC++32bit環境
	  HWU_PLATFORM_MSVC64 : MicrosoftVisualStudioC++64bit環境

	  HWU_PLATFORM_GCC32  : gcc32bit環境
	  HWU_PLATFORM_GCC64  : gcc64bit環境
*/
#ifndef HWU_PLATFORM_H_
#define HWU_PLATFORM_H_

/* MicrosoftVisualStudioC++関連の環境定義 */
#if defined(_MSC_VER)

/* MicrosoftVisualStudioC++定義 */
#   define HWU_PLATFORM_MSVC

/* 32bit or 64bit 定義 */
#   if defined(_WIN64)
#       define HWU_PLATFORM_64BIT
#       define HWU_PLATFORM_MSVC64
#   elif
#       define HWU_PLATFORM_32BIT
#       define HWU_PLATFORM_MSVC32
#   endif


/* 他環境を考えるとVC専用関数は多用できないのでセキュア関数関連の警告を無視する */
#   pragma warning(disable:4996)

/* GCC環境定義 */
#elif defined(__GNUC__)

/* GCC定義 */
#   define HWU_PLATFORM_GCC

/* 32bit or 64bit 定義 */
#   if defined(__i386__)
#       define HWU_PLATFORM_32BIT
#       define HWU_PLATFORM_GCC32
#   else
#       define HWU_PLATFORM_64BIT
#       define HWU_PLATFORM_GCC64
#   endif
#endif	/* defined(__GNUC__) */

/* コンパイルターゲット定義 */
/* デバッグコンパイルでなく、HWU_RELEASE設定でなければHWU_PROFILE設定にしておく */
/* HWU_RELEASE設定はユーザーが明示的に行うこと */
#if defined(_DEBUG)
#   define HWU_DEBUG
#elif !defined(HWU_RELEASE)
#   define HWU_PROFILE
#endif

#endif  /* HWU_PLATFORM_H_ */

