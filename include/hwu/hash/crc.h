#ifndef HWU_HASH_CRC_
#define HWU_HASH_CRC_

#include <stddef.h>
#include "hwu/types.h"

extern hws16 hwu_hash_crc16(const void* data, size_t size);
extern hws32 hwu_hash_crc32(const void* data, size_t size);

#endif /* end of include guard */

