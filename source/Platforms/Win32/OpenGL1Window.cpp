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

#include <SDL3Lite/Platforms/Win32/MainWindow.hpp>
#include <SDL3Lite/Platforms/Win32/OpenGL1Window.hpp>

using namespace SDL;

OpenGL1Window::OpenGL1Window(OpenGLAttributes& openGLAttributes, Result& result, EventHandler& eventHandler, const Vec2i& pos, const Vec2i& size, const std::string& title, SDL_WindowFlags mode) :
	_openGLAttributes(&openGLAttributes),
	_result(&result),
	_renderContext(NULL),
	_mainWindow(result, eventHandler, pos, size, title, mode)
{
	memset(&_format, 0, sizeof(PIXELFORMATDESCRIPTOR));

	_format.nSize      = sizeof(_format);
	_format.nVersion   = 1;
	_format.dwFlags    = (PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER);
	_format.iLayerType = PFD_MAIN_PLANE;
	_format.iPixelType = PFD_TYPE_RGBA;

	//_format.cRedBits   = _openGLAttributes->GetRedSize();
	//_format.cGreenBits = _openGLAttributes->GetGreenSize();
	//_format.cBlueBits  = _openGLAttributes->GetBlueSize();
	//_format.cAlphaBits = _openGLAttributes->GetAlphaSize();

	//_format.cAccumRedBits   = _openGLAttributes->GetAccumRedSize();
	//_format.cAccumGreenBits = _openGLAttributes->GetAccumGreenSize();
	//_format.cAccumBlueBits  = _openGLAttributes->GetAccumBlueSize();
	//_format.cAccumAlphaBits = _openGLAttributes->GetAccumAlphaSize();

	int format = ChoosePixelFormat(_mainWindow.GetHdc(), &_format);


	if (format == 0)
	{
		_result->Message(_windowError.GetErrorMessage());
		return;
	}

	if (!SetPixelFormat(_mainWindow.GetHdc(), format, &_format))
	{
		_result->Message(_windowError.GetErrorMessage());
		return;
	}

	_renderContext = wglCreateContext(_mainWindow.GetHdc());

	if (_renderContext == NULL)
	{
		_result->Message(_windowError.GetErrorMessage());
		return;
	}

	if (!wglMakeCurrent(_mainWindow.GetHdc(), _renderContext))
	{
		_result->Message(_windowError.GetErrorMessage());
		return;
	}
}

OpenGL1Window::~OpenGL1Window()
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(_renderContext);
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

SDL_WindowFlags SDL::OpenGL1Window::GetFlags()
{
	return _mainWindow.GetFlags();
}

bool OpenGL1Window::Present()
{
	return SwapBuffers(_mainWindow.GetHdc());
}

void OpenGL1Window::PollEvents()
{
	_mainWindow.PollEvents();
}
