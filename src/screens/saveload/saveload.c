#include "common.h"
#include "gpu.h"
#include "bodyprog/bodyprog.h"
#include "screens/credits/credits.h"
#include "screens/saveload/saveload.h"

// ===== Temporary declarations =====

void func_801E2D8C(); // bodyprog

//===================================

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E2D8C);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E2EBC);

void func_801E2F90(s32 idx)
{
    D_801E7578[idx] = D_800A97D4[idx] - D_801E7570[idx];
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E2FCC);

s32 func_801E3078(s_UnkSaveload0* arg0)
{
    if (arg0 != NULL && (arg0->field_08 & 0x01000000))
    {
        func_8004A8DC(0);
        return 1;
    }
        
    func_8004A8DC(7);
    return 0;
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E30C4);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E326C);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E3304);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E3910);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E3C44);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E3E78);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E4010);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E43C8);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E451C);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E4D90);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E52D8);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E54DC);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E5898);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E5E18);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E6320);

void func_801E63C0(void)
{
    if (D_800BC728.field_590 == 7)
    {
        VSync(8);
    }
    
    D_800A8FF0 = 1;
    D_800BCD0C = 6;
    
    D_800BC728.field_58C = 0;
    D_800BC728.field_58D = 0;
    D_800BC728.field_58E = 0;
    
    D_800BCD39 = 0;
    
    if (D_800BC728.field_594 == 4 || D_800BC728.field_594 == 8)
    {
        if (D_800A97D8 != 0)
        {
            D_800BCD34 = 0;
        }
    }
    
    D_801E7520 = 0;
    D_800A97D8 = (D_800BC728.field_594 == 16);
    
    func_801E2D8C();
    
    D_800B9FE0[0] = 0;
    D_800BC728.field_598++;
    D_800BC728.field_59C = 0;
    D_800BC728.field_5A0 = 0;
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E649C);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E69E8);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E6B18);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E6DB0);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E6F38);

void func_801E709C(void)
{
    func_801E2EBC();
    func_800314EC(&D_800A902C);
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E70C8);

void func_801E7244(void)
{
    if (D_801E7520 > 0)
    {
        D_801E76D0 = 0;
        D_801E7520 -= 1;

        switch (D_801E751C) 
        {
            case 1:
                func_801E3910(D_801E751C, (D_800BCD34 >> (D_800BCD40 * 3)) & 7);
                break;

            case 2:
            case 3:
                func_801E3910(D_801E751C, func_8002E990());
                break;
        }
    }
}

void func_801E72DC(void)
{
    func_801E3C44();
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E72FC);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E737C);
