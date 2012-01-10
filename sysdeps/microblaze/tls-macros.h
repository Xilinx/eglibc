
#define TLS_LD(x)					\
  ({ char *__result;					\
     int __offset;					\
     extern void *__tls_get_addr (void *);		\
     asm ("mfs r20,rpc \n"				\
	  "addik r20,r20,_GLOBAL_OFFSET_TABLE_+8\n"     \
	  "addik %0,r20," #x "@TLSLDM"                  \
	  : "=r" (__result));				\
     __result = (char *)__tls_get_addr (__result);	\
     asm ("addik %0,r0,"#x"@TLSDTPREL"                  \
	  : "=r" (__offset));				\
     (int *) (__result + __offset); })


#define TLS_GD(x)					\
  ({ int *__result;					\
     extern void *__tls_get_addr (void *);		\
     asm ("mfs  r20,rpc\n"				\
	  "addik r20,r20,_GLOBAL_OFFSET_TABLE_+8\n"     \
	  "addik %0,r20," #x "@TLSGD"			\
	  : "=r" (__result));				\
     (int *)__tls_get_addr (__result); })

/* REVISIT: Modify these when LE and IE are supported */

#define TLS_LE(x) TLS_LD(x)

#define TLS_IE(x) TLS_GD(x)
