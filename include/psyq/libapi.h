#ifndef _LIBAPI_H_
#define _LIBAPI_H_

/*
 *	File:libapi.h
 *	Copyright (C) 1997 by Sony Computer Entertainment Inc.
 *			All rights Reserved
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef _KERNEL_H
#include "kernel.h"
#endif

/* don't change these macros and structures which is referred in controler code */

/*
 * Prototypes
 */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

/* prototypes added by suzu 96/03/01 and changed by hakama 96/06/06*/

extern long SetRCnt(unsigned long, unsigned short, long);
extern long GetRCnt(unsigned long);
extern long ResetRCnt(unsigned long);
extern long StartRCnt(unsigned long);
extern long StopRCnt(unsigned long);

extern long OpenEvent(unsigned long,long,long,long (*func)());
extern long CloseEvent(long);
extern long WaitEvent(long);
extern long TestEvent(long);
extern long EnableEvent(long);
extern long DisableEvent(long);
extern void DeliverEvent(unsigned long, unsigned long);
extern void UnDeliverEvent(unsigned long, unsigned long);

extern long OpenTh(long (*func)(), unsigned long , unsigned long);
extern int CloseTh(long);
extern int ChangeTh(long);

extern long open(char *, unsigned long);
extern long close(long);
extern long lseek(long, long, long);
extern long read(long, void *, long);
extern long write(long, void *, long);
extern long ioctl(long, long, long);
extern struct DIRENTRY * firstfile(char *, struct DIRENTRY *);
extern struct DIRENTRY * nextfile(struct DIRENTRY *);
extern long erase(char *);


extern long undelete(char *);
extern long format(char *);
extern long rename(char *, char *);
extern long cd(char *);

extern long LoadTest(char *, struct EXEC *);
extern long Load(char *, struct EXEC *);
extern long Exec(struct EXEC *, long, char **);
extern long LoadExec(char *, unsigned long, unsigned long);

extern long InitPAD(char *,long ,char *,long);
extern long StartPAD(void);
extern void StopPAD(void);
extern void EnablePAD(void);
extern void DisablePAD(void);

extern void FlushCache(void);
extern void ReturnFromException(void);
extern int  EnterCriticalSection(void);
extern void ExitCriticalSection(void);
extern void Exception(void);
extern void SwEnterCriticalSection(void);
extern void SwExitCriticalSection(void);

extern unsigned long SetSp(unsigned long);
extern unsigned long GetSp( void );
extern unsigned long GetGp( void );
extern unsigned long GetCr( void );
extern unsigned long GetSr( void );
extern unsigned long GetSysSp(void);

extern long SetConf(unsigned long,unsigned long,unsigned long);
extern void GetConf(unsigned long *,unsigned long *,unsigned long *);

extern long _get_errno(void);
extern long _get_error(long);

extern void SystemError( char, long);
extern void SetMem(long);

extern long Krom2RawAdd( unsigned long );
extern long Krom2RawAdd2(unsigned short);

extern void _96_init(void);
extern void _96_remove(void);
extern void _boot(void);

extern void ChangeClearPAD( long );

/* prototypes added by shino 96/05/22 */
extern void InitCARD(long val);
extern long StartCARD(void);
extern long StopCARD(void);
extern void _bu_init(void);
extern long _card_info(long chan);
extern long _card_clear(long chan);
extern long _card_load(long chan);
extern long _card_auto(long val);
extern void _new_card(void);
extern long _card_status(long drv);
extern long _card_wait(long drv);
extern unsigned long _card_chan(void);
extern long _card_write(long chan, long block, unsigned char *buf);
extern long _card_read(long chan, long block, unsigned char *buf);
extern long _card_format(long chan);	/* added by iwano 98/03/24 */



#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _LIBAPI_H_ */

/* don't add stuff after this */

