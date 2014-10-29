#include "hwg.h"
#include <hw/types.h>
#include <hw/error.h>
#include "hwg/dx.h"

typedef struct hwg_context_t {
    hwg_parameter_t    param;
    D3D_DRIVER_TYPE    driver_type;
    D3D_FEATURE_LEVEL  feature_level;
    IDXGISwapChain*    swap_chain;
    ID3DDeviceContext* device_context;
    ID3D11Texture2D*   back_buffer;
} hwg_context_t;

static hwg_context_t g_context;

hwbool hwg_initialize(const hwg_parameter_t* param)
{
    HRESULT result = S_OK;
    RECT rc;
    UINT device_flag = 0;
    DXGI_SWAP_CHAIN_DESC sd;
    UINT i;

    D3D_DRIVER_TYPE driver_types[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT driver_type_num = sizeof(driver_types) / sizeof(driver_types[0]);

    D3D_FEATURE_LEVEL levels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT level_num = sizeof(levels) / sizeof(levels[0]);

    HW_ASSERT(param->hwnd != NULL);

    device_flag |= D3D11_CREATE_DEVICE_DEBUG;

    memset(&sd, 0, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = param->frame_width;
    sd.BufferDesc.Height = param->frame_height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = param->frame_rate;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = param->hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = param->is_windowed;

    for(i = 0; i < type_num; ++i) {
        D3D_DRIVER_TYPE      driver_type    = driver_types[i];
        IDXGISwapChain*      swap_chain     = NULL;
        D3D_FEATURE_LEVEL    feature_level  = D3D_FEATURE_LEVEL_11_0;
        ID3D11DeviceContext* device_context = NULL;

        result = D3D11CreateDeviceAndSwapChain(
                NULL, 
                type, 
                NULL,
                device_flag,
                feature_levels,
                feature_level_num, 
                D3D11_SDK_VERSION, 
                &sd,
                &swap_chain,
                &feature_level,
                &device_context
                );

        if(SUCCEEDED(result)) {
            g_context.dirver_type    = driver_type;
            g_context.swap_chain     = swap_chain;
            g_context.feature_level  = feature_level;
            g_context.device_context = device_context;
            break;
        }
    }

    if(FAILED(result)) {
        HW_ASSERT(0);
    }
}

hwbool hwg_finalize()
{
}

