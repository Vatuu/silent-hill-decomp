#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"

s32 func_800334D8(s32 idx) // 0x800334D8
{
    s32 i;
    s32 res;
    s32 var0;
    s32 var1;

    res  = 0;
    var0 = Savegame_CardFilesGetUsageBits(idx);

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        var1 = (var0 >> (i * 2)) & 3;
        if (var1 == 1)
        {
            return 0;
        }

        if (var1 == 3)
        {
            res = 1;
        }
    }

    return res;
}

static inline s32 WrapIdx(s32 idx)
{
    return (idx < 0) ? (idx + 3) : idx;
}

// One of it's purposes is check if the memory card is loaded.
bool func_80033548() // 0x80033548
{
    u32                 sp10[2];
    s32                 sp18[8];
    u32                 sp38;
    s32                 sp3C;
    s32                 temp_t0;
    s32                 temp_v0_4;
    u32                 temp_v0_6;
    s32                 temp_v0_8;
    u32                 temp_v1_7;
    s32                 var_a0;
    s32                 var_a1;
    s32                 i;
    s32                 j;
    s32                 k;
    s32                 var_v1;
    s_SavegameMetadata* savegameMetaPtr;
    u32                 temp_a2;

    sp3C = 1;

    memset(&sp10, 0, 8);
    func_8002E7BC();
    func_8002E85C();

    if (g_GameWork.gameState_594 == GameState_Unk10 ||
        g_GameWork.gameState_594 == GameState_KcetLogo)
    {
        g_SaveScreenPlayerState = 2;
    }
    else
    {
        g_SaveScreenPlayerState = 3;
    }

    sp38                        = D_800BCD34;
    D_800BCD34                  = func_8002E898();
    g_MemCardsTotalElementCount = 0;
    g_SavegameCount             = 0;

    for (i = 0; i < 8; i += 4)
    {
        temp_a2 = (D_800BCD34 >> (i * 3)) & 0x7;
        sp3C   *= temp_a2;
        temp_t0 = (sp38 >> (i * 3)) & 0x7;
        var_a0  = WrapIdx(i);

        g_ActiveSavegameEntry                              = GetActiveSavegameEntry(var_a0 >> 2);
        g_SlotElementCount[var_a0 >> 2]                    = 0;
        g_MemCardElementCount[var_a0 >> 2]                 = 0;
        sp18[i]                                            = 0;
        g_ActiveSavegameEntry->currentScreenSessionSaves_0 = NO_VALUE;
        g_ActiveSavegameEntry->field_5                     = i;
        g_ActiveSavegameEntry->fileIdx_6                   = 0;
        g_ActiveSavegameEntry->elementIdx_7                = 0;
        g_ActiveSavegameEntry->field_C                     = NULL;

        if (temp_t0 == 3)
        {
            if (temp_a2 != 3)
            {
                sp10[var_a0 >> 2] = 1;
            }
        }
        else if (temp_a2 == 3)
        {
            sp10[var_a0 >> 2] = 1;
        }

        if (g_SaveScreenPlayerState == 2)
        {
            if (temp_t0 == 4 && temp_a2 != temp_t0)
            {
                sp10[WrapIdx(i) >> 2] = 1;
            }

            if (temp_t0 != 4 && temp_a2 == 4)
            {
                sp10[WrapIdx(i) >> 2] = 1;
            }
        }

        if (temp_a2 != 3)
        {
            switch (temp_a2)
            {
                case 1:
                    g_ActiveSavegameEntry->type_4 = SavegameEntryType_NoMemCard;
                    break;

                case 4:
                    if (g_SaveScreenPlayerState == 2)
                    {
                        g_ActiveSavegameEntry->currentScreenSessionSaves_0 = 31600;
                        var_a0                                             = WrapIdx(i);
                        g_MemCardElementCount[var_a0 >> 2]++;
                    }

                    g_ActiveSavegameEntry->type_4 = SavegameEntryType_UnformattedMemCard;
                    break;

                case 5:
                    g_ActiveSavegameEntry->type_4 = SavegameEntryType_CorruptedMemCard;
                    break;

                case 0:
                case 2:
                    g_ActiveSavegameEntry->type_4 = SavegameEntryType_LoadMemCard;
                    break;
            }

            g_SlotElementCount[WrapIdx(i) >> 2]++;
            g_ActiveSavegameEntry++;
        }
        else if (Savegame_CardFileUsageCount(i) == 0)
        {
            if (g_SaveScreenPlayerState == 3)
            {
                g_ActiveSavegameEntry->type_4 = SavegameEntryType_NoDataInMemCard;
            }
            else if (Savegame_CardFileUsageFreeCount(i) == 0)
            {
                g_ActiveSavegameEntry->type_4 = SavegameEntryType_OutOfBlocks;
            }
            else
            {
                g_ActiveSavegameEntry->currentScreenSessionSaves_0 = 31700;
                g_ActiveSavegameEntry->type_4                      = SavegameEntryType_NewFile;

                var_a0 = WrapIdx(i);
                g_MemCardElementCount[var_a0 >> 2]++;
            }

            g_SlotElementCount[WrapIdx(i) >> 2]++;
            g_ActiveSavegameEntry++;
        }
        else if (g_SaveScreenPlayerState == 3 && func_800334D8(i) != 0)
        {
            g_ActiveSavegameEntry->type_4 = SavegameEntryType_CorruptedSave;

            var_a0 = WrapIdx(i);
            g_SlotElementCount[var_a0 >> 2]++;
            g_ActiveSavegameEntry++;
        }
        else
        {
            D_800A97E4[i] = Savegame_CardFilesGetUsageBits(i);

            for (j = 0; j < 15; j++)
            {
                temp_v0_4 = (D_800A97E4[i] >> (j * 2)) & 0x3;

                if (temp_v0_4 == 0)
                {
                    continue;
                }

                if (temp_v0_4 == 3)
                {
                    g_ActiveSavegameEntry->currentScreenSessionSaves_0 = 0;
                    g_ActiveSavegameEntry->field_5                     = i;
                    g_ActiveSavegameEntry->fileIdx_6                   = j;
                    g_ActiveSavegameEntry->elementIdx_7                = 0;
                    g_ActiveSavegameEntry->type_4                      = SavegameEntryType_CorruptedSave;

                    var_a0 = WrapIdx(i);

                    g_MemCardElementCount[var_a0 >> 2]++;
                    g_SavegameCount--;
                    g_SlotElementCount[var_a0 >> 2]++;

                    g_ActiveSavegameEntry++;
                }
                else
                {
                    for (k = 0; k < 11; k++)
                    {
                        savegameMetaPtr = Savegame_MetadataGet(i, j, k);

                        g_ActiveSavegameEntry->currentScreenSessionSaves_0 = savegameMetaPtr->field_0;
                        g_ActiveSavegameEntry->field_5                     = i;
                        g_ActiveSavegameEntry->fileIdx_6                   = j;
                        g_ActiveSavegameEntry->elementIdx_7                = k;
                        g_ActiveSavegameEntry->savegameCount_2             = savegameMetaPtr->savegameCount_8;
                        g_ActiveSavegameEntry->locationId_8                = savegameMetaPtr->locationId_A;
                        g_ActiveSavegameEntry->field_C                     = savegameMetaPtr;

                        if (savegameMetaPtr->field_0 > 0)
                        {
                            g_ActiveSavegameEntry->type_4 = SavegameEntryType_Save;

                            var_v1 = WrapIdx(i);

                            g_MemCardElementCount[var_v1 >> 2]++;
                            g_SlotElementCount[var_v1 >> 2]++;
                            g_ActiveSavegameEntry++;
                        }
                        else if (g_SaveScreenPlayerState == 2 && sp18[i] == 0)
                        {
                            sp18[i]                                            = 1;
                            g_ActiveSavegameEntry->type_4                      = SavegameEntryType_NewSave;
                            g_ActiveSavegameEntry->currentScreenSessionSaves_0 = 31900;

                            var_a1 = WrapIdx(i);
                            g_MemCardElementCount[var_a1 >> 2]++;
                            g_SlotElementCount[var_a1 >> 2]++;
                            g_ActiveSavegameEntry++;
                        }
                    }
                }
            }

            if (g_SaveScreenPlayerState == 2 && sp18[i] == 0 && Savegame_CardFileUsageFreeCount(i) > 0)
            {
                g_ActiveSavegameEntry->savegameCount_2             = 0;
                g_ActiveSavegameEntry->field_C                     = NULL;
                sp18[i]                                            = 1;
                g_ActiveSavegameEntry->currentScreenSessionSaves_0 = 31800;
                temp_v1_7                                          = D_800A97E4[i];
                temp_v0_6                                          = temp_v1_7 & 0x3;

                for (j = 0; temp_v0_6 == 3 || temp_v0_6 == 1; j++)
                {
                    j++;
                    temp_v0_6 = (temp_v1_7 >> (j * 2)) & 0x3;
                    j--;
                }

                g_ActiveSavegameEntry->field_5   = i;
                g_ActiveSavegameEntry->fileIdx_6 = j;

                g_ActiveSavegameEntry->elementIdx_7 = 0;
                g_ActiveSavegameEntry->type_4       = SavegameEntryType_NewFile;

                var_a0 = WrapIdx(i);

                g_MemCardElementCount[var_a0 >> 2]++;

                temp_v0_4 = ((D_800A97E4[i]) >> (j * 2)) & 0x3; // Not needed here but fixes stack order.

                g_SlotElementCount[var_a0 >> 2]++;
                g_ActiveSavegameEntry++;
            }
        }

        g_MemCardsTotalElementCount += g_MemCardElementCount[WrapIdx(i) >> 2];
    }

    g_SavegameCount += g_MemCardsTotalElementCount;

    for (i = 0; i < 8; i += 4)
    {
        temp_v0_8 = (D_800BCD34 >> (i * 3)) & 0x7;
        if (temp_v0_8 == 0 || temp_v0_8 == 2)
        {
            D_800A97E0            = (WrapIdx(i) >> 2) == 0;
            g_ActiveSavegameEntry = GetActiveSavegameEntry(D_800A97E0);

            if (g_ActiveSavegameEntry->type_4 == SavegameEntryType_NoMemCard)
            {
                D_800A97DC = 24;
            }
            else if (g_ActiveSavegameEntry->type_4 == SavegameEntryType_UnformattedMemCard)
            {
                if (g_SaveScreenPlayerState == 2)
                {
                    D_800A97DC = 22;
                }
                else
                {
                    D_800A97DC = g_ActiveSavegameEntry->type_4;
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
        sp10[D_800A97E0 == 0] = 1;
        D_800A97E0            = NO_VALUE;
    }

    if (D_800A97E0 >= 0)
    {
        g_ActiveSavegameEntry = GetActiveSavegameEntry(D_800A97E0 == 0);

        g_ActiveSavegameEntry->currentScreenSessionSaves_0 = NO_VALUE;
        g_ActiveSavegameEntry->field_5                     = 0;
        g_ActiveSavegameEntry->fileIdx_6                   = 0;
        g_ActiveSavegameEntry->elementIdx_7                = 0;
        g_ActiveSavegameEntry->type_4                      = SavegameEntryType_LoadMemCard;
        g_SlotElementCount[D_800A97E0 == 0]                = 1;
        g_ActiveSavegameEntry                              = GetActiveSavegameEntry(D_800A97E0);

        if ((g_ActiveSavegameEntry->type_4 == SavegameEntryType_UnformattedMemCard && g_SaveScreenPlayerState == SavegameEntryType_CorruptedMemCard) ||
            g_ActiveSavegameEntry->type_4 == SavegameEntryType_Save ||
            g_ActiveSavegameEntry->type_4 == SavegameEntryType_NewSave ||
            g_ActiveSavegameEntry->type_4 == SavegameEntryType_NewFile)
        {
            g_ActiveSavegameEntry->currentScreenSessionSaves_0 = NO_VALUE;
            g_ActiveSavegameEntry->field_5                     = 0;
            g_ActiveSavegameEntry->fileIdx_6                   = 0;
            g_ActiveSavegameEntry->elementIdx_7                = 0;
            g_ActiveSavegameEntry->type_4                      = SavegameEntryType_LoadMemCard;
            g_SlotElementCount[D_800A97E0]                     = 1;
        }

        sp3C = 0;
    }

    if (D_800A97D9 == 0 && (sp10[0] != 0 || sp10[1] != 0))
    {
        for (j = 0; j < 2; j++)
        {
            g_ActiveSavegameEntry = GetActiveSavegameEntry(j);
            D_800BCD18[j]         = 0;
            D_800BCD20[j]         = 0;

            for (i = 0; i < g_SlotElementCount[j]; i++)
            {
                if (D_800BCD18[j] < g_ActiveSavegameEntry->currentScreenSessionSaves_0)
                {
                    D_800BCD18[j] = g_ActiveSavegameEntry->currentScreenSessionSaves_0;
                    D_800BCD20[j] = i;
                }

                g_ActiveSavegameEntry++;
            }

            if (sp10[j] != 0)
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