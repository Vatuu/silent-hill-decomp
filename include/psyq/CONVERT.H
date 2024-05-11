/*
 * File:convert.h
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */
#ifndef _CONVERT_H
#define _CONVERT_H

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
extern int atoi(char *);
extern long atol(char *);
extern long strtol(char *,char**, int);
extern unsigned long strtoul(char *, char **, int);
extern long labs(long);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif
