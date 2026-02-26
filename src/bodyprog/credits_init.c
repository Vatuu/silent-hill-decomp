#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/text/text_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/ranking.h"
#include "main/fsqueue.h"

s32 D_800C48F0;

s_800AFE08 D_800AFE08 = {
    .field_6  = 0x18,
    .field_8  = 0x64FFFFFF,
    .field_C  = (s16*)0x801E5C24,
    .field_10 = (s32*)0x801E5E24
};

s_800AFE24 D_800AFE24 = {
    .sub_0 = {
        .field_6   = 24,
        .field_8   = 0x2CFFFFFF,
        .field_C   = (s16*)0x801E5C24,
        .field_10  = (s32*)0x801E5E40
    },
    .field_1C  = 4096,
    .field_24  = 240,
    .field_30  = 0xF0000,
    .field_34  = 4096,
    .field_3C  = -4096,
    .field_48  = 4096,
    .field_4C  = 4551
};

void GameFs_StfRollBinLoad() // 0x80091778
{
    // Required for match.
    if (g_Font24AtlasImg.tPage != 0) {}

    Fs_QueueStartRead(FILE_VIN_STF_ROLL_BIN, FS_BUFFER_1);
    func_800917C0(FONT24_BUFFER, 1, &g_Font24AtlasImg);
}

void func_800917C0(void* arg0, s32 arg1, s_FsImageDesc* img) // 0x800917C0
{
    u32 tPage;

    if (arg1 != 0)
    {
        arg0 -= ALIGN(Fs_GetFileSize(FILE_TIM_FONT24_TIM), 0x800);
    }

    Fs_QueueStartReadTim(FILE_TIM_FONT24_TIM, arg0, img);

    D_800AFE08.field_18 = ((u8*)&img->tPage)[1]; // `Fs_QueuePostLoadTim` does something similar.
    tPage               = ((u8*)&img->tPage)[1];

    D_800AFE08.field_14  = tPage & 0x10;
    D_800AFE08.field_14 |= tPage & 0xF;
    D_800AFE08.field_16  = (img->clutY << 6) | ((img->clutX >> 4) & 0x3F);
}

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
    temp_lo_4 = (arg6 + (s32)Q12_MULT_PRECISE(arg3, temp_lo_2)) >> 2;
    temp_lo_4 = temp_t1 / temp_lo_4;

    D_800AFE24.sub_0.field_0  = 0;
    D_800AFE24.sub_0.field_2  = 0;
    D_800AFE24.sub_0.field_4  = 0;
    D_800AFE24.sub_0.field_6  = 24;
    D_800AFE24.sub_0.field_7  = 0;
    D_800AFE24.sub_0.field_8  = 0x2CFFFFFF;
    D_800AFE24.sub_0.field_18 = D_800AFE08.field_18;
    D_800AFE24.sub_0.field_16 = D_800AFE08.field_16;
    D_800AFE24.sub_0.field_14 = D_800AFE08.field_14;
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
    D_800AFE24.field_40 = Q12_MULT_PRECISE(temp_lo, arg4);
    D_800AFE24.field_44 = Q12_MULT_PRECISE(temp_lo_4, arg4);

    temp_v0             = arg4 + Q12_MULT_PRECISE(arg3, arg7);
    D_800AFE24.field_48 = Q12_MULT_PRECISE(temp_lo, temp_v0) - D_800AFE24.field_40;
    D_800AFE24.field_4C = Q12_MULT_PRECISE(temp_lo_4, temp_v0) - D_800AFE24.field_44;
    D_800AFE24.field_50 = Q12_MULT_PRECISE(temp_lo, arg5);

    temp_lo_7           = arg8 * temp_t0;
    temp_t2             = arg5 + Q12_MULT_PRECISE(arg3, temp_lo_7);
    D_800AFE24.field_54 = Q12_MULT_PRECISE(temp_lo_4, temp_t2);
}
