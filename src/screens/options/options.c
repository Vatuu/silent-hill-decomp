#include "game.h"

#include "bodyprog/bodyprog.h"
#include "screens/options/options.h"

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

/** Screen position draw related
Triggers on the screen position configuration screen,
likely drawing some sort of graphic
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E53A0);

/** Screen position draw related
Triggers on the screen position configuration screen,
likely drawing some sort of graphic
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E5A08);

/** Screen position draw related
Triggers on the screen position configuration screen,
likely drawing some sort of graphic
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E5CBC);

/** Brightness screen draw related
Triggers on the brightness configuration screen, likely
drawing some sort of graphic
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E6018);

void Gfx_DrawBrightnessLevelText()
{
    #define POS_X 80
    #define POS_Y 190

    char* str = D_801E2C64;

    func_8004A8DC(7);
    Gfx_StringPosition(POS_X, POS_Y);
    Gfx_StringDraw(str, 20);
    func_8004B9F8(1, g_GameWork.optBrightness_22);
}

/** Brightness screen draw related
Triggers on the brightness configuration screen, likely
drawing some sort of graphic
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E628C);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E641C);

/** Draw related?
Triggers when an option that shows a triangle appears on
screen
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E662C);

INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E67B0);

/** Controls screen draw related
Triggers on the controls configuration screen, likely
drawing some sort of graphic
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E69BC);

/** Controls screen draw related
Triggers on the controls configuration screen, likely
drawing some sort of graphic
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E6CF4);

/** Controls screen draw related
Triggers on the controls configuration screen when
having selected any game action
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E6F60);

/** Controls screen draw related
Triggers on the controls configuration screen, likely
drawing some sort of graphic
*/
INCLUDE_ASM("asm/screens/options/nonmatchings/options", func_801E716C);
