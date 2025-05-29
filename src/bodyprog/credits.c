#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/credits_system.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

INCLUDE_ASM("asm/bodyprog/nonmatchings/credits", func_8008F94C); // 0x8008F94C

INCLUDE_ASM("asm/bodyprog/nonmatchings/credits", func_800904F4); // 0x800904F4

INCLUDE_ASM("asm/bodyprog/nonmatchings/credits", func_80090664); // 0x80090664

INCLUDE_ASM("asm/bodyprog/nonmatchings/credits", func_8009134C); // 0x8009134C

void func_80091380() {} // 0x80091380

INCLUDE_ASM("asm/bodyprog/nonmatchings/credits", func_80091388); // 0x80091388

void func_80091464() {} // 0x80091464

INCLUDE_ASM("asm/bodyprog/nonmatchings/credits", func_8009146C); // 0x8009146C

INCLUDE_ASM("asm/bodyprog/nonmatchings/credits", func_800914C4); // 0x800914C4

INCLUDE_ASM("asm/bodyprog/nonmatchings/credits", func_8009151C); // 0x8009151C

void GameFs_StfRollBinLoad() // 0x80091778
{
    if (D_800A909C.tPage != 0)
    {
    }

    Fs_QueueStartRead(FILE_VIN_STF_ROLL_BIN, FS_BUFFER_1);
    func_800917C0(FONT24_BUFFER, 1, &D_800A909C);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/credits", func_800917C0); // 0x800917C0

void func_8009185C(s16 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) // 0x8009185C
{
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_4;
    s32 temp_lo_7;
    s32 temp_t1;
    s32 temp_t2;
    s32 temp_v0;
    u16 temp_t0 = 24;

    temp_t1   = arg2 << 22;
    temp_lo   = temp_t1 / (arg6 >> 2);
    temp_lo_2 = arg9 * temp_t0;
    temp_lo_4 = (arg6 + (s32)FP_MULTIPLY((s64)arg3, temp_lo_2, Q12_SHIFT)) >> 2;
    temp_lo_4 = temp_t1 / temp_lo_4;

    D_800AFE24.field_0  = 0;
    D_800AFE24.field_2  = 0;
    D_800AFE24.field_4  = 0;
    D_800AFE24.field_6  = 24;
    D_800AFE24.field_7  = 0;
    D_800AFE24.field_8  = 0x2CFFFFFF;
    D_800AFE24.field_18 = D_800AFE08.field_18;
    D_800AFE24.field_16 = D_800AFE08.field_16;
    D_800AFE24.field_14 = D_800AFE08.field_14;
    D_800AFE24.field_1C = arg3;
    D_800AFE24.field_20 = arg0;
    D_800AFE24.field_22 = arg1;
    D_800AFE24.field_24 = arg2;
    D_800AFE24.field_28 = arg4;
    D_800AFE24.field_2C = arg5;
    D_800AFE24.field_30 = arg6;
    D_800AFE24.field_34 = arg7;
    D_800AFE24.field_38 = arg8;
    D_800AFE24.field_3C = arg9;
    D_800AFE24.field_40 = FP_MULTIPLY((s64)temp_lo, arg4, Q12_SHIFT);
    D_800AFE24.field_44 = FP_MULTIPLY((s64)temp_lo_4, arg4, Q12_SHIFT);

    temp_v0             = arg4 + FP_MULTIPLY((s64)arg3, arg7, Q12_SHIFT);
    D_800AFE24.field_48 = FP_MULTIPLY((s64)temp_lo, temp_v0, Q12_SHIFT) - D_800AFE24.field_40;
    D_800AFE24.field_4C = FP_MULTIPLY((s64)temp_lo_4, temp_v0, Q12_SHIFT) - D_800AFE24.field_44;
    D_800AFE24.field_50 = FP_MULTIPLY((s64)temp_lo, arg5, Q12_SHIFT);

    temp_lo_7           = arg8 * temp_t0;
    temp_t2             = arg5 + FP_MULTIPLY((s64)arg3, temp_lo_7, Q12_SHIFT);
    D_800AFE24.field_54 = FP_MULTIPLY((s64)temp_lo_4, temp_t2, Q12_SHIFT);
}
