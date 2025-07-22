/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <SDL3/StdMem.h>
#include <SDL3/StdStr.h>
#include <SDL3/ShortStr.hpp>

ShortString::ShortString()
{
	Clear();
}

void ShortString::Clear()
{
	SDL_memset(_message, 0, Max);
}

void ShortString::Append(const char* source)
{
	SDL_strlcat(_message, source, Max);
}

const char* ShortString::Str()
{
	return _message;
}
