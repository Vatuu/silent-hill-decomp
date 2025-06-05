#ifndef _INVENTORY_SYSTEM_MAIN_H
#define _INVENTORY_SYSTEM_MAIN_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the functionallity and logic of the inventory and result
 * screen system.
 */

// ========
// STRUCTS
// =========

// This function is the same as `s_ArrowVectors` from options.
typedef struct
{
    DVECTOR field_0;
    DVECTOR field_4;
    DVECTOR field_8;
} s_80026264;

typedef struct
{
    u8 field_0;
    u8 field_1;
    u8 field_2;
    u8 field_3;
} s_80025FFC;

// ========
// GLOBALS
// ========

extern s32 g_Inventory_CmdSelectedIdx;

// g_Inventory_CurrentSelectedStatus
/** This variable defines what the player has selected.
* 0 - Items.
* 1 - Equiped item.
* 2 - Exit option.
* 3 - Settings option.
* 4 - Map option.
* 5 - Command options for item selected.
* 6 - Command options for item equiped.
* 7 - Select health status. (Used for the animation when the player uses a health item)
* 8 - Examining items.
*
* @note
* `D_800C399C` sames the same behaviour,
* the main difference is that this can be modified on memory
* while `D_800C399C` is constatly updating with the same value
* that this variable has.
*/
extern s32 D_800ADB5C;

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

void func_8004C8DC();

// Also updates both inventory screen and result screen... what
void GameState_ItemScreens_Update();

#endif