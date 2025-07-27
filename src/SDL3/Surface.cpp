/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <SDL3/Surface.hpp>
#include <SDL3/StdMem.h>
#include <SDL3/Pixels.hpp>

Surface::Surface(const SDL_Point& size, const SDL_PixelFormat pixelFormat) :
	_size(size)
{
	int bpp  = PixelFormatToBytesPerPixels(pixelFormat);

	flags    = 0;
	format   = pixelFormat;
	w        = _size.x;
	h        = _size.y;
	pitch    = w * bpp;
	pixels   = SDL_malloc(w * h * bpp);
	refcount = 0;
	reserved = NULL;
}

Surface::~Surface()
{
	SDL_free(pixels);
}

int Surface::GetBpp()
{
	return PixelFormatToBytesPerPixels(format);
}

int Surface::GetPitch()
{
	return pitch;
}

SDL_PixelFormat Surface::GetPixelFormat()
{
	return format;
}

const SDL_Point& Surface::GetSize()
{
	return _size;
}

Uint8 SDL_FAR* Surface::GetPixels()
{
	return (Uint8 SDL_FAR*)pixels;
}

SDL_Surface* SDL_CreateSurface(int width, int height, SDL_PixelFormat format)
{
	SDL_Point size = { width , height };

	return new Surface(size, format);
}

void SDL_DestroySurface(SDL_Surface* surface)
{
	delete surface;
}
