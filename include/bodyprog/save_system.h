#ifndef _SAVE_SYSTEM_H
#define _SAVE_SYSTEM_H

#include "screens/saveload/saveload.h"

/** @brief
* This file is used for define any variable, struct and
* function that is part of `BODYPROG.BIN` and has been
* identified to be related to the save game system.
*/

// ================
// UNKNOWN STRUCTS
// ================
/* Struct called by functions
that haven't been recognized */

typedef struct 
{
    u8  unk_0[315];
    u8  field_13B[15];
} s_func_8002F278;

typedef struct 
{
    s32                field_0[10][3];
    u8                 unk_78[132];
    s_ShSavegameFooter field_FC;
} s_func_8002FB64;


// ========
// STRUCTS
// =========


typedef struct
{
    s32                field_0; // Pointer
    s8                 field_4[16]; 
    struct s_800B5508* field_14;
    s32                field_18; 
} s_800B5508;


// ========
// GLOBALS
// ========

extern u8 g_SaveSelectedIdx[MEMORY_CARD_SLOT_COUNT]; // Selected save index. [0] - Slot 1, [1] - Slot 2.

extern s8 g_SlotSelectedIdx; // Selected save slot index. 0 - Slot 1, 1 - Slot 2.

extern s8 D_800A97D7;

extern s8 D_800A97D8;

/**
* Declaration of the struct takes 224 bytes (0xE0 bytes in hex).
* It is possible that the full size of the struct
* it is 0x1C/28 bytes as function `func_8002E94C`
* access to the element 8 and multiplying it by 28 
* equals 224 bytes.
* Additionally, investigating the ram could reaffirm
* that as at some point of the memory each 1C/28 bytes
* an address is repeated in the space assigned for the
* struct which the decompiled code seems to be pointing
* as the first element of the struct.
*/
extern s_800B5508 D_800B5508[];

/** @brief
* Supposition: access basic information required for draw
* information of saves.
* Addreses accessed based on the slot: Slot 1 - 0x801E09E0, Slot 2 - 0x801E1440.
*/
extern s_UnkSaveload0* D_800BCD2C;

extern u8 D_800BCD30[]; // Counts saves and the space to make a new save.

extern u32 D_800BCD34;

extern s8 D_800BCD38;

extern s8 D_800BCD39;

extern s16 D_800BCD3A; // Similar to `D_800BCD30` it counts all saves and includes the `New save` to the sum.

extern s8 D_800BCD40;

extern u8 g_SaveCount[MEMORY_CARD_SLOT_COUNT]; // Saves count for each slot.

extern u8 g_SelectedSaveIdx;

extern s8 g_SelectedFileIdx;

// ==========
// FUNCTIONS
// ==========

s32 func_8002E94C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_8002E990();

/** This function is use to get the pointer of a struct which seems to be `s_UnkSaveload1`. */
s32 func_8002E9EC(s32 arg0, s32 arg1, s32 arg2);

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


#endif