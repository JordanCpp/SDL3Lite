/*
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef SDL3Lite_SDL_Window_h
#define SDL3Lite_SDL_Window_h

#include <SDL3/SDL_Types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The flags on a window.
 *
 * These cover a lot of true/false, or on/off, window state. Some of it is
 * immutable after being set through SDL_CreateWindow(), some of it can be
 * changed on existing windows by the app, and some of it might be altered by
 * the user or system outside of the app's control.
 *
 * \since This datatype is available since SDL 3.2.0.
 *
 * \sa SDL_GetWindowFlags
 */

typedef Uint64 SDL_WindowFlags;

#define SDL_WINDOW_FULLSCREEN           SDL_UINT64_C(0x0000000000000001)    /**< window is in fullscreen mode */
#define SDL_WINDOW_OPENGL               SDL_UINT64_C(0x0000000000000002)    /**< window usable with OpenGL context */
#define SDL_WINDOW_OCCLUDED             SDL_UINT64_C(0x0000000000000004)    /**< window is occluded */
#define SDL_WINDOW_HIDDEN               SDL_UINT64_C(0x0000000000000008)    /**< window is neither mapped onto the desktop nor shown in the taskbar/dock/window list; SDL_ShowWindow() is required for it to become visible */
#define SDL_WINDOW_BORDERLESS           SDL_UINT64_C(0x0000000000000010)    /**< no window decoration */
#define SDL_WINDOW_RESIZABLE            SDL_UINT64_C(0x0000000000000020)    /**< window can be resized */
#define SDL_WINDOW_MINIMIZED            SDL_UINT64_C(0x0000000000000040)    /**< window is minimized */
#define SDL_WINDOW_MAXIMIZED            SDL_UINT64_C(0x0000000000000080)    /**< window is maximized */
#define SDL_WINDOW_MOUSE_GRABBED        SDL_UINT64_C(0x0000000000000100)    /**< window has grabbed mouse input */
#define SDL_WINDOW_INPUT_FOCUS          SDL_UINT64_C(0x0000000000000200)    /**< window has input focus */
#define SDL_WINDOW_MOUSE_FOCUS          SDL_UINT64_C(0x0000000000000400)    /**< window has mouse focus */
#define SDL_WINDOW_EXTERNAL             SDL_UINT64_C(0x0000000000000800)    /**< window not created by SDL */
#define SDL_WINDOW_MODAL                SDL_UINT64_C(0x0000000000001000)    /**< window is modal */
#define SDL_WINDOW_HIGH_PIXEL_DENSITY   SDL_UINT64_C(0x0000000000002000)    /**< window uses high pixel density back buffer if possible */
#define SDL_WINDOW_MOUSE_CAPTURE        SDL_UINT64_C(0x0000000000004000)    /**< window has mouse captured (unrelated to MOUSE_GRABBED) */
#define SDL_WINDOW_MOUSE_RELATIVE_MODE  SDL_UINT64_C(0x0000000000008000)    /**< window has relative mode enabled */
#define SDL_WINDOW_ALWAYS_ON_TOP        SDL_UINT64_C(0x0000000000010000)    /**< window should always be above others */
#define SDL_WINDOW_UTILITY              SDL_UINT64_C(0x0000000000020000)    /**< window should be treated as a utility window, not showing in the task bar and window list */
#define SDL_WINDOW_TOOLTIP              SDL_UINT64_C(0x0000000000040000)    /**< window should be treated as a tooltip and does not get mouse or keyboard focus, requires a parent window */
#define SDL_WINDOW_POPUP_MENU           SDL_UINT64_C(0x0000000000080000)    /**< window should be treated as a popup menu, requires a parent window */
#define SDL_WINDOW_KEYBOARD_GRABBED     SDL_UINT64_C(0x0000000000100000)    /**< window has grabbed keyboard input */
#define SDL_WINDOW_VULKAN               SDL_UINT64_C(0x0000000010000000)    /**< window usable for Vulkan surface */
#define SDL_WINDOW_METAL                SDL_UINT64_C(0x0000000020000000)    /**< window usable for Metal view */
#define SDL_WINDOW_TRANSPARENT          SDL_UINT64_C(0x0000000040000000)    /**< window with transparent buffer */
#define SDL_WINDOW_NOT_FOCUSABLE        SDL_UINT64_C(0x0000000080000000)    /**< window should not be focusable */

typedef struct SDL_Window SDL_Window;

extern SDL_DECLSPEC SDL_Window* SDLCALL SDL_CreateWindow(const char* title, int w, int h, size_t flags);
extern SDL_DECLSPEC void SDLCALL SDL_DestroyWindow(SDL_Window* window);

#ifdef __cplusplus
}
#endif

#endif
