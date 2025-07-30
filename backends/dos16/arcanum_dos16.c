/**
 * DOS 16-bit Main Engine Implementation
 * Core engine functions for Borland C++ 3.1
 */

#include "../../core/arcanum.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dos.h>
#include <stdio.h>

#ifdef ARCANUM_DOS16

/* Global engine state */
static arc_bool g_engine_initialized = ARC_FALSE;
static arc_bool g_should_quit = ARC_FALSE;
static arc_config g_engine_config;
static clock_t g_start_time;

/* File structure for DOS */
struct arc_file {
    FILE* handle;
    char mode[4];
};

arc_result arc_init(const arc_config* config)
{
    if (g_engine_initialized) {
        return ARC_ERROR_INIT;
    }
    
    if (!config) {
        return ARC_ERROR_INIT;
    }
    
    /* Copy configuration */
    g_engine_config = *config;
    
    /* Initialize timer */
    g_start_time = clock();
    
    /* Initialize graphics */
    if (arc_graphics_init(config->screen_width, config->screen_height, config->screen_bpp) != ARC_OK) {
        return ARC_ERROR_GRAPHICS;
    }
    
    /* Initialize input */
    if (arc_input_init() != ARC_OK) {
        arc_graphics_quit();
        return ARC_ERROR_INPUT;
    }
    
    /* Initialize audio if requested */
    if (config->use_sound) {
        if (arc_audio_init() != ARC_OK) {
            arc_input_quit();
            arc_graphics_quit();
            return ARC_ERROR_SOUND;
        }
    }
    
    g_engine_initialized = ARC_TRUE;
    g_should_quit = ARC_FALSE;
    
    return ARC_OK;
}

void arc_quit(void)
{
    if (!g_engine_initialized) {
        return;
    }
    
    if (g_engine_config.use_sound) {
        arc_audio_quit();
    }
    
    arc_input_quit();
    arc_graphics_quit();
    
    g_engine_initialized = ARC_FALSE;
}

arc_bool arc_should_quit(void)
{
    /* Check for ESC key or Alt+F4 equivalent */
    if (arc_key_pressed(ARC_KEY_ESCAPE)) {
        g_should_quit = ARC_TRUE;
    }
    
    return g_should_quit;
}

/* Memory management */
void* arc_malloc(arc_u32 size)
{
    return malloc((size_t)size);
}

void* arc_calloc(arc_u32 count, arc_u32 size)
{
    return calloc((size_t)count, (size_t)size);
}

void arc_free(void* ptr)
{
    if (ptr) {
        free(ptr);
    }
}

/* String functions */
arc_u32 arc_strlen(const char* str)
{
    return str ? (arc_u32)strlen(str) : 0;
}

char* arc_strcpy(char* dest, const char* src)
{
    return strcpy(dest, src);
}

char* arc_strcat(char* dest, const char* src)
{
    return strcat(dest, src);
}

int arc_strcmp(const char* str1, const char* str2)
{
    return strcmp(str1, str2);
}

/* File system */
arc_file* arc_open_file(const char* filename, const char* mode)
{
    arc_file* file;
    FILE* handle;
    
    if (!filename || !mode) {
        return NULL;
    }
    
    handle = fopen(filename, mode);
    if (!handle) {
        return NULL;
    }
    
    file = (arc_file*)arc_malloc(sizeof(arc_file));
    if (!file) {
        fclose(handle);
        return NULL;
    }
    
    file->handle = handle;
    strcpy(file->mode, mode);
    
    return file;
}

void arc_close_file(arc_file* file)
{
    if (file) {
        if (file->handle) {
            fclose(file->handle);
        }
        arc_free(file);
    }
}

arc_u32 arc_read_file(arc_file* file, void* buffer, arc_u32 size)
{
    if (!file || !file->handle || !buffer) {
        return 0;
    }
    
    return (arc_u32)fread(buffer, 1, (size_t)size, file->handle);
}

arc_u32 arc_write_file(arc_file* file, const void* buffer, arc_u32 size)
{
    if (!file || !file->handle || !buffer) {
        return 0;
    }
    
    return (arc_u32)fwrite(buffer, 1, (size_t)size, file->handle);
}

arc_bool arc_file_exists(const char* filename)
{
    FILE* file;
    
    if (!filename) {
        return ARC_FALSE;
    }
    
    file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return ARC_TRUE;
    }
    
    return ARC_FALSE;
}

/* Timing */
arc_u32 arc_get_ticks(void)
{
    clock_t current_time = clock();
    return (arc_u32)((current_time - g_start_time) * 1000L / CLOCKS_PER_SEC);
}

void arc_delay(arc_u32 ms)
{
    arc_u32 start_time = arc_get_ticks();
    while (arc_get_ticks() - start_time < ms) {
        /* Busy wait - not ideal but simple for DOS */
    }
}

#endif /* ARCANUM_DOS16 */