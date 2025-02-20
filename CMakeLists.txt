
include_directories("include")

if (WIN32)
    FILE(GLOB PLATFORM_SOURCES "source/Platforms/Win32/*.cpp")
elseif (UNIX AND NOT APPLE)
    FILE(GLOB PLATFORM_SOURCES "source/Platforms/UNIX/*.cpp")
endif()

FILE(GLOB SHARED_SOURCES "source/Shared/*.cpp" "source/SDL3/*.cpp" "source/OpenGL/*.cpp" "source/Renders/Software/*.cpp")

add_library(SDL3 SHARED ${SHARED_SOURCES} ${PLATFORM_SOURCES})
target_link_libraries(SDL3 gdi32 opengl32)

add_executable(main "main.c")
target_link_libraries(main SDL3)
