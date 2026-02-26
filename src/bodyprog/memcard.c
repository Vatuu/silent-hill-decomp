#include "game.h"

#include <psyq/libapi.h>
#include <psyq/limits.h>
#include <psyq/strings.h>
#include <psyq/sys/file.h>

#include "main/fsqueue.h"
#include "bodyprog/memcard.h"

// ========================================
// STATIC VARIABLES
// ========================================

static s_MemCard_SaveHeader g_MemCard_BasicSaveInfo1[MEMCARD_FILE_COUNT_MAX];
static s_MemCard_SaveHeader g_MemCard_BasicSaveInfo2[MEMCARD_FILE_COUNT_MAX];
static s_MemCard_SaveHeader g_MemCard_BasicSaveInfo3[MEMCARD_FILE_COUNT_MAX];

// ========================================
// GLOBAL VARIABLES
// ========================================

bool               g_MemCard_AvailibityStatus;
s32                pad_bss_800B5484;
s_MemCard_Work     g_MemCard_Work;
s_MemCard_SaveWork g_MemCard_SaveWork;

// ========================================
// INLINE FUNCTIONS
// ========================================

static inline void MemCard_DirectoryFileClear(s32 idx)
{
    strcpy(g_MemCard_Work.directories_40->filenames_0[idx], ""); // 0x80024B64 .rodata
    g_MemCard_Work.directories_40->blockCounts_13B[idx] = 0;
}

static inline void MemCard_SaveWork_SetParams(s_MemCard_Process* ptr, s32 processId, s32 deviceId, s32 fileIdx, s32 saveIdx, s32 state, s32 lastMemCardResult)
{
    ptr->processId_0          = processId;
    ptr->deviceId_4           = deviceId;
    ptr->fileIdx_8            = fileIdx;
    ptr->saveIdx_C            = saveIdx;
    ptr->processState_10      = state;
    ptr->lastMemCardResult_14 = lastMemCardResult;
}

// ========================================
// MEMORY CARD - INITIALIZATION
// ========================================

void MemCard_SysInit(void) // 0x8002E630
{
    s32                   i;
    s_MemCard_SaveHeader* ptr;

    MemCard_Init();

    g_MemCard_AvailibityStatus = false;

    // Clear arrays.
    bzero(&g_MemCard_SaveWork, sizeof(s_MemCard_SaveWork));
    bzero(g_MemCard_BasicSaveInfo1, sizeof(s_MemCard_SaveHeader) * 3);

    for (i = 0; i < MEMCARD_DEVICE_COUNT_MAX; i++)
    {
        g_MemCard_SaveWork.devices_0[i].status_0 = 0;

        MemCard_FileStatusClear(i);

        switch (i)
        {
            case 0:
                ptr = g_MemCard_BasicSaveInfo1;
                break;

            case 4:
                ptr = g_MemCard_BasicSaveInfo2;
                break;

            default:
                ptr = g_MemCard_BasicSaveInfo3;
                break;
        }

        g_MemCard_SaveWork.devices_0[i].saveHeader_14 = ptr;

        MemCard_RamClear(i);
    }
}

void MemCard_RamClear(s32 deviceId) // 0x8002E6E4
{
    g_MemCard_SaveWork.devices_0[deviceId].status_0 = 0;

    MemCard_FileStatusClear(deviceId);
    bzero(g_MemCard_SaveWork.devices_0[deviceId].saveHeader_14, sizeof(s_MemCard_SaveHeader) * MEMCARD_FILE_COUNT_MAX);

    g_MemCard_SaveWork.devices_0[deviceId].fileLimit_18 = 0;
}

void MemCard_FileStatusClear(s32 deviceId) // 0x8002E730
{
    s32 i;

    for (i = 0; i < MEMCARD_FILE_COUNT_MAX; i++)
    {
        g_MemCard_SaveWork.devices_0[deviceId].fileState_4[i] = FileState_Unused;
    }
}

bool MemCard_AreAllFilesUsed(s32 deviceId) // 0x8002E76C
{
    bool result;
    s32  i;

    result = true;
    for (i = 0; i < MEMCARD_FILE_COUNT_MAX; i++)
    {
        if (g_MemCard_SaveWork.devices_0[deviceId].fileState_4[i] != FileState_Unused)
        {
            result = false;
            break;
        }
    }

    return result;
}

void MemCard_SysInit2(void) // 0x8002E7BC
{
    if (g_MemCard_AvailibityStatus == true)
    {
        return;
    }

    g_MemCard_AvailibityStatus = true;
    MemCard_StatusInitSuccess();
    MemCard_EventsInit();

    MemCard_SaveWork_SetParams(&g_MemCard_SaveWork.saveWork_E0[0], 0, 0, 0, 0, 0, MemCardResult_NotConnected);
    MemCard_SaveWork_SetParams(&g_MemCard_SaveWork.saveWork_E0[1], 0, 0, 0, 0, 0, MemCardResult_NotConnected);
}

void MemCard_Disable(void) // 0x8002E830
{
    if (g_MemCard_AvailibityStatus != false)
    {
        g_MemCard_AvailibityStatus = false;
        MemCard_EventsClose();
    }
}

void MemCard_InitStatus(void) // 0x8002E85C
{
    g_MemCard_SaveWork.memCardInitalized_110 = 1;
}

void MemCard_StatusInitNotConnected(void) // 0x8002E86C
{
    g_MemCard_SaveWork.memCardInitalized_110 = 0;

    MemCard_SaveWork_SetParams(&g_MemCard_SaveWork.saveWork_E0[1], 0, 0, 0, 0, 0, MemCardResult_NotConnected);
}

s32 MemCard_AllMemCardsStatusGet(void) // 0x8002E898
{
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < MEMCARD_DEVICE_COUNT_MAX; i++)
    {
        ret |= MemCard_StatusStore(g_MemCard_SaveWork.devices_0[i].status_0, i);
    }

    return ret;
}

void func_8002E8D4(void) // 0x8002E8D4
{
    g_MemCard_SaveWork.memCardInitalized_110 = 1;
}

void MemCard_StatusInitSuccess(void) // 0x8002E8E4
{
    g_MemCard_SaveWork.memCardInitalized_110 = 0;

    MemCard_SaveWork_SetParams(&g_MemCard_SaveWork.saveWork_E0[1], 0, 0, 0, 0, 0, MemCardResult_Success);
}

// ========================================
// MEMORY CARD - HELPERS
// ========================================

s32 func_8002E914(void) // 0x8002E914
{
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < MEMCARD_DEVICE_COUNT_MAX; i++)
    {
        ret |= MemCard_FileStatusStore(g_MemCard_SaveWork.devices_0[i].status_0, i);
    }

    return ret;
}

bool MemCard_ProcessSet(s32 arg0, s32 deviceId, s32 fileIdx, s32 saveIdx) // 0x8002E94C
{
    if (g_MemCard_SaveWork.saveWork_E0[0].processId_0 != MemCardProcess_None)
    {
        return false;
    }

    MemCard_SaveWork_SetParams(&g_MemCard_SaveWork.saveWork_E0[0], arg0, deviceId, fileIdx, saveIdx, 0, MemCardResult_Success);
    return true;
}

s32 MemCard_LastMemCardResultGet(void) // 0x8002E990
{
    return g_MemCard_SaveWork.saveWork_E0[0].lastMemCardResult_14;
}

s32 MemCard_AllFilesStatusGet(s32 deviceId) // 0x8002E9A0
{
    s32 ret;
    s32 i;

    ret = 0;

    for (i = 0; i < MEMCARD_FILE_COUNT_MAX; i++)
    {
        ret |= MemCard_FileStatusStore(g_MemCard_SaveWork.devices_0[deviceId].fileState_4[i], i);
    }

    return ret;
}

s_MemCard_SaveMetadata* MemCard_SaveMetadataGet(s32 deviceId, s32 fileIdx, s32 saveIdx) // 0x8002E9EC
{
    return &g_MemCard_SaveWork.devices_0[deviceId].saveHeader_14[fileIdx].saveMetadata_4[saveIdx];
}

s32 MemCard_UsedFileCount(s32 deviceId) // 0x8002EA28
{
    s32 ret;
    s32 i;

    ret = 0;

    for (i = 0; i < MEMCARD_FILE_COUNT_MAX; i++)
    {
        if (g_MemCard_SaveWork.devices_0[deviceId].fileState_4[i] != FileState_Unused)
        {
            ret++;
        }
    }

    return ret;
}

s32 MemCard_FreeFilesCount(s32 deviceId) // 0x8002EA78
{
    return g_MemCard_SaveWork.devices_0[deviceId].fileLimit_18 - MemCard_UsedFileCount(deviceId);
}

bool MemCard_NoSavesDoneCheck(s32* outDeviceId, s32* outFileIdx, s32* outSaveIdx) // 0x8002EABC
{
    s_MemCard_TotalSavesInfo saveInfo;
    s32                      i;
    s32                      totalSavegameCount;

    totalSavegameCount = 0;

    *outDeviceId = 0;
    *outFileIdx  = 0;
    *outSaveIdx  = 0;

    for (i = 0; i < MEMCARD_DEVICE_COUNT_MAX; i++)
    {
        if (g_MemCard_SaveWork.devices_0[i].status_0 == 3)
        {
            MemCard_SaveWithBiggestTotalSavegameCountGet(i, &saveInfo);

            if (totalSavegameCount < saveInfo.totalSavegameCount_0)
            {
                *outDeviceId = i;
                *outFileIdx  = saveInfo.fileIdx_4;
                *outSaveIdx  = saveInfo.saveIdx_8;

                totalSavegameCount = saveInfo.totalSavegameCount_0;
            }
        }
    }

    return totalSavegameCount != 0;
}

// ========================================
// MEMORY CARD - PROCESSES
// ========================================

void MemCard_Update(void) // 0x8002EB88
{
    s_MemCard_Process* statusPtr;

    if (g_MemCard_AvailibityStatus == false)
    {
        return;
    }

    MemCard_StateUpdate();

    if (g_MemCard_SaveWork.saveWork_E0[0].processId_0 != MemCardProcess_None)
    {
        if (g_MemCard_SaveWork.saveWork_E0[1].processId_0 == MemCardProcess_None)
        {
            statusPtr = &g_MemCard_SaveWork.saveWork_E0[0];
        }
        else
        {
            statusPtr = &g_MemCard_SaveWork.saveWork_E0[1];
        }
    }
    else
    {
        if (g_MemCard_SaveWork.memCardInitalized_110 == 1 && g_MemCard_SaveWork.saveWork_E0[1].processId_0 == MemCardProcess_None)
        {
            MemCard_SaveWork_SetParams(&g_MemCard_SaveWork.saveWork_E0[1], g_MemCard_SaveWork.memCardInitalized_110, g_MemCard_SaveWork.saveWork_E0[1].deviceId_4, 0, 0, 0, g_MemCard_SaveWork.memCardInitalized_110);
        }

        statusPtr = &g_MemCard_SaveWork.saveWork_E0[1];
    }

    switch (statusPtr->processId_0)
    {
        case MemCardProcess_Init: // Also used as update process.
            MemCard_Process_Init(statusPtr);
            break;

        case MemCardProcess_Load_Game:
        case MemCardProcess_Load_Settings:
            MemCard_Process_Load(statusPtr);
            break;

        case MemCardProcess_Save_3:
        case MemCardProcess_Save_5:
            MemCard_Process_Save(statusPtr);
            break;

        case MemCardProcess_Format:
            MemCard_Process_Format(statusPtr);
            break;

        case MemCardProcess_None:
        default:
            break;
    }

    if (statusPtr->processId_0 != MemCardProcess_None && statusPtr->lastMemCardResult_14 != MemCardResult_Success)
    {
        statusPtr->processId_0 = MemCardProcess_None;
        if (statusPtr == &g_MemCard_SaveWork.saveWork_E0[1])
        {
            g_MemCard_SaveWork.saveWork_E0[1].deviceId_4 = (g_MemCard_SaveWork.saveWork_E0[1].deviceId_4 + 1) & 0x7;
        }
    }
}

void MemCard_Process_Format(s_MemCard_Process* statusPtr) // 0x8002ECE0
{
    if (MemCard_DeviceFormat(statusPtr->deviceId_4) != 0)
    {
        statusPtr->lastMemCardResult_14 = MemCardResult_FileIoComplete;

        g_MemCard_SaveWork.devices_0[statusPtr->deviceId_4].status_0 = 3;

        MemCard_FileStatusClear(statusPtr->deviceId_4);

        g_MemCard_SaveWork.devices_0[statusPtr->deviceId_4].fileLimit_18 = MEMCARD_FILE_COUNT_MAX;
    }
    else
    {
        statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
    }
}

void MemCard_Process_Init(s_MemCard_Process* statusPtr) // 0x8002ED7C
{
    char                       filePath[24];
    s32                        memCardResult;
    s32                        i;
    s_MemCard_SaveHeader*      saveHeaderPtr;
    s_MemCard_DeviceInfo*      deviceInfoPtr;
    static s32                 fileIdx;
    static s32                 D_800B261C;
    static s32                 checkSumValidationAttempts;
    static s32                 D_800B2624;
    static s_MemCard_Directory directoryInfoCpy;

    statusPtr->lastMemCardResult_14 = MemCardResult_Success;

    deviceInfoPtr = &g_MemCard_SaveWork.devices_0[statusPtr->deviceId_4];

    switch (statusPtr->processState_10)
    {
        case 0: // Start memcard process initialization.
            D_800B261C = 0;

            if (MemCard_WorkSet(MemCardIoMode_Init, statusPtr->deviceId_4, NULL, NULL, 0, 0, NULL, 0))
            {
                statusPtr->processState_10 = 1;
            }
            break;

        case 1: // Checks if previous step was successful
            memCardResult = MemCard_StateResult();
            switch (memCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    deviceInfoPtr->status_0         = UnkMemCardState1_1;
                    statusPtr->lastMemCardResult_14 = memCardResult;
                    break;

                case MemCardResult_InitError:
                    statusPtr->processState_10 = 2;
                    break;

                case MemCardResult_InitComplete:
                    switch(deviceInfoPtr->status_0)
                    {
                        case UnkMemCardState1_3:
                            statusPtr->lastMemCardResult_14 = MemCardResult_FileIoComplete;
                            break;

                        case UnkMemCardState1_4:
                            statusPtr->lastMemCardResult_14 = MemCardResult_LoadError;
                            break;

                        case UnkMemCardState1_5:
                            statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
                            break;

                        default:
                            statusPtr->processState_10 = 2;
                            break;
                    }
                    break;
            }
            break;

        case 2: // Copies memory card directory information.
            deviceInfoPtr->status_0 = UnkMemCardState1_2;
            if (MemCard_WorkSet(MemCardIoMode_DirRead, statusPtr->deviceId_4, &directoryInfoCpy, NULL, 0, 0, NULL, 0))
            {
                statusPtr->processState_10 = 3;
            }
            break;

        case 3: // Checks if previous step was successful
            memCardResult = MemCard_StateResult();
            switch (memCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = memCardResult;
                    deviceInfoPtr->status_0         = UnkMemCardState1_1;
                    break;

                case MemCardResult_LoadError:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = memCardResult;
                    deviceInfoPtr->status_0         = UnkMemCardState1_4;
                    break;

                case MemCardResult_NewDevice:
                case MemCardResult_NoNewDevice:
                    statusPtr->processState_10 = 4;
                    return;
            }
            break;

        case 4: // Clear memory card files status.
            fileIdx = NO_VALUE;

            MemCard_FileStatusClear(statusPtr->deviceId_4);
            bzero(g_MemCard_SaveWork.devices_0[statusPtr->deviceId_4].saveHeader_14, sizeof(s_MemCard_SaveHeader) * MEMCARD_FILE_COUNT_MAX);

            statusPtr->processState_10 = 5;

        case 5: // Checks if memory card contains game directory.
            fileIdx++;
            checkSumValidationAttempts = 0;

            for (fileIdx; fileIdx < MEMCARD_FILE_COUNT_MAX; fileIdx++)
            {
                MemCard_FilenameGenerate(filePath, fileIdx);

                for (i = 0; i < MEMCARD_FILE_COUNT_MAX; i++)
                {
                    if (strcmp(directoryInfoCpy.filenames_0[i], filePath) == 0)
                    {
                        statusPtr->processState_10 = 6;
                        return;
                    }
                }
            }

            if (fileIdx == MEMCARD_FILE_COUNT_MAX)
            {
                statusPtr->processState_10 = 9;
            }
            break;

        case 6: // Copies memory card header data and ties game directory to file.
            MemCard_FilenameGenerate(filePath, fileIdx);

            if (MemCard_WorkSet(MemCardIoMode_Read, statusPtr->deviceId_4, NULL, filePath, 0, sizeof(s_MemCard_SaveHeader) * 2, &g_MemCard_SaveWork.devices_0[statusPtr->deviceId_4].saveHeader_14[fileIdx], sizeof(s_MemCard_SaveHeader)))
            {
                statusPtr->processState_10 = 7;
            }
            break;

        case 7: // Checks if previous step was successful
            memCardResult = MemCard_StateResult();
            switch (memCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(statusPtr->deviceId_4);

                    statusPtr->lastMemCardResult_14 = memCardResult;
                    deviceInfoPtr->status_0         = UnkMemCardState1_1;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    statusPtr->processState_10 = 0;

                    if (D_800B261C >= 3)
                    {
                        MemCard_RamClear(statusPtr->deviceId_4);

                        statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
                        deviceInfoPtr->status_0         = UnkMemCardState1_5;
                        break;
                    }

                    D_800B261C++;
                    statusPtr->processState_10 = 2;
                    break;

                case MemCardResult_FileIoComplete:
                    statusPtr->processState_10 = 8;
                    break;
            }
            break;

        case 8: // Checks if save header checksum matches with current save header data.
            saveHeaderPtr = &g_MemCard_SaveWork.devices_0[statusPtr->deviceId_4].saveHeader_14[fileIdx];

            // Checksum check.
            if (MemCard_ChecksumValidate(&saveHeaderPtr->footer_FC, (s8*)saveHeaderPtr, sizeof(s_MemCard_SaveHeader)))
            {
                deviceInfoPtr->fileState_4[fileIdx] = FileState_Used;
                statusPtr->processState_10          = 5;
                return;
            }

            // If checksum check fails start a process where the memory card will be read three times,
            // if the file fails to load after three attempts the file will be qualified to be damage.
            checkSumValidationAttempts++;

            if (checkSumValidationAttempts >= 3)
            {
                statusPtr->processState_10          = 5;
                deviceInfoPtr->fileState_4[fileIdx] = FileState_Damaged;
                return;
            }

            statusPtr->processState_10 = 6;
            break;

        case 9: // Finalize and marks as succesful memory card initalization process.
            // For some reason also updates the file limit of the memory card.
            deviceInfoPtr->fileLimit_18     = MemCard_FileLimitUpdate(statusPtr->deviceId_4, &directoryInfoCpy);
            statusPtr->lastMemCardResult_14 = MemCardResult_FileIoComplete;
            deviceInfoPtr->status_0         = UnkMemCardState1_3;
            break;
    }
}

s32 MemCard_FileLimitUpdate(s32 deviceId, s_MemCard_Directory* dir) // 0x8002F278
{
    s32 ret;
    s32 i;

    ret = MEMCARD_FILE_COUNT_MAX;

    for (i = 0; i < MEMCARD_FILE_COUNT_MAX; i++)
    {
        ret -= dir->blockCounts_13B[i];
    }

    return ret + MemCard_UsedFileCount(deviceId);
}

void MemCard_Process_Load(s_MemCard_Process* statusPtr)
{
    char                  filePath[24];
    s32                   memCardResult;
    s32                   saveData0Offset;
    s8*                   saveData0Buf;
    s32                   saveData0Size;
    s_MemCard_DeviceInfo* saveInfo;
    s8*                   saveData1Buf;
    s32                   saveData1Size;
    s_Savegame_Footer*    saveData1Footer;
    static s32            fileIdx;

    saveInfo = &g_MemCard_SaveWork.devices_0[statusPtr->deviceId_4];

    statusPtr->lastMemCardResult_14 = MemCardResult_Success;

    switch (statusPtr->processState_10)
    {
        case 0: // Checks if any file from the memory card is used.
            if (statusPtr->processId_0 == MemCardProcess_Load_Game)
            {
                if (MemCard_AreAllFilesUsed(statusPtr->deviceId_4) != true)
                {
                    fileIdx = MemCard_BiggestTotalSavegameCountGet(statusPtr->deviceId_4);
                    if (fileIdx == NO_VALUE)
                    {
                        statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
                    }
                    else
                    {
                        statusPtr->processState_10 = 1;
                    }
                }
                else
                {
                    statusPtr->lastMemCardResult_14 = MemCardResult_Full;
                }
            }
            else
            {
                fileIdx = statusPtr->fileIdx_8;
                switch (saveInfo->fileState_4[fileIdx])
                {
                    case FileState_Used:
                        if (MemCard_SaveMetadataGet(statusPtr->deviceId_4, fileIdx, statusPtr->saveIdx_C)->totalSavegameCount_0 != 0)
                        {
                            statusPtr->processState_10 = 1;
                            break;
                        }

                    case FileState_Unused:
                        statusPtr->lastMemCardResult_14 = MemCardResult_Full;
                        break;

                    case FileState_Damaged:
                        statusPtr->lastMemCardResult_14 = MemCardResult_DamagedData;
                        break;
                }
            }
            break;

        case 1: // Reads savegame data or reads game configurations.
            if (statusPtr->processId_0 == MemCardProcess_Load_Game) // Load only game configurations.
            {
                saveData0Offset = 0x300;
                saveData0Buf    = (s8*)&g_MemCard_SaveWork.userConfig_418;
                saveData0Size   = sizeof(s_Savegame_UserConfigs);
            }
            else
            {
                saveData0Offset = 0x300 + sizeof(s_Savegame_UserConfigs) + (statusPtr->saveIdx_C * sizeof(s_Savegame_Container));
                saveData0Buf    = (s8*)&g_MemCard_SaveWork.saveGame_498;
                saveData0Size   = sizeof(s_Savegame_Container);
            }

            MemCard_FilenameGenerate(filePath, fileIdx);

            if (MemCard_WorkSet(MemCardIoMode_Read, statusPtr->deviceId_4, NULL, filePath, 0, saveData0Offset, saveData0Buf, saveData0Size) == true)
            {
                statusPtr->processState_10 = 2;
            }
            break;

        case 2: // Checks if previous step was successful
            memCardResult = MemCard_StateResult();
            switch (memCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = memCardResult;
                    saveInfo->status_0              = 1;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
                    saveInfo->status_0              = 0;
                    break;

                case MemCardResult_FileIoComplete:
                    statusPtr->processState_10 = 3;
                    break;
            }
            break;

        case 3: // Checks if data checksum matches and moves data to game's global variables.
            if (statusPtr->processId_0 == MemCardProcess_Load_Game)
            {
                saveData1Size   = sizeof(s_Savegame_UserConfigs);
                saveData1Buf    = (s8*)&g_MemCard_SaveWork.userConfig_418;
                saveData1Footer = &g_MemCard_SaveWork.userConfig_418.footer_7C;
            }
            else
            {
                saveData1Buf    = (s8*)&g_MemCard_SaveWork.saveGame_498;
                saveData1Size   = sizeof(s_Savegame_Container);
                saveData1Footer = &g_MemCard_SaveWork.saveGame_498.footer_27C;
            }

            if (MemCard_ChecksumValidate(saveData1Footer, saveData1Buf, saveData1Size) == false)
            {
                statusPtr->lastMemCardResult_14 = MemCardResult_DamagedData;
                return;
            }

            statusPtr->lastMemCardResult_14 = MemCardResult_FileIoComplete;

            if (statusPtr->processId_0 == MemCardProcess_Load_Game)
            {
                memcpy(&g_GameWorkConst->config_0, &g_MemCard_SaveWork.userConfig_418.config_0, sizeof(s_SaveUserConfig));
            }
            else
            {
                memcpy(g_SavegamePtr, &g_MemCard_SaveWork.saveGame_498.savegame_0, sizeof(s_Savegame));
            }
            break;
    }
}

void MemCard_Process_Save(s_MemCard_Process* statusPtr)
{
    char                  filePath[24];
    s32                   fileIdx;
    s32                   memCardResult;
    s_MemCard_DeviceInfo* ptr;
    static s32            fileIdxCpy;
    static s32            D_800B277C;

    statusPtr->lastMemCardResult_14 = MemCardResult_Success;

    ptr = &g_MemCard_SaveWork.devices_0[statusPtr->deviceId_4];

    switch (statusPtr->processState_10)
    {
        case 0: // Checks currently saving file status.
            if (statusPtr->processId_0 == MemCardProcess_Save_3)
            {
                fileIdx = statusPtr->fileIdx_8;
                if (fileIdx != NO_VALUE)
                {
                    switch (ptr->fileState_4[fileIdx])
                    {
                        case FileState_Unused:
                            fileIdxCpy                 = fileIdx;
                            statusPtr->processState_10 = 1;
                            break;

                        case FileState_Used:
                            fileIdxCpy                 = fileIdx;
                            statusPtr->processState_10 = 3;
                            break;

                        case FileState_Damaged:
                            statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
                            break;

                        default:
                            break;
                    }
                }
                else
                {
                    if (MemCard_AreAllFilesUsed(statusPtr->deviceId_4) == true)
                    {
                        fileIdxCpy                 = 0;
                        statusPtr->processState_10 = 1;
                    }
                    else
                    {
                        fileIdxCpy = MemCard_BiggestTotalSavegameCountGet(statusPtr->deviceId_4);
                        if (fileIdxCpy != fileIdx)
                        {
                            statusPtr->processState_10 = 3;
                        }
                        else
                        {
                            statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
                        }
                    }
                }
            }
            else
            {
                fileIdxCpy = statusPtr->fileIdx_8;
                switch (ptr->fileState_4[fileIdxCpy])
                {
                    case FileState_Unused:
                        statusPtr->processState_10 = 1;
                        return;

                    case FileState_Used:
                        statusPtr->processState_10 = 5;
                        return;

                    case FileState_Damaged:
                        statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
                        break;

                    default:
                        break;
                }
            }
            break;

        case 1: // Creates a new file in the memory card.
            MemCard_SaveBlockInit(&g_MemCard_SaveWork.saveBlock_118, 1, fileIdxCpy, 0, 0, 0x70, 0x60, 0, 0);
            MemCard_SaveInfoClear(&g_MemCard_SaveWork.saveInfo_318);
            MemCard_FilenameGenerate(filePath, fileIdxCpy);

            if (MemCard_WorkSet(MemCardIoMode_Create, statusPtr->deviceId_4, NULL, filePath, 1, 0, &g_MemCard_SaveWork.saveBlock_118, 0x300))
            {
                statusPtr->processState_10 = 2;
            }
            break;

        case 2: // Checks if previous step was successful.
            memCardResult = MemCard_StateResult();
            switch (memCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = memCardResult;
                    ptr->status_0 = 1;
                    break;

                case MemCardResult_FileCreateError:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = memCardResult;
                    ptr->status_0 = 0;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    MemCard_RamClear(statusPtr->deviceId_4);

                    statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
                    ptr->status_0 = 0;

                    MemCard_FilenameGenerate(filePath, fileIdxCpy);
                    MemCard_FileClear(statusPtr->deviceId_4, filePath);
                    break;

                case MemCardResult_FileIoComplete:
                    ptr->fileState_4[fileIdxCpy] = FileState_Used;

                    if (statusPtr->processId_0 == MemCardProcess_Save_3)
                    {
                        statusPtr->processState_10 = 3;
                    }
                    else
                    {
                        statusPtr->processState_10 = 5;
                    }
                    break;

                default:
                    break;
            }
            break;

        case 3: // Copies and saves user configs.
            MemCard_UserConfigCopy(&g_MemCard_SaveWork.userConfig_418, &g_GameWorkConst->config_0);
            MemCard_FilenameGenerate(filePath, fileIdxCpy);

            if (MemCard_WorkSet(MemCardIoMode_Write, statusPtr->deviceId_4, NULL, filePath, 0, 0x300, &g_MemCard_SaveWork.userConfig_418, 0x80))
            {
                statusPtr->processState_10 = 4;
            }
            break;

        case 4: // Checks if previous step was successful.
            memCardResult = MemCard_StateResult();
            switch (memCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = memCardResult;
                    ptr->status_0 = 1;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
                    ptr->status_0 = 0;
                    break;

                case MemCardResult_FileIoComplete:
                    statusPtr->lastMemCardResult_14 = memCardResult;
                    break;

                default:
                    break;
            }
            break;

        case 5: // Copies and saves user progress.
            MemCard_FilenameGenerate(filePath, fileIdxCpy);
            MemCard_GameDataCopy(&g_MemCard_SaveWork.saveGame_498, g_SavegamePtr);

            if (MemCard_WorkSet(MemCardIoMode_Write, statusPtr->deviceId_4, NULL, filePath, 0, (statusPtr->saveIdx_C * 0x280) + 0x380, &g_MemCard_SaveWork.saveGame_498, 0x280))
            {
                statusPtr->processState_10 = 6;
            }
            break;

        case 6: // Checks if previous step was successful
            memCardResult = MemCard_StateResult();
            switch (memCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = memCardResult;
                    ptr->status_0                   = 1;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
                    ptr->status_0                   = 0;
                    break;

                case MemCardResult_FileIoComplete:
                    statusPtr->processState_10 = 7;
                    break;
            }
            break;

        case 7: // Updates total save games count.
            MemCard_TotalSavegameCountUpdate(statusPtr->deviceId_4, fileIdxCpy, statusPtr->saveIdx_C, g_SavegamePtr);
            statusPtr->processState_10 = 8;

        case 8: // Saves header information progress.
            MemCard_FilenameGenerate(filePath, fileIdxCpy);

            if (MemCard_WorkSet(MemCardIoMode_Write, statusPtr->deviceId_4, NULL, filePath, 0, 512, (u8*)g_MemCard_SaveWork.devices_0[statusPtr->deviceId_4].saveHeader_14 + (fileIdxCpy * sizeof(s_MemCard_SaveHeader)), sizeof(s_MemCard_SaveHeader)))
            {
                statusPtr->processState_10 = 9;
            }
            break;

        case 9: // Checks if previous step was successful
            memCardResult = MemCard_StateResult();
            switch (memCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = memCardResult;
                    ptr->status_0 = 1;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    MemCard_RamClear(statusPtr->deviceId_4);
                    statusPtr->lastMemCardResult_14 = MemCardResult_FileIoError;
                    ptr->status_0 = 0;
                    break;

                case MemCardResult_FileIoComplete:
                    statusPtr->lastMemCardResult_14 = memCardResult;
                    break;
            }
            break;
    }
}

void MemCard_SaveInfoClear(s_MemCard_SaveHeader* saveInfo) // 0x8002FB64
{
    s32 i;

    bzero(saveInfo, sizeof(s_MemCard_SaveHeader));

    for (i = 0; i < MEMCARD_SAVES_COUNT_MAX; i++)
    {
        saveInfo->saveMetadata_4[i].totalSavegameCount_0 = 0;
    }

    MemCard_ChecksumUpdate(&saveInfo->footer_FC, (s8*)saveInfo, sizeof(s_MemCard_SaveHeader));
}

void MemCard_UserConfigCopy(s_Savegame_UserConfigs* dest, s_SaveUserConfig* src) // 0x8002FBB4
{
    bzero(dest, sizeof(s_Savegame_UserConfigs));
    dest->config_0 = *src;
    MemCard_ChecksumUpdate(&dest->footer_7C, &dest->config_0, sizeof(s_Savegame_UserConfigs));
}

s32 MemCard_BiggestTotalSavegameCountGet(s32 deviceId) // 0x8002FC3C
{
    s32 totalSavegameCount;
    s32 saveIdx;
    s32 fileIdx;
    s32 biggesttotalSavegameCount;
    s32 fileIdxWithBiggestTotalSavegameCount;

    fileIdxWithBiggestTotalSavegameCount = NO_VALUE;
    biggesttotalSavegameCount            = NO_VALUE;

    for (fileIdx = 0; fileIdx < MEMCARD_FILE_COUNT_MAX; fileIdx++)
    {
        if (g_MemCard_SaveWork.devices_0[deviceId].fileState_4[fileIdx] != FileState_Used)
        {
            continue;
        }

        for (saveIdx = 0; saveIdx < MEMCARD_SAVES_COUNT_MAX; saveIdx++)
        {
            totalSavegameCount = g_MemCard_SaveWork.devices_0[deviceId].saveHeader_14[fileIdx].saveMetadata_4[saveIdx].totalSavegameCount_0;
            if (biggesttotalSavegameCount < totalSavegameCount)
            {
                fileIdxWithBiggestTotalSavegameCount = fileIdx;
                biggesttotalSavegameCount            = totalSavegameCount;
            }
        }
    }

    return fileIdxWithBiggestTotalSavegameCount;
}

void MemCard_GameDataCopy(s_Savegame_Container* dest, s_Savegame* src) // 0x8002FCCC
{
    bzero(dest, sizeof(s_Savegame_Container));
    memcpy(&dest->savegame_0, src, sizeof(s_Savegame));
    MemCard_ChecksumUpdate(&dest->footer_27C, &dest->savegame_0, sizeof(s_Savegame_Container));
}

void MemCard_TotalSavegameCountUpdate(s32 deviceId, s32 fileIdx, s32 saveIdx, s_Savegame* arg3) // 0x8002FD5C
{
    s_MemCard_SaveHeader* ptr;

    ptr = &g_MemCard_SaveWork.devices_0[deviceId].saveHeader_14[fileIdx];

    MemCard_TotalSavegameCountStepUpdate(deviceId, fileIdx, saveIdx);
    MemCard_ChecksumUpdate(&ptr->footer_FC, ptr, sizeof(s_MemCard_SaveHeader));
}

void MemCard_TotalSavegameCountStepUpdate(s32 deviceId, s32 fileIdx, s32 saveIdx)
{
    s32                      i;
    s32                      totalSavegameCount;
    s_MemCard_TotalSavesInfo saveInfo;

    totalSavegameCount = 0;
    for (i = 0; i < MEMCARD_DEVICE_COUNT_MAX; i++)
    {
        MemCard_SaveWithBiggestTotalSavegameCountGet(i, &saveInfo);

        if (totalSavegameCount < saveInfo.totalSavegameCount_0)
        {
            totalSavegameCount = saveInfo.totalSavegameCount_0;
        }
    }

    g_MemCard_SaveWork.devices_0[deviceId].saveHeader_14[fileIdx].saveMetadata_4[saveIdx].totalSavegameCount_0 = totalSavegameCount + 1;
}

void MemCard_SaveWithBiggestTotalSavegameCountGet(s32 deviceId, s_MemCard_TotalSavesInfo* result)
{
    s32 totalSavegameCount;
    s32 saveIdx;
    s32 fileIdx;

    result->fileIdx_4            = 0;
    result->saveIdx_8            = 0;
    result->totalSavegameCount_0 = 0;

    if (g_MemCard_SaveWork.devices_0[deviceId].status_0 != 3)
    {
        return;
    }

    for (fileIdx = 0; fileIdx < MEMCARD_FILE_COUNT_MAX; fileIdx++)
    {
        if (g_MemCard_SaveWork.devices_0[deviceId].fileState_4[fileIdx] != FileState_Used)
        {
            continue;
        }

        for (saveIdx = 0; saveIdx < MEMCARD_SAVES_COUNT_MAX; saveIdx++)
        {
            totalSavegameCount = g_MemCard_SaveWork.devices_0[deviceId].saveHeader_14[fileIdx].saveMetadata_4[saveIdx].totalSavegameCount_0;

            if (result->totalSavegameCount_0 < totalSavegameCount)
            {
                result->fileIdx_4            = fileIdx;
                result->saveIdx_8            = saveIdx;
                result->totalSavegameCount_0 = totalSavegameCount;
            }
        }
    }
}

// ========================================
// MEMORY CARD - CHECKSUM
// ========================================

void MemCard_ChecksumUpdate(s_Savegame_Footer* saveFooter, s8* saveData, s32 saveDataLength) // 0x8002FF30
{
    u8 checksum;

    saveFooter->checksum_0[0] = saveFooter->checksum_0[1] = 0;
    saveFooter->magic_2                                   = SAVEGAME_FOOTER_MAGIC;
    checksum                                              = MemCard_ChecksumGenerate(saveData, saveDataLength);
    saveFooter->checksum_0[0] = saveFooter->checksum_0[1] = checksum;
}

bool MemCard_ChecksumValidate(s_Savegame_Footer* saveFooter, s8* saveData, s32 saveDataLength) // 0x8002FF74
{
    bool isValid = false;

    if (saveFooter->checksum_0[0] == MemCard_ChecksumGenerate(saveData, saveDataLength))
    {
        isValid = saveFooter->magic_2 == SAVEGAME_FOOTER_MAGIC;
    }

    return isValid;
}

u8 MemCard_ChecksumGenerate(s8* saveData, s32 saveDataLength) // 0x8002FFD0
{
    u8  checksum = 0;
    s32 i        = 0;

    for (i = 0; i < saveDataLength;)
    {
        i++;
        checksum ^= *saveData++;
    }

    return checksum;
}

// ========================================
// MEMORY CARD - HELPERS 2
// ========================================

void MemCard_FilenameGenerate(char* dest, s32 fileIdx) // 0x80030000
{
    char buf[3];

    strcpy(dest, "BA");
    strcat(dest, VERSION_SERIAL);
    strcat(dest, "SILENT");

    buf[0] = '0' + (fileIdx / 10);
    buf[1] = '0' + (fileIdx % 10);
    buf[2] = 0;

    strcat(dest, buf);
}

void MemCard_SaveBlockInit(s_PsxSaveBlock* saveBlock, s8 blockCount, s32 saveIdx, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) // 0x800300B4
{
    char      saveIdxStr[8];
    TIM_IMAGE iconTexture;

    bzero(saveBlock, sizeof(s_PsxSaveBlock));

    saveBlock->magic_0[0]        = 'S';
    saveBlock->magic_0[1]        = 'C';
    saveBlock->iconDisplayFlag_2 = 0x11; // ICON_HAS_1_STATIC_FRAME
    saveBlock->blockCount_3      = blockCount;
    bzero(saveBlock->titleNameShiftJis_4, 0x40);

    strcpy(saveIdxStr, "００");
    saveIdxStr[1] += (saveIdx + 1) / 10;
    saveIdxStr[3] += (saveIdx + 1) % 10;

#if defined(VERSION_NTSC) || defined(VERSION_PAL)
    strcpy(saveBlock->titleNameShiftJis_4, "ＳＩＬＥＮＴ　ＨＩＬＬ");
    strcat(saveBlock->titleNameShiftJis_4, "　　ＦＩＬＥ");
#elif defined(VERSION_NTSCJ)
    strcpy(saveBlock->titleNameShiftJis_4, "サイレントヒル");
    strcat(saveBlock->titleNameShiftJis_4, "　ファイル");
#endif

    strcat(saveBlock->titleNameShiftJis_4, saveIdxStr);

    bzero(saveBlock->field_44, 0x1C);

    OpenTIM(&D_800A8D98);
    ReadTIM(&iconTexture);

    memcpy(saveBlock->iconPalette_60, iconTexture.caddr, iconTexture.crect->w * iconTexture.crect->h * 2);
    memcpy(saveBlock->textureData_80, iconTexture.paddr, iconTexture.prect->w * iconTexture.prect->h * 2);
}

s32 MemCard_DeviceTest(s32 deviceId) // 0x80030288
{
    u8 cardBuf[128];

    memset(cardBuf, 0xFF, 128);

    MemCard_HwEventsReset();
    _new_card();
    _card_write(((deviceId & (1 << 2)) << 2) | (deviceId & 0x3), 0, cardBuf);

    g_MemCard_Work.devicesPending_0 |= 1 << g_MemCard_Work.deviceId_3C;

    return MemCard_HwEventsTest() != 0;
}

s32 MemCard_DeviceFormat(s32 deviceId) // 0x8003030C
{
    #define BUF_SIZE 16

    char buf[BUF_SIZE];

    MemCard_DevicePathGenerate(deviceId, buf);

    return format(buf);

    #undef BUF_SIZE
}

s32 MemCard_FileClear(s32 deviceId, char* fileName) // 0x80030334
{
    #define BUF_SIZE 32

    char buf[BUF_SIZE];

    MemCard_DevicePathGenerate(deviceId, buf);

    strcat(buf, fileName);

    return erase(buf);

    #undef BUF_SIZE
}

s32 MemCard_FileRename(s32 deviceId, char* prevName, char* newName) // 0x80030370
{
    #define BUF_SIZE 32

    char prevBuf[BUF_SIZE];
    char newBuf[BUF_SIZE];

    MemCard_DevicePathGenerate(deviceId, prevBuf);
    MemCard_DevicePathGenerate(deviceId, newBuf);

    strcat(prevBuf, prevName);
    strcat(newBuf, newName);

    return rename(prevBuf, newBuf);

    #undef BUF_SIZE
}

// ========================================
// MEMORY CARD - EVENTS
// ========================================

void MemCard_Init(void) // 0x800303E4
{
    InitCARD(0);
    StartCARD();
    g_MemCard_Work.devicesPending_0 = UINT_MAX; // All bits set.
}

void MemCard_EventsInit(void) // 0x80030414
{
    MemCard_StateInit();
    MemCard_SwEventsInit();
    MemCard_HwEventsInit();
}

void MemCard_StateInit(void) // 0x80030444
{
    g_MemCard_Work.state_4       = MemCardCardState_Idle;
    g_MemCard_Work.stateStep_8   = 0;
    g_MemCard_Work.stateResult_C = 0;
}

void MemCard_SwEventsInit(void) // 0x8003045C
{
    EnterCriticalSection();
    g_MemCard_Work.eventSwSpIOE_10    = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    g_MemCard_Work.eventSwSpERROR_14  = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    g_MemCard_Work.eventSwSpTIMOUT_18 = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    g_MemCard_Work.eventSwSpNEW_1C    = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    ExitCriticalSection();

    EnableEvent(g_MemCard_Work.eventSwSpIOE_10);
    EnableEvent(g_MemCard_Work.eventSwSpERROR_14);
    EnableEvent(g_MemCard_Work.eventSwSpTIMOUT_18);
    EnableEvent(g_MemCard_Work.eventSwSpNEW_1C);

    MemCard_SwEventsReset();
}

void MemCard_HwEventsInit(void) // 0x80030530
{
    EnterCriticalSection();
    g_MemCard_Work.eventHwSpIOE_20     = OpenEvent(HwCARD, EvSpIOE, EvMdINTR, MemCard_HwEventSpIOE);
    g_MemCard_Work.eventHwSpERROR_24   = OpenEvent(HwCARD, EvSpERROR, EvMdINTR, MemCard_HwEventSpERROR);
    g_MemCard_Work.eventHwSpTIMOUT_28  = OpenEvent(HwCARD, EvSpTIMOUT, EvMdINTR, MemCard_HwEventSpTIMOUT);
    g_MemCard_Work.eventHwSpNEW_2C     = OpenEvent(HwCARD, EvSpNEW, EvMdINTR, MemCard_HwEventSpNEW);
    g_MemCard_Work.eventHwSpUNKNOWN_30 = OpenEvent(HwCARD, EvSpUNKNOWN, EvMdINTR, MemCard_HwEventSpUNKNOWN);
    ExitCriticalSection();

    EnableEvent(g_MemCard_Work.eventHwSpIOE_20);
    EnableEvent(g_MemCard_Work.eventHwSpERROR_24);
    EnableEvent(g_MemCard_Work.eventHwSpTIMOUT_28);
    EnableEvent(g_MemCard_Work.eventHwSpNEW_2C);
    EnableEvent(g_MemCard_Work.eventHwSpUNKNOWN_30);

    MemCard_HwEventsReset();
}

void MemCard_EventsClose(void) // 0x80030640
{
    MemCard_SwEventsClose();
    MemCard_HwEventsClose();
}

void MemCard_SwEventsClose(void) // 0x80030668
{
    EnterCriticalSection();
    CloseEvent(g_MemCard_Work.eventSwSpIOE_10);
    CloseEvent(g_MemCard_Work.eventSwSpERROR_14);
    CloseEvent(g_MemCard_Work.eventSwSpTIMOUT_18);
    CloseEvent(g_MemCard_Work.eventSwSpNEW_1C);
    ExitCriticalSection();
}

void MemCard_HwEventsClose(void) // 0x800306C8
{
    EnterCriticalSection();
    CloseEvent(g_MemCard_Work.eventHwSpIOE_20);
    CloseEvent(g_MemCard_Work.eventHwSpERROR_24);
    CloseEvent(g_MemCard_Work.eventHwSpTIMOUT_28);
    CloseEvent(g_MemCard_Work.eventHwSpNEW_2C);
    CloseEvent(g_MemCard_Work.eventHwSpUNKNOWN_30);
    ExitCriticalSection();
}

s32 MemCard_SwEventsTest(void) // 0x80030734
{
    if (TestEvent(g_MemCard_Work.eventSwSpERROR_14) == 1)
    {
        return EvSpERROR;
    }

    if (TestEvent(g_MemCard_Work.eventSwSpTIMOUT_18) == 1)
    {
        return EvSpTIMOUT;
    }

    if (TestEvent(g_MemCard_Work.eventSwSpNEW_1C) == 1)
    {
        return EvSpNEW;
    }

    if (TestEvent(g_MemCard_Work.eventSwSpIOE_10) == 1)
    {
        return EvSpIOE;
    }

    return 0;
}

void MemCard_SwEventsReset(void) // 0x800307BC
{
    TestEvent(g_MemCard_Work.eventSwSpERROR_14);
    TestEvent(g_MemCard_Work.eventSwSpTIMOUT_18);
    TestEvent(g_MemCard_Work.eventSwSpNEW_1C);
    TestEvent(g_MemCard_Work.eventSwSpIOE_10);
}

s32 MemCard_HwEventsTest(void) // 0x80030810
{
    return g_MemCard_Work.lastEventHw_34;
}

void MemCard_HwEventsReset(void) // 0x80030820
{
    TestEvent(g_MemCard_Work.eventHwSpERROR_24);
    TestEvent(g_MemCard_Work.eventHwSpTIMOUT_28);
    TestEvent(g_MemCard_Work.eventHwSpNEW_2C);
    TestEvent(g_MemCard_Work.eventHwSpIOE_20);
    TestEvent(g_MemCard_Work.eventHwSpUNKNOWN_30);

    g_MemCard_Work.lastEventHw_34 = 0;
}

void MemCard_HwEventSpIOE(void) // 0x80030884
{
    g_MemCard_Work.lastEventHw_34 = EvSpIOE;
}

void MemCard_HwEventSpERROR(void) // 0x80030894
{
    g_MemCard_Work.lastEventHw_34 = EvSpERROR;
}

void MemCard_HwEventSpNEW(void) // 0x800308A4
{
    g_MemCard_Work.lastEventHw_34 = EvSpNEW;
}

void MemCard_HwEventSpTIMOUT(void) // 0x800308B4
{
    g_MemCard_Work.lastEventHw_34 = EvSpTIMOUT;
}

void MemCard_HwEventSpUNKNOWN(void) // 0x800308C4
{
    g_MemCard_Work.lastEventHw_34 = EvSpUNKNOWN;
}

// ========================================
// MEMORY CARD - STATES WORK
// ========================================

s32 MemCard_StateResult(void) // 0x800308D4
{
    return g_MemCard_Work.stateResult_C;
}

bool MemCard_WorkSet(e_MemCardIoMode mode, s32 deviceId, s_MemCard_Directory* outDir, char* filename, s32 createBlockCount, s32 fileOffset, void* outBuf, s32 bufSize) // 0x800308E4
{
    if (MemCard_MemCardIsIdle() == false)
    {
        return false;
    }

    g_MemCard_Work.MemCardIoMode_38 = mode;

    switch (mode)
    {
        case MemCardIoMode_Init:
        case MemCardIoMode_DirRead:
            g_MemCard_Work.state_4     = MemCardCardState_Init;
            g_MemCard_Work.stateStep_8 = 0;
            break;

        case MemCardIoMode_Read:
        case MemCardIoMode_Write:
            g_MemCard_Work.state_4     = MemCardCardState_FileOpen;
            g_MemCard_Work.stateStep_8 = 0;
            break;

        case MemCardIoMode_Create:
            g_MemCard_Work.state_4     = MemCardCardState_FileCreate;
            g_MemCard_Work.stateStep_8 = 0;
            break;

        default:
            break;
    }

    g_MemCard_Work.deviceId_3C    = deviceId;
    g_MemCard_Work.directories_40 = outDir;

    MemCard_DevicePathGenerate(deviceId, g_MemCard_Work.filePath_44);
    strcat(g_MemCard_Work.filePath_44, filename);

    g_MemCard_Work.createBlockCount_60 = createBlockCount;
    g_MemCard_Work.seekOffset_64       = fileOffset;
    g_MemCard_Work.dataBuffer_68       = outBuf;
    g_MemCard_Work.dataSize_6C         = bufSize;
    g_MemCard_Work.hasNewDevice_70     = false;
    return true;
}

bool MemCard_MemCardIsIdle(void) // 0x800309FC
{
    return g_MemCard_Work.state_4 == MemCardCardState_Idle;
}

void MemCard_StateUpdate(void) // 0x80030A0C
{
    switch (g_MemCard_Work.state_4)
    {
        case MemCardCardState_Idle:
            // @hack Probably some optimized out code here.
            g_MemCard_Work.stateResult_C += 0;
            break;

        case MemCardCardState_Init:
            g_MemCard_Work.stateResult_C = MemCard_State_Init();
            break;

        case MemCardCardState_Check:
            g_MemCard_Work.stateResult_C = MemCard_State_Check();
            break;

        case MemCardCardState_Load:
            g_MemCard_Work.stateResult_C = MemCard_State_Load();
            break;

        case MemCardCardState_DirRead:
            g_MemCard_Work.stateResult_C = MemCard_State_DirRead();
            break;

        case MemCardCardState_FileCreate:
            g_MemCard_Work.stateResult_C = MemCard_State_FileCreate();
            break;

        case MemCardCardState_FileOpen:
            g_MemCard_Work.stateResult_C = MemCard_State_FileOpen();
            break;

        case MemCardCardState_FileReadWrite:
            g_MemCard_Work.stateResult_C = MemCard_State_FileReadWrite();
            break;

        default:
            break;
    }
}

s32 MemCard_State_Init(void) // 0x80030AD8
{
    s32 channel;
    s32 result;

    result  = MemCardResult_Success;
    channel = ((g_MemCard_Work.deviceId_3C & (1 << 2)) << 2) + (g_MemCard_Work.deviceId_3C & ((1 << 0) | (1 << 1)));

    switch (g_MemCard_Work.stateStep_8)
    {
        case 0:
            g_MemCard_Work.retryCount_78 = 0;
            g_MemCard_Work.field_7C      = 0;
            g_MemCard_Work.stateStep_8   = 1;

        case 1:
            MemCard_SwEventsReset();

            if (_card_info(channel) == 1)
            {
                g_MemCard_Work.stateStep_8++;
            }
            else
            {
                g_MemCard_Work.retryCount_78++;
            }
            break;

        case 2:
            switch (MemCard_SwEventsTest())
            {
                case EvSpIOE: // Connected.
                    if (g_MemCard_Work.MemCardIoMode_38 == MemCardIoMode_Init)
                    {
                        result                     = MemCardResult_InitComplete;
                        g_MemCard_Work.state_4     = MemCardCardState_Idle;
                        g_MemCard_Work.stateStep_8 = 0;
                    }
                    else if (!((g_MemCard_Work.devicesPending_0 >> g_MemCard_Work.deviceId_3C) & (1 << 0)))
                    {
                        g_MemCard_Work.state_4     = MemCardCardState_DirRead;
                        g_MemCard_Work.stateStep_8 = 0;
                    }
                    else
                    {
                        g_MemCard_Work.state_4     = MemCardCardState_Check;
                        g_MemCard_Work.stateStep_8 = 0;
                    }
                    break;

                case EvSpNEW: // "No writing after connection"
                    g_MemCard_Work.hasNewDevice_70 = true;

                    if (g_MemCard_Work.MemCardIoMode_38 == MemCardIoMode_Init)
                    {
                        result                 = MemCardResult_InitError;
                        g_MemCard_Work.state_4     = MemCardCardState_Idle;
                        g_MemCard_Work.stateStep_8 = 0;
                    }
                    else
                    {
                        g_MemCard_Work.state_4     = MemCardCardState_Check;
                        g_MemCard_Work.stateStep_8 = 0;
                    }
                    break;

                case EvSpTIMOUT: // Not connected.
                    result                 = MemCardResult_NotConnected;
                    g_MemCard_Work.state_4     = MemCardCardState_Idle;
                    g_MemCard_Work.stateStep_8 = 0;
                    break;

                case EvSpERROR: // Error.
                    g_MemCard_Work.stateStep_8 = 1;
                    break;
            }
            break;
    }

    return result;
}

s32 MemCard_State_Check(void) // 0x80030C88
{
    s32 channel;
    s32 result;

    result  = MemCardResult_Success;
    channel = ((g_MemCard_Work.deviceId_3C & (1 << 2)) << 2) + (g_MemCard_Work.deviceId_3C & ((1 << 0) | (1 << 1)));

    switch (g_MemCard_Work.stateStep_8)
    {
        case 0:
            g_MemCard_Work.retryCount_78 = 0;
            g_MemCard_Work.field_7C      = 0;
            g_MemCard_Work.stateStep_8   = 1;

        case 1:
            MemCard_HwEventsReset();

            if (_card_clear(channel) == 1)
            {
                g_MemCard_Work.stateStep_8++;
            }
            break;

        case 2:
            switch (MemCard_HwEventsTest())
            {
                case EvSpIOE: // Completed.
                    g_MemCard_Work.state_4     = MemCardCardState_Load;
                    g_MemCard_Work.stateStep_8 = 0;
                    break;

                case EvSpTIMOUT: // Card not connected.
                    result                 = MemCardResult_NotConnected;
                    g_MemCard_Work.state_4     = MemCardCardState_Idle;
                    g_MemCard_Work.stateStep_8 = 0;
                    break;

                case EvSpNEW:   // New card detected.
                case EvSpERROR: // Error.
                    g_MemCard_Work.stateStep_8 = 1;
                    break;
            }
            break;
    }

    return result;
}

s32 MemCard_State_Load(void) // 0x80030DC8
{
    s32 channel;
    s32 result;

    result  = MemCardResult_Success;
    channel = ((g_MemCard_Work.deviceId_3C & (1 << 2)) << 2) + (g_MemCard_Work.deviceId_3C & ((1 << 0) | (1 << 1)));

    switch (g_MemCard_Work.stateStep_8)
    {
        case 0:
            g_MemCard_Work.retryCount_78 = 0;
            g_MemCard_Work.field_7C      = 0;
            g_MemCard_Work.stateStep_8   = 1;

        case 1:
            MemCard_SwEventsReset();

            if (_card_load(channel) == 1)
            {
                g_MemCard_Work.stateStep_8++;
                if (!(g_MemCard_Work.deviceId_3C & (1 << 2)))
                {
                    g_MemCard_Work.devicesPending_0 |= 0xF;
                }
                else
                {
                    g_MemCard_Work.devicesPending_0 |= 0xF0;
                }
            }
            break;

        case 2:
            switch (MemCard_SwEventsTest())
            {
                case EvSpIOE: // Read completed.
                    g_MemCard_Work.state_4           = MemCardCardState_DirRead;
                    g_MemCard_Work.stateStep_8       = 0;
                    g_MemCard_Work.devicesPending_0 &= ~(1 << g_MemCard_Work.deviceId_3C);
                    break;

                case EvSpNEW: // Uninitialized card.
                    g_MemCard_Work.devicesPending_0 |= 1 << g_MemCard_Work.deviceId_3C;
                    if (g_MemCard_Work.retryCount_78 < 3)
                    {
                        g_MemCard_Work.retryCount_78++;
                        g_MemCard_Work.stateStep_8 = 1;
                    }
                    else
                    {
                        result                 = MemCardResult_LoadError;
                        g_MemCard_Work.state_4     = MemCardCardState_Idle;
                        g_MemCard_Work.stateStep_8 = 0;
                    }
                    break;

                case EvSpTIMOUT: // Not connected.
                    result                 = MemCardResult_NotConnected;
                    g_MemCard_Work.state_4     = MemCardCardState_Idle;
                    g_MemCard_Work.stateStep_8 = 0;
                    break;

                case EvSpERROR: // Error.
                    g_MemCard_Work.stateStep_8 = 1;
                    break;
            }
            break;
    }

    return result;
}

s32 MemCard_State_DirRead(void) // 0x80030F7C
{
    struct DIRENTRY  fileInfo;
    struct DIRENTRY* curFile;
    char             filePath[16];
    s32              result;
    s32              i;

    for (i = 0; i < MEMCARD_FILE_COUNT_MAX; i++)
    {
        MemCard_DirectoryFileClear(i);
    }

    for (i = 0; i < MEMCARD_FILE_COUNT_MAX; i++)
    {
        if (i == 0)
        {
            MemCard_DevicePathGenerate(g_MemCard_Work.deviceId_3C, filePath);
            strcat(filePath, "*");
            curFile = firstfile(filePath, &fileInfo);
        }
        else
        {
            curFile = nextfile(&fileInfo);
        }

        if (curFile == NULL)
        {
            break;
        }

        strcpy(g_MemCard_Work.directories_40->filenames_0[i], fileInfo.name);
        g_MemCard_Work.directories_40->blockCounts_13B[i] = (fileInfo.size + (8192 - 1)) / 8192;
    }

    result = (g_MemCard_Work.hasNewDevice_70 == true) ? MemCardResult_NewDevice : MemCardResult_NoNewDevice;

    g_MemCard_Work.state_4     = MemCardCardState_Idle;
    g_MemCard_Work.stateStep_8 = 0;

    return result;
}

s32 MemCard_State_FileCreate(void) // 0x800310B4
{
    s32 result;

    result = MemCardResult_Success;

    switch (g_MemCard_Work.stateStep_8)
    {
        case 0:
            g_MemCard_Work.retryCount_78 = 0;
            g_MemCard_Work.field_7C      = 0;
            g_MemCard_Work.stateStep_8   = 1;

        case 1:
            g_MemCard_Work.fileHandle_74 = open(g_MemCard_Work.filePath_44, (g_MemCard_Work.createBlockCount_60 << 16) | O_CREAT);
            if (g_MemCard_Work.fileHandle_74 == NO_VALUE)
            {
                if (g_MemCard_Work.retryCount_78++ >= 15)
                {
                    result                 = MemCardResult_FileCreateError;
                    g_MemCard_Work.state_4     = MemCardCardState_Idle;
                    g_MemCard_Work.stateStep_8 = 0;
                    break;
                }
            }
            else
            {
                close(g_MemCard_Work.fileHandle_74);
                g_MemCard_Work.state_4     = MemCardCardState_FileOpen;
                g_MemCard_Work.stateStep_8 = 0;
            }
            break;
    }

    return result;
}

s32 MemCard_State_FileOpen(void) // 0x80031184
{
    s32 mode;
    s32 result;

    result = MemCardResult_Success;

    switch (g_MemCard_Work.stateStep_8)
    {
        case 0:
            g_MemCard_Work.retryCount_78 = 0;
            g_MemCard_Work.field_7C      = 0;
            g_MemCard_Work.stateStep_8   = 1;

        case 1:
            switch (g_MemCard_Work.MemCardIoMode_38)
            {
                case MemCardIoMode_Read:
                    mode = O_RDONLY;
                    break;

                case MemCardIoMode_Write:
                case MemCardIoMode_Create:
                    mode = O_WRONLY;
                    break;

                default:
                    mode = 0;
                    break;
            }

            g_MemCard_Work.fileHandle_74 = open(g_MemCard_Work.filePath_44, mode | O_NOWAIT);
            if (g_MemCard_Work.fileHandle_74 == NO_VALUE)
            {
                if (g_MemCard_Work.retryCount_78++ >= 15)
                {
                    result                 = MemCardResult_FileOpenError;
                    g_MemCard_Work.state_4     = MemCardCardState_Idle;
                    g_MemCard_Work.stateStep_8 = 0;
                    break;
                }
            }
            else
            {
                g_MemCard_Work.state_4     = MemCardCardState_FileReadWrite;
                g_MemCard_Work.stateStep_8 = 0;
            }
            break;
    }

    return result;
}

s32 MemCard_State_FileReadWrite(void) // 0x80031260
{
    s32 result;
    s32 ioResult;

    result = MemCardResult_Success;

    switch (g_MemCard_Work.stateStep_8)
    {
        case 0:
            g_MemCard_Work.retryCount_78 = 0;
            g_MemCard_Work.field_7C      = 0;
            g_MemCard_Work.stateStep_8   = 1;

        case 1:
            if (lseek(g_MemCard_Work.fileHandle_74, g_MemCard_Work.seekOffset_64, SEEK_SET) == NO_VALUE)
            {
                if (g_MemCard_Work.retryCount_78++ >= 15)
                {
                    result                     = MemCardResult_FileSeekError;
                    g_MemCard_Work.state_4     = MemCardCardState_Idle;
                    g_MemCard_Work.stateStep_8 = 0;
                }
            }
            else
            {
                g_MemCard_Work.retryCount_78 = 0;
                g_MemCard_Work.stateStep_8++;
            }
            break;

        case 2:
            MemCard_SwEventsReset();

            switch (g_MemCard_Work.MemCardIoMode_38)
            {
                case MemCardIoMode_Read:
                    ioResult = read(g_MemCard_Work.fileHandle_74, g_MemCard_Work.dataBuffer_68, g_MemCard_Work.dataSize_6C);
                    break;

                case MemCardIoMode_Write:
                case MemCardIoMode_Create:
                    ioResult = write(g_MemCard_Work.fileHandle_74, g_MemCard_Work.dataBuffer_68, g_MemCard_Work.dataSize_6C);
                    break;

                default:
                    ioResult = NO_VALUE;
                    break;
            }

            if (ioResult == NO_VALUE)
            {
                if (g_MemCard_Work.retryCount_78++ >= 15)
                {
                    result                 = MemCardResult_FileIoError;
                    g_MemCard_Work.state_4     = MemCardCardState_Idle;
                    g_MemCard_Work.stateStep_8 = 0;
                    close(g_MemCard_Work.fileHandle_74);
                }
            }
            else
            {
                g_MemCard_Work.stateStep_8++;
            }
            break;

        case 3:
            switch (MemCard_SwEventsTest())
            {
                case EvSpIOE: // Completed.
                    result                     = MemCardResult_FileIoComplete;
                    g_MemCard_Work.state_4     = MemCardCardState_Idle;
                    g_MemCard_Work.stateStep_8 = 0;
                    close(g_MemCard_Work.fileHandle_74);
                    break;

                case EvSpTIMOUT: // Card not connected.
                    result                     = MemCardResult_NotConnected;
                    g_MemCard_Work.state_4     = MemCardCardState_Idle;
                    g_MemCard_Work.stateStep_8 = 0;
                    close(g_MemCard_Work.fileHandle_74);
                    break;

                case EvSpNEW: // New card detected.
                    result                     = MemCardResult_FileIoError;
                    g_MemCard_Work.state_4     = MemCardCardState_Idle;
                    g_MemCard_Work.stateStep_8 = 0;
                    close(g_MemCard_Work.fileHandle_74);

                case EvSpERROR: // Error.
                    g_MemCard_Work.stateStep_8 = 1;
                    break;
            }
    }

    return result;
}

void MemCard_DevicePathGenerate(s32 deviceId, char* result) // 0x800314A4
{
    strcpy(result, "buXX:");

    // Convert sequential device ID to PSX channel number.
    result[2] = '0' + ((deviceId & (1 << 2)) >> 2);
    result[3] = '0' + (deviceId & ((1 << 0) | (1 << 1)));
}

const s32 pad_rodata_80024C98 = 0x8E080000;
