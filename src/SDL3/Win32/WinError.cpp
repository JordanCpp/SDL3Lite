/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <assert.h>
#include <SDL3/Win32/WinError.hpp>

const char* WindowError::GetErrorMessage()
{
    DWORD ident = GetLastError();
    assert(ident != 0);

    LPSTR buffer = NULL;

    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, ident, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&buffer, 0, NULL);

    assert(size < Max);

    memset(_message, 0, Max);
    strcpy(_message, buffer);

    LocalFree(buffer);

    return _message;
}
