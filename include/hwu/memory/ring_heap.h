#ifndef HWU_MEMORY_RING_HEAP_H_
#define HWU_MEMORY_RING_HEAP_H

#include "hwu/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hwu_ring_heap_t
{
	void*		memory;
	hwu32	    heap_size;
	hwu32       allocated_size;
	hwuptr_t	current_address;
} hwu_ring_heap_t;

typedef hwuptr_t hwu_ring_heap_marker_t;

extern void hwu_ring_heap_initialize(hwu_ring_heap_t* heap, void* memory, hwu32 size);
extern void* hwu_ring_heap_allocate(hwu_ring_heap_t* heap, hwu32 size, hwu32 alignment);
extern void hwu_ring_heap_reset_allocated_size(hwu_ring_heap_t* heap);

#ifdef __cplusplus
}
#endif

#endif	/* HWU_MEMORY_RING_HEAP_H */

