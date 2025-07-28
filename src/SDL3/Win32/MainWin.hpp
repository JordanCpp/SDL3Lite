/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_Win32_MainWin_hpp
#define SDL3Lite_Win32_MainWin_hpp

#include <SDL3/Window.h>
#include <SDL3/Result.hpp>
#include <SDL3/BaseWin.hpp>
#include <SDL3/EventH.hpp>
#include <SDL3/Win32/WinError.hpp>

class MainWindow
{
public:
	MainWindow(Result& result, EventHandler& eventHandler, const SDL_Point& pos, const SDL_Point& size, const char* title, SDL_WindowFlags mode);
	~MainWindow();
	const SDL_Point& GetPos();
	void SetPos(const SDL_Point& pos);
	const SDL_Point& GetSize();
	void SetSize(const SDL_Point& size);
	const char* GetTitle();
	void SetTitle(const char* title);
	SDL_WindowFlags GetFlags();
	void PollEvents();
public:
	HWND GetHwnd();
	HDC GetHdc();
private:
	LRESULT CALLBACK Handler(UINT Message, WPARAM WParam, LPARAM LParam);
	static LRESULT CALLBACK WndProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam);
	Result* _result;
	EventHandler* _eventHandler;
	HWND            _hwnd;
	HDC             _hdc;
	WindowError     _windowError;
	MSG             _message;
	BaseWindow      _baseWindow;
	WNDCLASSA       _windowClass;
	SDL_WindowFlags _WindowFlags;
};

#endif
