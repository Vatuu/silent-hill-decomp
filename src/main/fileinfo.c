#include "main/fileinfo.h"

#define NAME_PART_CHARS  4
#define NAME_CHAR_BITS   6
#define NAME_CHAR_MASK   0x3F
#define NAME_CHAR_OFFSET 0x20

/** Convenience macros to convert constant filenames to `name0123_4_4` and `name4567_8_0`. */
#define FA2N(c) (((u8)(c) - 0x20) & 0x3f)
#define FNP(c0, c1, c2, c3) (FA2N(c0) | (FA2N(c1) << 6) | (FA2N(c2) << 12) | (FA2N(c3) << 18))
#define FN(c0, c1, c2, c3, c4, c5, c6, c7) FNP(c0, c1, c2, c3), FNP(c4, c5, c6, c7)

s_FileInfo g_FileTable[FS_FILE_COUNT] = {
#if defined(VER_USA)
    #include "filetable.c.USA.inc"
#elif defined(VER_JAP0)
    #include "filetable.c.JAP0.inc"
#endif
};

char* g_FilePaths[] = {
    "\\1ST\\",
    "\\ANIM\\",
    "\\BG\\",
    "\\CHARA\\",
    "\\ITEM\\",
    "\\MISC\\",
    "\\SND\\",
    "\\TEST\\",
    "\\TIM\\",
    "\\VIN\\",
    "\\XA\\"
};

char* g_FileExts[] = {
    ".TIM",
    ".VAB",
    ".BIN",
    ".DMS",
    ".ANM",
    ".PLM",
    ".IPD",
    ".ILM",
    ".TMD",
    ".DAT",
    ".KDT",
    ".CMP"
};

u32 g_FileXaLoc[] = {
#if defined(VER_USA)
    0x00000,
    0x099BF,
    0x0A227,
    0x0B377,
    0x0D0BF,
    0x0EA57,
    0x0F997,
    0x1096F,
    0x16F07,
    0x19797,
    0x00000
#elif defined(VER_JAP0)
    0x00000,
    0x099C3,
    0x0A22B,
    0x0B37B,
    0x0D0C3,
    0x0EA5B,
    0x0F99B,
    0x10973,
    0x16F0B,
    0x1979B,
    0x00000
#endif
};

void Fs_DecryptOverlay(s32* dst, const s32* src, s32 size)
{
    s32 i    = 0;
    s32 seed = 0;

    i = 0;
    while (i < (size >> 2))
    {
        seed = (seed + 0x01309125) * 0x03A452F7;
        *dst = *src ^ seed;

        i++;
        src++;
        dst++;
    }
}

s32 Fs_GetFileSize(s32 fileIdx)
{
    return g_FileTable[fileIdx].blockCount_0_19 * FS_BLOCK_SIZE;
}

void Fs_GetFileName(char* outName, s32 fileIdx)
{
    Fs_GetFileInfoName(outName, &g_FileTable[fileIdx]);
}

void Fs_GetFileInfoName(char* outName, const s_FileInfo* const fileEntry)
{
    s32   i = 0;
    char  decoded;
    u32   namePart;
    char  fileType;
    char* fileExt;

    namePart = fileEntry->name0123_4_4;

    while (i < FS_NAME_CHAR_MAX)
    {
        if (i == NAME_PART_CHARS)
        {
            namePart = fileEntry->name4567_8_0;
        }

        decoded = namePart & NAME_CHAR_MASK;

        if (decoded == 0)
        {
            break;
        }

        outName[i] = decoded + NAME_CHAR_OFFSET;
        namePart >>= NAME_CHAR_BITS;
        i++;
    }

    fileType = fileEntry->type_8_24;

    if (fileType == FS_INVALID_TYPE)
    {
        outName[i] = '\0';
        return;
    }

    fileExt    = g_FileExts[fileType];
    outName[i] = *fileExt;

    while (*fileExt)
    {
        fileExt++;
        i++;
        outName[i] = *fileExt;
    }
}

void Fs_EncodeFileName(s32* outName0123, s32* outName4567, const char* srcName)
{
    s32 i;
    s32 currentShift;
    s32 srcChar;
    s32 encoded;
    s32 name0123;
    s32 name4567;

    name0123     = 0;
    name4567     = 0;
    currentShift = 0;
    for (i = 0; i < FS_NAME_CHAR_MAX; i++)
    {
        srcChar = srcName[i];

        if (i == NAME_PART_CHARS)
            currentShift = 0;

        if (srcChar == '\0' || srcChar == '.')
            break;

        encoded = (srcChar - NAME_CHAR_OFFSET) << currentShift;

        if (i < 4)
        {
            name0123 |= encoded;
        }
        else
        {
            name4567 |= encoded;
        }

        currentShift += NAME_CHAR_BITS;
    }

    *outName0123 = name0123;
    *outName4567 = name4567;
}

s32 Fs_GetFileSectorAlignedSize(s32 fileIdx)
{
    return ALIGN(g_FileTable[fileIdx].blockCount_0_19 * FS_BLOCK_SIZE, FS_SECTOR_SIZE);
}

s32 Fs_FindNextFileOfType(s32 fileType, s32 startIdx, s32 dir)
{
    s32 i;
    u32 currentIdx;
    s32 inc;

    inc = (dir < 0) ? -1 : 1;

    i = 0;
    currentIdx = startIdx + inc;
    while (i < FS_FILE_COUNT)
    {
        if (currentIdx >= FS_FILE_COUNT)
        {
            currentIdx = (dir < 0) ? (FS_FILE_COUNT - 1) : 0;
        }

        if (g_FileTable[currentIdx].type_8_24 == fileType)
        {
            return currentIdx;
        }

        currentIdx += inc;
        i++;
    }

    return NO_VALUE;
}

s32 Fs_FindNextFile(const char* name, s32 fileType, s32 startIdx)
{
    s_FileInfo* fileEntry;
    s32         name0123;
    s32         name4567;
    s32         i        = startIdx;
    s32         foundIdx = NO_VALUE;

    Fs_EncodeFileName(&name0123, &name4567, name);

    fileEntry = &g_FileTable[i];
    while (i < FS_FILE_COUNT)
    {
        if (fileEntry->name4567_8_0 == name4567 &&
            fileEntry->name0123_4_4 == name0123 &&
            fileEntry->type_8_24    == fileType)
        {
            foundIdx = i;
            break;
        }

        i++;
        fileEntry++;
    }

    return foundIdx;
}
