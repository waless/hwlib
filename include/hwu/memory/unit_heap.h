#ifndef HWU_MEMORY_UNIT_HEAP_H_
#define HWU_MEMORY_UNIT_HEAP_H_

#include "hwu/types.h"

typedef struct tag_hwu_unit_heap_t
{
	void* head;
	void* memory;
	int   unit_size;
	int   total_unit_num;
	int   current_unit_num;
} hwu_unit_heap_t;

extern void hwu_unit_heap_initialize(hwu_unit_heap_t* heap, void* memory, int unit_size, int unit_num);
extern void hwu_unit_heap_finalize(hwu_unit_heap_t* heap);
extern void* hwu_unit_heap_allocate(hwu_unit_heap_t* heap);
extern void hwu_unit_heap_deallocate(hwu_unit_heap_t* heap, void* memory);
extern void* hwu_unit_heap_get_memory(hwu_unit_heap_t* heap);
extern int hwu_unit_heap_get_unit_size(hwu_unit_heap_t* heap);
extern BOOL hwu_unit_heap_empty(hwu_unit_heap_t* heap);
extern BOOL hwu_unit_heap_full(hwu_unit_heap_t* heap);

#endif  /* HWU_MEMORY_UNIT_HEAP_H_ */
