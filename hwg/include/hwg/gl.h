#ifndef HWG_GL_H_
#define HWG_GL_H_

#include <hw/platform.h>
#include <hwg/config.h>

#if defined(HW_PLATFORM_WINDOWS)
#   if defined(HWG_CONFIG_GL_4_0)
#       error /* not support */
#   elif defined(HWG_CONFIG_GL_ES_1_1)
#       error /* not support */
#   elif defined(HWG_CONFIG_GL_ES_2_0)
#       include <GLES2/gl2.h>
#       include <GLES2/gl2ext.h>
#   elif defined(HWG_CONFIG_GL_ES_3_0)
#       error /* not support */
#   elif defined(HWG_CONFIG_MANTLE)
#       error /* not support */
#   endif
#elif defined(HW_PLATFORM_ANDROID)
#   if defined(HWG_CONFIG_GL_4_0)
#       error /* failed API */
#   elif defined(HWG_CONFIG_GL_ES_1_1)
#       error /* not support */
#   elif defined(HWG_CONFIG_GL_ES_2_0)
#       include <GLES2/gl2.h>
#       include <GLES2/gl2ext.h>
#   elif defined(HWG_CONFIG_GL_ES_3_0)
#       error /* not support */
#   elif defined(HWG_CONFIG_MANTLE)
#       error /* not support */
#   endif
#elif defined(HW_PLATFORM_IOS)
#   error
#endif

#endif

