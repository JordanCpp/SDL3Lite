# SDL3Lite - Simple Directmedia Layer Version 3 Lite

This is a lightweight implementation of the SDL3 library. 

I really like the SDL3 library, but it saddens me that with each release of a new version, support for older systems is removed. 
Therefore, I decided to write a simpler version compatible at the API level. 
To support old and new systems, architectures, and operating systems.

## Library Features

To be described later (TBD)

## Build for Linux

```shell
# Install dependencies
$ sudo apt-get install libx11-dev
$ sudo apt-get install libgl1-mesa-dev

# Clone this repository & go into its directory
$ git clone https://github.com/JordanCpp/SDL3Lite.git
$ cd SDL3Lite

# Generate Makefile
$ cmake -Bout
$ cd out

# Build library
$ make
```

## Integration into your project (CMake Linux or Windows)

TBD

## Supported platforms

- Windows 95 and higher
- Linux (XLib) Debian 3 and higher

## Supported graphics API

- OpenGL >= 1.0 and <= 4.6

## Supported 2D renders

- OpenGL 1.2
- Software

## License

Boost Software License - Version 1.0 - August 17th, 2003

## Supported compillers

TBD

## Screenshots

![renderer](/screenshots/SDL_Renderer.jpg)
![Rects](/screenshots/Rects.jpg)
![Textures](/screenshots/Textures.jpg)
![Textures1](/screenshots/Textures1.jpg)
![Textures2](/screenshots/examples_renderer_textures.jpg)
![Tetrahedron](/screenshots/Tetrahedron.jpg)
![Triangle](/screenshots/Triangle.jpg)

## Examples

### Renderer - Screen color

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

### OpenGL 3.3 - Triangle

```c++
#define OPENGL_IMPLEMENTATION
#include "OpenGL.h"
#include <SDL3/SDL.h>
#include <math.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

#define WINDOW_WIDTH  (640)
#define WINDOW_HEIGTH (480)

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Init error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_Window* window = SDL_CreateWindow("OpenGL1", WINDOW_WIDTH, WINDOW_HEIGTH, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        SDL_Log("Create window error: %s\n", SDL_GetError());
        return 1;
    }

    OpenGL_Compatibility_Init(3, 3);

    SDL_GLContext* context = SDL_GL_CreateContext(window);
    if (context == NULL)
    {
        SDL_Log("Create context error: %s\n", SDL_GetError());
        return 1;
    }
    
    bool done = false;

    // Specify the viewport of OpenGL in the Window
    // In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGTH);

    // Create Vertex Shader Object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);

    // Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);

    // Create Shader Program Object and get its reference
    GLuint shaderProgram = glCreateProgram();
    // Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(shaderProgram);

    // Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Vertices coordinates
    GLfloat vertices[] =
    {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
         0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
         0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
    };

    // Create reference containers for the Vartex Array Object and the Vertex Buffer Object
    GLuint VAO, VBO;

    // Generate the VAO and VBO with only 1 object each
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);

    // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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

        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
        // Tell OpenGL which Shader Program we want to use
        glUseProgram(shaderProgram);
        // Bind the VAO so OpenGL knows to use it
        glBindVertexArray(VAO);
        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        SDL_GL_SwapWindow(window);
    }

    // Delete all the objects we've created
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

    return 0;
}
```

### OpenGL 1.2 - Triangle

```c++
#define OPENGL_IMPLEMENTATION
#include "OpenGL.h"
#include <SDL3/SDL.h>

int main()
{
    OpenGL_Compatibility_Init(1, 2);

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Init error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("OpenGL1", 640, 480, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        SDL_Log("Create window error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_GLContext* context = SDL_GL_CreateContext(window);
    if (context == NULL)
    {
        SDL_Log("Create context error: %s\n", SDL_GetError());
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

        glClear(GL_DEPTH_BUFFER_BIT);

        glBegin(GL_POLYGON);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.6f, -0.75f, 0.5f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.6f , -0.75f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f , 0.75f , 0.0f);
        glEnd();
        
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

    return 0;
}
```
