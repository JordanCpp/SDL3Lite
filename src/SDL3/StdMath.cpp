/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <math.h>
#include <SDL3/StdMath.h>

double SDL_sqrt(double x)
{
	return sqrt(x);
}

float SDL_sqrtf(float x)
{
	return (float)sqrt(x);
}

double SDL_pow(double x, double y)
{
	return pow(x, y);
}

float SDL_powf(float x, float y)
{
	return (float)pow((float)x, (float)y);
}
