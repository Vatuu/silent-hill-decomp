#ifndef _FSQUEUE_H
#define _FSQUEUE_H

#include "common.h"
#include "main/fileinfo.h"

 /** FS queue size. */
#define FS_QUEUE_LENGTH 32

#define FS_BUFFER0 ((void*)0x8010A600)
#define FS_BUFFER1 ((void*)0x801E2600)

/** @brief `FsQueue::state` values when processing a read operation (`Fs_UpdateQueueRead`).
 *
 * When `Fs_UpdateQueue` is called and the current op is a read, it will perform the corresponding action below.
 * Unless otherwise specified, success of that action will advance to the next state.
 *
 * `FSQS_READ_RESET` and `FSQS_READ_CHECK` perform one check/tick iteration every time `Fs_UpdateQueue` is called
 * and only advance to the next state when they're done.
 */
enum FsQueueReadState
{
    FSQS_READ_ALLOCATE = 0, /** Allocate memory for the current read operation (`fsQueueAllocData`), if needed. */
    FSQS_READ_CHECK    = 1, /** Check if the current read operation can proceed (`Fs_CanReadQueue`). Goto next state if it can. */
    FSQS_READ_SETLOC   = 2, /** Set start sector from `info` (`Fs_TickQueueSetLoc`). If failure, goto `FSQS_READ_RESET`. */
    FSQS_READ_READ     = 3, /** Read from CD (`Fs_TickQueueRead`). If failure, goto `FSQS_READ_RESET`. */
    FSQS_READ_SYNC     = 4, /** Wait for read to complete. If failure, goto `FSQS_READ_RESET`. */
    FSQS_READ_RESET    = 5  /** Tick the reset timers (`Fs_ResetQueueTick`). When done, reset CD driver and goto `FSQS_READ_SETLOC`. */
};

/** @brief `FsQueue::state` values when processing a seek operation (`Fs_UpdateQueueSeek`).
 *
 * When `Fs_UpdateQueue` is called and the current op is a seek, it will perform the corresponding action below.
 * Unless otherwise specified, success of that action will advance to the next state.
 */
enum FsQueueSeekState
{
    FSQS_SEEK_SET_LOC = 0, /** Set seek sector from `info` (`Fs_TickQueueSetLoc`). */
    FSQS_SEEK_SEEKL   = 1, /** Start seeking to above location (via `CdControl(CdlSeekL, ...)`). */
    FSQS_SEEK_SYNC    = 2, /** Wait for seek to complete (`CdSync()`). If `CdlDiskError`, goto `FSQS_SEEK_RESET`. */
    FSQS_SEEK_RESET   = 3  /** See `FSQS_READ_RESET`. When done, reset CD driver and go to `FSQS_SEEK_SET_LOC`. */
};

/** @brief Post-load state.
 *
 * When `Fs_UpdateQueue` is called it will perform an action on the current post load entry, if any,
 * according to `g_FsQueue.postLoadState`, which can have one of these values.
 *
 * See `FsQueue::postLoadState`.
 */
enum FsQueuePostLoadState
{
    FSQS_POST_LOAD_INIT = 0, /** Check for allocated memory and proceed to `SKIP` or `EXEC`. */
    FSQS_POST_LOAD_SKIP = 1, /** Skip post loading because this entry owns allocated memory. */
    FSQS_POST_LOAD_EXEC = 2  /** Execute post load operation. */
};

/** @brief Post-load types.
 *
 * What to do with a queue entry after its `operation` is done. Might be better described as "file format", but
 * it only applies to two filetypes.
 *
 * See `FsQueueEntry::postLoad`.
 */
enum FsQueuePostLoadType
{
    FS_POST_LOAD_NONE = 0, /** Do nothing. */
    FS_POST_LOAD_TIM  = 1, /** Parse TIM file (`Fs_QueuePostLoadTim`). Can use `extra.image`. */
    FS_POST_LOAD_ANM  = 2  /** Parse ANM file maybe (`Fs_QueuePostLoadAnm`). Always uses `extra.anm`. */
};

/** @brief FS queue operation type.
 * What to do for a queue entry.
 * See `s_FsQueueEntry::operation`.
 */
enum FsQueueOperation
{
    FS_OP_NONE = 0, /** Uninitialized. */
    FS_OP_SEEK = 1, /** Seek to file location on CD (`Fs_UpdateQueueSeek`). */
    FS_OP_READ = 2  /** Read from CD (`Fs_UpdateQueueRead`). */
};

/**
 * @brief Extra queue entry data describing where to upload a TIM after reading.
 * See `FsQueueExtra`.
 * @note `tPage` seems to be byte swapped.
 */
typedef struct
{
    u16 tPage;
    u8  u;
    u8  v;
    s16 clutX;
    s16 clutY;
} s_FsImageDesc;

/**
 * @brief Extra queue entry data describing something related to loading some ANM files.
 * See `FsQueueExtra`.
 */
typedef struct
{
    u32 field00;
    u32 field04;
    u32 field08;
} s_FsAnmDesc;

/**
 * @brief Extra data passed with the queue entry.
 *
 * Seems to be either a TIM descriptor (`image`), or something for ANM files (`anm`).
 *
 * For `image` usage, see `Fs_QueuePostLoadTim`.
 *
 * Unknown what exactly `anm` is, but it is used with preprocess type 2, which is only used
 * for some ANM files, but not others. See `Fs_QueuePostLoadAnm`.
 */
typedef union
{
    s_FsImageDesc image; /** Location in VRAM where to upload a TIM during post-load. */
    s_FsAnmDesc   anm;   /** Unknown. Used when loading some ANM files. */
} s_FsQueueExtra;

/**
 * @brief FS queue entry.
 *
 * Entry in the FS queue.
 * Holds the state of one read/seek operation and a pointer to the `FileInfo` of the file it's for.
 */
typedef struct
{
    const s_FileInfo* info;         /** Pointer to the file table entry of the file this entry is for. */
    u8                operation;    /** What to do. See `FsQueueOperation`. */
    u8                postLoad;     /** What to do after `operation` is done. See `FsQueuePostLoadType`. */
    u8                allocate;     /** If 1, allocate a buffer for `data` from `g_FsMemory`, otherwise use `externalData` */
    u8                unused0;      /** Unused or padding. */
    void*             externalData; /** Pointer to an external buffer. */
    u32               unused1;      /** Unused but set by `Fs_EnqueueQueue`. */
    s_FsQueueExtra    extra;        /** Extra data, used during post load. */
    void*             data;         /** Output buffer. Either allocated or same as `externalData`. */
} s_FsQueueEntry;

/** Queue pointer.
 * These had to be wrapped into a struct for some code to match.
 * Used for last added element, current read/seek op and current post process op.
 */
typedef struct
{
    s32             idx; /** Index in `entries` this is pointing to. */
    s_FsQueueEntry* ptr; /** Entry in `entries` this is pointing to. */
} s_FsQueuePtr;

/**
 * @brief FS queue.
 *
 * State of the file system operations queue.
 *
 * The queue is used for async reads from the CD and from PCDRV and async seeking on the CD.
 * Each operation can optionally include a post-process (post-load) step that happens after the main operation is complete.
 * For example, parsing a TIM file after reading it.
 *
 * New entries are added by `Fs_EnqueueQueue`. The queue is processed in `Fs_UpdateQueue`.
 *
 * @note Assuming this is a single struct because there's a `bzero` that zeroes out this entire block.
 */
typedef struct
{
    s_FsQueueEntry entries[FS_QUEUE_LENGTH]; /** Circular buffer for the queue itself. */
    s_FsQueuePtr   last;                  /** Index and address of the last added entry. */
    s_FsQueuePtr   read;                  /** Index and address the current operation entry to process. */
    s_FsQueuePtr   postLoad;              /** Index and address of the current operation entry to post-process. */
    u32            state;                 /** Current processing stage. `FsQueueReadState` for reads, `FsQueueSeekState` for seeks. */
    u32            postLoadState;         /** Current postprocessing stage. See `FsQueuePostLoadState`. */
    s32            resetTimer0;           /** Reset timer (lo). Incs up to 8, then incs `reset_timer_1`. See `Fs_ResetQueueTick`. */
    s32            resetTimer1;           /** Reset timer (hi). When it reaches 9, `CdReset` is called. See `Fs_ResetQueueTick`. */
} s_FsQueue;

extern s_FsQueue g_FsQueue;

// 1

s32  Fs_IsQueueEntryLoaded(s32 queueIdx);
s32  Fs_GetQueueLength(void);
s32  Fs_DoQueueThingWhenEmpty(void);
void Fs_WaitForEmptyQueue(void);
s32  Fs_StartQueueSeek(s32 fileIdx);
s32  Fs_StartQueueRead(s32 fileIdx, void* dest);
s32  Fs_StartQueueReadTim(s32 fileIdx, void* dest, s_FsImageDesc* image);
s32  Fs_StartQueueReadAnm(s32 arg0, s32 arg1, void* arg2, s32 arg3);
s32  Fs_EnqueueQueue(s32 fileIdx, u8 op, u8 postLoad, u8 alloc, void* data, u32 unused0, s_FsQueueExtra* extra);
void Fs_InitializeQueue(void);
void Fs_ResetQueue(void);
void Fs_UpdateQueue(void);
s32  Fs_UpdateQueueSeek(s_FsQueueEntry* entry);

// 2

s32 Fs_UpdateQueueRead(s_FsQueueEntry* entry);

// 3

s32 Fs_AllocQueueEntryData(s_FsQueueEntry* entry);
s32 Fs_CanReadQueue(s_FsQueueEntry* entry);
s32 Fs_DoQueueBuffersOverlap(u8* data0, u32 size0, u8* data1, u32 size1);
s32 Fs_TickQueueSetLoc(s_FsQueueEntry* entry);
s32 Fs_TickQueueRead(s_FsQueueEntry* entry);
s32 Fs_ResetQueueTick(s_FsQueueEntry* entry);
s32 Fs_TickQueueReadPcDvr(s_FsQueueEntry* entry);
s32 Fs_UpdateQueuePostLoad(s_FsQueueEntry* entry);
s32 Fs_QueuePostLoadTim(s_FsQueueEntry* entry);
s32 Fs_QueuePostLoadAnm(s_FsQueueEntry* entry);

#endif
