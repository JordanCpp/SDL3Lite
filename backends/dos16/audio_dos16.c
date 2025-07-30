/**
 * DOS 16-bit Audio Backend
 * PC Speaker implementation for Borland C++ 3.1
 */

#include "../../core/arcanum.h"
#include <dos.h>
#include <conio.h>

#ifdef ARCANUM_DOS16

/* PC Speaker ports */
#define SPEAKER_PORT        0x61
#define TIMER_COMMAND_PORT  0x43
#define TIMER_DATA_PORT     0x42

/* Timer frequency for PC Speaker */
#define TIMER_FREQUENCY     1193180L

/* Global audio state */
static arc_bool g_audio_initialized = ARC_FALSE;

/* Simple sound structure for PC Speaker */
struct arc_sound {
    arc_u16 frequency;
    arc_u16 duration;
};

arc_result arc_audio_init(void)
{
    g_audio_initialized = ARC_TRUE;
    return ARC_OK;
}

void arc_audio_quit(void)
{
    /* Turn off any playing sound */
    outp(SPEAKER_PORT, inp(SPEAKER_PORT) & 0xFC);
    g_audio_initialized = ARC_FALSE;
}

void arc_beep(arc_u16 frequency, arc_u16 duration_ms)
{
    arc_u16 timer_value;
    arc_u8 speaker_control;
    
    if (!g_audio_initialized || frequency == 0) {
        return;
    }
    
    /* Calculate timer value for frequency */
    timer_value = (arc_u16)(TIMER_FREQUENCY / frequency);
    
    /* Set timer mode */
    outp(TIMER_COMMAND_PORT, 0xB6);
    
    /* Set frequency */
    outp(TIMER_DATA_PORT, timer_value & 0xFF);
    outp(TIMER_DATA_PORT, timer_value >> 8);
    
    /* Turn on speaker */
    speaker_control = inp(SPEAKER_PORT);
    outp(SPEAKER_PORT, speaker_control | 0x03);
    
    /* Wait for duration */
    delay(duration_ms);
    
    /* Turn off speaker */
    outp(SPEAKER_PORT, speaker_control & 0xFC);
}

arc_sound* arc_load_sound(const char* filename)
{
    /* For DOS 16-bit, we don't support loading sound files */
    /* This would require SoundBlaster support which is more complex */
    return NULL;
}

void arc_free_sound(arc_sound* sound)
{
    if (sound) {
        arc_free(sound);
    }
}

void arc_play_sound(arc_sound* sound)
{
    if (sound) {
        arc_beep(sound->frequency, sound->duration);
    }
}

/* Create a simple tone sound */
arc_sound* arc_create_tone(arc_u16 frequency, arc_u16 duration_ms)
{
    arc_sound* sound = (arc_sound*)arc_malloc(sizeof(arc_sound));
    if (sound) {
        sound->frequency = frequency;
        sound->duration = duration_ms;
    }
    return sound;
}

/* Play musical note */
void arc_play_note(char note, arc_u8 octave, arc_u16 duration_ms)
{
    arc_u16 frequency = 0;
    
    /* Base frequencies for octave 4 */
    switch (note) {
        case 'C': case 'c': frequency = 262; break;
        case 'D': case 'd': frequency = 294; break;
        case 'E': case 'e': frequency = 330; break;
        case 'F': case 'f': frequency = 349; break;
        case 'G': case 'g': frequency = 392; break;
        case 'A': case 'a': frequency = 440; break;
        case 'B': case 'b': frequency = 494; break;
        default: return;
    }
    
    /* Adjust for octave */
    if (octave > 4) {
        frequency <<= (octave - 4);
    } else if (octave < 4) {
        frequency >>= (4 - octave);
    }
    
    arc_beep(frequency, duration_ms);
}

/* Play simple melody */
void arc_play_startup_sound(void)
{
    arc_play_note('C', 4, 200);
    arc_play_note('E', 4, 200);
    arc_play_note('G', 4, 200);
    arc_play_note('C', 5, 300);
}

void arc_play_error_sound(void)
{
    arc_beep(200, 500);
}

void arc_play_success_sound(void)
{
    arc_beep(800, 100);
    delay(50);
    arc_beep(1000, 100);
}

#endif /* ARCANUM_DOS16 */