
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
endif()

if (UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    link_libraries(${X11_LIBRARIES})
    include_directories(${X11_INCLUDE_DIR})
endif()

if (WIN32)
    set(DEPS_LIBRARIES gdi32 user32 winmm opengl32)
elseif (UNIX AND NOT APPLE)
    set(DEPS_LIBRARIES X11 GL dl)
endif()

include_directories("include")
include_directories("dependencies")

if (WIN32)
    FILE(GLOB PLATFORM_SOURCES "source/Platforms/Win32/*.cpp")
elseif (UNIX AND NOT APPLE)
    FILE(GLOB PLATFORM_SOURCES "source/Platforms/Unix/*.cpp")
endif()

FILE(GLOB SHARED_SOURCES "source/Shared/*.cpp" "dependencies/simplebmp/*.cpp")
FILE(GLOB SDL3_SOURCES   "source/SDL3/*.cpp")

FILE(GLOB RENDER_SOURCES
"source/OpenGL/*.cpp" 
"source/Renders/Software/*.cpp"
"source/Renders/OpenGL1/*.cpp")

add_library(SDL3 SHARED ${PLATFORM_SOURCES} ${SHARED_SOURCES} ${SDL3_SOURCES} ${RENDER_SOURCES})
target_link_libraries(SDL3 ${DEPS_LIBRARIES})

add_executable(OpenGL1 "OpenGL1.c")
target_link_libraries(OpenGL1 SDL3)

add_executable(Rects "Rects.c")
target_link_libraries(Rects SDL3)

add_executable(Renderer "Renderer.c")
target_link_libraries(Renderer SDL3)

add_executable(Textures "Textures.c")
target_link_libraries(Textures SDL3)

add_executable(Window "Window.c")
target_link_libraries(Window SDL3)

add_executable(Tests "Tests.cpp" ${PLATFORM_SOURCES} ${SHARED_SOURCES} ${SDL3_SOURCES} ${RENDER_SOURCES})
target_link_libraries(Tests ${DEPS_LIBRARIES})
