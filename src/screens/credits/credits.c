#include "common.h"
#include "main/rng.h"
#include "screens/credits/credits.h"

void func_8004729C(u16);

typedef struct
{
    s16 field_00;
    s16 field_02;
    s16 field_04;
    s8  unk_06;
    s8  field_07; // bool
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    u16 field_14;
    s16 unk_16;
    u32 field_18;
} s_UnkCredits0; // Size: unknown

// Used by func_801E2E28.
typedef struct
{
    s16 field_00;
    s16 field_02;
    s16 field_04;
} s_UnkCredits1; // Size: 6

extern s_UnkCredits0 D_800AFE08;
extern s8            D_800AFE0E;
extern s32           D_800AFE10; // Packed RGB+command color? Command is 0x64.
extern s_UnkCredits0 D_800AFE24;
extern s8            D_800AFE2A;
extern s32           D_800AFE2C; // Packed RGB+command color? Command is 0x2C.
extern s_UnkCredits1 D_801E5558[];
extern s32           D_801E5C20;
extern s32           D_801E5E7C;
extern s32           D_801E5E80;
extern s32           D_801E5E84;
extern s32           D_801E5E88;
extern s32           D_801E5E8C; // Index for some array used by most recent func_801E2E28 call.
extern s32           D_801E600C;

void func_801E2E28(s32 idx)
{
    s32 temp_lo;
    s32 temp_v1;

    D_801E5E8C = idx;
    
    func_8004729C(D_801E5558[idx].field_00);
    temp_v1 = (D_801E5558[idx].field_04 * 2) - 0x1F8;
    temp_lo = temp_v1 / D_801E5C20;
    
    D_801E5E7C = temp_v1;
    D_801E5E88 = 1;
    D_801E5E7C = temp_lo;
    D_801E5E84 = (temp_lo * D_801E5C20) + 0x1E0;
    D_801E5E80 = 0x10000 / temp_lo;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E2ED8);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E2FC0);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3094);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3124);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3304);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E342C);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3684);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E386C);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3970);

void func_801E3DD0(void)
{
    D_801E600C = Rng_Rand16();
}

s32 func_801E3DF8(s32 arg0)
{
    return ((u32)((arg0 & 0xff) * 0x31) >> 6) | 0x38;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3E18);

void func_801E42F8(s16 arg0, s16 arg1)
{
    D_800AFE08.field_00 = arg0;
    D_800AFE08.field_02 = arg1;
    D_800AFE08.field_04 = arg0;
}

void func_801E4310(s32 r, s32 g, s32 b)
{
    D_800AFE10 = (r & 0xff) | ((g & 0xff) << 8) | ((b & 0xff) << 16) | (0x64 << 24);
}

void func_801E4340(s8 arg0)
{
    D_800AFE0E = arg0;
}

void func_801E434C(u32 arg0, u32 arg1)
{
    u32 shiftedArg1;
    u32 shiftedField_18;
    u32 maskedField_18;

    D_800AFE08.field_07 = (arg0 != 0);

    if (arg1 < 4)
    {
        maskedField_18 = D_800AFE08.field_18;
        shiftedField_18 = (maskedField_18 << 4) & 0x100;
        
        maskedField_18 &= 0xf;
        shiftedField_18 >>= 4;
        
        shiftedArg1 = arg1 & 3;
        shiftedArg1 <<= 5;
        shiftedArg1 |= shiftedField_18;
        shiftedArg1 |= (u8)maskedField_18;
        
        D_800AFE08.field_14 = shiftedArg1;
    }
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4394);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E47E0);

void func_801E4B98(s32 r, s32 g, s32 b)
{
    D_800AFE2C = (r & 0xff) | ((g & 0xff) << 8) | ((b & 0xff) << 16) | (0x2c << 24);
}

void func_801E4BC8(s8 arg0)
{
    D_800AFE2A = arg0;
}

void func_801E4BD4(u32 arg0, u32 arg1)
{
    u32 shiftedArg1;
    u32 shiftedField_18;
    u32 maskedField_18;

    D_800AFE24.field_07 = (arg0 != 0);

    if (arg1 < 4)
    {
        maskedField_18 = D_800AFE24.field_18;
        shiftedField_18 = (maskedField_18 << 4) & 0x100;
        
        maskedField_18 &= 0xf;
        shiftedField_18 >>= 4;
        
        shiftedArg1 = arg1 & 3;
        shiftedArg1 <<= 5;
        shiftedArg1 |= shiftedField_18;
        shiftedArg1 |= (u8)maskedField_18;
        
        D_800AFE24.field_14 = shiftedArg1;
    }
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4C1C);
