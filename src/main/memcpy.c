#include "common.h"

/** NOTE: `memcpy` may rely on hand-tuned or inline assembly.
 * This code matches but is almost just straight ASM -> C in some parts, if it was written in C originally it likely didn't look like this.
 * Matching it precisely isn't really a priority, since this would likely just be replaced down the line.
 */
char* memcpy(void* dest0, void* src0, unsigned int count)
{
    u8*           ret;
    s32           i;
    s32*          dest32;
    s32           src_offset;
    u32           src_data;
    s32           part;
    s32           mask;
    s32           mask2;
    s32           comb;
    s32           v0;
    u8*           dest;
    u8*           src;
    register s32* src32 asm("a2");
    register s32  a0 asm("a0");
    register s32  v1 asm("v1");

    dest = dest0;
    src  = src0;

    __asm__ volatile("addiu $4, $4, 0" :);
    __asm__ volatile("addiu $5, $5, 0" :);
    __asm__ volatile("addiu %0, $6, 0" : "r="(v1) :);

    ret = dest;

    for (i = (4 - (u32)dest) % 4; i > 0 && v1 > 0;)
    {
        i--;
        v1--;
        *dest++ = *src++;
    }

    src_offset = (u32)src % 4;
    if (v1 > 0)
    {
        dest32 = (s32*)dest;

        if (src_offset == 0)
        {
            v1   -= 4;
            src32 = (s32*)src;

            for (; v1 >= 0; v1 -= 4)
            {
                a0        = *src32++;
                *dest32++ = a0;
            }

            v1 += 4;

            if (v1 > 0)
            {
                a0      = *dest32;
                mask    = -1 << (v1 * 8);
                comb    = a0 & mask;
                a0      = *src32;
                a0      = a0 & ~mask;
                comb   |= a0;
                *dest32 = comb;
            }
        }
        else
        {
            src32 = (s32*)(src - src_offset);

            src_offset *= 8;
            i           = 32 - src_offset;

            src_data = *src32++;
            part     = src_data >> src_offset;

            v1 -= 4;

            for (; v1 >= 0; v1 -= 4)
            {
                src_data  = *src32++;
                part     |= (src_data << i);
                *dest32++ = part;
                part      = src_data >> src_offset;
            }

            v1 += 4;

            if (v1 > 0)
            {
                v0      = 32 - (v1 * 8);
                v1      = -1U >> v0;
                a0      = *src32;
                v0      = a0 << i;
                part   |= v0;
                comb    = part & v1;
                a0      = *dest32 & ~v1;
                comb   |= a0;
                *dest32 = comb;
            }
        }
    }

    return ret;
}

void nullsub_800120b0(void) {}
