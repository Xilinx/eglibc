# Copyright (C) 1991-2006, 2007 Free Software Foundation, Inc.
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
# License along with the GNU C Library; if not, write to the Free
# Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
# 02111-1307 USA.

#
#	Specific makefile for stdio-common.
#
include ../option-groups.mak

subdir	:= stdio-common

headers	:= stdio_ext.h printf.h bits/printf-ldbl.h

routines	:=							      \
	ctermid cuserid							      \
	_itoa _itowa itoa-digits itoa-udigits itowa-digits		      \
	vfprintf vprintf printf_fp reg-printf printf-prs printf_fphex	      \
	printf_size fprintf printf snprintf sprintf asprintf dprintf	      \
	vfwprintf vfscanf vfwscanf					      \
	fscanf scanf sscanf						      \
	perror psignal							      \
	tmpfile tmpfile64 tmpnam tmpnam_r tempnam tempname		      \
	getline getw putw						      \
	remove rename renameat						      \
	flockfile ftrylockfile funlockfile

include ../Makeconfig

install-headers-nosubdir: $(inst_includedir)/bits/stdio_lim.h

aux	:= errlist siglist printf-parsemb printf-parsewc fxprintf
distribute := _itoa.h _itowa.h _i18n_number.h \
	      printf-parse.h stdio_lim.h.in tst-unbputc.sh tst-printf.sh

tests := tstscanf test_rdwr test-popen tstgetln test-fseek \
	 temptest tst-fileno test-fwrite tst-ungetc tst-ferror \
	 xbug errnobug \
	 bug1 bug2 bug3 bug4 bug5 bug6 bug7 bug8 bug9 bug10 bug11 bug12 bug13 \
	 tfformat tiformat tllformat tstdiomisc tst-printfsz tst-wc-printf \
	 scanf1 scanf2 scanf3 scanf4 scanf5 scanf7 scanf8 scanf9 scanf10 \
	 scanf11 scanf12 tst-tmpnam tst-cookie tst-obprintf \
	 tst-fseek tst-fmemopen tst-gets \
	 tst-perror tst-sprintf tst-rndseek tst-fdopen tst-fphex bug14 \
	 tst-popen tst-unlockedio tst-fmemopen2 tst-put-error tst-fgets \
	 tst-fwrite bug16 bug17 tst-swscanf tst-sprintf2 bug18 bug18a \
	 bug19 bug19a tst-popen2
tests-$(OPTION_EGLIBC_LOCALE_CODE) \
      += tst-sscanf tst-swprintf bug15 test-vfprintf

test-srcs = tst-unbputc tst-printf

include ../Rules

$(inst_includedir)/bits/stdio_lim.h: $(common-objpfx)bits/stdio_lim.h $(+force)
	$(do-install)

# eglibc: ifeq ($(cross-compiling),no)
.PHONY: do-tst-unbputc do-tst-printf
tests: do-tst-unbputc do-tst-printf

do-tst-unbputc: $(objpfx)tst-unbputc.out
$(objpfx)tst-unbputc.out: $(objpfx)tst-unbputc tst-unbputc.sh
	$(SHELL) -e tst-unbputc.sh $(common-objpfx) '$(run-program-prefix)'

do-tst-printf: $(objpfx)tst-printf.out
$(objpfx)tst-printf.out: $(objpfx)tst-printf tst-printf.sh
	$(SHELL) -e tst-printf.sh $(common-objpfx) '$(run-program-prefix)'
# eglibc: endif

OPTION_EGLIBC_LOCALE_CODE-CFLAGS-$(OPTION_EGLIBC_LOCALE_CODE) \
	= -DOPTION_EGLIBC_LOCALE_CODE

CFLAGS-vfprintf.c = -Wno-uninitialized
CFLAGS-vfwprintf.c = -Wno-uninitialized
CFLAGS-tst-printf.c = -Wno-format
CFLAGS-tstdiomisc.c = -Wno-format
CFLAGS-scanf4.c = -Wno-format
CFLAGS-scanf7.c = -Wno-format
CFLAGS-tst-printfsz.c = -Wno-format
CFLAGS-printf_fp.c = $(OPTION_EGLIBC_LOCALE_CODE-CFLAGS-y)
CFLAGS-printf_fphex.c = $(OPTION_EGLIBC_LOCALE_CODE-CFLAGS-y)

CFLAGS-tmpfile.c = -fexceptions
CFLAGS-tmpfile64.c = -fexceptions
CFLAGS-tempname.c = -fexceptions
CFLAGS-psignal.c = -fexceptions
CFLAGS-vprintf.c = -fexceptions
CFLAGS-cuserid.c = -fexceptions
CFLAGS-errlist.c = $(fno-unit-at-a-time)
CFLAGS-siglist.c = $(fno-unit-at-a-time)

# We know the test has a format string problem.
CFLAGS-tst-sprintf.c = -Wno-format
tst-sscanf-ENV = LOCPATH=$(common-objpfx)localedata
tst-swprintf-ENV = LOCPATH=$(common-objpfx)localedata
test-vfprintf-ENV = LOCPATH=$(common-objpfx)localedata
bug14-ENV = LOCPATH=$(common-objpfx)localedata
bug15-ENV = LOCPATH=$(common-objpfx)localedata

ifneq (,$(filter %REENTRANT, $(defines)))
CPPFLAGS += -D_IO_MTSAFE_IO
endif
