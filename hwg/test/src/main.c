#include <hwfw.h>

static void on_initialize(void* p);
static void on_finalize(void* p);
static void on_run(void* p);
static void on_suspend(void* p);
static void on_resume(void* p);

int main(int argc, char* argv[])
{
    hwfw_callback_t app_callback;
    hwfw_config_t   app_config;

    (void)argc;
    (void)argv;

    app_callback.initializer = on_initialize;
    app_callback.finalizer   = on_finalize;
    app_callback.runner      = on_run;
    app_callback.suspender   = on_suspend;
    app_callback.resumer     = on_resume;

    app_config.title  = TEXT("hwg_test");
    app_config.left   = 0;
    app_config.top    = 0;
    app_config.width  = 640;
    app_config.height = 480;

    hwfw_initialize(&app_callback, &app_config);
    hwfw_run();

    return 0;
}

void on_initialize(void* p)
{
}

void on_finalize(void* p)
{
}

void on_run(void* p)
{
}

void on_suspend(void* p)
{
}

void on_resume(void* p)
{
}

