#ifndef HWG_DX_H_
#define HWG_DX_H_

#include "hwg/config.h"

#if !defined(__cplusplus)
#   error /* this header cpp only */
#endif

#if defined(HWG_CONFIG_DX_11)
#   include <d3d11.h>
#elif defined(HWG_CONFIG_DX_11_WP)
#   include <d3d11.h>
#endif

#endif

