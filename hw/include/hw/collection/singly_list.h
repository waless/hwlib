#ifndef HW_COLLECTION_SINGLY_LIST_H_
#define HW_COLLECTION_SINGLY_LIST_H_

#include "hw/types.h"
#include "hw/collection/singly_link.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hw_singly_list_t
{
	hw_singly_link_t root;
} hw_singly_list_t;

extern void hw_singly_list_initialize(hw_singly_list_t* list);
extern hw_singly_link_t* hw_singly_get_head(hw_singly_list_t* list);
extern hw_singly_link_t* hw_singly_get_tail(hw_singly_list_t* list);
extern void hw_singly_list_push_front(hw_singly_list_t* list, hw_singly_link_t* link);
extern hw_singly_link_t* hw_singly_list_pop_front(hw_singly_list_t* list);
extern void hw_singly_list_insert(hw_singly_list_t* list, hw_singly_link_t* pos, hw_singly_link_t* link);
extern void hw_singly_list_remove(hw_singly_list_t* list, hw_singly_link_t* link);
extern hwbool hw_singly_list_empty(hw_singly_list_t* list);
extern int  hw_singly_list_count(hw_singly_list_t* list);

#ifdef __cplusplus
}
#endif

#endif  /* HW_COLLECTION_SINGLY_LIST_H_ */

