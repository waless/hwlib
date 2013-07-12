#ifndef HWU_MEMORY_UNIT_HEAP_H_
#define HWU_MEMORY_UNIT_HEAP_H_

#include "hwu/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hwu_unit_heap_t
{
	void* head;
	void* memory;
	hwu32 unit_size;
	hwu32 total_unit_num;
	hwu32 current_unit_num;
} hwu_unit_heap_t;

extern void hwu_unit_heap_initialize(hwu_unit_heap_t* heap, void* memory, hwu32 unit_size, hwu32 unit_num);
extern void hwu_unit_heap_finalize(hwu_unit_heap_t* heap);
extern void* hwu_unit_heap_allocate(hwu_unit_heap_t* heap);
extern void hwu_unit_heap_deallocate(hwu_unit_heap_t* heap, void* memory);
extern void* hwu_unit_heap_get_memory(hwu_unit_heap_t* heap);
extern hwu32 hwu_unit_heap_get_unit_size(hwu_unit_heap_t* heap);
extern hwbool hwu_unit_heap_empty(hwu_unit_heap_t* heap);
extern hwbool hwu_unit_heap_full(hwu_unit_heap_t* heap);

#ifdef __cplusplus
}
#endif

#endif  /* HWU_MEMORY_UNIT_HEAP_H_ */
