#ifndef HW_ERROR_H_
#define HW_ERROR_H_

#include "hw/platform.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum hw_error_kind_t {
    HW_ERROR_SUCCESS = 0,
    HW_ERROR_NULL_POINTER,
    HW_ERROR_INDEX_OUT_OF_RANGE,
} hw_error_kind_t;

typedef struct hw_error_t {
    int         kind;
    const char* message;
    const char* file;
    const char* func;
    int         line;
} hw_error_t;

extern void hw_set_error(int kind, const char* message, const char* file, const char* func, int line);
extern const hw_error_t* hw_get_error();

#if !defined(HW_RELEASE)
#   define HW_ERROR(kind)              hw_set_error(kind, "", __FILE__, __func__, __LINE__)
#   define HW_ERROR_MSG(kind, message) hw_set_error(kind, message, __FILE__, __func__, __LINE__);
#else
#   define HW_ERROR(kind)              hw_set_error(kind, "", "", "", 0)
#   define HW_ERROR_MSG(kind, message) hw_set_error(kind, "", "", "", 0)
#endif

#ifdef __cplusplus
}
#endif

#endif

