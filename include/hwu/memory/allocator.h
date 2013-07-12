#ifndef HWU_MEMORY_ALLOCATOR_H_
#define HWU_MEMORY_ALLOCATOR_H_

#include "hwu/platform.h"
#include "hwu/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* メモリ確保関数型定義 */
typedef void* (*hwu_allocator_t)(hwu32 size);
typedef void  (*hwu_deallocator_t)(void* p);
typedef void* (*hwu_allocator_aligned_t)(hwu32 size, hwu32 alignment);
typedef void  (*hwu_deallocator_aligned_t)(void* p);

extern void* hwu_malloc(hwu32 size);
extern void* hwu_malloc_aligned(hwu32 size, hwu32 alignment);
extern void  hwu_free(void* p);

#ifndef HWU_RELEASE

extern void* hwu_malloc_debug(hwu32 size, const char* file, int line);
extern void* hwu_malloc_aligned_debug(hwu32 size, hwu32 alignment, const char* file, int line);
extern void  hwu_free_debug(void* p);

#define hwu_malloc(size)		            hwu_malloc_debug(size, __FILE__, __LINE__)
#define hwu_malloc_aligned(size, alignment) hwu_malloc_aligned_debug(size, alignment, __FILE__, __LINE__)
#define hwu_free(p)				            hwu_free_debug(p)

#endif

#ifdef __cplusplus
}
#endif

#endif  /* HWU_MEMORY_ALLOCATOR_H_ */
