#include "game.h"

#include <memory.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/savegame.h"
#include "screens/saveload.h"
#include "bodyprog/memcard.h"

// u8 D_800BCD10[8] = { 0x00, 0x00, 0x00, 0x00, 0x80, 0x18, 0x13, 0x00 }; // @unused 
// s32 D_800BCD18[2] = {};
// s32 D_800BCD20[2] = {};
// s16 g_MemCard_SavegameCount = 0;
// // 2 bytes of padding.
// s_Savegame_Entry* g_MemCard_ActiveSavegameEntry = 0;
// u8 g_Savegame_ElementCount0[CARD_SLOT_COUNT] = {};
// // bytes of padding.
// u32 g_MemCard_AllMemCardsStatus = 0;
// s8 g_SaveScreen_SaveScreenState = 0;
// s8 D_800BCD39 = 0;
// s16 g_MemCard_TotalElementsCount = 0;
// u8 g_Savegame_ElementCount1[CARD_SLOT_COUNT] = {};
// u8 g_Savegame_SelectedElementIdx = 0;
// s8 g_SelectedFileIdx = 0;
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

bool MemCard_FilesAreNotUsedCheck(s32 idx) // 0x800334D8
{
    s32  i;
    bool res;
    s32  allFilesStatus;
    s32  fileStatus;

    res = false;
    allFilesStatus = MemCard_AllFilesStatusGet(idx);

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
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
	//static s32          D_800A97DC = 0;
	//static s8           D_800A97E0 = 0xFF;
	//static u32          allFileStatus[CARD_DEVICE_COUNT] = { };
    u32                 sp10[CARD_SLOT_COUNT]; // Boolean.
    s32                 sp18[CARD_DEVICE_COUNT]; // Boolean. Important to generate `Create New File` and `New Save`.
    u32                 prevStatusCpy;
    s32                 sp3C;
    s32                 preMemCardStatus;
    s32                 fileStatus;
    u32                 MemCardStatus1;
    s32                 MemCardStatus2;
    u32                 MemCardStatus0;
    s32                 memSaveDataIdx;
    s32                 i;
    s32                 j;
    s32                 k;
    u32                 memCardStatus;
    s_Savegame_Metadata* saveMetadata;

    sp3C = 1;

    memset(&sp10, 0, 8);
    MemCard_SysInit2();
    MemCard_InitStatus();

    if (g_GameWork.gameState_594 == GameState_SaveScreen ||
        g_GameWork.gameState_594 == GameState_KcetLogo)
    {
        g_SaveScreen_SaveScreenState = MEMCARD_UNK_STATE_SAVE;
    }
    else
    {
        g_SaveScreen_SaveScreenState = MEMCARD_UNK_STATE_LOAD;
    }

    prevStatusCpy                = g_MemCard_AllMemCardsStatus;
    g_MemCard_AllMemCardsStatus  = MemCard_AllMemCardsStatusGet();
    g_MemCard_TotalElementsCount = 0;
    g_MemCard_SavegameCount      = 0;

    for (i = 0; i < CARD_DEVICE_COUNT; i += 4)
    {
        memCardStatus    = MemCard_StatusGet(g_MemCard_AllMemCardsStatus, i);
        sp3C            *= memCardStatus;
        preMemCardStatus = MemCard_StatusGet(prevStatusCpy, i);
        memSaveDataIdx   = WrapIdx(i);

        g_MemCard_ActiveSavegameEntry                              = GetActiveSavegameEntry(memSaveDataIdx >> 2);
        g_Savegame_ElementCount1[memSaveDataIdx >> 2]              = 0;
        g_Savegame_ElementCount0[memSaveDataIdx >> 2]              = 0;
        sp18[i]                                                    = false;
        g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = NO_VALUE;
        g_MemCard_ActiveSavegameEntry->deviceId_5                  = i;
        g_MemCard_ActiveSavegameEntry->fileIdx_6                   = 0;
        g_MemCard_ActiveSavegameEntry->elementIdx_7                = 0;
        g_MemCard_ActiveSavegameEntry->saveMetadata_C              = NULL;

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

        if (g_SaveScreen_SaveScreenState == MEMCARD_UNK_STATE_SAVE)
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
                    if (g_SaveScreen_SaveScreenState == MEMCARD_UNK_STATE_SAVE)
                    {
                        g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = 31600;
                        memSaveDataIdx                                             = WrapIdx(i);
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
            if (g_SaveScreen_SaveScreenState == MEMCARD_UNK_STATE_LOAD)
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
        else if (g_SaveScreen_SaveScreenState == MEMCARD_UNK_STATE_LOAD && MemCard_FilesAreNotUsedCheck(i) != false)
        {
            g_MemCard_ActiveSavegameEntry->type_4 = SavegameEntryType_CorruptedSave;

            memSaveDataIdx = WrapIdx(i);
            g_Savegame_ElementCount1[memSaveDataIdx >> 2]++;
            g_MemCard_ActiveSavegameEntry++;
        }
        else
        {
            allFileStatus[i] = MemCard_AllFilesStatusGet(i);

            for (j = 0; j < CARD_DEVICE_FILE_COUNT; j++)
            {
                fileStatus = MemCard_FileStatusGet(allFileStatus[i], j);

                if (fileStatus == FileState_Unused)
                {
                    continue;
                }

                if (fileStatus == FileState_Damaged)
                {
                    g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = 0;
                    g_MemCard_ActiveSavegameEntry->deviceId_5                  = i;
                    g_MemCard_ActiveSavegameEntry->fileIdx_6                   = j;
                    g_MemCard_ActiveSavegameEntry->elementIdx_7                = 0;
                    g_MemCard_ActiveSavegameEntry->type_4                      = SavegameEntryType_CorruptedSave;

                    memSaveDataIdx = WrapIdx(i);

                    g_Savegame_ElementCount0[memSaveDataIdx >> 2]++;
                    g_MemCard_SavegameCount--;
                    g_Savegame_ElementCount1[memSaveDataIdx >> 2]++;

                    g_MemCard_ActiveSavegameEntry++;
                }
                else
                {
                    for (k = 0; k < SAVEGAME_SLOT_COUNT_MAX; k++)
                    {
                        saveMetadata = MemCard_SaveMetadataGet(i, j, k);

                        g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = saveMetadata->totalSavegameCount_0;
                        g_MemCard_ActiveSavegameEntry->deviceId_5                  = i;
                        g_MemCard_ActiveSavegameEntry->fileIdx_6                   = j;
                        g_MemCard_ActiveSavegameEntry->elementIdx_7                = k;
                        g_MemCard_ActiveSavegameEntry->savegameCount_2             = saveMetadata->savegameCount_8;
                        g_MemCard_ActiveSavegameEntry->locationId_8                = saveMetadata->locationId_A;
                        g_MemCard_ActiveSavegameEntry->saveMetadata_C              = saveMetadata;

                        if (saveMetadata->totalSavegameCount_0 > 0)
                        {
                            g_MemCard_ActiveSavegameEntry->type_4 = SavegameEntryType_Save;

                            memSaveDataIdx = WrapIdx(i);

                            g_Savegame_ElementCount0[memSaveDataIdx >> 2]++;
                            g_Savegame_ElementCount1[memSaveDataIdx >> 2]++;
                            g_MemCard_ActiveSavegameEntry++;
                        }
                        else if (g_SaveScreen_SaveScreenState == MEMCARD_UNK_STATE_SAVE && sp18[i] == false)
                        {
                            sp18[i]                                                    = true;
                            g_MemCard_ActiveSavegameEntry->type_4                      = SavegameEntryType_NewSave;
                            g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = 31900;

                            memSaveDataIdx = WrapIdx(i);
                            g_Savegame_ElementCount0[memSaveDataIdx >> 2]++;
                            g_Savegame_ElementCount1[memSaveDataIdx >> 2]++;
                            g_MemCard_ActiveSavegameEntry++;
                        }
                    }
                }
            }

            if (g_SaveScreen_SaveScreenState == MEMCARD_UNK_STATE_SAVE && sp18[i] == false && MemCard_FreeFilesCount(i) > 0)
            {
                g_MemCard_ActiveSavegameEntry->savegameCount_2             = 0;
                g_MemCard_ActiveSavegameEntry->saveMetadata_C              = NULL;
                sp18[i]                                                    = true;
                g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = 31800;
                MemCardStatus0                                             = allFileStatus[i];
                MemCardStatus1                                             = MemCardStatus0 & 0x3;

                for (j = 0; MemCardStatus1 == FileState_Damaged || MemCardStatus1 == FileState_Used; j++)
                {
                    j++;
                    MemCardStatus1 = MemCard_FileStatusGet(MemCardStatus0, j);
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

    for (i = 0; i < CARD_DEVICE_COUNT; i += 4)
    {
        MemCardStatus2 = MemCard_StatusGet(g_MemCard_AllMemCardsStatus, i);
        if (MemCardStatus2 == FileState_Unused || MemCardStatus2 == FileState_Unk2)
        {
            D_800A97E0                    = (WrapIdx(i) >> 2) == 0;
            g_MemCard_ActiveSavegameEntry = GetActiveSavegameEntry(D_800A97E0);

            if (g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_NoMemCard)
            {
                D_800A97DC = 24;
            }
            else if (g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_UnformattedMemCard)
            {
                if (g_SaveScreen_SaveScreenState == MEMCARD_UNK_STATE_SAVE)
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
        g_MemCard_ActiveSavegameEntry = GetActiveSavegameEntry(D_800A97E0 == 0);

        g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = NO_VALUE;
        g_MemCard_ActiveSavegameEntry->deviceId_5                  = 0;
        g_MemCard_ActiveSavegameEntry->fileIdx_6                   = 0;
        g_MemCard_ActiveSavegameEntry->elementIdx_7                = 0;
        g_MemCard_ActiveSavegameEntry->type_4                      = SavegameEntryType_LoadMemCard;
        g_Savegame_ElementCount1[D_800A97E0 == 0]                  = 1;
        g_MemCard_ActiveSavegameEntry                              = GetActiveSavegameEntry(D_800A97E0);

        if ((g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_UnformattedMemCard && g_SaveScreen_SaveScreenState == MEMCARD_UNK_STATE_SAVE) ||
            g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_Save ||
            g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_NewSave ||
            g_MemCard_ActiveSavegameEntry->type_4 == SavegameEntryType_NewFile)
        {
            g_MemCard_ActiveSavegameEntry->totalSavegameCount_0 = NO_VALUE;
            g_MemCard_ActiveSavegameEntry->deviceId_5                  = 0;
            g_MemCard_ActiveSavegameEntry->fileIdx_6                   = 0;
            g_MemCard_ActiveSavegameEntry->elementIdx_7                = 0;
            g_MemCard_ActiveSavegameEntry->type_4                      = SavegameEntryType_LoadMemCard;
            g_Savegame_ElementCount1[D_800A97E0]                       = 1;
        }

        sp3C = 0;
    }

    if (D_800A97D9 == 0 && (sp10[0] || sp10[1]))
    {
        for (j = 0; j < 2; j++)
        {
            g_MemCard_ActiveSavegameEntry = GetActiveSavegameEntry(j);
            D_800BCD18[j]                 = 0;
            D_800BCD20[j]                 = 0;

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

const char unkRodata_800251F4[] = { 0x00, 0x1C, 0x97, 0x50 };
