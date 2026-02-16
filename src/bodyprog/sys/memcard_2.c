#include "game.h"

#include <memory.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"
#include "screens/saveload.h"

s16 g_MemCard_SavegameCount;

s16 pad_bss_800BCD2A;

s_SaveScreenElement* g_MemCard_ActiveSavegameEntry;

u8  g_Savegame_ElementCount0[MEMCARD_SLOT_COUNT_MAX];

s16 pad_bss_800BCD32;

u32 g_MemCard_AllMemCardsStatus;

s8  g_SaveScreen_SaveScreenState;

s8  pad_bss_800BCD39;

s16 g_MemCard_TotalElementsCount;

u8  g_Savegame_ElementCount1[MEMCARD_SLOT_COUNT_MAX];

u8  g_Savegame_SelectedElementIdx;

s8  g_SelectedFileIdx;

s8  g_SelectedDeviceId;

s8  pad_bss_800BCD41[3];

u8 g_SlotElementSelectedIdx[MEMCARD_SLOT_COUNT_MAX] = { 0, 0 };
s8 g_SelectedSaveSlotIdx = 0;
u8 D_800A97D7 = 0;
s8 D_800A97D8 = 0xFF;
s8 D_800A97D9 = 0;

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
    u32                         sp10[MEMCARD_SLOT_COUNT_MAX]; // Boolean.
    s32                         sp18[MEMCARD_DEVICE_COUNT_MAX]; // Boolean. Used to generate `Create New File` and `New Save`.
    u32                         prevStatusCpy;
    s32                         sp3C;
    s32                         preMemCardStatus;
    s32                         fileStatus;
    u32                         memCardStatus1;
    s32                         memCardStatus2;
    u32                         memCardStatus0;
    s32                         memSaveDataIdx;
    s32                         i;
    s32                         j;
    s32                         k;
    u32                         memCardStatus;
    s_MemCard_SaveMetadata*     saveMetadata;
	static s32                  D_800BCD18[2];
	static s32                  D_800BCD20[2];
	static s32                  D_800A97DC = 0; /** `e_SavegameEntryType` */
	static s8                   D_800A97E0 = NO_VALUE;
	static u32                  allFileStatus[MEMCARD_DEVICE_COUNT_MAX] = { };

    sp3C = 1;

    memset(&sp10, 0, 8);
    MemCard_SysInit2();
    MemCard_InitStatus();

    if (g_GameWork.gameState_594 == GameState_SaveScreen ||
        g_GameWork.gameState_594 == GameState_KcetLogo)
    {
        g_SaveScreen_SaveScreenState = SaveScreenState_Save;
    }
    else
    {
        g_SaveScreen_SaveScreenState = SaveScreenState_Load;
    }

    prevStatusCpy                = g_MemCard_AllMemCardsStatus;
    g_MemCard_AllMemCardsStatus  = MemCard_AllMemCardsStatusGet();
    g_MemCard_TotalElementsCount = 0;
    g_MemCard_SavegameCount      = 0;

    for (i = 0; i < MEMCARD_DEVICE_COUNT_MAX; i += 4)
    {
        memCardStatus    = MemCard_StatusGet(g_MemCard_AllMemCardsStatus, i);
        sp3C            *= memCardStatus;
        preMemCardStatus = MemCard_StatusGet(prevStatusCpy, i);
        memSaveDataIdx   = WrapIdx(i);

        g_MemCard_ActiveSavegameEntry                       = MemCard_ActiveSavegameEntryGet(memSaveDataIdx >> 2);
        g_Savegame_ElementCount1[memSaveDataIdx >> 2]       = 0;
        g_Savegame_ElementCount0[memSaveDataIdx >> 2]       = 0;
        sp18[i]                                             = false;
        g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = NO_VALUE;
        g_MemCard_ActiveSavegameEntry->deviceId_5           = i;
        g_MemCard_ActiveSavegameEntry->fileIdx_6            = 0;
        g_MemCard_ActiveSavegameEntry->elementIdx_7         = 0;
        g_MemCard_ActiveSavegameEntry->saveMetadata_C       = NULL;

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

        if (g_SaveScreen_SaveScreenState == SaveScreenState_Save)
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
                    g_MemCard_ActiveSavegameEntry->type_4 = SavegameEntryType_NoMemCard;
                    break;

                case MemCardResult_LoadError:
                    if (g_SaveScreen_SaveScreenState == SaveScreenState_Save)
                    {
                        g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = 31600;
                        memSaveDataIdx                                      = WrapIdx(i);
                        g_Savegame_ElementCount0[memSaveDataIdx >> 2]++;
                    }

                    g_MemCard_ActiveSavegameEntry->type_4 = SavegameEntryType_UnformattedMemCard;
                    break;

                case MemCardResult_NewDevice:
                    g_MemCard_ActiveSavegameEntry->type_4 = SavegameEntryType_CorruptedMemCard;
                    break;

                case MemCardResult_NotConnected:
                case MemCardResult_InitError:
                    g_MemCard_ActiveSavegameEntry->type_4 = SavegameEntryType_LoadMemCard;
                    break;
            }

            g_Savegame_ElementCount1[WrapIdx(i) >> 2]++;
            g_MemCard_ActiveSavegameEntry++;
        }
        else if (MemCard_UsedFileCount(i) == 0)
        {
            if (g_SaveScreen_SaveScreenState == SaveScreenState_Load)
            {
                g_MemCard_ActiveSavegameEntry->type_4 = SavegameEntryType_NoDataInMemCard;
            }
            else if (MemCard_FreeFilesCount(i) == 0)
            {
                g_MemCard_ActiveSavegameEntry->type_4 = SavegameEntryType_OutOfBlocks;
            }
            else
            {
                g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = 31700;
                g_MemCard_ActiveSavegameEntry->type_4               = SavegameEntryType_NewFile;

                memSaveDataIdx = WrapIdx(i);
                g_Savegame_ElementCount0[memSaveDataIdx >> 2]++;
            }

            g_Savegame_ElementCount1[WrapIdx(i) >> 2]++;
            g_MemCard_ActiveSavegameEntry++;
        }
        else if (g_SaveScreen_SaveScreenState == SaveScreenState_Load && MemCard_FilesAreNotUsedCheck(i) != false)
        {
            g_MemCard_ActiveSavegameEntry->type_4 = SavegameEntryType_CorruptedSave;

            memSaveDataIdx = WrapIdx(i);
            g_Savegame_ElementCount1[memSaveDataIdx >> 2]++;
            g_MemCard_ActiveSavegameEntry++;
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
                    g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = 0;
                    g_MemCard_ActiveSavegameEntry->deviceId_5           = i;
                    g_MemCard_ActiveSavegameEntry->fileIdx_6            = j;
                    g_MemCard_ActiveSavegameEntry->elementIdx_7         = 0;
                    g_MemCard_ActiveSavegameEntry->type_4               = SavegameEntryType_CorruptedSave;

                    memSaveDataIdx = WrapIdx(i);

                    g_Savegame_ElementCount0[memSaveDataIdx >> 2]++;
                    g_MemCard_SavegameCount--;
                    g_Savegame_ElementCount1[memSaveDataIdx >> 2]++;

                    g_MemCard_ActiveSavegameEntry++;
                }
                else
                {
                    for (k = 0; k < MEMCARD_SAVES_COUNT_MAX; k++)
                    {
                        saveMetadata = MemCard_SaveMetadataGet(i, j, k);

                        g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = saveMetadata->totalSavegameCount_0;
                        g_MemCard_ActiveSavegameEntry->deviceId_5           = i;
                        g_MemCard_ActiveSavegameEntry->fileIdx_6            = j;
                        g_MemCard_ActiveSavegameEntry->elementIdx_7         = k;
                        g_MemCard_ActiveSavegameEntry->savegameCount_2      = saveMetadata->savegameCount_8;
                        g_MemCard_ActiveSavegameEntry->locationId_8         = saveMetadata->locationId_A;
                        g_MemCard_ActiveSavegameEntry->saveMetadata_C       = saveMetadata;

                        if (saveMetadata->totalSavegameCount_0 > 0)
                        {
                            g_MemCard_ActiveSavegameEntry->type_4 = SavegameEntryType_Save;

                            memSaveDataIdx = WrapIdx(i);

                            g_Savegame_ElementCount0[memSaveDataIdx >> 2]++;
                            g_Savegame_ElementCount1[memSaveDataIdx >> 2]++;
                            g_MemCard_ActiveSavegameEntry++;
                        }
                        else if (g_SaveScreen_SaveScreenState == SaveScreenState_Save && sp18[i] == false)
                        {
                            sp18[i]                                             = true;
                            g_MemCard_ActiveSavegameEntry->type_4               = SavegameEntryType_NewSave;
                            g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = 31900;

                            memSaveDataIdx = WrapIdx(i);
                            g_Savegame_ElementCount0[memSaveDataIdx >> 2]++;
                            g_Savegame_ElementCount1[memSaveDataIdx >> 2]++;
                            g_MemCard_ActiveSavegameEntry++;
                        }
                    }
                }
            }

            if (g_SaveScreen_SaveScreenState == SaveScreenState_Save && sp18[i] == false && MemCard_FreeFilesCount(i) > 0)
            {
                g_MemCard_ActiveSavegameEntry->savegameCount_2      = 0;
                g_MemCard_ActiveSavegameEntry->saveMetadata_C       = NULL;
                sp18[i]                                             = true;
                g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = 31800;
                memCardStatus0                                      = allFileStatus[i];
                memCardStatus1                                      = memCardStatus0 & 0x3;

                for (j = 0; memCardStatus1 == FileState_Damaged || memCardStatus1 == FileState_Used; j++)
                {
                    j++;
                    memCardStatus1 = MemCard_FileStatusGet(memCardStatus0, j);
                    j--;
                }

                g_MemCard_ActiveSavegameEntry->deviceId_5   = i;
                g_MemCard_ActiveSavegameEntry->fileIdx_6    = j;
                g_MemCard_ActiveSavegameEntry->elementIdx_7 = 0;
                g_MemCard_ActiveSavegameEntry->type_4       = SavegameEntryType_NewFile;

                memSaveDataIdx = WrapIdx(i);

                g_Savegame_ElementCount0[memSaveDataIdx >> 2]++;

                fileStatus = MemCard_FileStatusGet(allFileStatus[i], j); // @hack Fixes stack order.

                g_Savegame_ElementCount1[memSaveDataIdx >> 2]++;
                g_MemCard_ActiveSavegameEntry++;
            }
        }

        g_MemCard_TotalElementsCount += g_Savegame_ElementCount0[WrapIdx(i) >> 2];
    }

    g_MemCard_SavegameCount += g_MemCard_TotalElementsCount;

    for (i = 0; i < MEMCARD_DEVICE_COUNT_MAX; i += 4)
    {
        memCardStatus2 = MemCard_StatusGet(g_MemCard_AllMemCardsStatus, i);
        if (memCardStatus2 == FileState_Unused || memCardStatus2 == FileState_Unk2)
        {
            D_800A97E0          = (WrapIdx(i) >> 2) == 0;
            g_MemCard_ActiveSavegameEntry = MemCard_ActiveSavegameEntryGet(D_800A97E0);

            if (g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_NoMemCard)
            {
                D_800A97DC = 24;
            }
            else if (g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_UnformattedMemCard)
            {
                if (g_SaveScreen_SaveScreenState == SaveScreenState_Save)
                {
                    D_800A97DC = 22;
                }
                else
                {
                    D_800A97DC = g_MemCard_ActiveSavegameEntry->type_4;
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
        g_MemCard_ActiveSavegameEntry = MemCard_ActiveSavegameEntryGet(D_800A97E0 == 0);

        g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = NO_VALUE;
        g_MemCard_ActiveSavegameEntry->deviceId_5           = 0;
        g_MemCard_ActiveSavegameEntry->fileIdx_6            = 0;
        g_MemCard_ActiveSavegameEntry->elementIdx_7         = 0;
        g_MemCard_ActiveSavegameEntry->type_4               = SavegameEntryType_LoadMemCard;
        g_Savegame_ElementCount1[D_800A97E0 == 0]           = 1;
        g_MemCard_ActiveSavegameEntry                       = MemCard_ActiveSavegameEntryGet(D_800A97E0);

        if ((g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_UnformattedMemCard && g_SaveScreen_SaveScreenState == SaveScreenState_Save) ||
            g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_Save ||
            g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_NewSave ||
            g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_NewFile)
        {
            g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = NO_VALUE;
            g_MemCard_ActiveSavegameEntry->deviceId_5           = 0;
            g_MemCard_ActiveSavegameEntry->fileIdx_6            = 0;
            g_MemCard_ActiveSavegameEntry->elementIdx_7         = 0;
            g_MemCard_ActiveSavegameEntry->type_4               = SavegameEntryType_LoadMemCard;
            g_Savegame_ElementCount1[D_800A97E0]                = 1;
        }

        sp3C = 0;
    }

    if (D_800A97D9 == 0 && (sp10[0] || sp10[1]))
    {
        for (j = 0; j < 2; j++)
        {
            g_MemCard_ActiveSavegameEntry = MemCard_ActiveSavegameEntryGet(j);
            D_800BCD18[j]       = 0;
            D_800BCD20[j]       = 0;

            for (i = 0; i < g_Savegame_ElementCount1[j]; i++)
            {
                if (D_800BCD18[j] < g_MemCard_ActiveSavegameEntry->totalSavegameCount_0)
                {
                    D_800BCD18[j] = g_MemCard_ActiveSavegameEntry->totalSavegameCount_0;
                    D_800BCD20[j] = i;
                }

                g_MemCard_ActiveSavegameEntry++;
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
const s32 pad_rodata_800251F8[2] = {};
