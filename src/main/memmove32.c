#include "main/mem.h"

void Mem_Move32(u32* dest, u32* src, s32 byteCount)
{
    u32* end;
    s32  wordCount;

    if (dest == src)
    {
        return;
    }

    wordCount = byteCount >> 2;
    if (dest < src)
    {
        end = src + wordCount;

        while (src < end)
        {
            *dest++ = *src++;
        }
    }
    else
    {
        end = src;

        dest += wordCount;
        src  += wordCount;

        while (src > end)
        {
            *(--dest) = *(--src);
        }
    }
}
