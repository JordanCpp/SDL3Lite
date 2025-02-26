# Greetings

# SDL3Lite - Simple Directmedia Layer Version 3 Lite
This is a lightweight implementation of the SDL3 library. 
I really like the SDL3 library, but it saddens me that with each release of a new version, support for older systems is removed. 
Therefore, I decided to write a simpler version compatible at the API level. 
To support old and new systems, architectures, and operating systems.

# Library Features

# Build for Linux
sudo apt-get install libx11-dev

sudo apt-get install libgl1-mesa-dev

git clone https://github.com/JordanCpp/SDL3Lite.git

cd SDL3Lite

cmake -Bout

cd out

make

# Integration into your project (CMake Linux or Windows)

# Support platforms.
Windows 95 and higher

Linux (XLib) Debian 3 and higher

# Support graphics API.

# Support 2D renders.

# License.
Boost Software License - Version 1.0 - August 17th, 2003

# Support compillers

![renderer](/screenshots/SDL_Renderer.jpg)
![Rects](/screenshots/Rects.jpg)
![Textures](/screenshots/Textures.jpg)
![Textures1](/screenshots/Textures1.jpg)
![Tetrahedron](/screenshots/Tetrahedron.jpg)
![Triangle](/screenshots/Triangle.jpg)

# Renderer - Screen color
```c++
#include <SDL3/SDL.h>
#include <stdio.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Renderer", 640, 480, SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        printf("Create window error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    
    if (renderer == NULL)
    {
        printf("Create renderer error: %s\n", SDL_GetError());
        return 1;
    }
    
    bool done = false;

    SDL_SetRenderDrawColor(renderer, 237, 28, 36, 0);

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
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```

# OpenGL 1.2 - Screen color

```c++
#define OPENGL_IMPLEMENTATION
#include "OpenGL.h"
#include <SDL3/SDL.h>
#include <stdio.h>

int main()
{
    OpenGL_Compatibility_Init(1, 2);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("OpenGL1", 640, 480, SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        printf("Create window error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GLContext* context = SDL_GL_CreateContext(window);

    if (context == NULL)
    {
        printf("Create context error: %s\n", SDL_GetError());
        return 1;
    }
    
    bool done = false;

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

        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

    return 0;
}

```



