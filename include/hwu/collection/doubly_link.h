#ifndef HWU_DOUBLY_LINK_H_
#define HWU_DOUBLY_LINK_H_

typedef struct tag_hwu_doubly_link_t
{
	struct tag_hwu_doubly_link_t* prev;
	struct tag_hwu_doubly_link_t* next;
} hwu_doubly_link_t;

#endif /* HWU_DOUBLY_LINK_H_ */
