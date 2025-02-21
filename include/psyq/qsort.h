/*
 * File:qsort.h
 * memory functions pseudo definition header
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef _QSORT_H
#define _QSORT_H

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
extern void qsort(void *, size_t, size_t, int (*)());
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif  /* _QSORT_H */

