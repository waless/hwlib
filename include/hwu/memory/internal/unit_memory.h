#ifndef HWU_MEMORY_INTERNAL_UNIT_MEMORY_H_
#define HWU_MEMORY_INTERNAL_UNIT_MEMORY_H

#include "hwu/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void  hwuL_unit_memory_initialize(void* memory, hwu32 unit_size, hwu32 unit_num, void* append_unit_memory);
extern void* hwuL_unit_memory_pop(void* head, void** new_head);
extern void  hwuL_unit_memory_push(void* head, void* memory, void** new_head);
extern hwbool hwuL_unit_memory_empty(void* head);
extern hwu32 hwuL_unit_memory_calculate_need_size(hwu32 unit_size, hwu32 unit_num);

#ifdef __cplusplus
}
#endif

#endif	/* HWU_MEMORY_INTERNAL_UNIT_MEMORY_H */
