#include "hw/collection/doubly_list.h"
#include "hw/debug/assert.h"

void hw_doubly_list_initialize(hw_doubly_list_t* list)
{
	HW_NULL_ASSERT(list);
	list->root.prev = &list->root;
	list->root.next = &list->root;
}

hw_doubly_link_t* hw_doubly_list_get_head(hw_doubly_list_t* list)
{
	HW_NULL_ASSERT(list);
	return (list->root.next != &list->root) ? list->root.next : NULL;
}

hw_doubly_link_t* hw_doubly_list_get_tail(hw_doubly_list_t* list)
{
	HW_NULL_ASSERT(list);
	return (list->root.prev != &list->root) ? list->root.prev : NULL;
}

void hw_doubly_list_push_front(hw_doubly_list_t* list, hw_doubly_link_t* link)
{
	HW_NULL_ASSERT(list);
	HW_NULL_ASSERT(link);
	
	link->prev		= &list->root;
	link->next		= list->root.next;
	list->root.next = link;
}

void hw_doubly_list_push_back(hw_doubly_list_t* list, hw_doubly_link_t* link)
{
	HW_NULL_ASSERT(list);
	HW_NULL_ASSERT(link);
	
	link->prev		= list->root.prev;
	link->next		= &list->root;
	list->root.prev = link;
}

hw_doubly_link_t* hw_doubly_list_pop_front(hw_doubly_list_t* list)
{
	HW_NULL_ASSERT(list);
	if(list->root.next == &list->root) {
		return NULL;
	}
	else {
		hw_doubly_link_t* head  = list->root.next;
		head->next->prev = &list->root;
		list->root.next	 = head->next;
		
		return head;
	}
}

hw_doubly_link_t* hw_doubly_list_pop_back(hw_doubly_list_t* list)
{
	HW_NULL_ASSERT(list);
	if(list->root.prev == &list->root) {
		return NULL;
	}
	else {
		hw_doubly_link_t* tail = list->root.prev;
		tail->prev->next = list->root.prev;
		list->root.prev  = tail->prev;

		return tail;
	}
}

void hw_doubly_list_insert(hw_doubly_list_t* list, hw_doubly_link_t* pos, hw_doubly_link_t* link)
{
	HW_NULL_ASSERT(list);
	HW_NULL_ASSERT(pos)
	HW_NULL_ASSERT(link);

	link->prev		= pos;
	link->next		= pos->next;
	pos->next->prev = link;
	pos->next		= link;
}

void hw_doubly_list_remove(hw_doubly_list_t* list, hw_doubly_link_t* link)
{
	HW_NULL_ASSERT(list);
	HW_NULL_ASSERT(link);

	link->prev->next = link->next;
	link->next->prev = link->prev;
	link->prev = NULL;
	link->next = NULL;
}

hwbool hw_doubly_lits_empty(hw_doubly_list_t* list)
{
	HW_NULL_ASSERT(list);
	return list->root.prev == list->root.next;
}

int hw_doubly_list_count(hw_doubly_list_t* list)
{
	hw_doubly_link_t* link  = NULL;
	int                count = 0;
	
	HW_NULL_ASSERT(list);
	while(link != &list->root) {
		++count;
		link = link->next;
	}
		
	return count;
}


