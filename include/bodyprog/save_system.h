#ifndef _SAVE_SYSTEM_H
#define _SAVE_SYSTEM_H

#include "screens/saveload/saveload.h"

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the savegame system.
 */

// ================
// UNKNOWN STRUCTS
// ================

/* Struct called by functions that haven't been identified. */

typedef struct 
{
    u8 unk_0[315];
    u8 field_13B[15];
} s_func_8002F278;

typedef struct 
{
    s32                field_0[10][3];
    u8                 unk_78[132];
    s_ShSavegameFooter field_FC;
} s_func_8002FB64; // Likely `s_ShSaveUserConfigContainer`.

// ========
// STRUCTS
// ========

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 fileIdx_8;
    s32 saveIdx_C;
    s32 field_10;
    s32 field_14;
} s_800B5508_sub;

typedef struct
{
    //s_800B5508_sub*    field_0; // TODO: Use this instead.
    s32                field_0; // Pointer.
    s8                 field_4[16]; 
    struct s_800B5508* field_14;
    s32                field_18; 
} s_800B5508;

// https://github.com/Sparagas/Silent-Hill/blob/1f24eb097a4b99129bc7c9793d23c82244848a27/010%20Editor%20-%20Binary%20Templates/ps1_memory_card.bt#L122C8-L122C17
typedef struct
{
    char magic_0[2];
    u8   iconDisplayFlag_2;
    u8   blockCount_3;
    u16  titleNameShiftJIS_4[0x20];
    s8   field_44[0x1C];       // Reserved/unused?
    s8   iconPalette_60[0x20]; // CLUT data copied from TIM_IMAGE.caddr
    s8   textureData_80[0x20]; // Copied from TIM_IMAGE.paddr
    s8   unk_A0[0x160];
} s_PSXSaveBlock;
STATIC_ASSERT_SIZEOF(s_PSXSaveBlock, 0x200);

// ========
// GLOBALS
// ========

extern char D_80024B64;

extern u8 g_SlotElementSelectedIdx[MEMORY_CARD_SLOT_COUNT]; // 0 - Slot 1, 1 - Slot 2.

extern s8 g_SelectedSaveSlotIdx; // 0 - Slot 1, 1 - Slot 2.

extern u8 D_800A8D98[]; // TIM image for save file?

extern s8 D_800A97D7;

extern s8 D_800A97D8;

extern s8 D_800A97D9;

extern s32 D_800A97DC; // `e_SavegameEntryType`

extern s8 D_800A97E0;

extern u32 D_800A97E4[];

/** Declaration of the struct takes 224 bytes (0xE0 bytes in hex).
* It is possible that the full size of the struct
* is `0x1C/28` bytes, as `func_8002E94C`
* accesses element 8 and multiplies it by 28 to give 224.
* Additionally, investigating the RAM affirms
* that every `0x1C/28` bytes is the start address of a new element
* which the decompiled code seems to point to.
*/
extern s_800B5508 D_800B5508[];

/** @brief Basic information required to draw information of elements in save slots.
* Address access is based on the slot: Slot 1 - 0x801E09E0, Slot 2 - 0x801E1440.
*/
extern s_SavegameEntry* g_ActiveSavegameEntry;

extern u8 g_MemCardElementCount[MEMORY_CARD_SLOT_COUNT];

extern s32 D_800BCD18[];

extern s32 D_800BCD20[];

extern u32 D_800BCD34;

extern s8 D_800BCD38;

extern s8 D_800BCD39;

extern s16 g_MemCardsTotalElementCount; // Counts all elements of all inserted memory cards.

extern s8 D_800BCD40;

extern u8 g_SlotElementCounts[MEMORY_CARD_SLOT_COUNT];

extern u8 g_SelectedSaveIdx;

extern s8 g_SelectedFileIdx;

// ==========
// FUNCTIONS
// ==========

s32 func_8002E94C(s32 arg0, s32 arg1, s32 fileIdx, s32 saveIdx);

s32 func_8002E990();

/** Used to get the pointer of a struct which seems to be `s_SavegameMetadata`. */
s32 func_8002E9EC(s32 arg0, s32 fileIdx, s32 saveIdx);

s32 func_8002EA28(s32 idx);

s32 func_8002EA78(s32 idx);

s32 func_8002EABC(s32* arg0, s32* arg1, s32* arg2);

void func_8002EB88(); // Return type assumed.

void func_8002ECE0(s_800B55E8* arg0);

s32 func_8002F278(s32 arg0, s_func_8002F278* arg1);

void func_8002FB64(s_func_8002FB64 *arg0);

/** Copies user config into an `s_ShSaveUserConfigContainer` and calculates footer checksum. */
void Savegame_UserConfigCopyWithChecksum(s_ShSaveUserConfigContainer* dest, s_ShSaveUserConfig* src);

/** Copies savegame into an s_ShSavegameContainer and calculates footer checksum. */
void Savegame_CopyWithChecksum(s_ShSavegameContainer* dest, s_ShSavegame* src);

/** Updates the footer with the checksum of the given data. */
void Savegame_ChecksumUpdate(s_ShSavegameFooter* saveFooter, s8* saveData, s32 saveDataLength);

/** Generates a checksum of the given saveData and compares it against the checksum value in the footer.
 * Returns 1 if the checksums match, otherwise 0.
 */
s32 Savegame_ChecksumValidate(s_ShSavegameFooter* saveFooter, s8* saveData, s32 saveDataLength);

/** Generates an 8-bit XOR checksum over the given data, only appears used with s_ShSavegame data. */
u8 Savegame_ChecksumGenerate(s8* saveData, s32 saveDataLength);

/** Generates a save filename for the given save index. */
void Savegame_FilenameGenerate(char* dest, s32 saveIdx);

void func_800300B4(s_PSXSaveBlock* saveBlock, s8 blockCount, s32 saveIdx);

s32 func_80030288(s32 deviceId);

s32 func_8003030C(s32 deviceId);

s32 func_80030334(s32 deviceId, char* fileName);

s32 func_80030370(s32 deviceId, char* prevName, char* newName);

void func_800303E4();

void func_80030414();

void func_80030444();

void func_8003045C();

void func_80030530();

void func_80030640();

void func_80030668();

void func_800306C8();

void func_800307BC();

s32 func_80030734();

void func_800307BC();

s32 func_80030810();

void func_80030820();

void func_80030884();

void func_80030894();

void func_800308A4();

void func_800308B4();

void func_800308C4();

s32 func_800308D4();

s32 func_800309FC();

void func_80030A0C();

void Savegame_DevicePathGenerate(s32 deviceId, char* result);

#endif
