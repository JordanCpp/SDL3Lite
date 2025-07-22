/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3_StdMath_h
#define SDL3_StdMath_h

#include <SDL3/Types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern SDL_DECLSPEC double SDLCALL SDL_sqrt(double x);
extern SDL_DECLSPEC float  SDLCALL SDL_sqrtf(float x);
extern SDL_DECLSPEC double SDLCALL SDL_pow(double x, double y);
extern SDL_DECLSPEC float  SDLCALL SDL_powf(float x, float y);

#ifdef __cplusplus
}
#endif

#endif
