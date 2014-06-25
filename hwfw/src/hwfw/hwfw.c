#include "hwfw.h"

#if defined(HW_PLATFORM_WINDOWS)
#   include "internal/win/native.h"
#elif defined(HW_PLATFORM_WP8)
#   error /* not support */
#elif defined(HW_PLATFORM_IOS)	
#   error /* not support */
#elif defined(HW_PLATFORM_ANDROID)
#   error /* not support */
#endif

void hwfw_initialize(const hwfw_callback_t* callback, const hwfw_config_t* config)
{
    native_initialize(callback, config);
}

void hwfw_run()
{
    native_run();
}

const hwfw_config_t* hwfw_get_config()
{
    return native_get_config();
}

const hwfw_environment_t* hwfw_get_native_environment()
{
    return native_get_environment();
}

void* hwfw_get_user_data()
{
    return native_get_user_data();
}

