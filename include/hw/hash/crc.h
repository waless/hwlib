#ifndef HW_HASH_CRC_
#define HW_HASH_CRC_

#include <stddef.h>
#include "hw/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern hw16 hw_hash_crc16(hw16 init, const void* data, hw32 size);
extern hw32 hw_hash_crc32(hw32 init, const void* data, hw32 size);

#ifdef __cplusplus
}
#endif

#endif /* end of include guard */

