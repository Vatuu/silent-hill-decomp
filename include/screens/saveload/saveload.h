#ifndef _SAVELOAD_H
#define _SAVELOAD_H

#include "common.h"

#define MEMORY_CARD_SLOT_COUNT 2
#define SAVE_COUNT_MAX         165

typedef struct
{
    s32                    unk_0;
    s32                    unk_4;
    s32                     field_8; // Maybe bitfield.
    //struct s_UnkSaveload0* field_9;
} s_UnkSaveload0; // Size: >=12

typedef struct
{
    u8 field_0[25];
} s_801E2728;

extern s_FsImageDesc D_800A902C;

extern s8 D_800A97D8;

extern s32 D_800B9FE0[];

extern u32 D_800BCD34;

extern s8 D_800BCD39;

extern s_801E2728 D_801E2728; // Probably an array instead.

extern char* D_801E74A8[];

extern s32 D_801E750C;

extern s32 D_801E7510;

extern s16 D_801E7514[MEMORY_CARD_SLOT_COUNT];

extern s16 D_801E7518[MEMORY_CARD_SLOT_COUNT];

extern s32 D_801E751C;

extern s32 D_801E7520;

extern void (*D_801E7524[])(); // func table

extern void (*D_801E7544[])(); // func table

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

extern s8 D_801E76D6;

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

void func_801E4D90(s8* arg0, s8* arg1, s32 arg2, s32 arg3);

void GameState_Unk8_Update();

void func_801E63C0();

void func_801E709C();

void func_801E70C8();

void func_801E7244();

void func_801E72DC();

void GameState_Unk4_Update();

void func_801E737C();

#endif
