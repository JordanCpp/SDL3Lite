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

#include <SDL3Lite/Platforms/Unix/MainWindow.hpp>
#include <SDL3Lite/Platforms/Unix/OpenGL1Window.hpp>

using namespace SDL;

OpenGL1Window::OpenGL1Window(OpenGLAttributes& openGLAttributes, Result& result, EventHandler& eventHandler, const Vec2i& pos, const Vec2i& size, const std::string& title, SDL_WindowFlags mode) :
	_openGLAttributes(&openGLAttributes),
	_result(&result),
	_mainWindow(result, eventHandler, pos, size, title, mode)
{
	int major = 0;
	int minor = 0;

	glXQueryVersion(_mainWindow.GetDisplay(), &major, &minor);

	int ga[] = {
		GLX_RGBA,
		GLX_DOUBLEBUFFER,
		GLX_DEPTH_SIZE, 24,
		GLX_STENCIL_SIZE, 8,
		GLX_RED_SIZE, 8,
		GLX_GREEN_SIZE, 8,
		GLX_BLUE_SIZE, 8,
		GLX_SAMPLE_BUFFERS, 0,
		GLX_SAMPLES, 0,
		None };

	_Visual = glXChooseVisual(_mainWindow.GetDisplay(), _mainWindow.GetScreen(), ga);

	if (_Visual == NULL)
	{
		_result->Message("glXChooseVisual failed");
	}

	XSetWindowAttributes wa;

	wa.border_pixel      = BlackPixel(_mainWindow.GetDisplay(), _mainWindow.GetScreen());
	wa.background_pixel  = WhitePixel(_mainWindow.GetDisplay(), _mainWindow.GetScreen());
	wa.override_redirect = True;
	wa.colormap          = XCreateColormap(_mainWindow.GetDisplay(), _mainWindow.GetRoot(), _Visual->visual, AllocNone);
	wa.event_mask        = ExposureMask;

	size_t x = pos.x;
	size_t y = pos.y;
	size_t w = size.x;
	size_t h = size.y;

	Window window = XCreateWindow(_mainWindow.GetDisplay(), _mainWindow.GetRoot(), x, y, w, h, 0, _Visual->depth, InputOutput, _Visual->visual, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &wa);
	_mainWindow.SetWindow(window); 

	XSelectInput(_mainWindow.GetDisplay(), _mainWindow.GetWindow(), _mainWindow.GetEventMask());

	_Context = glXCreateContext(_mainWindow.GetDisplay(), _Visual, NULL, true);

	glXMakeCurrent(_mainWindow.GetDisplay(), _mainWindow.GetWindow(), _Context);

	XClearWindow(_mainWindow.GetDisplay(), _mainWindow.GetWindow());
	XMapRaised(_mainWindow.GetDisplay(), _mainWindow.GetWindow());
}

OpenGL1Window::~OpenGL1Window()
{
	glXDestroyContext(_mainWindow.GetDisplay(), _Context);
}

const Vec2i& OpenGL1Window::GetPos()
{
	return _mainWindow.GetPos();
}

void OpenGL1Window::SetPos(const Vec2i& pos)
{
	_mainWindow.SetPos(pos);
}

const Vec2i& OpenGL1Window::GetSize()
{
	return _mainWindow.GetSize();
}

void OpenGL1Window::SetSize(const Vec2i& size)
{
	_mainWindow.SetSize(size);
}

const std::string& OpenGL1Window::GetTitle()
{
	return _mainWindow.GetTitle();
}

void OpenGL1Window::SetTitle(const std::string& title)
{
	_mainWindow.SetTitle(title);
}

bool OpenGL1Window::Present()
{
	glXSwapBuffers(_mainWindow.GetDisplay(), _mainWindow.GetWindow());

	return true;
}

SDL_WindowFlags OpenGL1Window::GetFlags()
{
	return _mainWindow.GetFlags();
}

void OpenGL1Window::PollEvents()
{
	_mainWindow.PollEvents();
}
