#ifndef HWU_MEMORY_STACK_HEAP_H_
#define HWU_MEMORY_STACK_HEAP_H_

#include "hwu/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hwu_stack_heap_t
{
	hwuptr_t memory_address;
	hwuptr_t top_address;
	hwuptr_t bottom_address;
	hwu32    memory_size;
} hwu_stack_heap_t;

typedef enum tag_hwu_stack_heap_direction_t
{
	HWU_STACK_HEAP_DIRECTION_TOP = 0,
	HWU_STACK_HEAP_DIRECTION_BOTTOM,
} hwu_stack_heap_direction_t;

typedef hwuptr_t hwu_stack_heap_maker_t;

extern void hwu_stack_heap_initialize(hwu_stack_heap_t* heap, void* memory, hwu32 size);
extern void hwu_stack_heap_finalize(hwu_stack_heap_t* heap);
extern void* hwu_stack_heap_allocate_ex(hwu_stack_heap_t* heap, hwu32 size, hwu32 alignment, hwu_stack_heap_direction_t direction);
extern void hwu_stack_heap_deallocate_to_maker_ex(hwu_stack_heap_t* heap, hwu_stack_heap_maker_t maker, hwu_stack_heap_direction_t direction);
extern hwu_stack_heap_maker_t hwu_stack_heap_get_maker_ex(hwu_stack_heap_t* heap, hwu_stack_heap_direction_t direction);

/* アラインメント、確保方向を意識しない時の為の定義 */
#define hwu_stack_heap_allocate(heap, size)             hwu_stack_heap_allocate_ex(heap, size, sizeof(double), HWU_STACK_HEAP_DIRECTION_TOP)
#define hwu_stack_heap_deallocate_to_maker(heap, maker) hwu_stack_heap_deallocate_ex(heap, maker, HWU_STACK_HEAP_DIRECTION_TOP)
#define hwu_stack_heap_get_maker(heap)                  hwu_stack_heap_get_maker_ex(heap, HWU_STACK_HEAP_DIRECTION_TOP)

#ifdef __cplusplus
}
#endif

#endif  /* HWU_MEMORY_STACK_HEAP_H_ */

