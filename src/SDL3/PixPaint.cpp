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

// 32-bit RGBA format macros
#define PIXEL_RGBA(pixels, offset, color) *(Uint32*)(pixels + offset) = (color.r << 0) | (color.g << 8) | (color.b << 16) | (color.a << 24)
#define PIXEL_BGRA(pixels, offset, color) *(Uint32*)(pixels + offset) = (color.b << 0) | (color.g << 8) | (color.r << 16) | (color.a << 24)
#define PIXEL_ARGB(pixels, offset, color) *(Uint32*)(pixels + offset) = (color.a << 0) | (color.r << 8) | (color.g << 16) | (color.b << 24)
#define PIXEL_ABGR(pixels, offset, color) *(Uint32*)(pixels + offset) = (color.a << 0) | (color.b << 8) | (color.g << 16) | (color.r << 24)

// Alpha blending function - classic Porter-Duff "over" operation
inline SDL_Color BlendAlpha(const SDL_Color& src, const SDL_Color& dst)
{
    if (src.a == 255) return src;  // Fully opaque source
    if (src.a == 0) return dst;    // Fully transparent source
    
    // Normalize alpha to 0-1 range for calculation
    Uint16 srcAlpha = src.a;
    Uint16 invAlpha = 255 - srcAlpha;
    
    SDL_Color result;
    result.r = (Uint8)((src.r * srcAlpha + dst.r * invAlpha) / 255);
    result.g = (Uint8)((src.g * srcAlpha + dst.g * invAlpha) / 255);
    result.b = (Uint8)((src.b * srcAlpha + dst.b * invAlpha) / 255);
    result.a = (Uint8)((src.a * srcAlpha + dst.a * invAlpha) / 255);
    
    return result;
}

// Extract color from 32-bit pixel based on format
inline SDL_Color ExtractPixel32(Uint32 pixel, SDL_PixelFormat format)
{
    SDL_Color color;
    switch (format)
    {
    case SDL_PIXELFORMAT_RGBA32:
        color.r = (pixel >> 0) & 0xFF;
        color.g = (pixel >> 8) & 0xFF;
        color.b = (pixel >> 16) & 0xFF;
        color.a = (pixel >> 24) & 0xFF;
        break;
    case SDL_PIXELFORMAT_BGRA32:
        color.b = (pixel >> 0) & 0xFF;
        color.g = (pixel >> 8) & 0xFF;
        color.r = (pixel >> 16) & 0xFF;
        color.a = (pixel >> 24) & 0xFF;
        break;
    case SDL_PIXELFORMAT_ARGB32:
        color.a = (pixel >> 0) & 0xFF;
        color.r = (pixel >> 8) & 0xFF;
        color.g = (pixel >> 16) & 0xFF;
        color.b = (pixel >> 24) & 0xFF;
        break;
    case SDL_PIXELFORMAT_ABGR32:
        color.a = (pixel >> 0) & 0xFF;
        color.b = (pixel >> 8) & 0xFF;
        color.g = (pixel >> 16) & 0xFF;
        color.r = (pixel >> 24) & 0xFF;
        break;
    default:
        color.r = color.g = color.b = color.a = 0;
        break;
    }
    return color;
}

// Set 32-bit pixel with proper format
inline void SetPixel32(Uint8* pixels, size_t offset, const SDL_Color& color, SDL_PixelFormat format)
{
    switch (format)
    {
    case SDL_PIXELFORMAT_RGBA32:
        PIXEL_RGBA(pixels, offset, color);
        break;
    case SDL_PIXELFORMAT_BGRA32:
        PIXEL_BGRA(pixels, offset, color);
        break;
    case SDL_PIXELFORMAT_ARGB32:
        PIXEL_ARGB(pixels, offset, color);
        break;
    case SDL_PIXELFORMAT_ABGR32:
        PIXEL_ABGR(pixels, offset, color);
        break;
    }
}

void PixelPainter::Clear(Surface* dest, const SDL_Color& color, Uint8 index)
{
	assert(dest);

	size_t w                  = dest->GetSize().x;
	size_t h                  = dest->GetSize().y;
	size_t bpp                = dest->GetBpp();
	Uint8 SDL_FAR* pixels     = dest->GetPixels();
	SDL_PixelFormat format    = dest->GetPixelFormat();

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
	else if (bpp == 4)
	{
		for (size_t i = 0; i < w * h * bpp; i += bpp)
		{
			SetPixel32(pixels, i, color, format);
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

// Alpha blending implementations
void PixelPainter::PointAlpha(Surface* dest, float x, float y, const SDL_Color& color)
{
	assert(dest);

	size_t width              = dest->GetSize().x;
	size_t height             = dest->GetSize().y;
	size_t bpp                = dest->GetBpp();
	Uint8 SDL_FAR* pixels     = dest->GetPixels();
	SDL_PixelFormat format    = dest->GetPixelFormat();

	size_t idx = (width * (size_t)y + (size_t)x) * bpp;

	if (idx < width * height * bpp && bpp == 4)
	{
		// Read existing pixel
		Uint32 existingPixel = *(Uint32*)(pixels + idx);
		SDL_Color existingColor = ExtractPixel32(existingPixel, format);
		
		// Blend colors
		SDL_Color blendedColor = BlendAlpha(color, existingColor);
		
		// Write blended pixel
		SetPixel32(pixels, idx, blendedColor, format);
	}
}

void PixelPainter::PointsAlpha(Surface* dest, const SDL_FPoint* points, int count, const SDL_Color& color)
{
	assert(dest);
	assert(points);
	assert(count > 0);

	for (int i = 0; i < count; i++)
	{
		PointAlpha(dest, points[i].x, points[i].y, color);
	}
}

void PixelPainter::FillRectAlpha(Surface* dest, const SDL_FRect* rect, const SDL_Color& color)
{
	assert(dest);
	assert(rect);

	size_t width              = dest->GetSize().x;
	size_t height             = dest->GetSize().y;
	size_t bpp                = dest->GetBpp();
	Uint8 SDL_FAR* pixels     = dest->GetPixels();
	SDL_PixelFormat format    = dest->GetPixelFormat();

	size_t x = (size_t)rect->x;
	size_t y = (size_t)rect->y;
	size_t w = (size_t)rect->w;
	size_t h = (size_t)rect->h;

	if (bpp == 4)
	{
		for (size_t i = 0; i < w; i++)
		{
			for (size_t j = 0; j < h; j++)
			{
				size_t idx = (width * (y + j) + (x + i)) * bpp;

				if (idx < width * height * bpp)
				{
					// Read existing pixel
					Uint32 existingPixel = *(Uint32*)(pixels + idx);
					SDL_Color existingColor = ExtractPixel32(existingPixel, format);
					
					// Blend colors
					SDL_Color blendedColor = BlendAlpha(color, existingColor);
					
					// Write blended pixel
					SetPixel32(pixels, idx, blendedColor, format);
				}
			}
		}
	}
}

void PixelPainter::FillRectsAlpha(Surface* dest, const SDL_FRect* rects, int count, const SDL_Color& color)
{
	assert(dest);
	assert(rects);
	assert(count > 0);

	for (int i = 0; i < count; i++)
	{
		FillRectAlpha(dest, &rects[i], color);
	}
}

void PixelPainter::RectAlpha(Surface* dest, const SDL_FRect* rect, const SDL_Color& color)
{
	assert(dest);
	assert(rect);

	// Draw rectangle outline using alpha blending lines
	// Top edge
	LineAlpha(dest, rect->x, rect->y, rect->x + rect->w - 1, rect->y, color);
	// Bottom edge  
	LineAlpha(dest, rect->x, rect->y + rect->h - 1, rect->x + rect->w - 1, rect->y + rect->h - 1, color);
	// Left edge
	LineAlpha(dest, rect->x, rect->y, rect->x, rect->y + rect->h - 1, color);
	// Right edge
	LineAlpha(dest, rect->x + rect->w - 1, rect->y, rect->x + rect->w - 1, rect->y + rect->h - 1, color);
}

void PixelPainter::LineAlpha(Surface* dest, float px1, float py1, float px2, float py2, const SDL_Color& color)
{
	assert(dest);

	int x1 = (int)px1;
	int y1 = (int)py1;
	int x2 = (int)px2;
	int y2 = (int)py2;

	size_t width              = dest->GetSize().x;
	size_t height             = dest->GetSize().y;
	size_t bpp                = dest->GetBpp();
	Uint8 SDL_FAR* pixels     = dest->GetPixels();
	SDL_PixelFormat format    = dest->GetPixelFormat();

	if (bpp != 4) return; // Alpha blending only for 32-bit formats

	int deltaX = SDL_abs(x2 - x1);
	int deltaY = SDL_abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;

	// Plot end point
	size_t idx = (width * y2 + x2) * bpp;
	if (idx < width * height * bpp)
	{
		Uint32 existingPixel = *(Uint32*)(pixels + idx);
		SDL_Color existingColor = ExtractPixel32(existingPixel, format);
		SDL_Color blendedColor = BlendAlpha(color, existingColor);
		SetPixel32(pixels, idx, blendedColor, format);
	}

	// Bresenham line algorithm with alpha blending
	while (x1 != x2 || y1 != y2)
	{
		idx = (width * y1 + x1) * bpp;

		if (idx < width * height * bpp)
		{
			Uint32 existingPixel = *(Uint32*)(pixels + idx);
			SDL_Color existingColor = ExtractPixel32(existingPixel, format);
			SDL_Color blendedColor = BlendAlpha(color, existingColor);
			SetPixel32(pixels, idx, blendedColor, format);
		}

		int error2 = error * 2;

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
