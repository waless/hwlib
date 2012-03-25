#include "hwu/memory/stack_heap.h"
#include <string.h>
#include "hwu/utility.h"
#include "hwu/debug/assert.h"

static void* allocate_from_top(hwu_stack_heap_t* heap, int size, hwu32 alignment);
static void* allocate_from_bottom(hwu_stack_heap_t* heap, int size, hwu32 alignment);
static void	 deallocate_to_top(hwu_stack_heap_t* heap, hwu_stack_heap_maker_t maker);
static void	 deallocate_to_bottom(hwu_stack_heap_t* heap, hwu_stack_heap_maker_t maker);

void hwu_stack_heap_initialize(hwu_stack_heap_t* heap, void* memory, int size)
{
	HWU_NULL_ASSERT(heap);
	HWU_NULL_ASSERT(memory);
	HWU_ASSERT(size > 0);

	heap->memory_address = (hwuptr_t)memory;
	heap->top_address    = heap->memory_address + size;
	heap->bottom_address = heap->memory_address;
	heap->memory_size    = size;
}

void hwu_stack_heao_finalize(hwu_stack_heap_t* heap)
{
	HWU_NULL_ASSERT(heap);
	memset(heap, 0, sizeof(*heap));
}

void* hwu_stack_heap_allocate_ex(hwu_stack_heap_t* heap, int size, hwu32 alignment, hwu_stack_heap_direction_t direction)
{
	HWU_NULL_ASSERT(heap);
	return direction == HWU_STACK_HEAP_DIRECTION_TOP ? allocate_from_top(heap, size, alignment) : allocate_from_bottom(heap, size, alignment);
}

void hwu_stack_heap_deallocate_to_maker_ex(hwu_stack_heap_t* heap, hwu_stack_heap_maker_t maker, hwu_stack_heap_direction_t direction)
{
	HWU_NULL_ASSERT(heap);
	return direction == HWU_STACK_HEAP_DIRECTION_TOP ? deallocate_to_top(heap, maker) : deallocate_to_bottom(heap, maker);
}

hwu_stack_heap_maker_t hwu_stack_heap_get_maker_ex(hwu_stack_heap_t* heap, hwu_stack_heap_direction_t direction)
{
	HWU_NULL_ASSERT(heap);
	return direction == HWU_STACK_HEAP_DIRECTION_TOP ? heap->top_address : heap->bottom_address;
}

static void* allocate_from_top(hwu_stack_heap_t* heap, int size, hwu32 alignment)
{
	if(size > 0) {
		hwuptr_t address = HWU_ALIGNED_ROUND_UP(heap->top_address - size, alignment);
		if(address >= heap->bottom_address) {
			heap->top_address = address;
			return (void*)address;
		}
	}
	return NULL;
}

static void* allocate_from_bottom(hwu_stack_heap_t* heap, int size, hwu32 alignment)
{
	if(size > 0) {
		hwuptr_t address = HWU_ALIGNED_ROUND_UP(heap->bottom_address, alignment);
		hwuptr_t next_address = address + size;
		if(next_address <= heap->top_address) {
			heap->bottom_address = next_address;
			return (void*)address;
		}
	}
	return NULL;
}

static void deallocate_to_top(hwu_stack_heap_t* heap, hwu_stack_heap_maker_t maker)
{
	HWU_ASSERT(maker >= heap->memory_address && maker <= (heap->memory_address + heap->memory_size));
	HWU_ASSERT(maker >= heap->bottom_address);
	heap->top_address = maker;
}

static void deallocate_to_bottom(hwu_stack_heap_t* heap, hwu_stack_heap_maker_t maker)
{
	HWU_ASSERT(maker >= heap->memory_address && maker <= (heap->memory_address + heap->memory_size));
	HWU_ASSERT(maker <= heap->top_address);
	heap->bottom_address = maker;
}

