#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"

s32 func_8004C45C() // 0x8004C45C
{
    s32 i;

    for (i = 0; i < INVENTORY_ITEM_COUNT_MAX; i++)
    {
        // Already in inventory, can't add new one.
        if (g_SavegamePtr->items_0[i].id_0 == InventoryItemId_HyperBlaster)
        {
            return NO_VALUE;
        }
    }

    if (g_SavegamePtr->mapOverlayId_A4 > 0)
    {
        // Konami gun controller connected.
        if (g_GameWork.controllers_38[1].analogController_0.status == 0 &&
            g_GameWork.controllers_38[1].analogController_0.received_bytes == 1 &&
            g_GameWork.controllers_38[1].analogController_0.terminal_type == PadTerminalType_GunControllerKonami)
        {
            return 1;
        }

        // Game completed with some condition met?
        if (g_SavegamePtr->clearGameCount_24A != 0 && (g_SavegamePtr->field_24B & (1 << 4)) != 0)
        {
            return 1;
        }
    }

    return 0;
}

s32 func_8004C4F8() // 0x8004C4F8
{
    if (g_SavegamePtr->mapOverlayId_A4 > 0)
    {
        if ((g_SavegamePtr->field_24B & (1 << 4)) != 0)
        {
            return 2; // Game completed with some condition met?
        }

        // Returns 1 if controller port 2 has Konami gun controller connected.
        return g_GameWork.controllers_38[1].analogController_0.status == 0 &&
               g_GameWork.controllers_38[1].analogController_0.received_bytes == 1 &&
               g_GameWork.controllers_38[1].analogController_0.terminal_type == PadTerminalType_GunControllerKonami;
    }

    return 0;
}

u32 func_8004C54C() // 0x8004C54C
{
    return g_SavegamePtr->hyperBlasterFlags_25C_3 >> 3;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004C564); // 0x8004C564

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004C8DC); // 0x8004C8DC

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", GameState_InventoryScreen_Update); // 0x8004C9B0

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004D1A0); // 0x8004D1A0

/** Related to control handling in inventory screen. */
INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004D518); // 0x8004D518

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004E6D4); // 0x8004E6D4

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", Gfx_Inventory_CmdOptions); // 0x8004E864

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004EC7C); // 0x8004EC7C

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004EE94); // 0x8004EE94

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004EF48); // 0x8004EF48

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004F10C); // 0x8004F10C

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004F190); // 0x8004F190

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004F57C); // 0x8004F57C

/** Likely control handling in inventory screen. */
INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004F5DC); // 0x8004F5DC

/** Controls and graphics related to the inventory screen. */
INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004F764); // 0x8004F764

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004FB0C); // 0x8004FB0C

/** Draws many of 2D elements of the menu.
* This draws the background behind the text
* in the upper and lower part of the inventory
* screen, the box use to indicate what the player
* has selected and triggers the draw of the health
* status.
*/
INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8004FBCC); // 0x8004FBCC

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", Gfx_Inventory_HealthStatusDraw); // 0x80051020

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", Gfx_Inventory_ItemDescription); // 0x8005192C

/** Related to the draw of arrows that are aside
* of the selected item in the inventory.
* Breaking it seems to reveal that they are
* whitening the arrows as without the function
* the arrows look a bit gray.
*/
INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_80052088); // 0x80052088

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_800521A8); // 0x800521A8

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_8005227C); // 0x8005227C

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_800523D8); // 0x800523D8

INCLUDE_ASM("asm/bodyprog/nonmatchings/inventory_main", func_800539A4); // 0x800539A4