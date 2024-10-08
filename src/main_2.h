#ifndef MAIN_2_H
#define MAIN_2_H

#include "common.h"
#include "game.h"
#include "files.h"

#define FILE_ENTRY_BLOCK_SIZE 0x100
#define FILE_ENTRY_ALIGNMENT_SIZE 0x800

/* File entries table
   Contains encoded file names and locations(?) of entries
   The file names are uppercase letters with max length of 8
   They are encoded into 2 parts of 24 bits values,
   The encoding is done by subtracting 0x20 from each character,
   (which limits values to 6 bit,
    as max 6 bit value is 0x3F (0011 1111) + 0x20 = 1011 1111 (0x5F),
    while 'Z' = 0x5A)

   and then OR'ing the results shifted left by 6

Example for 'HERO':
  i0 'H' - 0x20 << 0      = 0x28  	  (0000 0000 0000 0000 0010 1000)
    -> 0x28 | 0x0         = 0x28  	  (0000 0000 0000 0000 0010 1000)

  i1 'E' - 0x20 << 6      = 0x940  		(0000 0000 0000 1001 0100 0000)
    -> 0x28 | 0x940       = 0x968 	  (0000 0000 0000 1001 0110 1000)

  i2 'R' - 0x20 << 12     = 0x32000 	(0000 0011 0010 0000 0000 0000)
    -> 0x968 | 0x32000    = 0x32968   (0000 0011 0010 1001 0110 1000)

  i3 'O' - 0x20 << 18     = 0xBC0000	(1011 1100 0000 0000 0000 0000)
    -> 0x32968 | 0xBC0000 = 0xBF2968	(1011 1111 0010 1001 0110 1000)
*/
typedef struct {
  u32 addr : 19;
  u32 blocks_num : 12; // size of file in 256 byte blocks
  u8  dir_id : 4;
  u32 part1 : 24;
  u32 part2 : 24;
  u8  file_type_id : 4;
} FileEntry;

extern FileEntry FILE_ENTRIES_TABLE[];

void FUN_80010ad0(s32 *ovl_result, s32 *encrypted_ovl, s32 size);

s32 getFileEntrySizeBytes(s32 entry_idx);

/* Decode file entry name from FILE_ENTRIES_TABLE + offset */
void decodeFileEntryNameByOffset(char *out_name, s32 offset);

/* Decode file entry name from FILE_ENTRIES_TABLE */
void decodeFileEntryName(char *out_name, FileEntry *file_entry);

/* Encode name as a FileEntry record parts */
void encodeFileEntryName(s32 *out_part1, s32 *out_part2, char *name);

/* Get file entry size aligned to 0x800 block (2MB) */
s32 getFileEntrySizeBytesAligned(s32 entry_idx);

/* Find offset from FILE_ENTRIES_TABLE for a given file_type_id,
   Search starts from from start_offset
   When direction is positive - search goes incrementally;
   Otherwise - decrementally  */
u32 findFileEntryByFileTypeId(s32 file_type_id, s32 start_offset,
                              s32 direction);

s32 findFileEntry(u8 *name, s32 file_type_id, s32 start_offset);

extern s32 D_800230A8;

s32 FUN_80010e58(s32 arg0);

extern s32 D_80022C98[];

s32 FUN_80010E68(void);

#endif
