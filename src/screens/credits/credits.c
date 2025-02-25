#include "common.h"
#include "screens/credits/credits.h"

extern s8  D_800AFE0E;
extern s32 D_800AFE10; // Packed RGB+command color?
extern s8  D_800AFE2A;

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

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3DD0);

s32 func_801E3DF8(s32 arg0)
{
    return ((u32)((arg0 & 0xFF) * 0x31) >> 6) | 0x38;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3E18);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E42F8);

/**
 * @brief Set the current opaque RGB+command color for an unknown purpose.
 *
 * This function sets the packed RGB+command color of D_800AFE10.
 * The hard set component is either a graphics command code for a textured
 * rectangle, or an alpha, though the latter is unlikely given the PS1's
 * lack of proper alpha blending.
 *
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 */
void func_801E4310(s32 r, s32 g, s32 b)
{
    D_800AFE10 = (r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | (100 << 24);
}

void func_801E4340(s8 arg0)
{
    D_800AFE0E = arg0;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E434C);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4394);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E47E0);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4B98);

void func_801E4BC8(s8 arg0)
{
    D_800AFE2A = arg0;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4BD4);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4C1C);
