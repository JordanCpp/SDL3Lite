/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <assert.h>
#include <SDL3/StdMath.h>
#include <SDL3/StdMem.h>
#include <SDL3/PixPaint.hpp>

#define PIXEL_BGR(pixels, offset, color) *(Uint32*)(pixels + offset) = (color.b << 0) | (color.g << 8) | (color.r << 16)
#define PIXEL_RGB(pixels, offset, color) *(Uint32*)(pixels + offset) = (color.r << 0) | (color.g << 8) | (color.b << 16)

void PixelPainter::Clear(Surface* dest, const SDL_Color& color, Uint8 index, SDL_PixelFormat sourceFormat)
{
	assert(dest);

	size_t w                   = dest->GetSize().x;
	size_t h                   = dest->GetSize().y;
	Uint8 SDL_FAR* pixels      = dest->GetPixels();
	SDL_PixelFormat destFormat = dest->GetPixelFormat();

	if (destFormat == SDL_PIXELFORMAT_INDEX8)
	{
		SDL_memset(pixels, index, w * h);
		return;
	}

	Uint8 srcR = 0;
	Uint8 srcG = 0;
	Uint8 srcB = 0;
	Uint8 srcA = 0;

	switch (sourceFormat)
	{
	case SDL_PIXELFORMAT_RGB24:
	case SDL_PIXELFORMAT_RGBA32:
	case SDL_PIXELFORMAT_ARGB32:
	case SDL_PIXELFORMAT_INDEX8:
		srcR = color.r; 
		srcG = color.g; 
		srcB = color.b; 
		srcA = color.a;
		break;

	case SDL_PIXELFORMAT_BGR24:
	case SDL_PIXELFORMAT_BGRA32:
	case SDL_PIXELFORMAT_ABGR32:
		srcR = color.b; 
		srcG = color.g; 
		srcB = color.r; 
		srcA = color.a;
		break;

	default:
		srcR = color.r; 
		srcG = color.g; 
		srcB = color.b; 
		srcA = color.a;
		break;
	}

	switch (destFormat)
	{
	case SDL_PIXELFORMAT_RGB24:
		for (size_t i = 0; i < w * h * 3; i += 3)
		{
			pixels[i + 0] = srcR;
			pixels[i + 1] = srcG;
			pixels[i + 2] = srcB;
		}
		break;

	case SDL_PIXELFORMAT_BGR24:
		for (size_t i2 = 0; i2 < w * h * 3; i2 += 3)
		{
			pixels[i2 + 0] = srcB;
			pixels[i2 + 1] = srcG;
			pixels[i2 + 2] = srcR;
		}
		break;

	case SDL_PIXELFORMAT_RGBA32:
	{
		for (size_t i = 0; i < w * h * 4; i += 4)
		{
			pixels[i + 0] = srcR;
			pixels[i + 1] = srcG;
			pixels[i + 2] = srcB;
			pixels[i + 3] = srcA;
		}
	}
	break;

	case SDL_PIXELFORMAT_BGRA32:
	{
		for (size_t i = 0; i < w * h * 4; i += 4)
		{
			pixels[i + 0] = srcB;
			pixels[i + 1] = srcG;
			pixels[i + 2] = srcR;
			pixels[i + 3] = srcA;
		}
	}
	break;

	case SDL_PIXELFORMAT_ARGB32:
	{
		for (size_t i = 0; i < w * h * 4; i += 4)
		{
			pixels[i + 0] = srcA;
			pixels[i + 1] = srcR;
			pixels[i + 2] = srcG;
			pixels[i + 3] = srcB;
		}
	}
	break;

	case SDL_PIXELFORMAT_ABGR32:
	{
		for (size_t i = 0; i < w * h * 4; i += 4)
		{
			pixels[i + 0] = srcA;
			pixels[i + 1] = srcB;
			pixels[i + 2] = srcG;
			pixels[i + 3] = srcR;
		}
	}
	break;

	default:
		assert(false && "Unsupported destination format");
		break;
	}
}

void PixelPainter::Point(Surface* dest, float x, float y, const SDL_Color& color, Uint8 index, SDL_PixelFormat sourceFormat)
{
	assert(dest);

	size_t width = dest->GetSize().x;
	size_t height = dest->GetSize().y;
	Uint8 SDL_FAR* pixels = dest->GetPixels();
	SDL_PixelFormat destFormat = dest->GetPixelFormat();

	if (x < 0 || y < 0 || x >= width || y >= height) {
		return;
	}

	size_t pixelX = (size_t)x;
	size_t pixelY = (size_t)y;

	Uint8 srcR, srcG, srcB, srcA;
	switch (sourceFormat) {
	case SDL_PIXELFORMAT_RGB24:
	case SDL_PIXELFORMAT_RGBA32:
		srcR = color.r; 
		srcG = color.g; 
		srcB = color.b; 
		srcA = color.a;
		break;
	case SDL_PIXELFORMAT_BGR24:
	case SDL_PIXELFORMAT_BGRA32:
		srcR = color.b; 
		srcG = color.g; 
		srcB = color.r; 
		srcA = color.a;
		break;
	case SDL_PIXELFORMAT_ARGB32:
		srcR = color.g; 
		srcG = color.b; 
		srcB = color.a; 
		srcA = color.r;
		break;
	case SDL_PIXELFORMAT_ABGR32:
		srcR = color.a; 
		srcG = color.b; 
		srcB = color.g; 
		srcA = color.r;
		break;
	default:
		srcR = color.r; 
		srcG = color.g; 
		srcB = color.b; 
		srcA = color.a;
		break;
	}

	switch (destFormat)
	{
	case SDL_PIXELFORMAT_INDEX8:
	{
		size_t idx = width * pixelY + pixelX;
		pixels[idx] = index;
	}
	break;

	case SDL_PIXELFORMAT_RGB24:
	{
		size_t idx = (width * pixelY + pixelX) * 3;
		pixels[idx + 0] = srcR;
		pixels[idx + 1] = srcG;
		pixels[idx + 2] = srcB;
	}
	break;

	case SDL_PIXELFORMAT_BGR24:
	{
		size_t idx = (width * pixelY + pixelX) * 3;
		pixels[idx + 0] = srcB;
		pixels[idx + 1] = srcG;
		pixels[idx + 2] = srcR;
	}
	break;

	case SDL_PIXELFORMAT_RGBA32:
	{
		size_t idx = (width * pixelY + pixelX) * 4;
		pixels[idx + 0] = srcR;
		pixels[idx + 1] = srcG;
		pixels[idx + 2] = srcB;
		pixels[idx + 3] = srcA;
	}
	break;

	case SDL_PIXELFORMAT_BGRA32:
	{
		size_t idx = (width * pixelY + pixelX) * 4;
		pixels[idx + 0] = srcB;
		pixels[idx + 1] = srcG;
		pixels[idx + 2] = srcR;
		pixels[idx + 3] = srcA;
	}
	break;

	case SDL_PIXELFORMAT_ARGB32:
	{
		size_t idx = (width * pixelY + pixelX) * 4;
		pixels[idx + 0] = srcA;
		pixels[idx + 1] = srcR;
		pixels[idx + 2] = srcG;
		pixels[idx + 3] = srcB;
	}
	break;

	case SDL_PIXELFORMAT_ABGR32:
	{
		size_t idx = (width * pixelY + pixelX) * 4;
		pixels[idx + 0] = srcA;
		pixels[idx + 1] = srcB;
		pixels[idx + 2] = srcG;
		pixels[idx + 3] = srcR;
	}
	break;
	}
}

void PixelPainter::FillRect(Surface* dst, const SDL_FRect* rect, const SDL_Color& color, Uint8 index, SDL_PixelFormat srcFormat)
{
	assert(dst);
	assert(rect);

	size_t dstWidth           = dst->GetSize().x;
	size_t dstHeight          = dst->GetSize().y;
	Uint8 SDL_FAR* pixels     = dst->GetPixels();
	SDL_PixelFormat dstFormat = dst->GetPixelFormat();

	int x1 = SDL_max(0, (int)rect->x);
	int y1 = SDL_max(0, (int)rect->y);
	int x2 = SDL_min((int)dstWidth, (int)(rect->x + rect->w));
	int y2 = SDL_min((int)dstHeight, (int)(rect->y + rect->h));

	if (x1 >= x2 || y1 >= y2) return;

	int fillWidth  = x2 - x1;
	int fillHeight = y2 - y1;

	Uint8 srcR, srcG, srcB, srcA;
	switch (srcFormat) 
	{
	case SDL_PIXELFORMAT_RGB24:
	case SDL_PIXELFORMAT_RGBA32:
		srcR = color.r; srcG = color.g; srcB = color.b; srcA = color.a;
		break;
	case SDL_PIXELFORMAT_BGR24:
	case SDL_PIXELFORMAT_BGRA32:
		srcR = color.b; srcG = color.g; srcB = color.r; srcA = color.a;
		break;
	case SDL_PIXELFORMAT_ARGB32:
		srcR = color.r; srcG = color.g; srcB = color.b; srcA = color.a;
		break;
	case SDL_PIXELFORMAT_ABGR32:
		srcR = color.r; srcG = color.g; srcB = color.b; srcA = color.a;
		break;
	default:
		srcR = color.r; srcG = color.g; srcB = color.b; srcA = color.a;
		break;
	}

	switch (dstFormat) 
	{
	case SDL_PIXELFORMAT_INDEX8:
	{
		for (int y = y1; y < y2; y++) {
			size_t rowStart = dstWidth * y + x1;
			SDL_memset(pixels + rowStart, index, fillWidth);
		}
	}
	break;

	case SDL_PIXELFORMAT_RGB24:
	{
		for (int y = y1; y < y2; y++) {
			size_t rowStart = (dstWidth * y + x1) * 3;
			for (int x = 0; x < fillWidth; x++) {
				size_t idx = rowStart + x * 3;
				pixels[idx + 0] = srcR;
				pixels[idx + 1] = srcG;
				pixels[idx + 2] = srcB;
			}
		}
	}
	break;

	case SDL_PIXELFORMAT_BGR24:
	{
		for (int y = y1; y < y2; y++) {
			size_t rowStart = (dstWidth * y + x1) * 3;
			for (int x = 0; x < fillWidth; x++) {
				size_t idx = rowStart + x * 3;
				pixels[idx + 0] = srcB;
				pixels[idx + 1] = srcG;
				pixels[idx + 2] = srcR;
			}
		}
	}
	break;

	case SDL_PIXELFORMAT_RGBA32:
	{
		for (int y = y1; y < y2; y++) {
			size_t rowStart = (dstWidth * y + x1) * 4;
			for (int x = 0; x < fillWidth; x++) {
				size_t idx = rowStart + x * 4;
				pixels[idx + 0] = srcR;
				pixels[idx + 1] = srcG;
				pixels[idx + 2] = srcB;
				pixels[idx + 3] = srcA;
			}
		}
	}
	break;

	case SDL_PIXELFORMAT_BGRA32:
	{
		for (int y = y1; y < y2; y++) {
			size_t rowStart = (dstWidth * y + x1) * 4;
			for (int x = 0; x < fillWidth; x++) {
				size_t idx = rowStart + x * 4;
				pixels[idx + 0] = srcB;
				pixels[idx + 1] = srcG;
				pixels[idx + 2] = srcR;
				pixels[idx + 3] = srcA;
			}
		}
	}
	break;

	case SDL_PIXELFORMAT_ARGB32:
	{
		for (int y = y1; y < y2; y++) {
			size_t rowStart = (dstWidth * y + x1) * 4;
			for (int x = 0; x < fillWidth; x++) {
				size_t idx = rowStart + x * 4;
				pixels[idx + 0] = srcA;
				pixels[idx + 1] = srcR;
				pixels[idx + 2] = srcG;
				pixels[idx + 3] = srcB;
			}
		}
	}
	break;

	case SDL_PIXELFORMAT_ABGR32:
	{
		for (int y = y1; y < y2; y++) {
			size_t rowStart = (dstWidth * y + x1) * 4;
			for (int x = 0; x < fillWidth; x++) {
				size_t idx = rowStart + x * 4;
				pixels[idx + 0] = srcA;
				pixels[idx + 1] = srcB;
				pixels[idx + 2] = srcG;
				pixels[idx + 3] = srcR;
			}
		}
	}
	break;
	}
}


void PixelPainter::Rect(Surface* dest, const SDL_FRect* rect, const SDL_Color& color, Uint8 index, SDL_PixelFormat sourceFormat)
{
	assert(dest);
	assert(rect);

	size_t destWidth = dest->GetSize().x;
	size_t destHeight = dest->GetSize().y;
	Uint8 SDL_FAR* pixels = dest->GetPixels();
	SDL_PixelFormat destFormat = dest->GetPixelFormat();

	int x1 = (int)rect->x;
	int y1 = (int)rect->y;
	int x2 = (int)(rect->x + rect->w - 1);
	int y2 = (int)(rect->y + rect->h - 1);

	if (x1 < 0) x1 = 0;
	if (y1 < 0) y1 = 0;
	if (x2 >= (int)destWidth) x2  = (int)destWidth  - 1;
	if (y2 >= (int)destHeight) y2 = (int)destHeight - 1;

	if (x1 > x2 || y1 > y2) return;

	Uint8 srcR, srcG, srcB, srcA;
	switch (sourceFormat) {
	case SDL_PIXELFORMAT_RGB24:
	case SDL_PIXELFORMAT_RGBA32:
		srcR = color.r; 
		srcG = color.g; 
		srcB = color.b; 
		srcA = color.a;
		break;
	case SDL_PIXELFORMAT_BGR24:
	case SDL_PIXELFORMAT_BGRA32:
		srcR = color.b; 
		srcG = color.g; 
		srcB = color.r; 
		srcA = color.a;
		break;
	case SDL_PIXELFORMAT_ARGB32:
		srcR = color.g; 
		srcG = color.b; 
		srcB = color.a; 
		srcA = color.r;
		break;
	case SDL_PIXELFORMAT_ABGR32:
		srcR = color.a; 
		srcG = color.b; 
		srcB = color.g; 
		srcA = color.r;
		break;
	default:
		srcR = color.r; 
		srcG = color.g; 
		srcB = color.b; 
		srcA = color.a;
		break;
	}

	switch (destFormat) {
	case SDL_PIXELFORMAT_INDEX8:
	{
		for (int x = x1; x <= x2; x++) 
		{
			pixels[destWidth * y1 + x] = index;

			if (y1 != y2) 
			{
				pixels[destWidth * y2 + x] = index;
			}
		}

		for (int y = y1 + 1; y < y2; y++) 
		{
			pixels[destWidth * y + x1] = index;

			if (x1 != x2)
			{
				pixels[destWidth * y + x2] = index;
			}
		}
	}
	break;

	case SDL_PIXELFORMAT_RGB24:
	{
		for (int x = x1; x <= x2; x++)
		{
			size_t idx1 = (destWidth * y1 + x) * 3;
			pixels[idx1 + 0] = srcR;
			pixels[idx1 + 1] = srcG;
			pixels[idx1 + 2] = srcB;

			if (y1 != y2)
			{
				size_t idx2 = (destWidth * y2 + x) * 3;
				pixels[idx2 + 0] = srcR;
				pixels[idx2 + 1] = srcG;
				pixels[idx2 + 2] = srcB;
			}
		}

		for (int y = y1 + 1; y < y2; y++) 
		{
			size_t idx1 = (destWidth * y + x1) * 3;
			pixels[idx1 + 0] = srcR;
			pixels[idx1 + 1] = srcG;
			pixels[idx1 + 2] = srcB;

			if (x1 != x2) 
			{
				size_t idx2 = (destWidth * y + x2) * 3;
				pixels[idx2 + 0] = srcR;
				pixels[idx2 + 1] = srcG;
				pixels[idx2 + 2] = srcB;
			}
		}
	}
	break;

	case SDL_PIXELFORMAT_BGR24:
	{
		for (int x = x1; x <= x2; x++) 
		{
			size_t idx1 = (destWidth * y1 + x) * 3;
			pixels[idx1 + 0] = srcB;
			pixels[idx1 + 1] = srcG;
			pixels[idx1 + 2] = srcR;

			if (y1 != y2)
			{
				size_t idx2 = (destWidth * y2 + x) * 3;
				pixels[idx2 + 0] = srcB;
				pixels[idx2 + 1] = srcG;
				pixels[idx2 + 2] = srcR;
			}
		}

		for (int y = y1 + 1; y < y2; y++) 
		{
			size_t idx1 = (destWidth * y + x1) * 3;
			pixels[idx1 + 0] = srcB;
			pixels[idx1 + 1] = srcG;
			pixels[idx1 + 2] = srcR;

			if (x1 != x2) 
			{
				size_t idx2 = (destWidth * y + x2) * 3;
				pixels[idx2 + 0] = srcB;
				pixels[idx2 + 1] = srcG;
				pixels[idx2 + 2] = srcR;
			}
		}
	}
	break;
	case SDL_PIXELFORMAT_RGBA32:
	{
		for (int x = x1; x <= x2; x++)
		{
			size_t idx1 = (destWidth * y1 + x) * 4;
			pixels[idx1 + 0] = srcR;
			pixels[idx1 + 1] = srcG;
			pixels[idx1 + 2] = srcB;
			pixels[idx1 + 3] = srcA;

			if (y1 != y2) 
			{
				size_t idx2 = (destWidth * y2 + x) * 4;
				pixels[idx2 + 0] = srcR;
				pixels[idx2 + 1] = srcG;
				pixels[idx2 + 2] = srcB;
				pixels[idx2 + 3] = srcA;
			}
		}

		for (int y = y1 + 1; y < y2; y++) 
		{
			size_t idx1 = (destWidth * y + x1) * 4;
			pixels[idx1 + 0] = srcR;
			pixels[idx1 + 1] = srcG;
			pixels[idx1 + 2] = srcB;
			pixels[idx1 + 3] = srcA;

			if (x1 != x2) 
			{
				size_t idx2 = (destWidth * y + x2) * 4;
				pixels[idx2 + 0] = srcR;
				pixels[idx2 + 1] = srcG;
				pixels[idx2 + 2] = srcB;
				pixels[idx2 + 3] = srcA;
			}
		}
	}
	break;
	}
}

void PixelPainter::Line(Surface* dst, float px1, float py1, float px2, float py2,const SDL_Color& color, Uint8 index, SDL_PixelFormat sourceFormat)
{
	assert(dst);

	int width                 = dst->GetSize().x;
	int height                = dst->GetSize().y;
	Uint8 SDL_FAR* pixels     = dst->GetPixels();
	SDL_PixelFormat dstFormat = dst->GetPixelFormat();

	int x1 = (int)px1;
	int y1 = (int)py1;
	int x2 = (int)px2;
	int y2 = (int)py2;

	Uint8 srcR = 0;
	Uint8 srcG = 0;
	Uint8 srcB = 0;
	Uint8 srcA = 0;

	switch (sourceFormat) 
	{
	case SDL_PIXELFORMAT_RGB24:
	case SDL_PIXELFORMAT_RGBA32:
		srcR = color.r; 
		srcG = color.g; 
		srcB = color.b; 
		srcA = color.a;
		break;
	case SDL_PIXELFORMAT_BGR24:
	case SDL_PIXELFORMAT_BGRA32:
		srcR = color.b; 
		srcG = color.g; 
		srcB = color.r; 
		srcA = color.a;
		break;
	default:
		srcR = color.r; 
		srcG = color.g; 
		srcB = color.b; 
		srcA = color.a;
		break;
	}

	int dx = SDL_abs(x2 - x1);
	int dy = SDL_abs(y2 - y1);
	int sx = (x1 < x2) ? 1 : -1;
	int sy = (y1 < y2) ? 1 : -1;
	int err = dx - dy;

	switch (dstFormat) 
	{
	case SDL_PIXELFORMAT_INDEX8:
		while (true) 
		{
			if (x1 >= 0 && y1 >= 0 && x1 < width && y1 < height) 
			{
				size_t idx = width * y1 + x1;
				pixels[idx] = index;
			}

			if (x1 == x2 && y1 == y2) break;

			int e2 = 2 * err;
			if (e2 > -dy) { err -= dy; x1 += sx; }
			if (e2 < dx) { err += dx; y1 += sy; }
		}
		break;

	case SDL_PIXELFORMAT_RGB24:
		while (true) 
		{
			if (x1 >= 0 && y1 >= 0 && x1 < width && y1 < height) 
			{
				size_t idx = (width * y1 + x1) * 3;
				pixels[idx + 0] = srcR;
				pixels[idx + 1] = srcG;
				pixels[idx + 2] = srcB;
			}

			if (x1 == x2 && y1 == y2) break;

			int e2 = 2 * err;
			if (e2 > -dy) { err -= dy; x1 += sx; }
			if (e2 < dx) { err += dx; y1 += sy; }
		}
		break;

	case SDL_PIXELFORMAT_BGR24:
		while (true)
		{
			if (x1 >= 0 && y1 >= 0 && x1 < width && y1 < height) 
			{
				size_t idx = (width * y1 + x1) * 3;
				pixels[idx + 0] = srcB;
				pixels[idx + 1] = srcG;
				pixels[idx + 2] = srcR;
			}

			if (x1 == x2 && y1 == y2) break;

			int e2 = 2 * err;
			if (e2 > -dy) { err -= dy; x1 += sx; }
			if (e2 < dx) { err += dx; y1 += sy; }
		}
		break;

	case SDL_PIXELFORMAT_RGBA32:
		while (true)
		{
			if (x1 >= 0 && y1 >= 0 && x1 < width && y1 < height) 
			{
				size_t idx = (width * y1 + x1) * 4;
				pixels[idx + 0] = srcR;
				pixels[idx + 1] = srcG;
				pixels[idx + 2] = srcB;
				pixels[idx + 3] = srcA;
			}

			if (x1 == x2 && y1 == y2) break;

			int e2 = 2 * err;
			if (e2 > -dy) { err -= dy; x1 += sx; }
			if (e2 < dx) { err += dx; y1 += sy; }
		}
		break;
	}
}
