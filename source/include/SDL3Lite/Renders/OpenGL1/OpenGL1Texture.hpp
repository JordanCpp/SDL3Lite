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

#ifndef SDL3Lite_Renders_OpenGL1_OpenGL1Texture_hpp
#define SDL3Lite_Renders_OpenGL1_OpenGL1Texture_hpp

#include <OpenGL.h>
#include <SDL3/pstdint.h>
#include <SDL3Lite/Vec2.hpp>
#include <SDL3Lite/SDL_Texture.hpp>
#include <SDL3Lite/Renders/OpenGL1/OpenGL1Render.hpp>

namespace SDL
{
	class OpenGL1Render;

	class OpenGL1Texture : public SDL_Texture
	{
	public:
		~OpenGL1Texture();
		OpenGL1Texture(OpenGL1Render& render, const Vec2i& size, int bpp);
		OpenGL1Texture(OpenGL1Render& render, const Vec2i& size, int bpp, uint8_t* pixels);
		const Vec2i& GetSize();
		const Vec2i& GetQuad();
		bool Update(const Vec2i& pos, const Vec2i& size, uint8_t* pixels, int bpp);
	public:
		GLuint GetTexture();
	private:
		OpenGL1Render& _render;
		GLuint         _texture;
		Vec2i          _size;
		Vec2i          _quad;
	};
}

#endif
