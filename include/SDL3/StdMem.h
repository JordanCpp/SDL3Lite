/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3_StdMem_h
#define SDL3_StdMem_h

#include <SDL3/Types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern SDL_DECLSPEC void SDL_FAR* SDLCALL SDL_malloc(size_t bytes);
extern SDL_DECLSPEC void          SDLCALL SDL_free(void SDL_FAR* ptr);
extern SDL_DECLSPEC void SDL_FAR* SDLCALL SDL_memset(void SDL_FAR* dst, int c, size_t len);
extern SDL_DECLSPEC void*         SDLCALL SDL_memcpy(void* dst, const void* src, size_t len);

#ifdef __cplusplus
}
#endif

#endif
