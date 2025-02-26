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

#ifndef SDL3Lite_SDL_Texture_h
#define SDL3Lite_SDL_Texture_h

#include <SDL3/SDL_Types.h>
#include <SDL3/SDL_Surface.h>
#include <SDL3/SDL_Renderer.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef enum SDL_TextureAccess
    {
        SDL_TEXTUREACCESS_STATIC,    /**< Changes rarely, not lockable */
        SDL_TEXTUREACCESS_STREAMING, /**< Changes frequently, lockable */
        SDL_TEXTUREACCESS_TARGET     /**< Texture can be used as a render target */
    } SDL_TextureAccess;

typedef struct SDL_Texture  SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;

extern SDL_DECLSPEC SDL_Texture* SDLCALL SDL_CreateTexture(SDL_Renderer* renderer, SDL_PixelFormat format, SDL_TextureAccess access, int w, int h);
extern SDL_DECLSPEC void         SDLCALL SDL_DestroyTexture(SDL_Texture* texture);
extern SDL_DECLSPEC bool         SDLCALL SDL_UpdateTexture(SDL_Texture* texture, const SDL_Rect* rect, const void* pixels, int pitch);
extern SDL_DECLSPEC SDL_Texture* SDLCALL SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface);

#ifdef __cplusplus
}
#endif

#endif
