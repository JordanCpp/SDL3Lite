/**
 * DOS 16-bit Input Backend
 * Keyboard and mouse handling for Borland C++ 3.1
 */

#include "../../core/arcanum.h"
#include <dos.h>
#include <mem.h>
#include <conio.h>

#ifdef ARCANUM_DOS16

/* Keyboard state */
static arc_u8 g_key_states[128];
static arc_u8 g_prev_key_states[128];

/* Mouse state */
static arc_bool g_mouse_available = ARC_FALSE;
static arc_s16 g_mouse_x = 0;
static arc_s16 g_mouse_y = 0;
static arc_u8 g_mouse_buttons = 0;
static arc_u8 g_prev_mouse_buttons = 0;

/* Original keyboard interrupt handler */
static void (interrupt far *g_old_kb_handler)();
static volatile arc_bool g_kb_interrupt_installed = ARC_FALSE;

/* Keyboard interrupt handler */
void interrupt far keyboard_handler(void)
{
    arc_u8 scan_code = inp(0x60);
    arc_u8 key_released = scan_code & 0x80;
    
    scan_code &= 0x7F;
    
    if (scan_code < 128) {
        g_key_states[scan_code] = key_released ? 0 : 1;
    }
    
    /* Acknowledge interrupt */
    outp(0x20, 0x20);
}

arc_result arc_input_init(void)
{
    arc_u16 i;
    
    /* Clear key states */
    for (i = 0; i < 128; i++) {
        g_key_states[i] = 0;
        g_prev_key_states[i] = 0;
    }
    
    /* Install keyboard interrupt handler */
    g_old_kb_handler = getvect(0x09);
    setvect(0x09, keyboard_handler);
    g_kb_interrupt_installed = ARC_TRUE;
    
    /* Initialize mouse */
    asm {
        mov ax, 0x0000  ; Mouse reset
        int 0x33
        mov g_mouse_available, al
    }
    
    if (g_mouse_available) {
        /* Set mouse range to screen coordinates */
        asm {
            mov ax, 0x0007  ; Set horizontal range
            mov cx, 0       ; Min X
            mov dx, 319     ; Max X
            int 0x33
            
            mov ax, 0x0008  ; Set vertical range
            mov cx, 0       ; Min Y  
            mov dx, 199     ; Max Y
            int 0x33
        }
    }
    
    return ARC_OK;
}

void arc_input_quit(void)
{
    /* Restore original keyboard handler */
    if (g_kb_interrupt_installed) {
        setvect(0x09, g_old_kb_handler);
        g_kb_interrupt_installed = ARC_FALSE;
    }
}

void arc_input_update(void)
{
    arc_u16 i;
    
    /* Update previous key states */
    for (i = 0; i < 128; i++) {
        g_prev_key_states[i] = g_key_states[i];
    }
    
    /* Update mouse state */
    if (g_mouse_available) {
        g_prev_mouse_buttons = g_mouse_buttons;
        
        asm {
            mov ax, 0x0003  ; Get mouse position and buttons
            int 0x33
            mov g_mouse_x, cx
            mov g_mouse_y, dx
            mov g_mouse_buttons, bl
        }
    }
}

arc_bool arc_key_pressed(arc_keycode key)
{
    if (key >= 128) return ARC_FALSE;
    return g_key_states[key] && !g_prev_key_states[key];
}

arc_bool arc_key_down(arc_keycode key)
{
    if (key >= 128) return ARC_FALSE;
    return g_key_states[key];
}

arc_bool arc_key_up(arc_keycode key)
{
    if (key >= 128) return ARC_FALSE;
    return !g_key_states[key] && g_prev_key_states[key];
}

arc_bool arc_mouse_button_pressed(arc_mouse_button button)
{
    if (!g_mouse_available) return ARC_FALSE;
    return (g_mouse_buttons & button) && !(g_prev_mouse_buttons & button);
}

arc_bool arc_mouse_button_down(arc_mouse_button button)
{
    if (!g_mouse_available) return ARC_FALSE;
    return (g_mouse_buttons & button) != 0;
}

arc_bool arc_mouse_button_up(arc_mouse_button button)
{
    if (!g_mouse_available) return ARC_FALSE;
    return !(g_mouse_buttons & button) && (g_prev_mouse_buttons & button);
}

void arc_get_mouse_pos(arc_s16* x, arc_s16* y)
{
    if (x) *x = g_mouse_x;
    if (y) *y = g_mouse_y;
}

#endif /* ARCANUM_DOS16 */