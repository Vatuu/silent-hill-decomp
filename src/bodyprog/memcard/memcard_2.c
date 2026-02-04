#include "game.h"

#include <memory.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"
#include "screens/saveload.h"

// u8 D_800BCD10[8] = { 0x00, 0x00, 0x00, 0x00, 0x80, 0x18, 0x13, 0x00 }; // @unused 
// // 2 bytes of padding.
// s_SaveScreen_Element* activeSavegameEntry = 0;
// u8 slotElementCount0[MEMCARD_SLOT_COUNT_MAX] = {};
// // bytes of padding.
// u32 allMemCardsStatus = 0;
// s8 saveScreenState = 0;
// s8 D_800BCD39 = 0;
// s16 totalElementsCount = 0;
// u8 slotElementCount1[MEMCARD_SLOT_COUNT_MAX] = {};
// u8 selectedElementIdx = 0;
// s8 selectedFileIdx = 0;
// s8 g_SelectedDeviceId = 0;
// 
// u8 D_800BCD41 = 0x70;
// u8 D_800BCD42 = 0xE5;
// u8 D_800BCD43 = 0x8D;
// u8 D_800BCD44 = 0x05;
// u8 D_800BCD45 = 0x00;
// u8 D_800BCD46 = 0x02;
// u8 D_800BCD47 = 0x24;
/*
s32 g_DemoLoadAttempCount = 0;
s32 D_800BCD4C = 0x24020028; // @unused
s8 D_800BCD50[8] = {};
u32 D_800BCD58 = 0;
s32 D_800BCD5C;
*/

// s32 D_800BCD18[2];
// s32 D_800BCD20[2];
// s16 g_MemCard_SavegameCount;
// s8  g_SelectedDeviceId; 

bool MemCard_FilesAreNotUsedCheck(s32 idx) // 0x800334D8
{
    s32  i;
    bool res;
    s32  allFilesStatus;
    s32  fileStatus;

    res = false;
    allFilesStatus = MemCard_AllFilesStatusGet(idx);

    for (i = 0; i < MEMCARD_FILE_COUNT_MAX; i++)
    {
        fileStatus = MemCard_FileStatusGet(allFilesStatus, i);
        if (fileStatus == FileState_Used)
        {
            return false;
        }

        if (fileStatus == FileState_Damaged)
        {
            res = true;
        }
    }

    return res;
}

static inline s32 WrapIdx(s32 idx)
{
    return (idx < 0) ? (idx + 3) : idx;
}

bool func_80033548(void) // 0x80033548
{
	static s_SaveScreen_Element* activeSavegameEntry;
	static u8                    slotElementCount0[MEMCARD_SLOT_COUNT_MAX];
	static s16                   pad_bss_800BCD32;
	static u32                   allMemCardsStatus;
	static s8                    saveScreenState;
	static s8                    pad_bss_800BCD39;
	static s16                   totalElementsCount;
	static u8                    slotElementCount1[MEMCARD_SLOT_COUNT_MAX];
	static u8                    selectedElementIdx;
	static s8                    selectedFileIdx;
	//static s32                 D_800A97DC = 0;
	//static s8                  D_800A97E0 = 0xFF;
	//static u32                 allFileStatus[MEMCARD_DEVICE_COUNT_MAX] = { };
    u32                          sp10[MEMCARD_SLOT_COUNT_MAX]; // Boolean.
    s32                          sp18[MEMCARD_DEVICE_COUNT_MAX]; // Boolean. Important to generate `Create New File` and `New Save`.
    u32                          prevStatusCpy;
    s32                          sp3C;
    s32                          preMemCardStatus;
    s32                          fileStatus;
    u32                          MemCardStatus1;
    s32                          MemCardStatus2;
    u32                          MemCardStatus0;
    s32                          memSaveDataIdx;
    s32                          i;
    s32                          j;
    s32                          k;
    u32                          memCardStatus;
    s_MemCard_SaveMetadata*      saveMetadata;

    sp3C = 1;

    memset(&sp10, 0, 8);
    MemCard_SysInit2();
    MemCard_InitStatus();

    if (g_GameWork.gameState_594 == GameState_SaveScreen ||
        g_GameWork.gameState_594 == GameState_KcetLogo)
    {
        saveScreenState = SaveScreenState_Save;
    }
    else
    {
        saveScreenState = SaveScreenState_Load;
    }

    prevStatusCpy                = allMemCardsStatus;
    allMemCardsStatus            = MemCard_AllMemCardsStatusGet();
    totalElementsCount           = 0;
    g_MemCard_SavegameCount      = 0;

    for (i = 0; i < MEMCARD_DEVICE_COUNT_MAX; i += 4)
    {
        memCardStatus    = MemCard_StatusGet(allMemCardsStatus, i);
        sp3C            *= memCardStatus;
        preMemCardStatus = MemCard_StatusGet(prevStatusCpy, i);
        memSaveDataIdx   = WrapIdx(i);

        activeSavegameEntry                       = MemCard_ActiveSavegameEntryGet(memSaveDataIdx >> 2);
        slotElementCount1[memSaveDataIdx >> 2]    = 0;
        slotElementCount0[memSaveDataIdx >> 2]    = 0;
        sp18[i]                                   = false;
        activeSavegameEntry->totalSavegameCount_0 = NO_VALUE;
        activeSavegameEntry->deviceId_5           = i;
        activeSavegameEntry->fileIdx_6            = 0;
        activeSavegameEntry->elementIdx_7         = 0;
        activeSavegameEntry->saveMetadata_C       = NULL;

        if (preMemCardStatus == MemCardResult_InitComplete)
        {
            if (memCardStatus != MemCardResult_InitComplete)
            {
                sp10[memSaveDataIdx >> 2] = true;
            }
        }
        else if (memCardStatus == MemCardResult_InitComplete)
        {
            sp10[memSaveDataIdx >> 2] = true;
        }

        if (saveScreenState == SaveScreenState_Save)
        {
            if (preMemCardStatus == MemCardResult_LoadError && memCardStatus != preMemCardStatus)
            {
                sp10[WrapIdx(i) >> 2] = true;
            }

            if (preMemCardStatus != MemCardResult_LoadError && memCardStatus == MemCardResult_LoadError)
            {
                sp10[WrapIdx(i) >> 2] = true;
            }
        }

        if (memCardStatus != MemCardResult_InitComplete)
        {
            switch (memCardStatus)
            {
                case MemCardResult_Success:
                    activeSavegameEntry->type_4 = SavegameEntryType_NoMemCard;
                    break;

                case MemCardResult_LoadError:
                    if (saveScreenState == SaveScreenState_Save)
                    {
                        activeSavegameEntry->totalSavegameCount_0 = 31600;
                        memSaveDataIdx                            = WrapIdx(i);
                        slotElementCount0[memSaveDataIdx >> 2]++;
                    }

                    activeSavegameEntry->type_4 = SavegameEntryType_UnformattedMemCard;
                    break;

                case MemCardResult_NewDevice:
                    activeSavegameEntry->type_4 = SavegameEntryType_CorruptedMemCard;
                    break;

                case MemCardResult_NotConnected:
                case MemCardResult_InitError:
                    activeSavegameEntry->type_4 = SavegameEntryType_LoadMemCard;
                    break;
            }

            slotElementCount1[WrapIdx(i) >> 2]++;
            activeSavegameEntry++;
        }
        else if (MemCard_UsedFileCount(i) == 0)
        {
            if (saveScreenState == SaveScreenState_Load)
            {
                activeSavegameEntry->type_4 = SavegameEntryType_NoDataInMemCard;
            }
            else if (MemCard_FreeFilesCount(i) == 0)
            {
                activeSavegameEntry->type_4 = SavegameEntryType_OutOfBlocks;
            }
            else
            {
                activeSavegameEntry->totalSavegameCount_0 = 31700;
                activeSavegameEntry->type_4               = SavegameEntryType_NewFile;

                memSaveDataIdx = WrapIdx(i);
                slotElementCount0[memSaveDataIdx >> 2]++;
            }

            slotElementCount1[WrapIdx(i) >> 2]++;
            activeSavegameEntry++;
        }
        else if (saveScreenState == SaveScreenState_Load && MemCard_FilesAreNotUsedCheck(i) != false)
        {
            activeSavegameEntry->type_4 = SavegameEntryType_CorruptedSave;

            memSaveDataIdx = WrapIdx(i);
            slotElementCount1[memSaveDataIdx >> 2]++;
            activeSavegameEntry++;
        }
        else
        {
            allFileStatus[i] = MemCard_AllFilesStatusGet(i);

            for (j = 0; j < MEMCARD_FILE_COUNT_MAX; j++)
            {
                fileStatus = MemCard_FileStatusGet(allFileStatus[i], j);

                if (fileStatus == FileState_Unused)
                {
                    continue;
                }

                if (fileStatus == FileState_Damaged)
                {
                    activeSavegameEntry->totalSavegameCount_0 = 0;
                    activeSavegameEntry->deviceId_5           = i;
                    activeSavegameEntry->fileIdx_6            = j;
                    activeSavegameEntry->elementIdx_7         = 0;
                    activeSavegameEntry->type_4               = SavegameEntryType_CorruptedSave;

                    memSaveDataIdx = WrapIdx(i);

                    slotElementCount0[memSaveDataIdx >> 2]++;
                    g_MemCard_SavegameCount--;
                    slotElementCount1[memSaveDataIdx >> 2]++;

                    activeSavegameEntry++;
                }
                else
                {
                    for (k = 0; k < MEMCARD_SAVES_COUNT_MAX; k++)
                    {
                        saveMetadata = MemCard_SaveMetadataGet(i, j, k);

                        activeSavegameEntry->totalSavegameCount_0 = saveMetadata->totalSavegameCount_0;
                        activeSavegameEntry->deviceId_5           = i;
                        activeSavegameEntry->fileIdx_6            = j;
                        activeSavegameEntry->elementIdx_7         = k;
                        activeSavegameEntry->savegameCount_2      = saveMetadata->savegameCount_8;
                        activeSavegameEntry->locationId_8         = saveMetadata->locationId_A;
                        activeSavegameEntry->saveMetadata_C       = saveMetadata;

                        if (saveMetadata->totalSavegameCount_0 > 0)
                        {
                            activeSavegameEntry->type_4 = SavegameEntryType_Save;

                            memSaveDataIdx = WrapIdx(i);

                            slotElementCount0[memSaveDataIdx >> 2]++;
                            slotElementCount1[memSaveDataIdx >> 2]++;
                            activeSavegameEntry++;
                        }
                        else if (saveScreenState == SaveScreenState_Save && sp18[i] == false)
                        {
                            sp18[i]                                   = true;
                            activeSavegameEntry->type_4               = SavegameEntryType_NewSave;
                            activeSavegameEntry->totalSavegameCount_0 = 31900;

                            memSaveDataIdx = WrapIdx(i);
                            slotElementCount0[memSaveDataIdx >> 2]++;
                            slotElementCount1[memSaveDataIdx >> 2]++;
                            activeSavegameEntry++;
                        }
                    }
                }
            }

            if (saveScreenState == SaveScreenState_Save && sp18[i] == false && MemCard_FreeFilesCount(i) > 0)
            {
                activeSavegameEntry->savegameCount_2      = 0;
                activeSavegameEntry->saveMetadata_C       = NULL;
                sp18[i]                                   = true;
                activeSavegameEntry->totalSavegameCount_0 = 31800;
                MemCardStatus0                            = allFileStatus[i];
                MemCardStatus1                            = MemCardStatus0 & 0x3;

                for (j = 0; MemCardStatus1 == FileState_Damaged || MemCardStatus1 == FileState_Used; j++)
                {
                    j++;
                    MemCardStatus1 = MemCard_FileStatusGet(MemCardStatus0, j);
                    j--;
                }

                activeSavegameEntry->deviceId_5   = i;
                activeSavegameEntry->fileIdx_6    = j;
                activeSavegameEntry->elementIdx_7 = 0;
                activeSavegameEntry->type_4       = SavegameEntryType_NewFile;

                memSaveDataIdx = WrapIdx(i);

                slotElementCount0[memSaveDataIdx >> 2]++;

                fileStatus = MemCard_FileStatusGet(allFileStatus[i], j); // @hack Fixes stack order.

                slotElementCount1[memSaveDataIdx >> 2]++;
                activeSavegameEntry++;
            }
        }

        totalElementsCount += slotElementCount0[WrapIdx(i) >> 2];
    }

    g_MemCard_SavegameCount += totalElementsCount;

    for (i = 0; i < MEMCARD_DEVICE_COUNT_MAX; i += 4)
    {
        MemCardStatus2 = MemCard_StatusGet(allMemCardsStatus, i);
        if (MemCardStatus2 == FileState_Unused || MemCardStatus2 == FileState_Unk2)
        {
            D_800A97E0          = (WrapIdx(i) >> 2) == 0;
            activeSavegameEntry = MemCard_ActiveSavegameEntryGet(D_800A97E0);

            if (activeSavegameEntry->type_4 == SavegameEntryType_NoMemCard)
            {
                D_800A97DC = 24;
            }
            else if (activeSavegameEntry->type_4 == SavegameEntryType_UnformattedMemCard)
            {
                if (saveScreenState == SaveScreenState_Save)
                {
                    D_800A97DC = 22;
                }
                else
                {
                    D_800A97DC = activeSavegameEntry->type_4;
                }
            }
            else
            {
                D_800A97DC = 24;
            }
            break;
        }
    }

    D_800A97DC--;

    if (D_800A97DC == 0)
    {
        sp10[D_800A97E0 == 0] = true;
        D_800A97E0            = NO_VALUE;
    }

    if (D_800A97E0 >= 0)
    {
        activeSavegameEntry = MemCard_ActiveSavegameEntryGet(D_800A97E0 == 0);

        activeSavegameEntry->totalSavegameCount_0 = NO_VALUE;
        activeSavegameEntry->deviceId_5           = 0;
        activeSavegameEntry->fileIdx_6            = 0;
        activeSavegameEntry->elementIdx_7         = 0;
        activeSavegameEntry->type_4               = SavegameEntryType_LoadMemCard;
        slotElementCount1[D_800A97E0 == 0]        = 1;
        activeSavegameEntry                       = MemCard_ActiveSavegameEntryGet(D_800A97E0);

        if ((activeSavegameEntry->type_4 == SavegameEntryType_UnformattedMemCard && saveScreenState == SaveScreenState_Save) ||
            activeSavegameEntry->type_4 == SavegameEntryType_Save ||
            activeSavegameEntry->type_4 == SavegameEntryType_NewSave ||
            activeSavegameEntry->type_4 == SavegameEntryType_NewFile)
        {
            activeSavegameEntry->totalSavegameCount_0 = NO_VALUE;
            activeSavegameEntry->deviceId_5           = 0;
            activeSavegameEntry->fileIdx_6            = 0;
            activeSavegameEntry->elementIdx_7         = 0;
            activeSavegameEntry->type_4               = SavegameEntryType_LoadMemCard;
            slotElementCount1[D_800A97E0]             = 1;
        }

        sp3C = 0;
    }

    if (D_800A97D9 == 0 && (sp10[0] || sp10[1]))
    {
        for (j = 0; j < 2; j++)
        {
            activeSavegameEntry = MemCard_ActiveSavegameEntryGet(j);
            D_800BCD18[j]       = 0;
            D_800BCD20[j]       = 0;

            for (i = 0; i < slotElementCount1[j]; i++)
            {
                if (D_800BCD18[j] < activeSavegameEntry->totalSavegameCount_0)
                {
                    D_800BCD18[j] = activeSavegameEntry->totalSavegameCount_0;
                    D_800BCD20[j] = i;
                }

                activeSavegameEntry++;
            }

            if (sp10[j])
            {
                g_SlotElementSelectedIdx[j] = D_800BCD20[j];
            }
        }

        if (D_800BCD18[1] > D_800BCD18[0])
        {
            g_SelectedSaveSlotIdx = 1;
        }
        else
        {
            g_SelectedSaveSlotIdx = 0;
        }

        g_GameWork.gameStateStep_598[1] = 0;
        g_GameWork.gameStateStep_598[2] = 0;
    }

    switch (sp3C)
    {
        case 1:
        case 3:
        case 4:
        case 5:
        case 9:
        case 12:
        case 15:
        case 16:
        case 20:
        case 25:
            return true;

        default:
            return false;
    }
}

const char pad_rodata_800251F4[] = { 0x00, 0x1C, 0x97, 0x50 };
const s32 pad_rodata_800251F8 = 0;
const s32 pad_rodata_800251FC = 0;
