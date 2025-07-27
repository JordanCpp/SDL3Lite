/*
 * SDL3Lite - Simple Directmedia Layer Version 3 Lite
 * Copyright (c) 2025 JordanCpp
 *
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE or copy at https://www.boost.org/LICENSE_1_0.txt)
 */

#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/Result.hpp>
#include <SDL3/BaseWin.hpp>
#include <SDL3/BaseRndr.hpp>
#include <SDL3/EventH.hpp>
#include <SDL3/Pixels.hpp>
#include <SDL3/Surface.hpp>
#include <SDL3/PixPaint.hpp>

void SDL3LiteTest(bool expression, const char* file, int line, const char* detail)
{
    if (!expression)
    {
        printf("Test fail! Expression: %s File: %s Line: %d \n", detail, file, line);
    }
}

void SDL3LiteTestToFile(bool expression, const char* file, int line, const char* detail)
{
    if (!expression)
    {
        FILE* output = fopen("Tests.txt", "a");

        if (output != NULL)
        {
            fprintf(output, "Test fail! Expression: %s File: %s Line: %d \n", detail, file, line);

            fclose(output);
        }
    }
}

#if defined(__MSDOS__)
    #define SDL_TEST(expression) SDL3LiteTestToFile(expression, __FILE__, __LINE__, #expression)
#else
    #define SDL_TEST(expression) SDL3LiteTest(expression, __FILE__, __LINE__, #expression)
#endif  

void SDL_MemoryTest()
{
    SDL_TEST(SDL_malloc(0) == NULL);

    Uint8 SDL_FAR* memory = (Uint8 SDL_FAR*)SDL_malloc(1024);
    SDL_TEST(memory != NULL);

    SDL_memset(memory, 42, 1024);

    for (size_t i = 0; i < 1024; i++)
    {
        SDL_TEST(memory[i] == 42);
    }

    Uint8 SDL_FAR* memory2 = (Uint8 SDL_FAR*)SDL_malloc(1024);
    SDL_TEST(memory2 != NULL);

    SDL_memset(memory2, 77, 1024);

    SDL_memcpy(memory, memory2, 1024);

    for (size_t j = 0; j < 1024; j++)
    {
        SDL_TEST(memory[j] == 77);
    }

    SDL_free(memory);
    SDL_free(memory2);
}

void SDL_ShortStringTest()
{
    ShortString shortString;

    SDL_TEST(shortString.GetStr() != NULL);
    SDL_TEST(SDL_strcmp(shortString.GetStr(), "") == 0);

    shortString.Assign("Hello ");
    SDL_TEST(SDL_strcmp(shortString.GetStr(), "Hello ") == 0);

    shortString.Append("world!");
    SDL_TEST(SDL_strcmp(shortString.GetStr(), "Hello world!") == 0);

    shortString.Clear();
    SDL_TEST(SDL_strcmp(shortString.GetStr(), "") == 0);
}

void SDL_ResultTest()
{
    Result result;

    SDL_TEST(result.Ok() == true);
    SDL_TEST(result.Message() != NULL);
    SDL_TEST(SDL_strcmp(result.Message(), "") == 0);

    result.Message("Hello");
    SDL_TEST(result.Ok() == false);
    SDL_TEST(result.Message() != NULL);
    SDL_TEST(SDL_strcmp(result.Message(), "Hello") == 0);

    result.Message("Hello ", "world!");
    SDL_TEST(result.Ok() == false);
    SDL_TEST(result.Message() != NULL);
    SDL_TEST(SDL_strcmp(result.Message(), "Hello world!") == 0);

    result.Clear();
    SDL_TEST(result.Ok() == true);
    SDL_TEST(result.Message() != NULL);
    SDL_TEST(SDL_strcmp(result.Message(), "") == 0);
}

void SDL_StringTest()
{
    SDL_TEST(SDL_strlen("Hello") == 5);

    SDL_TEST(SDL_strcmp("Hello", "Hello")  == 0);
    SDL_TEST(SDL_strcmp("Hello", "World!") != 0);

    const size_t max = 32;
    char text[max];
    SDL_TEST(SDL_strlcpy(text, "Hello ", max) == 6);
    SDL_TEST(SDL_strcmp(text, "Hello ")       == 0);

    SDL_TEST(SDL_strlcat(text, "world!", max) == 12);
    SDL_TEST(SDL_strcmp(text, "Hello world!") == 0);
}

void SDL_BaseWindowTest()
{
    SDL_Point pos = { 15, 30 };
    SDL_Point size = { 320, 200 };

    BaseWindow baseWindow(pos, size, "Base window title");
    SDL_TEST(baseWindow.GetPos().x == 15);
    SDL_TEST(baseWindow.GetPos().y == 30);
    SDL_TEST(baseWindow.GetSize().x == 320);
    SDL_TEST(baseWindow.GetSize().y == 200);
    SDL_TEST(SDL_strcmp(baseWindow.GetTitle(), "Base window title") == 0);

    pos.x = 45;
    pos.y = 95;
    baseWindow.SetPos(pos);
    SDL_TEST(baseWindow.GetPos().x == 45);
    SDL_TEST(baseWindow.GetPos().y == 95);

    size.x = 640;
    size.y = 480;
    baseWindow.SetSize(size);
    SDL_TEST(baseWindow.GetSize().x == 640);
    SDL_TEST(baseWindow.GetSize().y == 480);

    baseWindow.SetTitle("New title window");
    SDL_TEST(SDL_strcmp(baseWindow.GetTitle(), "New title window") == 0);
}

void SDL_EventQueueTest()
{
    EventQueue eventQueue;
    SDL_TEST(eventQueue.IsEmpty() == true);
    SDL_TEST(eventQueue.IsFull()  == false);

    SDL_Event event;
    for (size_t i = 0; i < EventQueue::Max; i++)
    {
        event.type = SDL_EVENT_QUIT;
        eventQueue.Enqueue(event);
    }

    SDL_TEST(eventQueue.IsEmpty() == false);
    SDL_TEST(eventQueue.IsFull()  == true);

    for (size_t j = 0; j < EventQueue::Max; j++)
    {
        SDL_Event event2;
        SDL_TEST(eventQueue.Dequeue(event2) == true);
        SDL_TEST(event2.type == SDL_EVENT_QUIT);
    }

    SDL_TEST(eventQueue.IsEmpty() == true);
    SDL_TEST(eventQueue.IsFull() == false);
}

void SDL_EventHandlerTest()
{
    EventHandler eventHandler;
    SDL_TEST(eventHandler.Running() == true);
    SDL_TEST(eventHandler.Empty()   == true);

    SDL_Event event;
    for (size_t i = 0; i < EventQueue::Max; i++)
    {
        event.type = SDL_EVENT_QUIT;
        eventHandler.Push(event);
        SDL_TEST(eventHandler.Running() == true);
        SDL_TEST(eventHandler.Empty()   == false);
    }

    SDL_Event event2;
    for (size_t j = 0; j < EventQueue::Max; j++)
    {
        SDL_TEST(eventHandler.Pop(event2) == true);
        SDL_TEST(event2.type              == SDL_EVENT_QUIT);
        SDL_TEST(eventHandler.Running()   == true);
    }

    SDL_TEST(eventHandler.Running() == true);
    SDL_TEST(eventHandler.Empty()   == true);

    eventHandler.Stop();
    SDL_TEST(eventHandler.Running() == false);
    SDL_TEST(eventHandler.Empty()   == true);
}

void SDL_BaseRenderTest()
{
    BaseRender baseRender("Base render");
    SDL_TEST(baseRender.GetColor().r == 0);
    SDL_TEST(baseRender.GetColor().g == 0);
    SDL_TEST(baseRender.GetColor().b == 0);
    SDL_TEST(baseRender.GetColor().a == 255);
    SDL_TEST(SDL_strcmp(baseRender.GetName(), "Base render") == 0);

    SDL_Color color = { 1, 2, 3, 4 };
    baseRender.SetColor(color);
    SDL_TEST(baseRender.GetColor().r == 1);
    SDL_TEST(baseRender.GetColor().g == 2);
    SDL_TEST(baseRender.GetColor().b == 3);
    SDL_TEST(baseRender.GetColor().a == 4);

    baseRender.SetName("New base render");
    SDL_TEST(SDL_strcmp(baseRender.GetName(), "New base render") == 0);
}

void SDL_PixelsTest()
{
    SDL_TEST(PixelFormatToBytesPerPixels(SDL_PIXELFORMAT_UNKNOWN) == 0);
    SDL_TEST(PixelFormatToBytesPerPixels(SDL_PIXELFORMAT_INDEX8)  == 1);
    SDL_TEST(PixelFormatToBytesPerPixels(SDL_PIXELFORMAT_RGB24)   == 3);
    SDL_TEST(PixelFormatToBytesPerPixels(SDL_PIXELFORMAT_BGR24)   == 3);
}

void SDL_ColorDistanceTest()
{
    SDL_Color c1 = { 0, 0, 0, 255 };
    SDL_Color c2 = { 3, 4, 0, 255 };
    // sqrt(3^2 + 4^2 + 0^2) = 5
    SDL_TEST(ColorDistance(c1, c2) == 5.0);

    SDL_Color c3 = { 10, 20, 30, 255 };
    SDL_Color c4 = { 13, 24, 30, 255 };
    // sqrt((13-10)^2 + (24-20)^2 + (30-30)^2) = sqrt(9 + 16 + 0) = sqrt(25) = 5
    SDL_TEST(ColorDistance(c3, c4) == 5.0);

    SDL_Color c5 = { 0, 0, 0, 255 };
    SDL_Color c6 = { 0, 0, 0, 255 };
    SDL_TEST(ColorDistance(c5, c6) == 0.0);
}

void SDL_FindClosestColorTest()
{
    SDL_Color palette[3] = 
    {
        {0, 0, 0, 255},     // black
        {255, 0, 0, 255},   // red
        {0, 255, 0, 255}    // green
    };

    // red
    SDL_Color target1 = { 250, 10, 10, 255 };
    SDL_Color closest1 = FindClosestColor(target1, palette, 3);
    SDL_TEST(closest1.r == 255 && closest1.g == 0 && closest1.b == 0);

    // green
    SDL_Color target2 = { 5, 250, 5, 255 };
    SDL_Color closest2 = FindClosestColor(target2, palette, 3);
    SDL_TEST(closest2.r == 0 && closest2.g == 255 && closest2.b == 0);

    // black
    SDL_Color target3 = { 0, 0, 0, 255 };
    SDL_Color closest3 = FindClosestColor(target3, palette, 3);
    SDL_TEST(closest3.r == 0 && closest3.g == 0 && closest3.b == 0);

    SDL_Color palette2[2] = 
    {
        {10, 10, 10, 255},
        {10, 10, 10, 255}
    };

    SDL_Color target4 = { 10, 10, 10, 255 };
    SDL_Color closest4 = FindClosestColor(target4, palette2, 2);
    SDL_TEST(closest4.r == 10 && closest4.g == 10 && closest4.b == 10);
}

void SDL_FindClosestIndexTest()
{
    SDL_Color palette[4] = 
    {
        {0, 0, 0, 255},     // 0: black
        {255, 0, 0, 255},   // 1: red
        {0, 255, 0, 255},   // 2: green
        {0, 0, 255, 255}    // 3: blue
    };

    // red
    SDL_Color target1 = { 250, 10, 10, 255 };
    Uint8 idx1 = FindClosestIndex(target1, palette, 4);
    SDL_TEST(idx1 == 1);

    // green
    SDL_Color target2 = { 5, 250, 5, 255 };
    Uint8 idx2 = FindClosestIndex(target2, palette, 4);
    SDL_TEST(idx2 == 2);

    // blue
    SDL_Color target3 = { 10, 10, 240, 255 };
    Uint8 idx3 = FindClosestIndex(target3, palette, 4);
    SDL_TEST(idx3 == 3);

    // black
    SDL_Color target4 = { 0, 0, 0, 255 };
    Uint8 idx4 = FindClosestIndex(target4, palette, 4);
    SDL_TEST(idx4 == 0);

    SDL_Color palette2[2] = 
    {
        {10, 10, 10, 255},
        {10, 10, 10, 255}
    };
    SDL_Color target5 = { 10, 10, 10, 255 };
    Uint8 idx5 = FindClosestIndex(target5, palette2, 2);
    SDL_TEST(idx5 == 0);
}

void SDL_StdMathTest()
{
    // SDL_sqrt
    SDL_TEST(SDL_fabs(SDL_sqrt(9.0) - 3.0) < 1e-9);
    SDL_TEST(SDL_fabs(SDL_sqrt(0.0) - 0.0) < 1e-9);
    SDL_TEST(SDL_fabs(SDL_sqrt(1.0) - 1.0) < 1e-9);

    // SDL_sqrtf
    SDL_TEST(SDL_fabsf(SDL_sqrtf(16.0f) - 4.0f) < 1e-6f);
    SDL_TEST(SDL_fabsf(SDL_sqrtf(0.0f) - 0.0f)  < 1e-6f);

    // SDL_pow
    SDL_TEST(SDL_fabs(SDL_pow(2.0, 3.0) - 8.0) < 1e-9);
    SDL_TEST(SDL_fabs(SDL_pow(5.0, 0.0) - 1.0) < 1e-9);
    SDL_TEST(SDL_fabs(SDL_pow(9.0, 0.5) - 3.0) < 1e-9);

    // SDL_powf
    SDL_TEST(SDL_fabsf(SDL_powf(2.0f, 4.0f) - 16.0f) < 1e-6f);
    SDL_TEST(SDL_fabsf(SDL_powf(10.0f, 0.0f) - 1.0f) < 1e-6f);
    SDL_TEST(SDL_fabsf(SDL_powf(25.0f, 0.5f) - 5.0f) < 1e-6f);

    // SDL_fabs
    SDL_TEST(SDL_fabs(SDL_fabs(-5.0) - 5.0) < 1e-9);
    SDL_TEST(SDL_fabs(SDL_fabs(5.0) - 5.0)  < 1e-9);

    // SDL_fabsf
    SDL_TEST(SDL_fabsf(SDL_fabsf(-7.0f) - 7.0f) < 1e-6f);
    SDL_TEST(SDL_fabsf(SDL_fabsf(7.0f) - 7.0f)  < 1e-6f);
}

void SDL_SurfaceTest()
{
    SDL_Point size = { 320, 200 };
    Surface surface(size, SDL_PIXELFORMAT_INDEX8);

    SDL_TEST(surface.flags            == 0);
    SDL_TEST(surface.format           == SDL_PIXELFORMAT_INDEX8);
    SDL_TEST(surface.w                == 320);
    SDL_TEST(surface.h                == 200);
    SDL_TEST(surface.pitch            == 320);
    SDL_TEST(surface.pixels           != NULL);
    SDL_TEST(surface.refcount         == 0);
    SDL_TEST(surface.reserved         == 0);
    SDL_TEST(surface.GetBpp()         == 1);
    SDL_TEST(surface.GetPitch()       == 320);
    SDL_TEST(surface.GetPixelFormat() == SDL_PIXELFORMAT_INDEX8);
    SDL_TEST(surface.GetPixels()      != NULL);
    SDL_TEST(surface.GetPixels()      == surface.pixels);
    SDL_TEST(surface.GetSize().x      == 320);
    SDL_TEST(surface.GetSize().y      == 200);

    SDL_Surface* surface2 = SDL_CreateSurface(320, 200, SDL_PIXELFORMAT_INDEX8);
    SDL_TEST(surface2->flags    == 0);
    SDL_TEST(surface2->format   == SDL_PIXELFORMAT_INDEX8);
    SDL_TEST(surface2->w        == 320);
    SDL_TEST(surface2->h        == 200);
    SDL_TEST(surface2->pitch    == 320);
    SDL_TEST(surface2->pixels   != NULL);
    SDL_TEST(surface2->refcount == 0);
    SDL_TEST(surface2->reserved == 0);
    SDL_DestroySurface(surface2);
}

void SDL_PixelPainterIndex8Test()
{
    PixelPainter pixelPainter;

    SDL_Point size = { 16, 32 };
    Surface surface(size, SDL_PIXELFORMAT_INDEX8);

    SDL_Color color = { 1, 2, 3, 4 };
    Uint8 index     = 42;
    pixelPainter.Clear(&surface, color, index, SDL_PIXELFORMAT_INDEX8);

    size_t count = surface.GetSize().x * surface.GetSize().y * surface.GetBpp();

    for (size_t i = 0; i < count; i++)
    {
        SDL_TEST(surface.GetPixels()[i] == 42);
    }
}

void SDL_PixelPainterRgb24Test()
{
    PixelPainter pixelPainter;

    SDL_Point size = { 16, 32 };
    Surface surface(size, SDL_PIXELFORMAT_RGB24);

    SDL_Color color = { 1, 2, 3, 4 };
    Uint8 index = 42;
    pixelPainter.Clear(&surface, color, index, SDL_PIXELFORMAT_RGB24);

    size_t count = surface.GetSize().x * surface.GetSize().y * surface.GetBpp();

    for (size_t i = 0; i < count; i+=3)
    {
        SDL_TEST(surface.GetPixels()[i + 0] == color.r);
        SDL_TEST(surface.GetPixels()[i + 1] == color.g);
        SDL_TEST(surface.GetPixels()[i + 2] == color.b);
    }
}

void SDL_PixelPainterRgba32Test()
{
    PixelPainter pixelPainter;

    SDL_Point size = { 16, 32 };
    Surface surface(size, SDL_PIXELFORMAT_RGBA32);

    SDL_Color color = { 1, 2, 3, 4 };
    Uint8 index = 42;
    pixelPainter.Clear(&surface, color, index, SDL_PIXELFORMAT_RGBA32);

    size_t count = surface.GetSize().x * surface.GetSize().y * surface.GetBpp();

    for (size_t i = 0; i < count; i += 4)
    {
        SDL_TEST(surface.GetPixels()[i + 0] == color.r);
        SDL_TEST(surface.GetPixels()[i + 1] == color.g);
        SDL_TEST(surface.GetPixels()[i + 2] == color.b);
        SDL_TEST(surface.GetPixels()[i + 3] == color.a);
    }
}

int main()
{
    SDL_MemoryTest();
    SDL_ShortStringTest();
    SDL_ResultTest();
    SDL_StringTest();
    SDL_BaseWindowTest();
    SDL_EventQueueTest();
    SDL_EventHandlerTest();
    SDL_BaseRenderTest();
    SDL_PixelsTest();
    SDL_ColorDistanceTest();
    SDL_FindClosestColorTest();
    SDL_FindClosestIndexTest();
    SDL_StdMathTest();
    SDL_SurfaceTest();
    SDL_PixelPainterIndex8Test();
    SDL_PixelPainterRgb24Test();
    SDL_PixelPainterRgba32Test();

	return 0;
}
