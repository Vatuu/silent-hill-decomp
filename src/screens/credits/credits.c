#include "common.h"
#include "gpu.h"
#include "main/rng.h"
#include "screens/credits/credits.h"

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

typedef struct
{
    u32 unk_00;
    u32 unk_04;
    u32 field_08;
    u32 field_0C;
    u32 field_10;
    u32 field_14;
    u32 unk_18;
    u32 field_1C;
    u32 field_20;
    u32 field_24;
    u32 field_28;
    u32 field_2C;
} s_UnkCredits2; // Size: >=48

typedef struct
{
    u8  pad[1424];
    u32 field_590;
    u32 field_594;
    u32 field_598;
    u32 field_59C;
    u32 field_5A0;
} s_UnkCredits3; // Size: >=1460

extern s_UnkCredits0 D_800AFE08;
extern s8            D_800AFE0E;
extern s32           D_800AFE10; // Packed RGB+command color? Command is 0x64.
extern s_UnkCredits0 D_800AFE24;
extern s8            D_800AFE2A;
extern s32           D_800AFE2C; // Packed RGB+command color? Command is 0x2C.
extern s_UnkCredits2 D_800B9FC0;
extern s_UnkCredits3 D_800BC728;
extern s32           D_800BCD0C;
extern s32           D_800C48F0;
extern s_UnkCredits1 D_801E5558[];
extern RECT          D_801E557C[];
extern s32           D_801E5C20;
extern s32           D_801E5E7C;
extern s32           D_801E5E80;
extern s32           D_801E5E84;
extern s32           D_801E5E88;
extern s32           D_801E5E8C; // Index for some array used by most recent func_801E2E28 call. func_801E2ED8 accesses it.
extern s32           D_801E600C;

// =====Temporary function declarations=====

void func_80045A7C(u16); // Return type assumed.
u8   func_80045B28();
void func_8004729C(u16);

//==========================================

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

s32 func_801E2ED8(void)
{
    switch (D_801E5E88)
    {
        case 0:
            break;
        
        case 1:
            func_80045A7C(D_801E5558[D_801E5E8C].field_00);
            D_801E5E88 += 1;
            break;

        case 2:
            switch (func_80045B28())
            {
                default:
                case 0:
                    return 0;
                
                case 1:
                    D_800C48F0 = D_801E5558[D_801E5E8C].field_02;
                    return 1;
            }
        
        default:
            return 0;
    }

    return 0;
}

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E2FC0);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3094);

INCLUDE_ASM("asm/screens/credits/nonmatchings/credits", func_801E3124);

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
            
            D_800B9FC0.field_08 = 0;
            D_800B9FC0.field_24 = 0;
            D_800B9FC0.field_0C = 0;
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
    D_800AFE08.field_00 = arg0;
    D_800AFE08.field_02 = arg1;
    D_800AFE08.field_04 = arg0;
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

    D_800AFE08.field_07 = (arg0 != 0);

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

    D_800AFE24.field_07 = (arg0 != 0);

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
