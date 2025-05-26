#ifndef _SAVELOAD_H
#define _SAVELOAD_H

#include "common.h"

#define MEMORY_CARD_SLOT_COUNT 2
#define SAVE_COUNT_MAX         165

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
    u16 field_8;
    u16 field_A;
    u16 field_C;
    u16 pad_E;
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

extern char* D_801E74A8[];

extern s32 D_801E750C;

extern s32 D_801E7510;

extern s16 D_801E7514[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7518[MEMORY_CARD_SLOT_COUNT];

extern s32 g_MemCardState; // Format: 1, Save: 2, Load: 3

/** @brief Timer used when displaying the text after finishing any of the following states:
* - Formatting
* - Saving
* - Loading
* - Error
*/
extern s32 g_MemCardStateTextTimer;

extern void (*D_801E7524[])(); // func table

extern s32 D_801E753C;

extern s32 D_801E7540;

extern void (*D_801E7544[])(); // func table

extern s32 D_801E7554;

extern s32 D_801E755C;

extern s32 D_801E7558;

extern s32 D_801E7564[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E756C[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7570[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7574[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7578[6];

extern s8 D_801E7584[];

extern s8 D_801E76CE[MEMORY_CARD_SLOT_COUNT];

extern s8 g_DisplaySaveDataInfo;

extern s8 D_801E76D2[MEMORY_CARD_SLOT_COUNT];

extern s8 D_801E76D4;

extern u8 D_801E76D5;

extern u8 D_801E76D6;

/** Clears all saves? */
void func_801E2D8C();

void Gfx_SaveSelectedDisplacement(s32 saveSlotIdx, s32 arg1);

/** Draws the "FILE X" string in the save/load screen. */
void Gfx_SaveFileSelectedDraw(s32 arg0, s32 saveSlotIdx, s32 fileId, s32 arg3);

/** Draws some string. */
void func_801E30C4(s_UnkSaveload0* ptr, s32 arg1, s32 idx);

/** Sets the color of the string to be drawn based on some flag. */
s32 func_801E3078(s_UnkSaveload1* arg0);

void func_801E326C(s_UnkSaveload0* arg0, s_UnkSaveload0* arg1, s32 arg2, s32 arg3);

void Gfx_MemCardStateDraw(s32 memCardState, s32 arg1);

/** Produces the flicker over the saved game after saving sucessfully. */
void Gfx_SavedFlickerDraw();

void func_801E43C8(s32 arg0);

void Gfx_SavesTransparentBgDraw(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_801E52D8(s32 arg0, s32 arg1);

void Gfx_RectMemLoadDraw(s_801E2CAC* arg0, s_801E2CCC* arg1, s_801E2C8C* arg2, s32 arg3);

/** Updates the save screen. */
void GameState_SaveScreen_Update();

void func_801E63C0();

void func_801E69E8();

void func_801E6DB0();

void func_801E6F38();

/** Draws "SLOT1"/"SLOT2" strings, bottom transparent frame, and background image.*/
void Gfx_SaveBackground(); // 0x801E709C

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

void func_801E649C();

void func_801E6B18();

#endif
