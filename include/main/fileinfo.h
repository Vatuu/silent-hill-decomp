#ifndef _FILETABLE_H
#define _FILETABLE_H

#include "common.h"

#define FS_BLOCK_SIZE    0x100 /** Units in which file size is measured in file table. */
#define FS_SECTOR_SIZE   0x800 /** Size of a CD sector (2048 bytes). */
#define FS_SECTOR_SHIFT  11    /** For dividing by FS_SECTOR_SIZE. */
#define FS_NAME_CHAR_MAX 8     /** Maximum amount of characters in a file name (excluding extension and path). */
#define FS_INVALID_TYPE  0x0f  /** Unspecified file type (or empty extension). */
#define FS_FILE_COUNT    2074  /** Number of files in g_FileTable. Probably depends on version. */

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
typedef struct FileInfo
{
    u32 startSector : 19; /** Index of CD sector where file starts. */
    u32 blockCount  : 12; /** Size of file in 256-byte blocks. */
    u32 pathIdx     : 4;  /** Index of path to file in `g_FilePaths`. */
    u32 name0123    : 24; /** First four 6-bit characters of file name. */
    u32 name4567    : 24; /** Second four 6-bit characters of file name. */
    u32 type        : 4;  /** File type (and index of extension in `g_FileExts`). */
} FileInfo;

extern char* g_FilePaths[];
extern char* g_FileExts[];

extern FileInfo g_FileTable[];
extern u32      g_FileXaLoc[];

void Fs_DecryptOverlay_80010AD0(s32* dest, const s32* src, s32 size);
s32  Fs_GetFileSize_80010B24(s32 fileIdx);
void Fs_GetFileName_80010b54(char* outName, s32 fileIdx);
void Fs_GetFileInfoName_80010b88(char* outName, const FileInfo* const fileEntry);
void Fs_EncodeFileName_80010c60(s32* outName0123, s32* outName4567, const char* srcName);
s32  Fs_GetFileSectorAlignedSize_80010cd4(s32 fileIdx);
s32  Fs_FindNextFileOfType_80010d0c(s32 fileType, s32 startIdx, s32 dir);
s32  Fs_FindNextFile_80010d80(const char* name, s32 fileType, s32 startIdx);

#endif
