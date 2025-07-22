/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <SDL3/StdMath.h>
#include <SDL3/Pixels.hpp>

const double MinDistance = 250.0f;

int PixelFormatToBytesPerPixels(const SDL_PixelFormat pixelFormat)
{
    int result = SDL_PIXELFORMAT_UNKNOWN;

    switch (pixelFormat)
    {
    case SDL_PIXELFORMAT_INDEX8:
        result = 1;
        break;
    case SDL_PIXELFORMAT_RGB24:
        result = 3;
        break;
    }

	return result;
}

SDL_PixelFormat GetDefaultPixelFormat()
{

#if defined(_WIN32)
    return SDL_PIXELFORMAT_RGB24;
#elif defined(__unix__)
    return SDL_PIXELFORMAT_RGB24;
#elif defined(__MSDOS__)
    return SDL_PIXELFORMAT_INDEX8;
#elif defined(__BORLANDC__)
    return SDL_PIXELFORMAT_INDEX8;
#endif

}

double ColorDistance(const SDL_Color& c1, const SDL_Color& c2) 
{
    return SDL_sqrt(
        SDL_pow(c1.r - c2.r, 2) +
        SDL_pow(c1.g - c2.g, 2) +
        SDL_pow(c1.b - c2.b, 2)
    );
}

Uint8 FindClosest(SDL_Color target, SDL_Color* palette, size_t size)
{
    double minDistance = MinDistance;
    Uint8 closest      = 0;

    for (size_t i = 0; i < size; i++)
    {
        double distance = ColorDistance(target, palette[i]);

        if (distance < minDistance)
        {
            minDistance = distance;
            closest     = (Uint8)i;
        }
    }

    return closest;
}

SDL_Color FindClosestColor(SDL_Color target, SDL_Color* palette, size_t size)
{
    Uint8 index = FindClosest(target, palette, size);

    return palette[index];
}

Uint8 FindClosestIndex(SDL_Color target, SDL_Color* palette, size_t size)
{
    return FindClosest(target, palette, size);
}
