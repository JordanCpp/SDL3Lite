/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_BaseWindow_hpp
#define SDL3Lite_BaseWindow_hpp

#include <SDL3/Point.h>
#include <SDL3/ShortStr.hpp>

class BaseWindow
{
public:
	BaseWindow(const SDL_Point& pos, const SDL_Point& size, const char* title);
	const SDL_Point& GetPos();
	void SetPos(const SDL_Point& pos);
	const SDL_Point& GetSize();
	void SetSize(const SDL_Point& size);
	const char* GetTitle();
	void SetTitle(const char* title);
private:
	SDL_Point    _pos;
	SDL_Point    _size;
	ShortString  _title;
};

#endif
