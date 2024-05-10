/*
 * $PSLibId: Run-time Library Release 4.3$
 */
/*
 * File:stdio.h
*/

#ifndef _STDIO_H
#define _STDIO_H

#define	BUFSIZ 1024
#define EOF (-1)

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;  /* result type of the sizeof operator (ANSI) */
#endif

/* under constraction now */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
extern int printf(char *fmt, ...); /**/
extern int sprintf(char *buffer, char *fmt, ...);

extern char getc(int);		/**/
extern char getchar(void);
extern char *gets(char *);
extern void putc(char, int);	/**/
extern void putchar(char);
extern void puts(char *);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif /* _STDIO_H */
