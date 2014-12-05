#include "hwg.h"
#include <hw/types.h>
#include <hw/error.h>
#include <hw/debug/assert.h>
#include "hwg/dx.h"

typedef struct hwg_context_t {
    hwg_parameter_t         param;
    D3D_DRIVER_TYPE         driver_type;
    D3D_FEATURE_LEVEL       feature_level;
    IDXGISwapChain*         swap_chain;
    ID3D11Device*           device;
    ID3D11DeviceContext*    device_context;
    ID3D11RenderTargetView* render_target;
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

    D3D_FEATURE_LEVEL feature_levels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT feature_level_num = sizeof(feature_levels) / sizeof(feature_levels[0]);

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

    for(i = 0; i < driver_type_num; ++i) {
        D3D_DRIVER_TYPE      driver_type    = driver_types[i];
        IDXGISwapChain*      swap_chain     = NULL;
        D3D_FEATURE_LEVEL    feature_level  = D3D_FEATURE_LEVEL_11_0;
        ID3D11Device*        device         = NULL;
        ID3D11DeviceContext* device_context = NULL;

        result = D3D11CreateDeviceAndSwapChain(
                NULL, 
                driver_type, 
                NULL,
                device_flag,
                feature_levels,
                feature_level_num, 
                D3D11_SDK_VERSION, 
                &sd,
                &swap_chain,
                &device,
                &feature_level,
                &device_context
                );

        if(SUCCEEDED(result)) {
            g_context.driver_type    = driver_type;
            g_context.swap_chain     = swap_chain;
            g_context.feature_level  = feature_level;
            g_context.device         = device;
            g_context.device_context = device_context;
            break;
        }
    }

    if(FAILED(result)) {
        HW_ASSERT(0);
    }

    {
        ID3D11Texture2D*        back_buffer   = NULL;
        ID3D11RenderTargetView* render_target = NULL;

        result = IDXGISwapChain_GetBuffer(g_context.swap_chain, 0, &IID_ID3D11Texture2D, (LPVOID*)&back_buffer);
        if(FAILED(result)) {
            HW_ASSERT(0);
            return result;
        }

        //result = g_context.device->CreateRenderTargetView(back_buffer, NULL, &render_target);
        result = ID3D11Device_CreateRenderTargetView(g_context.device, (ID3D11Resource*)back_buffer, NULL, &render_target);
        ID3D11Texture2D_Release(back_buffer);
        if(FAILED(result)) {
            HW_ASSERT(0);
            return result;
        }

        ID3D11DeviceContext_OMSetRenderTargets(g_context.device_context, 1, &render_target, NULL);
        //g_context.device_context.OMSetRenderTargets(1, &render_target, NULL);
        g_context.render_target = render_target;
    }

    {
        D3D11_VIEWPORT vp;
        vp.Width    = (float)param->frame_width;
        vp.Height   = (float)param->frame_height;
        vp.MinDepth = 0.0f;
        vp.MaxDepth = 1.0f;
        vp.TopLeftX = 0;
        vp.TopLeftY = 0;
        //g_context.device_context->RSSetViewports(1, &vp);
        ID3D11DeviceContext_RSSetViewports(g_context.device_context, 1, &vp);
    }

    return HW_TRUE;
}

hwbool hwg_finalize()
{
    return HW_TRUE;
}

