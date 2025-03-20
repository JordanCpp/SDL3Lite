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

#include <SDL3/SDL.h>
#include <time.h>
#include <stdlib.h>

#define WINDOW_WIDTH  (640)
#define WINDOW_HEIGTH (480)
#define COUNT_RECTS   (100)

int RandomValue(int min, int max)
{
    return min + rand() % (max - min);
}

int main()
{
    SDL_Window* window     = NULL;
    SDL_Surface* surface   = NULL;
    SDL_Renderer* renderer = NULL;
    bool done              = false;
    size_t i               = 0;
    SDL_FRect rect;
    SDL_Rect viewport;

    srand(clock() / CLOCKS_PER_SEC);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Init error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Software", WINDOW_WIDTH, WINDOW_HEIGTH, 0);
    if (window == NULL)
    {
        SDL_Log("Create window error: %s\n", SDL_GetError());
        return 1;
    }

    surface = SDL_GetWindowSurface(window);
    if (surface == NULL)
    {
        SDL_Log("Get surface error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateSoftwareRenderer(surface);
    if (renderer == NULL) 
    {
        SDL_Log("Render creation for surface fail : %s\n", SDL_GetError());
        return 1;
    }

    SDL_GetRenderViewport(renderer, &viewport);

    while (!done)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                done = true;
            }
        }

        SDL_RenderClear(renderer);

        for (i = 0; i < COUNT_RECTS; i++)
        {
            SDL_SetRenderDrawColor(renderer, RandomValue(0, 255), RandomValue(0, 255), RandomValue(0, 255), 0);

            rect.x = (float)RandomValue(0, viewport.w);
            rect.y = (float)RandomValue(0, viewport.h);
            rect.w = (float)RandomValue(25, 50);
            rect.h = (float)RandomValue(25, 50);

            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);

        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
