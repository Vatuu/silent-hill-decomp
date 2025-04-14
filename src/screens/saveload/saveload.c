#include "game.h"

#include "bodyprog/bodyprog.h"
#include "screens/saveload/saveload.h"

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E2D8C);

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E2EBC);

void func_801E2F90(s32 idx) // 0x801E2F90
{
    D_801E7578[idx] = D_800A97D4[idx] - D_801E7570[idx];
}

void func_801E2FCC(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    extern char D_801E2720[]; // "FILE" - needs rodata migration
    char*       str = D_801E2720;

    if (arg0 == D_800A97D4[arg1] && arg3 >= 4)
    {
        Gfx_StringColor(7);
        Gfx_StringPosition((arg1 * 150) + 32, 35);
        Gfx_StringDraw(str, 50);
        Gfx_StringPosition((arg1 * 150) + 82, 35);
        Gfx_StringDrawInt(1, arg2);
    }
}

s32 func_801E3078(s_UnkSaveload0* arg0) // 0x801E3078
{
    if (arg0 != NULL && (arg0->field_8 & (1 << 24)))
    {
        Gfx_StringColor(0);
        return 1;
    }

    Gfx_StringColor(7);
    return 0;
}

INCLUDE_ASM("asm/screens/saveload/nonmatchings/saveload", func_801E30C4);

void func_801E326C(s8* arg0, s8* arg1, s32 arg2, s32 arg3) // 0x801E326C
{
    if (arg2 == 0)
    {
        D_801E756C[arg3] = 0;
    }

    if (arg2 < D_801E7570[arg3] || (D_801E7570[arg3] + 4) < arg2)
    {
        if (D_801E756C[arg3] != arg0[6])
        {
            D_801E756C[arg3] = arg0[6];
        }
    }
    else
    {
        func_801E4D90(arg0, arg1, arg2, arg3);
    }
}

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

void GameState_Unk8_Update() // 0x801E6320
{
    D_801E76D0 = 1;

    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        D_801E7524[0]();
    }

    D_801E7524[g_GameWork.gameStateStep_598[0]]();

    func_801E709C();
    func_801E7244();
    func_801E70C8();

    if (g_GameWork.gameState_594 == GameState_Unk10)
    {
        func_800363D0();
    }
}

void func_801E63C0() // 0x801E63C0
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

    g_SysWork.timer_20 = 0;
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

void func_801E72DC() // 0x801E72DC
{
    func_801E3C44();
}

void GameState_Unk4_Update() // 0x801E72FC
{
    if (g_GameWork.gameStateStep_598[0] == 0)
    {
        D_801E7544[0]();
    }

    D_801E7544[g_GameWork.gameStateStep_598[0]]();

    func_801E709C();
    func_801E7244();
    func_801E70C8();
}

void func_801E737C()
{
    if (!func_80033548())
    {
        return;
    }

    if (D_800BCD28 == 0 || D_800BCD39 != 0 || !func_80033548())
    {
        g_GameWork.gameState_594 = GameState_Unk8;

        if (g_GameWork.gameStatePrev_590 == GameState_KcetLogo)
        {
            g_GameWork.gameStateStep_598[0] = 1;
            g_GameWork.gameStateStep_598[1] = g_GameWork.gameStatePrev_590;

            D_800BCD0C = 3;

            GameFs_TitleGfxLoad();
        }

        return;
    }

    D_800BCD2C = (s8*)0x801E09E0 + (D_800A97D6 * 0xA50);
    D_800BCD2C = D_800BCD2C + (D_800A97D4[D_800A97D6] * 0x10);
    D_800BCD40 = D_800BCD2C[5];
    D_800BCD3F = D_800BCD2C[6];
    D_800BCD3E = D_800BCD2C[7];

    g_GameWork.gameStateStep_598[0]++;
    g_SysWork.timer_20              = 0;
    g_GameWork.gameStateStep_598[1] = 0;
    g_GameWork.gameStateStep_598[2] = 0;
}
