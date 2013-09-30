#ifndef HWG_GL_H_
#define HWG_GL_H_

#include <hw/platform.h>

#if defined(HW_PLATFORM_WINDOWS)
#   include <GLES2/gl2.h>
#   include <GLES2/gl2ext.h>
#elif defined(HW_PLATFORM_ANDROID)
#   include <GLES2/gl2.h>
#   include <GLES2/gl2ext.h>
#elif defined(HW_PLATFORM_IOS)
#   error
#endif

#endif

