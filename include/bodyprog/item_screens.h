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

// Couldn't this be actually GsCOORD2PARAM?
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

/** @brief Defines what the user has selected in the inventory.
 * `e_InventorySelectionId`
 *
 * @note
 * `g_Inventory_PrevSelectionId` has the same behaviour, with
 * the main difference being that it can be modified in memory
 * while `g_Inventory_PrevSelectionId` is constantly updated to the same value
 * as this variable.
 */
extern u32 g_Inventory_SelectionId; /** `e_InventorySelectionId` */ // 0x800ADB5C

/** @brief Dead code? - Player start scroll?
 * Only used when the player started to scroll through the inventory, but as soon
 * as it get asigned to 1 it turns into 0 again as `Gfx_Inventory_ItemDescriptionDraw`
 * turns it into 0.
 *
 * It serves no purpose on the code beyond the previously explained.
 */
extern s32 D_800AE178;

extern s32 g_Inventory_SelectedItemIdx; // 0x800AE17C

/** @brief Dead code? - Items loaded count?
 * At first glance it may look it counts the amount of scrolls the player does
 * in the inventory, however in reality it seems to be tied to the function
 * that asignates models each time it get up to 10 it stop counting. If the player
 * access to any item screen (Inventory/Results) the counter restart.
 *
 * Beyond that this is not used anywhere else and doesn't comply any purpose.
 */
extern s32 D_800AE180; // 0x800AE180

/** `e_InventoryItemId` */
extern u8 g_Inventory_EquippedItem; // 0x800AE184

/** @brief Dead code?
 * It serves no purpose on the code, only a two intances were it get turn into 0.
 */
extern s16 D_800AE18C; // Maybe DVECTOR
extern s16 D_800AE18E;

extern s32 D_800AE190;

/** Timer used for the black scanline gradient in the health status effect. */
extern s16 g_Inventory_HealthStatusScanlineTimer; // 0x800AE194

/** Timer used for the colored gradient in the health status effect. */
extern s16 g_Inventory_HealthStatusColorGradientTimer; // 0x800AE196

extern s16 D_800AE198; // 0x800AE198

extern s16 g_Inventory_HealthStatusScanlinePosition; // 0x800AE19A

extern s32 g_Inventory_ItemNameTimer; // 0x800AE19C

/** @brief Timer used for displaying item descriptions in the inventory. */
extern s32 g_Inventory_DescriptionRollTimer; // 0x800AE1A0

/** @brief Timer used for the transition of selected items
* when scrolling through the inventory.
*/
extern s32 g_Inventory_ScrollTransitionTimer; // 0x800AE1A4

extern GsCOORD2PARAM D_800C3928; // 0x800C3928

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

/** @note Specially used for smoothing the scrolling through the inventory
 * in case of the holding the directional pad/stick.
 */
extern s32 g_Inventory_IsPlayerScrolling; // 0x800C3990

/** @brief Timer used for the borders at the corners of the selection
 * box in the inventory.
 *
 * If 8 then it will show the borders, if not 8 then it will start summing
 * up until it reaches 8.
 */
extern s32 g_Gfx_Inventory_SelectionBordersDraw; // 0x800C3998

/** @brief Used for drawing the transition of the box position when changing
 * the selected option in the inventory.
 *
 * `e_InventorySelectionId`
 *
 * Specifically this indicate from where the box is moving.
 *
 * It's almost impossible to notice, but this shares the same value as
 * `g_Inventory_SelectionId` with the difference that it has a minor delay.
 */
extern s32 g_Inventory_PrevSelectionId; // 0x800C399C

extern GsF_LIGHT g_Items_ItemsLightingData[8][2]; // 0x800C39A8

extern GsCOORDINATE2 D_800C3AE8; // 0x800C3AE8

/** Used for displaying the item models.
 * It could either indicate values for the camera.
 */
extern SVECTOR3 D_800C3B38; // 0x800C3B38

extern VbRVIEW D_800C3B48; // 0x800C3B48

/** Holds the coords for displaying selection box around items and options. */
extern DVECTOR D_800C3B68[4][4]; // 0x800C3BE8 - Type assumed.

extern s_Items3dData g_Items_Items3dData0[10]; // 0x800C3BE8

extern u8 g_Item_MapLoadableItems[48]; // 0x800C3BB8

/** Used to organize the items displaying in the inventory. */
extern s32 D_800C3E18[7]; // 0x800C3E18

extern GsCOORDINATE2 g_Items_Items3dData1[10]; // 0x800C3E48

/** This value is based on the index of the equipped item.
 * If the player has nothing equipped, the value is `NO_VALUE`.
 */
extern s32 g_Inventory_EquippedItemIdx; // 0x800C3E34

/** Holds information of model data from items. */
extern GsDOBJ2 g_Items_ItemsMdlData[9]; // 0x800C3D78

// ==========
// FUNCTIONS
// ==========

/** This seems to set the camera for items. */
void Gfx_ItemScreens_SetCamera(VbRVIEW* view, GsCOORDINATE2* coord, SVECTOR3* vec, s32 arg3); // 0x8004BB4C

void GameFs_TmdDataAlloc(s32* buf); // 0x8004BCBC

/** @brief Used for item rotation and item scrolling in the inventory.
 *
 * Likely this name is not accurrated as it seems to be used for
 * some intances related to the camera.
 */
void Gfx_Items_ItemRotation(SVECTOR* arg0, GsCOORDINATE2* arg1); // 0x8004BCDC

void func_8004BD74(s32 arg0, GsDOBJ2* arg1, s32 arg2); // 0x8004BD74

void func_8004BFE8(); // 0x8004BFE8

void func_8004C040(); // 0x8004C040

/** @brief Used to correct aim animations when exiting the inventory screen.
 *
 * If removed, when the user enters the inventory between the transition of the
 * aim animation to the idle animation, then changes the weapon to another
 * type (e.g. from a gun weapon to a melee weapon), Harry will continue
 * aiming until he interacts with something or starts running.
 */
void Inventory_ExitAnimEquippedItemUpdate(u8* arg0); // 0x8004C088

/** @brief Used to check if the Hyper Blaster can be added to the inventory.
 *
 * @return -1 if it already exists in the inventory,
 *          1 if the Konami gun controller is connected or the savegame flag is set,
 *          0 otherwise.
 */
s32 Inventory_HyperBlasterUnlockTest(); // 0x8004C45C

/** @brief Called by status screen to check if Hyper Blaster can be used?
 *
 * @return 2 if the savegame flag is set,
 *         1 if the Konami gun controller is connected,
 *         0 otherwise.
 */
s32 Inventory_HyperBlasterFunctionalTest(); // 0x8004C4F8

/** @note Name could be inacurrate. */
u32 Game_HyperBlasterBeamColor(); // 0x8004C54C

/** `arg0` is probably a bit flag. */
void func_8004C564(u8 arg0, s32 arg1); // 0x8004C564

void Game_TimerUpdate(); // 0x8004C8DC

void GameState_ItemScreens_Update(); // 0x8004C9B0

void Gfx_Results_Save(); // 0x8004D1A0

/** Function mainly responsible for handling the inventory screen. */
void Inventory_Logic(); // 0x8004D518

/** @brief Used in circumstances involving the interaction of items that can
 * be used in the enviroment like keys or objects for puzzles or events like
 * the Cybil boss fight.
 *
 * @note Likely this function is where the Cybil boss fight skip bug relies
 * because this function has code specifically for the overlay where the battle
 * ocurrs.
 */
void Inventory_ItemInteraction(s32 arg0); // 0x8004E6D4

void Gfx_Inventory_CmdOptionsDraw(); // 0x8004E864

void Gfx_Inventory_ScrollArrowsDraw(s32* invSelectionId); // 0x8004EC7C

s32 func_8004EE94(u8 arg0, u8 arg1);

s32 func_8004F190(s_ShSavegame* save);

void func_8004F10C(s32* arg0);

/** @brief Draws the two messages that indicate when the player can't open
 * the map in the inventory.
 */
void Gfx_Inventory_UnavailableMapText(s32 strIdx); // 0x8004F57C

void Inventory_DirectionalInputSet(); // 0x8004F5DC

void Gfx_ItemScreens_RenderInit(u32* selectedItemId);

/** Draws some rectangle. */
void func_8004FB0C();

void Gfx_Results_ItemsDisplay(); //  0x800521A8

void Gfx_Primitive2dTextureSet(s32 x, s32 y, s32 otIdx, s32 abr); // 0x80052088

/** @brief Toggle visibility of object while the inventory scrolling rotates.
 *
 * Used in: `Inventory_Logic`
 *
 * Removing it causes the items to not disappear nor displaying items that
 * weren't appearing.
 */
void func_800539A4(s32 arg0, s32 arg1);

/** Related to file loading of inventory elements. Loads Harry's potrait
 * for the status image.
 */
void func_800540A4(s8 arg0);

void Gfx_Items_Render(); // 0x80054200

/** Lightly inacurrate name, part of the code reset values related specifically
 * to visual elements of the inventory.
 */
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

void Gfx_Items_Display(s_TmdFile* tmd, s32 arg1, s32 arg2); // 0x80054720

void func_800548D8(s32 Idx); // 0x800548D8

void Gfx_Items_SetAmbientLighting(); // 0x80054928

void Inventory_AddSpecialItem(u8 itemId, s32 itemCount); // 0x80054CAC

#endif
