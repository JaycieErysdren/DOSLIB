// ========================================================
//
// FILE:			/source/inc/doslib.h
//
// AUTHORS:			Jaycie Ewald
//
// PROJECT:			DOSLIB
//
// LICENSE:			ACSL 1.4
//
// DESCRIPTION:		DOSLIB header.
//
// LAST EDITED:		November 5th, 2022
//
// ========================================================

#ifndef __DOSLIB_H__
#define __DOSLIB_H__

// Standard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

// DOS headers
#include <conio.h>
#include <dos.h>
#include <io.h>

// Watcom definitions
#ifdef __WATCOMC__

	// Headers
	#include <graph.h>
	#include <i86.h>

	// Text manipulation
	#define TEXT_SET_POS(col, row) _settextposition(row, col)
	#define TEXT_PRINT(text) _outtext(text);
	#define TEXT_SET_FG_COLOR(color) _settextcolor(color)
	#define TEXT_SET_BG_COLOR(color) _setbkcolor(color)

	// Video manipulation
	#define VID_RESET _setvideomode(_DEFAULTMODE)
	#define VID_CLEAR _clearscreen(_GCLEARSCREEN)

	// Hardware manipulation
	#define DOSLIB_INTERRUPT __interrupt __far

	// Globals
	static struct videoconfig videoconfig;

#endif

// DJGPP definitions
#if defined __DJGPP__

	// Headers
	#include <pc.h>
	#include <dpmi.h>

	// Text manipulation
	#define TEXT_SET_POS(col, row) gotoxy(col, row)
	#define TEXT_PRINT(text) cprintf(text);
	#define TEXT_SET_FG_COLOR(color) textcolor(color)
	#define TEXT_SET_BG_COLOR(color) textbackground(color)

	// Video manipulation
	#define VID_RESET normvideo()
	#define VID_CLEAR clrscr()

	// Hardware manipulation
	#define DOSLIB_INTERRUPT

#endif

// Global definitions
#define MODE_TEXT_C80 0x03
#define MODE_VGA_13H 0x13
#define DOS_CLOCK_SPEED 1193181

//
// Text functions
//

// Prints a formatted, colored text string at the specified column and row
void doslib_printf(int column, int row, int bg_color, int fg_color, const char *text, ...)
{
	va_list args;
	char message_buffer[512];

	va_start(args, text);
	vsnprintf(message_buffer, sizeof(message_buffer), text, args);
	va_end(args);

	if (bg_color > -1) TEXT_SET_BG_COLOR(bg_color);
	if (fg_color > -1) TEXT_SET_FG_COLOR(fg_color);

	TEXT_SET_POS(column, row);

	TEXT_PRINT(message_buffer);

	TEXT_SET_BG_COLOR(0);
	TEXT_SET_FG_COLOR(7);
}

//
// Video functions
//

// Set the video mode to the specified value.
void doslib_video_set_mode(int mode)
{
	#ifdef __WATCOMC__

		union REGS r;

		memset(&r, 0, sizeof(r));

		r.x.eax = mode;

		int386(0x10, &r, &r);

	#endif

	#ifdef __DJGPP__

		__dpmi_regs r;

		memset(&r, 0, sizeof(r));

		r.x.ax = mode;

		__dpmi_int(0x10, &r);

	#endif
}

// Reset video mode to the default for the system.
void doslib_video_reset_mode(void)
{
	VID_RESET;
}

// Clear the screen.
void doslib_video_clear(void)
{
	VID_CLEAR;
}

//
// Hardware functions
//

#if 0 // doesn't work on DJGPP yet

unsigned int doslib_timer;

static void DOSLIB_INTERRUPT *_doslib_timer_interrupt;

void DOSLIB_INTERRUPT doslib_timer_interrupt(void)
{
	doslib_timer++;

	outp(0x20, 0x20);
}

// Set the system clock speed interrupt.
void doslib_timer_install(int target_speed)
{
	int speed = DOS_CLOCK_SPEED / target_speed;

	_disable();

	if (!_doslib_timer_interrupt)
	{
		_doslib_timer_interrupt = _dos_getvect(8);

		_dos_setvect(8, doslib_timer_interrupt);
		outp(0x43, 0x34);
		outp(0x40, speed);
		outp(0x40, speed >> 8);
	}

	_enable();
}

// Reset the system clock speed interrupt.
void doslib_timer_remove(void)
{
	_disable();

	if (_doslib_timer_interrupt)
	{
		_dos_setvect(8, _doslib_timer_interrupt);
		outp(0x43, 0x34);
		outp(0x40, 0x00);
		outp(0x40, 0x00);
		_doslib_timer_interrupt = 0;
	}

	_enable();
}

#endif

#endif // __DOSLIB_H__
