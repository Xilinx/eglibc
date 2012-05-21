ifeq ($(subdir),misc)
sysdep_routines += mremap
sysdep_headers += sys/reg.h
endif

ifeq ($(subdir),elf)
sysdep-others += lddlibc4
install-bin += lddlibc4
endif

ifeq ($(subdir),resource)
sysdep_routines += oldgetrlimit64 backtrace_linux
endif
