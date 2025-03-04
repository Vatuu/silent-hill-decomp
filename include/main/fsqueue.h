#ifndef _FSQUEUE_H
#define _FSQUEUE_H

#include "common.h"
#include "main/fileinfo.h"

 /** FS queue size. */
#define FS_QUEUE_LENGTH 32

#define FS_BUFFER0 ((void*)0x8010A600)
#define FS_BUFFER1 ((void*)0x801E2600)

/** @brief `FsQueue::state` values when processing a read operation (`Fs_QueueUpdateRead`).
 *
 * When `Fs_QueueUpdate` is called and the current op is a read, it will perform the corresponding action below.
 * Unless otherwise specified, success of that action will advance to the next state.
 *
 * `FSQS_READ_RESET` and `FSQS_READ_CHECK` perform one check/tick iteration every time `Fs_QueueUpdate` is called
 * and only advance to the next state when they're done.
 */
enum FsQueueReadState
{
    FSQS_READ_ALLOCATE = 0, /** Allocate memory for the current read operation (`fsQueueAllocData`), if needed. */
    FSQS_READ_CHECK    = 1, /** Check if the current read operation can proceed (`Fs_QueueCanRead`). Goto next state if it can. */
    FSQS_READ_SETLOC   = 2, /** Set start sector from `info` (`Fs_QueueTickSetLoc`). If failure, goto `FSQS_READ_RESET`. */
    FSQS_READ_READ     = 3, /** Read from CD (`Fs_QueueTickRead`). If failure, goto `FSQS_READ_RESET`. */
    FSQS_READ_SYNC     = 4, /** Wait for read to complete. If failure, goto `FSQS_READ_RESET`. */
    FSQS_READ_RESET    = 5  /** Tick the reset timers (`Fs_QueueResetTick`). When done, reset CD driver and goto `FSQS_READ_SETLOC`. */
};

/** @brief `FsQueue::state` values when processing a seek operation (`Fs_QueueUpdateSeek`).
 *
 * When `Fs_QueueUpdate` is called and the current op is a seek, it will perform the corresponding action below.
 * Unless otherwise specified, success of that action will advance to the next state.
 */
enum FsQueueSeekState
{
    FSQS_SEEK_SET_LOC = 0, /** Set seek sector from `info` (`Fs_QueueTickSetLoc`). */
    FSQS_SEEK_SEEKL   = 1, /** Start seeking to above location (via `CdControl(CdlSeekL, ...)`). */
    FSQS_SEEK_SYNC    = 2, /** Wait for seek to complete (`CdSync()`). If `CdlDiskError`, goto `FSQS_SEEK_RESET`. */
    FSQS_SEEK_RESET   = 3  /** See `FSQS_READ_RESET`. When done, reset CD driver and go to `FSQS_SEEK_SET_LOC`. */
};

/** @brief Post-load state.
 *
 * When `Fs_QueueUpdate` is called it will perform an action on the current post load entry, if any,
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
    FS_OP_SEEK = 1, /** Seek to file location on CD (`Fs_QueueUpdateSeek`). */
    FS_OP_READ = 2  /** Read from CD (`Fs_QueueUpdateRead`). */
};

/**
 * @brief Extra queue entry data describing where to upload a TIM after reading.
 * See `FsQueueExtra`.
 * 
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
    u32 field_00;
    u32 field_04;
    u32 field_08;
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
    u32               unused1;      /** Unused but set by `Fs_QueueEnqueue`. */
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
 * New entries are added by `Fs_QueueEnqueue`. The queue is processed in `Fs_QueueUpdate`.
 *
 * @note Assuming this is a single struct because there's a `bzero` that zeroes out this entire block.
 */
typedef struct
{
    s_FsQueueEntry entries[FS_QUEUE_LENGTH]; /** Circular buffer for the queue itself. */
    s_FsQueuePtr   last;                     /** Index and address of the last added entry. */
    s_FsQueuePtr   read;                     /** Index and address the current operation entry to process. */
    s_FsQueuePtr   postLoad;                 /** Index and address of the current operation entry to post-process. */
    u32            state;                    /** Current processing stage. `FsQueueReadState` for reads, `FsQueueSeekState` for seeks. */
    u32            postLoadState;            /** Current postprocessing stage. See `FsQueuePostLoadState`. */
    s32            resetTimer0;              /** Reset timer (lo). Incs up to 8, then incs `reset_timer_1`. See `Fs_QueueResetTick`. */
    s32            resetTimer1;              /** Reset timer (hi). When it reaches 9, `CdReset` is called. See `Fs_QueueResetTick`. */
} s_FsQueue;

/** The FS queue. See `s_FsQueue`. */
extern s_FsQueue g_FsQueue;

/** Check if queue entry index has been loaded and post-loaded.
 * 
 * @param queueIdx The index of the queue entry to check.
 * @return 1 if the entry has been fully processed, 0 otherwise.
 */
s32  Fs_QueueIsEntryLoaded(s32 queueIdx);

/** Get number of operations currently in the queue.
 * @return Number of operations in the queue. Includes both pending reads and pending post-loads.
 */
s32 Fs_QueueGetLength(void);

/** Unknown. If queue is empty, call `func_8003c850`.
 * @return 1 when queue is empty and the call suceeds, 0 otherwise.
 */
s32 Fs_QueueDoThingWhenEmpty(void);

/** Spin-waits for the queue to become empty while calling `Fs_QueueUpdate`.
 * Calls some bodyprog functions before and after the wait, `VSync` in the wait and `DrawSync` after the wait.
 */
void Fs_QueueWaitForEmpty(void);

/** Add a new seek operation to the queue.
 * @param fileIdx File table index of the file to seek to.
 * @return Index of the new queue entry.
 */
s32 Fs_QueueStartSeek(s32 fileIdx);

/** Add a new read operation to the queue.
 * 
 * @param fileIdx File table index of the file to read.
 * @param dest Destination buffer. Seems there are no size checks.
 * @return Index of the new queue entry.
 */
s32 Fs_QueueStartRead(s32 fileIdx, void* dest);

/** @brief Add a new TIM read operation to the queue.
 * Adds a read operation with `postload = FS_POST_LOAD_TIM`.
 * 
 * @param fileIdx File table index of the file to read.
 * @param dest Destination buffer. Seems there are no size checks.
 * @param image Where to upload the TIM in VRAM.
 * @return Index of the new queue entry.
 */
s32 Fs_QueueStartReadTim(s32 fileIdx, void* dest, s_FsImageDesc* image);

/** @brief Add a new ANM read operation to the queue.
 * Adds a read operation with `postLoad = FS_POST_LOAD_ANM`.
 * 
 * @note Does not actually take a file number, but instead takes one from an array of structs at 0x800a90fc in bodyprog,
 * using `arg1` as an index. Does not seem to take a `s_FsAnmDesc` pointer either. Maybe by value?
 * 
 * @param arg0
 * @param arg1 Index of something in an array in bodyprog.
 * @param arg2 Destination buffer?
 * @param arg3
 * @return Index of the new queue entry.
 */
s32 Fs_QueueStartReadAnm(s32 arg0, s32 arg1, void* arg2, s32 arg3);

/** @brief Add new operation to the queue.
 *
 * If the queue is full, will spin while calling `Fs_QueueUpdate` and wait until space frees up.
 * Called by all of the `Fs_QueueStart...` functions.
 *
 * @param fileIdx File table index of the file to load/seek.
 * @param op Operation type (`FsQueueOperation`).
 * @param postLoad Postload type (`FsQueuePostLoadType`).
 * @param alloc Whether to allocate owned memory for this operation (`s_FsQueueEntry::allocate`).
 * @param unused1 Value for `s_FsQueueEntry::unused1`. Seems to be unused.
 * @param extra Extra data for operation (`s_FsQueueEntry::extra`).
 * @return Index of the new queue entry.
 */
s32 Fs_QueueEnqueue(s32 fileIdx, u8 op, u8 postLoad, u8 alloc, void* data, u32 unused0, s_FsQueueExtra* extra);

/** @brief Initialize FS queue and FS memory.
 * Initializes `g_FsQueue` and calls `Fs_InitializeMem`.
 */
void Fs_QueueInitialize(void);

/** Seems to clear the queue. */
void Fs_QueueReset(void);

/** @brief Ticks the FS queue once.
 *
 * Depending on current read entry's operation type, either ticks reading it (`Fs_QueueUpdateRead`) or seeking it (`Fs_QueueUpdateSeek`).
 * If they return 1, advances `g_FsQueue.read.idx` and `g_FsQueue.read.ptr`.
 *
 * Regardless of the outcome of the above, also ticks postloading (`Fs_QueueUpdatePostLoad`) if there is an entry to postload.
 * If that reports that the current postload entry is done postloading, advances `g_FsQueue.postLoad.idx` and `g_FsQueue.postLoad.ptr`.
 */
void Fs_QueueUpdate(void);

/** @brief Ticks a seek operation once.
 *
 * Performs one step in the seeking process according to `g_FsQueue.state`. When the whole process is done, returns 1.
 *
 * @param entry Entry to tick.
 * @return 1 when `entry` is done seeking, 0 otherwise.
 */
s32 Fs_QueueUpdateSeek(s_FsQueueEntry* entry);

/** @brief Ticks a read operation once.
 *
 * Performs one step in the reading process according to `g_FsQueue.state`. When the whole process is done, it returns 1.
 *
 * @param entry Entry to tick.
 * @return 1 when `entry` is done loading, 0 otherwise.
 */
s32 Fs_QueueUpdateRead(s_FsQueueEntry* entry);

/** If `entry->allocate` is set, allocate memory for `entry->data`, otherwise use `entry->externalData`.
 * 
 * @param entry Entry to allocate memory for.
 * @return 1 if allocation was successful or was not needed, 0 otherwise.
 */
s32 Fs_QueueAllocEntryData(s_FsQueueEntry* entry);

/** @brief Check if the specified read operation entry can be processed.
 *
 * Checks if loading `entry` will clobber any memory that was allocated for pending entries in the queue,
 * or memory that's used for post-loading.
 *
 * @param entry Entry to check against.
 * @return 1 if the entry can be loaded without clobbering anything, 0 otherwise.
 */
s32 Fs_QueueCanRead(s_FsQueueEntry* entry);

/** @brief Check if two buffers overlap in memory. Used by `Fs_QueueCanRead`.
 * 
 * @param data0 Start of the first buffer.
 * @param size0 Size of the first buffer in bytes.
 * @param data1 Start of the second buffer.
 * @param size1 Size of the second buffer in bytes.
 * @return 1 if buffers overlap, 0 otherwise.
 */
s32 Fs_QueueDoBuffersOverlap(u8* data0, u32 size0, u8* data1, u32 size1);

/** @brief Process `FSQS_READ_SETLOC` or `FSQS_SEEK_SETLOC` state: set target sector.
 *
 * Calls `CdControl(CdlSetloc, ...)`.
 *
 * @param entry Entry to process.
 * @return 1 if succeded, 0 if `CdControl` failed.
 */
s32 Fs_QueueTickSetLoc(s_FsQueueEntry* entry);

/** @brief Process `FSQS_READ_READ` state: read from CD.
 *
 * Calls `CdRead()`.
 *
 * @param entry Entry to process.
 * @return 1 if succeded, 0 if `CdControl` failed.
 */
s32 Fs_QueueTickRead(s_FsQueueEntry* entry);

/** @brief Process `FSQS_READ_RESET` or `FSQS_SEEK_RESET` state: wait for a bit and reset CD driver.
 *
 * Increments `g_FsQueue.resetTimer0` once. If it has reached 8, clears it and increments `g_FsQueue.resetTimer1`.
 * If `g_FsQueue.resetTimer1` has reached 9, clears it and calls `CdReset()`.
 *
 * @param entry Entry to process.
 * @return 1 if succeded, 0 if `CdControl` failed.
 */
s32 Fs_QueueResetTick(s_FsQueueEntry* entry);

/** Process a read from PCDRV. Seems to be unused in release.
 * @param entry PCDRV read operation entry to process.
 * @return 1 if succeeded, 0 otherwise.
 */
s32 Fs_QueueTickReadPcDvr(s_FsQueueEntry* entry);

/** @brief Ticks postloading once.
 *
 * Performs one step in the post-loading process according to `entry->postLoadState`. When the whole process is done, returns 1.
 *
 * @param entry Entry to tick.
 * @return 1 when `entry` is done postloading, 0 otherwise.
 */
s32 Fs_QueueUpdatePostLoad(s_FsQueueEntry* entry);

/** @brief Parse a TIM file after loading it.
 *
 * Called during post-loading for TIM files (`entry->postLoad = 1`).
 * Will use `OpenTIM`/`ReadTIM` to parse the loaded data and then upload it via `LoadImage`.
 * If `entry->extra.image.u` is not 0xFF, will override the XY components of the pixel and CLUT rects with values from `image`.
 *
 * @param entry Entry to parse.
 * @return Always 1.
 */
s32 Fs_QueuePostLoadTim(s_FsQueueEntry* entry);

/** @brief Parse an ANM file after loading it?
 *
 * Called during post-loading for some ANM files (when `entry->postLoad = 2`).
 * For example, it is called for CLD2.ANM, SRL.ANM, SBL.ANM (maybe ones used for NPCs?), but not for others
 * (e.g. HB_M0S01.ANM).
 *
 * Calls into BODYPROG, where a function gets a `GsCOORDINATE2` from somewhere in the loaded data.
 * Always uses data from `entry->extra.anm`.
 *
 * @param entry Entry to parse.
 * @return Always 1.
 */
s32 Fs_QueuePostLoadAnm(s_FsQueueEntry* entry);

#endif
