#ifndef _SAVELOAD_H
#define _SAVELOAD_H

#include "common.h"

#define MEMORY_CARD_SLOT_COUNT 2
#define SAVE_COUNT_MAX         165

/** @brief
* This file is used for define any variable, struct and
* function that is part of `SAVELOAD.BIN`.
*/

// ============
// ENUMERATORS
// ============


/** @brief
* Used by `s_SaveSlotElementInfo` to identify
* the type of element in the slot save.
*/
typedef enum _SlotElementType
{
    ElementType_NoMemCard     = 0,
    ElementType_Unk1          = 1,
    ElementType_BrokenMemCard = 2,
    ElementType_LoadMemCard   = 3,
    ElementType_Unk4          = 4,
    ElementType_Unk5          = 5,
    ElementType_Unk6          = 6,
    ElementType_BrokenSave    = 7,
    ElementType_Save          = 8,
    ElementType_NewSave       = 9,
    ElementType_NewFile       = 10
} e_SlotElementType;


// ================
// UNKNOWN STRUCTS
// ================
/* Struct called by functions
that haven't been recognized */

typedef struct
{
    s32 unk_0; // Same behaviour as field_0 in `s_SaveSlotElementInfo`.
    u32 gameplayTimer_4;
    u16 savegameCount_8;
    s8  mapEventIdx_A;
    u8  isTitleYellowFlag_B_0 : 1;
    u8  add290Hours_B_1       : 2;
    u8  hyperBlasterFlags_B_3 : 5;
} s_SaveBasicInfo;
/** Possible size is 0xC/12 bytes. */

typedef struct
{
	/** @brief
	* field_0 is a counter that add one each time
	* the game is saved in the memory cards, however
	* it seems buggy or works weirdly as it doesn't
	* add saves based on which memory card the player
	* did the save, for example:
	* If the player saves on slot 1 the first save
	* the value will be 1, but then the player saves
	* on slot 2 the value will be 2 and then the
	* player saves on slot 1 again the value will be 3.
	* Another fact what makes it believe to be a bug
	* is that reproducing the previous example,
	* after the player saves in slot 2, if instead of
	* saving in slot 1 the player removes the memory
	* card and then saves in slot 1 the value won't
	* be 3, but instead it will be 2.
	*/
    s16              field_0;
    s16              savegameCount_2;
    s8               elementType_4; /** `e_SlotElementType` */
    s8               field_5; // The value changes between 0 when the first save slot is selected and 4 when the second is selected.
    s8               file_Idx_6;
    s8               element_Idx_7;
    s32              mapEventIdx_8;
    s_SaveBasicInfo* field_C;
} s_SaveSlotElementInfo;
/**
* Possible size is 0x10/16 bytes.
* This struct is written in memory each time a
* new save is created in any slot and that struct
* always grabs 16 bytes. This pressumption can
* reaffirmed by the fact that always the last
* element of the struct is a struct pointer.
*
* Extra note:
* This struct is also used for the `New save`
* option.
*/


// ========
// STRUCTS
// ========


typedef struct
{
    DVECTOR field_0;
    DVECTOR field_4;
} s_801E2A98;

typedef struct
{
    DVECTOR field_0;
    DVECTOR field_4;
    DVECTOR field_8;
    DVECTOR field_C;
} s_801E2A48;

typedef struct
{
    DVECTOR field_0;
    DVECTOR field_4;
    DVECTOR field_8;
} s_801E2B58;

typedef struct
{
    DVECTOR field_0;
    DVECTOR field_4;
    u16     field_8;
    u16     field_A;
    u16     field_C;
    u16     pad_E;
} s_801E2C8C;

typedef struct
{
    s_801E2A98 field_0[4];
} s_801E2CAC;

typedef struct
{
    s_801E2A48 field_0[4];
} s_801E2CCC;

typedef struct
{
    u8 r, g, b, p;
} s_primColor;


// ========
// GLOBALS
// ========


extern char* g_StageStrings[];

/**
* This and `D_801E7510` are related each
* other, when this is 0 `D_801E7510` is 1
* and when this is 1 the other is 0.
* It is related to saves and overwrites.
* If the player have save the game then
* `D_801E7510` will be 1, but if the player
* is going to overwrite then `D_801E750C`
* turns 1 and `D_801E7510` 0 and onces
* he confirms the overwrite then `D_801E750C`
* turns 0 and `D_801E7510` 1, but if the
* player cancels the overwrite then they keep
* the values (`D_801E750C` 1 and `D_801E7510` 0).
*
* `D_801E7510` it is also related to loading.
*/
extern s32 D_801E750C;

extern s32 D_801E7510;

extern s16 D_801E7514[MEMORY_CARD_SLOT_COUNT];

extern s16 g_LoadingMemCardTimer[MEMORY_CARD_SLOT_COUNT]; // Timer that triggers when loading a detected memory card.

extern s32 g_MemCardState; // Format: 1, Save: 2, Load: 3

/** @brief Timer used when displaying the text after finishing any of the following states:
* - Formatting
* - Saving
* - Loading
* - Error
*/
extern s32 g_MemCardStateTextTimer;

extern void (*g_GameState_SaveScreen_Funcs[])();

extern s32 D_801E753C;

extern s32 g_IsSaveSelected; // 0 - User has `New save` selected, 1 - User has a save selected.

extern void (*g_GameState_DeathLoadScreen_Funcs[])();

extern s32 D_801E7554;

extern s32 D_801E7558;

extern s32 g_OverwriteOptionSelected; // 0 - Nothing/No, 1 - Yes

extern s32 D_801E7564[MEMORY_CARD_SLOT_COUNT];

/** @brief
* Detect what memory card are inserted, but seems
* buggy, it doesn't properly update when a memory
* card was removed while the player is on the save screen.
*/
extern s16 D_801E756C[MEMORY_CARD_SLOT_COUNT];

/** @brief
* Count elements that get hidden as the player move
* down the slot.
*/
extern s16 g_HiddentElementByDisplacement[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7574[MEMORY_CARD_SLOT_COUNT];

/** @brief
* Stores the selected save in each slot.
* Only the first two values are used.
* Possibly the next values are an unused
* variable which Splat detect incorrectly
* and merge it.
*/
extern s16 D_801E7578[MEMORY_CARD_SLOT_COUNT];

extern s8 D_801E7584[SAVE_COUNT_MAX * 2];

extern s8 g_LastSaveIdx[MEMORY_CARD_SLOT_COUNT];

extern s8 g_DisplaySaveDataInfo;

extern s8 g_IsMemCardNotInserted[MEMORY_CARD_SLOT_COUNT]; // 0 - is inserted, 1 - is not inserted.

extern s8 g_Gfx_SaveShineTimer;

// Use when overwriting a save with yellow text.
extern u8 D_801E76D5;

extern u8 g_IsGameSaving;


// ==========
// FUNCTIONS
// ==========


/** Clears all saves? */
void Savegame_ScreenSubInit();

void Gfx_SaveSelectedDisplacement(s32 saveSlotIdx, s32 arg1);

/** Draws the "FILE X" string in the save/load screen. */
void Gfx_SaveFileSelectedDraw(s32 arg0, s32 saveSlotIdx, s32 fileId, s32 arg3);

/** Draws the string of the location where the save was done. */
void Gfx_SavesLocationDraw(s_SaveSlotElementInfo* ptr, s32 arg1, s32 idx);

/** Sets the color of the string to be drawn based on some flag. */
s32 func_801E3078(s_SaveBasicInfo* arg0);

void func_801E326C(s_SaveSlotElementInfo* arg0, s_SaveSlotElementInfo* arg1, s32 arg2, s32 arg3);

void Gfx_MemCardStateDraw(s32 memCardState, s32 arg1);

/** Produces the flicker over the saved game after saving sucessfully. */
void Gfx_SavedFlickerDraw();

void func_801E43C8(s32 arg0);

void Gfx_SavesTransparentBgDraw(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_801E52D8(s32 arg0, s32 arg1);

void Gfx_RectMemLoadDraw(s_801E2CAC* arg0, s_801E2CCC* arg1, s_801E2C8C* arg2, s32 arg3);

/** Updates the save screen. */
void GameState_SaveScreen_Update();

void Savegame_FormatLogic();

void Savegame_LoadLogic();

void Savegame_ContinueLogic();

/** Draws "SLOT1"/"SLOT2" strings, bottom transparent frame, and background image.*/
void Gfx_SaveBackground();

/** Draws all file box strings and graphics, as well as the strings in the transparent frame at the bottom. */
void func_801E70C8();

/** Handles the text that shows when formatting, saving or loading a file.
 *  Used in `GameState_SaveScreen_Update` and `GameState_DeathLoadScreen_Update`.
 */
void Gfx_MemCardState();

void Gfx_OverwriteSave();

/** Updates the death load screen. */
void GameState_DeathLoadScreen_Update();

void func_801E737C();

/** Initialize save screen. */
void Savegame_ScreenInit();

/**
* Crucial for working with the overlay.
* If `g_GameWork.gameStateStep_598[1]` comply any of the conditionals this happen:
* 0 - The user can fully move through the save menu.
* 1 - Triggers the overwrite save.
* 2 - Player leaves the save screen.
*/
void Savegame_ScreenLogic();

void Savegame_SaveLogic();

#endif