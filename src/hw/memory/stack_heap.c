#include "hw/memory/stack_heap.h"
#include <string.h>
#include "hw/utility.h"
#include "hw/debug/assert.h"

static void* allocate_from_top(hw_stack_heap_t* heap, hwu32 size, hwu32 alignment);
static void* allocate_from_bottom(hw_stack_heap_t* heap, hwu32 size, hwu32 alignment);
static void	 deallocate_to_top(hw_stack_heap_t* heap, hw_stack_heap_maker_t maker);
static void	 deallocate_to_bottom(hw_stack_heap_t* heap, hw_stack_heap_maker_t maker);

void hw_stack_heap_initialize(hw_stack_heap_t* heap, void* memory, hwu32 size)
{
	HW_NULL_ASSERT(heap);
	HW_NULL_ASSERT(memory);
	HW_ASSERT(size > 0);

	heap->memory_address = (hwptr_t)memory;
	heap->top_address    = heap->memory_address + size;
	heap->bottom_address = heap->memory_address;
	heap->memory_size    = size;
}

void hw_stack_heao_finalize(hw_stack_heap_t* heap)
{
	HW_NULL_ASSERT(heap);
	memset(heap, 0, sizeof(*heap));
}

void* hw_stack_heap_allocate_ex(hw_stack_heap_t* heap, hwu32 size, hwu32 alignment, hw_stack_heap_direction_t direction)
{
	HW_NULL_ASSERT(heap);
	return direction == HW_STACK_HEAP_DIRECTION_TOP ? allocate_from_top(heap, size, alignment) : allocate_from_bottom(heap, size, alignment);
}

void hw_stack_heap_deallocate_to_maker_ex(hw_stack_heap_t* heap, hw_stack_heap_maker_t maker, hw_stack_heap_direction_t direction)
{
	HW_NULL_ASSERT(heap);
	direction == HW_STACK_HEAP_DIRECTION_TOP ? deallocate_to_top(heap, maker) : deallocate_to_bottom(heap, maker);
}

hw_stack_heap_maker_t hw_stack_heap_get_maker_ex(hw_stack_heap_t* heap, hw_stack_heap_direction_t direction)
{
	HW_NULL_ASSERT(heap);
	return direction == HW_STACK_HEAP_DIRECTION_TOP ? heap->top_address : heap->bottom_address;
}

static void* allocate_from_top(hw_stack_heap_t* heap, hwu32 size, hwu32 alignment)
{
	if(size > 0) {
		hwptr_t address = HW_ALIGNED_ROUND_UP(heap->top_address - size, alignment);
		if(address >= heap->bottom_address) {
			heap->top_address = address;
			return (void*)address;
		}
	}
	return NULL;
}

static void* allocate_from_bottom(hw_stack_heap_t* heap, hwu32 size, hwu32 alignment)
{
	if(size > 0) {
		hwptr_t address = HW_ALIGNED_ROUND_UP(heap->bottom_address, alignment);
		hwptr_t next_address = address + size;
		if(next_address <= heap->top_address) {
			heap->bottom_address = next_address;
			return (void*)address;
		}
	}
	return NULL;
}

static void deallocate_to_top(hw_stack_heap_t* heap, hw_stack_heap_maker_t maker)
{
	HW_ASSERT(maker >= heap->memory_address && maker <= (heap->memory_address + heap->memory_size));
	HW_ASSERT(maker >= heap->bottom_address);
	heap->top_address = maker;
}

static void deallocate_to_bottom(hw_stack_heap_t* heap, hw_stack_heap_maker_t maker)
{
	HW_ASSERT(maker >= heap->memory_address && maker <= (heap->memory_address + heap->memory_size));
	HW_ASSERT(maker <= heap->top_address);
	heap->bottom_address = maker;
}

