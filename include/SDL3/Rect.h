/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3_Rect_h
#define SDL3_Rect_h

typedef struct SDL_FRect
{
    float x, y;
    float w, h;
} SDL_FRect;

typedef struct SDL_Rect
{
    int x, y;
    int w, h;
} SDL_Rect;

#endif
