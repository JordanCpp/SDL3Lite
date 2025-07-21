
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
#endif

#if defined(__TURBOC__)
    #define SDL_FAR far
#else
    #define SDL_FAR
#endif

#endif
