/* Copyright (C) 2002, 2003, 2004, 2005 Free Software Foundation, Inc.
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

#include <stdint.h>
#include <sysdep.h>


typedef int8_t atomic8_t;
typedef uint8_t uatomic8_t;
typedef int_fast8_t atomic_fast8_t;
typedef uint_fast8_t uatomic_fast8_t;

typedef int32_t atomic32_t;
typedef uint32_t uatomic32_t;
typedef int_fast32_t atomic_fast32_t;
typedef uint_fast32_t uatomic_fast32_t;

typedef intptr_t atomicptr_t;
typedef uintptr_t uatomicptr_t;
typedef intmax_t atomic_max_t;
typedef uintmax_t uatomic_max_t;


/*
 * Microblaze does not have byte and halfword forms of load and reserve and
 * store conditional. So for microblaze we stub out the 8- and 16-bit forms.
 */
#define __arch_compare_and_exchange_bool_8_acq(mem, newval, oldval)                           \
  (abort (), 0)

#define __arch_compare_and_exchange_bool_16_acq(mem, newval, oldval)                          \
  (abort (), 0)

#define __arch_compare_and_exchange_bool_8_rel(mem, newval, oldval)                           \
  (abort (), 0)

#define __arch_compare_and_exchange_bool_16_rel(mem, newval, oldval)                          \
  (abort (), 0)

#define __arch_compare_and_exchange_val_32_acq(mem, newval, oldval)                           \
  ({                                                                                          \
      __typeof (*(mem)) __tmp;                                                                \
      __typeof (mem)  __memp = (mem);                                                         \
      int test;                                                                               \
      __asm __volatile (                                                                      \
                "   addc    r0, r0, r0;"    /* clean carry bit*/                              \
                "1: lwx     %0, %3, r0;"    /* atomic_add_return */                           \
                "   addic   %1, r0, 0;"     /* check Carry*/                                  \
                "   bnei    %1, 1b;"        /* jump if Carry is set*/                         \
                "   cmp     %1, %0, %4;"    /* compare signed values loaded/newval */         \
                "   bnei    %1, 2f;"        /* if is not equal - jump over */                 \
                "   swx     %5, %3, r0;"    /* save newval */                                 \
                "   addic   %1, r0, 0;"     /* check Carry if saving was OK */                \
                "   bnei    %1, 1b;"        /* jump if swx wasn't successful */               \
                "2:"                                                                          \
                    : "=&r" (__tmp),        /* %0 */                                          \
                    "=&r" (test),           /* %1 */                                          \
                    "=m" (*__memp)          /* Dummy output so gcc knows writing *__memp */   \
                    : "r" (__memp),         /* %3 */                                          \
                    "r" (oldval),           /* %4 */                                          \
                    "r" (newval)            /* %5 */                                          \
                    : "cc", "memory");                                                        \
      __tmp;                                                                                  \
  })

#define __arch_compare_and_exchange_val_64_acq(mem, newval, oldval)                           \
  (abort (), (__typeof (*mem)) 0)

#define atomic_compare_and_exchange_val_acq(mem, newval, oldval)                              \
  ({                                                                                          \
    __typeof (*(mem)) __result;                                                               \
    if (sizeof (*mem) == 4)                                                                   \
      __result = __arch_compare_and_exchange_val_32_acq(mem, newval, oldval);                 \
    else if (sizeof (*mem) == 8)                                                              \
      __result = __arch_compare_and_exchange_val_64_acq(mem, newval, oldval);                 \
    else                                                                                      \
       abort ();                                                                              \
    __result;                                                                                 \
  })

#define atomic_compare_and_exchange_val_rel(mem, newval, oldval)                              \
  ({                                                                                          \
    __typeof (*(mem)) __result;                                                               \
    if (sizeof (*mem) == 4) {                                                                 \
        if (__builtin_types_compatible_p (typeof (*mem), int))                                \
            __result = __arch_compare_and_exchange_val_32_acq(mem, newval, oldval);           \
        else if (__builtin_types_compatible_p (typeof (*mem), unsigned int))                  \
            __result = __arch_compare_and_exchange_val_32_acq_unsigned(mem, newval, oldval);  \
    }                                                                                         \
    else if (sizeof (*mem) == 8)                                                              \
      __result = __arch_compare_and_exchange_val_64_acq(mem, newval, oldval);                 \
    else                                                                                      \
       abort ();                                                                              \
    __result;                                                                                 \
  })

#define __arch_atomic_exchange_32_acq(mem, value)                                             \
  ({                                                                                          \
      __typeof (*(mem)) __tmp;                                                                \
      __typeof (mem)  __memp = (mem);                                                         \
      int test;                                                                               \
      __asm __volatile (                                                                      \
                "   addc    r0, r0, r0;"    /* clean carry bit*/                              \
                "1: lwx     %0, %4, r0;"    /* atomic_add_return */                           \
                "   addic   %1, r0, 0;"     /* check Carry*/                                  \
                "   bnei    %1, 1b;"        /* jump if Carry is set*/                         \
                "   swx     %3, %4, r0;"    /* save newval */                                 \
                "   addic   %1, r0, 0;"     /* check Carry if saving was OK */                \
                "   bnei    %1, 1b;"        /* jump if swx wasn't successful */               \
                    : "=&r" (__tmp),        /* %0 */                                          \
                    "=&r" (test),           /* %1 */                                          \
                    "=m" (*__memp)          /* Dummy output so gcc knows writing *__memp */   \
                    : "r" (value),          /* %3 */                                          \
                    "r" (__memp)            /* %4 */                                          \
                    : "cc", "memory");                                                        \
      __tmp;                                                                                  \
  })

#define __arch_atomic_exchange_64_acq(mem, newval)                                            \
  (abort (), (__typeof (*mem)) 0)

#define atomic_exchange_acq(mem, value)                                                       \
  ({                                                                                          \
    __typeof (*(mem)) __result;                                                               \
    if (sizeof (*mem) == 4)                                                                   \
      __result = __arch_atomic_exchange_32_acq (mem, value);                                  \
    else if (sizeof (*mem) == 8)                                                              \
      __result = __arch_atomic_exchange_64_acq (mem, value);                                  \
    else                                                                                      \
       abort ();                                                                              \
    __result;                                                                                 \
  })

#define atomic_exchange_rel(mem, value)                                                       \
  ({                                                                                          \
    __typeof (*(mem)) __result;                                                               \
    if (sizeof (*mem) == 4)                                                                   \
      __result = __arch_atomic_exchange_32_acq (mem, value);                                  \
    else if (sizeof (*mem) == 8)                                                              \
      __result = __arch_atomic_exchange_64_acq (mem, value);                                  \
    else                                                                                      \
       abort ();                                                                              \
    __result;                                                                                 \
  })

#define __arch_atomic_exchange_and_add_32(mem, value)                                         \
  ({                                                                                          \
    __typeof (*(mem)) __tmp;                                                                  \
      __typeof (mem)  __memp = (mem);                                                         \
    int test;                                                                                 \
    __asm __volatile (                                                                        \
                "   addc    r0, r0, r0;"    /* clean carry bit*/                              \
                "1: lwx     %0, %4, r0;"    /* atomic_add_return */                           \
                "   addic   %1, r0, 0;"     /* check Carry*/                                  \
                "   bnei    %1, 1b;"        /* jump if Carry is set*/                         \
                "   add     %1, %3, %0;"    /* add value */                                   \
                "   swx     %1, %4, r0;"    /* save value back */                             \
                "   addic   %1, r0, 0;"     /* check Carry if saving was OK */                \
                "   bnei    %1, 1b;"        /* jump if swx wasn't successful */               \
                    : "=&r" (__tmp),        /* %0 */                                          \
                    "=&r" (test),           /* %1 */                                          \
                    "=m" (*__memp)          /* Dummy output so gcc knows writing *__memp */   \
                    : "r" (value),          /* %3 */                                          \
                    "r" (__memp)            /* %4 */                                          \
                    : "cc", "memory");                                                        \
    __tmp;                                                                                    \
  })

#define __arch_atomic_exchange_and_add_64(mem, value)                                         \
  (abort (), (__typeof (*mem)) 0)

#define atomic_exchange_and_add(mem, value)                                                   \
  ({                                                                                          \
    __typeof (*(mem)) __result;                                                               \
    if (sizeof (*mem) == 4)                                                                   \
      __result = __arch_atomic_exchange_and_add_32 (mem, value);                              \
    else if (sizeof (*mem) == 8)                                                              \
      __result = __arch_atomic_exchange_and_add_64 (mem, value);                              \
    else                                                                                      \
       abort ();                                                                              \
    __result;                                                                                 \
  })

#define __arch_atomic_increment_val_32(mem)                                                   \
  ({                                                                                          \
    __typeof (*(mem)) __val;                                                                  \
    int test;                                                                                 \
    __asm __volatile (                                                                        \
                "   addc    r0, r0, r0;"    /* clean carry bit*/                              \
                "1: lwx     %0, %3, r0;"    /* atomic_add_return*/                            \
                "   addic   %1, r0, 0;"     /* check Carry*/                                  \
                "   bnei    %1, 1b;"        /* jump if Carry is set*/                         \
                "   addi    %0, %0, 1;"     /* add 1 */                                       \
                "   swx     %0, %3, r0;"    /* save value back */                             \
                "   addic   %1, r0, 0;"     /* check Carry if saving was OK */                \
                "   bnei    %1, 1b;"        /* jump if swx wasn't successful */               \
                    : "=&r" (__val),        /* %0 */                                          \
                    "=&r" (test),           /* %1 */                                          \
                    "=m" (*mem)             /* Dummy output so gcc knows writing *mem */      \
                    : "r" (mem),            /* %3 */                                          \
                    "m" (*mem)              /* %4 */                                          \
                    : "cc", "memory");                                                        \
    __val;                                                                                    \
  })

#define __arch_atomic_increment_val_64(mem)                                                   \
  (abort (), (__typeof (*mem)) 0)

#define atomic_increment_val(mem)                                                             \
  ({                                                                                          \
    __typeof (*(mem)) __result;                                                               \
    if (sizeof (*(mem)) == 4)                                                                 \
      __result = __arch_atomic_increment_val_32 (mem);                                        \
    else if (sizeof (*(mem)) == 8)                                                            \
      __result = __arch_atomic_increment_val_64 (mem);                                        \
    else                                                                                      \
       abort ();                                                                              \
    __result;                                                                                 \
  })

#define atomic_increment(mem) ({ atomic_increment_val (mem); (void) 0; })

#define __arch_atomic_decrement_val_32(mem)                                                   \
  ({                                                                                          \
    __typeof (*(mem)) __val;                                                                  \
    int test;                                                                                 \
    __asm __volatile (                                                                        \
                "   addc    r0, r0, r0;"    /* clean carry bit*/                              \
                "1: lwx     %0, %3, r0;"    /* atomic_add_return*/                            \
                "   addic   %1, r0, 0;"     /* check Carry*/                                  \
                "   bnei    %1, 1b;"        /* jump if Carry is set*/                         \
                "   rsubi   %0, %0, 1;"     /* sub 1 */                                       \
                "   swx     %0, %3, r0;"    /* save value back */                             \
                "   addic   %1, r0, 0;"     /* check Carry if saving was OK */                \
                "   bnei    %1, 1b;"        /* jump if swx wasn't successful */               \
                    : "=&r" (__val),        /* %0 */                                          \
                    "=&r" (test),           /* %1 */                                          \
                    "=m" (*mem)             /* Dummy output so gcc knows writing *mem */      \
                    : "r" (mem),            /* %3 */                                          \
                    "m" (*mem)              /* %4 */                                          \
                    : "cc", "memory");                                                        \
    __val;                                                                                    \
  })

#define __arch_atomic_decrement_val_64(mem)                                                   \
  (abort (), (__typeof (*mem)) 0)

#define atomic_decrement_val(mem)                                                             \
  ({                                                                                          \
    __typeof (*(mem)) __result;                                                               \
    if (sizeof (*(mem)) == 4)                                                                 \
      __result = __arch_atomic_decrement_val_32 (mem);                                        \
    else if (sizeof (*(mem)) == 8)                                                            \
      __result = __arch_atomic_decrement_val_64 (mem);                                        \
    else                                                                                      \
       abort ();                                                                              \
    __result;                                                                                 \
  })


#define atomic_decrement(mem) ({ atomic_decrement_val (mem); (void) 0; })

