/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3_Pixels_h
#define SDL3_Pixels_h

#include <SDL3/Types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SDL_PixelFormat
{
    SDL_PIXELFORMAT_UNKNOWN,

    SDL_PIXELFORMAT_INDEX8,

    SDL_PIXELFORMAT_RGB24,
    SDL_PIXELFORMAT_BGR24,

    SDL_PIXELFORMAT_BGRA32,
    SDL_PIXELFORMAT_ABGR32,

    SDL_PIXELFORMAT_RGBA32,
    SDL_PIXELFORMAT_ARGB32
} SDL_PixelFormat;

typedef struct SDL_Color
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} SDL_Color;

typedef struct SDL_Palette
{
    int        ncolors;   /**< number of elements in `colors`. */
    SDL_Color* colors;    /**< an array of colors, `ncolors` long. */
    Uint32     version;   /**< internal use only, do not touch. */
    int        refcount;  /**< internal use only, do not touch. */
} SDL_Palette;

#ifdef __cplusplus
}
#endif

#endif
