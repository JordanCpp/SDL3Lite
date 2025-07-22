/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <string.h>
#include <SDL3/StdStr.h>

size_t SDL_strlen(const char* source)
{
	return strlen(source);
}

size_t SDL_strlcpy(char* dst, const char* src, size_t size)
{
    size_t srcLen = 0;

    while (src[srcLen] != '\0')
    {
        srcLen++;
    }

    if (size == 0) 
    {
        return srcLen;
    }

    size_t i;

    for (i = 0; i < size - 1 && src[i] != '\0'; i++) {
        dst[i] = src[i];
    }

    dst[i] = '\0';

    return srcLen;
}

size_t SDL_strlcat(char* dst, const char* src, size_t size) 
{
    size_t dstLen = 0;
    size_t srcLen = 0;

    while (dstLen < size && dst[dstLen] != '\0') 
    {
        dstLen++;
    }

    while (src[srcLen] != '\0') 
    {
        srcLen++;
    }

    if (dstLen == size) 
    {
        return size + srcLen;
    }

    size_t i;

    for (i = 0; i < size - dstLen - 1 && src[i] != '\0'; i++) 
    {
        dst[dstLen + i] = src[i];
    }

    dst[dstLen + i] = '\0';

    return dstLen + srcLen;
}
