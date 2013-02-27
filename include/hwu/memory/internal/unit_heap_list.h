#ifndef HWU_MEMORY_UNIT_HEAP_LIST_H_
#define HWU_MEMORY_UNIT_HEAP_LIST_H

#include "hwu/collection/doubly_link.h"
#include "hwu/collection/doubly_list.h"
#include "hwu/memory/allocator.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hwuL_unit_heap_list_t
{
	hwu_doubly_list_t heap_list;
	int               unit_size;
	int               unit_num;
} hwuL_unit_heap_list_t;

typedef struct tag_hwuL_unit_heap_list_node_t
{
	hwu_doubly_link_t			link;
	void*						heap;
	int							current_unit_num;
	hwuL_unit_heap_list_t*		parent;
} hwuL_unit_heap_list_node_t;

extern void  hwuL_unit_heap_list_initialize(hwuL_unit_heap_list_t* list, int unit_size, int unit_num);
extern void* hwuL_unit_heap_list_allocate(hwuL_unit_heap_list_t* list);
extern hwuL_unit_heap_list_node_t* hwuL_unit_heap_list_deallocate(hwuL_unit_heap_list_t* list, hwuL_unit_heap_list_node_t* node, void* memory);
extern void  hwuL_unit_heap_list_grow(hwuL_unit_heap_list_t* list, void* memory, int memory_size);
extern int   hwuL_unit_heap_list_get_heap_size(hwuL_unit_heap_list_t* list);
extern int   hwuL_unit_heap_list_get_unit_size(hwuL_unit_heap_list_t* list);
extern int   hwuL_unit_heap_list_get_unit_num(hwuL_unit_heap_list_t* list);
extern hwuL_unit_heap_list_node_t* hwuL_unit_heap_list_get_node_from_heap_memory(void* memory, int memory_size);

#ifdef __cplusplus
}
#endif

#endif	/* HWU_MEMORY_UNIT_HEAP_LIST_H */
