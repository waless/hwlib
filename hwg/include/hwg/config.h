#ifndef HWG_CONFIG_H_
#define HWG_CONFIG_H_

#include "hw/platform.h"

#if defined(HW_PLATFORM_WINDOWS)
#   define HWG_CONFIG_DX_11
/* #   define HWG_CONFIG_GL_4_0 */
#elif defined(HW_PLATFORM_WP8)
#   define HWG_CONFIG_DX_11_WP
#elif defined(HW_PLATFORM_IOS) || defined(HW_PLATFORM_ANDROID)
/* #   define HWG_CONFIG_GL_ES_1_1 */
#   define HWG_CONFIG_GL_ES_2_0
/* #   define HWG_CONFIG_GL_ES_3_0 */
#endif

#endif

