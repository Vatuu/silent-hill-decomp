#include "filetable.h"

#define NAME_PART_CHARS 4
#define NAME_CHAR_BITS 6
#define NAME_CHAR_MASK 0x3F
#define NAME_CHAR_OFFSET 0x20

void fsDecryptOverlay(s32 *dst, const s32 *src, s32 size) {
  s32 i, seed = 0;

  i = 0;
  while (i < (size >> 2)) {
    seed = (seed + 0x01309125) * 0x03A452F7;

    *dst = *src ^ seed;

    i++;
    src++;
    dst++;
  }
}

s32 fsFileGetSize(s32 filenum) {
  return g_FileTable[filenum].numblocks * FS_BLOCK_SIZE;
}

void fsFileGetFullName(char *outname, s32 filenum) {
  fsFileEntryGetFullName(outname, &g_FileTable[filenum]);
}

void fsFileEntryGetFullName(char *outname, const FileEntry *const fentry) {
  s32   i = 0;
  char  decoded;
  u32   namepart;
  char  ftype;
  char *fext;

  namepart = fentry->name0123;

  while (i < FS_MAX_NAME) {
    if (i == NAME_PART_CHARS) {
      namepart = fentry->name4567;
    }

    decoded = namepart & NAME_CHAR_MASK;

    if (decoded == 0) {
      break;
    }

    outname[i] = decoded + NAME_CHAR_OFFSET;
    namepart >>= NAME_CHAR_BITS;
    i++;
  }

  ftype = fentry->type;

  if (ftype == FS_INVALID_TYPE) {
    outname[i] = '\0';
    return;
  }

  fext = g_FileExts[ftype];
  outname[i] = *fext;

  while (*fext) {
    fext++;
    i++;
    outname[i] = *fext;
  }
}

void fsEncodeFileName(s32 *outname0123, s32 *outname4567, const char *srcname) {
  s32 i;
  s32 curshift;
  s32 srcchar;

  s32 encoded;
  s32 name0123;
  s32 name4567;

  name0123 = 0;
  name4567 = 0;
  curshift = 0;

  for (i = 0; i < FS_MAX_NAME; i++) {
    srcchar = srcname[i];

    if (i == NAME_PART_CHARS) {
      curshift = 0;
    }

    if (srcchar == '\0' || srcchar == '.') {
      break;
    }

    encoded = (srcchar - NAME_CHAR_OFFSET) << curshift;

    if (i < 4) {
      name0123 |= encoded;
    } else {
      name4567 |= encoded;
    }

    curshift += NAME_CHAR_BITS;
  }

  *outname0123 = name0123;
  *outname4567 = name4567;
}

s32 fsFileGetSizeInSectors(s32 filenum) {
  return ((g_FileTable[filenum].numblocks * FS_BLOCK_SIZE) +
          (FS_SECTOR_SIZE - 1)) &
         ~(FS_SECTOR_SIZE - 1);
}

s32 fsFileFindNextOfType(s32 ftype, s32 startnum, s32 direction) {
  s32 i;
  u32 curnum;
  s32 increment;

  increment = direction < 0 ? -1 : 1;

  i = 0;
  curnum = startnum + increment;

  while (i < FS_NUM_FILES) {
    if (curnum >= FS_NUM_FILES) {
      curnum = direction < 0 ? FS_NUM_FILES - 1 : 0;
    }

    if (g_FileTable[curnum].type == ftype) {
      return curnum;
    }

    curnum += increment;
    i++;
  }

  return -1;
}

s32 fsFileFindNext(const char *name, s32 ftype, s32 startnum) {
  FileEntry *fentry;

  s32 name0123;
  s32 name4567;

  s32 i = startnum;

  s32 foundidx = -1;

  fsEncodeFileName(&name0123, &name4567, name);

  fentry = &g_FileTable[i];

  while (i < FS_NUM_FILES) {
    if (fentry->name4567 == name4567 && fentry->name0123 == name0123 &&
        fentry->type == ftype) {
      foundidx = i;
      break;
    }

    i++;
    fentry++;
  }

  return foundidx;
}
