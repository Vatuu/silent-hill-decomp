#include "game.h"

#include "bodyprog/bodyprog.h"
#include "screens/saveload/saveload.h"

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E2D8C);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E2EBC);

void func_801E2F90(s32 idx)
{
    D_801E7578[idx] = D_800A97D4[idx] - D_801E7570[idx];
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E2FCC);

s32 func_801E3078(s_UnkSaveload0* arg0)
{
    if (arg0 != NULL && (arg0->field_8 & (1 << 24)))
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

void func_801E63C0()
{
    if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
    {
        VSync(8);
    }

    g_IntervalVBlanks = 1;
    D_800BCD0C = 6;

    g_GameWork.field_58C = 0;
    g_GameWork.field_58D = 0;
    g_GameWork.field_58E = 0;

    D_800BCD39 = 0;
    if (g_GameWork.gameState_594 == GameState_Unk4 || g_GameWork.gameState_594 == GameState_Unk8)
    {
        if (D_800A97D8 != 0)
        {
            D_800BCD34 = 0;
        }
    }

    D_801E7520 = 0;
    D_800A97D8 = (g_GameWork.gameState_594 == GameState_Unk10);

    func_801E2D8C();

    g_SysWork.field_20 = 0;
    g_GameWork.gameStateStep_598[0]++;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E649C);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E69E8);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E6B18);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E6DB0);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E6F38);

void func_801E709C()
{
    func_801E2EBC();
    func_800314EC(&D_800A902C);
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E70C8);

void func_801E7244()
{
    if (D_801E7520 <= 0)
        return;

    D_801E76D0 = 0;
    D_801E7520--;

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

void func_801E72DC()
{
    func_801E3C44();
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E72FC);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E737C);
