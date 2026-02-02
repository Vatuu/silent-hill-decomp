#ifndef _MEMCARD_H
#define _MEMCARD_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the memory card system (not from PSY-Q SDK).
 */

#define MEMCARD_UNK_STATE_SAVE 2
#define MEMCARD_UNK_STATE_LOAD 3

#define CARD_DEVICE_COUNT      8
#define CARD_DEVICE_FILE_COUNT 15

#define MemCard_StatusGet(status, deviceIdx) \
    status >> (deviceIdx * 3) & 0x7

#define MemCard_StatusStore(status, deviceIdx) \
    status << (deviceIdx * 3)

#define MemCard_FileStatusGet(status, deviceIdx) \
    status >> (deviceIdx * 2) & 0x3

#define MemCard_FileStatusStore(status, deviceIdx) \
    status << (deviceIdx * 2)

// ============
// ENUMERATORS
// ============

typedef enum _MemCardProcess
{
    MemCardProcess_None = 0,
    MemCardProcess_Init = 1,
    MemCardProcess_Load_Game = 2,
    MemCardProcess_Save_3 = 3,
	MemCardProcess_Load_Settings = 4,
	MemCardProcess_Save_5 = 5,
	MemCardProcess_Format = 6
} e_MemCardProcess;

typedef enum _UnkMemCardState1
{
    UnkMemCardState1_0  = 0,
    UnkMemCardState1_1  = 1,
    UnkMemCardState1_2  = 2,
    UnkMemCardState1_3  = 3,
	UnkMemCardState1_4  = 4,
	UnkMemCardState1_5  = 5,
	UnkMemCardState1_6  = 6,
	UnkMemCardState1_7  = 7,
	UnkMemCardState1_8  = 8,
	UnkMemCardState1_9  = 9,
	UnkMemCardState1_10 = 10
} e_UnkMemCardState1;

typedef enum _FileState
{
    FileState_Unused  = 0,
    FileState_Used    = 1,
    FileState_Unk2    = 2,
    FileState_Damaged = 3
} e_FileState;

typedef enum _CardState
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

typedef enum _MemCardIoMode
{
    MemCardIoMode_Init    = 0,
    MemCardIoMode_DirRead = 1, // TODO: Not sure if this is actual purpose yet.
    MemCardIoMode_Read    = 2,
    MemCardIoMode_Write   = 3,
    MemCardIoMode_Create  = 4,
} e_MemCardIoMode;

typedef enum _MemCardResult
{
    MemCardResult_NotConnected    = 0,   /** "Card not connected". */
    MemCardResult_Success         = 1,   /** Default code returned when no errors occur. */
    MemCardResult_InitError       = 2,   /** `MemCard_State_Init` `EvSpNEW` "No writing after connection". */
    MemCardResult_InitComplete    = 3,   /** `MemCard_State_Init` `EvSpIOE` "Connected". */
    MemCardResult_LoadError       = 4,   /** `MemCard_State_Load` `EvSpNEW` "Uninitialized card". */
    MemCardResult_NewDevice       = 5,   /** `MemCard_State_DirRead` when `g_MemCard_Work.hasNewDevice_70`. */
    MemCardResult_NoNewDevice     = 6,   /** `MemCard_State_DirRead` when `!g_MemCard_Work.hasNewDevice_70`. */
    MemCardResult_FileCreateError = 7,   /** `MemCard_State_FileCreate` after 15 retries. */
    MemCardResult_FileOpenError   = 8,   /** `MemCard_State_FileOpen` after 15 retries. */
    MemCardResult_FileSeekError   = 9,   /** `MemCard_State_FileReadWrite` after 15 retries. */
    MemCardResult_FileIoError     = 10,  /** `MemCard_State_FileReadWrite` after 15 retries. */
    MemCardResult_FileIoComplete  = 11,  /** `MemCard_State_FileReadWrite` `EvSpIOE` "Completed". */
    MemCardResult_Full            = 100, /** Used outside main memcard code. */
    MemCardResult_DamagedData     = 101  /** Used outside main memcard code. */
} e_MemCardResult;

// ========
// STRUCTS
// ========

typedef struct
{
    s32 totalSavegameCount_0;
    s32 fileIdx_4;
    s32 saveIdx_8;
} s_MemCard_TotalSavesInfo;

/** @note Oddly fortunate event in the OPM16 build there
 * are some strings related to this split which indicate
 * the name of 6 structs. Those split names being:
 * * MCM_FUNC_WORK
 * * MC_FILE
 * * SCE_HEADER
 * * MC_HEADER
 * * MC_CONFIG
 * * MC_PROGRESS
*/

typedef struct
{
    s32                 unk_0;
    s_Savegame_Metadata saveMetadata_4[11]; // SAVEGAME_SLOT_COUNT_MAX
    s8                  unk_88[116];
    s_Savegame_Footer   footer_FC;
} s_MemCard_SaveHeader;
STATIC_ASSERT_SIZEOF(s_MemCard_SaveHeader, 256);

typedef struct
{
    char filenames_0[CARD_DEVICE_FILE_COUNT][21];
    u8   blockCounts_13B[CARD_DEVICE_FILE_COUNT]; // Size of each file in 8192 byte blocks.
    s8   pad_14C[2];
} s_MemCard_Directory;
STATIC_ASSERT_SIZEOF(s_MemCard_Directory, 332);

typedef struct
{
    s32 devicesPending_0; /** Bitfield of device IDs, each set bit index is an ID that must be read/initialized first. */
    s32 state_4;          /** `e_CardState` */
    s32 stateStep_8;
    s32 stateResult_C;    /** `e_MemCardResult` */
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
    s32 MemCardIoMode_38; /** `e_MemCardIoMode` */
    s32 deviceId_3C;

    s_MemCard_Directory* directories_40; /** Array of files on the card, pointer supplied by caller to `MemCard_WorkSet`. */

    char  filePath_44[28];
    s32   createBlockCount_60; /** Block count passed to `open` when creating new file. */
    s32   seekOffset_64;
    void* dataBuffer_68;
    s32   dataSize_6C;
    bool  hasNewDevice_70;
    s32   fileHandle_74;
    s32   retryCount_78;
    s32   field_7C;
} s_MemCard_Work;
STATIC_ASSERT_SIZEOF(s_MemCard_Work, 128);

typedef struct
{
    s32                   status_0;
    s8                    fileState_4[CARD_DEVICE_FILE_COUNT];
    s_MemCard_SaveHeader* saveHeader_14; /** Slots saves information. */
    s32                   fileLimit_18;  /** Max count of files allowed in the memory card. */
} s_MemCard_DeviceInfo;
STATIC_ASSERT_SIZEOF(s_MemCard_DeviceInfo, 28);

/** @note Some memory card states information. Related to `s_Savegame_Entry`.
 * Very likely used only for process related to memory cards.
 */
typedef struct
{
    s32 processId_0;          /** e_MemCardProcess. */
    s32 deviceId_4;
    s32 fileIdx_8;
    s32 saveIdx_C;            /** Index of the save in a determined file. */
    s32 processState_10;      /** States related to specific memory card events. */
    s32 lastMemCardResult_14; /** `e_MemCardResult` */
} s_MemCard_Process;
STATIC_ASSERT_SIZEOF(s_MemCard_Process, 24);

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

// OPM16 has `MCM_FUNC_WORK` struct with size 0x6D8, close to this 0x718.
typedef struct
{
    s_MemCard_DeviceInfo   devices_0[CARD_DEVICE_COUNT];
    s_MemCard_Process      saveWork_E0[2]; // This seems to be used mainly for processes. Element 0 is used for general processes while 1 is exclusively used for 
    s32                    memCardInitalized_110;
    s32                    unk_114;
    s_PsxSaveBlock         saveBlock_118;
    s_MemCard_SaveHeader   saveInfo_318;
    s_Savegame_UserConfigs userConfig_418;
    s_Savegame_Container   saveGame_498;
} s_MemCard_SaveWork;
STATIC_ASSERT_SIZEOF(s_MemCard_SaveWork, 1816);

// ========
// GLOBALS
// ========

extern u8 g_SlotElementSelectedIdx[2]; // 0 - Slot 1, 1 - Slot 2.

extern s8 g_SelectedSaveSlotIdx; // 0 - Slot 1, 1 - Slot 2.

extern s_FsImageDesc D_800A8D98;

extern u8 D_800A97D7;

extern s8 D_800A97D8;

extern s8 D_800A97D9;

extern s32 D_800A97DC; // `e_SavegameEntryType`

extern s8 D_800A97E0;

extern u32 allFileStatus[];

extern s_MemCard_SaveHeader g_MemCard_BasicSaveInfo1[CARD_DEVICE_FILE_COUNT];

extern s_MemCard_SaveHeader g_MemCard_BasicSaveInfo2[CARD_DEVICE_FILE_COUNT];

extern s_MemCard_SaveHeader g_MemCard_BasicSaveInfo3[CARD_DEVICE_FILE_COUNT];

/** @brief Defines if the game can use the memory card. */
extern bool g_MemCard_AvailibityStatus;

extern s32 pad_bss_800B5484;

extern s_MemCard_Work g_MemCard_Work; // 0x800B5488

extern s_MemCard_SaveWork g_MemCard_SaveWork;

extern s32 g_MemCard_PrevSavegameCount;

extern s16 g_MemCard_SavegameCount;

// ==========
// FUNCTIONS
// ==========

/** @brief Initializes memory card system.
 * This Initializes the entire memory card handling system while
 * `MemCard_Init` exclusively initalizes the memory cards.
 */
void MemCard_SysInit(void);

/** @brief Clear memory card data in RAM. */
void MemCard_RamClear(s32 deviceId);

/** @brief Clear all files status. */
void MemCard_FileStatusClear(s32 deviceId);

bool MemCard_AreFilesAllNotUnused(s32 deviceId);

void MemCard_SysInit2(void);

/** @brief Disables memory card. */
void MemCard_Disable(void);

void MemCard_InitStatus(void);

void MemCard_StatusInitNotConnected(void);

s32 MemCard_AllMemCardsStatusGet(void);

void func_8002E8D4(void);

void MemCard_StatusInitSuccess(void);

s32 func_8002E914(void);

bool MemCard_ProcessSet(s32 arg0, s32 deviceId, s32 fileIdx, s32 saveIdx);

/** @brief Related to formatting logic.
 * Used in: `SAVELOAD.BIN`
 */
s32 MemCard_LastMemCardResultGet(void);

s32 MemCard_AllFilesStatusGet(s32 deviceId);

s_Savegame_Metadata* MemCard_SaveMetadataGet(s32 deviceId, s32 fileIdx, s32 saveIdx);

/** @brief Returns the count of files used in the memory card. */
s32 MemCard_UsedFileCount(s32 deviceId);

/** @brief Returns the count available files in the memory card. */
s32 MemCard_FreeFilesCount(s32 deviceId);

/** @unused Checks if no save have been done in any inserted memory card. */
bool MemCard_NoSavesDoneCheck(s32* outDeviceId, s32* outFileIdx, s32* outSaveIdx);

void MemCard_Update(void); // Return type assumed.

void MemCard_Process_Format(s_MemCard_Process* statusPtr);

void MemCard_Process_Init(s_MemCard_Process* statusPtr);

// NOT SURE
s32 MemCard_FileLimitUpdate(s32 deviceId, s_MemCard_Directory* dir);

void MemCard_Process_Load(s_MemCard_Process* statusPtr);

void MemCard_Process_Save(s_MemCard_Process* statusPtr);

void MemCard_SaveInfoClear(s_MemCard_SaveHeader* saveInfo);

/** Copies user config into an `s_Savegame_UserConfigs` and calculates footer checksum. */
void MemCard_UserConfigCopy(s_Savegame_UserConfigs* dest, s_SaveUserConfig* src);

s32 MemCard_BiggestTotalSavegameCountGet(s32 deviceId);

/** Copies savegame into an s_Savegame_Container and calculates footer checksum. */
void MemCard_GameDataCopy(s_Savegame_Container* dest, s_Savegame* src);

void MemCard_TotalSavegameCountUpdate(s32 deviceId, s32 fileIdx, s32 saveIdx, s_Savegame* arg3);

void MemCard_TotalSavegameCountStepUpdate(s32 deviceId, s32 fileIdx, s32 saveIdx);

void MemCard_SaveWithBiggestTotalSavegameCountGet(s32 deviceId, s_MemCard_TotalSavesInfo* result);

/** Updates the footer with the checksum of the given data. */
void MemCard_ChecksumUpdate(s_Savegame_Footer* saveFooter, s8* saveData, s32 saveDataLength);

/** Generates a checksum of the given saveData and compares it against the checksum value in the footer.
 * Returns 1 if the checksums match, otherwise 0.
 */
bool MemCard_ChecksumValidate(s_Savegame_Footer* saveFooter, s8* saveData, s32 saveDataLength); // 0x8002FF74

/** Generates an 8-bit XOR checksum over the given data, only appears used with s_Savegame data. */
u8 MemCard_ChecksumGenerate(s8* saveData, s32 saveDataLength);

/** Generates a save filename for the given save index. */
void MemCard_FilenameGenerate(char* dest, s32 fileIdx);

void MemCard_SaveBlockInit(s_PsxSaveBlock* saveBlock, s8 blockCount, s32 saveIdx, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);

/** Unused function? Appears to write `0xFF` to first 128 bytes of card and check if event is triggered. */
s32 MemCard_DeviceTest(s32 deviceId);

s32 MemCard_DeviceFormat(s32 deviceId);

s32 MemCard_FileClear(s32 deviceId, char* fileName);

s32 MemCard_FileRename(s32 deviceId, char* prevName, char* newName);

void MemCard_Init(void);

void MemCard_EventsInit(void);

void MemCard_StateInit(void);

void MemCard_SwEventsInit(void);

void MemCard_HwEventsInit(void);

void MemCard_EventsClose(void);

void MemCard_SwEventsClose(void);

void MemCard_HwEventsClose(void);

s32 MemCard_SwEventsTest(void);

void MemCard_SwEventsReset(void);

s32 MemCard_HwEventsTest(void);

void MemCard_HwEventsReset(void);

void MemCard_HwEventSpIOE(void);

void MemCard_HwEventSpERROR(void);

void MemCard_HwEventSpNEW(void);

void MemCard_HwEventSpTIMOUT(void);

void MemCard_HwEventSpUNKNOWN(void);

s32 MemCard_StateResult(void); /** `e_MemCardResult` */

bool MemCard_WorkSet(e_MemCardIoMode mode, s32 deviceId, s_MemCard_Directory* outDir, char* filename, s32 createBlockCount, s32 fileOffset, void* outBuf, s32 bufSize);

bool MemCard_MemCardIsIdle(void);

void MemCard_StateUpdate(void);

s32 MemCard_State_Init(void);

s32 MemCard_State_Check(void);

s32 MemCard_State_Load(void);

s32 MemCard_State_DirRead(void);

s32 MemCard_State_FileCreate(void);

s32 MemCard_State_FileOpen(void);

s32 MemCard_State_FileReadWrite(void);

void MemCard_DevicePathGenerate(s32 deviceId, char* res);

/** @brief Checks if any file is corrupted, unused or used.
 * If any file is used then it return false.
 */
bool MemCard_FilesAreNotUsedCheck(s32 idx);

#endif
