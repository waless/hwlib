#ifndef HWG_DX_H_
#define HWG_DX_H_

#include "hwg/config.h"

#if defined(HWG_CONFIG_DX_11) || defined(HWG_CONFIG_DX_11_WP)
#   define CINTERFACE
#   define COBJMACROS
#   pragma warning(push)
#   pragma warning(disable:4201) /* C非標準である警告の抑制 */
#       include <dxgi.h>
#       include <d3d11.h>
#   pragma warning(pop)
#endif

#endif

