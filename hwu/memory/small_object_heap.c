#include "hwu/memory/small_object_heap.h"
#include "hwu/memory/unit_heap.h"
#include "hwu/memory/misc.h"
#include "hwu/memory/internal/unit_heap_list.h"
#include "hwu/debug/assert.h"

/* このアロケータから確保された事を表すタグ */
typedef void* small_object_tag_t;

static void grow_heap(hwu_small_object_heap_t* parent, hwuL_unit_heap_list_t* heap);
static hwuL_unit_heap_list_node_t* get_node_from_memory(hwu_small_object_heap_t* heap, void* memory);
static small_object_tag_t* get_tag_address(void* memory, int memory_size);
static int calculate_allocate_size(int size, int alignment);

void hwu_small_object_heap_initialize(hwu_small_object_heap_t* heap, hwu_allocator_aligned_t allocator, hwu_deallocator_aligned_t deallocator, int max_unit_size, int split_unit_size, int unit_heap_size)
{
    hwuL_unit_heap_list_t*		heap_array = NULL;
    int							heap_num   = 0;
	int							i		   = 0;
	
    /* NULLチェック */
    HWU_NULL_ASSERT(heap);
    HWU_NULL_ASSERT(allocator);
    HWU_NULL_ASSERT(deallocator);

    /* 最低限のサイズがあるかチェック */
    HWU_ASSERT(split_unit_size > 0);
    HWU_ASSERT(max_unit_size > 0);
    HWU_ASSERT(max_unit_size > split_unit_size);

	/* 最大サイズと分割サイズは割り切れること */
    HWU_ASSERT((max_unit_size % split_unit_size) == 0);

	/* ヒープの配列メモリ確保 */
 	heap_num   = max_unit_size / split_unit_size;
	heap_array = (hwuL_unit_heap_list_t*)allocator(sizeof(hwuL_unit_heap_list_t) * heap_num, sizeof(double));

	/* 各ヒープのブロックサイズ計算して初期化 */
	for(i = 0; i < heap_num; ++i) {
		int unit_size = split_unit_size * i;
		int unit_num  = (unit_heap_size - sizeof(hwuL_unit_heap_list_node_t)) / unit_size;
		hwuL_unit_heap_list_initialize(heap_array + i, unit_size, unit_num);
	}

	/* パラメータ記憶 */
	heap->heaps			  = heap_array;
	heap->max_unit_size   = max_unit_size;
	heap->split_unit_size = split_unit_size;
	heap->allocator		  = allocator;
	heap->deallocator	  = deallocator;
}

void* hwu_small_object_heap_allocate(hwu_small_object_heap_t* heap, int size, int alignment)
{
	int							heap_index    = 0;
	int							allocate_size = 0;
	hwuL_unit_heap_list_t*		target_heap	  = NULL;
	void*                       memory        = NULL;
		
	HWU_NULL_ASSERT(heap);

	/* 最大単位サイズを超えていたらNULLを返す */
	allocate_size = calculate_allocate_size(size, alignment);
	if(allocate_size > heap->max_unit_size) {
		return NULL;
	}
	
	heap_index    = allocate_size / heap->split_unit_size;
	target_heap   = ((hwuL_unit_heap_list_t*)heap->heaps) + heap_index;
	memory        = heap->allocator(allocate_size, allocate_size);
	if(memory == NULL) {
		grow_heap(heap, target_heap);
		memory = heap->allocator(allocate_size, allocate_size);
	}

	/* 余分に確保した最後尾のメモリにタグとしてこのアロケータのアドレスを設定 */
	if(memory != NULL) {
		small_object_tag_t* tag = get_tag_address(memory, hwuL_unit_heap_list_get_unit_size(target_heap));
		*tag = heap;
	}
	
	return memory;
}

void hwu_small_object_heap_deallocate(hwu_small_object_heap_t* heap, void* memory)
{
	hwuL_unit_heap_list_node_t* target_heap_node = NULL;
	hwuL_unit_heap_list_t*		target_heap		 = NULL;
	
	HWU_NULL_ASSERT(heap);
	HWU_NULL_ASSERT(memory);

	/* ヒープメモリアドレスからメモリが属しているヒープを取得 */
	target_heap_node = get_node_from_memory(heap, memory);

	/* ヒープは親のヒープリストを覚えているので取得 */
	target_heap = target_heap_node->parent;

	/* ヒープにメモリを返却 */
	/* そのヒープのメモリが使用されなくなったら */
	/* リストから分離され返ってくるのでメモリを開放する */
	hwuL_unit_heap_list_node_t* empty_heap = hwuL_unit_heap_list_deallocate(target_heap, target_heap_node, memory);
	if(empty_heap != NULL) {
		heap->deallocator(empty_heap->heap);
	}
}

BOOL hwu_small_object_heap_is_in_heap(hwu_small_object_heap_t* heap, void* memory)
{
	hwuL_unit_heap_list_node_t* target_heap_node = NULL;
	hwuL_unit_heap_list_t*		target_heap		 = NULL;
	small_object_tag_t*         tag              = NULL;

	HWU_NULL_ASSERT(heap);
	HWU_NULL_ASSERT(memory);

	target_heap_node = get_node_from_memory(heap, memory);
	target_heap		 = target_heap_node->parent;
	tag				 = get_tag_address(memory, hwuL_unit_heap_list_get_unit_size(target_heap));

	return ((hwuptr_t)tag) == ((hwuptr_t)heap);
}

void grow_heap(hwu_small_object_heap_t* parent, hwuL_unit_heap_list_t* heap)
{
	int	  allocate_size = parent->unit_heap_size;
	void* heap_memory   = parent->allocator(allocate_size, allocate_size);
	if(heap_memory != NULL) {
		hwuL_unit_heap_list_grow(heap, heap_memory, allocate_size);
	}
}

hwuL_unit_heap_list_node_t* get_node_from_memory(hwu_small_object_heap_t* heap, void* memory)
{
	hwuptr_t					heap_memory		 = 0;
	hwuL_unit_heap_list_node_t* target_heap_node = NULL;
	
	/* ヒープのメモリアドレスはヒープサイズでアラインメントされている */
	/* そのため、ヒープに属しているメモリブロックのANDをとると */
	/* ヒープメモリのアドレスを取得できる */
	heap_memory = (hwuptr_t)memory & heap->unit_heap_size;

	/* ヒープメモリアドレスからメモリが属しているヒープを取得 */
	target_heap_node = hwuL_unit_heap_list_get_node_from_heap_memory((void*)heap_memory, heap->unit_heap_size);

	return target_heap_node;
}

small_object_tag_t* get_tag_address(void* memory, int memory_size)
{
	return (small_object_tag_t*)((char*)memory + memory_size - sizeof(small_object_tag_t));
}

int calculate_allocate_size(int size, int alignment)
{
	return HWU_MEMORY_ROUND_UP(size + sizeof(small_object_tag_t), alignment);
}
