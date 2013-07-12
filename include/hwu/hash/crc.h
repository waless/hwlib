#ifndef HWU_HASH_CRC_
#define HWU_HASH_CRC_

#include <stddef.h>
#include "hwu/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern hwu16 hwu_hash_crc16(hwu16 init, const void* data, hwu32 size);
extern hwu32 hwu_hash_crc32(hwu32 init, const void* data, hwu32 size);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard */

