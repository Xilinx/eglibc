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

# The mpn functions need this.  All existing 68k ports use MIT syntax.  If
# a new port wants to use Motorola or Sony syntax, it can redefine this
# variable.

pic-ccflag = -fPIC

# Make sure setjmp.c is compiled with a frame pointer
CFLAGS-setjmp.c := -fno-omit-frame-pointer

ifeq ($(subdir),elf)
CFLAGS-rtld.c += -Wno-uninitialized -Wno-unused
endif

# Without the following we get undefined references from these
# various libs to __tls_get_addr. Not sure why only microblaze
# needs this?
$(objpfx)libm.so: $(elfobjdir)/ld.so
$(objpfx)libcrypt.so: $(elfobjdir)/ld.so
$(objpfx)libresolv.so: $(elfobjdir)/ld.so
$(objpfx)libnss_dns.so: $(elfobjdir)/ld.so
$(objpfx)libnss_files.so: $(elfobjdir)/ld.so
$(objpfx)libnss_db.so: $(elfobjdir)/ld.so
$(objpfx)libnss_nis.so: $(elfobjdir)/ld.so
$(objpfx)libnss_nisplus.so: $(elfobjdir)/ld.so
$(objpfx)libnss_hesiod.so: $(elfobjdir)/ld.so
$(objpfx)libnss_compat.so: $(elfobjdir)/ld.so
$(objpfx)libanl.so: $(elfobjdir)/ld.so
$(objpfx)libnsl.so: $(elfobjdir)/ld.so
$(objpfx)libcidn.so: $(elfobjdir)/ld.so
$(objpfx)libutil.so: $(elfobjdir)/ld.so

