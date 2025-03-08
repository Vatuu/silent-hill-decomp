/*
 * $PSLibId: Run-time Library Release 4.3$
 */
/*
 * File:libcomb.h
*/
#ifndef _LIBCOMB_H_
#define _LIBCOMB_H_

/* Status bits */
#define COMB_CTS		0x100
#define COMB_DSR		0x80
#define COMB_FE			0x20
#define COMB_OE			0x10
#define COMB_PERROR		0x8
#define COMB_TXU		0x4
#define COMB_RXRDY		0x2
#define COMB_TXRDY		0x1


/* Control bits */
#define COMB_BIT_DTR	0x1
#define COMB_BIT_RTS	0x2

/* Macros */
#define CombSioStatus()		_comb_control(0,0,0)	/* Return serial controller status */
#define CombControlStatus()	_comb_control(0,1,0)	/* Return control line status */
#define CombGetMode()		_comb_control(0,2,0)	/* Return communication mode */
#define CombGetBPS()		_comb_control(0,3,0)	/* Return transfer rate */
#define CombGetPacketSize()	_comb_control(0,4,0)	/* Return current packet size */
#define CombBytesToWrite()	_comb_control(0,5,0)	/* Return # bytes remaining in write buffer */
#define CombBytesToRead()	_comb_control(0,5,1)	/* Return # bytes remaining to be read */
#define CombBytesRemaining(a)	_comb_control(0,5,a)	/* Return # bytes remaining to read or write */
#define CombAsyncRequest(a)	_comb_control(0,6,a)	/* Return async read/write request */

#define CombSetControl(a)	_comb_control(1,1,a)	/* Set the control line status */
#define CombSetMode(a)		_comb_control(1,2,a)	/* Sets communications mode */
#define CombSetBPS(a)		_comb_control(1,3,a)	/* Sets the transfer rate */
#define CombSetPacketSize(a)	_comb_control(1,4,a)	/* Sets the packet size */

#define	CombReset()		_comb_control(2,0,0)	/* Reset serial controller */
#define	CombResetError()	_comb_control(2,1,0)	/* Reset error bits */
#define	CombCancelWrite()	_comb_control(2,2,0)	/* Cancel async write request */
#define CombCancelRead()	_comb_control(2,3,0)	/* Cancel async read request */

#define CombSetRTS(a)		_comb_control(3,0,a)	/* Set RTS to 'a' */
#define CombCTS()		_comb_control(3,1,0)	/* Return status of CTS */

#define CombWaitCallback(a)	_comb_control(4,0,a)	/* Install wait callback function */

#define CombResetVBLANK()	_comb_control(5,0,0)	/* Restart VBLANK signal */

/* Prototypes */
#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif

extern void AddCOMB(void);
extern void DelCOMB(void);
extern void ChangeClearSIO(long);
extern long _comb_control(unsigned long,unsigned long,unsigned long);

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif
#endif /*_LIBCOMB_H_*/

