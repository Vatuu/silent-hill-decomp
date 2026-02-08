#ifndef _MEMCARD_H
#define _MEMCARD_H

/** @brief This header is used to declare any variable, struct, or
 * function part of `BODYPROG.BIN` identified to be related
 * to the memory card system (not from PSY-Q SDK).
 */

// ==========
// CONSTANTS
// ==========

#define SAVEGAME_ENTRY_BUFFER_0 ((u8*)0x801E09E0) // Slot 1 savegame entry.
#define SAVEGAME_ENTRY_BUFFER_1 ((u8*)0x801E1430) // Slot 2 savegame entry.

#define MEMCARD_DEVICE_COUNT_MAX 8
#define MEMCARD_SAVES_COUNT_MAX  11
#define MEMCARD_FILE_COUNT_MAX   15
#define MEMCARD_SLOT_COUNT_MAX   2

#define SAVEGAME_FOOTER_MAGIC 0xDCDC
#define SAVEGAME_COUNT_MAX    MEMCARD_SAVES_COUNT_MAX * MEMCARD_FILE_COUNT_MAX

// ==============
// HELPER MACROS
// ==============

#define MemCard_ActiveSavegameEntryGet(slotIdx) \
    ((s_SaveScreen_Element*)&SAVEGAME_ENTRY_BUFFER_0[2640 * (slotIdx)])

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

/** @brief Used by `s_SaveScreen_Element`. */
typedef enum _SavegameEntryType
{
    SavegameEntryType_NoMemCard          = 0,
    SavegameEntryType_UnformattedMemCard = 1,
    SavegameEntryType_CorruptedMemCard   = 2,
    SavegameEntryType_LoadMemCard        = 3,
    SavegameEntryType_OutOfBlocks        = 4,
    SavegameEntryType_NoDataInMemCard    = 5,
    SavegameEntryType_Unk6               = 6,
    SavegameEntryType_CorruptedSave      = 7,
    SavegameEntryType_Save               = 8,
    SavegameEntryType_NewSave            = 9,
    SavegameEntryType_NewFile            = 10
} e_SavegameEntryType;

/** @brief Save location IDs. */
typedef enum _SaveLocationId
{
    SaveLocationId_Anywhere    = 0,
    SaveLocationId_Cafe        = 1,
    SaveLocationId_Bus         = 2,
    SaveLocationId_Store       = 3,
    SaveLocationId_Infirmary   = 4,
    SaveLocationId_Doghouse    = 5,
    SaveLocationId_Gordon      = 6,
    SaveLocationId_Church      = 7,
    SaveLocationId_Garage      = 8,
    SaveLocationId_Police      = 9,
    SaveLocationId_Reception   = 10,
    SaveLocationId_Room302     = 11,
    SaveLocationId_Directors   = 12,
    SaveLocationId_JewelryShop = 13,
    SaveLocationId_PoolHall    = 14,
    SaveLocationId_AntiqueShop = 15,
    SaveLocationId_ThemePark   = 16,
    SaveLocationId_Boat        = 17,
    SaveLocationId_Bridge      = 18,
    SaveLocationId_Motel       = 19,
    SaveLocationId_Lighthouse  = 20,
    SaveLocationId_Sewer       = 21,
    SaveLocationId_Nowhere     = 22,
    SaveLocationId_ChildsRoom  = 23,
    SaveLocationId_NextFear    = 24
} e_SaveLocationId;

typedef enum _MemCardProcess
{
    MemCardProcess_None          = 0,
    MemCardProcess_Init          = 1,
    MemCardProcess_Load_Game     = 2,
    MemCardProcess_Save_3        = 3,
	MemCardProcess_Load_Settings = 4,
	MemCardProcess_Save_5        = 5,
	MemCardProcess_Format        = 6
} e_MemCardProcess;

typedef enum _UnkMemCardState1
{
    UnkMemCardState1_0  = 0,
    UnkMemCardState1_1  = 1,
    UnkMemCardState1_2  = 2,
    UnkMemCardState1_3  = 3,
	UnkMemCardState1_4  = 4,
	UnkMemCardState1_5  = 5
} e_UnkMemCardState1;

typedef enum _FileState
{
    FileState_Unused  = 0,
    FileState_Used    = 1,
    FileState_Unk2    = 2, // @unused See `func_80033548`.
    FileState_Damaged = 3
} e_FileState;

typedef enum _MemCardCardState
{
    MemCardCardState_Idle          = 0,
    MemCardCardState_Init          = 1,
    MemCardCardState_Check         = 2,
    MemCardCardState_Load          = 3,
    MemCardCardState_DirRead       = 4,
    MemCardCardState_FileCreate    = 5,
    MemCardCardState_FileOpen      = 6,
    MemCardCardState_FileReadWrite = 7
} e_MemCardCardState;

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
    char filenames_0[MEMCARD_FILE_COUNT_MAX][21];
    u8   blockCounts_13B[MEMCARD_FILE_COUNT_MAX]; // Size of each file in 8192 byte blocks.
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

typedef struct _Savegame_Metadata
{
    s32 totalSavegameCount_0;
    u32 gameplayTimer_4;
    u16 savegameCount_8;
    u8  locationId_A;
    u8  isNextFearMode_B             : 1;
    u8  add290Hours_B_1              : 2;
    u8  pickedUpSpecialItemCount_B_3 : 5; /** See `pickedUpSpecialItemCount_25C_3` comment in `s_Savegame`. */
} s_MemCard_SaveMetadata;
STATIC_ASSERT_SIZEOF(s_MemCard_SaveMetadata, 12);

/** @brief Information of elements in save screen.
 * 
 * @note This is use to determine both saves and other
 * elements in save screen as it is use to display
 * the "New Save" or "The file is damage" elements.
 * It is also used to display rectangle status messages
 * as the memory card is not inserted or no save available.
 */
typedef struct _SaveScreen_Element
{
    s16                     totalSavegameCount_0; /** Counter that stores all the times the player have save throughout the entire game.
	                                               * In order to get the set this value the code will go through all saves in the memory
	                                               * card and check which have this variable with the biggest value.
	                                               *
	                                               * @bug: For some unknown reason, this counter it is used by the code uses to
	                                               * determine if the player have selected the "New Save" element which will make
	                                               * overwrites to not show the "Yes/No" message to show up.
	                                               */
    s16                     savegameCount_2;
    s8                      type_4;               /** `e_SavegameEntryType` */
    s8                      deviceId_5;
    s8                      fileIdx_6;
    s8                      elementIdx_7;
    s8                      locationId_8;
    s8                      pad_9[3];
    s_MemCard_SaveMetadata* saveMetadata_C;
} s_SaveScreen_Element;
STATIC_ASSERT_SIZEOF(s_SaveScreen_Element, 16);

/** @brief Appended to `ShSavegame` and `ShSaveUserConfig` during game save. Contains 8-bit XOR checksum + magic.
 * Checksum generated via `MemCard_ChecksumGenerate`.
 */
typedef struct _SavegameFooter
{
    u8  checksum_0[2];
    u16 magic_2;
} s_Savegame_Footer;
STATIC_ASSERT_SIZEOF(s_Savegame_Footer, 4);

/** @brief Contains `s_Savegame` data with the footer appended to the end containing the checksum + magic. */
typedef struct _SavegameContainer
{
    s_Savegame        savegame_0;
    s_Savegame_Footer footer_27C;
} s_Savegame_Container;
STATIC_ASSERT_SIZEOF(s_Savegame_Container, 640);

/** @brief Contains `s_SaveUserConfig` data padded to 128 bytes with a footer at the end containing checksum + magic. */
typedef struct _SaveUserConfigContainer
{
    s_SaveUserConfig config_0;
    u8                pad_38[68];
    s_Savegame_Footer footer_7C;
} s_Savegame_UserConfigs;

typedef struct
{
    s32 totalSavegameCount_0;
    s32 fileIdx_4;
    s32 saveIdx_8;
} s_MemCard_TotalSavesInfo;

typedef struct
{
    s32                    unk_0;
    s_MemCard_SaveMetadata saveMetadata_4[MEMCARD_SAVES_COUNT_MAX];
    s8                     unk_88[116];
    s_Savegame_Footer      footer_FC;
} s_MemCard_SaveHeader;
STATIC_ASSERT_SIZEOF(s_MemCard_SaveHeader, 256);

typedef struct
{
    s32                   status_0;
    s8                    fileState_4[MEMCARD_FILE_COUNT_MAX];
    s_MemCard_SaveHeader* saveHeader_14; /** Slots saves information. */
    s32                   fileLimit_18;  /** Max count of files allowed in the memory card. */
} s_MemCard_DeviceInfo;
STATIC_ASSERT_SIZEOF(s_MemCard_DeviceInfo, 28);

/** @note Some memory card states information. Related to `s_SaveScreen_Element`.
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

// OPM16 has `MCM_FUNC_WORK` struct with size 0x6D8, close to this 0x718.
typedef struct
{
    s_MemCard_DeviceInfo   devices_0[MEMCARD_DEVICE_COUNT_MAX];
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

/** @brief Basic information required to draw information of elements in save slots.
 * Address access is based on the slot: slot 1 = 0x801E09E0, slot 2 = 0x801E1440.
 * 
 * @note Macros for its references are in `saveload.h`:
 * `SAVEGAME_ENTRY_BUFFER_0`
 * `SAVEGAME_ENTRY_BUFFER_1`
 */

/** @brief Amount of elements in each memory card. */
extern u8 g_Savegame_ElementCount0[2];

extern s_SaveScreen_Element* g_MemCard_ActiveSavegameEntry; // 0x800BCD2C

extern u8 g_SlotElementSelectedIdx[2]; // 0 - Slot 1, 1 - Slot 2.

extern s8 g_SelectedSaveSlotIdx; // 0 - Slot 1, 1 - Slot 2.

extern s_FsImageDesc D_800A8D98;

extern u8 D_800A97D7;

extern s8 D_800A97D8;

extern s8 D_800A97D9;

extern s32 D_800A97DC; // `e_SavegameEntryType`

extern s8 D_800A97E0;

extern u32 allFileStatus[];

extern s32 D_800BCD18[2];

extern s32 D_800BCD20[2];

/** @brief Stores all memory cards/devices status. */
extern u32 g_MemCard_AllMemCardsStatus;

/** @brief Some determinator for the state of the save screen.
 * 2 - Saving, 3 - Loading.
 */
extern s8 g_SaveScreen_SaveScreenState;

extern s8 D_800BCD39; // Boolean.

/** @brief Counts all elements of all inserted memory cards. */
extern s16 g_MemCard_TotalElementsCount;

extern s8 g_SelectedDeviceId;

/** @brief Amount of elements in each memory card. */
extern u8 g_Savegame_ElementCount1[2];

/** @brief Index of selected element in each memory card. */
extern u8 g_Savegame_SelectedElementIdx;

extern s8 g_SelectedFileIdx;

extern s_MemCard_SaveHeader g_MemCard_BasicSaveInfo1[MEMCARD_FILE_COUNT_MAX];

extern s_MemCard_SaveHeader g_MemCard_BasicSaveInfo2[MEMCARD_FILE_COUNT_MAX];

extern s_MemCard_SaveHeader g_MemCard_BasicSaveInfo3[MEMCARD_FILE_COUNT_MAX];

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

s_MemCard_SaveMetadata* MemCard_SaveMetadataGet(s32 deviceId, s32 fileIdx, s32 saveIdx);

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
