#ifndef HW_MEMORY_SMALL_OBJECT_HEAP_H_
#define HW_MEMORY_SMALL_OBJECT_HEAP_H

#include "hw/types.h"
#include "hw/memory/allocator.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hw_small_object_heap_t
{
	void*						heaps;
	hwu32						max_unit_size;
	hwu32					    split_unit_size;
	hwu32                       unit_heap_size;
	hw_allocator_aligned_t		allocator;
	hw_deallocator_aligned_t	deallocator;
} hw_small_object_heap_t;

extern void hw_small_object_heap_initialize(hw_small_object_heap_t* heap, hw_allocator_aligned_t allocator, hw_deallocator_aligned_t deallocator, hwu32 max_unit_size, hwu32 split_unit_size, hwu32 unit_heap_size);
extern void* hw_small_object_heap_allocate(hw_small_object_heap_t* heap, hwu32 size, hwu32 alignment);
extern void hw_small_object_heap_deallocate(hw_small_object_heap_t* heap, void* memory);
extern hwbool hw_small_object_heap_is_in_heap(hw_small_object_heap_t* heap, void* memory);

#ifdef __cplusplus
}
#endif

#endif	/* HW_MEMORY_SMALL_OBJECT_HEAP_H */
