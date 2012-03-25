#ifndef HWU_MEMORY_RING_HEAP_H_
#define HWU_MEMORY_RING_HEAP_H

#include "hwu/types.h"

typedef struct tag_hwu_ring_heap_t
{
	void*		memory;
	int			heap_size;
	int         allocated_size;
	hwuptr_t	current_address;
} hwu_ring_heap_t;

typedef hwuptr_t hwu_ring_heap_marker_t;

extern void hwu_ring_heap_initialize(hwu_ring_heap_t* heap, void* memory, int size);
extern void* hwu_ring_heap_allocate(hwu_ring_heap_t* heap, int size, int alignment);
extern void hwu_ring_heap_reset_allocated_size(hwu_ring_heap_t* heap);

#endif	/* HWU_MEMORY_RING_HEAP_H */

