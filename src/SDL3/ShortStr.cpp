
#include <SDL3/StdMem.h>
#include <SDL3/StdStr.h>
#include <SDL3/ShortStr.hpp>

ShortString::ShortString()
{
	Clear();
}

void ShortString::Clear()
{
	SDL_memset(_message, 0, Max);
}

void ShortString::Append(const char* source)
{
	SDL_strlcat(_message, source, Max);
}

const char* ShortString::Str()
{
	return _message;
}
