/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_EventQ_hpp
#define SDL3Lite_EventQ_hpp

#include <SDL3/Events.h>

class EventQueue
{
public:
	enum
	{
		Max = 256
	};
	EventQueue();
	bool IsEmpty();
	bool IsFull();
	int NextPosition(int position);
	bool Dequeue(SDL_Event& element);
	void Enqueue(const SDL_Event& element);
private:
	SDL_Event _content[Max];
	int       _head;
	int       _tail;
	int       _length;
	int       _capacity;
};

#endif