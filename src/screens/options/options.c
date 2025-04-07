#include "game.h"

#include "bodyprog/bodyprog.h"
#include "screens/options/options.h"
#include "screens/stream/stream.h"

// ========================================
// GENERAL, MAIN AND EXTRA OPTION SCREENS
// ========================================

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E2D44);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Settings_ExtraScreen); // 0x801E318C

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Settings_MainScreen); // 0x801E3770

void Gfx_BGMBarDraw() // 0x801E3F68
{
    Gfx_BarDraw(0, g_GameWork.optVolumeBgm_1F);
}

void Gfx_SFXBarDraw() // 0x801E3F90
{
    Gfx_BarDraw(1, g_GameWork.optVolumeSe_20);
}

/** Draw strings related
Function that generates and draw bars used for SFX and BGM audio options
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_BarDraw); // 0x801E3FB8

/** Draw strings related
Function that draws the strings of the options available on the extra options screen
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_OptionsStringsExtraDraw); // 0x801E416C

/** Draw strings related
Function that draws the strings of the options available on the main options screen
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_OptionsStringsMainDraw); // 0x801E42EC

/** Draw related
Function that draws the buttons aside the options and the line that indicates the
selected option from the extra options screen
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_SelectedOptionExtra); // 0x801E4450

/** Draw related
Function that draws the buttons aside the options and the line that indicates the
selected option from the main options screen
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_SelectedOptionMain); // 0x801E472C

/** Draw related
Function that draws the vignette for the main and extra options screens
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_VignetteDraw); // 0x801E49F0

/** Draw related
Function that draws the options for each setting used on the extra options screen
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_SettingsOptionsExtraDraw); // 0x801E4B2C

/** Draw related
Function that draws the options for each setting used on the main options screen
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_SettingsOptionsMainDraw); // 0x801E4FFC

// ========================================
// SCREEN POSITION OPTION SCREEN
// ========================================

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Settings_PositionScreen); // 0x801E53A0 

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_PositionArrowsDraw); // 0x801E5A08

/** Draw related
Function that draws the box that indicate the coordinates of the position of the
screen in the position screen configuration
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_PositionIndicatorDraw); // 0x801E5CBC

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
    Gfx_BrightnessLevelArrowsDraw();
    Gfx_BrightnessLevelTextDraw();
}

void Gfx_BrightnessLevelTextDraw() // 0x801E6238
{
    #define POS_X 80
    #define POS_Y 190

    char* str = D_801E2C64;

    func_8004A8DC(7);
    Gfx_StringPosition(POS_X, POS_Y);
    Gfx_StringDraw(str, 20);
    func_8004B9F8(1, g_GameWork.optBrightness_22);
}

void Gfx_BrightnessLevelArrowsDraw() // 0x801E628C
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
        Gfx_ArrowDraw(&var0.field_0[i], 1, 0);
    }
    
    for (i = dir - 1; i < dir; i++)
    {
        Gfx_ArrowDraw(&var1.field_0[i], 0, 0);
    }
}

// ========================================
// DRAW OPTIONS FEATURES SCREEN
// ========================================

/** Draw related
Function that draws the line used on the selected option from options screens
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_LineDraw); // 0x801E641C

/** Draw related
Function that draws the arrows used on the many options screens
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_ArrowDraw); // 0x801E662C

/** Draw related
Function that draws the button aside of options from main and extra options screens
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_ButtonDraw); // 0x801E67B0

// ========================================
// CONTROLS OPTION SCREEN
// ========================================

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Settings_ControllerScreen); // 0x801E69BC

/** Controller mapping related
Function that changes the button mapping based on the input
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", Settings_ButtonChange); // 0x801E6CF4

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_ControllerScreenDraw); // 0x801E6F60

INCLUDE_ASM("asm/screens/options/nonmatchings/options", Gfx_ControllerButtonsDraw); // 0x801E716C
