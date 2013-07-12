#ifndef HWU_HASH_FNV_
#define HWU_HASH_FNV_

#include <stddef.h>
#include "hwu/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern hwu32 hwu_hash_fnv(const void* data, hwu32 size);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard */

