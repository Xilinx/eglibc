/* Copyright (C) 2009 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Jakub Jelinek <jakub@redhat.com>.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <errno.h>
#include <sysdep.h>
#include <setjmp.h>
#include <bits/setjmp.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define __longjmp ____longjmp_chk

#define CHECK_SP(env, guard) \
  do									\
    {									\
      uintptr_t cur_sp;							\
      uintptr_t new_sp = env->__gregs[9];				\
      __asm ("lr %0, %%r15" : "=r" (cur_sp));				\
      new_sp ^= guard;							\
      if (new_sp < cur_sp)						\
	__fortify_fail ("longjmp causes uninitialized stack frame");	\
    } while (0)

#include "__longjmp.c"
