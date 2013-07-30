#include "hw/error.h"

static hw_error_t error =
{
    HW_ERROR_SUCCESS,
    NULL,
    0,
};

void hw_set_error(int kind, const char* file, int line)
{
    error.kind = kind;
    error.file = file;
    error.line = line;
}

const hw_error_t* hw_get_error()
{
    return &error;
}

