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

#include <SDL3Lite/SDL3/SDL_Renderer.hpp>
#include <SDL3Lite/SDL3/SDL_Surface.hpp>
#include <SDL3Lite/Renders/OpenGL1/OpenGL1Texture.hpp>

SDL_Texture* SDL_CreateTexture(SDL_Renderer* renderer, SDL_PixelFormat format, SDL_TextureAccess access, int w, int h)
{
	SDL_Texture* texture = new SDL::OpenGL1Texture((SDL::OpenGL1Render&)renderer, SDL::Vec2i(w, h), 3);

	return texture;
}

void SDL_DestroyTexture(SDL_Texture* texture)
{
	delete texture;
}

bool SDL_UpdateTexture(SDL_Texture* texture, const SDL_Rect* rect, const void* pixels, int pitch)
{
	texture->Update(SDL::Vec2i(rect->x, rect->y), SDL::Vec2i(rect->w, rect->h), (uint8_t*)pixels, pitch);

	return true;
}

SDL_Texture* SDL_CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
{
	SDL_Texture* result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, surface->GetSurface()->GetSize().x, surface->GetSurface()->GetSize().y);

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = surface->GetSurface()->GetSize().x;
	rect.h = surface->GetSurface()->GetSize().y;

	SDL_UpdateTexture(result, &rect, (void*)&surface->GetSurface()->GetPixels()[0], surface->GetSurface()->GetBpp());
		
	return result;
}
