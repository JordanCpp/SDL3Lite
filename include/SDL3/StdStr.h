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

#ifdef __cplusplus
extern "C" {
#endif

extern SDL_DECLSPEC size_t SDLCALL SDL_strlen(const char* source);
extern SDL_DECLSPEC size_t SDLCALL SDL_strlcpy(char* dst, const char* src, size_t size);
extern SDL_DECLSPEC size_t SDLCALL SDL_strlcat(char* dst, const char* src, size_t size);

#ifdef __cplusplus
}
#endif

#endif
