/* The GNU C Library is free software; you can redistribute it and/or
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

#ifdef HAVE_ELF

/* ELF uses byte-counts for .align, most others use log2 of count of bytes.  */
#define ALIGNARG(log2) 1<<log2
/* For ELF we need the `.type' directive to make shared libs work right.  */
#define PROLOG(name) .type name,@function
#define EPILOG(name) .size name,.-name
/* For ELF we need to prefix register names and local labels.  */
#ifdef __STDC__
#define R_(r) %##r
#define R(r) R_(r)
#define L(label) .##label
#else
#define R(r) %/**/r
#define L(label) ./**/label
#endif

#else

#define ALIGNARG(log2) log2
#define PROLOG(name) /* Nothing.  */
#define EPILOG(name) /* Nothing.  */
#define R(r) r
#define L(label) label

#endif
