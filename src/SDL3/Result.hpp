/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_Result_hpp
#define SDL3Lite_Result_hpp

#include <SDL3/Types.h>
#include <SDL3/ShortStr.hpp>

class Result
{
public:
	Result();
	bool Ok();
	const char* Message();
	void Message(const char* message);
	void Message(const char* message, const char* detail);
	void Clear();
private:
	bool        _ok;
	ShortString _message;
};

#endif
