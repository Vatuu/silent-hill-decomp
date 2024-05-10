/*
 * File:rand.h
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef _RAND_H
#define _RAND_H

#define RAND_MAX	32767

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
extern int  rand(void);
extern void srand(unsigned int);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _RAND_H */
