#ifndef HWFW_INTERNAL_WIN_NATIVE_H_
#define HWFW_INTERNAL_WIN_NATIVE_H_

#include <hw/platform.h>
#include <hwfw.h>
#include <hwfw/environment.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(HW_PLATFORM_WINDOWS_DESKTOP)

extern hwbool native_initialize(const hwfw_callback_t* callback, const hwfw_config_t* config);
extern hwbool native_run();
extern const hwfw_config_t* native_get_config();
extern const hwfw_environment_t* native_get_environment();
extern void* native_get_user_data();

#endif

#ifdef __cplusplus
}
#endif

#endif

