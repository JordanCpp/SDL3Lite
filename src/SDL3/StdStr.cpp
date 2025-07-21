
#include <string.h>
#include <SDL3/StdStr.h>

size_t SDL_strlen(const char* source)
{
	return strlen(source);
}

size_t SDL_strlcpy(char* dst, const char* src, size_t size)
{
    size_t src_len = 0;

    while (src[src_len] != '\0')
    {
        src_len++;
    }

    if (size == 0) 
    {
        return src_len;
    }

    size_t i;

    for (i = 0; i < size - 1 && src[i] != '\0'; i++) {
        dst[i] = src[i];
    }

    dst[i] = '\0';

    return src_len;
}

size_t SDL_strlcat(char* dst, const char* src, size_t size) 
{
    size_t dst_len = 0;
    size_t src_len = 0;

    while (dst_len < size && dst[dst_len] != '\0') 
    {
        dst_len++;
    }

    while (src[src_len] != '\0') 
    {
        src_len++;
    }

    if (dst_len == size) 
    {
        return size + src_len;
    }

    size_t i;

    for (i = 0; i < size - dst_len - 1 && src[i] != '\0'; i++) 
    {
        dst[dst_len + i] = src[i];
    }

    dst[dst_len + i] = '\0';

    return dst_len + src_len;
}
