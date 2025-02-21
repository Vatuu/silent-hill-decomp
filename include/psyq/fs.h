/*
 * File:fs.h
 */
/*
 * $PSLibId: Run-time Library Release 4.3$
 */

#ifndef _FS_H
#define _FS_H

#if defined(_LANGUAGE_C)||defined(LANGUAGE_C)||defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)

/* device table */
struct device_table {
	char *dt_string;	/* device name */
	int dt_type;		/* device "type" */
	int dt_bsize;		/* file system type */
	char *dt_desc;		/* device description */
	int (*dt_init)();	/* device init routine */
	int (*dt_open)();	/* device open routine */
	int (*dt_strategy)();	/* device strategy routine, returns cnt */
	int (*dt_close)();	/* device close routine */
	int (*dt_ioctl)();	/* device ioctl routine */
	int (*dt_read)();	/* fs read routine, returns count */
	int (*dt_write)();	/* fs write routine, return count */
	int (*dt_delete)();	/* file delete routine */
	int (*dt_undelete)();	/* file delete routine */
	int (*dt_firstfile)();	/* directory serach routine */
	int (*dt_nextfile)();	/* directory serach routine */
	int (*dt_format)();
	int (*dt_cd)();	
	int (*dt_rename)();	
	int (*dt_remove)();	
	int (*dt_else)();	
};
#endif /* LANGUAGE_C */

/* device types */
#define	DTTYPE_CHAR	0x1	/* character device */
#define	DTTYPE_CONS	0x2	/* can be console */
#define	DTTYPE_BLOCK	0x4	/* block device */
#define DTTYPE_RAW	0x8	/* raw device that uses fs switch */
#define DTTYPE_FS	0x10


/* character device flags */
#define	DB_RAW		0x1	/* don't interpret special chars */
#define	DB_STOPPED	0x2	/* stop output */
#define	DB_BREAK	0x4	/* cntl-c raise console interrpt */

/* character device buffer */
#define	CBUFSIZE	256

#if defined(_LANGUAGE_C)||defined(LANGUAGE_C)||defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
struct device_buf {
	int db_flags;		/* character device flags */
	char *db_in;		/* pts at next free char */
	char *db_out;		/* pts at next filled char */
	char db_buf[CBUFSIZE];	/* circular buffer for input */
};
#endif /* LANGUAGE_C */

/* circular buffer functions */
#define	CIRC_EMPTY(x)	((x)->db_in == (x)->db_out)
#define	CIRC_FLUSH(x)	((x)->db_in = (x)->db_out = (x)->db_buf)
#define	CIRC_STOPPED(x)	((x)->db_flags & DB_STOPPED)


/* io block */
#if defined(_LANGUAGE_C)||defined(LANGUAGE_C)||defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
struct	iob {
	int	i_flgs;		
	int	i_unit;		/* pseudo device unit */
	char	*i_ma;		/* memory address of i/o buffer */
	unsigned int	i_cc;		/* character count of transfer */
	unsigned long	i_offset;	/* seek offset in file */
	int	i_fstype;	/* file system type */
	int	i_errno;	/* error # return */
	struct device_table *i_dp;	/* pointer into device_table */
        unsigned long    i_size;
        long    i_head;
        long    i_fd;		/* file descriptor */
};
#endif /* LANGUAGE_C */

#ifndef NULL
#define NULL 0
#endif

/* Request codes */
#define	READ	1
#define	WRITE	2

#define NIOB	16	/* max number of open files */

/*
extern int _nulldev();
extern int _nodev();
*/

#endif /* _FS_H */


