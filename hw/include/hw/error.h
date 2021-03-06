﻿#ifndef HW_ERROR_H_
#define HW_ERROR_H_

#include "hw/platform.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "hw/platform.h"
#include "hw/config.h"

typedef enum hw_error_kind_t {
    HW_ERROR_SUCCESS = 0,
    HW_ERROR_NULL_POINTER,
    HW_ERROR_INDEX_OUT_OF_RANGE,
} hw_error_kind_t;

typedef struct hw_error_t {
    int         kind;
    char        message[HW_ERROR_MESSAGE_LENGTH_MAX];
    const char* file;
    const char* func;
    int         line;
    int         frame;
} hw_error_t;

extern void hw_error_update();
extern void hw_error_push(int kind, const char* message, const char* file, int line);
extern const hw_error_t* hw_error_get(int depth);
extern const hw_error_t* hw_error_pop();
extern const hw_error_t* hw_error_peek();
extern void hw_error_clear();
extern int hw_errr_get_depth();
extern int hw_error_current_frame();

#define HW_ERROR(kind) hw_error_push(kind, "", __FILE__, __LINE__);
#define HW_ERROR_MESSAGE(kind, message) hw_error_push(kind, message, __FILE__, __LINE__);

#ifdef __cplusplus
}
#endif

#endif

