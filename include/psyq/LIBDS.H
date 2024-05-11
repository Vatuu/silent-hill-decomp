/* $PSLibId: Run-time Library Release 4.3$ */
/*
 * libds.h
 *	Copyright(C) 1996 1997, Sony Computer Entertainment Inc.
 *	All Rights Reserved.
 */

#ifndef _LIBDS_H_
#define _LIBDS_H_

#include <kernel.h>

/*
 * CD-ROM Mode (used int CdlSetmode)
 */
#define DslModeStream	0x100	/* Normal Streaming                     */
#define DslModeStream2	0x120	/* SUB HEADER information includes      */
#define DslModeSpeed	0x80	/* 0: normal speed	1: double speed	*/
#define DslModeRT	0x40	/* 0: ADPCM off		1: ADPCM on	*/
#define DslModeSize1	0x20	/* 0: 2048 byte		1: 2340byte	*/
#define DslModeSize0	0x10	/* 0: -			1: 2328byte	*/
#define DslModeSF	0x08	/* 0: Channel off	1: Channel on	*/
#define DslModeRept	0x04	/* 0: Report off	1: Report on	*/
#define DslModeAP	0x02	/* 0: AutoPause off	1: AutoPause on */
#define DslModeDA	0x01	/* 0: CD-DA off		1: CD-DA on	*/

/*
 * Status contents
 */
#define DslStatPlay		0x80	/* playing CD-DA */
#define DslStatSeek		0x40	/* seeking */
#define DslStatRead		0x20	/* reading data sectors */
#define DslStatShellOpen	0x10	/* once shell open */
#define DslStatSeekError	0x04	/* seek error detected */
#define DslStatStandby		0x02	/* spindle motor rotating */
#define DslStatError		0x01	/* command error detected */

/*
 * Macros for DsGetDiskType()
 */
#define DslStatNoDisk		0x01
#define DslOtherFormat		0x02
#define DslCdromFormat		0x04

/*
 * CD-ROM Primitive Commands
 */
#define DslNop			0x01	/* no operation */
#define DslSetloc		0x02	/* set head position */
#define DslPlay			0x03	/* play CD-DA */
#define DslForward		0x04	/* forward DA play */
#define DslBackward		0x05	/* backward DA play */
#define	DslReadN		0x06	/* read data with retry */
#define DslStandby		0x07	/* start spindle motor */
#define DslStop			0x08	/* stop spindle motor */
#define DslPause		0x09	/* pause */
#define DslMute			0x0b	/* mute on */
#define DslDemute		0x0c	/* mute off */
#define DslSetfilter		0x0d	/* set subheader filter */
#define DslSetmode		0x0e	/* set mode */
#define DslGetparam		0x0f	/* get mode */
#define DslGetlocL		0x10	/* get head position (data sector) */
#define DslGetlocP		0x11	/* get head position (DA sector) */
#define DslGetTN		0x13	/* get number of TOC */
#define DslGetTD		0x14	/* get TOC data */
#define DslSeekL		0x15	/* logical seek */
#define DslSeekP		0x16	/* phisical seek */
#define DslReadS		0x1B	/* read data without retry */

/*
 * Interrupts
 */
#define DslNoIntr		0x00	/* No interrupt */
#define DslDataReady		0x01	/* Data Ready */
#define DslComplete		0x02	/* Command Complete */
#define DslAcknowledge		0x03	/* Acknowledge (reserved) */
#define DslDataEnd		0x04	/* End of Data Detected */
#define DslDiskError		0x05	/* Error Detected */

#define DslNoResult		0x06
#define DslFinished		0x07

#ifndef btoi
#define btoi( b )	( ( b ) / 16 * 10 + ( b ) % 16 )
#endif
#ifndef itob
#define itob( i )	( ( i ) / 10 * 16 + ( i ) % 10 )
#endif

/*
 * Position
 */
#define DslMAXTOC	100

/*
 * Callback
 */
typedef void ( *DslCB )( u_char, u_char* );
typedef void ( *DslRCB )( u_char, u_char*, u_long* );

/*
 * Location
 */
typedef struct {
	u_char minute;		/* minute (BCD) */
	u_char second;		/* second (BCD) */
	u_char sector;		/* sector (BCD) */
	u_char track;		/* track (void) */
} DslLOC;

/*
 * ADPCM Filter
 */
typedef struct {
	u_char file;		/* file ID (always 1) */
	u_char chan;		/* channel ID */
	u_short pad;
} DslFILTER;

/*
 * Attenuator
 */
typedef struct {
	u_char val0;		/* volume for CD(L) -> SPU (L) */
	u_char val1;		/* volume for CD(L) -> SPU (R) */
	u_char val2;		/* volume for CD(R) -> SPU (L) */
	u_char val3;		/* volume for CD(R) -> SPU (R) */
} DslATV;

/*
 * Low Level File System for DsSearchFile() 
 */
#define DslMAXFILE	64	/* max number of files in a directory */
#define DslMAXDIR	128	/* max number of total directories */
#define DslMAXLEVEL	8	/* max levels of directories */

typedef struct {
	DslLOC pos;		/* file location */
	u_long size;		/* file size */
	char name[ 16 ];	/* file name (body) */
} DslFILE;

#ifndef _LIBCD_H_
/*
 * Streaming Structures
 */
typedef struct {
	u_short id;
	u_short type;
	u_short secCount;
	u_short nSectors;
	u_long frameCount;
	u_long frameSize;

	u_short width;
	u_short height;
	u_long dummy1;
	u_long dummy2;
	DslLOC loc;
} StHEADER;		/* CD-ROM STR structure */

#define StFREE		0x0000
#define StREWIND	0x0001
#define StCOMPLETE	0x0002
#define StBUSY		0x0003
#define StLOCK		0x0004

#define EDC		0
#define SECTOR_SIZE	( 512 )	/* Sector Size (word) */
#define HEADER_SIZE	( 8 )	/* Header Size (word) */

#define StSTATUS	0x00
#define StVER		0x00
#define StTYPE		0x01
#define StSECTOR_OFFSET	0x02
#define StSECTOR_SIZE	0x03
#define StFRAME_NO	0x04
#define StFRAME_SIZE	0x06

#define StMOVIE_WIDTH	0x08
#define StMOVIE_HEIGHT	0x09

/*
 * streaming library prototype declarations */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

void StSetRing( u_long* ring_addr, u_long ring_size );
void StClearRing( void );
void StUnSetRing( void );
void StSetStream( u_long mode, u_long start_frame, u_long end_frame,
  void ( *func1 )(), void ( *func2 )() );
void StSetEmulate( u_long* addr, u_long mode, u_long start_frame,
  u_long end_frame, void ( *func1 )(), void ( *func2 )() );
u_long StFreeRing( u_long* base );
u_long StGetNext( u_long** addr, u_long** header );
u_long StGetNextS( u_long** addr, u_long** header );
u_short StNextStatus( u_long** addr, u_long** header );
void StRingStatus( short* free_sectors, short* over_sectors );
void StSetMask( u_long mask, u_long start, u_long end );
void StCdInterrupt( void );
int StGetBackloc( DslLOC* loc );
int StSetChannel( u_long channel );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif	/* _LIBCD_H_ */

/* **** system status **** */

#define DslReady	1
#define DslBusy		2
#define DslNoCD		3

/* **** maximum number of commands that can be added to the queue **** */
#define DslMaxCOMMANDS	8

/***** maximum number of command execution results **** */
#define DslMaxRESULTS	8

/***** DS function prototype **** */

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

int DsInit( void );
int DsReset( void );
void DsClose( void );
int DsCommand( u_char com, u_char* param, DslCB cbsync, int count );
int DsPacket( u_char mode, DslLOC* pos, u_char com, DslCB func, int count );
DslCB DsSyncCallback( DslCB func );
DslCB DsReadyCallback( DslCB func );
int DsSync( int id, u_char* result );
int DsReady( u_char* result );
void DsFlush( void );
int DsSystemStatus( void );
int DsQueueLen( void );
u_char DsStatus( void );
int DsShellOpen( void );

int DsMix( DslATV* vol );
int DsGetSector( void* madr, int size );
int DsGetSector2( void* madr, int size );
int DsGetToc( DslLOC* loc );
void ( *DsDataCallback( void ( *func )() ) );
int DsDataSync( int mode );
DslLOC* DsIntToPos( int i, DslLOC* p );
int DsPosToInt( DslLOC* p );
int DsSetDebug( int level );
DslLOC* DsLastPos( DslLOC* p );
u_char DsLastCom( void );

char* DsComstr( u_char com );
char* DsIntstr( u_char intr );

int DsStartReadySystem( DslRCB func, int count );
void DsEndReadySystem( void );
int DsReadySystemMode( int mode );

int DsControlF( u_char com, u_char* param );
int DsControl( u_char com, u_char* param, u_char* result );
int DsControlB( u_char com, u_char* param, u_char* result );

int DsRead( DslLOC* pos, int sectors, u_long* buf, int mode );
int DsReadSync( u_char* result );
DslCB DsReadCallback( DslCB func );
void DsReadBreak( void );
int DsRead2( DslLOC* pos, int mode );

DslFILE* DsSearchFile( DslFILE* fp, char* name );
int DsReadFile( char* file, u_long* addr, int nbyte );
struct EXEC* DsReadExec( char* file );
int DsPlay( int mode, int* tracks, int offset );

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif

#endif	/* _LIBDS_H_ */
