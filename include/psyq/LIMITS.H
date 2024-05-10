/*
 * File:limits.h
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef _LIMITS_H
#define _LIMITS_H
/*
 * This file specifies the sizes of intergral types as required by the
 * proposed ANSI C standard.
 */

#define CHAR_BIT	8
#define SCHAR_MIN	(-128)
#define SCHAR_MAX	127
#define UCHAR_MAX	255
#define CHAR_MIN	SCHAR_MIN
#define CHAR_MAX	SCHAR_MAX
#define SHRT_MIN	(-32768)
#define SHRT_MAX	32767
#define USHRT_MAX	65535
#define INT_MIN		(-2147483648)
#define INT_MAX		2147483647
#define UINT_MAX	4294967295
#define LONG_MIN	(-2147483648)
#define LONG_MAX	2147483647
#define ULONG_MAX	4294967295

#define	USI_MAX		4294967295	/* max decimal value of an "unsigned" */
#define	WORD_BIT	32		/* # of bits in a "word" or "int" */

#ifndef MB_LEN_MAX
#define MB_LEN_MAX	4
#endif

#endif /* _LIMITS_H */
