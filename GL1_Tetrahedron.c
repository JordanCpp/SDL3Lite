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

//https://cs.lmu.edu/~ray/notes/openglexamples/

#define OPENGL_IMPLEMENTATION
#include "OpenGL.h"
#include <SDL3/SDL.h>

// Clears the window and draws the tetrahedron.  The tetrahedron is  easily
// specified with a triangle strip, though the specification really isn't very
// easy to read.
void display() 
{
    GLfloat i = 0;

    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a white grid "floor" for the tetrahedron to sit on.
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);

    for (i = -2.5; i <= 2.5; i += 0.25) 
    {
        glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
        glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);
    }

    glEnd();

    // Draw the tetrahedron.  It is a four sided figure, so when defining it
    // with a triangle strip we have to repeat the last two vertices.
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0f, 1.0f, 1.0f); glVertex3f( 0.0f, 2.0f,  0.0f);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, 0.0f,  1.0f);
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f( 1.0f, 0.0f,  1.0f);
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f( 0.0f, 0.0f, -1.4f);
    glColor3f(1.0f, 1.0f, 1.0f); glVertex3f( 0.0f, 2.0f,  0.0f);
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, 0.0f,  1.0f);
    glEnd();

    glFlush();
}

// Sets up global attributes like clear color and drawing color, enables and
// initializes any needed modes (in this case we want backfaces culled), and
// sets up the desired projection and modelview matrices. It is cleaner to
// define these operations in a function separate from main().
void init() 
{

    // Set the current clear color to sky blue and the current drawing color to
    // white.
    glClearColor(0.1f, 0.39f, 0.88f, 1.0f);
    glColor3f(1.0, 1.0, 1.0);

    // Tell the rendering engine not to draw backfaces.  Without this code,
    // all four faces of the tetrahedron would be drawn and it is possible
    // that faces farther away could be drawn after nearer to the viewer.
    // Since there is only one closed polyhedron in the whole scene,
    // eliminating the drawing of backfaces gives us the realism we need.
    // THIS DOES NOT WORK IN GENERAL.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Set the camera lens so that we have a perspective viewing volume whose
    // horizontal bounds at the near clipping plane are -2..2 and vertical
    // bounds are -1.5..1.5.  The near clipping plane is 1 unit from the camera
    // and the far clipping plane is 40 units away.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-2, 2, -1.5, 1.5, 1, 40);

    // Set up transforms so that the tetrahedron which is defined right at
    // the origin will be rotated and moved into the view volume.  First we
    // rotate 70 degrees around y so we can see a lot of the left side.
    // Then we rotate 50 degrees around x to "drop" the top of the pyramid
    // down a bit.  Then we move the object back 3 units "into the screen".
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -3);
    glRotatef(50, 1, 0, 0);
    glRotatef(70, 0, 1, 0);
}

#define WINDOW_WIDTH  (640)
#define WINDOW_HEIGTH (480)

int main()
{
    SDL_Window* window     = NULL;
    SDL_GLContext* context = NULL;
    bool done              = false;

    OpenGL_Compatibility_Init(1, 2);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Init error: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("OpenGL1", WINDOW_WIDTH, WINDOW_HEIGTH, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        SDL_Log("Create window error: %s\n", SDL_GetError());
        return 1;
    }

    context = SDL_GL_CreateContext(window);
    if (context == NULL)
    {
        SDL_Log("Create context error: %s\n", SDL_GetError());
        return 1;
    }
    
    init();

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

        display();
        
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

    return 0;
}
