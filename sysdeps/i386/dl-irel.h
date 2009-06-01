/* Machine-dependent ELF indirect relocation inline functions.
   i386 version.
   Copyright (C) 2009 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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

#ifndef _DL_IREL_H
#define _DL_IREL_H

#include <unistd.h>

#define ELF_MACHINE_IREL	1

static inline void
__attribute ((always_inline))
elf_irel (const Elf32_Rel *reloc)
{
  Elf32_Addr *const reloc_addr = (void *) reloc->r_offset;
  const unsigned long int r_type = ELF32_R_TYPE (reloc->r_info);

  if (__builtin_expect (r_type == R_386_IRELATIVE, 1))
    {
      Elf64_Addr value = ((Elf32_Addr (*) (void)) (*reloc_addr)) ();
      *reloc_addr = value;
    }
  else
    _exit (-1);
}

#endif /* dl-irel.h */
