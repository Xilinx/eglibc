/* Install given floating-point environment and raise exceptions.
   Copyright (C) 2004-2013 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Aldy Hernandez <aldyh@redhat.com>, 2004.

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

#include <fenv_libc.h>
#include <sysdep.h>
#include <sys/prctl.h>

int
__feupdateenv (const fenv_t *envp)
{
  unsigned long fpescr, old, new, pflags;
  fenv_union_t u;
  INTERNAL_SYSCALL_DECL (err);

  /* Save the currently set exceptions.  */
  u.fenv = *envp;
  new = u.l[1];
  old = fegetenv_register ();
  new |= (old & FE_ALL_EXCEPT);

  INTERNAL_SYSCALL (prctl, err, 2, PR_GET_FPEXC, &pflags);
  pflags |= u.l[0];
  INTERNAL_SYSCALL (prctl, err, 2, PR_SET_FPEXC, pflags);

  /* Enable and raise (if appropriate) exceptions set in `new'. */
  fesetenv_register (new);
  feraiseexcept (new & FE_ALL_EXCEPT);

  /* Success.  */
  return 0;
}

#include <shlib-compat.h>
#if SHLIB_COMPAT (libm, GLIBC_2_1, GLIBC_2_2)
strong_alias (__feupdateenv, __old_feupdateenv)
compat_symbol (libm, __old_feupdateenv, feupdateenv, GLIBC_2_1);
#endif

libm_hidden_ver (__feupdateenv, feupdateenv)
versioned_symbol (libm, __feupdateenv, feupdateenv, GLIBC_2_2);
