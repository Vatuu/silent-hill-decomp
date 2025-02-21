/*
 * File:stddef.h
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef _STDDEF_H
#define _STDDEF_H


#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;  /* result type of the sizeof operator (ANSI) */
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
typedef unsigned long wchar_t;		 /* type of a wide character */
#endif

#ifndef _UCHAR_T
#define _UCHAR_T
typedef unsigned char u_char;
#endif

#ifndef _USHORT_T
#define _USHORT_T
typedef unsigned short u_short;
#endif

#ifndef _UINT_T
#define _UINT_T
typedef	unsigned int u_int;
#endif

#ifndef _ULONG_T
#define _ULONG_T
typedef unsigned long u_long;
#endif

#ifndef WEOF
#define WEOF    0xffffffff
#endif

#ifndef NULL
#define NULL 0		       /* null pointer constant */
#endif

#endif /* _STDDEF_H */
