#include "hwu/collection/doubly_list.h"
#include "hwu/debug/assert.h"

void hwu_doubly_list_initialize(hwu_doubly_list_t* list)
{
	HWU_NULL_ASSERT(list);
	list->root.prev = &list->root;
	list->root.next = &list->root;
}

hwu_doubly_link_t* hwu_doubly_list_get_head(hwu_doubly_list_t* list)
{
	HWU_NULL_ASSERT(list);
	return (list->root.next != &list->root) ? list->root.next : NULL;
}

hwu_doubly_link_t* hwu_doubly_list_get_tail(hwu_doubly_list_t* list)
{
	HWU_NULL_ASSERT(list);
	return (list->root.prev != &list->root) ? list->root.prev : NULL;
}

void hwu_doubly_list_push_front(hwu_doubly_list_t* list, hwu_doubly_link_t* link)
{
	HWU_NULL_ASSERT(list);
	HWU_NULL_ASSERT(link);
	
	link->prev		= &list->root;
	link->next		= list->root.next;
	list->root.next = link;
}

void hwu_doubly_list_push_back(hwu_doubly_list_t* list, hwu_doubly_link_t* link)
{
	HWU_NULL_ASSERT(list);
	HWU_NULL_ASSERT(link);
	
	link->prev		= list->root.prev;
	link->next		= &list->root;
	list->root.prev = link;
}

hwu_doubly_link_t* hwu_doubly_list_pop_front(hwu_doubly_list_t* list)
{
	HWU_NULL_ASSERT(list);
	if(list->root.next == &list->root) {
		return NULL;
	}
	else {
		hwu_doubly_link_t* head  = list->root.next;
		head->next->prev = &list->root;
		list->root.next	 = head->next;
		
		return head;
	}
}

hwu_doubly_link_t* hwu_doubly_list_pop_back(hwu_doubly_list_t* list)
{
	HWU_NULL_ASSERT(list);
	if(list->root.prev == &list->root) {
		return NULL;
	}
	else {
		hwu_doubly_link_t* tail = list->root.prev;
		tail->prev->next = list->root.prev;
		list->root.prev  = tail->prev;

		return tail;
	}
}

void hwu_doubly_list_insert(hwu_doubly_list_t* list, hwu_doubly_link_t* pos, hwu_doubly_link_t* link)
{
	HWU_NULL_ASSERT(list);
	HWU_NULL_ASSERT(pos)
	HWU_NULL_ASSERT(link);

	link->prev		= pos;
	link->next		= pos->next;
	pos->next->prev = link;
	pos->next		= link;
}

void hwu_doubly_list_remove(hwu_doubly_list_t* list, hwu_doubly_link_t* link)
{
	HWU_NULL_ASSERT(list);
	HWU_NULL_ASSERT(link);

	link->prev->next = link->next;
	link->next->prev = link->prev;
	link->prev = NULL;
	link->next = NULL;
}

hwbool hwu_doubly_lits_empty(hwu_doubly_list_t* list)
{
	HWU_NULL_ASSERT(list);
	return list->root.prev == list->root.next;
}

int hwu_doubly_list_count(hwu_doubly_list_t* list)
{
	hwu_doubly_link_t* link  = NULL;
	int                count = 0;
	
	HWU_NULL_ASSERT(list);
	while(link != &list->root) {
		++count;
		link = link->next;
	}
		
	return count;
}


