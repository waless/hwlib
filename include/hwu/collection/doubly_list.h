#ifndef HWU_DOUBLY_LIST_H_
#define HWU_DOUBLY_LIST_H_

#include "hwu/types.h"
#include "hwu/collection/doubly_link.h"

typedef struct tag_hwu_doubly_list_t
{
	hwu_doubly_link_t root;
} hwu_doubly_list_t;

extern void               hwu_doubly_list_initialize(hwu_doubly_list_t* list);
extern hwu_doubly_link_t* hwu_doubly_list_get_head(hwu_doubly_list_t* list);
extern hwu_doubly_link_t* hwu_doubly_list_get_tail(hwu_doubly_list_t* list);
extern void               hwu_doubly_list_push_front(hwu_doubly_list_t* list, hwu_doubly_link_t* link);
extern void               hwu_doubly_list_push_back(hwu_doubly_list_t* list, hwu_doubly_link_t* link);
extern hwu_doubly_link_t* hwu_doubly_list_pop_front(hwu_doubly_list_t* list);
extern hwu_doubly_link_t* hwu_doubly_list_pop_back(hwu_doubly_list_t* list);
extern void               hwu_doubly_list_insert(hwu_doubly_list_t* list, hwu_doubly_link_t* pos, hwu_doubly_link_t* link);
extern void               hwu_doubly_list_remove(hwu_doubly_list_t* list, hwu_doubly_link_t* link);
extern hwbool             hwu_doubly_list_empty(hwu_doubly_list_t* list);
extern int                hwu_doubly_list_count(hwu_doubly_list_t* list);

#endif  /* HWU_DOUBLY_LIST_H_ */

