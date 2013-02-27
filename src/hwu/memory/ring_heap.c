#include "hwu/memory/ring_heap.h"
#include "hwu/utility.h"
#include "hwu/debug/assert.h"

void hwu_ring_heap_initialize(hwu_ring_heap_t* heap, void* memory, int size)
{
	HWU_NULL_ASSERT(heap);
	HWU_NULL_ASSERT(memory);
	HWU_ASSERT(size > 0);

	/* パラメータを記憶 */
	heap->memory			= memory;
	heap->heap_size         = size;
	heap->current_address	= (hwuptr_t)memory;
	heap->allocated_size    = 0;
}

void* hwu_ring_heap_allocate(hwu_ring_heap_t* heap, int size, int alignment)
{
	void* memory = NULL;
	
	HWU_NULL_ASSERT(heap);

	/* サイズ0か、ヒープサイズを超えているなら何もせずNULLを返す */
	if(size > 0 && size <= heap->heap_size){
		/* 確保する先頭アドレスと終端アドレスを計算 */
		/* 確保の結果、リングバッファ容量を超えたらNULLを返す */
		hwuptr_t head_address  = HWU_ALIGNED_ROUND_UP(heap->current_address, alignment);
		hwuptr_t tail_address  = head_address + size;
		hwuptr_t allocate_size = tail_address - head_address;
		hwuptr_t allocated_size = heap->allocated_size + allocate_size;
		if(allocated_size <= heap->heap_size) {

			/* バッファを１周するか計算 */
			/* しないなら今のアドレスから次のアドレスを計算 */
			hwuptr_t base_address = (hwuptr_t)heap->memory;
			hwuptr_t end_address  = base_address + heap->heap_size;
			if(tail_address <= end_address) {
				memory = (void*)head_address;
				heap->allocated_size  = allocated_size;
				heap->current_address = head_address;
			}
			/* バッファを１周するなら今のアドレスからは連続したバッファは確保できない */
			/* バッファ先頭から終端アドレスを計算 */
			/* バッファ容量を超えているかの判定ももう一度必要 */
			else {
				head_address   = HWU_ALIGNED_ROUND_UP(base_address, alignment);
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

void hwu_ring_heap_reset_allocated_size(hwu_ring_heap_t* heap)
{
	HWU_NULL_ASSERT(heap);
	heap->allocated_size = 0;
}

