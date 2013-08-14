#include "hw/error.h"

static hw_error_t error =
{
    HW_ERROR_SUCCESS,
    "",
    "",
    "",
    0,
};

void hw_set_error(int kind, const char* message, const char* file, const char* func, int line)
{
    error.kind    = kind;
    error.message = message;
    error.file    = file;
    error.func    = func;
    error.line    = line;
}

const hw_error_t* hw_get_error()
{
    return &error;
}

