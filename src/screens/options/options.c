#include "game.h"

#include "bodyprog/bodyprog.h"
#include "screens/options/options.h"
#include "screens/stream/stream.h"

// ========================================
// UNKNOWN OPTION SCREEN FUNCTIONS 1
// Likely general options
// ========================================

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E2D44);

/** Extra screen-related options. */
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E318C);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E3770);

void func_801E3F68()
{
    func_801E3FB8(0, g_GameWork.optVolumeBgm_1F);
}

void func_801E3F90()
{
    func_801E3FB8(1, g_GameWork.optVolumeSe_20);
}

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E3FB8);

/** Extra screen-related options. */
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E416C);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E42EC);

/** Extra screen-related options. */
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E4450);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E472C);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E49F0);

/** Extra screen-related options. */
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E4B2C);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E4FFC);

// ========================================
// SCREEN POSITION OPTION SCREEN
// ========================================

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E53A0);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E5A08);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E5CBC);

// ========================================
// BRIGHTNESS OPTION SCREEN
// ========================================

void Settings_BrightnessScreen() // 0x801E6018
{
    switch (g_GameWork.gameStateStep_598[1])
    {
    case 0:
        g_GameWork.gameStateStep_598[1] = 1;
        g_GameWork.gameStateStep_598[2] = 0;
    break;
    case 1:
        D_800BCD0C = 6;
        g_GameWork.gameStateStep_598[1] = 2;
        g_GameWork.gameStateStep_598[2] = 0;
    break;
    case 2:
        if (g_ControllerPtr0->field_18 & Pad_LStickLeft)
		{
            if (g_GameWork.optBrightness_22 != 0)
			{
                g_GameWork.optBrightness_22--;
                func_80046048(0x519, 0, 0x40);
            }
        }

        if (g_ControllerPtr0->field_18 & Pad_LStickRight)
		{
            if (g_GameWork.optBrightness_22 < 7)
			{
                g_GameWork.optBrightness_22++;
                func_80046048(0x519, 0, 0x40);
            }
        }

        if (g_ControllerPtr0->btns_new_10 & (g_GameWorkPtr1->controllerBinds_0.enter | g_GameWorkPtr1->controllerBinds_0.cancel))
		{
            if (g_ControllerPtr0->btns_new_10 & g_GameWorkPtr1->controllerBinds_0.enter)
			{
                func_80046048(0x51B, 0, 0x40);
            }
            else
			{
                func_80046048(0x51A, 0, 0x40);
            }
            D_800BCD0C = 2;
            g_GameWork.gameStateStep_598[1]++;
            g_GameWork.gameStateStep_598[2] = 0;
        }
    break;
    case 3:
        if (D_800BCD0C & 0x4 && (D_800BCD0C & 0x2) == 0 && D_800BCD0C & 0x1)
		{
            D_800BCD0C = 0x4 | 0x2;
            g_GameWork.gameStateStep_598[0] = 11;
            g_SysWork.field_20 = 0;
            g_GameWork.gameStateStep_598[1] = 0;
            g_GameWork.gameStateStep_598[2] = 0;
            g_GameWork.field_58C = 0;
            g_GameWork.field_58D = 0;
            g_GameWork.field_58E = 0;
        }
    break;
    }

    if (g_GameWork.gameStatePrev_590 == GameState_MainMenu)
	{
        func_800314EC(&D_800A9044);
    }
	else
	{
        func_800314EC(&D_800A904C);
    }
    func_8003E5E8(g_GameWork.optBrightness_22);
    Gfx_DrawBrightnessLevelArrows();
    Gfx_DrawBrightnessLevelText();
}

void Gfx_DrawBrightnessLevelText() // 0x801E6238
{
    #define POS_X 80
    #define POS_Y 190

    char* str = D_801E2C64;

    func_8004A8DC(7);
    Gfx_StringPosition(POS_X, POS_Y);
    Gfx_StringDraw(str, 20);
    func_8004B9F8(1, g_GameWork.optBrightness_22);
}

void Gfx_DrawBrightnessLevelArrows() // 0x801E628C
{
    s_801E2C74 var0;
    s_801E2C74 var1;
    s32 btn_input;
    s32 i;
    s32 dir;

    var0 = D_801E2C74;
    var1 = D_801E2C8C;

    btn_input = g_ControllerPtr0->btns_held_C;
    
    if (btn_input & Pad_LStickLeft)
	{
        dir = 1;
    }
	else if (btn_input & Pad_LStickRight)
	{
        dir = 2;
    }
	else
	{
        dir = 0;
    }

    for (i = 0; i < 2; i++)
    {
        func_801E662C(&var0.field_0[i], 1, 0);
    }
    
    for (i = dir - 1; i < dir; i++)
    {
        func_801E662C(&var1.field_0[i], 0, 0);
    }
}

// ========================================
// UNKNOWN OPTION SCREEN FUNCTIONS 2
// ========================================

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E641C);

/** Draw related
Function that draws the arrows used on option menus
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E662C);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E67B0);

// ========================================
// CONTROLS OPTION SCREEN
// ========================================

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E69BC);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E6CF4);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E6F60);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E716C);
