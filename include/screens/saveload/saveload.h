#ifndef _SAVELOAD_H
#define _SAVELOAD_H

#include "common.h"

#define SAVEGAME_ENTRY_BUFFER_0 ((u8*)0x801E09E0) // Slot 1 savegame entry.
#define SAVEGAME_ENTRY_BUFFER_1 ((u8*)0x801E1430) // Slot 2 savegame entry.

#define SAVEGAME_COUNT_MAX 165

#define GetActiveSavegameEntry(slotIdx) \
    ((s_SavegameEntry*)&SAVEGAME_ENTRY_BUFFER_0[2640 * (slotIdx)])

/** @brief This header is used to declare any variable, struct, or
 * function part of `SAVELOAD.BIN`.
 */

// ============
// ENUMERATORS
// ============

/** @brief Used by `g_MemCardState`. */
typedef enum _MemCardState
{
    MemCardState_None   = 0,
    MemCardState_Format = 1,
    MemCardState_Save   = 2,
    MemCardState_Load   = 3
} s_MemCardState;

/** @brief Used by `s_SavegameEntry`. */
typedef enum _SavegameEntryType
{
    SavegameEntryType_NoMemCard          = 0,
    SavegameEntryType_UnformattedMemCard = 1,
    SavegameEntryType_CorruptedMemCard   = 2,
    SavegameEntryType_LoadMemCard        = 3,
    SavegameEntryType_OutOfBlocks        = 4,
    SavegameEntryType_NoDataInMemCard    = 5,
    SavegameEntryType_Unk6               = 6,
    SavegameEntryType_CorruptedSave      = 7,
    SavegameEntryType_Save               = 8,
    SavegameEntryType_NewSave            = 9,
    SavegameEntryType_NewFile            = 10
} e_SavegameEntryType;

// ================
// UNKNOWN STRUCTS
// ================

/* Structs called by functions that haven't been identified. */

typedef struct _SavegameMetadata
{
    s32 field_0;                   // Same behavior as `totalSavegameCount_0` in `s_SavegameEntry`.
    u32 gameplayTimer_4;
    u16 savegameCount_8;
    u8  locationId_A;
    u8  isNextFearMode_B             : 1;
    u8  add290Hours_B_1              : 2;
    u8  pickedUpSpecialItemCount_B_3 : 5; /** See `pickedUpSpecialItemCount_25C_3` comment in `s_ShSavegame`. */
} s_SavegameMetadata; // Possible size is 12 bytes.

/** @note A new instance is written to memory each time a
 * new save is created in any slot.
 *
 * Also used for the `New save` entry.
 */
typedef struct _SavegameEntry
{
    /** @brief `currentScreenSessionSaves_0` is a counter
     * incremented each time the user saves during the
     * current save screen session.
	 *
	 * Behaviour seems to be buggy, as it
	 * doesn't consider circumstances where the
	 * user removes a memory card. For example:
     * If the user saves to slot 1, the first save's
     * value will be 1. If the user saves
     * to slot 2, the value will be 2. If the
     * user saves to slot 1 again, the value will be 3.
     * The reason to believe this may be buggy
     * is that by reproducing the previous example,
     * after the user saves to slot 2, if instead of
     * saving in slot 1 the user removes the memory
     * card and save to slot 1, the value will
     * be 2 instead of 3.
     */
    s16                 currentScreenSessionSaves_0;
    s16                 savegameCount_2;
    s8                  type_4;               /** `e_SavegameEntryType` */
    s8                  field_5;              // The value changes between 0 when the first save slot is selected and 4 when the second is selected.
    s8                  fileIdx_6;
    s8                  elementIdx_7;         // Index in file?
    s8                  locationId_8;
    s8                  unk_9[3]; // Probably padding.
    s_SavegameMetadata* field_C;
} s_SavegameEntry;
STATIC_ASSERT_SIZEOF(s_SavegameEntry, 16);

// ========
// GLOBALS
// ========

extern char* g_SaveLocationNames[];

/** This and `D_801E7510` are related.
 * When this is 0, `D_801E7510` is 1
 * and vice-versa.
 *
 * It is related to saves, specifically overwrites.
 *
 * If the user saves the game, `D_801E7510`
 * becomes 1, but if the user is about to overwrite
 * it, `D_801E750C` is set to 1 and `D_801E7510` is set
 * to 0. Once the overwrite is confirmed, `D_801E750C`
 * is set to 0 and `D_801E7510` is set to 1. If the
 * player cancels the overwrite, these variables
 * maintain their values (`D_801E750C` as 1 and `D_801E7510` as 0).
 *
 * `D_801E7510` is also related to loading.
 */
extern s32 D_801E750C;

extern s32 D_801E7510;

/** @brief Dead code?
 * Some boolean statuses for each save slot.
 *
 * This seems to be related to the color of the
 * borders of the file, but appears to do nothing
 * as the code only defines it as 1 or 0.
 * It might also be buggy as it constantly oscillates
 * between 0 and 1. For example:
 * in `Gfx_SaveScreenDraw`, the code has a conditional
 * that writes 1, but a little later
 * in the same function, it writes 1 again
 * without any conditional.
 */
extern s16 D_801E7514[MEMORY_CARD_SLOT_COUNT];

extern s16 g_LoadingMemCardTimer[MEMORY_CARD_SLOT_COUNT]; // Timer that triggers when loading a detected memory card.

extern s32 g_MemCardState; /** `s_MemCardState` */

/** @brief Timer used when displaying the text after finishing any of the following states:
 * - Formatting
 * - Saving
 * - Loading
 * - Error
 */
extern s32 g_MemCardStateTextTimer;

extern void (*g_GameState_SaveScreen_Funcs[])();

extern s32 g_SaveWriteOption; // 0 - Overwrite, 1 - Format

extern s32 g_IsSaveSelected; // 0 - User has `New save` selected, 1 - User has a save selected.

extern void (*g_GameState_DeathLoadScreen_Funcs[])();

extern s32 D_801E7554;

extern s32 D_801E7558;

extern s32 g_SaveWriteOptionSelected; // 0 - No, 1 - Yes

/** @brief Dead code?
 * The only time when this is used is when booting the save screen where
 * both values are defined as 0, the memory card is being loaded,
 * or the user has the last save selected in the slot (where it asks if
 * the value corresponding to the slot is 0 to then overwrite it with 1).
 * 
 * Used in: `Savegame_ScreenSubInit` and `Gfx_SaveScreenDraw`.
 */
extern s32 D_801E7564[MEMORY_CARD_SLOT_COUNT];

/** @brief Related to file count in a slot.
 * Counts the number of files in a slot. Has some odd
 * odd behavior as it resets the count to 1 if the selected element
 * isn't from the last save. If an element from the last file is
 * selected, it will correctly count all the files.
 *
 * `Gfx_SaveEntryBorder` is entirely on charge of it's logic.
 *
 * @note Detects what memory cards are inserted. Appears
 * buggy, as it doesn't properly update when a memory
 * card is removed while the user is on the save screen.
 */
extern s16 D_801E756C[MEMORY_CARD_SLOT_COUNT];

/** @brief Count of elements that are hidden as the user scrolls
 * through the displayed save elements in the slot.
 */
extern s16 g_HiddenElementsByDisplacement[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7574[MEMORY_CARD_SLOT_COUNT];

/** @brief This array is used to draw the flash of the selected save.
 *
 * Stores the index of the element selected in each
 * slot based on what is visually available in the slot.
 *
 * For example: if the user has 9 savegames in the file and
 * wants to create a new, separate savegame, the index of the
 * `New Save` element will  be 4 and not 9 (index starting from 0)
 * as it is the fifth element visually available in the slot.
 *
 * @note Only the first 4 bytes (as two `s16`) are used.
 * The next 8 bytes are unused, possibly from unused variables
 * which Splat detects incorrectly and merges it.
 */
extern s16 g_Gfx_SelectedSaveOffsetsY[MEMORY_CARD_SLOT_COUNT];

extern s8 D_801E7584[SAVEGAME_COUNT_MAX * MEMORY_CARD_SLOT_COUNT];

/** @brief Stores the index of the last save done.
 *
 * Depending on the slot where the last save is done
 * the value representing the other slot is turn into -1.
 */
extern s8 g_LastSaveIdx[MEMORY_CARD_SLOT_COUNT];

extern s8 g_DisplaySaveDataInfo;

extern s8 g_IsMemCardNotInserted[MEMORY_CARD_SLOT_COUNT]; // 0 - is inserted, 1 - is not inserted.

extern s8 g_Gfx_SaveFlashTimer;

extern u8 g_IsNextFearMode;

extern u8 g_IsGameSaving;

// ==========
// FUNCTIONS
// ==========

/** Clears all saves? */
void Savegame_ScreenSubInit();

void Gfx_SaveSelectedDisplacement(s32 slotIdx, s32 unusedSaveCount);

/** Draws the "FILE X" string in the save/load screen. */
void Gfx_SaveSlotFileStringDraw(s32 saveIdx, s32 slotIdx, s32 fileId, s32 entryType);

/** Draws the string of the location where the save was done. */
void Gfx_SavegameEntryLocationNameDraw(s_SavegameEntry* saveEntry, s32 saveIdx, s32 slotIdx);

/** Sets the color of the string to be drawn based on some flag. */
bool Gfx_SavegameEntryStringColorSet(s_SavegameMetadata* saveEntry);

void Gfx_SaveEntryBorder(s_SavegameEntry* saveEntry, s_SavegameEntry* nextSaveEntry, s32 saveIdx, s32 slotIdx);

void Gfx_MemCardStateDraw(s32 memCardState, s32 arg1);

/** Flashes savegame entry after saving sucessfully. */
void Gfx_SavegameEntryDrawFlash();

/** @brief Derivative of `Gfx_SaveSlotMemCardMsgBoxDraw`
 * this draws a flash which appears during an unusual
 * state where the memory card is "not formatted" and
 * `g_GameWork.gameState_594` is `GameState_Unk10`.
 */
void Gfx_SaveSlotMemCardMsgBoxShineDraw(s32 slotIdx);

/** Draws transparent background and scroll bar. */
void Gfx_SaveSlotBoxDraw(s32 slotIdx, s32 saveCount, s32 selectedSaveIdx, s32 selectedSaveOffsetY);

void Gfx_SaveEntryBorderDraw(s_SavegameEntry* saveEntry, s_SavegameEntry* nextSaveEntry, s32 saveIdx, s32 slotIdx); // 0x801E4D90

/** Draws message box that says "Now checking MEMEORY CARD" or "MEMORY CARD is not inserted". */
void Gfx_SaveSlotMemCardMsgBoxDraw(s32 slotIdx, s32 entryType);

void Gfx_SaveSlotMemCardMsgBoxSubDraw(s_LineBorder* borderLines, s_QuadBorder* borderGlowQuads, s_ColoredLine2d* coloredLine, s32 slotIdx);

void Gfx_RectSaveInfoDraw(s_Line2d* line); // 0x801E5898

void Gfx_SaveDataInfoDraw(s32 slotIdx, s32 selectedSaveIdx); // 0x801E5E18

/** Updates the save screen. */
void GameState_SaveScreen_Update();

void Savegame_FormatLogic();

void Savegame_LoadLogic();

void Savegame_ContinueLogic();

void Gfx_SaveBackgroundDraw();

void Gfx_SaveScreen(); // 0x801E70C8

/** @brief Handles the text that shows when formatting, saving, or loading a file.
 *
 *  Used in: `GameState_SaveScreen_Update` and `GameState_DeathLoadScreen_Update`.
 */
void Gfx_MemCardState();

void Gfx_WriteOptionSaveDraw(s32 arg0, s32 optionIdx);

void Gfx_SavedFlashDraw(); // 0x801E3E78

void Gfx_SaveSlotBorderDraw(); // 0x801E4010

void Gfx_WriteOptionSave(s32 arg0, s32 optionIdx);

/** Updates the death load screen. */
void GameState_DeathLoadScreen_Update();

void func_801E737C();

/** Initialize save screen. */
void Savegame_ScreenInit();

/** Crucial for working with the overlay.
 *
 * `g_GameWork.gameStateStep_598[1]` defines the state:
 * 0 - The user can freely move through the save menu.
 * 1 - Triggers the overwrite save.
 * 2 - Player leaves the save screen.
 */
void Savegame_ScreenLogic();

void Savegame_SaveLogic();

#endif
