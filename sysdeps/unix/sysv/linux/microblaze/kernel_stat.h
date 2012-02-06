/* Definition of `struct stat' used in the kernel..  */
/* Definition of `struct stat' used in the kernel..  */

struct kernel_stat
{
        unsigned long   st_dev;         /* Device.  */
        unsigned long   st_ino;         /* File serial number.  */
        unsigned int    st_mode;        /* File mode.  */
        unsigned int    st_nlink;       /* Link count.  */
        unsigned int    st_uid;         /* User ID of the file's owner.  */
        unsigned int    st_gid;         /* Group ID of the file's group. */
        unsigned long   st_rdev;        /* Device number, if device.  */
        unsigned long   __pad2;
#define _HAVE_STAT___PAD2
#define _HAVE_STAT64___PAD2
        long            st_size;        /* Size of file, in bytes.  */
        int             st_blksize;     /* Optimal block size for I/O.  */
        int             __pad3;
#define _HAVE_STAT___PAD3
#define _HAVE_STAT64___PAD3
        long            st_blocks;      /* Number 512-byte blocks allocated. */
        struct timespec st_atim;
        struct timespec st_mtim;
        struct timespec st_ctim;
#define _HAVE_STAT_NSEC
#define _HAVE_STAT64_NSEC
        unsigned int    __unused4;
#define _HAVE_STAT___UNUSED4
#define _HAVE_STAT64___UNUSED4
        unsigned int    __unused5;
#define _HAVE_STAT___UNUSED5
#define _HAVE_STAT64___UNUSED5
};

#if 0
struct kernel_stat
  {
    unsigned short int st_dev;
    unsigned short int __pad1;
#define _HAVE___PAD1
    unsigned long int st_ino;
    unsigned short int st_mode;
    unsigned short int st_nlink;
    unsigned short int st_uid;
    unsigned short int st_gid;
    unsigned short int st_rdev;
    unsigned short int __pad2;
#define _HAVE___PAD2
    unsigned long __pad3;
#define _HAVE___PAD3
    unsigned long int st_size;
    unsigned long int st_blksize;
    int __pad4;
#define _HAVE___PAD4
    unsigned long int st_blocks;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
    unsigned long int __unused4;
#define _HAVE___UNUSED4
    unsigned long int __unused5;
#define _HAVE___UNUSED5
  };

#define _HAVE_STAT___UNUSED4
#define _HAVE_STAT___UNUSED5
#define _HAVE_STAT___PAD1
#define _HAVE_STAT___PAD2
#define _HAVE_STAT___PAD3
#define _HAVE_STAT___PAD4
#define _HAVE_STAT_NSEC
#define _HAVE_STAT64___PAD1
#define _HAVE_STAT64___PAD2
#define _HAVE_STAT64___PAD3
#define _HAVE_STAT64___PAD4
#define _HAVE_STAT64___ST_INO
#define _HAVE_STAT64_NSEC
#endif
