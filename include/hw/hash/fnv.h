#ifndef HW_HASH_FNV_
#define HW_HASH_FNV_

#include <stddef.h>
#include "hw/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern hw32 hw_hash_fnv(const void* data, hw32 size);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard */

