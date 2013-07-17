#ifndef HW_DOUBLY_LIST_H_
#define HW_DOUBLY_LIST_H_

#include "hw/types.h"
#include "hw/collection/doubly_link.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hw_doubly_list_t
{
	hw_doubly_link_t root;
} hw_doubly_list_t;

extern void               hw_doubly_list_initialize(hw_doubly_list_t* list);
extern hw_doubly_link_t* hw_doubly_list_get_head(hw_doubly_list_t* list);
extern hw_doubly_link_t* hw_doubly_list_get_tail(hw_doubly_list_t* list);
extern void               hw_doubly_list_push_front(hw_doubly_list_t* list, hw_doubly_link_t* link);
extern void               hw_doubly_list_push_back(hw_doubly_list_t* list, hw_doubly_link_t* link);
extern hw_doubly_link_t* hw_doubly_list_pop_front(hw_doubly_list_t* list);
extern hw_doubly_link_t* hw_doubly_list_pop_back(hw_doubly_list_t* list);
extern void               hw_doubly_list_insert(hw_doubly_list_t* list, hw_doubly_link_t* pos, hw_doubly_link_t* link);
extern void               hw_doubly_list_remove(hw_doubly_list_t* list, hw_doubly_link_t* link);
extern hwbool             hw_doubly_list_empty(hw_doubly_list_t* list);
extern int                hw_doubly_list_count(hw_doubly_list_t* list);

#ifdef __cplusplus
}
#endif

#endif  /* HW_DOUBLY_LIST_H_ */

