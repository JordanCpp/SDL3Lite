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

#define WINDOW_WIDTH  (640)
#define WINDOW_HEIGTH (480)
#define WINDOW_FLAGS  (SDL_WINDOW_OPENGL)

int main()
{
    SDL_Window* window     = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* surface   = NULL;
    SDL_Texture* texture   = NULL;
    bool done              = false;

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Init error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Renderer", WINDOW_WIDTH, WINDOW_HEIGTH, WINDOW_FLAGS);
    if (window == NULL)
    {
        SDL_Log("Create window error: %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL)
    {
        SDL_Log("Create renderer error: %s\n", SDL_GetError());
        return 1;
    }
    
    surface = SDL_LoadBMP("sample.bmp");
    if (surface == NULL)
    {
        SDL_Log("Load bmp error: %s\n", SDL_GetError());
        return 1;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        SDL_Log("Create texture error: %s\n", SDL_GetError());
        return 1;
    }

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

        SDL_SetRenderDrawColor(renderer, 237, 28, 36, 0);
        SDL_RenderClear(renderer);

        SDL_RenderTexture(renderer, texture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
