#include "hwfw.h"
#include <hw/debug/assert.h>

static void on_initialize(void* p);
static void on_finalize(void* p);
static void on_run(void* p);
static void on_suspend(void* p);
static void on_resume(void* p);

int main(int argc, void** argv)
{
    hwfw_callback_t cb;
    hwfw_config_t config;

    (void)argc;
    (void)argv;

    cb.initializer = on_initialize;
    cb.finalizer   = on_finalize;
    cb.runner      = on_run;
    cb.suspender   = on_suspend;
    cb.resumer     = on_resume;
    cb.user_data   = 0;

    config.title  = TEXT("test");
    config.left   = 0;
    config.top    = 0;
    config.width  = 640;
    config.height = 480;

    hwfw_initialize(&cb, &config);
    hwfw_run();

    return 0;
}

void on_initialize(void* p)
{
    (void)p;
}

void on_finalize(void* p)
{
    (void)p;
}

void on_run(void* p)
{
    (void)p;
}

void on_suspend(void* p)
{
    (void)p;
}

void on_resume(void* p)
{
    (void)p;
}

