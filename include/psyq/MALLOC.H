/*
 * File:malloc.h
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */
#ifndef _MALLOC_H
#define _MALLOC_H

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
extern void InitHeap (unsigned long *, unsigned long);
extern void free(void *);
extern void *malloc(size_t);
extern void *calloc(size_t, size_t);
extern void *realloc(void *, size_t);
extern void InitHeap2 (unsigned long *, unsigned long);
extern void free2(void *);
extern void *malloc2(size_t);
extern void *calloc2(size_t, size_t);
extern void *realloc2(void *, size_t);
extern void InitHeap3(unsigned long *, unsigned long);
extern void free3(void *);
extern void *malloc3(size_t);
extern void *calloc3(size_t, size_t);
extern void *realloc3(void *, size_t);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _MALLOC_H */

