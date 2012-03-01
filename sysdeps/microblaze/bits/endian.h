/* MicroBlaze is big-endian.  */

#ifndef _ENDIAN_H
# error "Never use <bits/endian.h> directly; include <endian.h> instead."
#endif

#ifdef _BIG_ENDIAN
#define __BYTE_ORDER __BIG_ENDIAN
#define __FLOAT_WORD_ORDER __BIG_ENDIAN
#else
#define __BYTE_ORDER __LITTLE_ENDIAN
#define __FLOAT_WORD_ORDER __LITTLE_ENDIAN
#endif
