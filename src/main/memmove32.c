#include "main/mem.h"

/**
 * @brief Custom implementation of `memmove` that copies word-by-word.
 *
 * This function copies a specified number of bytes from the source
 * memory location to the destination memory location.
 * Copies word-by-word instead of byte-by-byte. Beware of unaligned access?
 *
 * @param dest Destination pointer to where the content is to be copied.
 * @param src Source pointer from where the content is to be copied.
 * @param byteCount Number of bytes (not words) to copy.
 */
void Mem_Move(u32* dest, u32* src, s32 byteCount)
{
        u32* end;
        s32 wordCount;

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
            src += wordCount;

            while (src > end)
            {
                *(--dest) = *(--src);
            }
        }
}
