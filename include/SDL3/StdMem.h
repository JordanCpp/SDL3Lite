
#ifndef SDL3_StdMem_h
#define SDL3_StdMem_h

#include <SDL3/Types.h>

void SDL_FAR* SDL_malloc(size_t bytes);
void SDL_free(void SDL_FAR* ptr);
void SDL_FAR* SDL_memset(void SDL_FAR* dst, int c, size_t len);

#endif
