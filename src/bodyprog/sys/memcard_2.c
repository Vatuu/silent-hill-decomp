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

/** @brief Checks if any file is corrupted, unused, or used.
 *
 * @param deviceId Memory card dDevice ID.
 * @return `true` if a file is damaged or used, `false` otherwise.
 */
static bool MemCard_FilesDamagedCheck(s32 deviceId) // 0x800334D8
{
    s32  i;
    bool res;
    s32  fileStatuses;
    s32  fileStatus;

    res = false;
    fileStatuses = MemCard_FileStatusesGet(deviceId);

    for (i = 0; i < MEMCARD_FILE_COUNT_MAX; i++)
    {
        fileStatus = MemCard_FileStatusGet(fileStatuses, i);
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
    u32                         unavailableMemCardSlot[MEMCARD_SLOT_COUNT_MAX]; // Boolean.
    s32                         isWriteNewSaveAvailable[MEMCARD_DEVICE_COUNT_MAX]; // Boolean. Used to generate `Create New File` and `New Save`.
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
    static s32                  totalElementCountInSlot[MEMCARD_SLOT_COUNT_MAX];
    static u32                  D_800A97DC = 0; /** @brief Timer for check.
                                                 * @bug This variable is constantly updated. It can happen
                                                 * that it will reach to the point where the conditional where
                                                 * it is used can be triggered. In case of not having a memory card
                                                 * connected nothing will happen, however, if it is connected and
                                                 * there are save games it will push the selected save game down
                                                 * to the lastest element in the selected slot.
                                                 */
    static s8                   unavailableMemCardSlotIdx = NO_VALUE;
    static u32                  fileStatuses[MEMCARD_DEVICE_COUNT_MAX] = { };

    memCardStatus3 = 1;

    memset(&unavailableMemCardSlot, 0, sizeof(unavailableMemCardSlot));
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

    // Update metadata of memory card elements.
    for (i = 0; i < MEMCARD_DEVICE_COUNT_MAX; i += 4)
    {
        memCardStatus     = MemCard_StatusGet(g_MemCard_AllMemCardsStatus, i);
        memCardStatus3   *= memCardStatus;
        prevMemCardStatus = MemCard_StatusGet(prevStatusCpy, i);
        slotIdx           = WrapIdx(i);

        g_MemCard_ActiveMemCardSlotSaves                     = MemCard_ActiveMemCardSlotGet(slotIdx >> 2);
        g_Savegame_ElementCount1[slotIdx >> 2]               = 0;
        g_Savegame_ElementCount0[slotIdx >> 2]               = 0;
        isWriteNewSaveAvailable[i]                           = false;
        g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount = NO_VALUE;
        g_MemCard_ActiveMemCardSlotSaves->deviceId_5         = i;
        g_MemCard_ActiveMemCardSlotSaves->fileIdx_6          = 0;
        g_MemCard_ActiveMemCardSlotSaves->elementIdx_7       = 0;
        g_MemCard_ActiveMemCardSlotSaves->saveMetadata_C     = NULL;
        
        /** Checks if any memory card have become unavailable or was previously mark as unavailable. */
        if (prevMemCardStatus == MemCardState_Available)
        {
            if (memCardStatus != MemCardState_Available)
            {
                unavailableMemCardSlot[slotIdx >> 2] = true;
            }
        }
        else if (memCardStatus == MemCardState_Available)
        {
            unavailableMemCardSlot[slotIdx >> 2] = true;
        }

        if (g_SaveScreen_SaveScreenState == SaveScreenState_Save)
        {
            if (prevMemCardStatus == MemCardState_Format && memCardStatus != prevMemCardStatus)
            {
                unavailableMemCardSlot[WrapIdx(i) >> 2] = true;
            }

            if (prevMemCardStatus != MemCardState_Format && memCardStatus == MemCardState_Format)
            {
                unavailableMemCardSlot[WrapIdx(i) >> 2] = true;
            }
        }
        
        // Performs multiple checks to initialize slot elements.
        //
        // 1. If the memory card is unavailable: 
        //    Sets the first element to reflect the current memory card state.
        //
        // 2. If the memory card is available but contains no files:
        //    - Displays "no save available" if the screen is in loading mode.
        //    - Displays "out of blocks" if the card is detected as empty.
        //    - Displays "create new file" if the screen is in save mode.
        //
        // 3. If the screen is in load mode and a damaged file is detected:
        //    Assigns the damaged file message to the slot.
        //
        // 4. Otherwise:
        //    Reads and updates all slot elements from memory.
        if (memCardStatus != MemCardState_Available)
        {
            switch (memCardStatus)
            {
                case MemCardState_Unavailable:
                    g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_NoMemCard;

#if VERSION_EQUAL_OR_NEWER(JAP1) // @bug Fail safe.
                                 // If the game have as selected the slot where a memory card is
                                 // not available (disconected) it will automatically switch to the one available.
                    if (g_SelectedSaveSlotIdx == (WrapIdx(i) >> 2))
                    {
                        g_SelectedSaveSlotIdx = g_SelectedSaveSlotIdx == 0;
                    }
#endif
                    break;

                case MemCardState_Format:
                    if (g_SaveScreen_SaveScreenState == SaveScreenState_Save)
                    {
                        g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount = 31600;
                        slotIdx                                              = WrapIdx(i);
                        g_Savegame_ElementCount0[slotIdx >> 2]++;
                    }

                    g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_UnformattedMemCard;
                    break;

                case MemCardState_Broken:
                    g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_CorruptedMemCard;
                    break;

                case MemCardState_Null:
                case MemCardState_Loading:
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
                g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount = 31700;
                g_MemCard_ActiveMemCardSlotSaves->type_4             = SavegameEntryType_NewFile;

                slotIdx = WrapIdx(i);
                g_Savegame_ElementCount0[slotIdx >> 2]++;
            }

            g_Savegame_ElementCount1[WrapIdx(i) >> 2]++;
            g_MemCard_ActiveMemCardSlotSaves++;
        }
        else if (g_SaveScreen_SaveScreenState == SaveScreenState_Load && MemCard_FilesDamagedCheck(i))
        {
            g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_CorruptedSave;

            slotIdx = WrapIdx(i);
            g_Savegame_ElementCount1[slotIdx >> 2]++;
            g_MemCard_ActiveMemCardSlotSaves++;
        }
        else
        {
            fileStatuses[i] = MemCard_FileStatusesGet(i);

            for (j = 0; j < MEMCARD_FILE_COUNT_MAX; j++)
            {
                fileStatus = MemCard_FileStatusGet(fileStatuses[i], j);

                if (fileStatus == FileState_Unused)
                {
                    continue;
                }

                if (fileStatus == FileState_Damaged)
                {
                    g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount = 0;
                    g_MemCard_ActiveMemCardSlotSaves->deviceId_5         = i;
                    g_MemCard_ActiveMemCardSlotSaves->fileIdx_6          = j;
                    g_MemCard_ActiveMemCardSlotSaves->elementIdx_7       = 0;
                    g_MemCard_ActiveMemCardSlotSaves->type_4             = SavegameEntryType_CorruptedSave;

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

                        g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount = saveMetadata->totalSavegameCount;
                        g_MemCard_ActiveMemCardSlotSaves->deviceId_5         = i;
                        g_MemCard_ActiveMemCardSlotSaves->fileIdx_6          = j;
                        g_MemCard_ActiveMemCardSlotSaves->elementIdx_7       = k;
                        g_MemCard_ActiveMemCardSlotSaves->savegameCount_2    = saveMetadata->savegameCount;
                        g_MemCard_ActiveMemCardSlotSaves->locationId_8       = saveMetadata->locationId;
                        g_MemCard_ActiveMemCardSlotSaves->saveMetadata_C     = saveMetadata;

                        if (saveMetadata->totalSavegameCount > 0)
                        {
                            g_MemCard_ActiveMemCardSlotSaves->type_4 = SavegameEntryType_Save;

                            slotIdx = WrapIdx(i);

                            g_Savegame_ElementCount0[slotIdx >> 2]++;
                            g_Savegame_ElementCount1[slotIdx >> 2]++;
                            g_MemCard_ActiveMemCardSlotSaves++;
                        }
                        else if (g_SaveScreen_SaveScreenState == SaveScreenState_Save && isWriteNewSaveAvailable[i] == false)
                        {
                            isWriteNewSaveAvailable[i]                           = true;
                            g_MemCard_ActiveMemCardSlotSaves->type_4             = SavegameEntryType_NewSave;
                            g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount = 31900;

                            slotIdx = WrapIdx(i);
                            g_Savegame_ElementCount0[slotIdx >> 2]++;
                            g_Savegame_ElementCount1[slotIdx >> 2]++;
                            g_MemCard_ActiveMemCardSlotSaves++;
                        }
                    }
                }
            }

            if (g_SaveScreen_SaveScreenState == SaveScreenState_Save && isWriteNewSaveAvailable[i] == false && MemCard_FreeFilesCount(i) > 0)
            {
                g_MemCard_ActiveMemCardSlotSaves->savegameCount_2    = 0;
                g_MemCard_ActiveMemCardSlotSaves->saveMetadata_C     = NULL;
                isWriteNewSaveAvailable[i]                           = true;
                g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount = 31800;
                memCardStatus0                                       = fileStatuses[i];
                memCardStatus1                                       = memCardStatus0 & 0x3;

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

                fileStatus = MemCard_FileStatusGet(fileStatuses[i], j); // @hack Fixes stack order.

                g_Savegame_ElementCount1[slotIdx >> 2]++;
                g_MemCard_ActiveMemCardSlotSaves++;
            }
        }

        g_MemCard_TotalElementsCount += g_Savegame_ElementCount0[WrapIdx(i) >> 2];
    }

    g_MemCard_SavegameCount += g_MemCard_TotalElementsCount;

    // Checks if any of the memory cards is disconected, unformatted, or loading.
    for (i = 0; i < MEMCARD_DEVICE_COUNT_MAX; i += 4)
    {
        memCardStatus2 = MemCard_StatusGet(g_MemCard_AllMemCardsStatus, i);
        if (memCardStatus2 == MemCardState_Null || memCardStatus2 == MemCardState_Loading)
        {
            unavailableMemCardSlotIdx          = (WrapIdx(i) >> 2) == 0;
            g_MemCard_ActiveMemCardSlotSaves = MemCard_ActiveMemCardSlotGet(unavailableMemCardSlotIdx);

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
        unavailableMemCardSlot[unavailableMemCardSlotIdx == 0] = true;
        unavailableMemCardSlotIdx                              = NO_VALUE;
    }

    // Set loading memory card status (visually).
    // @note Could this be the reason why whenever one memory card is connected, both are marked as "loaded"?
    if (unavailableMemCardSlotIdx >= 0)
    {
        g_MemCard_ActiveMemCardSlotSaves = MemCard_ActiveMemCardSlotGet(unavailableMemCardSlotIdx == 0);

        g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount   = NO_VALUE;
        g_MemCard_ActiveMemCardSlotSaves->deviceId_5           = 0;
        g_MemCard_ActiveMemCardSlotSaves->fileIdx_6            = 0;
        g_MemCard_ActiveMemCardSlotSaves->elementIdx_7         = 0;
        g_MemCard_ActiveMemCardSlotSaves->type_4               = SavegameEntryType_LoadMemCard;
        g_Savegame_ElementCount1[unavailableMemCardSlotIdx == 0] = 1;
        g_MemCard_ActiveMemCardSlotSaves                       = MemCard_ActiveMemCardSlotGet(unavailableMemCardSlotIdx);

        if ((g_MemCard_ActiveMemCardSlotSaves->type_4 == SavegameEntryType_UnformattedMemCard && g_SaveScreen_SaveScreenState == SaveScreenState_Save) ||
            g_MemCard_ActiveMemCardSlotSaves->type_4 == SavegameEntryType_Save ||
            g_MemCard_ActiveMemCardSlotSaves->type_4 == SavegameEntryType_NewSave ||
            g_MemCard_ActiveMemCardSlotSaves->type_4 == SavegameEntryType_NewFile)
        {
            g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount = NO_VALUE;
            g_MemCard_ActiveMemCardSlotSaves->deviceId_5         = 0;
            g_MemCard_ActiveMemCardSlotSaves->fileIdx_6          = 0;
            g_MemCard_ActiveMemCardSlotSaves->elementIdx_7       = 0;
            g_MemCard_ActiveMemCardSlotSaves->type_4             = SavegameEntryType_LoadMemCard;
            g_Savegame_ElementCount1[unavailableMemCardSlotIdx]    = 1;
        }

        memCardStatus3 = MemCardState_Null;
    }
    
    // Update user navigation information to switch automatically between slots if a memory card becomes unavailable.
    if (D_800A97D9 == 0 && (unavailableMemCardSlot[0] || unavailableMemCardSlot[1]))
    {
        for (j = 0; j < MEMCARD_SLOT_COUNT_MAX; j++)
        {
            g_MemCard_ActiveMemCardSlotSaves = MemCard_ActiveMemCardSlotGet(j);
            biggestTotalSaveCountInSlot[j]   = 0;
            totalElementCountInSlot[j]       = 0;

            for (i = 0; i < g_Savegame_ElementCount1[j]; i++)
            {
                if (biggestTotalSaveCountInSlot[j] < g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount)
                {
                    biggestTotalSaveCountInSlot[j] = g_MemCard_ActiveMemCardSlotSaves->totalSavegameCount;
                    totalElementCountInSlot[j]    = i;
                }

                g_MemCard_ActiveMemCardSlotSaves++;
            }

            if (unavailableMemCardSlot[j])
            {
                g_SlotElementSelectedIdx[j] = totalElementCountInSlot[j];
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
