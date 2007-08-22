# Copyright (C) 1996,1997,1998,2000,2001,2002 Free Software Foundation, Inc.
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
#	Makefile for name service switch.
#
include ../option-groups.mak

subdir	:= nss

headers			:= nss.h
distribute		:= nsswitch.h XXX-lookup.c getXXbyYY.c getXXbyYY_r.c \
			   getXXent.c getXXent_r.c databases.def \
			   nsswitch.conf digits_dots.c function.def \
			   gen-fixed-nsswitch.c

# These are the databases that go through nss dispatch.
# Caution: if you add a database here, you must add its real name
# in databases.def, too.
databases-y		= grp pwd spwd 
databases-$(OPTION_EGLIBC_INET) \
			+= proto service hosts network rpc ethers \
			   netgrp key
databases-$(OPTION_EGLIBC_DB_ALIASES) += alias

# This is the trivial part which goes into libc itself.
routines-y		+= nsswitch getnssent getnssent_r \
			  $(addsuffix -lookup,$(databases-y))
routines-$(OPTION_EGLIBC_INET) += digits_dots

others                  := getent
install-bin             := getent

tests-$(OPTION_EGLIBC_INET) += test-netdb
xtests-$(OPTION_EGLIBC_INET) += bug-erange

include ../Makeconfig

ifeq (yes,$(build-static-nss))
otherlibs += $(nssobjdir)/libnss_files.a $(resolvobjdir)/libnss_dns.a \
	     $(resolvobjdir)/libresolv.a
endif

# Specify rules for the nss_* modules.  We have some services.
services		:= files

extra-libs		= $(services:%=libnss_%)
# These libraries will be built in the `others' pass rather than
# the `lib' pass, because they depend on libc.so being built already.
extra-libs-others	= $(extra-libs)

# The sources are found in the appropriate subdir.
subdir-dirs = $(services:%=nss_%)
vpath %.c $(subdir-dirs)


libnss_files-routines	:= $(addprefix files-,$(databases-y))
distribute		+= files-XXX.c files-parse.c


# Build static module if requested
ifneq ($(build-static-nss),yes)
libnss_files-inhibit-o	= $(filter-out .os,$(object-suffixes))
endif

ifneq ($(OPTION_EGLIBC_NSSWITCH),y)

ifndef OPTION_EGLIBC_NSSWITCH_FIXED_CONFIG
$(error OPTION_EGLIBC_NSSWITCH_FIXED_CONFIG variable left unset)
endif

ifndef OPTION_EGLIBC_NSSWITCH_FIXED_FUNCTIONS
$(error OPTION_EGLIBC_NSSWITCH_FIXED_FUNCTIONS variable left unset)
endif

ifeq (,$(wildcard $(common-objpfx)$(OPTION_EGLIBC_NSSWITCH_FIXED_CONFIG)))
$(warning OPTION_EGLIBC_NSSWITCH is disabled, but fixed config file)
$(error does not exist: $(OPTION_EGLIBC_NSSWITCH_FIXED_CONFIG))
endif

ifeq (,$(wildcard $(common-objpfx)$(OPTION_EGLIBC_NSSWITCH_FIXED_FUNCTIONS)))
$(warning OPTION_EGLIBC_NSSWITCH is disabled, but fixed functions file)
oooo$(error does not exist: $(OPTION_EGLIBC_NSSWITCH_FIXED_FUNCTIONS))
endif

before-compile := $(objpfx)fixed-nsswitch.h
generated := fixed-nsswitch.h
$(objpfx)fixed-nsswitch.h $(objfpx)fixed-nsswitch-libs:		\
    $(objpfx)gen-fixed-nsswitch					\
    $(common-objpfx)$(OPTION_EGLIBC_NSSWITCH_FIXED_CONFIG)
	$< $(objpfx)fixed-nsswitch.h					\
	   $(objpfx)fixed-nsswitch-libs					\
	   $(common-objpfx)$(OPTION_EGLIBC_NSSWITCH_FIXED_CONFIG)

$(objpfx)gen-fixed-nsswitch: gen-fixed-nsswitch.c		\
    $(common-objpfx)option-groups.config			\
    $(common-objpfx)$(OPTION_EGLIBC_NSSWITCH_FIXED_FUNCTIONS)
	$(native-compile)
gen-fixed-nsswitch-CFLAGS = \
	-g3 -O -Wall \
	-I $(objpfx) \
	-DFIXED_FUNCTIONS='"$(common-objpfx)$(OPTION_EGLIBC_NSSWITCH_FIXED_FUNCTIONS)"'
endif

include ../Rules


ifeq (yes,$(build-static-nss))
$(objpfx)getent: $(objpfx)libnss_files.a
endif

# Depend on libc.so so a DT_NEEDED is generated in the shared objects.
# This ensures they will load libc.so for needed symbols if loaded by
# a statically-linked program that hasn't already loaded it.
$(services:%=$(objpfx)libnss_%.so): $(common-objpfx)libc.so \
				    $(common-objpfx)libc_nonshared.a

OPTION_EGLIBC_INET-CFLAGS-$(OPTION_EGLIBC_INET) = -DOPTION_EGLIBC_INET=1
OPTION_EGLIBC_NSSWITCH-CFLAGS-$(OPTION_EGLIBC_NSSWITCH) \
	= -DOPTION_EGLIBC_NSSWITCH=1
OPTION_EGLIBC_DB_ALIASES-CFLAGS-$(OPTION_EGLIBC_DB_ALIASES) \
	= -DOPTION_EGLIBC_DB_ALIASES=1

CFLAGS-nsswitch.c    = $(OPTION_EGLIBC_INET-CFLAGS-y) \
		       $(OPTION_EGLIBC_NSSWITCH-CFLAGS-y)
CFLAGS-getnssent_r.c = $(OPTION_EGLIBC_INET-CFLAGS-y)
CFLAGS-getent.c      = $(OPTION_EGLIBC_INET-CFLAGS-y) \
		       $(OPTION_EGLIBC_DB_ALIASES-y)
