#ifndef _LIBPAD_H_
#define _LIBPAD_H_

/*
 *	File:libpad.h
 *	Copyright (C) 1997 by Sony Computer Entertainment Inc.
 *			All rights Reserved
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

/* don't change these macros and structures which is referred in controler code */ 

#ifndef TRUE
#define TRUE		1
#endif
#ifndef FALSE
#define FALSE		0
#endif
#ifndef NULL
#define NULL		0
#endif


#define PadStateDiscon		0
#define PadStateFindPad		1
#define PadStateFindCTP1	2
#define PadStateFindCTP2	3
#define PadStateReqInfo		4
#define PadStateExecCmd		5
#define PadStateStable		6

#define InfoModeCurID		1
#define InfoModeCurExID		2
#define InfoModeCurExOffs	3
#define InfoModeIdTable		4

#define InfoActFunc		1
#define InfoActSub		2
#define InfoActSize		3
#define InfoActCurr		4
#define InfoActSign		5

#define PadMaxCurr		60	/* PS maximum current supply */
#define PadCurrCTP1		10	/* SCPH-1150 biblator current */


/*
 * Prototypes
 */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

void PadInitDirect(unsigned char *, unsigned char *);
void PadInitMtap(unsigned char *, unsigned char *);
void PadInitGun(unsigned char *, int);
int PadChkVsync(void);
void PadStartCom(void);
void PadStopCom(void);
unsigned PadEnableCom(unsigned);
void PadEnableGun(unsigned char);
void PadRemoveGun(void);
int PadGetState(int);
int PadInfoMode(int, int, int);
int PadInfoAct(int, int, int);
int PadInfoComb(int, int, int);
int PadSetActAlign(int, unsigned char *);
int PadSetMainMode(int socket, int offs, int lock);
void PadSetAct(int, unsigned char *, int);


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _LIBPAD_H_ */

/* don't add stuff after this */

