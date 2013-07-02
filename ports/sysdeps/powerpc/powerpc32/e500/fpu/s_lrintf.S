/* Round float to long int.  PowerPC E500 version.
   Copyright (C) 2006-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Joseph Myers <joseph@codesourcery.com>, 2006.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <sysdep.h>

ENTRY(__lrintf)
/* long int [r3] lrintf (float [r3] x) ;  */
	efsctsi r3,r3
	blr
END(__lrintf)

weak_alias(__lrintf,lrintf)
