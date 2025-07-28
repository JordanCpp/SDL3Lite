/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_Win32_SoftWin_hpp
#define SDL3Lite_Win32_SoftWin_hpp

#include <SDL3/Window.hpp>
#include <SDL3/Win32/MainWin.hpp>

class SoftwareWindow : public SDL_Window
{
public:
	SoftwareWindow(Result& result, EventHandler& eventHandler, const SDL_Point& pos, const SDL_Point& size, const char* title, SDL_WindowFlags mode, SDL_PixelFormat format);
	Surface* GetSurface();
	const SDL_Point& GetPos();
	void SetPos(const SDL_Point& pos);
	const SDL_Point& GetSize();
	void SetSize(const SDL_Point& size);
	const char* GetTitle();
	void SetTitle(const char* title);
	SDL_WindowFlags GetFlags();
	bool Present();
	void PollEvents();
private:
	BITMAPINFO _bitmapInfo;
	Surface    _surface;
	MainWindow _mainWindow;
};

#endif
