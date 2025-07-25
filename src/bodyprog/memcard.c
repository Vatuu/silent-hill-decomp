#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/memcard.h"

#include <libapi.h>
#include <limits.h>
#include <strings.h>
#include <sys/file.h>

static inline void CardWork_ClearDirectoryFile(s32 idx)
{
    strcpy(g_CardWork.cardDirectory_40->filenames_0[idx], ""); // 0x80024B64 .rodata
    g_CardWork.cardDirectory_40->blockCounts_13B[idx] = 0;
}

static inline void s_800B55E8_Init(s_800B55E8* p, s32 field_0, s32 deviceId, s32 fileIdx, s32 saveIdx, s32 field_10, s32 lastCardResult)
{
    p->field_0           = field_0;
    p->deviceId_4        = deviceId;
    p->fileIdx_8         = fileIdx;
    p->saveIdx_C         = saveIdx;
    p->field_10          = field_10;
    p->lastCardResult_14 = lastCardResult;
}

/** @note Strange data access.
 * Many functions access by strange means to
 * variables making an extreamly confusing
 * and arbitrary process.
 *
 * For example: `func_8002E7BC` access to
 * `D_800B55E8` which Splat indicates that
 * holds 0x14/20 bytes and the initial part
 * of the code indicate confirm it, however
 * the code get weirder as it imply that
 * `D_800B55E8` is an array of structs and it
 * modify the next 0x14/20 bytes of data
 * that follow `D_800B55E8` which lands in
 * `D_800B55FC` (single 4 byte variable) and
 * `D_800B5600` (another possible struct which
 * has a size of 0x18/24 bytes).
 *
 * Another example: `func_8002E86C` access to
 * `D_800B5508` (0x800B5508) which is
 * an array struct with the size of 0xE0/224,
 * however the function access to an element of
 * the array which lands in the position 0xF8/248
 * and another that lands in a position of
 * 0x110/272 of the array struct. In the first
 * case its actually accessing to `D_800B5600`
 * and the second case is accessing to `D_800B5508.field_110`.
 *
 * @note Could be that the size of `D_800B5600`
 * is actually 0x14/20 and uses the same struct
 * of `D_800B55E8` but the value at 0x800B5614
 * is unused and Splat merge it.
 */

void Savegame_CardCleanInit() // 0x8002E630
{
    s_MemCardInfo_BasicSaveInfo* ptr;
    s32         i;

    Savegame_CardInit();

    D_800B5480 = 0;

    // Clear arrays.
    bzero(&D_800B5508, sizeof(s_800B5508));
    bzero(g_MemCard_1_BasicSaveInfo, 768);

    for (i = 0; i < CARD_DEVICE_COUNT; i++)
    {
        D_800B5508.devices_0[i].memoryCardStatus_0 = 0;

        Savegame_CardFileUsageClear(i);

        switch (i) 
        {                          
            case 0:
                ptr = g_MemCard_1_BasicSaveInfo;
                break;

            case 4:
                ptr = g_MemCard_2_BasicSaveInfo;
                break;

            default:
                ptr = D_800B4580;
                break;
        }

        D_800B5508.devices_0[i].basicSaveInfo_14 = ptr;

        Savegame_GameMemDataClear(i);
    } 
}

void Savegame_GameMemDataClear(s32 deviceId) // 0x8002E6E4
{
    D_800B5508.devices_0[deviceId].memoryCardStatus_0 = 0;
    Savegame_CardFileUsageClear(deviceId);
    bzero(D_800B5508.devices_0[deviceId].basicSaveInfo_14, sizeof(s_MemCardInfo_BasicSaveInfo) * CARD_DEVICE_FILE_COUNT);
    D_800B5508.devices_0[deviceId].field_18 = 0;
}

void Savegame_CardFileUsageClear(s32 deviceId) // 0x8002E730
{
    s32 i;

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        D_800B5508.devices_0[deviceId].isFileUsed_4[i] = 0;
    }
}

s32 Savegame_CardFilesAreAllUnused(s32 deviceId) // 0x8002E76C
{
    s32 ret;
    s32 i;

    ret = 1;

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        if (D_800B5508.devices_0[deviceId].isFileUsed_4[i] != 0)
        {
            ret = 0;
            break;
        }
    }

    return ret;
}

void func_8002E7BC() // 0x8002E7BC
{
    s_800B55E8* ptr;

    if (D_800B5480 == 1)
    {
        return;
    }

    D_800B5480 = 1;
    func_8002E8E4();
    Savegame_CardEventsInit();

    s_800B55E8_Init(&D_800B5508.field_E0[0], 0, 0, 0, 0, 0, CardResult_NotConnected);
    s_800B55E8_Init(&D_800B5508.field_E0[1], 0, 0, 0, 0, 0, CardResult_NotConnected); // `D_800B5600`
}

void func_8002E830() // 0x8002E830
{
    if (D_800B5480 != 0) 
    {
        D_800B5480 = 0;
        Savegame_CardEventsClose();
    }
}

void func_8002E85C() // 0x8002E85C
{
    D_800B5508.field_110 = 1;
}

void func_8002E86C() // 0x8002E86C
{
    D_800B5508.field_110 = 0;

    s_800B55E8_Init(&D_800B5508.field_E0[1], 0, 0, 0, 0, 0, CardResult_NotConnected);
}

s32 func_8002E898() // 0x8002E898
{
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < CARD_DEVICE_COUNT; i++)
    {
        ret |= D_800B5508.devices_0[i].memoryCardStatus_0 << (i * 3);
    }

    return ret;
}

void func_8002E8D4() // 0x8002E8D4
{
    D_800B5508.field_110 = 1;
}

void func_8002E8E4() // 0x8002E8E4
{
    D_800B5508.field_110 = 0;

    s_800B55E8_Init(&D_800B5508.field_E0[1], 0, 0, 0, 0, 0, CardResult_Success);
}

s32 func_8002E914() // 0x8002E914
{
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < CARD_DEVICE_COUNT; i++)
    {
        ret |= D_800B5508.devices_0[i].memoryCardStatus_0 << (i * 2);
    }

    return ret;
}

s32 func_8002E94C(s32 arg0, s32 deviceId, s32 fileIdx, s32 saveIdx) // 0x8002E94C
{
    if (D_800B5508.field_E0[0].field_0 != 0)
    {
        return 0;
    }

    s_800B55E8_Init(&D_800B5508.field_E0[0], arg0, deviceId, fileIdx, saveIdx, 0, CardResult_Success);
    return 1;
}

/** @brief Related to formatting logic.
 * Used in: `SAVELOAD.BIN`
 */
s32 func_8002E990() // 0x8002E990
{
    return D_800B5508.field_E0[0].lastCardResult_14;
}

s32 Savegame_CardFilesGetUsageBits(s32 deviceId) // 0x8002E9A0
{
    s32 ret;
    s32 i;

    ret = 0;

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        ret |= D_800B5508.devices_0[deviceId].isFileUsed_4[i] << (i * 2);
    }

    return ret;
}

s_SavegameMetadata* Savegame_MetadataGet(s32 deviceId, s32 fileIdx, s32 saveIdx) // 0x8002E9EC
{
    return &D_800B5508.devices_0[deviceId].basicSaveInfo_14[fileIdx].savegameMetadatas_4[saveIdx];
}

s32 Savegame_CardFileUsageCount(s32 deviceId) // 0x8002EA28
{
    s32 ret;
    s32 i;

    ret = 0;

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        if (D_800B5508.devices_0[deviceId].isFileUsed_4[i] != 0)
        {
            ret++;
        }
    }

    return ret;
}

s32 Savegame_CardFileUsageFreeCount(s32 deviceId) // 0x8002EA78
{
    return D_800B5508.devices_0[deviceId].field_18 - Savegame_CardFileUsageCount(deviceId);
}

s32 func_8002EABC(s32* outDeviceId, s32* outFileIdx, s32* outSaveIdx) // 0x8002EABC
{
    s_func_8002FE70 sp10;
    s32    i;
    s32    ret;

    ret = 0;

    *outDeviceId = 0;
    *outFileIdx  = 0;
    *outSaveIdx  = 0;

    for (i = 0; i < CARD_DEVICE_COUNT; i++)
    {
        if (D_800B5508.devices_0[i].memoryCardStatus_0 == 3)
        {
            func_8002FE70(i, &sp10);

            if (ret < sp10.field_0)
            {
                *outDeviceId = i;
                *outFileIdx  = sp10.fileIdx_4;
                *outSaveIdx  = sp10.saveIdx_8;

                ret = sp10.field_0;
            }
        }
    }

    return ret != 0;
}

void func_8002EB88() // 0x8002EB88
{
    s_800B55E8* ptr;

    if (D_800B5480 == 0)
    {
        return;
    }

    Savegame_CardUpdate();

    if (D_800B5508.field_E0[0].field_0)
    {
        if (D_800B5508.field_E0[1].field_0 == 0)
        {
            ptr = &D_800B5508.field_E0[0];
        }
        else
        {
            ptr = &D_800B5508.field_E0[1];
        }
    }
    else
    {
        if (D_800B5508.field_110 == 1 && D_800B5508.field_E0[1].field_0 == 0)
        {
            s_800B55E8_Init(&D_800B5508.field_E0[1], D_800B5508.field_110, D_800B5508.field_E0[1].deviceId_4, 0, 0, 0, D_800B5508.field_110);
        }

        ptr = &D_800B5508.field_E0[1];
    }

    switch (ptr->field_0)
    {
        case 1:
            func_8002ED7C(ptr);
            break;

        case 2:
        case 4:
            func_8002F2C4(ptr);
            break;

        case 3:
        case 5:
            func_8002F61C(ptr);
            break;

        case 6:
            func_8002ECE0(ptr);
            break;

        case 0:
        default:
            break;
    }

    if (ptr->field_0 != 0 && ptr->lastCardResult_14 != CardResult_Success)
    {
        ptr->field_0 = 0;
        if (ptr == &D_800B5508.field_E0[1])
        {
            D_800B5508.field_E0[1].deviceId_4 = (D_800B5508.field_E0[1].deviceId_4 + 1) & 0x7;
        }
    }
}

void func_8002ECE0(s_800B55E8* arg0) // 0x8002ECE0
{
    if (Savegame_CardDeviceFormat(arg0->deviceId_4) != 0)
    {
        arg0->lastCardResult_14 = CardResult_FileIoComplete;

        D_800B5508.devices_0[arg0->deviceId_4].memoryCardStatus_0 = 3;

        Savegame_CardFileUsageClear(arg0->deviceId_4);

        D_800B5508.devices_0[arg0->deviceId_4].field_18 = 15; // `CARD_DEVICE_FILE_COUNT`? Field does look related to file counts.
    }
    else
    {
        arg0->lastCardResult_14 = CardResult_FileIoError;
    }
}

void func_8002ED7C(s_800B55E8* arg0) // 0x8002ED7C
{
    char filePath[24];
    s32  cardResult;
    s32  i;

    s_MemCardInfo_BasicSaveInfo* temp_a1;
    s_MemCardBasicInfo*          ptr;

    arg0->lastCardResult_14 = CardResult_Success;

    ptr = &D_800B5508.devices_0[arg0->deviceId_4];

    switch (arg0->field_10)
    {
        case 0:
            D_800B261C = 0;

            if (Savegame_CardRequest(CardIoMode_Init, arg0->deviceId_4, NULL, NULL, 0, 0, NULL, 0) != 0)
            {
                arg0->field_10 = 1;
            }
            break;
        
        case 1:
            cardResult = Savegame_CardResult();
            switch (cardResult)
            {
                case CardResult_NotConnected:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    ptr->memoryCardStatus_0 = 1;
                    arg0->lastCardResult_14 = cardResult;
                    break;

                case CardResult_InitError:
                    arg0->field_10 = 2;
                    break;

                case CardResult_InitComplete:
                    switch(ptr->memoryCardStatus_0)
                    {
                        case 3:
                            arg0->lastCardResult_14 = CardResult_FileIoComplete;
                            break;

                        case 4:
                            arg0->lastCardResult_14 = CardResult_LoadError;
                            break;

                        case 5:
                            arg0->lastCardResult_14 = CardResult_FileIoError;
                            break;

                        default:
                            arg0->field_10 = 2;
                            break;
                    }
                    break;
            }
            break;

        case 2:
            ptr->memoryCardStatus_0 = 2;
            if (Savegame_CardRequest(CardIoMode_DirRead, arg0->deviceId_4, &D_800B2628, NULL, 0, 0, NULL, 0) != 0)
            {
                arg0->field_10 = 3;
            }
            break;

        case 3:
            cardResult = Savegame_CardResult();
            switch (cardResult)
            {
                case CardResult_NotConnected:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14 = cardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case CardResult_LoadError:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14 = cardResult;
                    ptr->memoryCardStatus_0 = 4;
                    break;

                case CardResult_5:
                case CardResult_6:
                    arg0->field_10 = 4;
                    return;
            }
            break;

        case 4:
            D_800B2618 = NO_VALUE;

            Savegame_CardFileUsageClear(arg0->deviceId_4);
            bzero(D_800B5508.devices_0[arg0->deviceId_4].basicSaveInfo_14, 0xF00);

            arg0->field_10 = 5;

        case 5:
            D_800B2618++;

            for (D_800B2620 = 0; D_800B2618 < CARD_DEVICE_FILE_COUNT; D_800B2618++)
            {
                Savegame_FilenameGenerate(filePath, D_800B2618);

                for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
                {
                    if (!strcmp(D_800B2628.filenames_0[i], filePath))
                    {
                        arg0->field_10 = 6;
                        return;
                    }
                }
            }

            if (D_800B2618 == CARD_DEVICE_FILE_COUNT)
            {
                arg0->field_10 = 9;
            }
            break;
            
        case 6:
            Savegame_FilenameGenerate(filePath, D_800B2618);

            if (Savegame_CardRequest(CardIoMode_Read, arg0->deviceId_4, NULL, filePath, 0, 0x200, &D_800B5508.devices_0[arg0->deviceId_4].basicSaveInfo_14[D_800B2618], sizeof(s_MemCardInfo_BasicSaveInfo)) != 0)
            {
                arg0->field_10 = 7;
            }
            break;

        case 7:
            cardResult = Savegame_CardResult();
            switch (cardResult)
            {
                case CardResult_NotConnected:
                    Savegame_GameMemDataClear(arg0->deviceId_4);

                    arg0->lastCardResult_14 = cardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case CardResult_FileOpenError:
                case CardResult_FileSeekError:
                case CardResult_FileIoError:
                    arg0->field_10 = 0;

                    if (D_800B261C >= 3)
                    {
                        Savegame_GameMemDataClear(arg0->deviceId_4);

                        arg0->lastCardResult_14 = CardResult_FileIoError;
                        ptr->memoryCardStatus_0 = 5;
                        break;
                    }

                    D_800B261C++;
                    arg0->field_10 = 2;
                    break;

                case CardResult_FileIoComplete:
                    arg0->field_10 = 8;
                    break;
            }
            break;

        case 8:
            temp_a1 = &D_800B5508.devices_0[arg0->deviceId_4].basicSaveInfo_14[D_800B2618];

            if (Savegame_ChecksumValidate(&temp_a1->field_FC, (s8*)temp_a1, sizeof(s_MemCardInfo_BasicSaveInfo)) != 0)
            {
                ptr->isFileUsed_4[D_800B2618] = 1;
                arg0->field_10                = 5;
                return;
            }

            if (++D_800B2620 >= 3)
            {
                arg0->field_10                = 5;
                ptr->isFileUsed_4[D_800B2618] = 3;
                return;
            }

            arg0->field_10 = 6;
            break;

        case 9:
            ptr->field_18           = func_8002F278(arg0->deviceId_4, &D_800B2628);
            arg0->lastCardResult_14 = CardResult_FileIoComplete;
            ptr->memoryCardStatus_0 = 3;
            break;
    }
}

s32 func_8002F278(s32 deviceId, s_CardDirectory* dir) // 0x8002F278
{
    s32 ret;
    s32 i;

    ret = 15;

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        ret -= dir->blockCounts_13B[i];
    }

    return ret + Savegame_CardFileUsageCount(deviceId);
}

void func_8002F2C4(s_800B55E8* arg0)
{
    char                filePath[24];
    s32                 cardResult;
    s32                 saveData0Offset;
    s8*                 saveData0Buf;
    s32                 saveData0Size;
    s_MemCardBasicInfo* saveInfo;
    s8*                 saveData1Buf;
    s32                 saveData1Size;
    s_ShSavegameFooter* saveData1Footer;

    saveInfo = &D_800B5508.devices_0[arg0->deviceId_4];

    arg0->lastCardResult_14 = CardResult_Success;

    switch (arg0->field_10)
    {
        case 0:
            if (arg0->field_0 == 2)
            {
                if (Savegame_CardFilesAreAllUnused(arg0->deviceId_4) != 1)
                {
                    D_800B2774 = func_8002FC3C(arg0->deviceId_4);
                    if (D_800B2774 == NO_VALUE)
                    {
                        arg0->lastCardResult_14 = CardResult_FileIoError;
                    }
                    else
                    {
                        arg0->field_10 = 1;
                    }
                }
                else
                {
                    arg0->lastCardResult_14 = CardResult_100;
                }
            }
            else
            {
                D_800B2774 = arg0->fileIdx_8;
                switch (saveInfo->isFileUsed_4[D_800B2774])
                {
                    case 1:
                        if (Savegame_MetadataGet(arg0->deviceId_4, D_800B2774, arg0->saveIdx_C)->field_0 != 0)
                        {
                            arg0->field_10 = 1;
                            break;
                        }

                    case 0:
                        arg0->lastCardResult_14 = CardResult_100;
                        break;

                    case 3:
                        arg0->lastCardResult_14 = CardResult_101;
                        break;
                }
            }
            break;

        case 1:
            if (arg0->field_0 == 2)
            {
                saveData0Offset = 0x300;
                saveData0Buf    = (s8*)&D_800B5508.userConfig_418;
                saveData0Size   = sizeof(s_ShSaveUserConfigContainer);
            }
            else
            {
                saveData0Offset = 0x300 + sizeof(s_ShSaveUserConfigContainer) + (arg0->saveIdx_C * sizeof(s_ShSavegameContainer));
                saveData0Buf    = (s8*)&D_800B5508.saveGame_498;
                saveData0Size   = sizeof(s_ShSavegameContainer);
            }

            Savegame_FilenameGenerate(filePath, D_800B2774);

            if (Savegame_CardRequest(CardIoMode_Read, arg0->deviceId_4, NULL, filePath, 0, saveData0Offset, saveData0Buf, saveData0Size) == 1)
            {
                arg0->field_10 = 2;
            }
            break;

        case 2:
            cardResult = Savegame_CardResult();
            switch (cardResult)
            {
                case CardResult_NotConnected:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14      = cardResult;
                    saveInfo->memoryCardStatus_0 = 1;
                    break;

                case CardResult_FileOpenError:
                case CardResult_FileSeekError:
                case CardResult_FileIoError:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14      = CardResult_FileIoError;
                    saveInfo->memoryCardStatus_0 = 0;
                    break;

                case CardResult_FileIoComplete:
                    arg0->field_10 = 3;
                    break;
            }
            break;

        case 3:

            if (arg0->field_0 == 2)
            {
                saveData1Size   = sizeof(s_ShSaveUserConfigContainer);
                saveData1Buf    = (s8*)&D_800B5508.userConfig_418;
                saveData1Footer = &D_800B5508.userConfig_418.footer_7C;
            }
            else
            {
                saveData1Buf    = (s8*)&D_800B5508.saveGame_498;
                saveData1Size   = sizeof(s_ShSavegameContainer);
                saveData1Footer = &D_800B5508.saveGame_498.footer_27C;
            }

            if (Savegame_ChecksumValidate(saveData1Footer, saveData1Buf, saveData1Size) == 0)
            {
                arg0->lastCardResult_14 = CardResult_101;
                return;
            }

            arg0->lastCardResult_14 = CardResult_FileIoComplete;

            if (arg0->field_0 == 2)
            {
                memcpy(&g_GameWorkConst->config_0, &D_800B5508.userConfig_418.config_0, sizeof(s_ShSaveUserConfig));
            }
            else
            {
                memcpy(g_SavegamePtr, &D_800B5508.saveGame_498.savegame_0, sizeof(s_ShSavegame));
            }
            break;
    }
}

void func_8002F61C(s_800B55E8* arg0)
{
    char filePath[24];
    s32  fileIdx;
    s32  cardResult;

    s_MemCardBasicInfo* ptr;

    arg0->lastCardResult_14 = CardResult_Success;

    ptr = &D_800B5508.devices_0[arg0->deviceId_4];

    switch (arg0->field_10)
    {
        case 0:
            if (arg0->field_0 == 3)
            {
                fileIdx = arg0->fileIdx_8;
                if (fileIdx != NO_VALUE)
                {
                    switch (ptr->isFileUsed_4[fileIdx])
                    {
                        case 0:
                            D_800B2778     = fileIdx;
                            arg0->field_10 = 1;
                            break;

                        case 1:
                            D_800B2778     = fileIdx;
                            arg0->field_10 = 3;
                            break;

                        case 3:
                            arg0->lastCardResult_14 = CardResult_FileIoError;
                            break;

                        default:
                            break;
                    }
                }
                else
                {
                    if (Savegame_CardFilesAreAllUnused(arg0->deviceId_4) == 1)
                    {
                        D_800B2778     = 0;
                        arg0->field_10 = 1;
                    }
                    else
                    {
                        D_800B2778 = func_8002FC3C(arg0->deviceId_4);
                        if (D_800B2778 != fileIdx)
                        {
                            arg0->field_10 = 3;
                        }
                        else
                        {
                            arg0->lastCardResult_14 = CardResult_FileIoError;
                        }
                    }
                }
            }
            else
            {
                D_800B2778 = arg0->fileIdx_8;
                switch (ptr->isFileUsed_4[D_800B2778])
                {
                    case 0:
                        arg0->field_10 = 1;
                        return;

                    case 1:
                        arg0->field_10 = 5;
                        return;

                    case 3:
                        arg0->lastCardResult_14 = CardResult_FileIoError;
                        break;

                    default:
                        break;
                }
            }
            break;

        case 1:
            // TODO: Weird extra params to `Savegame_SaveBlockInit`. Do any other callers do the same?
            Savegame_SaveBlockInit(&D_800B5508.saveBlock_118, 1, D_800B2778, 0, 0, 0x70, 0x60, 0, 0);
            func_8002FB64(&D_800B5508.saveInfo_318);
            Savegame_FilenameGenerate(filePath, D_800B2778);

            if (Savegame_CardRequest(CardIoMode_Create, arg0->deviceId_4, NULL, filePath, 1, 0, &D_800B5508.saveBlock_118, 0x300) != 0)
            {
                arg0->field_10 = 2;
            }
            break;

        case 2:
            cardResult = Savegame_CardResult();
            switch (cardResult)
            {
                case CardResult_NotConnected:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14 = cardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case CardResult_FileCreateError:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14 = cardResult;
                    ptr->memoryCardStatus_0 = 0;
                    break;

                case CardResult_FileOpenError:
                case CardResult_FileSeekError:
                case CardResult_FileIoError:
                    Savegame_GameMemDataClear(arg0->deviceId_4);

                    arg0->lastCardResult_14 = CardResult_FileIoError;
                    ptr->memoryCardStatus_0 = 0;

                    Savegame_FilenameGenerate(filePath, D_800B2778);
                    Savegame_CardFileErase(arg0->deviceId_4, filePath);
                    break;

                case CardResult_FileIoComplete:
                    ptr->isFileUsed_4[D_800B2778] = 1;
                    if (arg0->field_0 == 3)
                    {
                        arg0->field_10 = 3;
                    }
                    else
                    {
                        arg0->field_10 = 5;
                    }
                    break;

                default:
                    break;
            }
            break;

        case 3:
            Savegame_UserConfigCopyWithChecksum(&D_800B5508.userConfig_418, &g_GameWorkConst->config_0);
            Savegame_FilenameGenerate(filePath, D_800B2778);

            if (Savegame_CardRequest(CardIoMode_Write, arg0->deviceId_4, NULL, filePath, 0, 0x300, &D_800B5508.userConfig_418, 0x80) != 0)
            {
                arg0->field_10 = 4;
            }
            break;

        case 4:
            cardResult = Savegame_CardResult();
            switch (cardResult)
            {
                case CardResult_NotConnected:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14 = cardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case CardResult_FileOpenError:
                case CardResult_FileSeekError:
                case CardResult_FileIoError:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14 = CardResult_FileIoError;
                    ptr->memoryCardStatus_0 = 0;
                    break;

                case CardResult_FileIoComplete:
                    arg0->lastCardResult_14 = cardResult;
                    break;

                default:
                    break;
            }
            break;

        case 5:
            Savegame_FilenameGenerate(filePath, D_800B2778);
            Savegame_CopyWithChecksum(&D_800B5508.saveGame_498, g_SavegamePtr);

            if (Savegame_CardRequest(CardIoMode_Write, arg0->deviceId_4, NULL, filePath, 0, (arg0->saveIdx_C * 0x280) + 0x380, &D_800B5508.saveGame_498, 0x280) != 0)
            {
                arg0->field_10 = 6;
            }
            break;

        case 6:
            cardResult = Savegame_CardResult();
            switch (cardResult)
            {
                case CardResult_NotConnected:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14 = cardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case CardResult_FileOpenError:
                case CardResult_FileSeekError:
                case CardResult_FileIoError:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14 = CardResult_FileIoError;
                    ptr->memoryCardStatus_0 = 0;
                    break;

                case CardResult_FileIoComplete:
                    arg0->field_10 = 7;
                    break;

                default:
                    break;
            }
            break;

        case 7:
            func_8002FD5C(arg0->deviceId_4, D_800B2778, arg0->saveIdx_C, g_SavegamePtr);
            arg0->field_10 = 8;

        case 8:
            Savegame_FilenameGenerate(filePath, D_800B2778);

            if (Savegame_CardRequest(CardIoMode_Write, arg0->deviceId_4, NULL, filePath, 0, 512, (u8*)D_800B5508.devices_0[arg0->deviceId_4].basicSaveInfo_14 + (D_800B2778 * 0x100), 0x100) != 0)
            {
                arg0->field_10 = 9;
            }
            break;

        case 9:
            cardResult = Savegame_CardResult();
            switch (cardResult)
            {
                case CardResult_NotConnected:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14 = cardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case CardResult_FileOpenError:
                case CardResult_FileSeekError:
                case CardResult_FileIoError:
                    Savegame_GameMemDataClear(arg0->deviceId_4);
                    arg0->lastCardResult_14 = CardResult_FileIoError;
                    ptr->memoryCardStatus_0 = 0;
                    break;

                case CardResult_FileIoComplete:
                    arg0->lastCardResult_14 = cardResult;
                    break;

                default:
                    break;
            }
            break;
    }
}

void func_8002FB64(s_MemCardInfo_BasicSaveInfo* arg0) // 0x8002FB64
{
    s32 i;

    bzero(arg0, sizeof(s_MemCardInfo_BasicSaveInfo));

    for (i = 0; i < 11; i++)
    {
        arg0->savegameMetadatas_4[i].field_0 = 0;
    }

    Savegame_ChecksumUpdate(&arg0->field_FC, (s8*)arg0, sizeof(s_MemCardInfo_BasicSaveInfo));
}

void Savegame_UserConfigCopyWithChecksum(s_ShSaveUserConfigContainer* dest, s_ShSaveUserConfig* src) // 0x8002FBB4
{
    bzero(dest, sizeof(s_ShSaveUserConfigContainer));
    dest->config_0 = *src;
    Savegame_ChecksumUpdate(&dest->footer_7C, &dest->config_0, sizeof(s_ShSaveUserConfigContainer));
}

s32 func_8002FC3C(s32 deviceId) // 0x8002FC3C
{
    s32 field0;
    s32 saveIdx;
    s32 fileIdx;
    s32 largestField0;
    s32 largestField0FileIdx;

    largestField0FileIdx = NO_VALUE;
    largestField0        = NO_VALUE;

    for (fileIdx = 0; fileIdx < CARD_DEVICE_FILE_COUNT; fileIdx++)
    {
        if (D_800B5508.devices_0[deviceId].isFileUsed_4[fileIdx] != 1)
        {
            continue;
        }

        for (saveIdx = 0; saveIdx < 11; saveIdx++)
        {
            field0 = D_800B5508.devices_0[deviceId].basicSaveInfo_14[fileIdx].savegameMetadatas_4[saveIdx].field_0;
            if (largestField0 < field0)
            {
                largestField0FileIdx = fileIdx;
                largestField0        = field0;
            }
        }
    }

    return largestField0FileIdx;
}

void Savegame_CopyWithChecksum(s_ShSavegameContainer* dest, s_ShSavegame* src) // 0x8002FCCC
{
    bzero(dest, sizeof(s_ShSavegameContainer));
    memcpy(&dest->savegame_0, src, sizeof(s_ShSavegame));
    Savegame_ChecksumUpdate(&dest->footer_27C, &dest->savegame_0, sizeof(s_ShSavegameContainer));
}

void func_8002FD5C(s32 deviceId, s32 fileIdx, s32 saveIdx, s_ShSavegame* arg3) // 0x8002FD5C
{
    s_MemCardInfo_BasicSaveInfo* ptr;

    ptr = &D_800B5508.devices_0[deviceId].basicSaveInfo_14[fileIdx];

    func_8002FDB0(deviceId, fileIdx, saveIdx);
    Savegame_ChecksumUpdate(&ptr->field_FC, ptr, sizeof(s_MemCardInfo_BasicSaveInfo));
}

void func_8002FDB0(s32 deviceId, s32 fileIdx, s32 saveIdx)
{
    s32             i;
    s32             var;
    s_func_8002FE70 sp10;

    var = 0;
    for (i = 0; i < CARD_DEVICE_COUNT; i++)
    {
        func_8002FE70(i, &sp10);

        if (var < sp10.field_0)
        {
            var = sp10.field_0;
        }
    }

    D_800B5508.devices_0[deviceId].basicSaveInfo_14[fileIdx].savegameMetadatas_4[saveIdx].field_0 = var + 1;
}

void func_8002FE70(s32 deviceId, s_func_8002FE70* result)
{
    s32 field0;
    s32 saveIdx;
    s32 fileIdx;

    result->fileIdx_4 = 0;
    result->saveIdx_8 = 0;
    result->field_0   = 0;

    if (D_800B5508.devices_0[deviceId].memoryCardStatus_0 != 0x3)
    {
        return;
    }

    for (fileIdx = 0; fileIdx < CARD_DEVICE_FILE_COUNT; fileIdx++)
    {
        if (D_800B5508.devices_0[deviceId].isFileUsed_4[fileIdx] != 1)
        {
            continue;
        }

        for (saveIdx = 0; saveIdx < 11; saveIdx++)
        {
            field0 = D_800B5508.devices_0[deviceId].basicSaveInfo_14[fileIdx].savegameMetadatas_4[saveIdx].field_0;

            if (result->field_0 < field0)
            {
                result->fileIdx_4 = fileIdx;
                result->saveIdx_8 = saveIdx;
                result->field_0   = field0;
            }
        }
    }
}

void Savegame_ChecksumUpdate(s_ShSavegameFooter* saveFooter, s8* saveData, s32 saveDataLength) // 0x8002FF30
{
    u8 checksum;

    saveFooter->checksum_0[0] = saveFooter->checksum_0[1] = 0;
    saveFooter->magic_2                                   = SAVEGAME_FOOTER_MAGIC;
    checksum                                              = Savegame_ChecksumGenerate(saveData, saveDataLength);
    saveFooter->checksum_0[0] = saveFooter->checksum_0[1] = checksum;
}

s32 Savegame_ChecksumValidate(s_ShSavegameFooter* saveFooter, s8* saveData, s32 saveDataLength) // 0x8002FF74
{
    s32 isValid = 0;

    if (saveFooter->checksum_0[0] == Savegame_ChecksumGenerate(saveData, saveDataLength))
    {
        isValid = saveFooter->magic_2 == SAVEGAME_FOOTER_MAGIC;
    }

    return isValid;
}

u8 Savegame_ChecksumGenerate(s8* saveData, s32 saveDataLength) // 0x8002FFD0
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

void Savegame_FilenameGenerate(char* dest, s32 saveIdx) // 0x80030000
{
    char buf[3];

    strcpy(dest, "BA");
    strcat(dest, "SLUS-00707");
    strcat(dest, "SILENT");

    buf[0] = '0' + (saveIdx / 10);
    buf[1] = '0' + (saveIdx % 10);
    buf[2] = 0;

    strcat(dest, buf);
}

void Savegame_SaveBlockInit(s_PsxSaveBlock* saveBlock, s8 blockCount, s32 saveIdx, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) // 0x800300B4
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

    strcpy(saveBlock->titleNameShiftJis_4, "ＳＩＬＥＮＴ　ＨＩＬＬ");
    strcat(saveBlock->titleNameShiftJis_4, "　　ＦＩＬＥ");
    strcat(saveBlock->titleNameShiftJis_4, saveIdxStr);

    bzero(saveBlock->field_44, 0x1C);

    OpenTIM(D_800A8D98);
    ReadTIM(&iconTexture);

    memcpy(saveBlock->iconPalette_60, iconTexture.caddr, iconTexture.crect->w * iconTexture.crect->h * 2);
    memcpy(saveBlock->textureData_80, iconTexture.paddr, iconTexture.prect->w * iconTexture.prect->h * 2);
}

s32 Savegame_CardDeviceTest(s32 deviceId) // 0x80030288
{
    // Unused function? Appears to write 0xFF to first 128 bytes of card and check if event is triggered.
    u8 cardBuf[128];

    memset(cardBuf, 0xFF, 128);

    Savegame_CardHwEventsReset();
    _new_card();
    _card_write(((deviceId & (1 << 2)) << 2) | (deviceId & 0x3), 0, cardBuf);

    g_CardWork.devicesPending_0 |= 1 << g_CardWork.deviceId_3C;

    return Savegame_CardHwEventsTest() != 0;
}

s32 Savegame_CardDeviceFormat(s32 deviceId) // 0x8003030C
{
    #define BUF_SIZE 16

    char buf[BUF_SIZE];

    Savegame_DevicePathGenerate(deviceId, buf);

    return format(buf);
}

s32 Savegame_CardFileErase(s32 deviceId, char* fileName) // 0x80030334
{
    #define BUF_SIZE 32

    char buf[BUF_SIZE];

    Savegame_DevicePathGenerate(deviceId, buf);

    strcat(buf, fileName);

    return erase(buf);
}

s32 Savegame_CardFileRename(s32 deviceId, char* prevName, char* newName) // 0x80030370
{
    #define BUF_SIZE 32

    char prevBuf[BUF_SIZE];
    char newBuf[BUF_SIZE];

    Savegame_DevicePathGenerate(deviceId, prevBuf);
    Savegame_DevicePathGenerate(deviceId, newBuf);

    strcat(prevBuf, prevName);
    strcat(newBuf, newName);

    return rename(prevBuf, newBuf);
}

void Savegame_CardInit() // 0x800303E4
{
    InitCARD(0);
    StartCARD();
    g_CardWork.devicesPending_0 = UINT_MAX; // All bits set.
}

void Savegame_CardEventsInit() // 0x80030414
{
    Savegame_CardStateInit();
    Savegame_CardSwEventsInit();
    Savegame_CardHwEventsInit();
}

void Savegame_CardStateInit() // 0x80030444
{
    g_CardWork.state_4       = CardState_Idle;
    g_CardWork.stateStep_8   = 0;
    g_CardWork.stateResult_C = 0;
}

void Savegame_CardSwEventsInit() // 0x8003045C
{
    EnterCriticalSection();
    g_CardWork.eventSwSpIOE_10    = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    g_CardWork.eventSwSpERROR_14  = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    g_CardWork.eventSwSpTIMOUT_18 = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    g_CardWork.eventSwSpNEW_1C    = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    ExitCriticalSection();

    EnableEvent(g_CardWork.eventSwSpIOE_10);
    EnableEvent(g_CardWork.eventSwSpERROR_14);
    EnableEvent(g_CardWork.eventSwSpTIMOUT_18);
    EnableEvent(g_CardWork.eventSwSpNEW_1C);

    Savegame_CardSwEventsReset();
}

void Savegame_CardHwEventsInit() // 0x80030530
{
    EnterCriticalSection();
    g_CardWork.eventHwSpIOE_20     = OpenEvent(HwCARD, EvSpIOE, EvMdINTR, Savegame_CardHwEventSpIOE);
    g_CardWork.eventHwSpERROR_24   = OpenEvent(HwCARD, EvSpERROR, EvMdINTR, Savegame_CardHwEventSpERROR);
    g_CardWork.eventHwSpTIMOUT_28  = OpenEvent(HwCARD, EvSpTIMOUT, EvMdINTR, Savegame_CardHwEventSpTIMOUT);
    g_CardWork.eventHwSpNEW_2C     = OpenEvent(HwCARD, EvSpNEW, EvMdINTR, Savegame_CardHwEventSpNEW);
    g_CardWork.eventHwSpUNKNOWN_30 = OpenEvent(HwCARD, EvSpUNKNOWN, EvMdINTR, Savegame_CardHwEventSpUNKNOWN);
    ExitCriticalSection();

    EnableEvent(g_CardWork.eventHwSpIOE_20);
    EnableEvent(g_CardWork.eventHwSpERROR_24);
    EnableEvent(g_CardWork.eventHwSpTIMOUT_28);
    EnableEvent(g_CardWork.eventHwSpNEW_2C);
    EnableEvent(g_CardWork.eventHwSpUNKNOWN_30);

    Savegame_CardHwEventsReset();
}

void Savegame_CardEventsClose() // 0x80030640
{
    Savegame_CardSwEventsClose();
    Savegame_CardHwEventsClose();
}

void Savegame_CardSwEventsClose() // 0x80030668
{
    EnterCriticalSection();
    CloseEvent(g_CardWork.eventSwSpIOE_10);
    CloseEvent(g_CardWork.eventSwSpERROR_14);
    CloseEvent(g_CardWork.eventSwSpTIMOUT_18);
    CloseEvent(g_CardWork.eventSwSpNEW_1C);
    ExitCriticalSection();
}

void Savegame_CardHwEventsClose() // 0x800306C8
{
    EnterCriticalSection();
    CloseEvent(g_CardWork.eventHwSpIOE_20);
    CloseEvent(g_CardWork.eventHwSpERROR_24);
    CloseEvent(g_CardWork.eventHwSpTIMOUT_28);
    CloseEvent(g_CardWork.eventHwSpNEW_2C);
    CloseEvent(g_CardWork.eventHwSpUNKNOWN_30);
    ExitCriticalSection();
}

s32 Savegame_CardSwEventsTest() // 0x80030734
{
    if (TestEvent(g_CardWork.eventSwSpERROR_14) == 1)
    {
        return EvSpERROR;
    }

    if (TestEvent(g_CardWork.eventSwSpTIMOUT_18) == 1)
    {
        return EvSpTIMOUT;
    }

    if (TestEvent(g_CardWork.eventSwSpNEW_1C) == 1)
    {
        return EvSpNEW;
    }

    if (TestEvent(g_CardWork.eventSwSpIOE_10) == 1)
    {
        return EvSpIOE;
    }

    return 0;
}

void Savegame_CardSwEventsReset() // 0x800307BC
{
    TestEvent(g_CardWork.eventSwSpERROR_14);
    TestEvent(g_CardWork.eventSwSpTIMOUT_18);
    TestEvent(g_CardWork.eventSwSpNEW_1C);
    TestEvent(g_CardWork.eventSwSpIOE_10);
}

s32 Savegame_CardHwEventsTest() // 0x80030810
{
    return g_CardWork.lastEventHw_34;
}

void Savegame_CardHwEventsReset() // 0x80030820
{
    TestEvent(g_CardWork.eventHwSpERROR_24);
    TestEvent(g_CardWork.eventHwSpTIMOUT_28);
    TestEvent(g_CardWork.eventHwSpNEW_2C);
    TestEvent(g_CardWork.eventHwSpIOE_20);
    TestEvent(g_CardWork.eventHwSpUNKNOWN_30);

    g_CardWork.lastEventHw_34 = 0;
}

void Savegame_CardHwEventSpIOE() // 0x80030884
{
    g_CardWork.lastEventHw_34 = EvSpIOE;
}

void Savegame_CardHwEventSpERROR() // 0x80030894
{
    g_CardWork.lastEventHw_34 = EvSpERROR;
}

void Savegame_CardHwEventSpNEW() // 0x800308A4
{
    g_CardWork.lastEventHw_34 = EvSpNEW;
}

void Savegame_CardHwEventSpTIMOUT() // 0x800308B4
{
    g_CardWork.lastEventHw_34 = EvSpTIMOUT;
}

void Savegame_CardHwEventSpUNKNOWN() // 0x800308C4
{
    g_CardWork.lastEventHw_34 = EvSpUNKNOWN;
}

s32 Savegame_CardResult() // 0x800308D4
{
    return g_CardWork.stateResult_C;
}

s32 Savegame_CardRequest(e_CardIoMode mode, s32 deviceId, s_CardDirectory* outDir, char* filename, s32 createBlockCount, s32 fileOffset, void* outBuf, s32 bufSize) // 0x800308E4
{
    if (!Savegame_CardIsIdle())
    {
        return 0;
    }

    g_CardWork.cardIoMode_38 = mode;

    switch (mode)
    {
        case CardIoMode_Init:
        case CardIoMode_DirRead:
            g_CardWork.state_4     = CardState_Init;
            g_CardWork.stateStep_8 = 0;
            break;

        case CardIoMode_Read:
        case CardIoMode_Write:
            g_CardWork.state_4     = CardState_FileOpen;
            g_CardWork.stateStep_8 = 0;
            break;

        case CardIoMode_Create:
            g_CardWork.state_4     = CardState_FileCreate;
            g_CardWork.stateStep_8 = 0;
            break;

        default:
            break;
    }

    g_CardWork.deviceId_3C      = deviceId;
    g_CardWork.cardDirectory_40 = outDir;

    Savegame_DevicePathGenerate(deviceId, g_CardWork.filePath_44);
    strcat(g_CardWork.filePath_44, filename);

    g_CardWork.createBlockCount_60 = createBlockCount;
    g_CardWork.seekOffset_64       = fileOffset;
    g_CardWork.dataBuffer_68       = outBuf;
    g_CardWork.dataSize_6C         = bufSize;
    g_CardWork.field_70            = 0;
    return 1;
}

s32 Savegame_CardIsIdle() // 0x800309FC
{
    return g_CardWork.state_4 == CardState_Idle;
}

void Savegame_CardUpdate() // 0x80030A0C
{
    switch (g_CardWork.state_4)
    {
        case CardState_Idle:
            // HACK: Probably some optimized out code here.
            g_CardWork.stateResult_C += 0;
            break;

        case CardState_Init:
            g_CardWork.stateResult_C = Savegame_CardState_Init();
            break;

        case CardState_Check:
            g_CardWork.stateResult_C = Savegame_CardState_Check();
            break;

        case CardState_Load:
            g_CardWork.stateResult_C = Savegame_CardState_Load();
            break;

        case CardState_DirRead:
            g_CardWork.stateResult_C = Savegame_CardState_DirRead();
            break;

        case CardState_FileCreate:
            g_CardWork.stateResult_C = Savegame_CardState_FileCreate();
            break;

        case CardState_FileOpen:
            g_CardWork.stateResult_C = Savegame_CardState_FileOpen();
            break;

        case CardState_FileReadWrite:
            g_CardWork.stateResult_C = Savegame_CardState_FileReadWrite();
            break;

        default:
            break;
    }
}

s32 Savegame_CardState_Init() // 0x80030AD8
{
    s32 channel;
    s32 result;

    result  = CardResult_Success;
    channel = ((g_CardWork.deviceId_3C & (1 << 2)) << 2) + (g_CardWork.deviceId_3C & ((1 << 0) | (1 << 1)));

    switch (g_CardWork.stateStep_8)
    {
        case 0:
            g_CardWork.retryCount_78 = 0;
            g_CardWork.field_7C      = 0;
            g_CardWork.stateStep_8   = 1;

        case 1:
            Savegame_CardSwEventsReset();

            if (_card_info(channel) == 1)
            {
                g_CardWork.stateStep_8++;
            }
            else
            {
                g_CardWork.retryCount_78++;
            }
            break;

        case 2:
            switch (Savegame_CardSwEventsTest())
            {
                case EvSpIOE: // Connected.
                    if (g_CardWork.cardIoMode_38 == CardIoMode_Init)
                    {
                        result                 = CardResult_InitComplete;
                        g_CardWork.state_4     = CardState_Idle;
                        g_CardWork.stateStep_8 = 0;
                    }
                    else if (!((g_CardWork.devicesPending_0 >> g_CardWork.deviceId_3C) & (1 << 0)))
                    {
                        g_CardWork.state_4     = CardState_DirRead;
                        g_CardWork.stateStep_8 = 0;
                    }
                    else
                    {
                        g_CardWork.state_4     = CardState_Check;
                        g_CardWork.stateStep_8 = 0;
                    }
                    break;

                case EvSpNEW: // "No writing after connection"
                    g_CardWork.field_70 = 1;
                    if (g_CardWork.cardIoMode_38 == CardIoMode_Init)
                    {
                        result                 = CardResult_InitError;
                        g_CardWork.state_4     = CardState_Idle;
                        g_CardWork.stateStep_8 = 0;
                    }
                    else
                    {
                        g_CardWork.state_4     = CardState_Check;
                        g_CardWork.stateStep_8 = 0;
                    }
                    break;

                case EvSpTIMOUT: // Not connected.
                    result                 = CardResult_NotConnected;
                    g_CardWork.state_4     = CardState_Idle;
                    g_CardWork.stateStep_8 = 0;
                    break;

                case EvSpERROR: // Error.
                    g_CardWork.stateStep_8 = 1;
                    break;
            }
            break;
    }

    return result;
}

s32 Savegame_CardState_Check() // 0x80030C88
{
    s32 channel;
    s32 result;

    result  = CardResult_Success;
    channel = ((g_CardWork.deviceId_3C & (1 << 2)) << 2) + (g_CardWork.deviceId_3C & ((1 << 0) | (1 << 1)));

    switch (g_CardWork.stateStep_8)
    {
        case 0:
            g_CardWork.retryCount_78 = 0;
            g_CardWork.field_7C      = 0;
            g_CardWork.stateStep_8   = 1;

        case 1:
            Savegame_CardHwEventsReset();

            if (_card_clear(channel) == 1)
            {
                g_CardWork.stateStep_8++;
            }
            break;

        case 2:
            switch (Savegame_CardHwEventsTest())
            {
                case EvSpIOE: // Completed.
                    g_CardWork.state_4     = CardState_Load;
                    g_CardWork.stateStep_8 = 0;
                    break;

                case EvSpTIMOUT: // Card not connected.
                    result                 = CardResult_NotConnected;
                    g_CardWork.state_4     = CardState_Idle;
                    g_CardWork.stateStep_8 = 0;
                    break;

                case EvSpNEW:   // New card detected.
                case EvSpERROR: // Error.
                    g_CardWork.stateStep_8 = 1;
                    break;
            }
            break;
    }

    return result;
}

s32 Savegame_CardState_Load() // 0x80030DC8
{
    s32 channel;
    s32 result;

    result  = CardResult_Success;
    channel = ((g_CardWork.deviceId_3C & (1 << 2)) << 2) + (g_CardWork.deviceId_3C & ((1 << 0) | (1 << 1)));

    switch (g_CardWork.stateStep_8)
    {
        case 0:
            g_CardWork.retryCount_78 = 0;
            g_CardWork.field_7C      = 0;
            g_CardWork.stateStep_8   = 1;

        case 1:
            Savegame_CardSwEventsReset();

            if (_card_load(channel) == 1)
            {
                g_CardWork.stateStep_8++;
                if (!(g_CardWork.deviceId_3C & (1 << 2)))
                {
                    g_CardWork.devicesPending_0 |= 0xF;
                }
                else
                {
                    g_CardWork.devicesPending_0 |= 0xF0;
                }
            }
            break;

        case 2:
            switch (Savegame_CardSwEventsTest())
            {
                case EvSpIOE: // Read completed.
                    g_CardWork.state_4           = CardState_DirRead;
                    g_CardWork.stateStep_8       = 0;
                    g_CardWork.devicesPending_0 &= ~(1 << g_CardWork.deviceId_3C);
                    break;

                case EvSpNEW: // Uninitialized card.
                    g_CardWork.devicesPending_0 |= 1 << g_CardWork.deviceId_3C;
                    if (g_CardWork.retryCount_78 < 3)
                    {
                        g_CardWork.retryCount_78++;
                        g_CardWork.stateStep_8 = 1;
                    }
                    else
                    {
                        result                 = CardResult_LoadError;
                        g_CardWork.state_4     = CardState_Idle;
                        g_CardWork.stateStep_8 = 0;
                    }
                    break;

                case EvSpTIMOUT: // Not connected.
                    result                 = CardResult_NotConnected;
                    g_CardWork.state_4     = CardState_Idle;
                    g_CardWork.stateStep_8 = 0;
                    break;

                case EvSpERROR: // Error.
                    g_CardWork.stateStep_8 = 1;
                    break;
            }
            break;
    }

    return result;
}

s32 Savegame_CardState_DirRead() // 0x80030F7C
{
    struct DIRENTRY  fileInfo;
    struct DIRENTRY* curFile;
    char             filePath[16];
    s32              result;
    s32              i;

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        CardWork_ClearDirectoryFile(i);
    }

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        if (i == 0)
        {
            Savegame_DevicePathGenerate(g_CardWork.deviceId_3C, filePath);
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

        strcpy(g_CardWork.cardDirectory_40->filenames_0[i], fileInfo.name);
        g_CardWork.cardDirectory_40->blockCounts_13B[i] = (fileInfo.size + (8192 - 1)) / 8192;
    }

    result = (g_CardWork.field_70 == 1) ? CardResult_5 : CardResult_6;

    g_CardWork.state_4     = CardState_Idle;
    g_CardWork.stateStep_8 = 0;

    return result;
}

s32 Savegame_CardState_FileCreate() // 0x800310B4
{
    s32 result;

    result = CardResult_Success;

    switch (g_CardWork.stateStep_8)
    {
        case 0:
            g_CardWork.retryCount_78 = 0;
            g_CardWork.field_7C      = 0;
            g_CardWork.stateStep_8   = 1;

        case 1:
            g_CardWork.fileHandle_74 = open(g_CardWork.filePath_44, (g_CardWork.createBlockCount_60 << 16) | O_CREAT);
            if (g_CardWork.fileHandle_74 == NO_VALUE)
            {
                if (g_CardWork.retryCount_78++ >= 15)
                {
                    result                 = CardResult_FileCreateError;
                    g_CardWork.state_4     = CardState_Idle;
                    g_CardWork.stateStep_8 = 0;
                    break;
                }
            }
            else
            {
                close(g_CardWork.fileHandle_74);
                g_CardWork.state_4     = CardState_FileOpen;
                g_CardWork.stateStep_8 = 0;
            }
            break;
    }

    return result;
}

s32 Savegame_CardState_FileOpen() // 0x80031184
{
    s32 mode;
    s32 result;

    result = CardResult_Success;

    switch (g_CardWork.stateStep_8)
    {
        case 0:
            g_CardWork.retryCount_78 = 0;
            g_CardWork.field_7C      = 0;
            g_CardWork.stateStep_8   = 1;

        case 1:
            switch (g_CardWork.cardIoMode_38)
            {
                case CardIoMode_Read:
                    mode = O_RDONLY;
                    break;

                case CardIoMode_Write:
                case CardIoMode_Create:
                    mode = O_WRONLY;
                    break;

                default:
                    mode = 0;
                    break;
            }

            g_CardWork.fileHandle_74 = open(g_CardWork.filePath_44, mode | O_NOWAIT);
            if (g_CardWork.fileHandle_74 == NO_VALUE)
            {
                if (g_CardWork.retryCount_78++ >= 15)
                {
                    result                 = CardResult_FileOpenError;
                    g_CardWork.state_4     = CardState_Idle;
                    g_CardWork.stateStep_8 = 0;
                    break;
                }
            }
            else
            {
                g_CardWork.state_4     = CardState_FileReadWrite;
                g_CardWork.stateStep_8 = 0;
            }
            break;
    }

    return result;
}

s32 Savegame_CardState_FileReadWrite() // 0x80031260
{
    s32 result;
    s32 ioResult;

    result = CardResult_Success;

    switch (g_CardWork.stateStep_8)
    {
        case 0:
            g_CardWork.retryCount_78 = 0;
            g_CardWork.field_7C      = 0;
            g_CardWork.stateStep_8   = 1;

        case 1:
            if (lseek(g_CardWork.fileHandle_74, g_CardWork.seekOffset_64, SEEK_SET) == NO_VALUE)
            {
                if (g_CardWork.retryCount_78++ >= 15)
                {
                    result                 = CardResult_FileSeekError;
                    g_CardWork.state_4     = CardState_Idle;
                    g_CardWork.stateStep_8 = 0;
                }
            }
            else
            {
                g_CardWork.retryCount_78 = 0;
                g_CardWork.stateStep_8++;
            }
            break;

        case 2:
            Savegame_CardSwEventsReset();

            switch (g_CardWork.cardIoMode_38)
            {
                case CardIoMode_Read:
                    ioResult = read(g_CardWork.fileHandle_74, g_CardWork.dataBuffer_68, g_CardWork.dataSize_6C);
                    break;

                case CardIoMode_Write:
                case CardIoMode_Create:
                    ioResult = write(g_CardWork.fileHandle_74, g_CardWork.dataBuffer_68, g_CardWork.dataSize_6C);
                    break;

                default:
                    ioResult = NO_VALUE;
                    break;
            }

            if (ioResult == NO_VALUE)
            {
                if (g_CardWork.retryCount_78++ >= 15)
                {
                    result                 = CardResult_FileIoError;
                    g_CardWork.state_4     = CardState_Idle;
                    g_CardWork.stateStep_8 = 0;
                    close(g_CardWork.fileHandle_74);
                }
            }
            else
            {
                g_CardWork.stateStep_8++;
            }
            break;

        case 3:
            switch (Savegame_CardSwEventsTest())
            {
                case EvSpIOE: // Completed.
                    result                 = CardResult_FileIoComplete;
                    g_CardWork.state_4     = CardState_Idle;
                    g_CardWork.stateStep_8 = 0;
                    close(g_CardWork.fileHandle_74);
                    break;

                case EvSpTIMOUT: // Card not connected.
                    result                 = CardResult_NotConnected;
                    g_CardWork.state_4     = CardState_Idle;
                    g_CardWork.stateStep_8 = 0;
                    close(g_CardWork.fileHandle_74);
                    break;

                case EvSpNEW: // New card detected.
                    result                 = CardResult_FileIoError;
                    g_CardWork.state_4     = CardState_Idle;
                    g_CardWork.stateStep_8 = 0;
                    close(g_CardWork.fileHandle_74);

                case EvSpERROR: // Error.
                    g_CardWork.stateStep_8 = 1;
                    break;
            }
    }

    return result;
}

void Savegame_DevicePathGenerate(s32 deviceId, char* result) // 0x800314A4
{
    strcpy(result, "buXX:");

    // Convert sequential device ID to PSX channel number.
    result[2] = '0' + ((deviceId & (1 << 2)) >> 2);
    result[3] = '0' + (deviceId & ((1 << 0) | (1 << 1)));
}
