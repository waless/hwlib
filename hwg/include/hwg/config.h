#ifndef HWG_CONFIG_H_
#define HWG_CONFIG_H_

#include "hw/platform.h"

#if defined(HW_PLATFORM_WINDOWS_DESKTOP)
#   define HWG_CONFIG_DX_11
/* #   define HWG_CONFIG_GL_4_0 */
#elif defined(HW_PLATFORM_WINDOWS_PHONE)
#   define HWG_CONFIG_DX_11_WP
#elif defined(HW_PLATFORM_IOS) || defined(HW_PLATFORM_ANDROID)
/* #   define HWG_CONFIG_GL_ES_1_1 */
#   define HWG_CONFIG_GL_ES_2_0
/* #   define HWG_CONFIG_GL_ES_3_0 */
#endif

#if defined(HWG_CONFIG_DX_11) || defined(HWG_CONFIG_DX_11_WP)
#   define HWG_CONFIG_DX
#elif defined(HWG_CONFIG_GL_4_0) || defined(HWG_CONFIG_GL_ES_1_1) || defined(HWG_CONFIG_GL_ES_2_0) || defined(HWG_CONFIG_GL_ES_3_0)
#   define HWG_CONFIG_GL
#endif

#endif

