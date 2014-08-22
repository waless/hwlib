#ifndef HWFW_H_
#define HWFW_H_

#include "hw/types.h"
#include "hwfw/error.h"
#include "hwfw/environment.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*hwfw_initialize_t)(void* user_data);
typedef void (*hwfw_finalize_t)(void* user_data);
typedef void (*hwfw_run_t)(void* user_data);
typedef void (*hwfw_suspend_t)(void* user_data);
typedef void (*hwfw_resume_t)(void* user_data);

typedef struct hwfw_callback_t {
    hwfw_initialize_t initializer;
    hwfw_finalize_t   finalizer;
    hwfw_run_t        runner;
    hwfw_suspend_t    suspender;
    hwfw_resume_t     resumer;
    void*             user_data;
} hwfw_callback_t;

extern hwbool hwfw_initialize(const hwfw_callback_t* callback, const hwfw_config_t* config);
extern hwbool hwfw_run();

extern const hwfw_config_t* hwfw_get_config();
extern const hwfw_environment_t* hwfw_get_native_environment();
extern void* hwfw_get_user_data();

#ifdef __cplusplus
}
#endif

#endif

