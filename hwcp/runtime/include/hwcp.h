#ifndef HWCP_H_
#define HWCP_H_

#include <hw/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HWCP_NAME_MAX 64

typedef struct hwcp_reference_t {
    hwu32 count;
    hwu32 offsets[];
} hwcp_reference_t;

#ifdef __cplusplus
}
#endif

#endif

