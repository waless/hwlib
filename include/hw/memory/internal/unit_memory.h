#ifndef HW_MEMORY_INTERNAL_UNIT_MEMORY_H_
#define HW_MEMORY_INTERNAL_UNIT_MEMORY_H

#include "hw/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void  hwL_unit_memory_initialize(void* memory, hw32 unit_size, hw32 unit_num, void* append_unit_memory);
extern void* hwL_unit_memory_pop(void* head, void** new_head);
extern void  hwL_unit_memory_push(void* head, void* memory, void** new_head);
extern hwbool hwL_unit_memory_empty(void* head);
extern hw32 hwL_unit_memory_calculate_need_size(hw32 unit_size, hw32 unit_num);

#ifdef __cplusplus
}
#endif

#endif	/* HW_MEMORY_INTERNAL_UNIT_MEMORY_H */
