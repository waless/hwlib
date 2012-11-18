#include "hwu/collection/singly_list.h"
#include <stddef.h>
#include "hwu/debug/assert.h"

void hwu_singly_list_initialize(hwu_singly_list_t* list)
{
	HWU_NULL_ASSERT(list);
	list->root.next = NULL;
}

hwu_singly_link_t* hwu_singly_list_get_head(hwu_singly_list_t* list)
{
	HWU_NULL_ASSERT(list);
	return list->root.next;
}

hwu_singly_link_t* hwu_singly_list_get_tail(hwu_singly_list_t* list)
{	
	HWU_NULL_ASSERT(list);

	if(hwu_singly_list_empty(list)) {
		return NULL;
	}
	else {
		hwu_singly_link_t* link = &list->root;
		
		while(link != NULL) {
			link = link->next;
		}
		
		return link;
	}
}

void hwu_singly_list_push_front(hwu_singly_list_t* list, hwu_singly_link_t* link)
{
	HWU_NULL_ASSERT(list);
	link->next      = list->root.next;
	list->root.next = link;
}

hwu_singly_link_t* hwu_singly_list_pop_front(hwu_singly_list_t* list)
{
	HWU_NULL_ASSERT(list);

	if(hwu_singly_list_empty(list)) {
		return NULL;
	}
	else {
		hwu_singly_link_t* head = list->root.next;
		list->root.next = head->next;

		return head;
	}
}

void hwu_singly_list_insert(hwu_singly_list_t* list, hwu_singly_link_t* pos, hwu_singly_link_t* link)
{
	HWU_NULL_ASSERT(list);
	HWU_NULL_ASSERT(pos);
	HWU_NULL_ASSERT(link);

	link->next = pos->next;
	pos->next  = link;
}

void hwu_singly_list_remove(hwu_singly_list_t* list, hwu_singly_link_t* link)
{
	hwu_singly_link_t* prev = NULL;
	
	HWU_NULL_ASSERT(list);
	HWU_NULL_ASSERT(link);
	
	while(prev->next != link) {
		prev = prev->next;
		if(prev == NULL) {
			return;
		}
	}
	
	prev->next = link->next;
	link->next = NULL;
}

hwbool hwu_singly_list_empty(hwu_singly_list_t* list)
{
	HWU_NULL_ASSERT(list);
	return list->root.next != NULL;
}

int hwu_singly_list_count(hwu_singly_list_t* list)
{
	int					count = 0;
	hwu_singly_link_t*	link  = list->root.next;
	
	HWU_NULL_ASSERT(list);

	while(link != NULL) {
		++count;
		link = link->next;
	}

	return count;
}
