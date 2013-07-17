#include "hw/memory/allocator.h"
#include <stddef.h>
#include <stdlib.h>
#include "hw/config.h"
#include "hw/utility.h"

#ifdef hw_malloc
#   undef hw_malloc
#endif

#ifdef hw_malloc_aligned
#   undef hw_malloc_aligned
#endif

#ifdef hw_free
#   undef hw_free
#endif

void* hw_malloc(hw32 size)
{
	return hw_malloc_aligned(size, HW_DEFAULT_ALIGNMENT);
}

void* hw_malloc_aligned(hw32 size, hw32 alignment)
{
#if defined(HW_PLATFORM_MSVC)
	return _aligned_malloc(size, alignment);
#else
	return memalign(alignment, size);
#endif
}

void hw_free(void* p)
{
#if defined(HW_PLATFORM_MSVC)
	_aligned_free(p);
#else
	free(p);
#endif
}

#ifndef HW_RELEASE

void* hw_malloc_debug(hw32 size, const char* file, int line)
{
    /* TODO */
    (void)file;
    (void)line;

	return hw_malloc(size);
}

void* hw_malloc_aligned_debug(hw32 size, hw32 alignment, const char* file, int line)
{
    /* TODO */
    (void)file;
    (void)line;

	return hw_malloc_aligned(size, alignment);
}

void hw_free_debug(void* p)
{
	hw_free(p);
}

#endif

