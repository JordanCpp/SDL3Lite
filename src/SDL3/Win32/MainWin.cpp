/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <SDL3/Win32/MainWin.hpp>

MainWindow::MainWindow(Result& result, EventHandler& eventHandler, const SDL_Point& pos, const SDL_Point& size, const char* title, SDL_WindowFlags mode) :
	_result(&result),
	_eventHandler(&eventHandler),
	_hdc(NULL),
	_hwnd(NULL),
	_baseWindow(pos, size, title),
	_WindowFlags(mode)
{
	memset(&_message, 0, sizeof(MSG));
	memset(&_windowClass, 0, sizeof(WNDCLASSA));

	_windowClass.style         = CS_HREDRAW | CS_VREDRAW;
	_windowClass.cbClsExtra    = 0;
	_windowClass.cbWndExtra    = 0;
	_windowClass.lpszClassName = GetTitle();
	_windowClass.hInstance     = GetModuleHandle(NULL);
	_windowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
	_windowClass.lpszMenuName  = NULL;
	_windowClass.lpfnWndProc   = WndProc;

	if (RegisterClass(&_windowClass) == NULL)
	{
		_result->Message(_windowError.GetErrorMessage());
		return;
	}

	DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;

	RECT rect;
	rect.left   = (LONG)_baseWindow.GetPos().x;
	rect.top    = (LONG)_baseWindow.GetPos().y;
	rect.right  = (LONG)_baseWindow.GetSize().x;
	rect.bottom = (LONG)_baseWindow.GetSize().y;

	if (!AdjustWindowRect(&rect, style, FALSE))
	{
		_result->Message(_windowError.GetErrorMessage());
		return;
	}

	int width  = rect.right  - rect.left;
	int height = rect.bottom - rect.top;

	_hwnd = CreateWindow(_windowClass.lpszClassName, GetTitle(), style, GetPos().x, GetPos().y, width, height, NULL, NULL, _windowClass.hInstance, NULL);

	if (_hwnd == NULL)
	{
		_result->Message(_windowError.GetErrorMessage());
		return;
	}

	_hdc = GetDC(_hwnd);

	if (_hdc == NULL)
	{
		_result->Message(_windowError.GetErrorMessage());
		return;
	}

#if defined(_WIN64)
	SetWindowLongPtr(_hwnd, GWLP_WNDPROC, (LONG_PTR)WndProc);
	SetWindowLongPtr(_hwnd, GWLP_USERDATA, (LONG_PTR)this);
#elif defined(_WIN32)
	SetWindowLong(_hwnd, GWL_WNDPROC, (LONG)WndProc);
	SetWindowLong(_hwnd, GWL_USERDATA, (LONG)this);
#endif  

}

MainWindow::~MainWindow()
{
	if (UnregisterClass(_windowClass.lpszClassName, _windowClass.hInstance) == FALSE)
	{
		_result->Message(_windowError.GetErrorMessage());
	}
	else
	{
		if (ReleaseDC(_hwnd, _hdc) == 0)
		{
			_result->Message(_windowError.GetErrorMessage());
		}
	}
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

	SetWindowText(GetHwnd(), _baseWindow.GetTitle());
}

SDL_WindowFlags MainWindow::GetFlags()
{
	return _WindowFlags;
}

void MainWindow::PollEvents()
{
	while (PeekMessage(&_message, _hwnd, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&_message);
		DispatchMessage(&_message);
	}
}

HWND MainWindow::GetHwnd()
{
	return _hwnd;
}

HDC MainWindow::GetHdc()
{
	return _hdc;
}

LRESULT CALLBACK MainWindow::Handler(UINT Message, WPARAM WParam, LPARAM LParam)
{
	SDL_Event event;

	switch (Message)
	{

	case WM_DESTROY:
		event.type = SDL_EVENT_QUIT;
		_eventHandler->Push(event);
		PostQuitMessage(0);
		break;

	case WM_CLOSE:
		break;

	case WM_ERASEBKGND:
		break;

	case WM_PALETTECHANGED:
		break;
	}

	return DefWindowProc(_hwnd, Message, WParam, LParam);
}

LRESULT CALLBACK MainWindow::WndProc(HWND Hwnd, UINT Message, WPARAM WParam, LPARAM LParam)
{
	LRESULT result;

#if defined(_WIN64)
	MainWindow* This = (MainWindow*)GetWindowLongPtr(Hwnd, GWLP_USERDATA);
#elif defined(_WIN32)
	MainWindow* This = (MainWindow*)GetWindowLong(Hwnd, GWL_USERDATA);
#endif  

	if (This != NULL)
	{
		result = This->Handler(Message, WParam, LParam);
	}
	else
	{
		result = DefWindowProc(Hwnd, Message, WParam, LParam);
	}

	return result;
}
