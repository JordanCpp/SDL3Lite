/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <SDL3/Result.hpp>

Result::Result()
{
	Clear();
}

bool Result::Ok()
{
	return _ok;
}

const char* Result::Message()
{
	return _message.GetStr();
}

void Result::Message(const char* message)
{
	Message(message, "");
}

void Result::Message(const char* message, const char* detail)
{
	Clear();

	_message.Append(message);
	_message.Append(detail);

	_ok = false;
}

void Result::Clear()
{
	_ok = true;
	_message.Clear();
}
