/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3_Surface_h
#define SDL3_Surface_h

#include <SDL3/Pixels.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef Uint32 SDL_SurfaceFlags;

#define SDL_SURFACE_PREALLOCATED    0x00000001u /**< Surface uses preallocated pixel memory */
#define SDL_SURFACE_LOCK_NEEDED     0x00000002u /**< Surface needs to be locked to access pixels */
#define SDL_SURFACE_LOCKED          0x00000004u /**< Surface is currently locked */
#define SDL_SURFACE_SIMD_ALIGNED    0x00000008u /**< Surface uses pixel memory allocated with SDL_aligned_alloc() */

typedef struct SDL_Surface SDL_Surface;

struct SDL_Surface
{
    SDL_SurfaceFlags flags;     /**< The flags of the surface, read-only */
    SDL_PixelFormat format;     /**< The format of the surface, read-only */
    int w;                      /**< The width of the surface, read-only. */
    int h;                      /**< The height of the surface, read-only. */
    int pitch;                  /**< The distance in bytes between rows of pixels, read-only */
    void SDL_FAR* pixels;       /**< A pointer to the pixels of the surface, the pixels are writeable if non-NULL */
    int refcount;               /**< Application reference count, used when freeing surface */
    void* reserved;             /**< Reserved for internal use */
};

extern SDL_DECLSPEC SDL_Surface* SDLCALL SDL_CreateSurface(int width, int height, SDL_PixelFormat format);
extern SDL_DECLSPEC void         SDLCALL SDL_DestroySurface(SDL_Surface* surface);

#ifdef __cplusplus
}
#endif

#endif
