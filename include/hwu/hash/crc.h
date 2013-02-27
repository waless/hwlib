#ifndef HWU_HASH_CRC_
#define HWU_HASH_CRC_

#include <stddef.h>
#include "hwu/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern hws16 hwu_hash_crc16(const void* data, size_t size);
extern hws32 hwu_hash_crc32(const void* data, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard */

