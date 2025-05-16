#ifndef _SAVELOAD_H
#define _SAVELOAD_H

#include "common.h"

#define MEMORY_CARD_SLOT_COUNT 2
#define SAVE_COUNT_MAX         165

typedef struct
{
    s32                    unk_0;
    s32                    unk_4;
    s32                    field_8; // Maybe bitfield.
    struct s_UnkSaveload0* field_C;
} s_UnkSaveload0; // Size: >=12

typedef struct
{
    DVECTOR field_0;
    DVECTOR field_4;
} s_func_801E5898;

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

extern s8 D_800A97D7;

extern s8 D_800A97D8;

extern s32 D_800B9FE0[];

extern u32 D_800BCD34;

extern u8 D_800BCD3C[];

extern s8 D_800BCD39;

extern u8 D_800BCD3C[];

extern char* D_801E74A8[];

extern s32 D_801E750C;

extern s32 D_801E7510;

extern s16 D_801E7514[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7518[MEMORY_CARD_SLOT_COUNT];

extern s32 D_801E751C;

extern s32 D_801E7520;

extern void (*D_801E7524[])(); // func table

extern void (*D_801E7544[])(); // func table

extern s32 D_801E7554;

extern s32 D_801E7558;

extern s32 D_801E7564[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E756C[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7570[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7574[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7578[MEMORY_CARD_SLOT_COUNT];

extern s8 D_801E7584[];

extern s8 D_801E76D0;

extern s8 D_801E76D2[MEMORY_CARD_SLOT_COUNT];

extern s8 D_801E76D4;

extern u8 D_801E76D5;

extern u8 D_801E76D6;

extern s8 D_801E76CE[MEMORY_CARD_SLOT_COUNT];

/** Clears all saves? */
void func_801E2D8C();

void func_801E2F90(s32 saveSlotIdx);

// TODO: Rename to `SaveLoad_FileStringDraw`.
/** Draws the "FILE X" string in the save/load screen. */
void func_801E2FCC(s32 arg0, s32 saveSlotIdx, s32 fileId, s32 arg3);

/** Draws some string. */
void func_801E30C4(s_UnkSaveload0* ptr, s32 arg1, s32 idx);

/** Sets the color of the string to be drawn based on some flag. */
s32 func_801E3078(s_UnkSaveload0* arg0);

void func_801E326C(s8* arg0, s8* arg1, s32 arg2, s32 arg3);

void func_801E3910(s32 arg0, s32 arg1);

void Gfx_SavesTransparentBgDraw(s8* arg0, s8* arg1, s32 arg2, s32 arg3);

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

/** Draws "Now saving..." and "Finished saving." strings. Handle something else too.
 *  Used in `GameState_SaveScreen_Update` and `GameState_DeathLoadScreen_Update`.
 */
void func_801E7244();

void func_801E72DC();

/** Updates the death load screen. */
void GameState_DeathLoadScreen_Update();

void func_801E737C();

#endif
