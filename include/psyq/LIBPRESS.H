/* $PSLibId: Run-time Library Release 4.3$ */
#ifndef _LIBPRESS_H_
#define _LIBPRESS_H_
/*
 *  (C) Copyright 1995 Sony Corporation,Tokyo,Japan. All Rights Reserved
 *
 * 		libpress.h: Prototypes for libpress
 *
 */
/* DecDCTvlc Table */
typedef	u_short DECDCTTAB[34816];

/* DecDCTEnv */	
typedef struct {
	u_char	iq_y[64];	/* IQ (Y): zig-zag order */
	u_char	iq_c[64];	/* IQ (Cb,Cr): zig-zag order */
	short	dct[64];	/* IDCT coef (reserved) */
} DECDCTENV;

typedef struct {
    short *src;			/* 16-bit strait PCM */
    short *dest;		/* PlayStation original waveform data */
    short *work;		/* scratch pad or NULL */
    long   size;		/* size (unit: byte) of source data */
    long   loop_start;		/* loop start point (unit: byte) of source data */
    char   loop;		/* whether loop or not */
    char   byte_swap;		/* source data is 16-bit big endian (1) / little endian (0) */
    char   proceed;		/* proceeding ? whole (0) / start (1) / cont. (2) / end (4) */
    char   pad4;		/* reserved */
} ENCSPUENV;
	
#define ENCSPU_ENCODE_ERROR    (-1)
#define ENCSPU_ENCODE_WHOLE     0
#define ENCSPU_ENCODE_START    (1<<0)
#define ENCSPU_ENCODE_CONTINUE (1<<1)
#define ENCSPU_ENCODE_END      (1<<2)

#define ENCSPU_ENCODE_LOOP    1
#define ENCSPU_ENCODE_NO_LOOP 0

#define ENCSPU_ENCODE_ENDIAN_LITTLE 0
#define ENCSPU_ENCODE_ENDIAN_BIG    1

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
extern void DecDCTReset(int mode);
extern DECDCTENV *DecDCTGetEnv(DECDCTENV *env);
extern DECDCTENV *DecDCTPutEnv(DECDCTENV *env);
extern int DecDCTBufSize(u_long *bs);
extern int DecDCTvlc(u_long *bs, u_long *buf);
extern int DecDCTvlc2(u_long *bs, u_long *buf, DECDCTTAB table);
extern int DecDCTvlcSize(int size);
extern int DecDCTvlcSize2(int size);
extern void DecDCTvlcBuild(u_short *table);
extern void DecDCTin(u_long *buf, int mode);
extern void DecDCTout(u_long *buf, int size);
extern int DecDCTinSync( int mode) ;
extern int DecDCToutSync( int mode) ;
extern int DecDCTinCallback(void (*func)());
extern int DecDCToutCallback(void (*func)());

extern long EncSPU (ENCSPUENV *env);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif
#endif /* _LIBPRESS_H_ */
