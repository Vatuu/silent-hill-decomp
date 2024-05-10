/*
 * File:strings.h
 * string functions pseudo definition header 
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef	_STRINGS_H
#define	_STRINGS_H

#define LMAX 256

#ifndef NULL
#define NULL 0		       /* null pointer constant */
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned int size_t;  /* result type of the sizeof operator (ANSI) */
#endif

#include <memory.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif
extern char *strcat (char *, char *);
extern char *strncat(char *, char *, int);
extern int   strcmp (/* char *, char * */);	/* To avoid conflicting */
extern int   strncmp(char *, char *, int);
extern char *strcpy (/* char *, char * */);	/* To avoid conflicting */
extern char *strncpy(char *, char *, int);
extern int   strlen (/* char * */);		/* To avoid conflicting */
extern char *index  (char *, char);
extern char *rindex (char *, char);

extern char *strchr (char *, char);
extern char *strrchr(char *, char);
extern char *strpbrk(char *, char *);
extern int   strspn (char *, char *);
extern int   strcspn(char *, char *);
extern char *strtok (char *, char *);
extern char *strstr (char *, char *);
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#define strdup(p)	( strcpy(malloc(strlen(p)+1),p); )

#endif	/* _STRINGS_H */

