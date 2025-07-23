
add_compile_definitions(-DSDL3LITE_SHARED)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)  
endif() 

include_directories("include")
include_directories("src")

if (WIN32)
    set(PLATFORM_FOLDER "Win32")
    set(DEPS_LIBRARIES gdi32 user32 winmm opengl32)
elseif (UNIX AND NOT APPLE)
    set(PLATFORM_FOLDER "Unix")
    set(DEPS_LIBRARIES X11 GL dl)
endif()

FILE(GLOB SDL3LITE_SOURCES "src/SDL3/*.cpp")

add_library(SDL3 SHARED ${SDL3LITE_SOURCES})
target_link_libraries(SDL3 ${DEPS_LIBRARIES})

add_executable(tests "tests.cpp" ${SDL3LITE_SOURCES})
target_link_libraries(tests ${DEPS_LIBRARIES})

add_executable(main "main.c")
target_link_libraries(main SDL3)
