/*
 * File:file.h
*/
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef _SYS_FILE_H
#define _SYS_FILE_H

#include <sys/fcntl.h>

/* Flag for open() */
#define O_RDONLY        FREAD
#define O_WRONLY        FWRITE
#define O_RDWR          FREAD|FWRITE
#define O_CREAT         FCREAT  /* open with file create */
#define O_NOBUF         FNBUF	/* no device buffer and console interrupt */
#define O_NBLOCK        FNBLOCK	/* non blocking mode */
#define O_NOWAIT        FASYNC	/* asyncronous i/o */

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif
#ifndef SEEK_END
#define SEEK_END 2
#endif

#endif /* _SYS_FILE_H */

