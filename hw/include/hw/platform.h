/*
    Copyright 2011 okanishi_kazuki
    Lisence:TODO
    初版 2011/07/08 okanishi_kazuki

    @file このファイルでは環境別プリプロセッサ定義を定義する
          環境別に必ず以下の定義を行わなければならない

	  HW_DEBUG   : デバッグコンパイル
	  HW_PROFILE : プロファイルコンパイル
	  HW_RELEASE : 出荷コンパイル
	                これはユーザーが明示的に定義すること
					定義されていない場合、HW_PROFILEを定義する

      HW_PLATFORM_32BIT  : 32bit環境
	  HW_PLATFORM_64BIT  : 64bit環境

	  HW_PLATFORM_MSVC   : MicrosoftVisualStudioC++環境
	  HW_PLATFORM_MSVC32 : MicrosoftVisualStudioC++32bit環境
	  HW_PLATFORM_MSVC64 : MicrosoftVisualStudioC++64bit環境

	  HW_PLATFORM_GCC32  : gcc32bit環境
	  HW_PLATFORM_GCC64  : gcc64bit環境

      HW_PLATFORM_WINDOWS : windows環境
      HW_PLATFORM_OSX     : mac-osx環境
      HW_PLATFORM_ANDROID : android環境
      HW_PLATFORM_IOS     : ios環境
      HW_PLATFORM_WP8     : windows phone8
*/
#ifndef HW_PLATFORM_H_
#define HW_PLATFORM_H_

/* ビルドツール定義 */
/* MicrosoftVisualStudioC++関連の環境定義 */
#if defined(_MSC_VER)

/* MicrosoftVisualStudioC++定義 */
#   define HW_PLATFORM_MSVC

#   if defined(WINDOWS)
#       define HW_PLATFORM_WINDOWS
#   elif defined(WINDOWS_PHONE)
#       define HW_PLATFORM_WP
#   endif

/* Microsoft Winodws 定義 */
#   define HW_PLATFORM_WINDOWS

/* 32bit or 64bit 定義 */
#   if defined(_WIN64)
#       define HW_PLATFORM_64BIT
#       define HW_PLATFORM_MSVC64
#   else
#       define HW_PLATFORM_32BIT
#       define HW_PLATFORM_MSVC32
#   endif


/* 他環境を考えるとVC専用関数は多用できないのでセキュア関数関連の警告を無視する */
#   pragma warning(disable:4996)

/* GCC環境定義 */
#elif defined(__GNUC__)

/* GCC定義 */
#   define HW_PLATFORM_GCC

/* 32bit or 64bit 定義 */
#   if defined(__i386__)
#       define HW_PLATFORM_32BIT
#       define HW_PLATFORM_GCC32
#   else
#       define HW_PLATFORM_64BIT
#       define HW_PLATFORM_GCC64
#   endif
#endif	/* defined(__GNUC__) */

/* コンパイルターゲット定義 */
/* デバッグコンパイルでなく、HW_RELEASE設定でなければHW_PROFILE設定にしておく */
/* HW_RELEASE設定はユーザーが明示的に行うこと */
#if defined(_DEBUG)
#   define HW_DEBUG
#elif !defined(HW_RELEASE)
#   define HW_PROFILE
#endif

#endif  /* HW_PLATFORM_H_ */

