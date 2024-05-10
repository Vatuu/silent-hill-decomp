/*
 * File:memory.h
 * memory functions pseudo definition header
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef _MEMORY_H
#define _MEMORY_H

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;  /* result type of the sizeof operator (ANSI) */
#endif

#ifndef NULL
#define NULL 0		       /* null pointer constant */
#endif

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
/* To avoid conflicting */
extern void *memcpy (/*  unsigned char *, unsigned char *, int  */); 
extern void *memmove(unsigned char *, unsigned char *, int);
/* To avoid conflicting */
extern int   memcmp (/*  unsigned char *, unsigned char *, int  */);
extern void *memchr (unsigned char *, unsigned char, int);
extern void *memset (/* unsigned char *, unsigned char, int */);

extern void *bcopy(unsigned char *, unsigned char *, int); /* src,dest */
extern void *bzero(unsigned char *, int);
extern int   bcmp (unsigned char *, unsigned char *, int);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _MEMORY_H */





