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

#include <SDL3Lite/Renders/Software/PixelCopier.hpp>

using namespace SDL;

void PixelCopier::Copy(uint8_t* dstPixels, int dstBpp, const Vec2i& dstArea, const Vec2i& dstPos, const Vec2i& dstSize, uint8_t* srcPixels, int srcBpp, const Vec2i& srcArea, const Vec2i& srcPos, const Vec2i& srcSize)
{
	size_t x = dstPos.x;
	size_t y = dstPos.y;

	size_t dstSizeX    = dstArea.x;
	size_t dstSizeY    = dstArea.y;
	size_t dstIndex    = 0;

	size_t srcSizeX    = srcArea.x;
	size_t srcSizeY    = srcArea.y;
	size_t srcIndex    = 0;

	size_t limitSizeX = 0;
	size_t limitSizeY = 0;

	if (srcSizeX + x > dstSizeX)
	{
		limitSizeX = dstSizeX - x;
	}
	else
	{
		limitSizeX = srcSizeX;
	}

	if (srcSizeY + y > dstSizeY)
	{
		limitSizeY = dstSizeY - y;
	}
	else
	{
		limitSizeY = srcSizeY;
	}

	for (size_t i = 0; i < limitSizeX; i++)
	{
		for (size_t j = 0; j < limitSizeY; j++)
		{
			dstIndex = (dstSizeX * (y + j) + (x + i)) * dstBpp;
			srcIndex = (srcSizeX * j + i) * srcBpp;

#if defined (_WIN32)
			dstPixels[dstIndex + 2] = srcPixels[srcIndex + 0];
			dstPixels[dstIndex + 1] = srcPixels[srcIndex + 1];
			dstPixels[dstIndex + 0] = srcPixels[srcIndex + 2];
#else
			dstPixels[dstIndex + 0] = srcPixels[srcIndex + 0];
			dstPixels[dstIndex + 1] = srcPixels[srcIndex + 1];
			dstPixels[dstIndex + 2] = srcPixels[srcIndex + 2];
#endif  
		}
	}
}
