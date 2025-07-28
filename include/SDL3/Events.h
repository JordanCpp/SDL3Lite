/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_SDL_Events_h
#define SDL3Lite_SDL_Events_h

#include <SDL3/Types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum SDL_EventType
{
    SDL_EVENT_FIRST = 0,
    SDL_EVENT_QUIT
} SDL_EventType;

typedef struct SDL_QuitEvent
{
    SDL_EventType type;
    Uint32        reserved;
    Uint64        timestamp;
} SDL_QuitEvent;

typedef union SDL_Event
{
    Uint32        type;
    SDL_QuitEvent quit;
} SDL_Event;

extern SDL_DECLSPEC int SDLCALL SDL_PollEvent(SDL_Event* dest);

#ifdef __cplusplus
}
#endif

#endif
