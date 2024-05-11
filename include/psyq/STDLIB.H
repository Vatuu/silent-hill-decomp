/*
 * File:stdlib.h
*/
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef _STDLIB_H
#define _STDLIB_H

#include <stddef.h>
#include <abs.h>
#include <convert.h>
#include <malloc.h>
#include <qsort.h>
#include <rand.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern void *bsearch(unsigned char *, unsigned char *, size_t, size_t, int (*)());
extern void exit();

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _STDLIB_H */
