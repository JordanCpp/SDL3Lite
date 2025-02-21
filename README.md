# Greetings

# SDL3Lite - Simple Directmedia Layer Version 3 Lite
This is a lightweight implementation of the SDL3 library. 
I really like the SDL3 library, but it saddens me that with each release of a new version, support for older systems is removed. 
Therefore, I decided to write a simpler version compatible at the API level. 
To support old and new systems, architectures, and operating systems.

# Library Features

# Build for Linux
sudo apt install libx11-dev
sudo apt-get install libgl1-mesa-dev

# Integration into your project (CMake Linux or Windows)

# Support platforms.
Windows 
# Support graphics API.

# Support 2D renders.

# License.
Boost Software License - Version 1.0 - August 17th, 2003

# Support compillers

# OpenGL 1.2 - Screen color

```c++
#define OPENGL_IMPLEMENTATION
#include "OpenGL.h"
#include <SDL3/SDL.h>
#include <stdio.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Window 1", 640, 480, SDL_WINDOW_OPENGL);

    if (window == NULL)
    {
        printf("Create window error: %s\n", SDL_GetError());
        return;
    }

    SDL_GLContext* context = SDL_GL_CreateContext(window);

    if (context == NULL)
    {
        printf("Create context error: %s\n", SDL_GetError());
        return;
    }

    OpenGL_Compatibility_Init(1, 2);

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
