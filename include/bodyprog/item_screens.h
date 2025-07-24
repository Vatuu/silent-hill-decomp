#ifndef _ITEM_SCREENS_H
#define _ITEM_SCREENS_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the functionallity and logic of the inventory and result
 * screen system.
 */

// ======
// ENUMS
// ======

typedef enum _InventoryItemFlags
{
    InventoryItemFlag_PlateOfTurtle   = 1 << 0,
    InventoryItemFlag_PlateOfHatter   = 1 << 1,
    InventoryItemFlag_PlateOfCat      = 1 << 2,
    InventoryItemFlag_PlateOfQueen    = 1 << 3,
    InventoryItemFlag_Lighter         = 1 << 4,
    InventoryItemFlag_Camera          = 1 << 5,
    InventoryItemFlag_VideoTape       = 1 << 6,
    InventoryItemFlag_ChannelingStone = 1 << 7
} e_InventoryItemFlags;

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
} e_InventorySelectionId;

// ========
// STRUCTS
// ========

typedef struct _ResultStringOffset
{
    u8 x0_0;
    u8 y0_1;
    u8 x1_2;
    u8 y1_3;
} s_ResultStringOffset;
STATIC_ASSERT_SIZEOF(s_ResultStringOffset, 4);

typedef struct
{
    DVECTOR field_0;
    DVECTOR field_4;
} s_Inventory_SelectionOutlineVector;

typedef struct
{
    VECTOR  scale_0;
    SVECTOR rotation_10;
    VECTOR  field_18; // Position? Doesn't seems to be used.
} s_Items3dData;

// ========
// GLOBALS
// ========

extern s32 g_Inventory_CmdSelectedIdx; // 0x800ADB58

/** @brief Defines what the user has selected in the inventory. `s_InventorySelectionId`
 *
 * @note
 * `D_800C399C` has the same behaviour, with
 * the main difference being that it can be modified in memory
 * while `D_800C399C` is constantly updated to the same value
 * as this variable.
 */
extern u32 g_Inventory_SelectionId; /** `s_InventorySelectionId` */ // 0x800ADB5C

extern s32 g_Inventory_SelectedItemIdx; // 0x800AE17C

/** `e_InventoryItemId` */
extern u8 g_Inventory_EquippedItem; // 0x800AE184

extern s32 D_800AE190;

/** Timer used for the black scanline gradient health status effect. */
extern s16 g_Inventory_StatusScanlineTimer; // 0x800AE194

/** Timer used for the colored gradient in the health status effect. */
extern s16 g_Inventory_StatusDarkGradientTimer; // 0x800AE196

extern s16 D_800AE198; // 0x800AE198

extern s16 g_Inventory_StatusScanlinePosition; // 0x800AE19A

extern s32 g_Inventory_ItemNameTimer; // 0x800AE19C

/** @brief Timer used for displaying item descriptions in the inventory. */
extern s32 g_Inventory_DescriptonRollTimer; // 0x800AE1A0

/** @brief Timer used for the transition of selected items
* when scrolling through the inventory.
*/
extern s32 g_Inventory_ScrollTransitionTimer; // 0x800AE1A4

extern s32 g_Inventory_IsUpClicked; // 0x800C3968

extern s32 g_Inventory_IsDownClicked; // 0x800C396C

extern s32 g_Inventory_IsLeftClicked; // 0x800C3970

extern s32 g_Inventory_IsRightClicked; // 0x800C3974

extern s32 g_Inventory_IsUpPulsed; // 0x800C3978

extern s32 g_Inventory_IsDownPulsed; // 0x800C397C

extern s32 g_Inventory_IsLeftPulsed; // 0x800C3980

extern s32 g_Inventory_IsRightPulsed; // 0x800C3984

extern s32 g_Inventory_IsLeftHeld; // 0x800C3988

extern s32 g_Inventory_IsRightHeld; // 0x800C398C

/** @brief Timer used for displaying outline at the corners
 * of the selected option/item in the inventory. */
extern s32 g_Inventory_CornersOutlineSelection; // 0x800C3998

extern GsF_LIGHT g_Items_ItemsLightingData[8][2]; // 0x800C39A8

/** Used for holding the coords for display item/option selection box */
extern DVECTOR D_800C3B68[4][4]; // Type assumed - 0x800C3BE8

extern s_Items3dData g_Items_Items3dData_1[10]; // 0x800C3B68

/** Used to organize the items displaying in the inventory.
* Size is `28/0x1C`.
*/
extern s32 D_800C3E18[7]; // 0x800C3E18

extern GsCOORDINATE2 g_Items_Items3dData_2[10]; // 0x800C3E48

/** This value is based on the index of the equipped item.
* If the player has nothing equipped, the value is `NO_VALUE`.
*/
extern s32 g_Inventory_EquippedItemIdx; // 0x800C3E34

// ==========
// FUNCTIONS
// ==========

/** Renders items. */
void func_8004BB4C(VbRVIEW* view, GsCOORDINATE2* coord, SVECTOR3* vec, s32 arg3);

/** Apparently adjusts the position of items in the inventory. */
void func_8004BFE8();

/** Used for item rotation and item scrolling in the inventory. */
void Gfx_Results_ItemsRotate(SVECTOR* arg0, GsCOORDINATE2* arg1); // 0x8004BCDC

void func_8004BD74(s32 arg0, GsDOBJ2* arg1, s32 arg2);

/** Used to correct aim animations when exiting the inventory screen.
 *
 * If removed, when the user enters the inventory between the transition of the
 * aim animation to the idle animation, then changes the weapon to another
 * type (e.g. from a gun weapon to a melee weapon), Harry will continue
 * aiming until he interacts with something or starts running.
 */
void Inventory_ExitAnimEquippedItemUpdate(u8* arg0); // 0x8004C088

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
void GameState_ItemScreens_Update(); // 0x8004C9B0

void Gfx_Results_Save(); // 0x8004D1A0

/** Function mainly responsible for handling the inventory screen. */
void Inventory_Logic(); // 0x8004D518

/** Something related to items commands.
 * This is used when the user does some action in in the commands space.
 */
void func_8004E6D4(s32 arg0);

void Gfx_Inventory_CmdOptionsDraw(); // 0x8004E864

void Gfx_Inventory_ScrollArrowsDraw(s32* invSelectionId); // 0x8004EC7C

// Unused?
s32 func_8004EE94(u8 arg0, u8 arg1);

// Unused?
void func_8004F10C(s32* arg0);

/** Draws the two messages that indicate when
 * the user can't open the map in the inventory.
 */
void Gfx_Inventory_UnavailableMapText(s32 strIdx); // 0x8004F57C

void Inventory_DirectionalInputSet(); // 0x8004F5DC

void Gfx_ItemScreens_RenderInit(u32* arg0);

/** Draws some rectangle. */
void func_8004FB0C();

/** Results screen related.
 * Used in: `Gfx_ItemScreens_RenderInit`
 */
void Gfx_Results_ItemsDisplay(); //  0x800521A8

void Gfx_Primitive2dTextureSet(s32 x, s32 y, s32 otIdx, s32 abr); // 0x80052088

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

/** Related to file loading of inventory elements. Loads Harry's potrait for the status image. */
void func_800540A4(s8 arg0);

void Gfx_Items_RenderItems(); // 0x80054200

void Gfx_Items_RenderInit(); // 0x80054558

/** Used for fixing bugs related to aiming animations when exiting the inventory screen.
 *
 * Used in: `GameState_ItemScreens_Update`
 *
 * This function calls two other functions that serves to fix bugs also related
 * to the animations when exiting the inventory screen and also have specific
 * code for a specific bug which causes the player to softlock if before entering
 * the inventory the player was aiming a weapon, then unequip that weapon and
 * leaves the inventory causing Harry to being unable to move or causing
 * buggy animations.
 */
void Inventory_ExitAnimFixes(); // 0x80054634

void func_800548D8(s32 arg0); // 0x800548D8

void Gfx_Items_SetAmbientLighting(); // 0x80054928

void func_80054CAC(u8 itemId, s32 itemCount); // 0x80054CAC

#endif
