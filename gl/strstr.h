/* Searching in a string.
   Copyright (C) 2001-2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation; either version 2.1, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

#if HAVE_STRSTR

/* Get strstr() declaration.  */
#include <string.h>

#else

#ifdef __cplusplus
extern "C" {
#endif

/* Find the first occurrence of NEEDLE in HAYSTACK.  */
extern char *strstr (const char *haystack, const char *needle);

#ifdef __cplusplus
}
#endif

#endif