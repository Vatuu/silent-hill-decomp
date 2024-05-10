/* $PSLibId: Run-time Library Release 4.3$ */
#ifndef _LIBGUN_H_
#define _LIBGUN_H_

/*
 *  Copyright (C) 1996 Sony Computer Entertainment America. All Rights Reserved
 *  libetc.h: Light Gun Interface
 */

/*
 * Prototypes
 */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
void InitGUN(char *bufA, long lenA, char *bufB, long lenB, char *buf1, char *buf2, long len);
void RemoveGUN(void);
void SelectGUN(int ch, unsigned char mask);
long StartGUN(void);
void StopGUN(void);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif
#endif /* _LIBGUN_H_ */
