#include "hw/memory/ring_heap.h"
#include "hw/utility.h"
#include "hw/debug/assert.h"

void hw_ring_heap_initialize(hw_ring_heap_t* heap, void* memory, hw32 size)
{
	HW_NULL_ASSERT(heap);
	HW_NULL_ASSERT(memory);
	HW_ASSERT(size > 0);

	/* パラメータを記憶 */
	heap->memory			= memory;
	heap->heap_size         = size;
	heap->current_address	= (hwptr_t)memory;
	heap->allocated_size    = 0;
}

void* hw_ring_heap_allocate(hw_ring_heap_t* heap, hw32 size, hw32 alignment)
{
	void* memory = NULL;
	
	HW_NULL_ASSERT(heap);

	/* サイズ0か、ヒープサイズを超えているなら何もせずNULLを返す */
	if(size > 0 && size <= heap->heap_size){
		/* 確保する先頭アドレスと終端アドレスを計算 */
		/* 確保の結果、リングバッファ容量を超えたらNULLを返す */
		hwptr_t head_address  = HW_ALIGNED_ROUND_UP(heap->current_address, alignment);
		hwptr_t tail_address  = head_address + size;
		hwptr_t allocate_size = tail_address - head_address;
		hwptr_t allocated_size = heap->allocated_size + allocate_size;
		if(allocated_size <= heap->heap_size) {

			/* バッファを１周するか計算 */
			/* しないなら今のアドレスから次のアドレスを計算 */
			hwptr_t base_address = (hwptr_t)heap->memory;
			hwptr_t end_address  = base_address + heap->heap_size;
			if(tail_address <= end_address) {
				memory = (void*)head_address;
				heap->allocated_size  = allocated_size;
				heap->current_address = head_address;
			}
			/* バッファを１周するなら今のアドレスからは連続したバッファは確保できない */
			/* バッファ先頭から終端アドレスを計算 */
			/* バッファ容量を超えているかの判定ももう一度必要 */
			else {
				head_address   = HW_ALIGNED_ROUND_UP(base_address, alignment);
				tail_address   = base_address + size;
				allocate_size  = tail_address - head_address;
				allocated_size = heap->allocated_size + allocate_size;
				if(allocated_size <= heap->heap_size) {	
					if(tail_address <= end_address) {
						memory = (void*)head_address;
						heap->allocated_size  = allocated_size;
						heap->current_address = head_address;
					}
				}		
			}
		}
	}

	return memory;
}

void hw_ring_heap_reset_allocated_size(hw_ring_heap_t* heap)
{
	HW_NULL_ASSERT(heap);
	heap->allocated_size = 0;
}

