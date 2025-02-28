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
#include <SDL3Lite/Platforms/OpenGLWindow.hpp>
#include <SDL3Lite/Platforms/SoftwareWindow.hpp>
#include <assert.h>

SDL_Window* SDL_CreateWindowImplementation(std::vector<SDL_Window*>& windows, SDL::OpenGLAttributes& openGLAttributes, SDL::Result& result, SDL::EventHandler& eventHandler, const char* title, int w, int h, size_t flags)
{
	SDL_Window* window = NULL;

	if (flags == SDL_WINDOW_OPENGL)
	{
		window = new SDL::OpenGLWindow(openGLAttributes, result, eventHandler, SDL::Vec2i(0, 0), SDL::Vec2i(w, h), title, flags);
	}
	else
	{
		window = new SDL::SoftwareWindow(result, eventHandler, SDL::Vec2i(0, 0), SDL::Vec2i(w, h), title, flags);
	}

	if (window)
	{
		windows.push_back(window);
	}

	return window;
}

SDL_Window* SDL_CreateWindow(const char* title, int w, int h, size_t flags)
{
	return SDL_CreateWindowImplementation(
		SDL::GetApplication().GetWindows(),
		SDL::GetApplication().GetOpenGLAttributes(),
		SDL::GetApplication().GetResult(),
		SDL::GetApplication().GetEventHandler(),
		title, w, h, flags);
}

void SDL_DestroyWindow(SDL_Window* window)
{
	assert(window);

	delete window;
}
