#ifndef _BODYPROG_ITEM_SCREENS_H
#define _BODYPROG_ITEM_SCREENS_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the functionallity and logic of the inventory and result
 * screen system.
 */

// ==========
// CONSTANTS
// ==========

#define DISPLAYED_ITEM_COUNT_MAX 10

// ======
// ENUMS
// ======

typedef enum _GameEndingFlags
{
    GameEndingFlag_GoodPlus = 1 << 0,
    GameEndingFlag_Good     = 1 << 1,
    GameEndingFlag_BadPlus  = 1 << 2,
    GameEndingFlag_Bad      = 1 << 3,
    GameEndingFlag_Ufo      = 1 << 4
} e_GameEndingFlags;

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

/** @brief Has user started scrolling. Dead code?
 * Only used when the user starts to scrolling through the inventory, but as soon
 * as it's assigned to 1, `Gfx_Inventory_ItemDescriptionDraw` makes it 0 again.
 * Serves no purpose beyond this.
 */
extern s32 D_800AE178;

extern s32 g_Inventory_SelectedItemIdx; // 0x800AE17C

/** @brief Loaded item count. Dead code?
 * Appears to count the number of times the user has scrolled in the inventory.
 * Tied to the function which assigns models. Caps at 10.
 * If the user opens any item screen (i.e. inventory or results), the counter restarts.
 * Serves no purpose beyond this.
 */
extern s32 g_Items_DisplayedCount; // 0x800AE180

/** `e_InventoryItemId` */
extern u8 g_Inventory_EquippedItem; // 0x800AE184

/** @brief Dead code?
 * No clear purpose. There are two intances were they are set to 0.
 */
extern s16 D_800AE18C; // Maybe `DVECTOR`.
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

extern bool g_Inventory_IsUpClicked; // 0x800C3968

extern bool g_Inventory_IsDownClicked; // 0x800C396C

extern bool g_Inventory_IsLeftClicked; // 0x800C3970

extern bool g_Inventory_IsRightClicked; // 0x800C3974

extern bool g_Inventory_IsUpPulsed; // 0x800C3978

extern bool g_Inventory_IsDownPulsed; // 0x800C397C

extern bool g_Inventory_IsLeftPulsed; // 0x800C3980

extern bool g_Inventory_IsRightPulsed; // 0x800C3984

extern bool g_Inventory_IsLeftHeld; // 0x800C3988

extern bool g_Inventory_IsRightHeld; // 0x800C398C

/** @brief Used for smooth inventory scrolling if a left/right input is held. */
extern bool g_Inventory_IsScrolling; // 0x800C3990

/** @brief Timer used for the corner borders of the selection box in the inventory.
 *
 * If set to 8, borders will be drawn. If not, it increments until it reaches 8.
 */
extern s32 g_Gfx_Inventory_SelectionBordersDraw; // 0x800C3998

/** @brief Used for drawing the transition of the corner borders' position when changing
 * the selected option in the inventory. Indicates where the box is moving to.
 *
 * `e_InventorySelectionId`
 *
 * Difficult to notice, but this shares the same value as
 * `g_Inventory_SelectionId`, with the difference of a minor delay.
 */
extern s32 g_Inventory_PrevSelectionId; // 0x800C399C

extern GsF_LIGHT g_Items_Lights[8][2]; // 0x800C39A8

extern GsCOORDINATE2 D_800C3AE8; // 0x800C3AE8

/** Used for displaying the item models.
 * Could also be camera values.
 */
extern SVECTOR3 D_800C3B38; // 0x800C3B38

extern VbRVIEW D_800C3B48; // 0x800C3B48

/** Holds the coords for displaying selection box around items and options. */
extern DVECTOR D_800C3B68[4][4]; // 0x800C3BE8 - Type assumed.

extern GsCOORD2PARAM g_Items_Transforms[DISPLAYED_ITEM_COUNT_MAX]; // 0x800C3BE8

extern u8 g_Item_MapLoadableItems[48]; // 0x800C3BB8

/** Used to organize the items displaying in the inventory.
 * 7 is the max number of visible items.
 */
extern s32 D_800C3E18[7]; // 0x800C3E18

extern GsCOORDINATE2 g_Items_Coords[DISPLAYED_ITEM_COUNT_MAX]; // 0x800C3E48

/** This value is based on the index of the equipped item.
 * If the player has nothing equipped, set to `NO_VALUE`.
 */
extern s32 g_Inventory_EquippedItemIdx; // 0x800C3E34

/** Stores item model data. */
extern GsDOBJ2 g_Items_ItemsModelData[9]; // 0x800C3D78

// ==========
// FUNCTIONS
// ==========

/** Appears to set the camera for items. */
void Gfx_ItemScreens_CameraSet(VbRVIEW* view, GsCOORDINATE2* coord, SVECTOR3* vec, s32 arg3); // 0x8004BB4C

void GameFs_TmdDataAlloc(s32* buf); // 0x8004BCBC

/** @brief Used for item rotation and scrolling in the inventory.
 *
 * Name might be inaccurate as it also appears to be used for the camera.
 */
void Gfx_Items_ItemRotate(SVECTOR* arg0, GsCOORDINATE2* arg1); // 0x8004BCDC

void func_8004BD74(s32 displayItemIdx, GsDOBJ2* arg1, s32 arg2); // 0x8004BD74

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

/** Returns `true` if player has usable ammo in inventory (i.e. ammo + gun needed
 * for it, or gun with ammo loaded) for the shotgun and the hunting rifle.
 *
 * @note Related to the ending unlockable if out of ammo. However, that
 * ending requires the handgun to be out of ammo too. This function is also triggered
 * during the boss fight.
 */
bool func_8004C328(); // 0x8004C328

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

/** @note Rough name. */
u32 Game_HyperBlasterBeamColorGet(); // 0x8004C54C

/** `arg0` is probably a bit flag. */
void func_8004C564(u8 arg0, s32 arg1); // 0x8004C564

void Game_TimerUpdate(); // 0x8004C8DC

void GameState_ItemScreens_Update(); // 0x8004C9B0

void Gfx_Results_Save(); // 0x8004D1A0

/** Function mainly responsible for handling the inventory screen. */
void Inventory_Logic(); // 0x8004D518

/** @brief Used for environmental item interactions such as keys, puzzle objects, or
 * events like the Cybil boss fight.
 *
 * @note This is where the Cybil boss fight skip bug occurs. The function is in
 * charge of triggering the event of Harry throwing the unknown liquid over
 * Cybil, however, the code doesn't check if the NPC that is being interacted
 * with is Cybil, allowing the player to trigger the bug by interacting with
 * the first NPC loaded in `g_SysWork`.
 */
void Inventory_ItemUse(s32 arg0); // 0x8004E6D4

void Gfx_Inventory_CmdOptionsDraw(); // 0x8004E864

void Gfx_Inventory_ScrollArrowsDraw(s32* invSelectionId); // 0x8004EC7C

bool func_8004EE94(u8 itemId, u8 arg1);

s32 func_8004F190(s_Savegame* save);

void func_8004F10C(s32* arg0);

/** @brief Draws the two messages that indicate when the player can't open
 * the map in the inventory.
 */
void Gfx_Inventory_UnavailableMapText(s32 strIdx); // 0x8004F57C

void Inventory_DirectionalInputSet(); // 0x8004F5DC

void Gfx_ItemScreens_RenderInit(u32* selectedItemId);

/** Draws some rectangle. */
void func_8004FB0C();

void Gfx_Inventory_HealthStatusDraw();

void Gfx_Inventory_ItemDescriptionDraw(s32* selectedItemId);

void Gfx_Results_ItemsDisplay(); //  0x800521A8

void Gfx_Results_ItemsPosition();

void Gfx_Primitive2dTextureSet(s32 x, s32 y, s32 otIdx, s32 abr); // 0x80052088

/** @brief Toggles the visibility of object while the inventory scrolls.
 *
 * Used in: `Inventory_Logic`
 */
void func_800539A4(s32 arg0, s32 arg1);

/** Related to file loading of inventory elements.
 * Loads Harry's potrait for the health status image.
 */
void func_800540A4(s8 arg0);

/** Related to rendering items. */
void Gfx_Items_Render(); // 0x80054200

/** Rough name. Part of this function resets values related to visual elements of the inventory. */
void Gfx_Items_RenderInit(); // 0x80054558

/** Used for correct reset of aiming animations when exiting the inventory screen.
 *
 * Used in: `GameState_ItemScreens_Update`
 *
 * This calls two other functions which reset Harry's animations when exiting the inventory screen.
 * If removed, the player softlocks in the following scenario: Harry aims a weapon,
 * the user enters the inventory, unequips the weapon, and exits the inventory.
 * This results in Harry being unable to move and use wrong animations.
 */
void Inventory_ExitAnimFixes(); // 0x80054634

/** Very rough param names. */
void Gfx_Items_Display(s_TmdFile* tmd, s32 displayItemIdx, s32 loadableItemIdx); // 0x80054720

/** Something related to items lighting. */
void func_800548D8(s32 idx); // 0x800548D8

void Gfx_Items_SetAmbientLighting(); // 0x80054928

void Inventory_AddSpecialItem(u8 itemId, u8 itemCount); // 0x80054CAC

#endif
