#ifndef HWU_MEMORY_INTERNAL_UNIT_MEMORY_H_
#define HWU_MEMORY_INTERNAL_UNIT_MEMORY_H

#include "hwu/types.h"

extern void  hwuL_unit_memory_initialize(void* memory, int unit_size, int unit_num, void* append_unit_memory);
extern void* hwuL_unit_memory_pop(void* head, void** new_head);
extern void  hwuL_unit_memory_push(void* head, void* memory, void** new_head);
extern hwbool hwuL_unit_memory_empty(void* head);
extern int   hwuL_unit_memory_calculate_need_size(int unit_size, int unit_num);

#endif	/* HWU_MEMORY_INTERNAL_UNIT_MEMORY_H */
