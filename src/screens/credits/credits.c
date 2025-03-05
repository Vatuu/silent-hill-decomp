#include "common.h"
#include "gpu.h"
#include "main/rng.h"
#include "bodyprog/bodyprog.h"
#include "screens/credits/credits.h"

// ===== Temporary declarations =====

void func_80032358(s16 x, s16 y, s16 w, s16 h, u8 r, u8 g, u8 b); // Return and arg types assumed.
void func_80032428(u32, u32);                                     // Return and arg types assumed.
void func_80045A7C(u16);                                          // Return type assumed.
u8   func_80045B28();                                             // bodyprog
void func_8004729C(u16);

//===================================

void func_801E2E28(s32 idx)
{
    s32 temp_lo;
    s32 temp_v1;

    D_801E5E8C = idx;
    
    func_8004729C(D_801E5558[idx].field_0);
    temp_v1 = (D_801E5558[idx].field_4 * 2) - 0x1F8;
    temp_lo = temp_v1 / D_801E5C20;
    
    D_801E5E7C = temp_v1;
    D_801E5E88 = 1;
    D_801E5E7C = temp_lo;
    D_801E5E84 = (temp_lo * D_801E5C20) + 0x1E0;
    D_801E5E80 = 0x10000 / temp_lo;
}

s32 func_801E2ED8(void)
{
    switch (D_801E5E88)
    {
        case 0:
            break;
        
        case 1:
            func_80045A7C(D_801E5558[D_801E5E8C].field_0);
            D_801E5E88 += 1;
            break;

        case 2:
            switch (func_80045B28())
            {
                default:
                case 0:
                    return 0;
                
                case 1:
                    D_800C48F0 = D_801E5558[D_801E5E8C].field_2;
                    return 1;
            }
        
        default:
            return 0;
    }

    return 0;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E2FC0);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3094);

// TODO: Matches, but checksum fails.
INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3124);
// Draws some image on the screen.
/*s32 func_801E3124(void)
{
    switch (D_800BC728.field_59C)
    {
        case 0:
            switch (D_800BCD0C)
            {
                case 13:
                    D_800BC728.field_58C = 0xFF;
                    D_800BC728.field_58D = 0xFF;
                    D_800BC728.field_58E = 0xFF;
                    break;

                case 5:
                    D_800BC728.field_58C = 0;
                    D_800BC728.field_58D = 0;
                    D_800BC728.field_58E = 0;
                    break;
            }

            func_80045A7C(0x12);
            func_80045A7C(0x10);
            D_800BC728.field_59C++;
            break;

        case 1:
            StoreImage(&D_801E557C[0], (u_long*)0x801CFA00);
            StoreImage(&D_801E557C[1], (u_long*)0x801C8200);
            DrawSync(0);

            // Maybe an enum entry check.
            switch (D_800BCD0C)
            {
                case 13:
                    func_80032358(0, 0x20, 0x200, 0x1C0, 0xFF, 0xFF, 0xFF);
                    break;

                case 5:
                    func_80032358(0, 0x20, 0x200, 0x1C0, 0x00, 0x00, 0x00);
                    break;
            }

            D_800BC728.field_59C++;
            break;

        case 2:
            func_80032428(0x200, 1);
            D_800A8FF0 = 1;
            D_801E5E74 = 0x3C;
            D_800BC728.field_59C++;
            break;

        case 3:
            D_801E5E74--;
            
            if (D_801E5E74 <= 0 && func_80045B28() < 2)
            {
                D_800BC728.field_58C = 0;
                D_800BC728.field_58D = 0;
                D_800BC728.field_58E = 0;
                return 1;
            }

            break;
    }

    return 0;
}*/

s32 func_801E3304(void)
{
    s32 temp;

    if (D_800BC728.field_590 == 11)
    {
        if (D_800BC728.field_59C == 0)
        {
            func_80032428(0x140, 0);
            D_800BCD0C = 0;
            D_800BC728.field_59C++;
        }
        else if (D_800BC728.field_59C != 10)
        {
            D_800BC728.field_59C++;
        }
        else
        {
            func_80032358(0, 0x20, 0x140, 0x1C0, 0, 0, 0);
            LoadImage(&D_801E557C[0], 0x801CFA00);
            LoadImage(&D_801E557C[1], 0x801C8200);
            DrawSync(0);
            VSync(2);
            
            temp = D_800BC728.field_594;
            
            D_800B9FC0.field_1C = 0;
            D_800B9FC0.field_20 = 0;
            
            D_800BC728.field_59C = 0;
            D_800BC728.field_5A0 = 0;
            
            D_800B9FC0.field_8 = 0;
            D_800B9FC0.field_24 = 0;
            D_800B9FC0.field_C = 0;
            D_800B9FC0.field_28 = 0;
            D_800B9FC0.field_10 = 0;
            D_800B9FC0.field_2C = 0;
            D_800B9FC0.field_14 = 0;
            
            D_800BC728.field_598 = temp;
            D_800BC728.field_594 = (s32)D_800BC728.field_590;
            D_800BC728.field_590 = temp;
            D_800BC728.field_598 = 0;
        }
        
        return 0;
    }

    return 0;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E342C);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3684);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E386C);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3970);

// Credits_SetRandomThingValue
void func_801E3DD0(void)
{
    D_801E600C = Rng_Rand16();
}

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

void func_801E434C(u32 arg0, u32 arg1)
{
    u32 shiftedArg1;
    u32 shiftedField_18;
    u32 maskedField_18;

    D_800AFE08.field_7 = (arg0 != 0);

    if (arg1 < 4)
    {
        maskedField_18 = D_800AFE08.field_18;
        shiftedField_18 = (maskedField_18 << 4) & 0x100;
        
        maskedField_18 &= 0xF;
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
    D_800AFE2C = (r & 0xFF) | ((g & 0xFF) << 8) | ((b & 0xFF) << 16) | (0x2C << 24);
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

    D_800AFE24.field_7 = (arg0 != 0);

    if (arg1 < 4)
    {
        maskedField_18 = D_800AFE24.field_18;
        shiftedField_18 = (maskedField_18 << 4) & 0x100;
        
        maskedField_18 &= 0xF;
        shiftedField_18 >>= 4;
        
        shiftedArg1 = arg1 & 3;
        shiftedArg1 <<= 5;
        shiftedArg1 |= shiftedField_18;
        shiftedArg1 |= (u8)maskedField_18;
        
        D_800AFE24.field_14 = shiftedArg1;
    }
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E4C1C);
