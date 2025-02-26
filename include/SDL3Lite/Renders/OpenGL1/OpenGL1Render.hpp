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

#ifndef SDL3Lite_Renders_OpenGL1_OpenGL1Render_hpp
#define SDL3Lite_Renders_OpenGL1_OpenGL1Render_hpp

#include <SDL3Lite/IRender.hpp>
#include <SDL3Lite/OpenGL/Mat4f.hpp>
#include <SDL3Lite/Renders/OpenGL1/OpenGL1Texture.hpp>

#if defined(_WIN32)
    #include <SDL3Lite/Platforms/Win32/OpenGL1Window.hpp>
#elif defined (__unix__)
    #include <SDL3Lite/Platforms/Unix/OpenGL1Window.hpp>
#endif

namespace SDL
{
	class OpenGL1Texture;

	class OpenGL1Render : public IRender
	{
	public:
	    OpenGL1Render(Result& result, IWindow* window);
		const Vec2i& GetSize();
		void Present();
		void SetColor(const Color& color);
		void Clear();
		void FillRect(const Vec2f& pos, const Vec2f& size);
		void Draw(ITexture* texture, const Vec2f& dstPos, const Vec2f& dstSize, const Vec2f& srcPos, const Vec2f& srcSize);
	private:
		Result&   _result;
	    IWindow* _window;
	    Color    _color;
		Mat4f    _projection;
		Mat4f    _modelView;
	};
}

#endif
