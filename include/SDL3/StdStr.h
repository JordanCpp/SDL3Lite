
#ifndef SDL3_StdStr_h
#define SDL3_StdStr_h

#include <SDL3/Types.h>

size_t SDL_strlen(const char* source);
size_t SDL_strlcpy(char* dst, const char* src, size_t size);
size_t SDL_strlcat(char* dst, const char* src, size_t size);

#endif
