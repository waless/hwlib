#ifndef HW_ERROR_H_
#define HW_ERROR_H_

#include "hw/platform.h"

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
    const char* file;
    int         line;
} hw_error_t;

extern void hw_set_error(int kind, const char* file, int line);
extern const hw_error_t* hw_get_error();

#if !defined(HW_RELEASE)
#   define HW_ERROR_SET(kind) hw_set_error(kind, __FILE__, __LINE__)
#else
#   define HW_ERROR_SET(kind) hw_set_error(kind, NULL, 0)
#endif

#ifdef __cplusplus
}
#endif

#endif

