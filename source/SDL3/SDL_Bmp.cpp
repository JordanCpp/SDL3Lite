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

#include <SDL3Lite/SDL3/SDL_Bmp.hpp>
#include <SDL3Lite/Application.hpp>
#include <SDL3Lite/BmpLoader.hpp>
#include <SDL3Lite/SDL3/SDL_Surface.hpp>

SDL_Surface* SDL_LoadBMP(const char* file)
{
	return SDL_LoadBMPImplementation(SDL::GetApplication().GetResult(), file);
}

SDL_Surface* SDL_LoadBMPImplementation(SDL::Result& result, const char* file)
{
	SDL::BmpLoader bmpLoader(result);

	if (bmpLoader.Reset(file))
	{
		SDL_Surface* result = new SDL_Surface(bmpLoader.GetSize(), SDL_PIXELFORMAT_RGB24);

		int width  = result->GetSurface()->GetSize().x;
		int heigth = result->GetSurface()->GetSize().y;
		int bpp    = result->GetSurface()->GetBpp();

		size_t bytes = width * heigth * bpp;
		uint8_t* dst = &result->GetSurface()->GetPixels()[0];
		uint8_t* src = bmpLoader.GetPixels();

		for (size_t i = 0; i < bytes; i += bpp)
		{
			dst[i + 0] = src[i + 0];
			dst[i + 1] = src[i + 1];
			dst[i + 2] = src[i + 2];
		}

		return result;
	}

	return NULL;
}
