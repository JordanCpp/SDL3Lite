/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <SDL3/Win32/SoftWin.hpp>

SoftwareWindow::SoftwareWindow(Result& result, EventHandler& eventHandler, const SDL_Point& pos, const SDL_Point& size, const char* title, SDL_WindowFlags mode, SDL_PixelFormat format) :
	_surface(size, format),
	_mainWindow(result, eventHandler, pos, size, title, mode)
{
}

Surface* SoftwareWindow::GetSurface()
{
	return &_surface;
}

const SDL_Point& SoftwareWindow::GetPos()
{
	return _mainWindow.GetPos();
}

void SoftwareWindow::SetPos(const SDL_Point& pos)
{
	_mainWindow.SetPos(pos);
}

const SDL_Point& SoftwareWindow::GetSize()
{
	return _mainWindow.GetSize();
}

void SoftwareWindow::SetSize(const SDL_Point& size)
{
	_mainWindow.SetSize(size);
}

const char* SoftwareWindow::GetTitle()
{
	return _mainWindow.GetTitle();
}

void SoftwareWindow::SetTitle(const char* title)
{
	_mainWindow.SetTitle(title);
}

SDL_WindowFlags SoftwareWindow::GetFlags()
{
	return _mainWindow.GetFlags();
}

bool SoftwareWindow::Present()
{
	DWORD w = (DWORD)_surface.GetSize().x;
	DWORD h = (DWORD)_surface.GetSize().y;

	_bitmapInfo.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	_bitmapInfo.bmiHeader.biWidth       = (LONG)w;
	_bitmapInfo.bmiHeader.biHeight      = -(LONG)h;
	_bitmapInfo.bmiHeader.biPlanes      = 1;
	_bitmapInfo.bmiHeader.biBitCount    = _surface.GetBpp() * 8;
	_bitmapInfo.bmiHeader.biCompression = BI_RGB;
	
	SetDIBitsToDevice(_mainWindow.GetHdc(), 0, 0, w, h, 0, 0, 0, h, _surface.GetPixels(), &_bitmapInfo, DIB_RGB_COLORS);

	return true;
}

void SoftwareWindow::PollEvents()
{
	_mainWindow.PollEvents();
}
