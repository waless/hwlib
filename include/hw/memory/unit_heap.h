#ifndef HW_MEMORY_UNIT_HEAP_H_
#define HW_MEMORY_UNIT_HEAP_H_

#include "hw/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hw_unit_heap_t
{
	void* head;
	void* memory;
	hw32 unit_size;
	hw32 total_unit_num;
	hw32 current_unit_num;
} hw_unit_heap_t;

extern void hw_unit_heap_initialize(hw_unit_heap_t* heap, void* memory, hw32 unit_size, hw32 unit_num);
extern void hw_unit_heap_finalize(hw_unit_heap_t* heap);
extern void* hw_unit_heap_allocate(hw_unit_heap_t* heap);
extern void hw_unit_heap_deallocate(hw_unit_heap_t* heap, void* memory);
extern void* hw_unit_heap_get_memory(hw_unit_heap_t* heap);
extern hw32 hw_unit_heap_get_unit_size(hw_unit_heap_t* heap);
extern hwbool hw_unit_heap_empty(hw_unit_heap_t* heap);
extern hwbool hw_unit_heap_full(hw_unit_heap_t* heap);

#ifdef __cplusplus
}
#endif

#endif  /* HW_MEMORY_UNIT_HEAP_H_ */
