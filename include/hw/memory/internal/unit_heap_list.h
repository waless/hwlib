#ifndef HW_MEMORY_UNIT_HEAP_LIST_H_
#define HW_MEMORY_UNIT_HEAP_LIST_H

#include "hw/collection/doubly_link.h"
#include "hw/collection/doubly_list.h"
#include "hw/memory/allocator.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hwL_unit_heap_list_t
{
	hw_doubly_list_t heap_list;
	hw32             unit_size;
	hw32             unit_num;
} hwL_unit_heap_list_t;

typedef struct tag_hwL_unit_heap_list_node_t
{
	hw_doubly_link_t			link;
	void*						heap;
	hw32						current_unit_num;
	hwL_unit_heap_list_t*		parent;
} hwL_unit_heap_list_node_t;

extern void  hwL_unit_heap_list_initialize(hwL_unit_heap_list_t* list, hw32 unit_size, int unit_num);
extern void* hwL_unit_heap_list_allocate(hwL_unit_heap_list_t* list);
extern hwL_unit_heap_list_node_t* hwL_unit_heap_list_deallocate(hwL_unit_heap_list_t* list, hwL_unit_heap_list_node_t* node, void* memory);
extern void  hwL_unit_heap_list_grow(hwL_unit_heap_list_t* list, void* memory, hw32 memory_size);
extern int   hwL_unit_heap_list_get_heap_size(hwL_unit_heap_list_t* list);
extern int   hwL_unit_heap_list_get_unit_size(hwL_unit_heap_list_t* list);
extern int   hwL_unit_heap_list_get_unit_num(hwL_unit_heap_list_t* list);
extern hwL_unit_heap_list_node_t* hwL_unit_heap_list_get_node_from_heap_memory(void* memory, hw32 memory_size);

#ifdef __cplusplus
}
#endif

#endif	/* HW_MEMORY_UNIT_HEAP_LIST_H */
