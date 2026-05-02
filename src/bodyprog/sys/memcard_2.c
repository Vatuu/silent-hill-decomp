#include "game.h"

#include <memory.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"
#include "screens/saveload.h"

#ifndef PAD_HACK_IGNORE
    s16 __pad_bss_800BCD2A;
    s16 __pad_bss_800BCD32;
    s8  __pad_bss_800BCD39;
#endif

// ========================================
// GLOBAL VARIABLES
// ========================================

s16                  g_MemCard_SavegameCount;
s_SaveScreenElement* g_MemCard_ActiveMemCardSlotSaves;
u8                   g_Savegame_ElementCount0[MEMCARD_SLOT_COUNT_MAX];
u32                  g_MemCard_AllMemCardsStatus;
s8                   g_SaveScreen_SaveScreenState;
s16                  g_MemCard_TotalElementsCount;
u8                   g_Savegame_ElementCount1[MEMCARD_SLOT_COUNT_MAX];
u8                   g_Savegame_SelectedElementIdx;
s8                   g_SelectedFileIdx;
s8                   g_SelectedDeviceId;

u8 g_SlotElementSelectedIdx[MEMCARD_SLOT_COUNT_MAX] = { 0, 0 };
s8 g_SelectedSaveSlotIdx                            = 0;
u8 D_800A97D7                                       = 0;
s8 D_800A97D8                                       = 0xFF;
s8 D_800A97D9                                       = 0; // @unused Dead code. Only used for a check which ask if this is 0.

// ========================================
// INLINE FUNCTIONS
// ========================================

static inline s32 WrapIdx(s32 idx)
{
    return (idx < 0) ? (idx + 3) : idx;
}

// ========================================
// MEMORY CARD - CARD CHECKS
// ========================================

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

bool func_80033548(void) // 0x80033548
{
    u32                         sp10[MEMCARD_SLOT_COUNT_MAX];   // Boolean. Player can interact with a memory slot?
    s32                         sp18[MEMCARD_DEVICE_COUNT_MAX]; // Boolean. Used to generate `Create New File` and `New Save`.
    u32                         prevStatusCpy;
    s32                         memCardStatus3; /** @brief Strange data.
                                       * This variable contains `e_MemCardState`. This variable is first defined with the value `1`
                                       * then get multiplied by the status value of the memory card state (`e_MemCardState`), additionally
                                       * if the memory card is not loaded then the value is set to 0.
                                       *
                                       * The strange side of this variable comes at the bottom of this function. At the bottom of this
                                       * function there is a switch which not only check for the states from 1 to 5 (skipping 2) but also
                                       * checks for states impossible to get. Considering the unnecesary multiplication it is possible
                                       * that at some point the variable could have been assigned a number different to `1` likely going from
                                       * 3 to 5 as all the unreachable cases are multiples of the states, as noted in the comment on the
                                       * switch statement.
                                       */
    s32                         prevMemCardStatus;
    s32                         fileStatus;
    u32                         memCardStatus1;
    s32                         memCardStatus2;
    u32                         memCardStatus0;
    s32                         slotIdx;
    s32                         i;
    s32                         j;
    s32                         k;
    s32                         memCardStatus;
    s_MemCard_SaveMetadata*     saveMetadata;
    static s32                  biggestTotalSaveCountInSlot[MEMCARD_SLOT_COUNT_MAX];
    static s32                  lastSavegameInSlotIdx[MEMCARD_SLOT_COUNT_MAX];
    static u32                  D_800A97DC = 0; /** @brief Timer for check.
                                                 * @bug This variable is constantly updated. It can happen
                                                 * that it will reach to the point where the conditional where
                                                 * it is used can be triggered. In case of not having a memory card
                                                 * connected nothing will happen, however, if it is connected and
                                                 * there are save games it will push the selected save game down
                                                 * to the lastest element in the selected slot.
                                                 */
    static s8                   D_800A97E0 = NO_VALUE;
    static u32                  allFileStatus[MEMCARD_DEVICE_COUNT_MAX] = { };

    memCardStatus3 = 1;

    memset(&sp10, 0, sizeof(sp10));
    MemCard_SysEnable();
    MemCard_InitStatus();

    if (g_GameWork.gameState == GameState_SaveScreen ||
        g_GameWork.gameState == GameState_KcetLogo)
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
        memCardStatus     = MemCard_StatusGet(g_MemCard_AllMemCardsStatus, i);
        memCardStatus3   *= memCardStatus;
        prevMemCardStatus = MemCard_StatusGet(prevStatusCpy, i);
        slotIdx           = WrapIdx(i);

        g_MemCard_ActiveMemCardSlotSaves                       = MemCard_ActiveMemCardSlotGet(slotIdx >> 2);
        g_Savegame_ElementCount1[slotIdx >> 2]                 = 0;
        g_Savegame_ElementCount0[slotIdx >> 2]                 = 0;
        sp18[i]                                                = false;
        g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount_0 = NO_VALUE;
        g_MemCard_ActiveMemCardSlotSaves->deviceId_5           = i;
        g_MemCard_ActiveMemCardSlotSaves->fileIdx_6            = 0;
        g_MemCard_ActiveMemCardSlotSaves->elementIdx_7         = 0;
        g_MemCard_ActiveMemCardSlotSaves->saveMetadata_C       = NULL;

        if (prevMemCardStatus == MemCardState_Available)
        {
            if (memCardStatus != MemCardState_Available)
            {
                sp10[slotIdx >> 2] = true;
            }
        }
        else if (memCardStatus == MemCardState_Available)
        {
            sp10[slotIdx >> 2] = true;
        }

        if (g_SaveScreen_SaveScreenState == SaveScreenState_Save)
        {
            if (prevMemCardStatus == MemCardState_Format && memCardStatus != prevMemCardStatus)
            {
                sp10[WrapIdx(i) >> 2] = true;
            }

            if (prevMemCardStatus != MemCardState_Format && memCardStatus == MemCardState_Format)
            {
                sp10[WrapIdx(i) >> 2] = true;
            }
        }

        if (memCardStatus != MemCardState_Available)
        {
            switch (memCardStatus)
            {
                case MemCardResult_Success:
                    g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_NoMemCard;

#if VERSION_EQUAL_OR_NEWER(JAP1) // @note Bugfix?
                    if (g_SelectedSaveSlotIdx == (WrapIdx(i) >> 2))
                    {
                        g_SelectedSaveSlotIdx = g_SelectedSaveSlotIdx == 0;
                    }
#endif
                    break;

                case MemCardResult_LoadError:
                    if (g_SaveScreen_SaveScreenState == SaveScreenState_Save)
                    {
                        g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount_0 = 31600;
                        slotIdx                                                 = WrapIdx(i);
                        g_Savegame_ElementCount0[slotIdx >> 2]++;
                    }

                    g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_UnformattedMemCard;
                    break;

                case MemCardResult_NewDevice:
                    g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_CorruptedMemCard;
                    break;

                case MemCardResult_NotConnected:
                case MemCardResult_InitError:
                    g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_LoadMemCard;
                    break;
            }

            g_Savegame_ElementCount1[WrapIdx(i) >> 2]++;
            g_MemCard_ActiveMemCardSlotSaves++;
        }
        else if (MemCard_UsedFileCount(i) == 0)
        {
            if (g_SaveScreen_SaveScreenState == SaveScreenState_Load)
            {
                g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_NoDataInMemCard;
            }
            else if (MemCard_FreeFilesCount(i) == 0)
            {
                g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_OutOfBlocks;
            }
            else
            {
                g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount_0 = 31700;
                g_MemCard_ActiveMemCardSlotSaves->type_4               = SavegameEntryType_NewFile;

                slotIdx = WrapIdx(i);
                g_Savegame_ElementCount0[slotIdx >> 2]++;
            }

            g_Savegame_ElementCount1[WrapIdx(i) >> 2]++;
            g_MemCard_ActiveMemCardSlotSaves++;
        }
        else if (g_SaveScreen_SaveScreenState == SaveScreenState_Load && MemCard_FilesAreNotUsedCheck(i) != false)
        {
            g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_CorruptedSave;

            slotIdx = WrapIdx(i);
            g_Savegame_ElementCount1[slotIdx >> 2]++;
            g_MemCard_ActiveMemCardSlotSaves++;
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
                    g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount_0 = 0;
                    g_MemCard_ActiveMemCardSlotSaves->deviceId_5           = i;
                    g_MemCard_ActiveMemCardSlotSaves->fileIdx_6            = j;
                    g_MemCard_ActiveMemCardSlotSaves->elementIdx_7         = 0;
                    g_MemCard_ActiveMemCardSlotSaves->type_4               = SavegameEntryType_CorruptedSave;

                    slotIdx = WrapIdx(i);

                    g_Savegame_ElementCount0[slotIdx >> 2]++;
                    g_MemCard_SavegameCount--;
                    g_Savegame_ElementCount1[slotIdx >> 2]++;

                    g_MemCard_ActiveMemCardSlotSaves++;
                }
                else
                {
                    for (k = 0; k < MEMCARD_SAVES_COUNT_MAX; k++)
                    {
                        saveMetadata = MemCard_SaveMetadataGet(i, j, k);

                        g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount_0 = saveMetadata->totalSavegameCount_0;
                        g_MemCard_ActiveMemCardSlotSaves->deviceId_5           = i;
                        g_MemCard_ActiveMemCardSlotSaves->fileIdx_6            = j;
                        g_MemCard_ActiveMemCardSlotSaves->elementIdx_7         = k;
                        g_MemCard_ActiveMemCardSlotSaves->savegameCount_2      = saveMetadata->savegameCount_8;
                        g_MemCard_ActiveMemCardSlotSaves->locationId_8         = saveMetadata->locationId_A;
                        g_MemCard_ActiveMemCardSlotSaves->saveMetadata_C       = saveMetadata;

                        if (saveMetadata->totalSavegameCount_0 > 0)
                        {
                            g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_Save;

                            slotIdx = WrapIdx(i);

                            g_Savegame_ElementCount0[slotIdx >> 2]++;
                            g_Savegame_ElementCount1[slotIdx >> 2]++;
                            g_MemCard_ActiveMemCardSlotSaves++;
                        }
                        else if (g_SaveScreen_SaveScreenState == SaveScreenState_Save && sp18[i] == false)
                        {
                            sp18[i]                                                = true;
                            g_MemCard_ActiveMemCardSlotSaves->type_4               = SavegameEntryType_NewSave;
                            g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount_0 = 31900;

                            slotIdx = WrapIdx(i);
                            g_Savegame_ElementCount0[slotIdx >> 2]++;
                            g_Savegame_ElementCount1[slotIdx >> 2]++;
                            g_MemCard_ActiveMemCardSlotSaves++;
                        }
                    }
                }
            }

            if (g_SaveScreen_SaveScreenState == SaveScreenState_Save && sp18[i] == false && MemCard_FreeFilesCount(i) > 0)
            {
                g_MemCard_ActiveMemCardSlotSaves->savegameCount_2      = 0;
                g_MemCard_ActiveMemCardSlotSaves->saveMetadata_C       = NULL;
                sp18[i]                                                = true;
                g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount_0 = 31800;
                memCardStatus0                                         = allFileStatus[i];
                memCardStatus1                                         = memCardStatus0 & 0x3;

                for (j = 0; memCardStatus1 == FileState_Damaged || memCardStatus1 == FileState_Used; j++)
                {
                    j++;
                    memCardStatus1 = MemCard_FileStatusGet(memCardStatus0, j);
                    j--;
                }

                g_MemCard_ActiveMemCardSlotSaves->deviceId_5   = i;
                g_MemCard_ActiveMemCardSlotSaves->fileIdx_6    = j;
                g_MemCard_ActiveMemCardSlotSaves->elementIdx_7 = 0;
                g_MemCard_ActiveMemCardSlotSaves->type_4       = SavegameEntryType_NewFile;

                slotIdx = WrapIdx(i);

                g_Savegame_ElementCount0[slotIdx >> 2]++;

                fileStatus = MemCard_FileStatusGet(allFileStatus[i], j); // @hack Fixes stack order.

                g_Savegame_ElementCount1[slotIdx >> 2]++;
                g_MemCard_ActiveMemCardSlotSaves++;
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
            D_800A97E0                       = (WrapIdx(i) >> 2) == 0;
            g_MemCard_ActiveMemCardSlotSaves = MemCard_ActiveMemCardSlotGet(D_800A97E0);

            if (g_MemCard_ActiveMemCardSlotSaves->type_4 == SavegameEntryType_NoMemCard)
            {
                D_800A97DC = 24;
            }
            else if (g_MemCard_ActiveMemCardSlotSaves->type_4 == SavegameEntryType_UnformattedMemCard)
            {
                if (g_SaveScreen_SaveScreenState == SaveScreenState_Save)
                {
                    D_800A97DC = 22;
                }
                else
                {
                    D_800A97DC = g_MemCard_ActiveMemCardSlotSaves->type_4;
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
        g_MemCard_ActiveMemCardSlotSaves = MemCard_ActiveMemCardSlotGet(D_800A97E0 == 0);

        g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount_0 = NO_VALUE;
        g_MemCard_ActiveMemCardSlotSaves->deviceId_5           = 0;
        g_MemCard_ActiveMemCardSlotSaves->fileIdx_6            = 0;
        g_MemCard_ActiveMemCardSlotSaves->elementIdx_7         = 0;
        g_MemCard_ActiveMemCardSlotSaves->type_4               = SavegameEntryType_LoadMemCard;
        g_Savegame_ElementCount1[D_800A97E0 == 0]              = 1;
        g_MemCard_ActiveMemCardSlotSaves                       = MemCard_ActiveMemCardSlotGet(D_800A97E0);

        if ((g_MemCard_ActiveMemCardSlotSaves->type_4 == SavegameEntryType_UnformattedMemCard && g_SaveScreen_SaveScreenState == SaveScreenState_Save) ||
            g_MemCard_ActiveMemCardSlotSaves->type_4 == SavegameEntryType_Save ||
            g_MemCard_ActiveMemCardSlotSaves->type_4 == SavegameEntryType_NewSave ||
            g_MemCard_ActiveMemCardSlotSaves->type_4 == SavegameEntryType_NewFile)
        {
            g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount_0 = NO_VALUE;
            g_MemCard_ActiveMemCardSlotSaves->deviceId_5           = 0;
            g_MemCard_ActiveMemCardSlotSaves->fileIdx_6            = 0;
            g_MemCard_ActiveMemCardSlotSaves->elementIdx_7         = 0;
            g_MemCard_ActiveMemCardSlotSaves->type_4               = SavegameEntryType_LoadMemCard;
            g_Savegame_ElementCount1[D_800A97E0]                   = 1;
        }

        memCardStatus3 = MemCardState_Null;
    }

    if (D_800A97D9 == 0 && (sp10[0] || sp10[1]))
    {
        for (j = 0; j < MEMCARD_SLOT_COUNT_MAX; j++)
        {
            g_MemCard_ActiveMemCardSlotSaves = MemCard_ActiveMemCardSlotGet(j);
            biggestTotalSaveCountInSlot[j]   = 0;
            lastSavegameInSlotIdx[j]         = 0;

            for (i = 0; i < g_Savegame_ElementCount1[j]; i++)
            {
                if (biggestTotalSaveCountInSlot[j] < g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount_0)
                {
                    biggestTotalSaveCountInSlot[j] = g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount_0;
                    lastSavegameInSlotIdx[j]       = i;
                }

                g_MemCard_ActiveMemCardSlotSaves++;
            }

            if (sp10[j])
            {
                g_SlotElementSelectedIdx[j] = lastSavegameInSlotIdx[j];
            }
        }

        if (biggestTotalSaveCountInSlot[1] > biggestTotalSaveCountInSlot[0])
        {
            g_SelectedSaveSlotIdx = 1;
        }
        else
        {
            g_SelectedSaveSlotIdx = 0;
        }

        g_GameWork.gameStateSteps[1] = 0;
        g_GameWork.gameStateSteps[2] = 0;
    }
    
    switch (memCardStatus3)
    {
        case MemCardState_Unavailable:
        case MemCardState_Available:
        case MemCardState_Format:
        case MemCardState_Broken:
        
        case 9:  // MemCardState_Available * 3
        case 12: // MemCardState_Format    * 3 | MemCardState_Available * 4
        case 15: // MemCardState_Broken    * 3 | MemCardState_Available * 5
        case 16: // MemCardState_Format    * 4
        case 20: // MemCardState_Broken    * 4 | MemCardState_Format    * 5
        case 25: // MemCardState_Broken    * 5
            return true;

        default:
            return false;
    }
}
