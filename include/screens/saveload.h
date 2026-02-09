#ifndef _SCREENS_SAVELOAD_H
#define _SCREENS_SAVELOAD_H

/** @brief This header contains variables, structs, or
 * function specifically intended for the save and load screen.
 */

// ============
// ENUMERATORS
// ============

/** @brief Used by `g_SaveScreen_State`. */
typedef enum _SaveScreenState
{
    SaveScreenState_None   = 0,
    SaveScreenState_Format = 1,
    SaveScreenState_Save   = 2,
    SaveScreenState_Load   = 3
} e_SaveScreenState;

// ========
// GLOBALS
// ========

extern char* g_Savegame_SaveLocationNames[];

/** @brief Reduntant code. Some overwrite status.
 * Indicates if the player is or have overwritten
 * a save.
 *
 * This is used in a switch statement from
 * `SaveScreen_WriteOptionsStepDraw` with two cases:
 ** 0: Prepares to draw overwritting options message.
 ** 1: Draws overwritting options message.
 * However, the preparation is unnecessary as the only
 * useful thing it does is assigning the value of `0`
 * to `g_SaveScreen_MemCardStateDisplay`, the other
 * two things the code does are useless, most noticiably
 * it assign itself the value of `1`, however, this
 * is useless as the case 0 have fallthrough to the case 1.
 */
extern s32 g_SaveScreen_OverwriteActive;

/** @brief Reduntant code. Some display state status.
 * Indicates if memory card or a save state is
 * or have been display.
 *
 * This is used in a switch statement from
 * `SaveScreen_MemCardStateDraw` with two cases:
 ** 0: Prepares to draw process status message.
 ** 1: Draws process status message.
 * However, the preparation is unnecessary as the only
 * useful thing it does is assigning the value of `0`
 * to `g_SaveScreen_OverwriteActive` and updates some
 * global variables in case the memory card have been
 * disconnected during the load of a save, the other
 * two things the code does are useless. It assign itself
 * the value of `1`, however, the case 0 have fallthrough
 * to case 1 and it assign to `D_801E7554` the value
 * of the string index to be display, but it only used as
 * an unnecessary double check for updating the message
 * that indicates a save have been done successfully.
 */
extern s32 g_SaveScreen_MemCardStateDisplay;

/** @brief Dead code
 * Some boolean statuses for each save slot.
 *
 * This seems to be related to the color of the
 * borders of the file, but appears to do nothing
 * as the code only defines it as 1 or 0.
 * It might also be buggy as it constantly oscillates
 * between 0 and 1. For example:
 * in `SaveScreen_SavesSlotDraw`, the code has a conditional
 * that writes 1, but a little later
 * in the same function, it writes 1 again
 * without any conditional.
 */
extern s16 D_801E7514[MEMCARD_SLOT_COUNT_MAX];

/** @brief Broken code.
 * This is used in some way to determine the y position
 * of some save/memcard states strings from `e_SavegameEntryType`.
 * This code works in a strange way as it is multiplied by 20
 * and then it get 20 added, each time the function
 * `SaveScreen_SavesSlotDraw` is run it get +1 added to it's value until
 * it reaches 5 or if one of the elements to be draw is the last
 * element of the memory card.
 */
extern s16 D_801E7518[MEMCARD_SLOT_COUNT_MAX];

extern s32 g_SaveScreen_State; /** `e_SaveScreenState` */

/** @brief Timer used when displaying the text after finishing any of the following states:
 * - Formatting
 * - Saving
 * - Loading
 * - Error
 */
extern s32 g_SaveScreen_MemCardStateTextTimer;

extern void (*g_GameState_SaveScreen_Funcs[])(void);

extern bool g_SaveScreen_IsFormatting; // `false` - Overwrite, `true` - Format.

extern bool g_SaveScreen_IsNewSaveSelected; // `false` - User has `New save` selected, `true` - User has a save selected.

extern void (*g_GameState_AutoLoadSavegame_Funcs[])(void);

// ====================
// GLOBALS (BSS; Hack)
// ====================
// For matching the order of the BSS segment it is required to declare
// each variable as an extern in a determined order.
// This is done on the meanwhile we found a way to replicate `common`
// segment behaviour.

extern s32 D_801E7560;

/** @brief Dead code.
 * Only used when booting the save screen where both
 * values are defined as 0, the memory card is being
 * loaded, or the user has the last save selected in
 * the slot (where it asks if the value corresponding
 * to the slot is 0 to then overwrite it with 1).
 * 
 * Used in: `SaveScreen_MemCardInfoReset` and `SaveScreen_SavesSlotDraw`.
 */
extern s32 D_801E7564[MEMCARD_SLOT_COUNT_MAX];

/** @brief Dead code.
 * Constantly updates changing the value from 0 up to
 * the amount of files available in the slot.
 *
 * Code indicate that it is related the draw of file borders color.
 */
extern s16 D_801E756C[MEMCARD_SLOT_COUNT_MAX];

/** @brief Count of saves hidden as the user scrolls down
 * through the displayed saves in the slot.
 */
extern s16 g_SaveScreen_HiddenSaves[MEMCARD_SLOT_COUNT_MAX];

/** @brief Dead code.
 * The only usage it is given is to check it is in `SaveScreen_SavesSlotDraw`
 * where it is used to check if the value is not the same as
 * `g_SaveScreen_HiddenSaves` if the condition is true then it assigns
 * `D_801E7514` a true value. However, the only instance where a value
 * is assigned is when booting the save screen when it get assigned
 * the value of -1 so it's always realizing the conditional.
 */
extern s16 D_801E7574[MEMCARD_SLOT_COUNT_MAX];

/** @brief Stores the index of the element selected in each
 * slot based on what is visually available in the slot.
 *
 * For example: if the user has 9 savegames in the slot and
 * wants to create a new, separate savegame, the index of the
 * `New Save` element will be 4 and not 9 (index starting from 0)
 * as it is the fifth element visually available in the slot.
 */
extern s16 g_SaveScreen_VisualElementIdx[MEMCARD_SLOT_COUNT_MAX];

extern s8 D_801E757C[8];

/** @brief Dead code. */
extern s8 D_801E7584[SAVEGAME_COUNT_MAX * MEMCARD_SLOT_COUNT_MAX];

/** @brief Stores the index of the last save done.
 *
 * Depending on the slot where the last save was done
 * the value representing the other slot is turn into -1.
 */
extern s8 g_SaveScreen_LastSaveIdx[MEMCARD_SLOT_COUNT_MAX];

/** @brief Boolean. State if save information should be displayed. */
extern s8 g_SaveScreen_DisplaySaveInfo;

extern s8 D_801E76D1;

extern u8 g_SaveScreen_IsMemCardNotInserted[MEMCARD_SLOT_COUNT_MAX]; /** `bool` */

extern s8 g_SaveScreen_SaveFlashTimer;

extern u8 g_SaveScreen_IsNextFearMode;

extern u8 g_SaveScreen_IsGameSaving;

// ==========
// FUNCTIONS
// ==========

/** @brief Clears all variable states used by the save screen. */
void SaveScreen_ScreenInfoClear(void);

/** @brief Draws the bottom information rectangle.
 *
 * @note SH2 counterpart is name `mcDrawStatus`,
 * but a noticiable difference between both games is
 * that SH2 do not feature a background rectangle.
 */
void SaveScreen_SlotStrAndBottomRectDraw(void);

/** @brief Updates `g_SaveScreen_VisualElementIdx` based on the slot indicated.
 *
 * @param slotIdx Memory Card slot to update.
 * @param unused Intended to getting pass the total amount of elements in the slot.
 */
void SaveScreen_SelectedElementIdxUpdate(s32 slotIdx, s32 unused);

/** @brief Draws the "FILE X" string. */
void SaveScreen_FileIdxDraw(s32 saveIdx, s32 slotIdx, s32 fileId, s32 entryType);

/** @brief Update color of the save string to be drawn
 * and returns a boolean value stating if the save
 * is in "Next Fear" mode.
 *
 * @param saveEntry Save metadata entry being processed.
 * @return Returns true or false depending if the save is in "Next Fear" mode or not.
 */
bool SaveScreen_NextFearModeSave(s_MemCard_SaveMetadata* saveEntry);

/** @brief Draws location of saves. */
void SaveScreen_SaveLocationDraw(s_SaveScreen_Element* saveEntry, s32 saveIdx, s32 slotIdx);

/** @brief Draws saves borders. */
void SaveScreen_SaveBorder(s_SaveScreen_Element* saveEntry, s_SaveScreen_Element* nextSaveEntry, s32 saveIdx, s32 slotIdx);

/** @brief Draws saves, information and slots. */
void SaveScreen_SavesSlotDraw(s_SaveScreen_Element* saveEntry, s32 saveIdx, s32 slotIdx);

/** @brief Draws memory card state.
 *
 * @param g_SaveScreen_SaveScreenState `e_SaveScreenState`
 * @param memCardState `e_MemCardResult`
 */
void SaveScreen_MemCardStateDraw(s32 g_SaveScreen_SaveScreenState, s32 memCardState);

/** @brief Draws options writing options when the
 * player is overwriting a save or is formatting
 * the memory card.
 *
 * @param stringIdx String index used to determine to display the overwrite or format status options.
 * @param optionSelected Option currently selected by the player.
 */
void SaveScreen_WriteOptionsStepDraw(s32 stringIdx, bool optionSelected);

/** @brief Draws the flash that overlap saves after saving. */
void SaveScreen_SaveFlash(void); // 0x801E3E78

/** @brief Draws slot border.
 *
 * @note SH2 counterpart is name `mcDrawFrame`,
 * but in constrast with SH1 it draws the upper
 * text that indicates the slot.
 */
void SaveScreen_SlotBorder(void); // 0x801E4010

/** @brief Draws the shine which appears during an unusual
 * state where the memory card is "not formatted" and
 * `g_GameWork.gameState_594` is `GameState_SaveScreen`.
 *
 * @note Intended to be used alongside `SaveScreen_SlotStatusMsgDraw`.
 */
void SaveScreen_SlotStatusMsgShineDraw(s32 slotIdx);

/** @brief Draws slot's transparent background, scroll bar and selected element shine. */
void SaveScreen_NavigationDraw(s32 slotIdx, s32 saveCount, s32 selectedSaveIdx, s32 selectedSaveOffsetY);

/** @brief Draws a flash on the selected save menu entry after saving sucessfully. */
void Savegame_SaveEntryFlashDraw(void);

void SaveScreen_SaveBorderDraw(s_SaveScreen_Element* saveEntry, s_SaveScreen_Element* nextSaveEntry, s32 saveIdx, s32 slotIdx); // 0x801E4D90

/** @brief Defines parameters used to draw the message
 * box use when the memory card is in an unavailable state.
 *
 * For example: When loading the memory card or the memory card is not inserted.
 */
void SaveScreen_SlotStatusMsgDraw(s32 slotIdx, s32 entryType);

/** @brief Draws the message box use when the memory card
 * is in an unavailable state.
 */
void SaveScreen_SlotStatusMsgStepDraw(s_LineBorder* borderLines, s_QuadBorder* borderGlowQuads, s_ColoredLine2d* coloredLine, s32 slotIdx);

/** @brief Draws bottom information rectangle. */
void SaveScreen_RectSaveInfoDraw(s_Line2d* line); // 0x801E5898

/** @brief Draws save information or new save text in the bottom rectangle. */
void SaveScreen_ElementInfoDraw(s32 slotIdx, s32 selectedSaveIdx); // 0x801E5E18

/** @brief Updates the save screen. */
void GameState_LoadSavegameScreen_Update(void);

/** @brief Initialize save screen. */
void SaveScreen_Init(void);

/** Crucial for working with the overlay.
 *
 * `g_GameWork.gameStateStep_598[1]` defines the state:
 * 0 - The user can freely move through the save menu.
 * 1 - Triggers the overwrite save.
 * 2 - Player leaves the save screen.
 */
void SaveScreen_LogicUpdate(void);

void SaveScreen_FormatCard(void);

void SaveScreen_SaveGame(void);

void SaveScreen_LoadSave(void);

void SaveScreen_Continue(void);

/** @brief Draws background and triggers save info draw. */
void SaveScreen_BackgroundAndInfoDraw(void);

/** @brief Draws background and triggers save info draw. */
void SaveScreen_ScreenDraw(void);

/** @brief Handles the text that shows when formatting, saving, or loading a file.
 *
 *  Used in: `GameState_LoadSavegameScreen_Update` and `GameState_AutoLoadSavegame_Update`.
 */
void SaveScreen_MemCardState(void);

void SaveScreen_WriteOptionsDraw(s32 stringIdx, bool optionSelected);

/** @brief Updates the death load screen. */
void GameState_AutoLoadSavegame_Update(void);

void func_801E737C(void);

#endif
