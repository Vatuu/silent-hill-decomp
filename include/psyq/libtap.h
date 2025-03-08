/* $PSLibId: Run-time Library Release 4.3$ */
#ifndef _LIBTAP_H_
#define _LIBTAP_H_

/*
 *  Copyright (C) 1996 Sony Computer Entertainment Inc. All Rights Reserved
 *  libtap.h: Multi Tap Interface
 */

/*
 * Prototypes
 */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
extern void InitTAP(char *, long, char *, long);
extern void StartTAP(void);
extern void StopTAP(void);
extern void SendTAP(char *, long, char *, long);
extern void EnableTAP(void);
extern void DisableTAP(void);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif
#endif /* _LIBTAP_H_ */
