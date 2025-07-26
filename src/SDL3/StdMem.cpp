/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <stdlib.h>
#include <string.h>
#include <SDL3/StdMem.h>

void SDL_FAR* SDL_malloc(size_t bytes)
{
	void SDL_FAR* result = NULL;

	if (bytes == 0)
	{
		return result;
	}
	else
	{
#if defined(__TURBOC__)
		result = farmalloc(bytes);
#else
		result = malloc(bytes);
#endif
		return result;
	}
}

void SDL_free(void SDL_FAR* ptr)
{

#if defined(__TURBOC__)
	farfree(ptr);
#else
	free(ptr);
#endif

}

void SDL_FAR* SDL_memset(void SDL_FAR* dst, int c, size_t len)
{

#if defined(__TURBOC__)
	Uint8 SDL_FAR* p = (Uint8 SDL_FAR*)dst;

	while (len--)
	{
		*p++ = (Uint8)c;
	}

	return dst;
#else
	return memset(dst, c, len);
#endif

}

void* SDL_memcpy(void* dst, const void* src, size_t len)
{
	return memcpy(dst, src, len);
}
