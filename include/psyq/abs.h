/*
 * File:abs.h
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef _ABS_H
#define _ABS_H

#ifndef ABS
#define ABS(x) (((x)>=0)?(x):(-(x)))
#endif /* abs */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
extern int abs(int);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _ABS_H */

