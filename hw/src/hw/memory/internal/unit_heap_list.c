#include "hw/memory/internal/unit_heap_list.h"
#include "hw/debug/assert.h"
#include "hw/collection/doubly_link.h"
#include "hw/memory/internal/unit_memory.h"

void hwL_unit_heap_list_initialize(hwL_unit_heap_list_t* heap, hwu32 unit_size, int unit_num)
{
	HW_NULL_ASSERT(heap);
	hw_doubly_list_initialize(&heap->heap_list);
	heap->unit_size = unit_size;
	heap->unit_num  = unit_num;
}

void* hwL_unit_heap_list_allocate(hwL_unit_heap_list_t* list)
{
	void* memory = NULL;
	hwL_unit_heap_list_node_t* node = NULL;
	
	HW_NULL_ASSERT(list);
	
	node = (hwL_unit_heap_list_node_t*)hw_doubly_list_get_head(&list->heap_list);
	if(node != NULL) {
		memory = hwL_unit_memory_pop(node->heap, &node->heap);
		--node->current_unit_num;
		HW_ASSERT_MESSAGE(node->current_unit_num >= 0, "ヒープが空にもかかわらずメモリを確保しました");

		/* 確保したヒープを一番後ろに回す */
		node = (hwL_unit_heap_list_node_t*)hw_doubly_list_pop_front(&list->heap_list);
		hw_doubly_list_push_back(&list->heap_list, &node->link);
	}

	return memory;
}

hwL_unit_heap_list_node_t* hwL_unit_heap_list_deallocate(hwL_unit_heap_list_t* list, hwL_unit_heap_list_node_t* node, void* memory)
{
	HW_NULL_ASSERT(list);

	/* メモリがNULLなら何もしない */
	if(memory != NULL) {
		/* メモリの返却 */
		hwL_unit_memory_push(node->heap, memory, &node->heap);
		++node->current_unit_num;
		HW_ASSERT_MESSAGE(node->current_unit_num <= list->unit_num, "ヒープの最大ブロック数を超えてメモリが返却されました");

		/* 対象ヒープのメモリがすべて返却されたらヒープをリストから分離して返す */
		hw_doubly_list_remove(&list->heap_list, &node->link);
		if(node->current_unit_num >= list->unit_num){
			return node;
		}
		/* でなければ先頭ヒープから確実に確保できるように返却されたヒープを先頭に持ってくる */
		else {
			hw_doubly_list_push_front(&list->heap_list, &node->link);
		}
	}

	return NULL;
}

void hwL_unit_heap_list_grow(hwL_unit_heap_list_t* list, void* memory, hwu32 memory_size)
{
	hwL_unit_heap_list_node_t* node = NULL;
	
	HW_NULL_ASSERT(list);
	HW_NULL_ASSERT(memory);
	HW_ASSERT_MESSAGE(memory_size >= (hwL_unit_memory_calculate_need_size(list->unit_size, list->unit_num) + sizeof(hwL_unit_heap_list_node_t)), "ヒープの作成に必要なサイズがありません");

	/* メモリをチャンクとして分割、初期化 */
	hwL_unit_memory_initialize(memory, list->unit_size, list->unit_num, NULL);

	/* メモリの一番後ろのブロックを管理領域として使用 */
	node = hwL_unit_heap_list_get_node_from_heap_memory(memory, memory_size);
	node->link.prev		   = NULL;
	node->link.next		   = NULL;
	node->heap			   = memory;
	node->current_unit_num = list->unit_num;
	node->parent		   = list;

	/* ヒープを先頭に追加 */
	hw_doubly_list_push_front(&list->heap_list, &node->link);
}

int hwL_unit_heap_list_get_heap_size(hwL_unit_heap_list_t* list)
{
	HW_NULL_ASSERT(list);
	return list->unit_size * list->unit_num;
}

int hwL_unit_heap_list_get_unit_size(hwL_unit_heap_list_t* list)
{
	HW_NULL_ASSERT(list);
	return list->unit_size;
}

int hwL_unit_heap_list_get_unit_num(hwL_unit_heap_list_t* list)
{
	HW_NULL_ASSERT(list);
	return list->unit_num;
}

hwL_unit_heap_list_node_t* hwL_unit_heap_list_get_node_from_heap_memory(void* memory, hwu32 memory_size)
{
	return (hwL_unit_heap_list_node_t*)((char*)memory + memory_size - sizeof(hwL_unit_heap_list_node_t));
}
