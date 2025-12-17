#include "bodyprog/bodyprog.h"
#include "bodyprog/libsd.h"

/** In Jan 16 Demo and the Nov 24, 98 Preview,
 * all these functions also nullsub. Additionally,
 * `func_800485C0` doesn't exist in the Jan 16 Demo.
 */

void func_800485B0(s16 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4) {} // 0x800485B0

void func_800485B8(s32 arg0, u8 arg1, u32 arg2) {} // 0x800485B8

void func_800485C0(s32 idx) // 0x800485C0
{
    g_AudioPlayingIdxList[idx] = 0;
}
