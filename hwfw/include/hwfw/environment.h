#ifndef HWFW_ENVIRONMENT_H_
#define HWFW_ENVIRONMENT_H_

#include <hw/platform.h>

#if defined(HW_PLATFORM_WINDOWS_DESKTOP)
#   include "hwfw/win/environment.h"
#elif defined(HW_PLATFORM_WINDOWS_PHONE)
#   error /* not support */
#elif defined(HW_PLATFORM_IOS)
#   error /* not support */
#elif defined(HW_PLATFORM_ANDROID)
#   error /* not support */
#endif

#endif

