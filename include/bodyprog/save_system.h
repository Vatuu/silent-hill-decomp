#ifndef _SAVE_SYSTEM_H
#define _SAVE_SYSTEM_H

#include "screens/saveload/saveload.h"

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the savegame system.
 */

// ========
// ENUMS
// ========

typedef enum
{
    CardState_Idle          = 0,
    CardState_Init          = 1,
    CardState_Check         = 2,
    CardState_Load          = 3,
    CardState_DirRead       = 4,
    CardState_FileCreate    = 5,
    CardState_FileOpen      = 6,
    CardState_FileReadWrite = 7
} e_CardState;

typedef enum
{
    CardIoMode_Init    = 0,
    CardIoMode_DirRead = 1, // TODO: Not sure if this is actual purpose yet.
    CardIoMode_Read    = 2,
    CardIoMode_Write   = 3,
    CardIoMode_Create  = 4,
} e_CardIoMode;

// ================
// UNKNOWN STRUCTS
// ================

/* Struct called by functions that haven't been identified. */

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
    char fileNames_0[15][21];
    u8   blockCounts_13B[15]; // Size of each file in 8192 byte blocks.
} s_CardDirectory;

typedef struct
{
    s32 devicesPending_0; /** Bitfield of device IDs, each set bit index is an ID that must be read/inited first. */
    s32 state_4;          /** `e_CardState` */
    s32 stateStep_8;
    s32 stateResult_C;
    s32 eventSwSpIOE_10;
    s32 eventSwSpERROR_14;
    s32 eventSwSpTIMOUT_18;
    s32 eventSwSpNEW_1C;
    s32 eventHwSpIOE_20;
    s32 eventHwSpERROR_24;
    s32 eventHwSpTIMOUT_28;
    s32 eventHwSpNEW_2C;
    s32 eventHwSpUNKNOWN_30;
    s32 lastEventHw_34;
    s32 cardIoMode_38; /** `e_CardIoMode` */
    s32 deviceId_3C;

    s_CardDirectory* cardDirectory_40; /** Array of files on the card, pointer supplied by caller to `Savegame_CardRequest`. */

    char  filePath_44[28];
    s32   createBlockCount_60; /** Block count passed to `open` when creating new file. */
    s32   seekOffset_64;
    void* dataBuffer_68;
    s32   dataSize_6C;
    s32   field_70;
    s32   fileHandle_74;
    s32   retryCount_78;
    s32   field_7C;
} s_800B5488;
STATIC_ASSERT_SIZEOF(s_800B5488, 128);

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
    s32                field_0; // Sometimes it's a pointer to a struct, sometimes is just a simple number.
    s8                 field_4[16]; 
    struct s_800B5508* field_14;
    s32                field_18; 
} s_800B5508;

typedef struct
{
    s32 field_0;
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s32 field_10;
    s32 field_14; // Pointer to a `s_800B55E8` static struct.
} s_800B55E8;

// https://github.com/Sparagas/Silent-Hill/blob/1f24eb097a4b99129bc7c9793d23c82244848a27/010%20Editor%20-%20Binary%20Templates/ps1_memory_card.bt#L122C8-L122C17
typedef struct
{
    char magic_0[2];
    u8   iconDisplayFlag_2;
    u8   blockCount_3;
    u16  titleNameShiftJis_4[32];
    s8   field_44[28];       // Reserved/unused?
    s8   iconPalette_60[32]; // CLUT data copied from `TIM_IMAGE.caddr`.
    s8   textureData_80[32]; // Copied from `TIM_IMAGE.paddr`.
    s8   unk_A0[352];
} s_PsxSaveBlock;
STATIC_ASSERT_SIZEOF(s_PsxSaveBlock, 512);

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

extern s_800B55E8 D_800B2780[];

extern s_800B55E8 D_800B3680[];

extern s_800B55E8 D_800B4580[];

extern s32 D_800B5480;

extern s_800B5488 D_800B5488; // SaveWork?

/** Declaration of the struct takes 224 bytes (0xE0 bytes in hex).
 * It is possible that the full size of the struct
 * is `0x1C/28` bytes, as `func_8002E94C` accesses 8 elements
 * and by multiplying 8 by 28 to gives 224.
 *
 *
 *
 * Additionally, investigating the RAM affirms that every
 * `0x1C/28` bytes is the start address of a new element
 * which the decompiled code seems to point to.
 */
extern s_800B5508 D_800B5508[8];

extern s_800B55E8 D_800B55E8[2];

extern s32 D_800B55FC;

/** @brief Basic information required to draw information of elements in save slots.
 * Address access is based on the slot: Slot 1 - 0x801E09E0, Slot 2 - 0x801E1440.
 * 
 * @note Macros for it's references can be found in `saveload.h` as:
 * `SAVEGAME_ENTRY_BUFFER_0`
 * `SAVEGAME_ENTRY_BUFFER_1`
 */
extern s_SavegameEntry* g_ActiveSavegameEntry; // 0x800BCD2C

extern u8 g_MemCardElementCount[MEMORY_CARD_SLOT_COUNT]; // 0x800BCD30

extern s32 D_800BCD18[];

extern s32 D_800BCD20[];

extern u32 D_800BCD34;

extern s8 g_SaveScreenPlayerState; // 2 - Saving, 3 - Loading.

extern s8 D_800BCD39;

extern s16 g_MemCardsTotalElementCount; // Counts all elements of all inserted memory cards.

extern s8 D_800BCD40;

extern u8 g_SlotElementCount[MEMORY_CARD_SLOT_COUNT];

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

s32 func_8002F278(s32 arg0, s_CardDirectory* arg1);

void func_8002FB64(s_func_8002FB64 *arg0);

/** Copies user config into an `s_ShSaveUserConfigContainer` and calculates footer checksum. */
void Savegame_UserConfigCopyWithChecksum(s_ShSaveUserConfigContainer* dest, s_ShSaveUserConfig* src);

/** Copies savegame into an s_ShSavegameContainer and calculates footer checksum. */
void Savegame_CopyWithChecksum(s_ShSavegameContainer* dest, s_ShSavegame* src);

void func_8002FD5C(s32 arg0, s32 arg1, s32 arg2);

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

void Savegame_SaveBlockInit(s_PsxSaveBlock* saveBlock, s8 blockCount, s32 saveIdx);

s32 Savegame_CardDeviceTest(s32 deviceId);

s32 Savegame_CardDeviceFormat(s32 deviceId);

s32 Savegame_CardFileErase(s32 deviceId, char* fileName);

s32 Savegame_CardFileRename(s32 deviceId, char* prevName, char* newName);

void Savegame_CardInit();

void Savegame_CardEventsInit();

void Savegame_CardStateInit();

void Savegame_CardSwEventsInit();

void Savegame_CardHwEventsInit();

void Savegame_CardEventsClose();

void Savegame_CardSwEventsClose();

void Savegame_CardHwEventsClose();

s32 Savegame_CardSwEventsTest();

void Savegame_CardSwEventsReset();

s32 Savegame_CardHwEventsTest();

void Savegame_CardHwEventsReset();

void Savegame_CardHwEventSpIOE();

void Savegame_CardHwEventSpERROR();

void Savegame_CardHwEventSpNEW();

void Savegame_CardHwEventSpTIMOUT();

void Savegame_CardHwEventSpUNKNOWN();

s32 Savegame_CardResult();

s32 Savegame_CardRequest(e_CardIoMode mode, s32 deviceId, s_CardDirectory* outDirectory, char* fileName, s32 createBlockCount, s32 fileOffset, s32 outBuffer, s32 outSize);

s32 Savegame_CardIsIdle();

void Savegame_CardUpdate();

s32 Savegame_CardState_1();

s32 Savegame_CardState_2();

s32 Savegame_CardState_3();

s32 Savegame_CardState_4();

s32 Savegame_CardState_5();

s32 Savegame_CardState_6();

s32 Savegame_CardState_7();

void Savegame_DevicePathGenerate(s32 deviceId, char* result);

#endif
