#ifndef _MEMCARD_H
#define _MEMCARD_H

#include "screens/saveload/saveload.h"

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the savegame and memory card system (not from PSY-Q SDK).
 */

#define CARD_DEVICE_COUNT      8
#define CARD_DEVICE_FILE_COUNT 15

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
    s32 field_0;
    s32 fileIdx_4;
    s32 saveIdx_8;
} s_func_8002FE70;

// ========
// STRUCTS
// ========

typedef struct
{
    s32                field_0;
    s_SavegameMetadata savegameMetadatas_4[11];
    s8                 unk_88[116];
    s_ShSavegameFooter field_FC;
} s_MemCardInfo_BasicSaveInfo;
STATIC_ASSERT_SIZEOF(s_MemCardInfo_BasicSaveInfo, 256);

typedef struct
{
    char filenames_0[CARD_DEVICE_FILE_COUNT][21];
    u8   blockCounts_13B[CARD_DEVICE_FILE_COUNT]; // Size of each file in 8192 byte blocks.
} s_CardDirectory;

typedef struct
{
    s32 devicesPending_0; /** Bitfield of device IDs, each set bit index is an ID that must be read/initialized first. */
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
} s_CardWork;
STATIC_ASSERT_SIZEOF(s_CardWork, 128);

typedef struct
{
    s32                          memoryCardStatus_0;
    s8                           isFileUsed_4[16]; 
    s_MemCardInfo_BasicSaveInfo* basicSaveInfo_14;
    s32                          field_18;
} s_MemCardBasicInfo;
STATIC_ASSERT_SIZEOF(s_MemCardBasicInfo, 28);

typedef struct
{
    s32 field_0;
    s32 deviceId_4;
    s32 fileIdx_8;
    s32 saveIdx_C;
    s32 field_10;
    s32 lastCardResult_14;
} s_800B55E8;
STATIC_ASSERT_SIZEOF(s_800B55E8, 24);

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

typedef struct
{
    s_MemCardBasicInfo          devices_0[CARD_DEVICE_COUNT];
    s_800B55E8                  field_E0[2];
    s32                         field_110;
    u8                          unk_114[4];
    s_PsxSaveBlock              saveBlock_118;
    s_MemCardInfo_BasicSaveInfo saveInfo_318;
    s_ShSaveUserConfigContainer userConfig_418;
    s_ShSavegameContainer       saveGame_498;
} s_800B5508;
STATIC_ASSERT_SIZEOF(s_800B5508, 1816);

// ========
// GLOBALS
// ========

extern u8 g_SlotElementSelectedIdx[MEMORY_CARD_SLOT_COUNT]; // 0 - Slot 1, 1 - Slot 2.

extern s8 g_SelectedSaveSlotIdx; // 0 - Slot 1, 1 - Slot 2.

extern u8 D_800A8D98[]; // TIM image for save file?

extern s8 D_800A97D7;

extern s8 D_800A97D8;

extern s8 D_800A97D9;

extern s32 D_800A97DC; // `e_SavegameEntryType`

extern s8 D_800A97E0;

extern u32 D_800A97E4[];

extern s_MemCardInfo_BasicSaveInfo g_MemCard_1_BasicSaveInfo[CARD_DEVICE_FILE_COUNT];

extern s_MemCardInfo_BasicSaveInfo g_MemCard_2_BasicSaveInfo[CARD_DEVICE_FILE_COUNT];

extern s_CardDirectory D_800B2628;

extern s32 D_800B2774;

extern s32 D_800B2778;

extern s_MemCardInfo_BasicSaveInfo D_800B4580[CARD_DEVICE_FILE_COUNT];

extern s32 D_800B5480;

extern s_CardWork g_CardWork; // 0x800B5488

/** Declaration of the struct takes 224 bytes (0xE0 bytes in hex).
 * It is possible that the full size of the struct
 * is `0x1C/28` bytes, as `func_8002E94C` accesses 8 elements,
 * and multiplying 8 by 28 gives 224.
 *
 * Additionally, investigating the RAM affirms that every
 * `0x1C/28` bytes is the start address of a new element,
 * which the decompiled code seems to point to.
 */
extern s_800B5508 D_800B5508;

/** @brief Basic information required to draw information of elements in save slots.
 * Address access is based on the slot: slot 1 = 0x801E09E0, slot 2 = 0x801E1440.
 * 
 * @note Macros for its references are in `saveload.h`:
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

void Savegame_CardCleanInit();

void Savegame_GameMemDataClear(s32 deviceId);

void Savegame_CardFileUsageClear(s32 deviceId);

s32 func_8002E76C(s32 deviceId);

void func_8002E7BC();

void func_8002E830();

void func_8002E85C();

void func_8002E86C();

s32 func_8002E898();

void func_8002E8D4();

void func_8002E8E4();

s32 func_8002E914();

s32 func_8002E94C(s32 arg0, s32 deviceId, s32 fileIdx, s32 saveIdx);

s32 func_8002E990();

s32 func_8002E9A0(s32 deviceId);

s_SavegameMetadata* func_8002E9EC(s32 deviceId, s32 fileIdx, s32 saveIdx);

s32 func_8002EA28(s32 deviceId);

s32 func_8002EA78(s32 deviceId);

s32 func_8002EABC(s32* outDeviceId, s32* outFileIdx, s32* outSaveIdx);

void func_8002EB88(); // Return type assumed.

void func_8002ECE0(s_800B55E8* arg0);

void func_8002ED7C(s_800B55E8* arg0);

s32 func_8002F278(s32 deviceId, s_CardDirectory* dir);

void func_8002F2C4(s_800B55E8* arg0);

void func_8002F61C(s_800B55E8* arg0);

void func_8002FB64(s_MemCardInfo_BasicSaveInfo* arg0);

/** Copies user config into an `s_ShSaveUserConfigContainer` and calculates footer checksum. */
void Savegame_UserConfigCopyWithChecksum(s_ShSaveUserConfigContainer* dest, s_ShSaveUserConfig* src);

s32 func_8002FC3C(s32 deviceId);

/** Copies savegame into an s_ShSavegameContainer and calculates footer checksum. */
void Savegame_CopyWithChecksum(s_ShSavegameContainer* dest, s_ShSavegame* src);

void func_8002FD5C(s32 deviceId, s32 fileIdx, s32 saveIdx, s_ShSavegame* arg3);

void func_8002FDB0(s32 deviceId, s32 fileIdx, s32 saveIdx);

void func_8002FE70(s32 deviceId, s_func_8002FE70* result);

/** Updates the footer with the checksum of the given data. */
void Savegame_ChecksumUpdate(s_ShSavegameFooter* saveFooter, s8* saveData, s32 saveDataLength);

/** Generates a checksum of the given saveData and compares it against the checksum value in the footer.
 * Returns 1 if the checksums match, otherwise 0.
 */
s32 Savegame_ChecksumValidate(s_ShSavegameFooter* saveFooter, s8* saveData, s32 saveDataLength); // 0x8002FF74

/** Generates an 8-bit XOR checksum over the given data, only appears used with s_ShSavegame data. */
u8 Savegame_ChecksumGenerate(s8* saveData, s32 saveDataLength);

/** Generates a save filename for the given save index. */
void Savegame_FilenameGenerate(char* dest, s32 saveIdx);

void Savegame_SaveBlockInit(s_PsxSaveBlock* saveBlock, s8 blockCount, s32 saveIdx, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);

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

s32 Savegame_CardRequest(e_CardIoMode mode, s32 deviceId, s_CardDirectory* outDir, char* filename, s32 createBlockCount, s32 fileOffset, void* outBuf, s32 bufSize);

s32 Savegame_CardIsIdle();

void Savegame_CardUpdate();

s32 Savegame_CardState_Init();

s32 Savegame_CardState_Check();

s32 Savegame_CardState_Load();

s32 Savegame_CardState_DirRead();

s32 Savegame_CardState_FileCreate();

s32 Savegame_CardState_FileOpen();

s32 Savegame_CardState_FileReadWrite();

void Savegame_DevicePathGenerate(s32 deviceId, char* res);

#endif
