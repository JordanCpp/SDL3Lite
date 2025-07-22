/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <string.h>
#include <SDL3/EventH.hpp>

EventQueue::EventQueue() :
	_head(-1),
	_tail(0),
	_length(0),
	_capacity(Max)
{
	memset(&_content, 0, sizeof(SDL_Event) * Max);
}

bool EventQueue::IsEmpty()
{
	return _length == 0;
}

bool EventQueue::IsFull()
{
	return _length == _capacity;
}

int EventQueue::NextPosition(int position)
{
	return (position + 1) % _capacity;
}

bool EventQueue::Dequeue(SDL_Event& element)
{
	if (!IsEmpty())
	{
		element = _content[_tail];
		_tail = NextPosition(_tail);
		_length--;

		return true;
	}

	return false;
}

void EventQueue::Enqueue(const SDL_Event& element)
{
	_head = NextPosition(_head);

	_content[_head] = element;

	if (IsFull())
	{
		_tail = NextPosition(_tail);
	}
	else
	{
		_length++;
	}
}
