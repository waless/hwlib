#include "internal/win/native.h"

#if defined(HW_PLATFORM_WINDOWS)

static LRESULT WINAPI window_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);
static void on_paint();

static void callback_clear(hwfw_callback_t* callback);
static void config_clear(hwfw_config_t* config);
static void environment_clear(hwfw_environment_t* environment);

static hwfw_callback_t    g_callback;
static hwfw_config_t      g_config;
static hwfw_environment_t g_environment;

void native_initialize(const hwfw_config_t* config)
{
    WNDCLASS  wc;
    RECT      wrect;
    DWORD     wstyle    = 0;
    HINSTANCE hinstance = NULL;
    HWND      hwnd      = NULL;
    
    callback_clear(&g_callback);
    config_clear(&g_config);
    environment_clear(&g_environment);

    hinstance = GetModuleHandle(NULL);
    if(hinstance == NULL) {
    }

    memset(&wc, 0, sizeof(wc));
    wc.style         = CS_OWDC;
    wc.lpfnWndProc   = (WNDPROC)window_proc;
    wc.hInstance     = hinstance;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszClassName = "HWFW_WINDOW_CLASS";

    if(RegisterClass(&wc) == FALSE) {
    }

    wstyle = WS_OVERLAPPEDWINDOW;

    wrect.left   = config->left;
    wrect.top    = config->top;
    wrect.right  = wrect.left + config->width;
    wrect.bottom = wrect.top  + config->height;
    AdjustWindowRect(&wrect, wstyle, FALSE);

    hwnd = CreateWindow(config->title, 
                        config->title,
                        wstyle,
                        200,
                        200,
                        config->width,
                        config->height,
                        NULL,
                        NULL,
                        hinstance,
                        NULL);

    if(hwnd == NULL) {
    }

    g_environment.hinstance = hinstance;
    g_environment.hwnd      = hwnd;
}

void native_run(hwfw_callback_t* callback)
{
    MSG msg;

    if(callback->initializer != NULL) {
        callback->initializer(g_callback.user_data);
    }

    ShowWindow((HWND)g_environment.hwnd, TRUE);

    while(1) {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if(msg.message == WM_QUIT) {
                break;
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else {
            if(g_callback.runner != NULL) {
                g_callback.runner(g_callback.user_data);
            }
        }
    }

    if(g_callback.finalizer != NULL) {
        g_callback.finalizer(g_callback.user_data);
    }
}

const hwfw_config_t* native_get_config()
{
    return &g_config;
}

const hwfw_environment_t* native_get_environment()
{
    return &g_environment;
}

void* hwfw_get_user_data()
{
    return g_callback.user_data;
}

LRESULT WINAPI window_proc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
    switch(umsg)
    {
    case WM_PAINT:
        on_paint();
        break;

    default:
        return DefWindowProc(hwnd, umsg, wparam, lparam);
    }

    return 0;
}

void on_paint()
{
    if(g_callback.runner != NULL) {
        g_callback.runner(g_callback.user_data);
    }
}

void callback_clear(hwfw_callback_t* callback)
{
    callback->initializer = NULL;
    callback->finalizer   = NULL;
    callback->runner      = NULL;
    callback->suspender   = NULL;
    callback->resumer     = NULL;
    callback->user_data   = NULL;
}

void config_clear(hwfw_config_t* config)
{
    config->left   = 0;
    config->top    = 0;
    config->width  = 0;
    config->height = 0;
}

void environment_clear(hwfw_environment_t* environment)
{
    environment->hinstance = NULL;
    environment->hwnd      = NULL;
}

#endif

