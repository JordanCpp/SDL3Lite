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
#include <SDL3Lite/RenderCreator.hpp>
#include <SDL3Lite/SDL3/SDL_Renderer.hpp>
#include <SDL3Lite/SDL3/SDL_Window.hpp>
#include <assert.h>

SDL_Renderer::SDL_Renderer(SDL::Application& application, SDL::IRender* render) :
	_application(application),
	_render(render)
{
}

SDL_Renderer::~SDL_Renderer()
{
	delete _render;
}

SDL::IRender* SDL_Renderer::GetRender()
{
	return _render;
}

SDL_Renderer* SDL_CreateRenderer(SDL_Window *window, const char *name)
{
	assert(window);

	SDL::IRender* render = SDL::GetApplication().GetRenderCreator().Create(window->GetWindow());
	assert(render);

	SDL_Renderer* result = new SDL_Renderer(SDL::GetApplication(), render);
	assert(result);

	return result;
}

void SDL_DestroyRenderer(SDL_Renderer* renderer)
{
	assert(renderer);

	delete renderer;
}

bool SDL_RenderPresent(SDL_Renderer* renderer)
{
	assert(renderer);
	assert(renderer->GetRender());

	renderer->GetRender()->Present();

	return true;
}

bool SDL_SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	assert(renderer);
	assert(renderer->GetRender());

	renderer->GetRender()->SetColor(SDL::Color(r, g, b, a));

	return true;
}

bool SDL_RenderClear(SDL_Renderer* renderer)
{
	assert(renderer);
	assert(renderer->GetRender());

	renderer->GetRender()->Clear();

	return true;
}

void SDL_RenderFillRect(SDL_Renderer* renderer, SDL_FRect* rect)
{
	assert(renderer);
	assert(renderer->GetRender());

	renderer->GetRender()->FillRect(SDL::Vec2f(rect->x, rect->y), SDL::Vec2f(rect->w, rect->h));
}
