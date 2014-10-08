#ifndef HWG_TEXTURE_OPERATOR_H_
#define HWG_TEXTURE_OPERATOR_H_

#include "hwg/config.h"

#if defined(HWG_CONFIG_DX)
#   include "hwg/texture/dx/operator.h"
#elif defined(HWG_CONFIG_GL)
#   error /* not support */
/* #   include "hwg/texture/gl/operator.h" */
#else
#endif

#endif

