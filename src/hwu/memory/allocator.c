﻿#include "hwu/memory/allocator.h"
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

void* hwu_malloc(hwu32 size)
{
	return hwu_malloc_aligned(size, HWU_DEFAULT_ALIGNMENT);
}

void* hwu_malloc_aligned(hwu32 size, hwu32 alignment)
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

void* hwu_malloc_debug(hwu32 size, const char* file, int line)
{
    /* TODO */
    (void)file;
    (void)line;

	return hwu_malloc(size);
}

void* hwu_malloc_aligned_debug(hwu32 size, hwu32 alignment, const char* file, int line)
{
    /* TODO */
    (void)file;
    (void)line;

	return hwu_malloc_aligned(size, alignment);
}

void hwu_free_debug(void* p)
{
	hwu_free(p);
}

#endif

