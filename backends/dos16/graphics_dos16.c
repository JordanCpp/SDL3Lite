/**
 * DOS 16-bit Graphics Backend
 * VGA Mode 13h (320x200x256) implementation for Borland C++ 3.1
 */

#include "../../core/arcanum.h"
#include <dos.h>
#include <mem.h>
#include <conio.h>

#ifdef ARCANUM_DOS16

/* VGA registers and constants */
#define VGA_MEMORY_SEGMENT  0xA000
#define VGA_MEMORY_SIZE     64000L
#define SCREEN_WIDTH        320
#define SCREEN_HEIGHT       200

/* Global state */
static arc_surface g_screen;
static arc_u8 ARCANUM_FAR* g_vga_memory;
static arc_u8 g_old_video_mode;

/* Palette registers */
#define PALETTE_INDEX_PORT  0x03C8
#define PALETTE_DATA_PORT   0x03C9

arc_result arc_graphics_init(arc_u16 width, arc_u16 height, arc_u8 bpp)
{
    /* Only support VGA Mode 13h for DOS 16-bit */
    if (width != 320 || height != 200 || bpp != 8) {
        return ARC_ERROR_GRAPHICS;
    }
    
    /* Save current video mode */
    g_old_video_mode = *((arc_u8 ARCANUM_FAR*)MK_FP(0x40, 0x49));
    
    /* Set VGA Mode 13h (320x200x256) */
    asm {
        mov ax, 0x0013
        int 0x10
    }
    
    /* Set up screen surface */
    g_screen.width = SCREEN_WIDTH;
    g_screen.height = SCREEN_HEIGHT;
    g_screen.bpp = 8;
    g_screen.buffer = (arc_u8 ARCANUM_FAR*)MK_FP(VGA_MEMORY_SEGMENT, 0);
    
    g_vga_memory = g_screen.buffer;
    
    return ARC_OK;
}

void arc_graphics_quit(void)
{
    /* Restore original video mode */
    asm {
        mov al, g_old_video_mode
        mov ah, 0
        int 0x10
    }
}

arc_surface* arc_get_screen(void)
{
    return &g_screen;
}

void arc_present(void)
{
    /* In Mode 13h, we draw directly to video memory */
    /* No double buffering in this simple implementation */
}

void arc_clear_screen(arc_u8 color)
{
    _fmemset(g_vga_memory, color, VGA_MEMORY_SIZE);
}

void arc_put_pixel(arc_s16 x, arc_s16 y, arc_u8 color)
{
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        g_vga_memory[y * SCREEN_WIDTH + x] = color;
    }
}

arc_u8 arc_get_pixel(arc_s16 x, arc_s16 y)
{
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        return g_vga_memory[y * SCREEN_WIDTH + x];
    }
    return 0;
}

void arc_draw_line(arc_s16 x1, arc_s16 y1, arc_s16 x2, arc_s16 y2, arc_u8 color)
{
    /* Bresenham's line algorithm */
    arc_s16 dx, dy, sx, sy, err, e2;
    
    dx = x2 > x1 ? x2 - x1 : x1 - x2;
    dy = y2 > y1 ? y2 - y1 : y1 - y2;
    sx = x1 < x2 ? 1 : -1;
    sy = y1 < y2 ? 1 : -1;
    err = dx - dy;
    
    while (1) {
        arc_put_pixel(x1, y1, color);
        
        if (x1 == x2 && y1 == y2) break;
        
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void arc_draw_rect(const arc_rect* rect, arc_u8 color)
{
    if (!rect) return;
    
    /* Top and bottom lines */
    arc_draw_line(rect->x, rect->y, rect->x + rect->w - 1, rect->y, color);
    arc_draw_line(rect->x, rect->y + rect->h - 1, rect->x + rect->w - 1, rect->y + rect->h - 1, color);
    
    /* Left and right lines */
    arc_draw_line(rect->x, rect->y, rect->x, rect->y + rect->h - 1, color);
    arc_draw_line(rect->x + rect->w - 1, rect->y, rect->x + rect->w - 1, rect->y + rect->h - 1, color);
}

void arc_fill_rect(const arc_rect* rect, arc_u8 color)
{
    arc_s16 x, y;
    arc_s16 x1, y1, x2, y2;
    
    if (!rect) return;
    
    x1 = rect->x;
    y1 = rect->y;
    x2 = rect->x + rect->w;
    y2 = rect->y + rect->h;
    
    /* Clip to screen bounds */
    if (x1 < 0) x1 = 0;
    if (y1 < 0) y1 = 0;
    if (x2 > SCREEN_WIDTH) x2 = SCREEN_WIDTH;
    if (y2 > SCREEN_HEIGHT) y2 = SCREEN_HEIGHT;
    
    for (y = y1; y < y2; y++) {
        for (x = x1; x < x2; x++) {
            g_vga_memory[y * SCREEN_WIDTH + x] = color;
        }
    }
}

void arc_set_palette_color(arc_u8 index, arc_u8 r, arc_u8 g, arc_u8 b)
{
    /* Set VGA palette color */
    outp(PALETTE_INDEX_PORT, index);
    outp(PALETTE_DATA_PORT, r >> 2);  /* VGA uses 6-bit RGB */
    outp(PALETTE_DATA_PORT, g >> 2);
    outp(PALETTE_DATA_PORT, b >> 2);
}

void arc_get_palette_color(arc_u8 index, arc_u8* r, arc_u8* g, arc_u8* b)
{
    /* Note: Reading VGA palette is more complex, this is simplified */
    if (r) *r = 0;
    if (g) *g = 0;
    if (b) *b = 0;
}

void arc_set_palette(const arc_color* palette, arc_u16 count)
{
    arc_u16 i;
    
    if (!palette) return;
    
    if (count > 256) count = 256;
    
    for (i = 0; i < count; i++) {
        arc_set_palette_color((arc_u8)i, palette[i].r, palette[i].g, palette[i].b);
    }
}

#endif /* ARCANUM_DOS16 */