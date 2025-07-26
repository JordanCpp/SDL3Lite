/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_PixPaint_hpp
#define SDL3Lite_PixPaint_hpp

#include <SDL3/Point.h>
#include <SDL3/Rect.h>
#include <SDL3/Pixels.h>
#include <SDL3/Surface.hpp>

class PixelPainter
{
public:
	void Clear(Surface* dest, const SDL_Color& color, Uint8 index);
	void Point(Surface* dest, float x, float y, const SDL_Color& color, Uint8 index);
	void Points(Surface* dest, const SDL_FPoint* points, int count, const SDL_Color& color, Uint8 index);
	void FillRect(Surface* dest, const SDL_FRect* rect, const SDL_Color& color, Uint8 index);
	void FillRects(Surface* dest, const SDL_FRect* rects, int count, const SDL_Color& color, Uint8 index);
	void Rect(Surface* dest, const SDL_FRect* rect, const SDL_Color& color, Uint8 index);
	void Line(Surface* dest, float px1, float py1, float px2, float py2, const SDL_Color& color, Uint8 index);
	
	// New alpha blending methods
	void PointAlpha(Surface* dest, float x, float y, const SDL_Color& color);
	void PointsAlpha(Surface* dest, const SDL_FPoint* points, int count, const SDL_Color& color);
	void FillRectAlpha(Surface* dest, const SDL_FRect* rect, const SDL_Color& color);
	void FillRectsAlpha(Surface* dest, const SDL_FRect* rects, int count, const SDL_Color& color);
	void RectAlpha(Surface* dest, const SDL_FRect* rect, const SDL_Color& color);
	void LineAlpha(Surface* dest, float px1, float py1, float px2, float py2, const SDL_Color& color);
private:
};

#endif
