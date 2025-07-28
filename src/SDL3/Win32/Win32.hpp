/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef SDL3Lite_Win32_Win32_hpp
#define SDL3Lite_Win32_Win32_hpp

#undef UNICODE
#undef _UNICODE
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXT)(HDC);
typedef BOOL(WINAPI* PFNWGLMAKECURRENT)(HDC, HGLRC);
typedef BOOL(WINAPI* PFNWGLDELETECONTEXT)(HGLRC);

typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int* attribList);

#define WGL_CONTEXT_MAJOR_VERSION_ARB             (0x2091)
#define WGL_CONTEXT_MINOR_VERSION_ARB             (0x2092)
#define WGL_CONTEXT_FLAGS_ARB                     (0x2094) 
#define WGL_CONTEXT_PROFILE_MASK_ARB              (0x9126) 
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB    (0x00000002) 
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          (0x00000001)
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB (0x00000002)

#endif
