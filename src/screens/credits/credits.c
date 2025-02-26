#include "common.h"
#include "screens/credits/credits.h"

typedef struct UnkStruct0
{
    s16 field_0;
    s16 field_2;
    s16 field_4;
    u8  field_7; // Used as bool.

    // Contains more unknown fields.
    
} UnkStruct0;

extern s8  D_800AFE0E;
extern s32 D_800AFE10; // Packed RGB+command color?
extern s8  D_800AFE2A;
extern s32 D_800AFE2C; // Packed RGB+command color?
extern s32 D_801E600C;

extern UnkStruct0 D_800AFE08;

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E2E28);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E2ED8);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E2FC0);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3094);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3124);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3304);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E342C);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3684);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E386C);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3970);

// TODO: Should be a match.
INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3DD0);
/*void func_801E3DD0(void)
{
    D_801E600C = Rng_Rand16();
}*/

s32 func_801E3DF8(s32 arg0)
{
    return ((u32)((arg0 & 0xFF) * 0x31) >> 6) | 0x38;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3E18);

void func_801E42F8(s16 arg0, s16 arg1)
{
    D_800AFE08.field_0 = arg0;
    D_800AFE08.field_2 = arg1;
    D_800AFE08.field_4 = arg0;
}

void func_801E4310(s32 r, s32 g, s32 b)
{
    D_800AFE10 = (r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | (0x64 << 24);
}

void func_801E4340(s8 arg0)
{
    D_800AFE0E = arg0;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E434C);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4394);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E47E0);

void func_801E4B98(s32 r, s32 g, s32 b)
{
    D_800AFE2C = (r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | (0x2C << 24);
}

void func_801E4BC8(s8 arg0)
{
    D_800AFE2A = arg0;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4BD4);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4C1C);
