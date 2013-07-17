#ifndef HW_MEMORY_ALLOCATOR_H_
#define HW_MEMORY_ALLOCATOR_H_

#include "hw/platform.h"
#include "hw/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* メモリ確保関数型定義 */
typedef void* (*hw_allocator_t)(hw32 size);
typedef void  (*hw_deallocator_t)(void* p);
typedef void* (*hw_allocator_aligned_t)(hw32 size, hw32 alignment);
typedef void  (*hw_deallocator_aligned_t)(void* p);

extern void* hw_malloc(hw32 size);
extern void* hw_malloc_aligned(hw32 size, hw32 alignment);
extern void  hw_free(void* p);

#ifndef HW_RELEASE

extern void* hw_malloc_debug(hw32 size, const char* file, int line);
extern void* hw_malloc_aligned_debug(hw32 size, hw32 alignment, const char* file, int line);
extern void  hw_free_debug(void* p);

#define hw_malloc(size)		            hw_malloc_debug(size, __FILE__, __LINE__)
#define hw_malloc_aligned(size, alignment) hw_malloc_aligned_debug(size, alignment, __FILE__, __LINE__)
#define hw_free(p)				            hw_free_debug(p)

#endif

#ifdef __cplusplus
}
#endif

#endif  /* HW_MEMORY_ALLOCATOR_H_ */
