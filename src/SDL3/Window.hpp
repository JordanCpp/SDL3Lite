/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_Window_hpp
#define SDL3Lite_Window_hpp

#include <SDL3/Window.h>
#include <SDL3/Surface.hpp>

struct SDL_Window
{
public:
	virtual ~SDL_Window() {};
	virtual Surface* GetSurface() = 0;
	virtual const SDL_Point& GetPos() = 0;
	virtual void SetPos(const SDL_Point& pos) = 0;
	virtual const SDL_Point& GetSize() = 0;
	virtual void SetSize(const SDL_Point& size) = 0;
	virtual const char* GetTitle() = 0;
	virtual void SetTitle(const char* title) = 0;
	virtual SDL_WindowFlags GetFlags() = 0;
	virtual void PollEvents() = 0;
	virtual bool Present() = 0;
};

#endif
