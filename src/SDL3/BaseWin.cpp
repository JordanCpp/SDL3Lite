/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <SDL3/BaseWin.hpp>

BaseWindow::BaseWindow(const SDL_Point& pos, const SDL_Point& size, const char* title) :
	_pos(pos),
	_size(size)
{
	_title.Append(title);
}

const SDL_Point& BaseWindow::GetPos()
{
	return _pos;
}

void BaseWindow::SetPos(const SDL_Point& pos)
{
	_pos = pos;
}

const SDL_Point& BaseWindow::GetSize()
{
	return _size;
}

void BaseWindow::SetSize(const SDL_Point& size)
{
	_size = size;
}

const char* BaseWindow::GetTitle()
{
	return _title.Str();
}

void BaseWindow::SetTitle(const char* title)
{
	_title.Clear();
	_title.Append(title);
}
