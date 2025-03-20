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

#include <SDL3Lite/Application.hpp>
#include <SDL3Lite/SDL3/SDL_Renderer.hpp>
#include <SDL3Lite/Renders/OpenGL1/OpenGL1Render.hpp>
#include <SDL3Lite/Renders/Software/SoftwareRender.hpp>
#include <SDL3Lite/Renders/Software/SurfaceRender.hpp>
#include <assert.h>

SDL_Renderer* SDL_CreateRendererImplementation(SDL::Result& result, SDL_Window* window, const char* name)
{
	assert(window);

	SDL_Renderer* renderer = NULL;

	if (window->GetFlags() == SDL_WINDOW_OPENGL)
	{
		renderer = new SDL::OpenGL1Render(result, window);
	}
	else
	{
		renderer = new SDL::SoftwareRender(window);
	}

	return renderer;
}

SDL_Renderer* SDL_CreateSoftwareRenderer(SDL_Surface* surface)
{
	return new SDL::SurfaceRender((SDL::Surface*)surface);
}

SDL_Renderer* SDL_CreateRenderer(SDL_Window *window, const char *name)
{
	return SDL_CreateRendererImplementation(SDL::GetApplication().GetResult(), window, name);
}

bool SDL_CreateWindowAndRenderer(const char* title, int width, int height, SDL_WindowFlags window_flags, SDL_Window** window, SDL_Renderer** renderer)
{
	SDL_Window* singleWindow = SDL_CreateWindowImplementation(
		SDL::GetApplication().GetWindows(),
		SDL::GetApplication().GetOpenGLAttributes(),
		SDL::GetApplication().GetResult(),
		SDL::GetApplication().GetEventHandler(),
		title, width, height, window_flags);

	*window = singleWindow;

	SDL_Renderer* singleRenderer = SDL_CreateRendererImplementation(
		SDL::GetApplication().GetResult(),
		singleWindow,
		"");

	*renderer = singleRenderer;

	return true;
}

void SDL_DestroyRenderer(SDL_Renderer* renderer)
{
	assert(renderer);

	delete renderer;
}

bool SDL_RenderPresent(SDL_Renderer* renderer)
{
	assert(renderer);

	renderer->Present();

	return true;
}

bool SDL_SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	assert(renderer);

	renderer->SetColor(SDL::Color(r, g, b, a));

	return true;
}

bool SDL_RenderClear(SDL_Renderer* renderer)
{
	assert(renderer);

	renderer->Clear();

	return true;
}

void SDL_RenderFillRect(SDL_Renderer* renderer, SDL_FRect* rect)
{
	assert(renderer);

	renderer->FillRect(SDL::Vec2f(rect->x, rect->y), SDL::Vec2f(rect->w, rect->h));
}

bool SDL_RenderTexture(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_FRect* srcrect, const SDL_FRect* dstrect)
{
	assert(renderer);
	assert(texture);

	SDL::Rect2f srcRect;
	SDL::Rect2f dstRect;

	if (srcrect == NULL)
	{
		srcRect = SDL::Rect2f(0, 0, (float)texture->GetSize().x, (float)texture->GetSize().y);
	}
	else
	{
		srcRect = srcrect;
	}

	if (dstrect == NULL)
	{
		dstRect = SDL::Rect2f(0, 0, (float)renderer->GetSize().x, (float)renderer->GetSize().y);
	}
	else
	{
		dstRect = dstrect;
	}

	renderer->Draw(texture, dstRect, srcRect);
		
	return true;
}

bool SDL_GetRenderViewport(SDL_Renderer* renderer, SDL_Rect* rect)
{
	assert(renderer);
	assert(rect);

	rect->x = 0;
	rect->y = 0;
	rect->w = renderer->GetSize().x;
	rect->h = renderer->GetSize().y;

	return true;
}
