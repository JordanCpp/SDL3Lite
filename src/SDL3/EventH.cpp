/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <SDL3/EventH.hpp>

EventHandler::EventHandler() :
	_running(true)
{
}

void EventHandler::Push(SDL_Event& event)
{
	_queue.Enqueue(event);
}

bool EventHandler::Pop(SDL_Event& event)
{
	if (!_queue.IsEmpty())
	{
		_queue.Dequeue(event);

		return true;
	}

	return false;
}

bool EventHandler::Running()
{
	return _running;
}

void EventHandler::Stop()
{
	_running = false;
}

bool EventHandler::Empty()
{
	return _queue.IsEmpty();
}
