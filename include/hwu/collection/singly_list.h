#ifndef HWU_COLLECTION_SINGLY_LIST_H_
#define HWU_COLLECTION_SINGLY_LIST_H_

#include "hwu/types.h"
#include "hwu/collection/singly_link.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hwu_singly_list_t
{
	hwu_singly_link_t root;
} hwu_singly_list_t;

extern void hwu_singly_list_initialize(hwu_singly_list_t* list);
extern hwu_singly_link_t* hwu_singly_get_head(hwu_singly_list_t* list);
extern hwu_singly_link_t* hwu_singly_get_tail(hwu_singly_list_t* list);
extern void hwu_singly_list_push_front(hwu_singly_list_t* list, hwu_singly_link_t* link);
extern hwu_singly_link_t* hwu_singly_list_pop_front(hwu_singly_list_t* list);
extern void hwu_singly_list_insert(hwu_singly_list_t* list, hwu_singly_link_t* pos, hwu_singly_link_t* link);
extern void hwu_singly_list_remove(hwu_singly_list_t* list, hwu_singly_link_t* link);
extern hwbool hwu_singly_list_empty(hwu_singly_list_t* list);
extern int  hwu_singly_list_count(hwu_singly_list_t* list);

#ifdef __cplusplus
}
#endif

#endif  /* HWU_COLLECTION_SINGLY_LIST_H_ */

