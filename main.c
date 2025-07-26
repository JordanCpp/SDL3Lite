/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <SDL3/SDL.h>
#include <SDL3/PixPaint.hpp>
#include <SDL3/Pixels.hpp>

int main()
{
	// Create RGBA surface for alpha blending demo
	SDL_PixelFormat format = GetDefaultRGBAPixelFormat();
	SDL_Surface* surface = SDL_CreateSurface(640, 480, format);
	
	if (surface)
	{
		PixelPainter painter;
		
		// Clear to white background
		SDL_Color white = {255, 255, 255, 255};
		painter.Clear((Surface*)surface, white, 0);
		
		// Draw some semi-transparent rectangles
		SDL_FRect rect1 = {50, 50, 200, 150};
		SDL_Color red_alpha = {255, 0, 0, 128};  // 50% transparent red
		painter.FillRectAlpha((Surface*)surface, &rect1, red_alpha);
		
		SDL_FRect rect2 = {150, 100, 200, 150};
		SDL_Color blue_alpha = {0, 0, 255, 128}; // 50% transparent blue
		painter.FillRectAlpha((Surface*)surface, &rect2, blue_alpha);
		
		// Draw some alpha-blended lines
		SDL_Color green_alpha = {0, 255, 0, 192}; // 75% transparent green
		painter.LineAlpha((Surface*)surface, 10, 10, 300, 200, green_alpha);
		painter.LineAlpha((Surface*)surface, 300, 10, 10, 200, green_alpha);
		
		SDL_DestroySurface(surface);
	}
	
	return 0;
}
