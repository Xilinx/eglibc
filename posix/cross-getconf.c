/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Undefine macros that should be defined in cross-getconf.h.  */
#undef _POSIX_V6_ILP32_OFF32
#undef _POSIX_V6_ILP32_OFFBIG
#undef _POSIX_V6_LP64_OFF64
#undef _POSIX_V6_LPBIG_OFFBIG

#include "cross-getconf.h"

/* Define macros cross-getconf.h doesn't define to (-1).
   This will prevent using host's __sysconf in confstr.inc.  */
#ifndef _POSIX_V6_ILP32_OFF32
# define _POSIX_V6_ILP32_OFF32 (-1)
#endif
#ifndef _POSIX_V6_ILP32_OFFBIG
# define _POSIX_V6_ILP32_OFFBIG (-1)
#endif
#ifndef _POSIX_V6_LP64_OFF64
# define _POSIX_V6_LP64_OFF64 (-1)
#endif
#ifndef _POSIX_V6_LPBIG_OFFBIG
# define _POSIX_V6_LPBIG_OFFBIG (-1)
#endif

/* Cross-getconf is a very simple program that assumes fixed
   input and produces fixed output.  It handles only cases
   that are necessary to cross-compile EGLIBC.  */

void
cross_getconf (void)
{
  const char *string = "";
  size_t string_len = 1;

#include "confstr.inc"

  printf ("%.*s\n", (int) string_len, string);
}

int
main (int argc, char *argv[])
{
  const char *getconf_dir;

  if (argc != 2 || strcmp (argv[1], "_POSIX_V6_WIDTH_RESTRICTED_ENVS") != 0)
    {
      fprintf (stderr,
	       "%s: the only supported argument value is "
	       "_POSIX_V6_WIDTH_RESTRICTED_ENVS", argv[0]);
      return 1;
    }

  getconf_dir = getenv ("GETCONF_DIR");
  if (getconf_dir == NULL
      || strcmp (getconf_dir, "/dev/null") != 0)
    {
      fprintf (stderr, "%s: GETCONF_DIR should be /dev/null\n", argv[0]);
      return 1;
    }

  cross_getconf ();
  return 0;
}
