#include "bodyprog/bodyprog.h"
#include "bodyprog/libsd.h"

/** In Jan 16 Demo and the Nov 24, 98 Preview
 * all this functions are nullsub too, additionally
 * in the Jan 16 Demo `func_800485C0` doesn't exist.
 */

void func_800485B0(s16 arg0, u8 arg1, u8 arg2, s16 arg3, s16 arg4) {}

void func_800485B8(s32 arg0, u8 arg1, u32 arg2) {}

void func_800485C0(s32 idx) // 0x800485C0
{
    D_800C15F8[idx] = 0;
}