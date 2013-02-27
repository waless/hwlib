#ifndef HWU_MEMORY_ALLOCATOR_H_
#define HWU_MEMORY_ALLOCATOR_H_

#include "hwu/platform.h"
#include "hwu/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* メモリ確保関数型定義 */
typedef void* (*hwu_allocator_t)(size_t size);
typedef void  (*hwu_deallocator_t)(void* p);
typedef void* (*hwu_allocator_aligned_t)(size_t size, size_t alignment);
typedef void  (*hwu_deallocator_aligned_t)(void* p);

void* hwu_malloc(size_t size);
void* hwu_malloc_aligned(size_t size, size_t alignment);
void  hwu_free(void* p);

#ifndef HWU_RELEASE

void* hwu_malloc_debug(size_t size, const char* file, int line);
void* hwu_malloc_aligned_debug(size_t size, size_t alignment, const char* file, int line);
void  hwu_free_debug(void* p);

#define hwu_malloc(size)		            hwu_malloc_debug(size, __FILE__, __LINE__)
#define hwu_malloc_aligned(size, alignment) hwu_malloc_aligned_debug(size, alignment, __FILE__, __LINE__)
#define hwu_free(p)				            hwu_free_debug(p)

#endif

#ifdef __cplusplus
}
#endif

#endif  /* HWU_MEMORY_ALLOCATOR_H_ */
