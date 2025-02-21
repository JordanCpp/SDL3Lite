
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
    set(libs gdi32 user32 winmm opengl32)
elseif (UNIX AND NOT APPLE)
    set(libs X11 GL dl)
endif()

include_directories("include")
include_directories("dependencies")

if (WIN32)
    FILE(GLOB PLATFORM_SOURCES "source/Platforms/Win32/*.cpp")
elseif (UNIX AND NOT APPLE)
    FILE(GLOB PLATFORM_SOURCES "source/Platforms/Unix/*.cpp")
endif()

FILE(GLOB SHARED_SOURCES 
"source/Shared/*.cpp" 
"source/SDL3/*.cpp" 
"source/OpenGL/*.cpp" 
"source/Renders/Software/*.cpp"
"source/Renders/OpenGL1/*.cpp")

add_library(SDL3 SHARED ${SHARED_SOURCES} ${PLATFORM_SOURCES})
target_link_libraries(SDL3 ${libs} )

add_executable(OpenGL1 "OpenGL1.c")
target_link_libraries(OpenGL1 SDL3)

add_executable(Renderer "Renderer.c")
target_link_libraries(Renderer SDL3)

add_executable(Window "Window.c")
target_link_libraries(Window SDL3)
