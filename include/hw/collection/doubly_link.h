#ifndef HW_DOUBLY_LINK_H_
#define HW_DOUBLY_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hw_doubly_link_t
{
	struct tag_hw_doubly_link_t* prev;
	struct tag_hw_doubly_link_t* next;
} hw_doubly_link_t;

#ifdef __cplusplus
}
#endif

#endif /* HW_DOUBLY_LINK_H_ */

