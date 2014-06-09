#ifndef HW_MEMORY_RING_HEAP_H_
#define HW_MEMORY_RING_HEAP_H

#include "hw/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hw_ring_heap_t
{
	void*	 memory;
	hwu32	 heap_size;
	hwu32    allocated_size;
	hwuptr_t current_address;
} hw_ring_heap_t;

typedef hwuptr_t hw_ring_heap_marker_t;

extern void hw_ring_heap_initialize(hw_ring_heap_t* heap, void* memory, hwu32 size);
extern void* hw_ring_heap_allocate(hw_ring_heap_t* heap, hwu32 size, hwu32 alignment);
extern void hw_ring_heap_reset_allocated_size(hw_ring_heap_t* heap);

#ifdef __cplusplus
}
#endif

#endif	/* HW_MEMORY_RING_HEAP_H */

