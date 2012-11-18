#include "hwu/memory/internal/unit_heap_list.h"
#include "hwu/debug/assert.h"
#include "hwu/collection/doubly_link.h"
#include "hwu/memory/internal/unit_memory.h"

void hwuL_unit_heap_list_initialize(hwuL_unit_heap_list_t* heap, int unit_size, int unit_num)
{
	HWU_NULL_ASSERT(heap);
	hwu_doubly_list_initialize(&heap->heap_list);
	heap->unit_size = unit_size;
	heap->unit_num  = unit_num;
}

void* hwuL_unit_heap_list_allocate(hwuL_unit_heap_list_t* list)
{
	void* memory = NULL;
	hwuL_unit_heap_list_node_t* node = NULL;
	
	HWU_NULL_ASSERT(list);
	
	node = (hwuL_unit_heap_list_node_t*)hwu_doubly_list_get_head(&list->heap_list);
	if(node != NULL) {
		memory = hwuL_unit_memory_pop(node->heap, &node->heap);
		--node->current_unit_num;
		HWU_ASSERT_MESSAGE(node->current_unit_num >= 0, "ヒープが空にもかかわらずメモリを確保しました");

		/* 確保したヒープを一番後ろに回す */
		node = (hwuL_unit_heap_list_node_t*)hwu_doubly_list_pop_front(&list->heap_list);
		hwu_doubly_list_push_back(&list->heap_list, &node->link);
	}

	return memory;
}

hwuL_unit_heap_list_node_t* hwuL_unit_heap_list_deallocate(hwuL_unit_heap_list_t* list, hwuL_unit_heap_list_node_t* node, void* memory)
{
	HWU_NULL_ASSERT(list);

	/* メモリがNULLなら何もしない */
	if(memory != NULL) {
		/* メモリの返却 */
		hwuL_unit_memory_push(node->heap, memory, &node->heap);
		++node->current_unit_num;
		HWU_ASSERT_MESSAGE(node->current_unit_num <= list->unit_num, "ヒープの最大ブロック数を超えてメモリが返却されました");

		/* 対象ヒープのメモリがすべて返却されたらヒープをリストから分離して返す */
		hwu_doubly_list_remove(&list->heap_list, &node->link);
		if(node->current_unit_num >= list->unit_num){
			return node;
		}
		/* でなければ先頭ヒープから確実に確保できるように返却されたヒープを先頭に持ってくる */
		else {
			hwu_doubly_list_push_front(&list->heap_list, &node->link);
		}
	}

	return NULL;
}

void hwuL_unit_heap_list_grow(hwuL_unit_heap_list_t* list, void* memory, int memory_size)
{
	hwuL_unit_heap_list_node_t* node = NULL;
	
	HWU_NULL_ASSERT(list);
	HWU_NULL_ASSERT(memory);
	HWU_ASSERT_MESSAGE(memory_size >= (hwuL_unit_memory_calculate_need_size(list->unit_size, list->unit_num) + sizeof(hwuL_unit_heap_list_node_t)), "ヒープの作成に必要なサイズがありません");

	/* メモリをチャンクとして分割、初期化 */
	hwuL_unit_memory_initialize(memory, list->unit_size, list->unit_num, NULL);

	/* メモリの一番後ろのブロックを管理領域として使用 */
	node = hwuL_unit_heap_list_get_node_from_heap_memory(memory, memory_size);
	node->link.prev		   = NULL;
	node->link.next		   = NULL;
	node->heap			   = memory;
	node->current_unit_num = list->unit_num;
	node->parent		   = list;

	/* ヒープを先頭に追加 */
	hwu_doubly_list_push_front(&list->heap_list, &node->link);
}

int hwuL_unit_heap_list_get_heap_size(hwuL_unit_heap_list_t* list)
{
	HWU_NULL_ASSERT(list);
	return list->unit_size * list->unit_num;
}

int hwuL_unit_heap_list_get_unit_size(hwuL_unit_heap_list_t* list)
{
	HWU_NULL_ASSERT(list);
	return list->unit_size;
}

int hwuL_unit_heap_list_get_unit_num(hwuL_unit_heap_list_t* list)
{
	HWU_NULL_ASSERT(list);
	return list->unit_num;
}

hwuL_unit_heap_list_node_t* hwuL_unit_heap_list_get_node_from_heap_memory(void* memory, int memory_size)
{
	return (hwuL_unit_heap_list_node_t*)((char*)memory + memory_size - sizeof(hwuL_unit_heap_list_node_t));
}
