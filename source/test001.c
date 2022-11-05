// ========================================================
//
// FILE:			/source/test001.c
//
// AUTHORS:			Jaycie Ewald
//
// PROJECT:			DOSLIB
//
// LICENSE:			ACSL 1.4
//
// DESCRIPTION:		DOSLIB test #001.
//
// LAST EDITED:		November 5th, 2022
//
// ========================================================

// DOSLIB header
#include "doslib.h"

int main(void)
{
	// random integer
	int xyz = 12454;

	// set video mode and clear screen
	doslib_video_set_mode(MODE_TEXT_C80);
	doslib_video_clear();

	// print some formatted, colored and positioned text
	doslib_printf(2, 1, 1, 2, "hello %d world\n", xyz);

	// wait for user input
	getch();

	// set video mode and clear screen
	doslib_video_set_mode(MODE_TEXT_C80);
	doslib_video_clear();

	// return exit condition
	return EXIT_SUCCESS;
}
