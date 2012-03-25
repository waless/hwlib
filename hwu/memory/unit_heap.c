#include "hwu/memory/unit_heap.h"
#include <string.h>
#include "hwu/memory/internal/unit_memory.h"
#include "hwu/debug/assert.h"

void hwu_unit_heap_initialize(hwu_unit_heap_t* heap, void* memory, int unit_size, int unit_num)
{
    HWU_NULL_ASSERT(heap);

    /* メモリをブロックに分けてリンク */
    hwuL_unit_memory_initialize(memory, unit_size, unit_num, NULL);

    /* 要素を記憶 */
    heap->head			   = memory;
	heap->unit_size		   = unit_size;
	heap->total_unit_num   = unit_num;
	heap->current_unit_num = 0;
}

void hwu_unit_heap_finalize(hwu_unit_heap_t* heap)
{
    HWU_NULL_ASSERT(heap);
    memset(heap, 0, sizeof(*heap));
}

void* hwu_unit_heap_allocate(hwu_unit_heap_t* heap)
{
	void* memory = NULL;
	
    HWU_NULL_ASSERT(heap);
	
    memory = hwuL_unit_memory_pop(heap->head, &heap->head);
	if(memory != NULL) {
		--heap->current_unit_num;
		HWU_ASSERT_MESSAGE(heap->current_unit_num >= 0, "ヒープが空にもかかわらずメモリが確保されました");
	}

	return memory;
}

void hwu_unit_heap_deallocate(hwu_unit_heap_t* heap, void* memory)
{
    HWU_NULL_ASSERT(heap);
    HWU_NULL_ASSERT(memory);
	
    hwuL_unit_memory_push(heap->head, memory, &heap->head);
	++heap->current_unit_num;

	HWU_ASSERT_MESSAGE(heap->current_unit_num <= heap->total_unit_num, "ヒープの最大ブロック数を超えてメモリが返却されました");
}

void* hwu_unit_heap_get_memory(hwu_unit_heap_t* heap)
{
	HWU_NULL_ASSERT(heap);
	return heap->memory;
}

int hwu_unit_heap_get_unit_size(hwu_unit_heap_t* heap)
{
	HWU_NULL_ASSERT(heap);
	return heap->unit_size;
}

BOOL hwu_unit_heap_empty(hwu_unit_heap_t* heap)
{
    HWU_NULL_ASSERT(heap);
    return hwuL_unit_memory_empty(heap->head);
}

BOOL hwu_unit_heap_full(hwu_unit_heap_t* heap)
{
	HWU_NULL_ASSERT(heap);
	HWU_ASSERT_MESSAGE(heap->current_unit_num > heap->total_unit_num, "保持ブロック数がヒープの最大ブロック数を超えています");
	return heap->current_unit_num == heap->total_unit_num;
}

