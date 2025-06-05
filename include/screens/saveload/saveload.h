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

/** @brief Used by `s_SavegameEntry`. */
typedef enum _SavegameEntryType
{
    SavegameEntryType_NoMemCard        = 0,
    SavegameEntryType_Unk1             = 1,
    SavegameEntryType_CorruptedMemCard = 2,
    SavegameEntryType_LoadMemCard      = 3,
    SavegameEntryType_Unk4             = 4,
    SavegameEntryType_Unk5             = 5,
    SavegameEntryType_Unk6             = 6,
    SavegameEntryType_CorruptedSave    = 7,
    SavegameEntryType_Save             = 8,
    SavegameEntryType_NewSave          = 9,
    SavegameEntryType_NewFile          = 10
} e_SavegameEntryType;

// ================
// UNKNOWN STRUCTS
// ================

/* Structs called by functions that haven't been identified. */

typedef struct _SavegameMetadata
{
    s32 unk_0;                     // Same behaviour as `totalSavegameCount_0` in `s_SavegameEntry`.
    u32 gameplayTimer_4;
    u16 savegameCount_8;
    s8  locationId_A;
    u8  isNextFearMode_B      : 1;
    u8  add290Hours_B_1       : 2;
    u8  hyperBlasterFlags_B_3 : 5;
} s_SavegameMetadata; // Possible size is 12 bytes.

/** @note A new instance is written to memory each time a
 * new save is created in any slot.
 *
 * Also used for the `New save` entry.
 */
typedef struct _SavegameEntry
{
    /** @brief `field_0` is a counter that increments by one each time
     * the game is saved to a memory card. However,
     * it seems to be buggy or works weirdly as it doesn't
     * add saves based on which memory card the player
     * used for the save. For example:
     * If the player saves to slot 1, the first save
     * the value will be 1. If the player saves
     * to slot 2, the value will be 2. If the
     * player saves to slot 1 again, the value will be 3.
     * Another reason to believe this may be a bug
     * is that by reproducing this example,
     * after the player saves to slot 2, if instead of
     * saving in slot 1 the player removes the memory
     * card and then saves to slot 1, the value will
     * be 2 instead of 3.
     */
    s16                 totalSavegameCount_0;
    s16                 savegameCount_2;
    s8                  type_4;               /** `e_SavegameEntryType` */
    s8                  field_5;              // The value changes between 0 when the first save slot is selected and 4 when the second is selected.
    s8                  fileIdx_6;
    s8                  elementIdx_7;         // Index in file?
    s32                 locationId_8;
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
 * It is related to saves and overwrites.
 *
 * If the player saves the game,
 * `D_801E7510` becomes 1, but if the player
 * is about to overwrite it, `D_801E750C`
 * is set to 1 and `D_801E7510` is set to 0. Once
 * the overwrite is confirmed, `D_801E750C`
 * is set to 0 and `D_801E7510` is set to 1. If the
 * player cancels the overwrite, these variables
 * maintain their values (`D_801E750C` as 1 and `D_801E7510` as 0).
 *
 * `D_801E7510` is also related to loading.
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

/** @brief Detects what memory cards are inserted, but seems
 * buggy, as it doesn't properly update when a memory
 * card is removed while the player is on the save screen.
 */
extern s16 D_801E756C[MEMORY_CARD_SLOT_COUNT];

/** @brief Count of elements that get hidden as the player scrolls
 * through displayed save elements in the slot.
 */
extern s16 g_HiddentElementByDisplacement[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7574[MEMORY_CARD_SLOT_COUNT];

/** @brief Stores the selected save in each slot.
 * Only the first two values are used.
 * The next values are possibly an unused
 * variable which Splat detects incorrectly
 * and merges it.
 */
extern s16 D_801E7578[MEMORY_CARD_SLOT_COUNT]; // `g_SelectedSaveOffsetsY`

extern s8 D_801E7584[SAVEGAME_COUNT_MAX * 2];

extern s8 g_PrevSaveIdx[MEMORY_CARD_SLOT_COUNT];

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

void Gfx_SaveSelectedDisplacement(s32 slotIdx, s32 arg1);

/** Draws the "FILE X" string in the save/load screen. */
void Gfx_SaveSlotDrawFileString(s32 arg0, s32 slotIdx, s32 fileId, s32 arg3);

/** Draws the string of the location where the save was done. */
void Gfx_SavegameEntryDrawLocationName(s_SavegameEntry* ptr, s32 arg1, s32 idx);

/** Sets the color of the string to be drawn based on some flag. */
s32 Gfx_SavegameEntryStringSetColor(s_SavegameMetadata* saveEntry);

void func_801E326C(s_SavegameEntry* saveEntry, s_SavegameEntry* nextSaveEntry, s32 saveIdx, s32 slotIdx);

void Gfx_MemCardStateDraw(s32 memCardState, s32 arg1);

/** Flashes savegame entry after saving sucessfully. */
void Gfx_SavegameEntryDrawFlash();

void func_801E43C8(s32 slotIdx);

/** Draws transparent background and scroll bar. */
void Gfx_SaveSlotDrawBox(s32 slotIdx, s32 saveCount, s32 selectedSaveIdx, s32 selectedSaveOffsetY);

/** Draws message box that says "Now checking MEMEORY CARD" or "MEMORY CARD is not inserted". */
void Gfx_SaveSlotDrawMemCardMsgBox(s32 slotIdx, s32 entryType);

void Gfx_SaveSlotDrawMemCardMsgBoxSub(s_LineBorder* borderLines, s_QuadBorder* borderGlowQuads, s_ColoredLine2d* coloredLine, s32 slotIdx);

/** Updates the save screen. */
void GameState_SaveScreen_Update();

void Savegame_FormatLogic();

void Savegame_LoadLogic();

void Savegame_ContinueLogic();

void Gfx_SavegameDrawBackground();

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
