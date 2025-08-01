/*
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef SDL3Lite_Surface_h
#define SDL3Lite_Surface_h

#include <SDL3/Pixels.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef Uint32 SDL_SurfaceFlags;

#define SDL_SURFACE_PREALLOCATED    (1) /**< Surface uses preallocated pixel memory */
#define SDL_SURFACE_LOCK_NEEDED     (2) /**< Surface needs to be locked to access pixels */
#define SDL_SURFACE_LOCKED          (3) /**< Surface is currently locked */
#define SDL_SURFACE_SIMD_ALIGNED    (4) /**< Surface uses pixel memory allocated with SDL_aligned_alloc() */

struct SDL_Surface
{
    SDL_SurfaceFlags flags;     /**< The flags of the surface, read-only */
    SDL_PixelFormat format;     /**< The format of the surface, read-only */
    int w;                      /**< The width of the surface, read-only. */
    int h;                      /**< The height of the surface, read-only. */
    int pitch;                  /**< The distance in bytes between rows of pixels, read-only */
    void* pixels;               /**< A pointer to the pixels of the surface, the pixels are writeable if non-NULL */
    int refcount;               /**< Application reference count, used when freeing surface */
    void* reserved;             /**< Reserved for internal use */
};

typedef struct SDL_Surface SDL_Surface;

extern SDL_DECLSPEC SDL_Surface* SDLCALL SDL_CreateSurface(int width, int height, SDL_PixelFormat format);
extern SDL_DECLSPEC void         SDLCALL SDL_DestroySurface(SDL_Surface* surface);
extern SDL_DECLSPEC bool         SDLCALL SDL_SetSurfaceColorKey(SDL_Surface* surface, bool enabled, Uint32 key);

#define SDL_ALPHA_OPAQUE_FLOAT (1.0f)
#define SDL_ALPHA_OPAQUE       (255)

extern SDL_DECLSPEC SDL_Surface* SDLCALL SDL_LoadBMP(const char* file);

#ifdef __cplusplus
}
#endif

#endif
