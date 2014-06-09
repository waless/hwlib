#include "hw/memory/small_object_heap.h"
#include "hw/utility.h"
#include "hw/memory/unit_heap.h"
#include "hw/memory/internal/unit_heap_list.h"
#include "hw/debug/assert.h"

/* このアロケータから確保された事を表すタグ */
typedef void* small_object_tag_t;

static void grow_heap(hw_small_object_heap_t* parent, hwL_unit_heap_list_t* heap);
static hwL_unit_heap_list_node_t* get_node_from_memory(hw_small_object_heap_t* heap, void* memory);
static small_object_tag_t* get_tag_address(void* memory, hwu32 memory_size);
static hwu32 calculate_allocate_size(hwu32 size, hwu32 alignment);

void hw_small_object_heap_initialize(hw_small_object_heap_t* heap, hw_allocator_aligned_t allocator, hw_deallocator_aligned_t deallocator, hwu32 max_unit_size, hwu32 split_unit_size, hwu32 unit_heap_size)
{
    hwL_unit_heap_list_t* heap_array = NULL;
    hwu32				   heap_num   = 0;
	hwu32				   i		  = 0;
	
    /* NULLチェック */
    HW_NULL_ASSERT(heap);
    HW_NULL_ASSERT(allocator);
    HW_NULL_ASSERT(deallocator);

    /* 最低限のサイズがあるかチェック */
    HW_ASSERT(split_unit_size > 0);
    HW_ASSERT(max_unit_size > 0);
    HW_ASSERT(max_unit_size > split_unit_size);

	/* 最大サイズと分割サイズは割り切れること */
    HW_ASSERT((max_unit_size % split_unit_size) == 0);

	/* ヒープの配列メモリ確保 */
 	heap_num   = max_unit_size / split_unit_size;
	heap_array = (hwL_unit_heap_list_t*)allocator(sizeof(hwL_unit_heap_list_t) * heap_num, sizeof(double));

	/* 各ヒープのブロックサイズ計算して初期化 */
	for(i = 0; i < heap_num; ++i) {
		hwu32 unit_size = split_unit_size * i;
		hwu32 unit_num  = (unit_heap_size - sizeof(hwL_unit_heap_list_node_t)) / unit_size;
		hwL_unit_heap_list_initialize(heap_array + i, unit_size, unit_num);
	}

	/* パラメータ記憶 */
	heap->heaps			  = heap_array;
	heap->max_unit_size   = max_unit_size;
	heap->split_unit_size = split_unit_size;
	heap->allocator		  = allocator;
	heap->deallocator	  = deallocator;
}

void* hw_small_object_heap_allocate(hw_small_object_heap_t* heap, hwu32 size, hwu32 alignment)
{
	hwu32						heap_index    = 0;
	hwu32						allocate_size = 0;
	hwL_unit_heap_list_t*		target_heap	  = NULL;
	void*                       memory        = NULL;
		
	HW_NULL_ASSERT(heap);

	/* 最大単位サイズを超えていたらNULLを返す */
	allocate_size = calculate_allocate_size(size, alignment);
	if(allocate_size > heap->max_unit_size) {
		return NULL;
	}
	
	heap_index    = allocate_size / heap->split_unit_size;
	target_heap   = ((hwL_unit_heap_list_t*)heap->heaps) + heap_index;
	memory        = heap->allocator(allocate_size, allocate_size);
	if(memory == NULL) {
		grow_heap(heap, target_heap);
		memory = heap->allocator(allocate_size, allocate_size);
	}

	/* 余分に確保した最後尾のメモリにタグとしてこのアロケータのアドレスを設定 */
	if(memory != NULL) {
		small_object_tag_t* tag = get_tag_address(memory, hwL_unit_heap_list_get_unit_size(target_heap));
		*tag = heap;
	}
	
	return memory;
}

void hw_small_object_heap_deallocate(hw_small_object_heap_t* heap, void* memory)
{
	hwL_unit_heap_list_node_t* target_heap_node = NULL;
	hwL_unit_heap_list_t*		target_heap		 = NULL;
	hwL_unit_heap_list_node_t* empty_heap       = NULL;
	
	HW_NULL_ASSERT(heap);
	HW_NULL_ASSERT(memory);

	/* ヒープメモリアドレスからメモリが属しているヒープを取得 */
	target_heap_node = get_node_from_memory(heap, memory);

	/* ヒープは親のヒープリストを覚えているので取得 */
	target_heap = target_heap_node->parent;

	/* ヒープにメモリを返却 */
	/* そのヒープのメモリが使用されなくなったら */
	/* リストから分離され返ってくるのでメモリを開放する */
	empty_heap = hwL_unit_heap_list_deallocate(target_heap, target_heap_node, memory);
	if(empty_heap != NULL) {
		heap->deallocator(empty_heap->heap);
	}
}

hwbool hw_small_object_heap_is_in_heap(hw_small_object_heap_t* heap, void* memory)
{
	hwL_unit_heap_list_node_t* target_heap_node = NULL;
	hwL_unit_heap_list_t*	   target_heap		= NULL;
	small_object_tag_t*        tag              = NULL;

	HW_NULL_ASSERT(heap);
	HW_NULL_ASSERT(memory);

	target_heap_node = get_node_from_memory(heap, memory);
	target_heap		 = target_heap_node->parent;
	tag				 = get_tag_address(memory, hwL_unit_heap_list_get_unit_size(target_heap));

	return ((hwuptr_t)tag) == ((hwuptr_t)heap);
}

void grow_heap(hw_small_object_heap_t* parent, hwL_unit_heap_list_t* heap)
{
	hwu32 allocate_size = parent->unit_heap_size;
	void* heap_memory   = parent->allocator(allocate_size, allocate_size);
	if(heap_memory != NULL) {
		hwL_unit_heap_list_grow(heap, heap_memory, allocate_size);
	}
}

hwL_unit_heap_list_node_t* get_node_from_memory(hw_small_object_heap_t* heap, void* memory)
{
	hwuptr_t				   heap_memory		= 0;
	hwL_unit_heap_list_node_t* target_heap_node = NULL;
	
	/* ヒープのメモリアドレスはヒープサイズでアラインメントされている */
	/* そのため、ヒープに属しているメモリブロックのANDをとると */
	/* ヒープメモリのアドレスを取得できる */
	heap_memory = (hwuptr_t)memory & heap->unit_heap_size;

	/* ヒープメモリアドレスからメモリが属しているヒープを取得 */
	target_heap_node = hwL_unit_heap_list_get_node_from_heap_memory((void*)heap_memory, heap->unit_heap_size);

	return target_heap_node;
}

small_object_tag_t* get_tag_address(void* memory, hwu32 memory_size)
{
	return (small_object_tag_t*)((char*)memory + memory_size - sizeof(small_object_tag_t));
}

hwu32 calculate_allocate_size(hwu32 size, hwu32 alignment)
{
	return HW_ALIGNED_ROUND_UP(size + sizeof(small_object_tag_t), alignment);
}
