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

#ifndef SDL3Lite_Unix_MainWindow_hpp
#define SDL3Lite_Unix_MainWindow_hpp

#include <SDL3/SDL_Window.h>
#include <SDL3Lite/Result.hpp>
#include <SDL3Lite/BaseWindow.hpp>
#include <SDL3Lite/EventHandler.hpp>
#include <SDL3Lite/Platforms/Unix/GLX.hpp>

namespace SDL
{
	class MainWindow
	{
	public:
		MainWindow(Result& result, EventHandler& eventHandler, const Vec2i& pos, const Vec2i& size, const std::string& title, SDL_WindowFlags mode);
		~MainWindow();
		const Vec2i& GetPos();
		void SetPos(const Vec2i& pos);
		const Vec2i& GetSize();
		void SetSize(const Vec2i& size);
		const std::string& GetTitle();
		void SetTitle(const std::string& title);
		void PollEvents();
		SDL_WindowFlags GetFlags();
	private:
		Result*         _result;
		EventHandler*   _eventHandler;
		BaseWindow      _baseWindow;
		Display*        _Display;
	    int             _Screen;
	    Window          _Root;
	    Window          _Window;
	    size_t          _EventMask;
		SDL_WindowFlags _windowFlags;
	public:
	    Display* GetDisplay();
	    int GetScreen();
	    Window GetRoot();
	    Window GetWindow();
		void SetWindow(Window window);
		size_t GetEventMask();
	};
}

#endif
