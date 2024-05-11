/*
 * File:fcntl.h
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef	_SYS_FCNTL_H
#define	_SYS_FCNTL_H

/* flags */
#define	FREAD		0x0001		/* readable */
#define	FWRITE		0x0002		/* writable */
#define	FNBLOCK		0x0004		/* non-blocking reads */
#define	FRLOCK		0x0010		/* read locked (non-shared) */
#define	FWLOCK		0x0020		/* write locked (non-shared) */
#define	FAPPEND		0x0100		/* append on each write */
#define	FCREAT		0x0200		/* create if nonexistant */
#define	FTRUNC		0x0400		/* truncate to zero length */
#define	FSCAN		0x1000		/* scan type */
#define	FRCOM		0x2000		/* remote command entry */
#define	FNBUF		0x4000		/* no ring buf. and console interrupt */
#define	FASYNC		0x8000		/* asyncronous i/o */

#endif	/* _SYS_FCNTL_H */
