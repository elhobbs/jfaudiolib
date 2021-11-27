/*
 Copyright (C) 2009 Jonathon Fowler <jf@jonof.id.au>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 
 See the GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 
 */

#include "asssys.h"

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <stdarg.h>
# include <stdio.h>
#else
# include <sys/types.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
#endif

void ASS_Sleep(int msec)
{
#ifdef _WIN32
	Sleep(msec);
#else
	struct timeval tv;

	tv.tv_sec = msec / 1000;
	tv.tv_usec = (msec % 1000) * 1000;
	select(0, NULL, NULL, NULL, &tv);
#endif
}

void ASS_Message(const char *fmt, ...)
{
    va_list va;

#ifdef _WIN32
    char text[256];

    if (!IsDebuggerPresent()) return;

    va_start(va, fmt);
    vsnprintf(text, sizeof(text), fmt, va);
    OutputDebugString(text);
    va_end(va);
#else
    va_start(va, fmt);
    vfprintf(stderr, fmt, va);
    va_end(va);
#endif
}
