#ifndef _SAVE_SYSTEM_H
#define _SAVE_SYSTEM_H

#include "screens/saveload/saveload.h"

/** @brief
* This file is used for define any variable, struct and
* function that is part of `BODYPROG.BIN` and has been
* identified to be related to the save game system.
*/

typedef struct 
{
    s32                field_0[10][3];
    u8                 unk_78[132];
    s_ShSavegameFooter field_FC;
} s_func_8002FB64;

extern u8 g_SaveSelectedIdx[MEMORY_CARD_SLOT_COUNT]; // Selected save index. [0] - Slot 1, [1] - Slot 2.

extern s8 g_SlotSelectedIdx; // Selected save slot index. 0 - Slot 1, 1 - Slot 2

extern s8 D_800A97D7;

extern s8 D_800A97D8;

extern s_UnkSaveload0* D_800BCD2C[]; // Type assumed.

extern s16 D_800BCD3A; // Similar to `D_800BCD30` it counts all saves and includes the `New save` to the sum.

extern u8 g_SaveCount[MEMORY_CARD_SLOT_COUNT]; // Saves count for each slot.

extern u8 D_800BCD30[]; // It counts saves and the space to make a new save.

extern u32 D_800BCD34;

extern s8 D_800BCD38;


// ==========
// FUNCTIONS
// ==========


s32 func_8002E990();

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