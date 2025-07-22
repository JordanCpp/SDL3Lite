/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <SDL3/BaseRndr.hpp>

BaseRender::BaseRender(const char* name)
{
	_color.r = 0;
	_color.g = 0;
	_color.b = 0;
	_color.a = 255;

	_name.Assign(name);
}

const SDL_Color& BaseRender::GetColor()
{
	return _color;
}

void BaseRender::SetColor(const SDL_Color& color)
{
	_color = color;
}

const char* BaseRender::GetName()
{
	return _name.GetStr();
}

void BaseRender::SetName(const char* title)
{
	_name.Assign(title);
}
