
if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)  
endif()

if (UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    link_libraries(${X11_LIBRARIES})
    include_directories(${X11_INCLUDE_DIR})
endif()

if (WIN32)
    set(PLATFORM_FOLDER "Win32")
    set(DEPS_LIBRARIES gdi32 user32 winmm opengl32)
elseif (UNIX AND NOT APPLE)
    set(PLATFORM_FOLDER "Unix")
    set(DEPS_LIBRARIES X11 GL dl)
endif()

include_directories("include")
include_directories("dependencies")

FILE(GLOB SOURCES
"source/OpenGL/*.cpp" 
"source/Platforms/${PLATFORM_FOLDER}/*.cpp"
"source/Renders/Software/*.cpp"
"source/Renders/OpenGL1/*.cpp"
"source/SDL3/*.cpp"
"source/Shared/*.cpp")

add_library(SDL3 SHARED ${SOURCES})
target_link_libraries(SDL3 ${DEPS_LIBRARIES})

add_executable(Tests "Tests.cpp" ${SOURCES})
target_link_libraries(Tests ${DEPS_LIBRARIES})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sample.bmp DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

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

add_executable(GL1_Triangle "GL1_Triangle.c")
target_link_libraries(GL1_Triangle SDL3)

add_executable(GL1_Tetrahedron "GL1_Tetrahedron.c")
target_link_libraries(GL1_Tetrahedron SDL3)

add_executable(GL3_Triangle "GL3_Triangle.cpp")
target_link_libraries(GL3_Triangle SDL3)
