#ifndef _FILETABLE_H
#define _FILETABLE_H

#include "common.h"

#define FS_BLOCK_SIZE 0x100  /** Units in which file size is measured in the file table */
#define FS_SECTOR_SIZE 0x800 /** Size of a CD sector (2048 bytes) */
#define FS_SECTOR_SHIFT 11   /** For dividing by FS_SECTOR_SIZE */
#define FS_MAX_NAME 8        /** Maximum amount of characters in a file name (without extension or path) */
#define FS_INVALID_TYPE 0x0f /** Unspecified file type (or empty extension) */
#define FS_NUM_FILES 2074    /** Number of files in g_FileTable. Probably depends on version. */

/**
 * @brief Entry in the file table.
 *
 * Contains the metadata of a single file in file table (`g_FileTable`):
 * its name, size and location on the CD.
 *
 * The file name is stored as 8 6-bit characters represented as two 24-bit bitfields:
 * `name0123` and `name4567`. The 6-bit character value maps to ASCII character range `0x20` ... `0x5f`.
 * The name does not contain the path or extension.
 *
 * The path and extension are stored as 4-bit indices of the path string in `g_FilePaths` and of
 * the extension string in `g_FileExts`, respectively. This limits the amount of paths and extensions
 * to 16 each, with one representing an empty extension.
 */
typedef struct FileInfo {
  u32 startsector : 19; /** Number of the CD sector where the file starts */
  u32 numblocks : 12;   /** Size of file in 256-byte blocks */
  u32 pathnum : 4;      /** Index of path to file in `g_FilePaths` */
  u32 name0123 : 24;    /** First four 6-bit characters of the file name */
  u32 name4567 : 24;    /** Second four 6-bit characters of the file name */
  u32 type : 4;         /** File type (and index of extension in `g_FileExts`) */
} FileInfo;

/**
 * @brief Array of file path strings.
 *
 * All possible path strings occuring in the data archives.
 * This is referenced by index (`pathnum`) in each file table entry.
 *
 * In SLUS_007.07 there are 11 possible paths. They are all one subfolder deep
 * and have starting and trailing path separators (backslashes).
 *
 * @note Not `const char *` because it has to end up in .data/.sdata. Was also `char *` in the header
 * found in one of the prototypes.
 */
extern char *g_FilePaths[];

/**
 * @brief Array of file extension strings.
 *
 * All possible file extensions occuring in the data archives.
 * This is referenced by index (`type`) in each file table entry.
 *
 * In SLUS_007.07 there are 12 possible extensions. They all have a starting dot
 * and are 3 characters long (`.XXX`).
 *
 * @note Not `const char *` because it has to end up in .data/.sdata. Was also `char *` in the header
 * found in one of the prototypes.
 */
extern char *g_FileExts[];

/**
 * @brief File information table.
 *
 * The file table is the index to the game's two data archives:
 * the files `SILENT` and `HILL` on the CD. It contains metadata of every file
 * in those archives, such as the name, size, file type and where the file is on the CD.
 *
 * @note Not `const` because it has to end up in .data. Was also like that in the header
 * found in one of the prototypes.
 */
extern FileInfo g_FileTable[];

/**
 * Array of starting sector numbers for the first 9 \XA\ files in the file table (2044 - 2052).
 * These files seem to contain dialog and music. Array starts and ends with 0s.
 */
extern u32 g_FileXaLoc[];

/**
 * @brief Decrypts an encrypted overlay.
 *
 * The overlays in the `1ST` folder in the data archives are encrypted.
 * Overlays in the `VIN` folder don't appear to be, though.
 * This function decrypts data dword-by-dword, so `size` presumably must be
 * divible by 4 for it to work properly.
 *
 * @param dst Destination buffer. Must be `size` long.
 * @param src Encrypted overlay data.
 * @param size The number of bytes to decrypt.
 */
void fsDecryptOverlay(s32 *dst, const s32 *src, s32 size);

/**
 * @brief Gets the size of a file in the file table.
 *
 * Takes a file table entry index (`filenum`) and returns the size of that file, obtained from
 * its file table entry.
 *
 * @param filenum The index of the file entry to look up.
 * @return The size of the specified file entry in bytes.
 */
s32 fsFileGetSize(s32 filenum);

/**
 * @brief Gets the full name of a file in the file table.
 *
 * Takes a file table entry index (`filenum`) and returns the name of that file (with extension)
 * into `outname`.
 * The name is decoded from its file table representation into proper ASCII and is null terminated.
 *
 * @note `outname` must be at least 13 bytes long to fit the longest possible name in 8.3 format.
 * There are no size checks.
 *
 * @param[out] outname Buffer where the decoded file name will be stored.
 * @param[in] filenum Index of the file in the file table.
 */
void fsFileGetName(char *outname, s32 filenum);

/**
 * @brief Gets the name from a file table entry.
 *
 * Returns the name (with extension) in the file table entry `fentry`.
 * The name is decoded from its file table representation into proper ASCII and is null terminated.
 *
 * @note `outname` must be at least 13 bytes long to fit the longest possible name in 8.3 format.
 * There are no size checks.
 *
 * @param[out] outname Buffer where the decoded file name will be stored.
 * @param[in] fentry Pointer to the file table entry from which to decode the name.
 */
void fsFileInfoGetName(char *outname, const FileInfo *const fentry);

/* Example of the file name encoding:
 *   For string like 'HERO':
 *   i0: 'H' - 0x20 << 0  = 0x28      (0000 0000 0000 0000 0010 1000)
 *       -> 0x28 | 0x0     = 0x28     (0000 0000 0000 0000 0010 1000)
 *   i1: 'E' - 0x20 << 6  = 0x940   (0000 0000 0000 1001 0100 0000)
 *       -> 0x28 | 0x940   = 0x968    (0000 0000 0000 1001 0110 1000)
 *   i2: 'R' - 0x20 << 12 = 0x32000     (0000 0011 0010 0000 0000 0000)
 *       -> 0x968 | 0x32000 = 0x32968  (0000 0011 0010 1001 0110 1000)
 *   i3: 'O' - 0x20 << 18 = 0xBC0000    (1011 1100 0000 0000 0000 0000)
 *       -> 0x32968 | 0xBC0000 = 0xBF2968 (1011 1111 0010 1001 0110 1000)
 */

/**
 * @brief Encodes a file name into 6-bit file table representation.
 *
 * Takes an ASCII file name and encodes it into the 6 bits per character format
 * used by the file table.
 * The name is stored in two 32-bit integers pointed to by `outname0123` and `outname4567`,
 * corresponding to the `FileInfo` fields of the same name.
 *
 * @param[out] outname0123 Pointer to the integer where the first part of the
 * encoded name will be stored.
 * @param[out] outname4567 Pointer to the integer where the second part of the
 * encoded name will be stored.
 * @param[in] srcname The file name string to encode.
 */
void fsEncodeFileName(s32 *outname0123, s32 *outname4567, const char *srcname);

/**
 * @brief Gets the size of a file rounded up to CD sector size.
 *
 * Takes an index in the file table and returns that file's size in bytes, rounded up to
 * CD sector size (2048 bytes).
 *
 * @param filenum The index of the file entry to look up.
 * @return The size of the specified file entry in bytes rounded up to CD sector boundary.
 */
s32 fsFileGetSectorAlignedSize(s32 filenum);

/**
 * @brief Finds a file of the specified type in the file table.
 *
 * Starts a linear search from the file table index `startnum`,
 * going forwards if `direction` is positive, or backwards if it is negative.
 * Returns the index of the first file it encounters whose `type` field is `ftype`,
 * or -1 if it reaches the end of the table without finding anything.
 *
 * @param ftype The file type to search for.
 * @param startnum The table index from which to start the search.
 * @param direction The direction of the search: positive for incrementing,
 * negative for decrementing.
 * @return The index of the first matching file entry, or -1 if not found.
 */
s32 fsFileFindNextOfType(s32 ftype, s32 startnum, s32 direction);

/**
 * @brief Finds a file with the specified name and type in the file table.
 *
 * Starts a linear search from the file table index `startnum` going forwards.
 * Returns the index of the first file it encounters whose `type` field is `ftype`
 * and whose name is the same as `name`, or -1 if it reaches the end of the table
 * without finding anything.
 *
 * @param name The file name to search for.
 * @param ftype The file type ID to match.
 * @param startnum The offset from which to start the search.
 * @return The index of the matching file entry, or -1 if not found.
 */
s32 fsFileFindNext(const char *name, s32 ftype, s32 startnum);

#endif
