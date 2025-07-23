/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <assert.h>
#include <SDL3/StdMath.h>
#include <SDL3/PixPaint.hpp>

#define PIXEL_BGR(pixels, offset, color) *(Uint32*)(pixels + offset) = (color.b << 0) | (color.g << 8) | (color.r << 16)
#define PIXEL_RGB(pixels, offset, color) *(Uint32*)(pixels + offset) = (color.r << 0) | (color.g << 8) | (color.b << 16)

void PixelPainter::Clear(Surface* dest, const SDL_Color& color, Uint8 index)
{
	assert(dest);

	size_t w              = dest->GetSize().x;
	size_t h              = dest->GetSize().y;
	size_t bpp            = dest->GetBpp();
	Uint8 SDL_FAR* pixels = dest->GetPixels();

	if (bpp == 1)
	{
		for (size_t i = 0; i < w * h; i++)
		{
			pixels[i] = index;
		}
	}
	else if (bpp == 3)
	{
		for (size_t i = 0; i < w * h * bpp; i += bpp)
		{
#if defined(_WIN32)
			PIXEL_BGR(pixels, i, color);
#else
			PIXEL_RGB(pixels, i, color);
#endif
		}
	}
}

void PixelPainter::Point(Surface* dest, float x, float y, const SDL_Color& color, Uint8 index)
{
	assert(dest);

	size_t width          = dest->GetSize().x;
	size_t height         = dest->GetSize().y;
	size_t bpp            = dest->GetBpp();
	Uint8 SDL_FAR* pixels = dest->GetPixels();

	size_t idx = (width * (size_t)y + (size_t)x) * bpp;

	if (idx < width * height * bpp)
	{
		if (bpp == 1)
		{
			pixels[idx] = index;
		}
		else if (bpp == 3)
		{
#if defined(_WIN32)
			PIXEL_BGR(pixels, idx, color);
#else
			PIXEL_RGB(pixels, idx, color);
#endif
		}
	}
}

void PixelPainter::Points(Surface* dest, const SDL_FPoint* points, int count, const SDL_Color& color, Uint8 index)
{
	assert(dest);
	assert(points);
	assert(count > 0);

	size_t width          = dest->GetSize().x;
	size_t height         = dest->GetSize().y;
	size_t bpp            = dest->GetBpp();
	Uint8 SDL_FAR* pixels = dest->GetPixels();

	for (size_t i = 0; i < (size_t)count; i++)
	{
		size_t idx = (width * (size_t)points[i].y + (size_t)points[i].x) * bpp;

		if (idx < width * height * bpp)
		{
			if (bpp == 1)
			{
				pixels[idx] = index;
			}
			else if (bpp == 3)
			{
#if defined(_WIN32)
				PIXEL_BGR(pixels, idx, color);
#else
				PIXEL_RGB(pixels, idx, color);
#endif
			}
		}
	}
}

void PixelPainter::FillRect(Surface* dest, const SDL_FRect* rect, const SDL_Color& color, Uint8 index)
{
	assert(dest);
	assert(rect);

	size_t width          = dest->GetSize().x;
	size_t height         = dest->GetSize().y;
	size_t bpp            = dest->GetBpp();
	Uint8 SDL_FAR* pixels = dest->GetPixels();

	size_t x = (size_t)rect->x;
	size_t y = (size_t)rect->y;
	size_t w = (size_t)rect->w;
	size_t h = (size_t)rect->h;

	if (bpp == 1)
	{
		for (size_t i = 0; i < w; i++)
		{
			for (size_t j = 0; j < h; j++)
			{
				size_t idx = (width * (y + j) + (x + i));

				if (idx < width * height)
				{
					pixels[idx] = index;
				}
			}
		}
	}
	else if (bpp == 3)
	{
		for (size_t i = 0; i < w; i++)
		{
			for (size_t j = 0; j < h; j++)
			{
				size_t idx = (width * (y + j) + (x + i)) * bpp;

				if (idx < width * height * bpp)
				{
#if defined(_WIN32)
					PIXEL_BGR(pixels, idx, color);
#else
					PIXEL_RGB(pixels, idx, color);
#endif
				}
			}
		}
	}
}

void PixelPainter::FillRects(Surface* dest, const SDL_FRect* rects, int count, const SDL_Color& color, Uint8 index)
{
	assert(dest);
	assert(rects);
	assert(count > 0);

	size_t width          = dest->GetSize().x;
	size_t height         = dest->GetSize().y;
	size_t bpp            = dest->GetBpp();
	Uint8 SDL_FAR* pixels = dest->GetPixels();

	for (size_t k = 0; k < (size_t)count; k++)
	{
		size_t x = (size_t)rects[k].x;
		size_t y = (size_t)rects[k].y;
		size_t w = (size_t)rects[k].w;
		size_t h = (size_t)rects[k].h;

		if (bpp == 1)
		{
			for (size_t i = 0; i < w; i++)
			{
				for (size_t j = 0; j < h; j++)
				{
					size_t idx = (width * (y + j) + (x + i)) * bpp;

					if (idx < width * height * bpp)
					{
						pixels[idx] = index;
					}
				}
			}
		}
		else if (bpp == 3)
		{
			for (size_t i = 0; i < w; i++)
			{
				for (size_t j = 0; j < h; j++)
				{
					size_t idx = (width * (y + j) + (x + i)) * bpp;

					if (idx < width * height * bpp)
					{
#if defined(_WIN32)
						PIXEL_BGR(pixels, idx, color);
#else
						PIXEL_RGB(pixels, idx, color);
#endif
					}
				}
			}
		}
	}
}

void PixelPainter::Rect(Surface* dest, const SDL_FRect* rect, const SDL_Color& color, Uint8 index)
{
	assert(dest);
	assert(rect);

	size_t width          = dest->GetSize().x;
	size_t height         = dest->GetSize().y;
	size_t bpp            = dest->GetBpp();
	Uint8 SDL_FAR* pixels = dest->GetPixels();

	size_t x = (size_t)rect->x;
	size_t y = (size_t)rect->y;
	size_t w = (size_t)rect->w;
	size_t h = (size_t)rect->h;

	if (bpp == 1)
	{
		for (size_t i = 0; i < w; i++)
		{
			for (size_t j = 0; j < h; j++)
			{
				size_t idx = (width * (y + j) + (x + i));

				if (idx < width * height)
				{
					pixels[idx] = index;
				}
			}
		}
	}
	else if (bpp == 3)
	{
		for (size_t i = 0; i < w; i++)
		{
			for (size_t j = 0; j < h; j++)
			{
				size_t idx = (width * (y + j) + (x + i)) * bpp;

				if (idx < width * height * bpp)
				{
#if defined(_WIN32)
					PIXEL_BGR(pixels, idx, color);
#else
					PIXEL_RGB(pixels, idx, color);
#endif
				}
			}
		}
	}
}

void PixelPainter::Line(Surface* dest, float px1, float py1, float px2, float py2, const SDL_Color& color, Uint8 index)
{
	int x1 = (int)px1;
	int y1 = (int)py1;

	int x2 = (int)px2;
	int y2 = (int)py2;

	size_t width          = dest->GetSize().x;
	size_t height         = dest->GetSize().y;
	size_t bpp            = dest->GetBpp();
	Uint8 SDL_FAR* pixels = dest->GetPixels();
	size_t idx            = 0;

	int deltaX;
	int deltaY;
	int signX;
	int signY;
	int error;
	int error2;

	deltaX = SDL_abs(x2 - x1);
	deltaY = SDL_abs(y2 - y1);
	signX = x1 < x2 ? 1 : -1;
	signY = y1 < y2 ? 1 : -1;

	error = deltaX - deltaY;

	idx = (width * (y2) + (x2)) * bpp;

	if (idx < width * height * bpp)
	{
		if (bpp == 1)
		{
			pixels[idx] = index;
		}
		else if (bpp == 3)
		{
#if defined(_WIN32)
			PIXEL_BGR(pixels, idx, color);
#else
			PIXEL_RGB(pixels, idx, color);
#endif
		}
	}

	if (bpp == 1)
	{
		while (x1 != x2 || y1 != y2)
		{
			idx = (width * (y1)+(x1));

			if (idx < width * height)
			{
				pixels[idx] = index;
			}

			error2 = error * 2;

			if (error2 > -deltaY)
			{
				error -= deltaY;
				x1 += signX;
			}

			if (error2 < deltaX)
			{
				error += deltaX;
				y1 += signY;
			}
		}
	}
	else if (bpp == 3)
	{
		while (x1 != x2 || y1 != y2)
		{
			idx = (width * (y1)+(x1)) * bpp;

			if (idx < width * height * bpp)
			{
                #if defined(_WIN32)
				    PIXEL_BGR(pixels, idx, color);
                #else
				    PIXEL_RGB(pixels, idx, color);
                #endif
			}

			error2 = error * 2;

			if (error2 > -deltaY)
			{
				error -= deltaY;
				x1 += signX;
			}

			if (error2 < deltaX)
			{
				error += deltaX;
				y1 += signY;
			}
		}
	}
}
