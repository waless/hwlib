#include "hw/memory/unit_heap.h"
#include <string.h>
#include "hw/memory/internal/unit_memory.h"
#include "hw/debug/assert.h"

void hw_unit_heap_initialize(hw_unit_heap_t* heap, void* memory, hw32 unit_size, hw32 unit_num)
{
    HW_NULL_ASSERT(heap);

    /* メモリをブロックに分けてリンク */
    hwL_unit_memory_initialize(memory, unit_size, unit_num, NULL);

    /* 要素を記憶 */
    heap->head			   = memory;
	heap->unit_size		   = unit_size;
	heap->total_unit_num   = unit_num;
	heap->current_unit_num = 0;
}

void hw_unit_heap_finalize(hw_unit_heap_t* heap)
{
    HW_NULL_ASSERT(heap);
    memset(heap, 0, sizeof(*heap));
}

void* hw_unit_heap_allocate(hw_unit_heap_t* heap)
{
	void* memory = NULL;
	
    HW_NULL_ASSERT(heap);
	
    memory = hwL_unit_memory_pop(heap->head, &heap->head);
	if(memory != NULL) {
		--heap->current_unit_num;
		HW_ASSERT_MESSAGE(heap->current_unit_num >= 0, "ヒープが空にもかかわらずメモリが確保されました");
	}

	return memory;
}

void hw_unit_heap_deallocate(hw_unit_heap_t* heap, void* memory)
{
    HW_NULL_ASSERT(heap);
    HW_NULL_ASSERT(memory);
	
    hwL_unit_memory_push(heap->head, memory, &heap->head);
	++heap->current_unit_num;

	HW_ASSERT_MESSAGE(heap->current_unit_num <= heap->total_unit_num, "ヒープの最大ブロック数を超えてメモリが返却されました");
}

void* hw_unit_heap_get_memory(hw_unit_heap_t* heap)
{
	HW_NULL_ASSERT(heap);
	return heap->memory;
}

hw32 hw_unit_heap_get_unit_size(hw_unit_heap_t* heap)
{
	HW_NULL_ASSERT(heap);
	return heap->unit_size;
}

hwbool hw_unit_heap_empty(hw_unit_heap_t* heap)
{
    HW_NULL_ASSERT(heap);
    return hwL_unit_memory_empty(heap->head);
}

hwbool hw_unit_heap_full(hw_unit_heap_t* heap)
{
	HW_NULL_ASSERT(heap);
	HW_ASSERT_MESSAGE(heap->current_unit_num > heap->total_unit_num, "");
	return heap->current_unit_num == heap->total_unit_num;
}

