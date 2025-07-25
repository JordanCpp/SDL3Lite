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

#ifndef SDL3Lite_Pixels_h
#define SDL3Lite_Pixels_h

#include <SDL3/StdInc.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct SDL_Color
    {
        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;
    } SDL_Color;

    typedef struct SDL_Palette
    {
        int ncolors;        /**< number of elements in `colors`. */
        SDL_Color* colors;  /**< an array of colors, `ncolors` long. */
        Uint32 version;     /**< internal use only, do not touch. */
        int refcount;       /**< internal use only, do not touch. */
    } SDL_Palette;

    /**
     * Pixel format.
     *
     * SDL's pixel formats have the following naming convention:
     *
     * - Names with a list of components and a single bit count, such as RGB24 and
     *   ABGR32, define a platform-independent encoding into bytes in the order
     *   specified. For example, in RGB24 data, each pixel is encoded in 3 bytes
     *   (red, green, blue) in that order, and in ABGR32 data, each pixel is
     *   encoded in 4 bytes alpha, blue, green, red) in that order. Use these
     *   names if the property of a format that is important to you is the order
     *   of the bytes in memory or on disk.
     * - Names with a bit count per component, such as ARGB8888 and XRGB1555, are
     *   "packed" into an appropriately-sized integer in the platform's native
     *   endianness. For example, ARGB8888 is a sequence of 32-bit integers; in
     *   each integer, the most significant bits are alpha, and the least
     *   significant bits are blue. On a little-endian CPU such as x86, the least
     *   significant bits of each integer are arranged first in memory, but on a
     *   big-endian CPU such as s390x, the most significant bits are arranged
     *   first. Use these names if the property of a format that is important to
     *   you is the meaning of each bit position within a native-endianness
     *   integer.
     * - In indexed formats such as INDEX4LSB, each pixel is represented by
     *   encoding an index into the palette into the indicated number of bits,
     *   with multiple pixels packed into each byte if appropriate. In LSB
     *   formats, the first (leftmost) pixel is stored in the least-significant
     *   bits of the byte; in MSB formats, it's stored in the most-significant
     *   bits. INDEX8 does not need LSB/MSB variants, because each pixel exactly
     *   fills one byte.
     *
     * The 32-bit byte-array encodings such as RGBA32 are aliases for the
     * appropriate 8888 encoding for the current platform. For example, RGBA32 is
     * an alias for ABGR8888 on little-endian CPUs like x86, or an alias for
     * RGBA8888 on big-endian CPUs.
     *
     * \since This enum is available since SDL 3.2.0.
     */
    typedef enum SDL_PixelFormat
    {
        SDL_PIXELFORMAT_UNKNOWN = 0,
        SDL_PIXELFORMAT_INDEX1LSB = 0x11100100u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_INDEX1, SDL_BITMAPORDER_4321, 0, 1, 0), */
        SDL_PIXELFORMAT_INDEX1MSB = 0x11200100u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_INDEX1, SDL_BITMAPORDER_1234, 0, 1, 0), */
        SDL_PIXELFORMAT_INDEX2LSB = 0x1c100200u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_INDEX2, SDL_BITMAPORDER_4321, 0, 2, 0), */
        SDL_PIXELFORMAT_INDEX2MSB = 0x1c200200u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_INDEX2, SDL_BITMAPORDER_1234, 0, 2, 0), */
        SDL_PIXELFORMAT_INDEX4LSB = 0x12100400u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_INDEX4, SDL_BITMAPORDER_4321, 0, 4, 0), */
        SDL_PIXELFORMAT_INDEX4MSB = 0x12200400u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_INDEX4, SDL_BITMAPORDER_1234, 0, 4, 0), */
        SDL_PIXELFORMAT_INDEX8 = 0x13000801u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_INDEX8, 0, 0, 8, 1), */
        SDL_PIXELFORMAT_RGB332 = 0x14110801u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED8, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_332, 8, 1), */
        SDL_PIXELFORMAT_XRGB4444 = 0x15120c02u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_4444, 12, 2), */
        SDL_PIXELFORMAT_XBGR4444 = 0x15520c02u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XBGR, SDL_PACKEDLAYOUT_4444, 12, 2), */
        SDL_PIXELFORMAT_XRGB1555 = 0x15130f02u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_1555, 15, 2), */
        SDL_PIXELFORMAT_XBGR1555 = 0x15530f02u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XBGR, SDL_PACKEDLAYOUT_1555, 15, 2), */
        SDL_PIXELFORMAT_ARGB4444 = 0x15321002u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ARGB, SDL_PACKEDLAYOUT_4444, 16, 2), */
        SDL_PIXELFORMAT_RGBA4444 = 0x15421002u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_RGBA, SDL_PACKEDLAYOUT_4444, 16, 2), */
        SDL_PIXELFORMAT_ABGR4444 = 0x15721002u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ABGR, SDL_PACKEDLAYOUT_4444, 16, 2), */
        SDL_PIXELFORMAT_BGRA4444 = 0x15821002u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_BGRA, SDL_PACKEDLAYOUT_4444, 16, 2), */
        SDL_PIXELFORMAT_ARGB1555 = 0x15331002u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ARGB, SDL_PACKEDLAYOUT_1555, 16, 2), */
        SDL_PIXELFORMAT_RGBA5551 = 0x15441002u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_RGBA, SDL_PACKEDLAYOUT_5551, 16, 2), */
        SDL_PIXELFORMAT_ABGR1555 = 0x15731002u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_ABGR, SDL_PACKEDLAYOUT_1555, 16, 2), */
        SDL_PIXELFORMAT_BGRA5551 = 0x15841002u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_BGRA, SDL_PACKEDLAYOUT_5551, 16, 2), */
        SDL_PIXELFORMAT_RGB565 = 0x15151002u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_565, 16, 2), */
        SDL_PIXELFORMAT_BGR565 = 0x15551002u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED16, SDL_PACKEDORDER_XBGR, SDL_PACKEDLAYOUT_565, 16, 2), */
        SDL_PIXELFORMAT_RGB24 = 0x17101803u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU8, SDL_ARRAYORDER_RGB, 0, 24, 3), */
        SDL_PIXELFORMAT_BGR24 = 0x17401803u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU8, SDL_ARRAYORDER_BGR, 0, 24, 3), */
        SDL_PIXELFORMAT_XRGB8888 = 0x16161804u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_8888, 24, 4), */
        SDL_PIXELFORMAT_RGBX8888 = 0x16261804u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_RGBX, SDL_PACKEDLAYOUT_8888, 24, 4), */
        SDL_PIXELFORMAT_XBGR8888 = 0x16561804u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_XBGR, SDL_PACKEDLAYOUT_8888, 24, 4), */
        SDL_PIXELFORMAT_BGRX8888 = 0x16661804u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_BGRX, SDL_PACKEDLAYOUT_8888, 24, 4), */
        SDL_PIXELFORMAT_ARGB8888 = 0x16362004u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_ARGB, SDL_PACKEDLAYOUT_8888, 32, 4), */
        SDL_PIXELFORMAT_RGBA8888 = 0x16462004u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_RGBA, SDL_PACKEDLAYOUT_8888, 32, 4), */
        SDL_PIXELFORMAT_ABGR8888 = 0x16762004u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_ABGR, SDL_PACKEDLAYOUT_8888, 32, 4), */
        SDL_PIXELFORMAT_BGRA8888 = 0x16862004u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_BGRA, SDL_PACKEDLAYOUT_8888, 32, 4), */
        SDL_PIXELFORMAT_XRGB2101010 = 0x16172004u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_XRGB, SDL_PACKEDLAYOUT_2101010, 32, 4), */
        SDL_PIXELFORMAT_XBGR2101010 = 0x16572004u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_XBGR, SDL_PACKEDLAYOUT_2101010, 32, 4), */
        SDL_PIXELFORMAT_ARGB2101010 = 0x16372004u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_ARGB, SDL_PACKEDLAYOUT_2101010, 32, 4), */
        SDL_PIXELFORMAT_ABGR2101010 = 0x16772004u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_PACKED32, SDL_PACKEDORDER_ABGR, SDL_PACKEDLAYOUT_2101010, 32, 4), */
        SDL_PIXELFORMAT_RGB48 = 0x18103006u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_RGB, 0, 48, 6), */
        SDL_PIXELFORMAT_BGR48 = 0x18403006u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_BGR, 0, 48, 6), */
        SDL_PIXELFORMAT_RGBA64 = 0x18204008u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_RGBA, 0, 64, 8), */
        SDL_PIXELFORMAT_ARGB64 = 0x18304008u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_ARGB, 0, 64, 8), */
        SDL_PIXELFORMAT_BGRA64 = 0x18504008u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_BGRA, 0, 64, 8), */
        SDL_PIXELFORMAT_ABGR64 = 0x18604008u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYU16, SDL_ARRAYORDER_ABGR, 0, 64, 8), */
        SDL_PIXELFORMAT_RGB48_FLOAT = 0x1a103006u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_RGB, 0, 48, 6), */
        SDL_PIXELFORMAT_BGR48_FLOAT = 0x1a403006u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_BGR, 0, 48, 6), */
        SDL_PIXELFORMAT_RGBA64_FLOAT = 0x1a204008u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_RGBA, 0, 64, 8), */
        SDL_PIXELFORMAT_ARGB64_FLOAT = 0x1a304008u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_ARGB, 0, 64, 8), */
        SDL_PIXELFORMAT_BGRA64_FLOAT = 0x1a504008u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_BGRA, 0, 64, 8), */
        SDL_PIXELFORMAT_ABGR64_FLOAT = 0x1a604008u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF16, SDL_ARRAYORDER_ABGR, 0, 64, 8), */
        SDL_PIXELFORMAT_RGB96_FLOAT = 0x1b10600cu,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_RGB, 0, 96, 12), */
        SDL_PIXELFORMAT_BGR96_FLOAT = 0x1b40600cu,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_BGR, 0, 96, 12), */
        SDL_PIXELFORMAT_RGBA128_FLOAT = 0x1b208010u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_RGBA, 0, 128, 16), */
        SDL_PIXELFORMAT_ARGB128_FLOAT = 0x1b308010u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_ARGB, 0, 128, 16), */
        SDL_PIXELFORMAT_BGRA128_FLOAT = 0x1b508010u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_BGRA, 0, 128, 16), */
        SDL_PIXELFORMAT_ABGR128_FLOAT = 0x1b608010u,
        /* SDL_DEFINE_PIXELFORMAT(SDL_PIXELTYPE_ARRAYF32, SDL_ARRAYORDER_ABGR, 0, 128, 16), */

        SDL_PIXELFORMAT_YV12 = 0x32315659u,      /**< Planar mode: Y + V + U  (3 planes) */
        /* SDL_DEFINE_PIXELFOURCC('Y', 'V', '1', '2'), */
        SDL_PIXELFORMAT_IYUV = 0x56555949u,      /**< Planar mode: Y + U + V  (3 planes) */
        /* SDL_DEFINE_PIXELFOURCC('I', 'Y', 'U', 'V'), */
        SDL_PIXELFORMAT_YUY2 = 0x32595559u,      /**< Packed mode: Y0+U0+Y1+V0 (1 plane) */
        /* SDL_DEFINE_PIXELFOURCC('Y', 'U', 'Y', '2'), */
        SDL_PIXELFORMAT_UYVY = 0x59565955u,      /**< Packed mode: U0+Y0+V0+Y1 (1 plane) */
        /* SDL_DEFINE_PIXELFOURCC('U', 'Y', 'V', 'Y'), */
        SDL_PIXELFORMAT_YVYU = 0x55595659u,      /**< Packed mode: Y0+V0+Y1+U0 (1 plane) */
        /* SDL_DEFINE_PIXELFOURCC('Y', 'V', 'Y', 'U'), */
        SDL_PIXELFORMAT_NV12 = 0x3231564eu,      /**< Planar mode: Y + U/V interleaved  (2 planes) */
        /* SDL_DEFINE_PIXELFOURCC('N', 'V', '1', '2'), */
        SDL_PIXELFORMAT_NV21 = 0x3132564eu,      /**< Planar mode: Y + V/U interleaved  (2 planes) */
        /* SDL_DEFINE_PIXELFOURCC('N', 'V', '2', '1'), */
        SDL_PIXELFORMAT_P010 = 0x30313050u,      /**< Planar mode: Y + U/V interleaved  (2 planes) */
        /* SDL_DEFINE_PIXELFOURCC('P', '0', '1', '0'), */
        SDL_PIXELFORMAT_EXTERNAL_OES = 0x2053454fu,     /**< Android video texture format */
        /* SDL_DEFINE_PIXELFOURCC('O', 'E', 'S', ' ') */

        SDL_PIXELFORMAT_MJPG = 0x47504a4du,     /**< Motion JPEG */
        /* SDL_DEFINE_PIXELFOURCC('M', 'J', 'P', 'G') */

    /* Aliases for RGBA byte arrays of color data, for the current platform */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        SDL_PIXELFORMAT_RGBA32 = SDL_PIXELFORMAT_RGBA8888,
        SDL_PIXELFORMAT_ARGB32 = SDL_PIXELFORMAT_ARGB8888,
        SDL_PIXELFORMAT_BGRA32 = SDL_PIXELFORMAT_BGRA8888,
        SDL_PIXELFORMAT_ABGR32 = SDL_PIXELFORMAT_ABGR8888,
        SDL_PIXELFORMAT_RGBX32 = SDL_PIXELFORMAT_RGBX8888,
        SDL_PIXELFORMAT_XRGB32 = SDL_PIXELFORMAT_XRGB8888,
        SDL_PIXELFORMAT_BGRX32 = SDL_PIXELFORMAT_BGRX8888,
        SDL_PIXELFORMAT_XBGR32 = SDL_PIXELFORMAT_XBGR8888
#else
        SDL_PIXELFORMAT_RGBA32 = SDL_PIXELFORMAT_ABGR8888,
        SDL_PIXELFORMAT_ARGB32 = SDL_PIXELFORMAT_BGRA8888,
        SDL_PIXELFORMAT_BGRA32 = SDL_PIXELFORMAT_ARGB8888,
        SDL_PIXELFORMAT_ABGR32 = SDL_PIXELFORMAT_RGBA8888,
        SDL_PIXELFORMAT_RGBX32 = SDL_PIXELFORMAT_XBGR8888,
        SDL_PIXELFORMAT_XRGB32 = SDL_PIXELFORMAT_BGRX8888,
        SDL_PIXELFORMAT_BGRX32 = SDL_PIXELFORMAT_XRGB8888,
        SDL_PIXELFORMAT_XBGR32 = SDL_PIXELFORMAT_RGBX8888
#endif
    } SDL_PixelFormat;

    typedef struct SDL_PixelFormatDetails
    {
        SDL_PixelFormat format;
        Uint8 bits_per_pixel;
        Uint8 bytes_per_pixel;
        Uint8 padding[2];
        Uint32 Rmask;
        Uint32 Gmask;
        Uint32 Bmask;
        Uint32 Amask;
        Uint8 Rbits;
        Uint8 Gbits;
        Uint8 Bbits;
        Uint8 Abits;
        Uint8 Rshift;
        Uint8 Gshift;
        Uint8 Bshift;
        Uint8 Ashift;
    } SDL_PixelFormatDetails;



extern SDL_DECLSPEC Uint32 SDLCALL SDL_MapRGB(const SDL_PixelFormatDetails* format, const SDL_Palette* palette, Uint8 r, Uint8 g, Uint8 b);

#ifdef __cplusplus
}
#endif

#endif
