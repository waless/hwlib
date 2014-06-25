#ifndef HWFW_WIN_ENVIRONMENT_H_
#define HWFW_WIN_ENVIRONMENT_H_

#include <hw/platform.h>

#if defined(HW_PLATFORM_WINDOWS)

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hwfw_config_t {
    int left;
    int top;
    int width;
    int height;
} hwfw_config_t;

typedef struct hwfw_environment_t {
    HINSTANCE hinstance;
    HWND      hwnd;
} hwfw_environment_t;

#ifdef __cplusplus
}
#endif

#endif

#endif

