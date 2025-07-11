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

#ifndef SDL3Lite_Renderer_hpp
#define SDL3Lite_Renderer_hpp

#include <SDL3/SDL_video.h>
#include <SDL3Lite/Vec2i.hpp>
#include <SDL3Lite/Rect2f.hpp>
#include <SDL3Lite/Color.hpp>
#include <SDL3Lite/Result.hpp>
#include <SDL3Lite/Texture.hpp>

struct SDL_Renderer
{
public:
	virtual ~SDL_Renderer() {};
	virtual SDL_WindowFlags GetFlags() = 0;
	virtual const SDL::Vec2i& GetSize() = 0;
	virtual void Present() = 0;
	virtual void SetColor(const SDL::Color& color) = 0;
	virtual void Clear() = 0;
	virtual void FillRect(const SDL::Vec2f& pos, const SDL::Vec2f& size) = 0;
	virtual void Line(const SDL::Vec2f& first, const SDL::Vec2f& last) = 0;
	virtual void Draw(SDL_Texture* texture, const SDL::Rect2f& dst, const SDL::Rect2f& src) = 0;
};

SDL_Renderer* SDL_CreateRendererImplementation(SDL::Result& result, SDL_Window* window, const char* name);

#endif
