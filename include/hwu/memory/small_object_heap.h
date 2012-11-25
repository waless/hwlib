#ifndef HWU_MEMORY_SMALL_OBJECT_HEAP_H_
#define HWU_MEMORY_SMALL_OBJECT_HEAP_H

#include "hwu/types.h"
#include "hwu/memory/allocator.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hwu_small_object_heap_t
{
	void*						heaps;
	int							max_unit_size;
	int							split_unit_size;
	int                         unit_heap_size;
	hwu_allocator_aligned_t		allocator;
	hwu_deallocator_aligned_t	deallocator;
} hwu_small_object_heap_t;

extern void hwu_small_object_heap_initialize(hwu_small_object_heap_t* heap, hwu_allocator_aligned_t allocator, hwu_deallocator_aligned_t deallocator, int max_unit_size, int split_unit_size, int unit_heap_size);
extern void* hwu_small_object_heap_allocate(hwu_small_object_heap_t* heap, int size, int alignment);
extern void hwu_small_object_heap_deallocate(hwu_small_object_heap_t* heap, void* memory);
extern hwbool hwu_small_object_heap_is_in_heap(hwu_small_object_heap_t* heap, void* memory);

#ifdef __cplusplus
}
#endif

#endif	/* HWU_MEMORY_SMALL_OBJECT_HEAP_H */
