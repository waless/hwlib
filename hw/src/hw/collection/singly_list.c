#include "hw/collection/singly_list.h"
#include <stddef.h>
#include "hw/debug/assert.h"

void hw_singly_list_initialize(hw_singly_list_t* list)
{
	HW_NULL_ASSERT(list);
	list->root.next = NULL;
}

hw_singly_link_t* hw_singly_list_get_head(hw_singly_list_t* list)
{
	HW_NULL_ASSERT(list);
	return list->root.next;
}

hw_singly_link_t* hw_singly_list_get_tail(hw_singly_list_t* list)
{	
	HW_NULL_ASSERT(list);

	if(hw_singly_list_empty(list)) {
		return NULL;
	}
	else {
		hw_singly_link_t* link = &list->root;
		
		while(link != NULL) {
			link = link->next;
		}
		
		return link;
	}
}

void hw_singly_list_push_front(hw_singly_list_t* list, hw_singly_link_t* link)
{
	HW_NULL_ASSERT(list);
	link->next      = list->root.next;
	list->root.next = link;
}

hw_singly_link_t* hw_singly_list_pop_front(hw_singly_list_t* list)
{
	HW_NULL_ASSERT(list);

	if(hw_singly_list_empty(list)) {
		return NULL;
	}
	else {
		hw_singly_link_t* head = list->root.next;
		list->root.next = head->next;

		return head;
	}
}

void hw_singly_list_insert(hw_singly_list_t* list, hw_singly_link_t* pos, hw_singly_link_t* link)
{
	HW_NULL_ASSERT(list);
	HW_NULL_ASSERT(pos);
	HW_NULL_ASSERT(link);

	link->next = pos->next;
	pos->next  = link;
}

void hw_singly_list_remove(hw_singly_list_t* list, hw_singly_link_t* link)
{
	hw_singly_link_t* prev = NULL;
	
	HW_NULL_ASSERT(list);
	HW_NULL_ASSERT(link);
	
	while(prev->next != link) {
		prev = prev->next;
		if(prev == NULL) {
			return;
		}
	}
	
	prev->next = link->next;
	link->next = NULL;
}

hwbool hw_singly_list_empty(hw_singly_list_t* list)
{
	HW_NULL_ASSERT(list);
	return list->root.next != NULL;
}

int hw_singly_list_count(hw_singly_list_t* list)
{
	int					count = 0;
	hw_singly_link_t*	link  = list->root.next;
	
	HW_NULL_ASSERT(list);

	while(link != NULL) {
		++count;
		link = link->next;
	}

	return count;
}
