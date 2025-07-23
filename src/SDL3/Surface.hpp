/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_Surface_hpp
#define SDL3Lite_Surface_hpp

#include <SDL3/Point.h>
#include <SDL3/Surface.h>

class Surface : public SDL_Surface
{
public:
	Surface(const SDL_Point& size, const SDL_PixelFormat pixelFormat);
	~Surface();
	int GetBpp();
	int GetPitch();
	SDL_PixelFormat GetPixelFormat();
	const SDL_Point& GetSize();
	Uint8 SDL_FAR* GetPixels();
private:
	SDL_Point _size;
};

#endif
