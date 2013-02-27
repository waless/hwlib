#include "hwu/memory/allocator.h"
#include <stddef.h>
#include <stdlib.h>
#include "hwu/config.h"
#include "hwu/utility.h"

#ifdef hwu_malloc
#   undef hwu_malloc
#endif

#ifdef hwu_malloc_aligned
#   undef hwu_malloc_aligned
#endif

#ifdef hwu_free
#   undef hwu_free
#endif

void* hwu_malloc(size_t size)
{
	return hwu_malloc_aligned(size, HWU_DEFAULT_ALIGNMENT);
}

void* hwu_malloc_aligned(size_t size, size_t alignment)
{
#if defined(HWU_PLATFORM_MSVC)
	return _aligned_malloc(size, alignment);
#else
	return memalign(alignment, size);
#endif
}

void hwu_free(void* p)
{
#if defined(HWU_PLATFORM_MSVC)
	_aligned_free(p);
#else
	free(p);
#endif
}

#ifndef HWU_RELEASE

void* hwu_malloc_debug(size_t size, const char* file, int line)
{
	return hwu_malloc(size);
}

void* hwu_malloc_aligned_debug(size_t size, size_t alignment, const char* file, int line)
{
	return hwu_malloc_aligned(size, alignment);
}

void  hwu_free_debug(void* p)
{
	hwu_free(p);
}

#endif
