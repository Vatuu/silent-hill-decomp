#ifndef FILE_ENTRIES_H
#define FILE_ENTRIES_H

#include "common.h"

#define FILE_ENTRY_BLOCK_SIZE 0x100
#define FILE_ENTRY_ALIGNMENT_SIZE 0x800

/**
 * @brief Array of folders.
 * 
 * This array, `g_FilePaths`, contains a list of (11) pointers to folder names.
 * The folder names are like "\XA\", "\VIN\", etc.
 */
extern char *const g_FilePaths[];

/**
 * @brief Array of file types.
 * 
 * This array, `g_FileExts`, contains a list of (12) pointers to file types.
 * The file types are like ".CMP", ".DAT", etc.
 */
extern char *const g_FileExts[];

/**
 * @brief Represents an entry in the file entries table.
 *
 * This struct contains encoded file names and locations of entries.
 * The file names are uppercase letters with a maximum length of 8.
 * They are encoded into 2 parts of 24-bit values. The encoding is done
 * by subtracting 0x20 from each character, which limits values to 6-bit
 * (as the maximum 6-bit value is 0x3F which is larger than 'Z' (0x5A) - 0x20),
 * and then OR'ing the results shifted left by 6.
 */
typedef struct FileEntry {
  u32 addr : 19;        // Address of the file entry
  u32 blocks_num : 12;  // Size of the file in 256-byte block chunks
  u8  dir_id : 4;       // Directory ID
  u32 part1 : 24;       // Encoded file name, part 1
  u32 part2 : 24;       // Encoded file name, part 2
  u8  file_type_id : 4; // File type ID
} FileEntry;

/**
 * @brief Array of file entries.
 *
 * This array holds information about (assumingly) every file in .SILENT and
 * .HILL files.
 */
extern FileEntry g_FileTable[];

/**
 * @brief Decrypts an encrypted overlay.
 *
 * This function takes an encrypted overlay and decrypts it, storing the result
 * in the provided result buffer. The decryption process is applied to the
 * specified number of bytes.
 *
 * @param ovl_result Pointer to the buffer where the decrypted overlay will be
 * stored.
 * @param encrypted_ovl Pointer to the buffer containing the encrypted overlay
 * data.
 * @param size The number of bytes to decrypt.
 */
void fsDecryptOverlay(s32 *ovl_result, const s32 *encrypted_ovl, s32 size);

/**
 * @brief Gets the size of a file entry in bytes.
 *
 * This function takes an index, looks up the corresponding file entry in
 * the global `g_FileTable` array, and returns the size of that file
 * entry in bytes.
 *
 * @param entry_idx The index of the file entry to look up.
 * @return The size of the specified file entry in bytes.
 */
s32 fsFileGetSize(s32 entry_idx);

/**
 * @brief Extracts the file name from a file entry at a given offset.
 *
 * This function decodes the file name from the file entry located at the
 * specified offset in the global `g_FileTable` array. The decoded name is
 * stored in the provided output buffer.
 *
 * @param[out] out_name Buffer where the decoded file name will be stored.
 * @param[in] offset The offset from the start of the `g_FileTable` array to
 * the target entry.
 */
void fsFileGetFullName(char *out_name, s32 offset);

/**
 * @brief Decodes the file name from a file entry.
 *
 * This function takes a pointer to a `FileEntry` and decodes the file name
 * from the `part1` and `part2` fields, storing the result in the provided
 * output buffer.
 *
 * @param[out] out_name Buffer where the decoded file name will be stored.
 * @param[in] file_entry Pointer to the file entry from which to decode the
 * name.
 */
void fsFileEntryGetFullName(char *out_name, const FileEntry *const file_entry);

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
 * @brief Encodes a file name into FileEntry record parts.
 *
 * This function takes a file name string and encodes it into two integers,
 * `part1` and `part2`, according to the encoding scheme described in the
 * `FileEntry` struct. The encoded values are stored in the provided output
 * parameters.
 *
 * @param[out] out_part1 Pointer to the integer where the first part of the
 * encoded name will be stored.
 * @param[out] out_part2 Pointer to the integer where the second part of the
 * encoded name will be stored.
 * @param[in] name The file name string to encode.
 */
void fsEncodeFileName(s32 *out_part1, s32 *out_part2, const char *name);

/**
 * @brief Calculates the size of a file entry aligned to 2MB blocks.
 *
 * This function takes an index, looks up the corresponding file entry in
 * the global `g_FileTable` array, and calculates the size of that file
 * entry, aligning the result to 0x800-byte (2MB) blocks.
 *
 * @param entry_idx The index of the file entry to look up.
 * @return The size of the specified file entry aligned to 0x800-byte (2MB)
 * blocks.
 */
s32 fsFileGetSizeInSectors(s32 entry_idx);

/**
 * @brief Finds the offset to a first file entry with a matching file type ID.
 *
 * This function searches for the first file entry in the global `g_FileTable`
 * array that matches the specified `file_type_id`. The search starts from the
 * `start_offset` and proceeds either incrementally or decrementally based on
 * the `direction` parameter.
 *
 * @param file_type_id The file type ID to search for.
 * @param start_offset The offset from which to start the search.
 * @param direction The direction of the search: positive for incrementing,
 * negative for decrementing.
 * @return The offset of the first matching file entry, or -1 if not found.
 */
u32 fsFileFindNextOfType(s32 file_type_id, s32 start_offset, s32 direction);

/**
 * @brief Searches for a file entry by name and file type ID.
 *
 * This function searches for a file entry in the global `g_FileTable` array
 * that matches the specified file name and file type ID, starting from the
 * given offset. The search returns the index of the matching entry, or -1 if
 * not found.
 *
 * @param name The file name to search for.
 * @param file_type_id The file type ID to match.
 * @param start_offset The offset from which to start the search.
 * @return The index of the matching file entry, or -1 if not found.
 */
s32 fsFileFindNext(const char *name, s32 file_type_id, s32 start_offset);

#endif
