/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_BaseRndr_hpp
#define SDL3Lite_BaseRndr_hpp

#include <SDL3/Pixels.h>
#include <SDL3/ShortStr.hpp>

class BaseRender
{
public:
	BaseRender(const char* name);
	const SDL_Color& GetColor();
	void SetColor(const SDL_Color& pos);
	const char* GetName();
	void SetName(const char* title);
private:
	SDL_Color    _color;
	ShortString  _name;
};

#endif
