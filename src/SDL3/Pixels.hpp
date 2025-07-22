/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_Pixels_hpp
#define SDL3Lite_Pixels_hpp

#include <SDL3/Surface.h>

int PixelFormatToBytesPerPixels(const SDL_PixelFormat pixelFormat);
SDL_PixelFormat GetDefaultPixelFormat();
Uint8 FindClosestIndex(SDL_Color target, SDL_Color* palette, size_t size);

#endif
