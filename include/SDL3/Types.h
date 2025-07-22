/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3_Types_h
#define SDL3_Types_h

#include <stddef.h>

#if defined(__TURBOC__)
    #include <alloc.h> 
#endif

#if defined(__TURBOC__)
    typedef int bool;
    #define true  (1)
    #define false (0)
#else
    #include <stdbool.h>
#endif

#define SDLCALL

#if defined(_WIN32)
    #define SDL3LITE_EXPORT __declspec(dllexport)
    #define SDL3LITE_IMPORT __declspec(dllimport)
#elif defined(__unix__)
    #define SDL3LITE_EXPORT __attribute__((visibility("default")))
    #define SDL3LITE_IMPORT
#else
    #define SDL3LITE_EXPORT
    #define SDL3LITE_IMPORT
#endif

#if defined(SDL3LITE_STATIC)
    #define SDL_DECLSPEC
#else
    #if defined(SDL3LITE_SHARED)
        #define SDL_DECLSPEC SDL3LITE_EXPORT
    #else
        #define SDL_DECLSPEC SDL3LITE_IMPORT
    #endif
#endif 

typedef unsigned char  Uint8;
typedef signed char    Sint8;

typedef unsigned short Uint16;
typedef signed short   Sint16;

typedef unsigned int   Uint32;
typedef signed int     Sint32;

#if defined(__TURBOC__)
    typedef Uint32  Uint64;
    typedef Sint32  Sint64;
#else
    typedef unsigned long int   Uint64;
    typedef signed long int     Sint64;
#endif

#if defined(__TURBOC__)
    #define SDL_FAR far
#else
    #define SDL_FAR
#endif

#endif
