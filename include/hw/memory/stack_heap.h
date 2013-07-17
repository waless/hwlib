#ifndef HW_MEMORY_STACK_HEAP_H_
#define HW_MEMORY_STACK_HEAP_H_

#include "hw/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_hw_stack_heap_t
{
	hwptr_t memory_address;
	hwptr_t top_address;
	hwptr_t bottom_address;
	hw32    memory_size;
} hw_stack_heap_t;

typedef enum tag_hw_stack_heap_direction_t
{
	HW_STACK_HEAP_DIRECTION_TOP = 0,
	HW_STACK_HEAP_DIRECTION_BOTTOM,
} hw_stack_heap_direction_t;

typedef hwptr_t hw_stack_heap_maker_t;

extern void hw_stack_heap_initialize(hw_stack_heap_t* heap, void* memory, hw32 size);
extern void hw_stack_heap_finalize(hw_stack_heap_t* heap);
extern void* hw_stack_heap_allocate_ex(hw_stack_heap_t* heap, hw32 size, hw32 alignment, hw_stack_heap_direction_t direction);
extern void hw_stack_heap_deallocate_to_maker_ex(hw_stack_heap_t* heap, hw_stack_heap_maker_t maker, hw_stack_heap_direction_t direction);
extern hw_stack_heap_maker_t hw_stack_heap_get_maker_ex(hw_stack_heap_t* heap, hw_stack_heap_direction_t direction);

/* アラインメント、確保方向を意識しない時の為の定義 */
#define hw_stack_heap_allocate(heap, size)             hw_stack_heap_allocate_ex(heap, size, sizeof(double), HW_STACK_HEAP_DIRECTION_TOP)
#define hw_stack_heap_deallocate_to_maker(heap, maker) hw_stack_heap_deallocate_ex(heap, maker, HW_STACK_HEAP_DIRECTION_TOP)
#define hw_stack_heap_get_maker(heap)                  hw_stack_heap_get_maker_ex(heap, HW_STACK_HEAP_DIRECTION_TOP)

#ifdef __cplusplus
}
#endif

#endif  /* HW_MEMORY_STACK_HEAP_H_ */

