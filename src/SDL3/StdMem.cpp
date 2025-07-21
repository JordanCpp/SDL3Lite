
#include <stdlib.h>
#include <SDL3/StdMem.h>

void SDL_FAR* SDL_malloc(size_t bytes)
{

#if defined(__TURBOC__)
	return farmalloc(bytes);
#else
	return malloc(bytes);
#endif

}

void SDL_free(void SDL_FAR* ptr)
{

#if defined(__TURBOC__)
	farfree(ptr);
#else
	free(ptr);
#endif

}
