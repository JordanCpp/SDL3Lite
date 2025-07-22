/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3_StdStr_h
#define SDL3_StdStr_h

#include <SDL3/Types.h>

size_t SDL_strlen(const char* source);
size_t SDL_strlcpy(char* dst, const char* src, size_t size);
size_t SDL_strlcat(char* dst, const char* src, size_t size);

#endif
