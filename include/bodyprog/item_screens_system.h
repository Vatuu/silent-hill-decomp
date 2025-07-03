#ifndef _INVENTORY_SYSTEM_MAIN_H
#define _INVENTORY_SYSTEM_MAIN_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the functionallity and logic of the inventory and result
 * screen system.
 */

typedef enum _InventorySelectionId
{
    InventorySelectionId_Item            = 0,
    InventorySelectionId_EquippedItem    = 1,
    InventorySelectionId_Exit            = 2,
    InventorySelectionId_Settings        = 3,
    InventorySelectionId_Map             = 4,
    InventorySelectionId_ItemCmd         = 5,
    InventorySelectionId_EquippedItemCmd = 6,
    InventorySelectionId_Health          = 7, // Used for animation when user selects health item.
    InventorySelectionId_Examine         = 8
} s_InventorySelectionId; 

// ========
// STRUCTS
// =========

typedef struct _ResultStringOffset
{
    u8 x0_0;
    u8 y0_1;
    u8 x1_2;
    u8 y1_3;
} s_ResultStringOffset;
STATIC_ASSERT_SIZEOF(s_ResultStringOffset, 4);

// ========
// GLOBALS
// ========

extern s32 g_Inventory_CmdSelectedIdx; // 0x800ADB58

/** Defines what the user has selected. `s_InventorySelectionId`.
 *
 * @note
 * `D_800C399C` has the same behaviour, with
 * the main difference being that it can be modified in memory
 * while `D_800C399C` is constatly updated to the same value
 * as this variable.
 */
extern u32 g_Inventory_SelectionId; /** `s_InventorySelectionId` */ // 0x800ADB5C

// ==========
// FUNCTIONS
// ==========

// TODO: The name `Inventory_HyperBlasterCanAdd` may be suitable, though inventory
// funcs seem to be bunched at a different address.
/** @brief Used to check if the Hyper Blaster can be added to the inventory.
 *
 * @return -1 if it already exists in the inventory,
 *          1 if the Konami gun controller is connected or the savegame flag is set,
 *          0 otherwise.
 */
s32 func_8004C45C();

// TODO: The name `Inventory_HyperBlasterCanUse` may be suitable.
/** @brief Called by status screen to check if Hyper Blaster can be used?
 *
 * @return 2 if the savegame flag is set,
 *         1 if the Konami gun controller is connected,
 *         0 otherwise.
 */
s32 func_8004C4F8();

u32 func_8004C54C();

/** `arg0` is probably a bit flag. */
void func_8004C564(u8 arg0, s32 arg1);

void func_8004C8DC();

// Also updates both inventory screen and result screen?
void GameState_ItemScreens_Update();

void Gfx_Results_Save();

/** Function mainly responsible for handling the inventory screen. */
void Inventory_Logic();

/** Something related to items commands.
 * This is used when the user does some action in in the commands space.
 */
void func_8004E6D4(s32 arg0);

void Gfx_Inventory_ScrollArrows(s32* invSelectionId);

// Unused?
s32 func_8004EE94(u8 arg0, u8 arg1);

// Unused?
void func_8004F10C(s32* arg0);

/** Draws the two messages that indicate when
 * the user can't open the map in the inventory.
 */
void Gfx_Inventory_UnavailableMapText(s32 strIdx);

/** Likely controls handling in inventory screen. */
void func_8004F5DC();

/** Draws some rectangle. */
void func_8004FB0C();

/** Related to the drawing of arrows next to
 * the selected item in the inventory.
 * Breaking it reveals that it whitens the arrows,
 * as without this function, the arrows look a bit grey.
 */
void func_80052088(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/** Results screen related.
 * Used in: `func_8004F764`
 */
void func_800521A8();

/** Used to toggle visibility of object while the inventory scrolling rotates.
 *
 * Used in: `Inventory_Logic`
 *
 * If removed, it may cause items to no longer appear when scrolling,
 * and seems to depend on the scroll direction.
 * Removing some parts will result in no issues rotating one way, but
 * will in the other.
 */
void func_800539A4(s32 arg0, s32 arg1);

#endif
