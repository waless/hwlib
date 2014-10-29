#ifndef HWG_DX_H_
#define HWG_DX_H_

#include "hwg/config.h"

#if defined(HWG_CONFIG_DX_11) || defined(HWG_CONFIG_DX_11_WP)
#   define CINTERFACE
#   include <d3d11.h>
#endif

#endif

