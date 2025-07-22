/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_ShortStr_hpp
#define SDL3Lite_ShortStr_hpp

class ShortString
{
public:
	enum
	{
		Max = 64
	};

	ShortString();
	void Clear();
	void Append(const char* source);
	const char* Str();
private:
	char _message[Max];
};

#endif
