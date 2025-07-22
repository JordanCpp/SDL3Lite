/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_EventH_hpp
#define SDL3Lite_EventH_hpp

#include <SDL3/EventQ.hpp>

class EventHandler
{
public:
	EventHandler();
	void Push(SDL_Event& event);
	bool Pop(SDL_Event& event);
	bool Running();
	void Stop();
	bool Empty();
private:
	bool       _running;
	EventQueue _queue;
};

#endif
