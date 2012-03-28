# Copyright (C) 1991,1996-1999,2003,2004 Free Software Foundation, Inc.
# This file is part of the GNU C Library.

# The GNU C Library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# The GNU C Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with the GNU C Library; if not, see
# <http://www.gnu.org/licenses/>.

#
#	Sub-makefile for pwd portion of the library.
#
include ../option-groups.mak

subdir	:= pwd
headers := pwd.h

routines := fgetpwent getpw putpwent \
	    getpwent getpwnam getpwuid \
	    getpwent_r getpwnam_r getpwuid_r fgetpwent_r

tests := tst-getpw

include ../Rules

ifeq ($(have-thread-library),yes)

OPTION_EGLIBC_INET-CFLAGS-$(OPTION_EGLIBC_INET) = -DUSE_NSCD=1

CFLAGS-getpwuid_r.c = $(OPTION_EGLIBC_INET-CFLAGS-y)
CFLAGS-getpwnam_r.c = $(OPTION_EGLIBC_INET-CFLAGS-y)
CFLAGS-getpwent_r.c = -fexceptions
CFLAGS-getpwent.c = -fexceptions
CFLAGS-getpw.c = -fexceptions
CFLAGS-fgetpwent_r.c = -D_IO_MTSAFE_IO

endif
