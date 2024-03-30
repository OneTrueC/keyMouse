/* a small program to control the cursor with the keyboard in x11         *\
|* Copyright (C) 2024  Andrew Charles Marino                              *|
|*                                                                        *|
|* This program is free software: you can redistribute it and/or modify   *|
|* it under the terms of the GNU General Public License as published by   *|
|* the Free Software Foundation, either version 3 of the License, or      *|
|* (at your option) any later version.                                    *|
|*                                                                        *|
|* This program is distributed in the hope that it will be useful,        *|
|* but WITHOUT ANY WARRANTY; without even the implied warranty of         *|
|* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *|
|* GNU General Public License for more details.                           *|
|*                                                                        *|
|* You should have received a copy of the GNU General Public License      *|
\* along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#define _POSIX_C_SOURCE 200809L

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>
#include <time.h>

#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>

/* config */
#	define UP XK_k
#	define DOWN XK_j
#	define LEFT XK_h
#	define RIGHT XK_l

#	define BUTTONL XK_a
#	define BUTTONM XK_s
#	define BUTTONR XK_d

	const struct timespec STARTDELAY = { 0, 50000000 };
	const int MOVEMENT = 5;
	const int MULTIPLIER = 5;
/* end config */

static void die(const char *errstr, ...);
static void move(Display *dpy, int x, int y, unsigned int mod);

int
main()
{
	char running;
	Display *dpy;
	int grab;
	KeySym ksym;
	Window root;
	XEvent ev;

	running = 1;

	if ((dpy = XOpenDisplay(NULL)) == NULL)
		die("display open failed: %s", strerror(errno));

	root = DefaultRootWindow(dpy);

	nanosleep(&STARTDELAY, (struct timespec*)&STARTDELAY);

	grab = XGrabKeyboard(dpy, root, True, GrabModeAsync, GrabModeAsync,
	                     CurrentTime);
	if (grab != GrabSuccess)
		die("keyboard grab failed: %s", strerror(errno));

	while (running && !XNextEvent(dpy, &ev)) {
		if (ev.type == KeyPress) {
			ksym = XLookupKeysym(&ev.xkey, 0);

			switch (ksym) {
			case UP:
				move(dpy, 0, -MOVEMENT, ev.xkey.state);
				break;

			case DOWN:
				move(dpy, 0, MOVEMENT, ev.xkey.state);
				break;

			case LEFT:
				move(dpy, -MOVEMENT, 0, ev.xkey.state);
				break;

			case RIGHT:
				move(dpy, MOVEMENT, 0, ev.xkey.state);
				break;

			case BUTTONL:
				XTestFakeButtonEvent(dpy, 1, 1, CurrentTime);
				break;

			case BUTTONM:
				XTestFakeButtonEvent(dpy, 2, 1, CurrentTime);
				break;

			case BUTTONR:
				XTestFakeButtonEvent(dpy, 3, 1, CurrentTime);
				break;

			case XK_Alt_L:
			case XK_Alt_R:
			case XK_Control_L:
			case XK_Control_R:
			case XK_Hyper_L:
			case XK_Hyper_R:
			case XK_ISO_Level3_Shift:
			case XK_ISO_Level5_Shift:
			case XK_Meta_L:
			case XK_Meta_R:
			case XK_Num_Lock:
			case XK_Shift_L:
			case XK_Shift_R:
			case XK_Shift_Lock:
			case XK_Super_L:
			case XK_Super_R:
				break;

			default:
				running = 0;
				break;
			}
		} else if (ev.type == KeyRelease) {
			ksym = XLookupKeysym(&ev.xkey, 0);

			switch (ksym) {
			case BUTTONL:
				XTestFakeButtonEvent(dpy, 1, 0, CurrentTime);
				break;

			case BUTTONM:
				XTestFakeButtonEvent(dpy, 2, 0, CurrentTime);
				break;

			case BUTTONR:
				XTestFakeButtonEvent(dpy, 3, 0, CurrentTime);
				break;

			default:
				break;
			}
		}
	}

	if (running)
		die("getting event failed: %s", strerror(errno));

	XUngrabKeyboard(dpy, CurrentTime);
	XCloseDisplay(dpy);

	return 0;
}

static void
die(const char *errstr, ...)
{
	va_list ap;

	va_start(ap, errstr);
	fprintf(stderr, "keyMouse: ");
	vfprintf(stderr, errstr, ap);
	fprintf(stderr, "\n");
	va_end(ap);

	exit(1);
}

static void
move(Display *dpy, int x, int y, unsigned int mod)
{
	int mult;

	mult = 1;

	if (mod & ShiftMask)
		mult *= MULTIPLIER;
	if (mod & ControlMask)
		mult *= MULTIPLIER;
	if (mod & Mod1Mask)
		mult *= MULTIPLIER;
	if (mod & Mod2Mask)
		mult *= MULTIPLIER;
	if (mod & Mod3Mask)
		mult *= MULTIPLIER;
	if (mod & Mod4Mask)
		mult *= MULTIPLIER;
	if (mod & Mod5Mask)
		mult *= MULTIPLIER;

	XWarpPointer(dpy, None, None, 0, 0, 0, 0, x * mult, y * mult);
}
