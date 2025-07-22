/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <SDL3/Dos16/MainWin.hpp>

MainWindow::MainWindow(Result& result, EventHandler& eventHandler, const SDL_Point& pos, const SDL_Point& size, const char* title, SDL_WindowFlags flags) :
	_flags(flags),
	_result(result),
	_eventHandler(eventHandler),
	_baseWindow(pos, size, title)
{
}

const SDL_Point& MainWindow::GetPos()
{
	return _baseWindow.GetPos();
}

void MainWindow::SetPos(const SDL_Point& pos)
{
	_baseWindow.SetPos(pos);
}

const SDL_Point& MainWindow::GetSize()
{
	return _baseWindow.GetSize();
}

void MainWindow::SetSize(const SDL_Point& size)
{
	_baseWindow.SetSize(size);
}

const char* MainWindow::GetTitle()
{
	return _baseWindow.GetTitle();
}

void MainWindow::SetTitle(const char* title)
{
	_baseWindow.SetTitle(title);
}

SDL_WindowFlags MainWindow::GetFlags()
{
	return _flags;
}
