/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_Win32_WinError_hpp
#define SDL3Lite_Win32_WinError_hpp

#include <SDL3/Win32/Win32.hpp>

class WindowError
{
public:
	const char* GetErrorMessage();
private:
	enum
	{
		Max = 128
	};

	char _message[Max];
};

#endif
