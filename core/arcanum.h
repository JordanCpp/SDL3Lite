/**
 * Arcanum Game Engine - Unified API
 * Cross-platform retro game engine for DOS, Windows, Linux
 */

#ifndef ARCANUM_H
#define ARCANUM_H

/* Compatibility macros for different compilers */
#ifdef __BORLANDC__
    #define ARCANUM_DOS16
    #define ARCANUM_NEAR near
    #define ARCANUM_FAR far
    #define ARCANUM_HUGE huge
#elif defined(__DJGPP__)
    #define ARCANUM_DOS32
    #define ARCANUM_NEAR
    #define ARCANUM_FAR
    #define ARCANUM_HUGE
#elif defined(__WATCOMC__)
    #define ARCANUM_DOS32
    #define ARCANUM_NEAR
    #define ARCANUM_FAR
    #define ARCANUM_HUGE
#elif defined(_WIN32)
    #define ARCANUM_WIN32
    #define ARCANUM_NEAR
    #define ARCANUM_FAR
    #define ARCANUM_HUGE
#else
    #define ARCANUM_POSIX
    #define ARCANUM_NEAR
    #define ARCANUM_FAR
    #define ARCANUM_HUGE
#endif

/* Basic types */
typedef unsigned char   arc_u8;
typedef signed char     arc_s8;
typedef unsigned short  arc_u16;
typedef signed short    arc_s16;

#ifdef ARCANUM_DOS16
    typedef unsigned long   arc_u32;
    typedef signed long     arc_s32;
#else
    typedef unsigned int    arc_u32;
    typedef signed int      arc_s32;
#endif

typedef arc_u8  arc_bool;
typedef void*   arc_handle;

#ifndef NULL
    #define NULL ((void*)0)
#endif

#define ARC_TRUE    1
#define ARC_FALSE   0

/* Error codes */
typedef enum {
    ARC_OK = 0,
    ARC_ERROR_INIT = -1,
    ARC_ERROR_MEMORY = -2,
    ARC_ERROR_FILE = -3,
    ARC_ERROR_GRAPHICS = -4,
    ARC_ERROR_SOUND = -5,
    ARC_ERROR_INPUT = -6
} arc_result;

/* Graphics subsystem */
typedef struct {
    arc_u16 width;
    arc_u16 height;
    arc_u8  bpp;        /* bits per pixel */
    arc_u8  ARCANUM_FAR* buffer;
} arc_surface;

typedef struct {
    arc_u8 r, g, b;
} arc_color;

typedef struct {
    arc_s16 x, y;
} arc_point;

typedef struct {
    arc_s16 x, y;
    arc_u16 w, h;
} arc_rect;

/* Graphics API */
arc_result arc_graphics_init(arc_u16 width, arc_u16 height, arc_u8 bpp);
void arc_graphics_quit(void);
arc_surface* arc_get_screen(void);
void arc_present(void);
void arc_clear_screen(arc_u8 color);

/* Drawing functions */
void arc_put_pixel(arc_s16 x, arc_s16 y, arc_u8 color);
arc_u8 arc_get_pixel(arc_s16 x, arc_s16 y);
void arc_draw_line(arc_s16 x1, arc_s16 y1, arc_s16 x2, arc_s16 y2, arc_u8 color);
void arc_draw_rect(const arc_rect* rect, arc_u8 color);
void arc_fill_rect(const arc_rect* rect, arc_u8 color);

/* Palette functions */
void arc_set_palette_color(arc_u8 index, arc_u8 r, arc_u8 g, arc_u8 b);
void arc_get_palette_color(arc_u8 index, arc_u8* r, arc_u8* g, arc_u8* b);
void arc_set_palette(const arc_color* palette, arc_u16 count);

/* Input subsystem */
typedef enum {
    ARC_KEY_ESCAPE = 1,
    ARC_KEY_1, ARC_KEY_2, ARC_KEY_3, ARC_KEY_4, ARC_KEY_5,
    ARC_KEY_6, ARC_KEY_7, ARC_KEY_8, ARC_KEY_9, ARC_KEY_0,
    ARC_KEY_Q, ARC_KEY_W, ARC_KEY_E, ARC_KEY_R, ARC_KEY_T,
    ARC_KEY_Y, ARC_KEY_U, ARC_KEY_I, ARC_KEY_O, ARC_KEY_P,
    ARC_KEY_A, ARC_KEY_S, ARC_KEY_D, ARC_KEY_F, ARC_KEY_G,
    ARC_KEY_H, ARC_KEY_J, ARC_KEY_K, ARC_KEY_L,
    ARC_KEY_Z, ARC_KEY_X, ARC_KEY_C, ARC_KEY_V, ARC_KEY_B,
    ARC_KEY_N, ARC_KEY_M,
    ARC_KEY_SPACE = 57,
    ARC_KEY_ENTER = 28,
    ARC_KEY_UP = 72,
    ARC_KEY_DOWN = 80,
    ARC_KEY_LEFT = 75,
    ARC_KEY_RIGHT = 77
} arc_keycode;

typedef enum {
    ARC_MOUSE_LEFT = 1,
    ARC_MOUSE_RIGHT = 2,
    ARC_MOUSE_MIDDLE = 4
} arc_mouse_button;

/* Input API */
arc_result arc_input_init(void);
void arc_input_quit(void);
void arc_input_update(void);

arc_bool arc_key_pressed(arc_keycode key);
arc_bool arc_key_down(arc_keycode key);
arc_bool arc_key_up(arc_keycode key);

arc_bool arc_mouse_button_pressed(arc_mouse_button button);
arc_bool arc_mouse_button_down(arc_mouse_button button);
arc_bool arc_mouse_button_up(arc_mouse_button button);
void arc_get_mouse_pos(arc_s16* x, arc_s16* y);

/* Audio subsystem */
typedef struct arc_sound arc_sound;

/* Audio API */
arc_result arc_audio_init(void);
void arc_audio_quit(void);

/* Simple beep for PC Speaker */
void arc_beep(arc_u16 frequency, arc_u16 duration_ms);

/* Sound loading and playing (for SoundBlaster and modern systems) */
arc_sound* arc_load_sound(const char* filename);
void arc_free_sound(arc_sound* sound);
void arc_play_sound(arc_sound* sound);

/* File system */
typedef struct arc_file arc_file;

arc_file* arc_open_file(const char* filename, const char* mode);
void arc_close_file(arc_file* file);
arc_u32 arc_read_file(arc_file* file, void* buffer, arc_u32 size);
arc_u32 arc_write_file(arc_file* file, const void* buffer, arc_u32 size);
arc_bool arc_file_exists(const char* filename);

/* Memory management */
void* arc_malloc(arc_u32 size);
void* arc_calloc(arc_u32 count, arc_u32 size);
void arc_free(void* ptr);

/* String functions */
arc_u32 arc_strlen(const char* str);
char* arc_strcpy(char* dest, const char* src);
char* arc_strcat(char* dest, const char* src);
int arc_strcmp(const char* str1, const char* str2);

/* Engine lifecycle */
typedef struct {
    arc_u16 screen_width;
    arc_u16 screen_height;
    arc_u8  screen_bpp;
    arc_bool use_sound;
    const char* window_title;
} arc_config;

arc_result arc_init(const arc_config* config);
void arc_quit(void);
arc_bool arc_should_quit(void);

/* Timing */
arc_u32 arc_get_ticks(void);
void arc_delay(arc_u32 ms);

#endif /* ARCANUM_H */