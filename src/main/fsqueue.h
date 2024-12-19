#ifndef _FSQUEUE_H
#define _FSQUEUE_H

#include "common.h"
#include "filetable.h"

#define FS_QUEUE_LEN 32 /** FS queue size. */

/**
 * @brief Extra queue entry data describing where to upload a TIM after reading.
 * See `FsQueueExtra`.
 */
typedef struct {
  u16 tpage;
  u8 u;
  u8 v;
  s16 clut_x;
  s16 clut_y;
} FsImageDesc;

/**
 * @brief Extra queue entry data describing something libgs-related.
 * See `FsQueueExtra`.
 */
typedef struct {
  u16 field_00;
  u16 field_02;
  u16 field_04;
  u16 field_06;
  u16 field_08;
  u16 field_0a;
} FsGsThingDesc;

/**
 * @brief Extra data passed with the queue entry.
 *
 * Seems to be either a TIM descriptor (`image`), or something libgs-related (`gs_thing`).
 * Not quite sure what `gs_thing` is, but it is processed in BODYPROG and the function that
 * does it uses a `GsCOORDINATE2`, so I'm assuming it's libgs-related.
 */
typedef union {
  FsImageDesc image;      /** Location in VRAM where to upload a TIM during postload. */
  FsGsThingDesc gs_thing; /** Unknown, but libgs-related. */
} FsQueueExtra;

/**
 * @brief FS queue entry.
 *
 * Entry in the FS queue.
 * Holds the state of one read/seek operation and a pointer to the `FileEntry` of the file it's for.
 */
typedef struct {
  const FileEntry *info; /** Pointer to the file table entry of the file this entry is for. */
  u8 operation;          /** What to do. See `FsQueueOperation`. */
  u8 postload;           /** What to do after `operation` is done. See `FsQueuePostLoadType`. */
  u8 allocate;           /** If 1, allocate a buffer for `data` from `g_FsMem`, otherwise use `external_data` */
  u8 unused_0;           /** Unused or padding. */
  void *external_data;   /** Pointer to an external buffer. */
  u32 unused_1;          /** Unused but set by `fsQueueEnqueue`. */
  FsQueueExtra extra;    /** Extra data, used during postload. */
  void *data;            /** Output buffer. Either allocated or same as `external_data`. */
} FsQueueEntry;

/**
 * @brief FS queue.
 *
 * State of the file system operations queue.
 *
 * The queue is used for async reads from the CD and from PCDRV and async seeking on the CD.
 * Each operation can optionally include a postprocess (postload) step that happens after the main operation is complete.
 * For example, parsing a TIM file after reading it.
 *
 * New entries are added by `fsQueueEnqueue`. The queue is processed in `fsQueueUpdate`.
 */
typedef struct {
  FsQueueEntry entries[FS_QUEUE_LEN]; /** Circular buffer for the queue itself. */
  s32 last_idx;                       /** Index of the last added entry. */
  FsQueueEntry *last_ptr;             /** Pointer to the last added entry. */
  s32 read_idx;                       /** Index of the current operation entry to process. */
  FsQueueEntry *read_ptr;             /** Pointer to the current operation entry to process. */
  s32 postload_idx;                   /** Index of the current operation entry to postprocess. */
  FsQueueEntry *postload_ptr;         /** Pointer to the current operation entry to postprocess.  */
  u32 state;                          /** Current processing stage. `FsQueueReadState` for reads, `FsQueueSeekState` for seeks. */
  u32 postload_state;                 /** Current postprocessing stage. See `FsQueuePostLoadState`. */
  s32 reset_timer_0;                  /** Reset timer (lo). Incs up to 8, then incs `reset_timer_1`. See `fsQueueTickReset`. */
  s32 reset_timer_1;                  /** Reset timer (hi). When it reaches 9, `CdReset` is called. See `fsQueueTickReset`. */
} FsQueue;

/** @brief `FsQueue::state` values when processing a read operation (`fsQueueUpdateRead`).
 *
 * When `fsQueueUpdate` is called and the current op is a read, it will perform the corresponding action below.
 * Unless otherwise specified, success of that action will advance to the next state.
 *
 * `FSQS_READ_RESET` and `FSQS_READ_CHECK` perform one check/tick iteration every time `fsQueueUpdate` is called
 * and only advance to the next state when they're done.
 */
enum FsQueueReadState {
  FSQS_READ_ALLOCATE = 0, /** Allocate memory for the current read operation (`fsQueueAllocData`), if needed. */
  FSQS_READ_CHECK = 1,    /** Check if the current read operation can proceed (`fsQueueCanRead`). Goto next state if it can. */
  FSQS_READ_SETLOC = 2,   /** Set start sector from `info` (`fsQueueTickSetLoc`). If failure, goto `FSQS_READ_RESET`. */
  FSQS_READ_READ = 3,     /** Read from CD (`fsQueueTickRead`). If failure, goto `FSQS_READ_RESET`. */
  FSQS_READ_SYNC = 4,     /** Wait for read to complete. If failure, goto `FSQS_READ_RESET`. */
  FSQS_READ_RESET = 5     /** Tick the reset timers (`fsQueueTickReset`). When done, reset CD driver and goto `FSQS_READ_SETLOC`. */
};

/** @brief `FsQueue::state` values when processing a seek operation (`fsQueueUpdateSeek`).
 *
 * When `fsQueueUpdate` is called and the current op is a seek, it will perform the corresponding action below.
 * Unless otherwise specified, success of that action will advance to the next state.
 */
enum FsQueueSeekState {
  FSQS_SEEK_SETLOC = 0, /** Set seek sector from `info` (`fsQueueTickSetLoc`). */
  FSQS_SEEK_SEEKL = 1,  /** Start seeking to above location (via `CdControl(CdlSeekL, ...)`). */
  FSQS_SEEK_SYNC = 2,   /** Wait for seek to complete (`CdSync()`). If `CdlDiskError`, goto `FSQS_SEEK_RESET`. */
  FSQS_SEEK_RESET = 3   /** See `FSQS_READ_RESET`. When done, reset CD driver and goto `FSQS_SEEK_SETLOC`. */
};

/** @brief Postload types.
 *
 * What to do with a queue entry after its `operation` is done. Might be better described as "file format", but
 * it only applies to two filetypes.
 *
 * See `FsQueueEntry::postload`.
 */
enum FsQueuePostLoadType {
  FS_POSTLOAD_NONE = 0,   /** Do nothing. */
  FS_POSTLOAD_TIM = 1,    /** Parse TIM file (`fsQueuePostLoadTim`). Can use `extra.image`. */
  FS_POSTLOAD_GSTHING = 2 /** Parse some libgs-related file (`fsQueuePostLoadGsThing`). Uses `extra.gs_thing`. */
};

/** @brief FS queue operation type.
 * What to do for a queue entry.
 * See `FsQueueEntry::operation`.
 */
enum FsQueueOperation {
  FS_OP_NONE = 0, /** Uninitialized. */
  FS_OP_READ = 1, /** Read from CD (`fsQueueUpdateRead`). */
  FS_OP_SEEK = 2  /** Seek to file location on CD (`fsQueueUpdateSeek`). */
};

/** The FS queue. See `FsQueue`. */
extern FsQueue g_FsQueue;

/** Unknown. Set in `fsQueueDoThingWhenEmpty`. */
extern s32 D_800C489C;

/** Unknown. In BODYPROG. Called by `fsQueueDoThingWhenEmpty`. */
s32 func_8003c850();

/** @brief Initialize FS queue and FS memory.
 * Initializes `g_FsQueue` and calls `fsMemInit`.
 */
void fsQueueInit(void);

/** Check if queue entry index `arg0` has been loaded and postloaded.
 * @param arg0 The index of the queue entry to check.
 * @return 1 if the entry has been fully processed, 0 otherwise.
 */
s32 fsQueueIsEntryLoaded(s32 arg0);

/** Get number of operations currently in queue.
 * @return Number of operations in queue. Includes both pending reads and pending postloads.
 */
s32 fsQueueGetLength(void);

/** Unknown. If queue is empty, call `func_8003c850`.
 * @return 1 when queue is empty and the call suceeds, 0 otherwise.
 */
s32 fsQueueDoThingWhenEmpty(void);

/** If `entry->allocate` is set, allocate memory for `entry->data`, otherwise use `entry->external_data`.
 * @param entry Entry to allocate memory for.
 * @return 1 if allocation was successful or was not needed, 0 otherwise.
 */
s32 fsQueueAllocEntryData(FsQueueEntry *entry);

/** @brief Add new operation to the queue.
 *
 * If the queue is full, will spin while calling `fsQueueUpdate` and wait until space frees up.
 * Called by all of the `fsQueueStart*` functions.
 *
 * @param fileno File table index of the file to load/seek.
 * @param op Operation type (`FsQueueOperation`).
 * @param postload Postload type (`FsQueuePostLoadType`).
 * @param alloc Whether to allocate owned memory for this operation (`FsQueueEntry::allocate`).
 * @param unused_1 Value for `FsQueueEntry::unused1`. Seems to be unused.
 * @param extra Extra data for operation (`FsQueueEntry::extra`).
 * @return Index of the new queue entry.
 */
s32 fsQueueEnqueue(s32 fileno, u8 op, u8 postload, u8 alloc, void *data, u32 unused_1, FsQueueExtra *extra);

/** Add a new read operation to the queue.
 * @param fileno File table index of the file to read.
 * @param dst Destination buffer. Seems there are no size checks.
 * @return Index of the new queue entry.
 */
s32 fsQueueStartRead(s32 fileno, void *dst);

/** @brief Add a new TIM read operation to the queue.
 * Adds a read operation with `postload = FS_POSTLOAD_TIM`.
 * @param fileno File table index of the file to read.
 * @param dst Destination buffer. Seems there are no size checks.
 * @param image Where to upload the TIM in VRAM.
 * @return Index of the new queue entry.
 */
s32 fsQueueStartReadTim(s32 fileno, void *dst, FsImageDesc *image);

/** @brief Add a new libgs thing read operation to the queue.
 * Adds a read operation with `postload = FS_POSTLOAD_GSTHING`.
 * @note Does not actually take a file number, but instead takes one from an array of structs at 0x800a90fc in bodyprog,
 * using `arg1` as an index. Does not seem to take a `FsGsThingDesc` pointer either. Maybe by value?
 * @param arg0
 * @param arg1 Index of something in an array in bodyprog.
 * @param arg2 Destination buffer?
 * @param arg3
 * @return Index of the new queue entry.
 */
s32 fsQueueStartReadGsThing(s32 arg0, s32 arg1, void *arg2, s32 arg3);

/** Add a new seek operation to the queue.
 * @param fileno File table index of the file to seek to.
 * @return Index of the new queue entry.
 */
s32 fsQueueStartSeek(s32 fileno);

/** Process a read from PCDRV. Seems to be unused in release.
 * @param entry PCDRV read operation entry to process.
 * @return 1 if succeeded, 0 otherwise.
 */
s32 fsQueueTickReadPcDrv(FsQueueEntry *entry);

/** @brief Process `FSQS_READ_SETLOC` or `FSQS_SEEK_SETLOC` state: set target sector.
 *
 * Calls `CdControl(CdlSetloc, ...)`.
 *
 * @param entry Entry to process.
 * @return 1 if succeded, 0 if `CdControl` failed.
 */
s32 fsQueueTickSetLoc(FsQueueEntry *entry);

/** @brief Process `FSQS_READ_READ` state: read from CD.
 *
 * Calls `CdRead()`.
 *
 * @param entry Entry to process.
 * @return 1 if succeded, 0 if `CdControl` failed.
 */
s32 fsQueueTickRead(FsQueueEntry *entry);

/** @brief Process `FSQS_READ_RESET` or `FSQS_SEEK_RESET` state: wait for a bit and reset CD driver.
 *
 * Increments `g_FsQueue.reset_timer_0` once. If it has reached 8, clears it and increments `g_FsQueue.reset_timer_1`.
 * If `g_FsQueue.reset_timer_1` has reached 9, clears it and calls `CdReset()`.
 *
 * @param entry Entry to process.
 * @return 1 if succeded, 0 if `CdControl` failed.
 */
s32 fsQueueTickReset(FsQueueEntry *entry);

/** @brief Ticks the FS queue once.
 *
 * Depending on current read entry's operation type, either ticks reading it (`fsQueueUpdateRead`) or seeking it (`fsQueueUpdateSeek`).
 * If they return 1, advances `g_FsQueue.read_idx` and `g_FsQueue.read_ptr`.
 *
 * Regardless of the outcome of the above, also ticks postloading (`fsQueueUpdatePostLoad`) if there is an entry to postload.
 * If that reports that the current postload entry is done postloading, advances `g_FsQueue.postload_idx` and `g_FsQueue.postload_ptr`.
 */
void fsQueueUpdate(void);

/** @brief Ticks a read operation once.
 *
 * Performs one step in the reading process according to `g_FsQueue.state`. When the whole process is done, returns 1.
 *
 * @param entry Entry to tick.
 * @return 1 when `entry` is done loading, 0 otherwise.
 */
s32 fsQueueUpdateRead(FsQueueEntry *entry);

/** @brief Ticks a seek operation once.
 *
 * Performs one step in the seeking process according to `g_FsQueue.state`. When the whole process is done, returns 1.
 *
 * @param entry Entry to tick.
 * @return 1 when `entry` is done seeking, 0 otherwise.
 */
s32 fsQueueUpdateSeek(FsQueueEntry *entry);

/** @brief Ticks postloading once.
 *
 * Performs one step in the postloading process according to `entry->postload_state`. When the whole process is done, returns 1.
 *
 * @param entry Entry to tick.
 * @return 1 when `entry` is done postloading, 0 otherwise.
 */
s32 fsQueueUpdatePostLoad(FsQueueEntry *entry);

/** @brief Parse a TIM file after loading it.
 *
 * Called during postloading for TIM files (`entry->postload = 1`).
 * Will use `OpenTIM`/`ReadTIM` to parse the loaded data and then upload it via `LoadImage`.
 * If `entry->extra.image.u` is not 0xFF, will override the XY components of the pixel and CLUT rects with values from `image`.
 *
 * @param entry Entry to parse.
 * @return Always 1.
 */
s32 fsQueuePostLoadTim(FsQueueEntry *entry);

/** @brief Parse something libgs-related after loading it.
 *
 * Called during postloading for an unknown file type (`entry->postload = 2`).
 * Calls into BODYPROG, where a function gets a `GsCOORDINATE2` from somewhere in the loaded data.
 * Always uses data from `entry->extra.gs_thing`.
 *
 * @param entry Entry to parse.
 * @return Always 1.
 */
s32 fsQueuePostLoadGsThing(FsQueueEntry *entry);

/** @brief Check if specified read operation entry can be processed.
 *
 * Checks if loading `entry` will clobber any allocated memory used by any currently postloading operations.
 * Does not care about entries without allocated data.
 *
 * @param entry Entry to check against.
 * @return 1 if the entry can be loaded without clobbering anything, 0 otherwise.
 */
s32 fsQueueCanRead(FsQueueEntry *entry);

/** Seems to clear the queue. */
void fsQueueReset(void);

/** Spin-waits for the queue to become empty while calling `fsQueueUpdate`.
 * Calls some bodyprog functions before and after the wait, `VSync` in the wait and `DrawSync` after the wait.
 */
void fsQueueWaitForEmpty(void);

/** @brief Check if two buffers overlap in memory.
 * Used by `fsQueueCanRead`.
 * @param data1 Start of the first buffer.
 * @param size1 Size of the first buffer in bytes.
 * @param data2 Start of the second buffer.
 * @param size2 Size of the second buffer in bytes.
 * @return 1 if buffers overlap, 0 otherwise.
 */
s32 fsQueueDoBuffersOverlap(u8 *data1, u32 size1, u8 *data2, u32 size2);

#endif
