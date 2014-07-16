#include "hw/error.h"
#include <string.h>
#include "hw/debug/assert.h"

static hw_error_t g_stack[HW_ERROR_DEPTH];
static int        g_stack_top     = 0;
static int        g_frame_counter = 0;

static void clear(hw_error_t* error);

void hw_error_update()
{
    g_frame_counter += 1;
}

void hw_error_push(int kind, const char* message, const char* file, const char* func, int line)
{
    HW_ASSERT(g_stack_top < HW_ERROR_DEPTH);

    if(g_stack_top < HW_ERROR_DEPTH) {
        hw_error_t* target = g_stack + g_stack_top;
        target->kind  = kind;
        target->file  = file;
        target->func  = func;
        target->line  = line;
        target->frame = g_frame_counter;

        if(message != NULL) {
            strncpy(target->message, message, sizeof(target->message));
        }
        g_stack_top += 1;
    }
}

const hw_error_t* hw_error_get(int depth)
{
    if(depth >= 0 && depth < g_stack_top) {
        return g_stack + depth;
    }
    else {
        return NULL;
    }
}

const hw_error_t* hw_error_pop()
{
    const hw_error_t* result = hw_error_peek();

    if(result != NULL) {
        g_stack_top -= 1;
    }

    return result;
}

const hw_error_t* hw_error_peek()
{
    hw_error_t* result = NULL;

    if(g_stack_top > 0) {
        result = g_stack + g_stack_top - 1;
    }

    return result;
}

void hw_error_clear()
{
    int i;

    for(i = 0; i < HW_ERROR_DEPTH; ++i) {
        clear(g_stack + i);
    }
    g_stack_top = 0;
}

int hw_error_get_depth()
{
    return g_stack_top;
}

int hw_error_get_current_frame()
{
    return g_frame_counter;
}

void clear(hw_error_t* error)
{
    error->kind = HW_ERROR_SUCCESS;
    error->file = "";
    error->func = "";
    error->line = 0;

    memset(error->message, 0, sizeof(error->message));
}

