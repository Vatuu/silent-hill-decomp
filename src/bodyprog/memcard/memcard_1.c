#include "game.h"

#include "main/fsqueue.h"
#include "bodyprog/savegame.h"
#include "bodyprog/memcard.h"

#include <psyq/libapi.h>
#include <psyq/limits.h>
#include <psyq/strings.h>
#include <psyq/sys/file.h>

s_MemCard_BasicSaveInfo g_MemCard_BasicSaveInfo1[CARD_DEVICE_FILE_COUNT];

s_MemCard_BasicSaveInfo g_MemCard_BasicSaveInfo2[CARD_DEVICE_FILE_COUNT];

s_MemCard_BasicSaveInfo g_MemCard_BasicSaveInfo3[CARD_DEVICE_FILE_COUNT];

bool g_MemCard_AvailibityStatus;

s32 pad_bss_800B5484;

s_MemCardWork g_MemCardWork;

s_800B5508 D_800B5508;

static inline void CardWork_ClearDirectoryFile(s32 idx)
{
    strcpy(g_MemCardWork.cardDirectory_40->filenames_0[idx], ""); // 0x80024B64 .rodata
    g_MemCardWork.cardDirectory_40->blockCounts_13B[idx] = 0;
}

static inline void s_MemCard_Status_Init(s_MemCard_Status* p, s32 field_0, s32 deviceId, s32 fileIdx, s32 saveIdx, s32 field_10, s32 lastMemCardResult)
{
    p->field_0              = field_0;
    p->deviceId_4           = deviceId;
    p->fileIdx_8            = fileIdx;
    p->saveIdx_C            = saveIdx;
    p->field_10             = field_10;
    p->lastMemCardResult_14 = lastMemCardResult;
}

/** @note Strange data access.
 * Many functions access by strange means to
 * variables making an extreamly confusing
 * and arbitrary process.
 *
 * For example: `MemCard_SysInit2` access to
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

void MemCard_SysInit(void) // 0x8002E630
{
    s32                      i;
    s_MemCard_BasicSaveInfo* ptr;

    MemCard_Init();

    g_MemCard_AvailibityStatus = false;

    // Clear arrays.
    bzero(&D_800B5508, sizeof(s_800B5508));
    bzero(g_MemCard_BasicSaveInfo1, sizeof(s_MemCard_BasicSaveInfo) * 3);

    for (i = 0; i < CARD_DEVICE_COUNT; i++)
    {
        D_800B5508.devices_0[i].memoryCardStatus_0 = 0;

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

        D_800B5508.devices_0[i].basicSaveInfo_14 = ptr;

        MemCard_RamClear(i);
    } 
}

void MemCard_RamClear(s32 deviceId) // 0x8002E6E4
{
    D_800B5508.devices_0[deviceId].memoryCardStatus_0 = 0;

    MemCard_FileStatusClear(deviceId);
    bzero(D_800B5508.devices_0[deviceId].basicSaveInfo_14, sizeof(s_MemCard_BasicSaveInfo) * CARD_DEVICE_FILE_COUNT);

    D_800B5508.devices_0[deviceId].memoryCardFileLimit_18 = 0;
}

void MemCard_FileStatusClear(s32 deviceId) // 0x8002E730
{
    s32 i;

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        D_800B5508.devices_0[deviceId].fileState_4[i] = FileState_Unused;
    }
}

bool Savegame_CardFilesAreAllUnused(s32 deviceId) // 0x8002E76C
{
    bool result;
    s32  i;

    result = true;
    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        if (D_800B5508.devices_0[deviceId].fileState_4[i] != FileState_Unused)
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
    func_8002E8E4();
    MemCard_EventsInit();

    s_MemCard_Status_Init(&D_800B5508.field_E0[0], 0, 0, 0, 0, 0, MemCardResult_NotConnected);
    s_MemCard_Status_Init(&D_800B5508.field_E0[1], 0, 0, 0, 0, 0, MemCardResult_NotConnected);
}

void MemCard_Disable(void) // 0x8002E830
{
    if (g_MemCard_AvailibityStatus != false)
    {
        g_MemCard_AvailibityStatus = false;
        MemCard_EventsClose();
    }
}

void func_8002E85C(void) // 0x8002E85C
{
    D_800B5508.field_110 = true;
}

void func_8002E86C(void) // 0x8002E86C
{
    D_800B5508.field_110 = false;

    s_MemCard_Status_Init(&D_800B5508.field_E0[1], 0, 0, 0, 0, 0, MemCardResult_NotConnected);
}

s32 MemCard_AllMemCardsStatusGet(void) // 0x8002E898
{
    s32 ret;
    s32 i;

    ret = 0;
    for (i = 0; i < CARD_DEVICE_COUNT; i++)
    {
        ret |= MemCard_StatusStore(D_800B5508.devices_0[i].memoryCardStatus_0, i);
    }

    return ret;
}

void func_8002E8D4(void) // 0x8002E8D4
{
    D_800B5508.field_110 = true;
}

void func_8002E8E4(void) // 0x8002E8E4
{
    D_800B5508.field_110 = false;

    s_MemCard_Status_Init(&D_800B5508.field_E0[1], 0, 0, 0, 0, 0, MemCardResult_Success);
}

s32 func_8002E914(void) // 0x8002E914
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

bool func_8002E94C(s32 arg0, s32 deviceId, s32 fileIdx, s32 saveIdx) // 0x8002E94C
{
    if (D_800B5508.field_E0[0].field_0 != false)
    {
        return false;
    }

    s_MemCard_Status_Init(&D_800B5508.field_E0[0], arg0, deviceId, fileIdx, saveIdx, 0, MemCardResult_Success);
    return true;
}

s32 func_8002E990(void) // 0x8002E990
{
    return D_800B5508.field_E0[0].lastMemCardResult_14;
}

s32 MemCard_AllFilesStatusGet(s32 deviceId) // 0x8002E9A0
{
    s32 ret;
    s32 i;

    ret = 0;

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        ret |= MemCard_FileStatusStore(D_800B5508.devices_0[deviceId].fileState_4[i], i);
    }

    return ret;
}

s_Savegame_Metadata* MemCard_SaveMetadataGet(s32 deviceId, s32 fileIdx, s32 saveIdx) // 0x8002E9EC
{
    return &D_800B5508.devices_0[deviceId].basicSaveInfo_14[fileIdx].saveMetadata_4[saveIdx];
}

s32 MemCard_UsedFileCount(s32 deviceId) // 0x8002EA28
{
    s32 ret;
    s32 i;

    ret = 0;

    for (i = 0; i < CARD_DEVICE_FILE_COUNT; i++)
    {
        if (D_800B5508.devices_0[deviceId].fileState_4[i] != FileState_Unused)
        {
            ret++;
        }
    }

    return ret;
}

s32 MemCard_FreeFilesCount(s32 deviceId) // 0x8002EA78
{
    return D_800B5508.devices_0[deviceId].memoryCardFileLimit_18 - MemCard_UsedFileCount(deviceId);
}

bool func_8002EABC(s32* outDeviceId, s32* outFileIdx, s32* outSaveIdx) // 0x8002EABC
{
    s_func_8002FE70 sp10;
    s32             i;
    s32             ret;

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

void func_8002EB88(void) // 0x8002EB88
{
    s_MemCard_Status* ptr;

    if (g_MemCard_AvailibityStatus == false)
    {
        return;
    }

    Savegame_CardUpdate();

    if (D_800B5508.field_E0[0].field_0 != false)
    {
        if (D_800B5508.field_E0[1].field_0 == false)
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
        if (D_800B5508.field_110 == true && D_800B5508.field_E0[1].field_0 == false)
        {
            s_MemCard_Status_Init(&D_800B5508.field_E0[1], D_800B5508.field_110, D_800B5508.field_E0[1].deviceId_4, 0, 0, 0, D_800B5508.field_110);
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

    if (ptr->field_0 != 0 && ptr->lastMemCardResult_14 != MemCardResult_Success)
    {
        ptr->field_0 = 0;
        if (ptr == &D_800B5508.field_E0[1])
        {
            D_800B5508.field_E0[1].deviceId_4 = (D_800B5508.field_E0[1].deviceId_4 + 1) & 0x7;
        }
    }
}

void func_8002ECE0(s_MemCard_Status* arg0) // 0x8002ECE0
{
    if (Savegame_CardDeviceFormat(arg0->deviceId_4) != 0)
    {
        arg0->lastMemCardResult_14 = MemCardResult_FileIoComplete;

        D_800B5508.devices_0[arg0->deviceId_4].memoryCardStatus_0 = 3;

        MemCard_FileStatusClear(arg0->deviceId_4);

        D_800B5508.devices_0[arg0->deviceId_4].memoryCardFileLimit_18 = CARD_DEVICE_FILE_COUNT; // `CARD_DEVICE_FILE_COUNT`? Field does look related to file counts.
    }
    else
    {
        arg0->lastMemCardResult_14 = MemCardResult_FileIoError;
    }
}

void func_8002ED7C(s_MemCard_Status* arg0) // 0x8002ED7C
{
    char                         filePath[24];
    s32                          MemCardResult;
    s32                          i;
    s_MemCard_BasicSaveInfo* temp_a1;
    s_MemCard_Info*          ptr;
    static s32                   D_800B2618;
    static s32                   D_800B261C;
    static s32                   D_800B2620;
    static s32                   D_800B2624;
    static s_CardDirectory       D_800B2628;

    arg0->lastMemCardResult_14 = MemCardResult_Success;

    ptr = &D_800B5508.devices_0[arg0->deviceId_4];

    switch (arg0->field_10)
    {
        case 0:
            D_800B261C = 0;

            if (Savegame_CardRequest(MemCardIoMode_Init, arg0->deviceId_4, NULL, NULL, 0, 0, NULL, 0))
            {
                arg0->field_10 = 1;
            }
            break;
        
        case 1:
            MemCardResult = MemCard_StateResult();
            switch (MemCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(arg0->deviceId_4);
                    ptr->memoryCardStatus_0 = 1;
                    arg0->lastMemCardResult_14 = MemCardResult;
                    break;

                case MemCardResult_InitError:
                    arg0->field_10 = 2;
                    break;

                case MemCardResult_InitComplete:
                    switch(ptr->memoryCardStatus_0)
                    {
                        case 3:
                            arg0->lastMemCardResult_14 = MemCardResult_FileIoComplete;
                            break;

                        case 4:
                            arg0->lastMemCardResult_14 = MemCardResult_LoadError;
                            break;

                        case 5:
                            arg0->lastMemCardResult_14 = MemCardResult_FileIoError;
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
            if (Savegame_CardRequest(MemCardIoMode_DirRead, arg0->deviceId_4, &D_800B2628, NULL, 0, 0, NULL, 0))
            {
                arg0->field_10 = 3;
            }
            break;

        case 3:
            MemCardResult = MemCard_StateResult();
            switch (MemCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14 = MemCardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case MemCardResult_LoadError:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14 = MemCardResult;
                    ptr->memoryCardStatus_0 = 4;
                    break;

                case MemCardResult_NewDevice:
                case MemCardResult_NoNewDevice:
                    arg0->field_10 = 4;
                    return;
            }
            break;

        case 4:
            D_800B2618 = NO_VALUE;

            MemCard_FileStatusClear(arg0->deviceId_4);
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

            if (Savegame_CardRequest(MemCardIoMode_Read, arg0->deviceId_4, NULL, filePath, 0, 0x200, &D_800B5508.devices_0[arg0->deviceId_4].basicSaveInfo_14[D_800B2618], sizeof(s_MemCard_BasicSaveInfo)))
            {
                arg0->field_10 = 7;
            }
            break;

        case 7:
            MemCardResult = MemCard_StateResult();
            switch (MemCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(arg0->deviceId_4);

                    arg0->lastMemCardResult_14 = MemCardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    arg0->field_10 = 0;

                    if (D_800B261C >= 3)
                    {
                        MemCard_RamClear(arg0->deviceId_4);

                        arg0->lastMemCardResult_14 = MemCardResult_FileIoError;
                        ptr->memoryCardStatus_0 = 5;
                        break;
                    }

                    D_800B261C++;
                    arg0->field_10 = 2;
                    break;

                case MemCardResult_FileIoComplete:
                    arg0->field_10 = 8;
                    break;
            }
            break;

        case 8:
            temp_a1 = &D_800B5508.devices_0[arg0->deviceId_4].basicSaveInfo_14[D_800B2618];

            if (Savegame_ChecksumValidate(&temp_a1->field_FC, (s8*)temp_a1, sizeof(s_MemCard_BasicSaveInfo)) != 0)
            {
                ptr->fileState_4[D_800B2618] = FileState_Used;
                arg0->field_10                = 5;
                return;
            }

            if (++D_800B2620 >= 3)
            {
                arg0->field_10                = 5;
                ptr->fileState_4[D_800B2618] = FileState_Damaged;
                return;
            }

            arg0->field_10 = 6;
            break;

        case 9:
            ptr->memoryCardFileLimit_18           = func_8002F278(arg0->deviceId_4, &D_800B2628);
            arg0->lastMemCardResult_14 = MemCardResult_FileIoComplete;
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

    return ret + MemCard_UsedFileCount(deviceId);
}

void func_8002F2C4(s_MemCard_Status* arg0)
{
    char                filePath[24];
    s32                 MemCardResult;
    s32                 saveData0Offset;
    s8*                 saveData0Buf;
    s32                 saveData0Size;
    s_MemCard_Info* saveInfo;
    s8*                 saveData1Buf;
    s32                 saveData1Size;
    s_Savegame_Footer*   saveData1Footer;
    static s32          D_800B2774;

    saveInfo = &D_800B5508.devices_0[arg0->deviceId_4];

    arg0->lastMemCardResult_14 = MemCardResult_Success;

    switch (arg0->field_10)
    {
        case 0:
            if (arg0->field_0 == 2)
            {
                if (Savegame_CardFilesAreAllUnused(arg0->deviceId_4) != true)
                {
                    D_800B2774 = func_8002FC3C(arg0->deviceId_4);
                    if (D_800B2774 == NO_VALUE)
                    {
                        arg0->lastMemCardResult_14 = MemCardResult_FileIoError;
                    }
                    else
                    {
                        arg0->field_10 = 1;
                    }
                }
                else
                {
                    arg0->lastMemCardResult_14 = MemCardResult_Full;
                }
            }
            else
            {
                D_800B2774 = arg0->fileIdx_8;
                switch (saveInfo->fileState_4[D_800B2774])
                {
                    case FileState_Used:
                        if (MemCard_SaveMetadataGet(arg0->deviceId_4, D_800B2774, arg0->saveIdx_C)->field_0 != 0)
                        {
                            arg0->field_10 = 1;
                            break;
                        }

                    case FileState_Unused:
                        arg0->lastMemCardResult_14 = MemCardResult_Full;
                        break;

                    case FileState_Damaged:
                        arg0->lastMemCardResult_14 = MemCardResult_DamagedData;
                        break;
                }
            }
            break;

        case 1:
            if (arg0->field_0 == 2)
            {
                saveData0Offset = 0x300;
                saveData0Buf    = (s8*)&D_800B5508.userConfig_418;
                saveData0Size   = sizeof(s_SaveUserConfigContainer);
            }
            else
            {
                saveData0Offset = 0x300 + sizeof(s_SaveUserConfigContainer) + (arg0->saveIdx_C * sizeof(s_SavegameContainer));
                saveData0Buf    = (s8*)&D_800B5508.saveGame_498;
                saveData0Size   = sizeof(s_SavegameContainer);
            }

            Savegame_FilenameGenerate(filePath, D_800B2774);

            if (Savegame_CardRequest(MemCardIoMode_Read, arg0->deviceId_4, NULL, filePath, 0, saveData0Offset, saveData0Buf, saveData0Size) == true)
            {
                arg0->field_10 = 2;
            }
            break;

        case 2:
            MemCardResult = MemCard_StateResult();
            switch (MemCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14      = MemCardResult;
                    saveInfo->memoryCardStatus_0 = 1;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14      = MemCardResult_FileIoError;
                    saveInfo->memoryCardStatus_0 = 0;
                    break;

                case MemCardResult_FileIoComplete:
                    arg0->field_10 = 3;
                    break;
            }
            break;

        case 3:

            if (arg0->field_0 == 2)
            {
                saveData1Size   = sizeof(s_SaveUserConfigContainer);
                saveData1Buf    = (s8*)&D_800B5508.userConfig_418;
                saveData1Footer = &D_800B5508.userConfig_418.footer_7C;
            }
            else
            {
                saveData1Buf    = (s8*)&D_800B5508.saveGame_498;
                saveData1Size   = sizeof(s_SavegameContainer);
                saveData1Footer = &D_800B5508.saveGame_498.footer_27C;
            }

            if (Savegame_ChecksumValidate(saveData1Footer, saveData1Buf, saveData1Size) == 0)
            {
                arg0->lastMemCardResult_14 = MemCardResult_DamagedData;
                return;
            }

            arg0->lastMemCardResult_14 = MemCardResult_FileIoComplete;

            if (arg0->field_0 == 2)
            {
                memcpy(&g_GameWorkConst->config_0, &D_800B5508.userConfig_418.config_0, sizeof(s_SaveUserConfig));
            }
            else
            {
                memcpy(g_SavegamePtr, &D_800B5508.saveGame_498.savegame_0, sizeof(s_Savegame));
            }
            break;
    }
}

void func_8002F61C(s_MemCard_Status* arg0)
{
    char                filePath[24];
    s32                 fileIdx;
    s32                 MemCardResult;
    s_MemCard_Info* ptr;
    static s32          D_800B2778;
    static s32          D_800B277C;

    arg0->lastMemCardResult_14 = MemCardResult_Success;

    ptr = &D_800B5508.devices_0[arg0->deviceId_4];

    switch (arg0->field_10)
    {
        case 0:
            if (arg0->field_0 == 3)
            {
                fileIdx = arg0->fileIdx_8;
                if (fileIdx != NO_VALUE)
                {
                    switch (ptr->fileState_4[fileIdx])
                    {
                        case FileState_Unused:
                            D_800B2778     = fileIdx;
                            arg0->field_10 = 1;
                            break;

                        case FileState_Used:
                            D_800B2778     = fileIdx;
                            arg0->field_10 = 3;
                            break;

                        case FileState_Damaged:
                            arg0->lastMemCardResult_14 = MemCardResult_FileIoError;
                            break;

                        default:
                            break;
                    }
                }
                else
                {
                    if (Savegame_CardFilesAreAllUnused(arg0->deviceId_4) == true)
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
                            arg0->lastMemCardResult_14 = MemCardResult_FileIoError;
                        }
                    }
                }
            }
            else
            {
                D_800B2778 = arg0->fileIdx_8;
                switch (ptr->fileState_4[D_800B2778])
                {
                    case FileState_Unused:
                        arg0->field_10 = 1;
                        return;

                    case FileState_Used:
                        arg0->field_10 = 5;
                        return;

                    case FileState_Damaged:
                        arg0->lastMemCardResult_14 = MemCardResult_FileIoError;
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

            if (Savegame_CardRequest(MemCardIoMode_Create, arg0->deviceId_4, NULL, filePath, 1, 0, &D_800B5508.saveBlock_118, 0x300))
            {
                arg0->field_10 = 2;
            }
            break;

        case 2:
            MemCardResult = MemCard_StateResult();
            switch (MemCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14 = MemCardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case MemCardResult_FileCreateError:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14 = MemCardResult;
                    ptr->memoryCardStatus_0 = 0;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    MemCard_RamClear(arg0->deviceId_4);

                    arg0->lastMemCardResult_14 = MemCardResult_FileIoError;
                    ptr->memoryCardStatus_0 = 0;

                    Savegame_FilenameGenerate(filePath, D_800B2778);
                    Savegame_CardFileErase(arg0->deviceId_4, filePath);
                    break;

                case MemCardResult_FileIoComplete:
                    ptr->fileState_4[D_800B2778] = FileState_Used;

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

            if (Savegame_CardRequest(MemCardIoMode_Write, arg0->deviceId_4, NULL, filePath, 0, 0x300, &D_800B5508.userConfig_418, 0x80))
            {
                arg0->field_10 = 4;
            }
            break;

        case 4:
            MemCardResult = MemCard_StateResult();
            switch (MemCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14 = MemCardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14 = MemCardResult_FileIoError;
                    ptr->memoryCardStatus_0 = 0;
                    break;

                case MemCardResult_FileIoComplete:
                    arg0->lastMemCardResult_14 = MemCardResult;
                    break;

                default:
                    break;
            }
            break;

        case 5:
            Savegame_FilenameGenerate(filePath, D_800B2778);
            Savegame_CopyWithChecksum(&D_800B5508.saveGame_498, g_SavegamePtr);

            if (Savegame_CardRequest(MemCardIoMode_Write, arg0->deviceId_4, NULL, filePath, 0, (arg0->saveIdx_C * 0x280) + 0x380, &D_800B5508.saveGame_498, 0x280))
            {
                arg0->field_10 = 6;
            }
            break;

        case 6:
            MemCardResult = MemCard_StateResult();
            switch (MemCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14 = MemCardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14 = MemCardResult_FileIoError;
                    ptr->memoryCardStatus_0 = 0;
                    break;

                case MemCardResult_FileIoComplete:
                    arg0->field_10 = 7;
                    break;
            }
            break;

        case 7:
            func_8002FD5C(arg0->deviceId_4, D_800B2778, arg0->saveIdx_C, g_SavegamePtr);
            arg0->field_10 = 8;

        case 8:
            Savegame_FilenameGenerate(filePath, D_800B2778);

            if (Savegame_CardRequest(MemCardIoMode_Write, arg0->deviceId_4, NULL, filePath, 0, 512, (u8*)D_800B5508.devices_0[arg0->deviceId_4].basicSaveInfo_14 + (D_800B2778 * 0x100), 0x100))
            {
                arg0->field_10 = 9;
            }
            break;

        case 9:
            MemCardResult = MemCard_StateResult();
            switch (MemCardResult)
            {
                case MemCardResult_NotConnected:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14 = MemCardResult;
                    ptr->memoryCardStatus_0 = 1;
                    break;

                case MemCardResult_FileOpenError:
                case MemCardResult_FileSeekError:
                case MemCardResult_FileIoError:
                    MemCard_RamClear(arg0->deviceId_4);
                    arg0->lastMemCardResult_14 = MemCardResult_FileIoError;
                    ptr->memoryCardStatus_0 = 0;
                    break;

                case MemCardResult_FileIoComplete:
                    arg0->lastMemCardResult_14 = MemCardResult;
                    break;
            }
            break;
    }
}

void func_8002FB64(s_MemCard_BasicSaveInfo* saveInfo) // 0x8002FB64
{
    s32 i;

    bzero(saveInfo, sizeof(s_MemCard_BasicSaveInfo));

    for (i = 0; i < 11; i++)
    {
        saveInfo->saveMetadata_4[i].field_0 = 0;
    }

    Savegame_ChecksumUpdate(&saveInfo->field_FC, (s8*)saveInfo, sizeof(s_MemCard_BasicSaveInfo));
}

void Savegame_UserConfigCopyWithChecksum(s_SaveUserConfigContainer* dest, s_SaveUserConfig* src) // 0x8002FBB4
{
    bzero(dest, sizeof(s_SaveUserConfigContainer));
    dest->config_0 = *src;
    Savegame_ChecksumUpdate(&dest->footer_7C, &dest->config_0, sizeof(s_SaveUserConfigContainer));
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
        if (D_800B5508.devices_0[deviceId].fileState_4[fileIdx] != FileState_Used)
        {
            continue;
        }

        for (saveIdx = 0; saveIdx < 11; saveIdx++)
        {
            field0 = D_800B5508.devices_0[deviceId].basicSaveInfo_14[fileIdx].saveMetadata_4[saveIdx].field_0;
            if (largestField0 < field0)
            {
                largestField0FileIdx = fileIdx;
                largestField0        = field0;
            }
        }
    }

    return largestField0FileIdx;
}

void Savegame_CopyWithChecksum(s_SavegameContainer* dest, s_Savegame* src) // 0x8002FCCC
{
    bzero(dest, sizeof(s_SavegameContainer));
    memcpy(&dest->savegame_0, src, sizeof(s_Savegame));
    Savegame_ChecksumUpdate(&dest->footer_27C, &dest->savegame_0, sizeof(s_SavegameContainer));
}

void func_8002FD5C(s32 deviceId, s32 fileIdx, s32 saveIdx, s_Savegame* arg3) // 0x8002FD5C
{
    s_MemCard_BasicSaveInfo* ptr;

    ptr = &D_800B5508.devices_0[deviceId].basicSaveInfo_14[fileIdx];

    func_8002FDB0(deviceId, fileIdx, saveIdx);
    Savegame_ChecksumUpdate(&ptr->field_FC, ptr, sizeof(s_MemCard_BasicSaveInfo));
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

    D_800B5508.devices_0[deviceId].basicSaveInfo_14[fileIdx].saveMetadata_4[saveIdx].field_0 = var + 1;
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
        if (D_800B5508.devices_0[deviceId].fileState_4[fileIdx] != FileState_Used)
        {
            continue;
        }

        for (saveIdx = 0; saveIdx < 11; saveIdx++)
        {
            field0 = D_800B5508.devices_0[deviceId].basicSaveInfo_14[fileIdx].saveMetadata_4[saveIdx].field_0;

            if (result->field_0 < field0)
            {
                result->fileIdx_4 = fileIdx;
                result->saveIdx_8 = saveIdx;
                result->field_0   = field0;
            }
        }
    }
}

void Savegame_ChecksumUpdate(s_Savegame_Footer* saveFooter, s8* saveData, s32 saveDataLength) // 0x8002FF30
{
    u8 checksum;

    saveFooter->checksum_0[0] = saveFooter->checksum_0[1] = 0;
    saveFooter->magic_2                                   = SAVEGAME_FOOTER_MAGIC;
    checksum                                              = Savegame_ChecksumGenerate(saveData, saveDataLength);
    saveFooter->checksum_0[0] = saveFooter->checksum_0[1] = checksum;
}

s32 Savegame_ChecksumValidate(s_Savegame_Footer* saveFooter, s8* saveData, s32 saveDataLength) // 0x8002FF74
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
    strcat(dest, VERSION_SERIAL);
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

s32 Savegame_CardDeviceTest(s32 deviceId) // 0x80030288
{
    u8 cardBuf[128];

    memset(cardBuf, 0xFF, 128);

    MemCard_HwEventsReset();
    _new_card();
    _card_write(((deviceId & (1 << 2)) << 2) | (deviceId & 0x3), 0, cardBuf);

    g_MemCardWork.devicesPending_0 |= 1 << g_MemCardWork.deviceId_3C;

    return MemCard_HwEventsTest() != 0;
}

s32 Savegame_CardDeviceFormat(s32 deviceId) // 0x8003030C
{
    #define BUF_SIZE 16

    char buf[BUF_SIZE];

    Savegame_DevicePathGenerate(deviceId, buf);

    return format(buf);
	
	#undef BUF_SIZE
}

s32 Savegame_CardFileErase(s32 deviceId, char* fileName) // 0x80030334
{
    #define BUF_SIZE 32

    char buf[BUF_SIZE];

    Savegame_DevicePathGenerate(deviceId, buf);

    strcat(buf, fileName);

    return erase(buf);
	
	#undef BUF_SIZE
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
	
	#undef BUF_SIZE
}

void MemCard_Init(void) // 0x800303E4
{
    InitCARD(0);
    StartCARD();
    g_MemCardWork.devicesPending_0 = UINT_MAX; // All bits set.
}

void MemCard_EventsInit(void) // 0x80030414
{
    MemCard_StateInit();
    MemCard_SwEventsInit();
    MemCard_HwEventsInit();
}

void MemCard_StateInit(void) // 0x80030444
{
    g_MemCardWork.state_4       = CardState_Idle;
    g_MemCardWork.stateStep_8   = 0;
    g_MemCardWork.stateResult_C = 0;
}

void MemCard_SwEventsInit(void) // 0x8003045C
{
    EnterCriticalSection();
    g_MemCardWork.eventSwSpIOE_10    = OpenEvent(SwCARD, EvSpIOE, EvMdNOINTR, NULL);
    g_MemCardWork.eventSwSpERROR_14  = OpenEvent(SwCARD, EvSpERROR, EvMdNOINTR, NULL);
    g_MemCardWork.eventSwSpTIMOUT_18 = OpenEvent(SwCARD, EvSpTIMOUT, EvMdNOINTR, NULL);
    g_MemCardWork.eventSwSpNEW_1C    = OpenEvent(SwCARD, EvSpNEW, EvMdNOINTR, NULL);
    ExitCriticalSection();

    EnableEvent(g_MemCardWork.eventSwSpIOE_10);
    EnableEvent(g_MemCardWork.eventSwSpERROR_14);
    EnableEvent(g_MemCardWork.eventSwSpTIMOUT_18);
    EnableEvent(g_MemCardWork.eventSwSpNEW_1C);

    MemCard_SwEventsReset();
}

void MemCard_HwEventsInit(void) // 0x80030530
{
    EnterCriticalSection();
    g_MemCardWork.eventHwSpIOE_20     = OpenEvent(HwCARD, EvSpIOE, EvMdINTR, MemCard_HwEventSpIOE);
    g_MemCardWork.eventHwSpERROR_24   = OpenEvent(HwCARD, EvSpERROR, EvMdINTR, MemCard_HwEventSpERROR);
    g_MemCardWork.eventHwSpTIMOUT_28  = OpenEvent(HwCARD, EvSpTIMOUT, EvMdINTR, MemCard_HwEventSpTIMOUT);
    g_MemCardWork.eventHwSpNEW_2C     = OpenEvent(HwCARD, EvSpNEW, EvMdINTR, MemCard_HwEventSpNEW);
    g_MemCardWork.eventHwSpUNKNOWN_30 = OpenEvent(HwCARD, EvSpUNKNOWN, EvMdINTR, MemCard_HwEventSpUNKNOWN);
    ExitCriticalSection();

    EnableEvent(g_MemCardWork.eventHwSpIOE_20);
    EnableEvent(g_MemCardWork.eventHwSpERROR_24);
    EnableEvent(g_MemCardWork.eventHwSpTIMOUT_28);
    EnableEvent(g_MemCardWork.eventHwSpNEW_2C);
    EnableEvent(g_MemCardWork.eventHwSpUNKNOWN_30);

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
    CloseEvent(g_MemCardWork.eventSwSpIOE_10);
    CloseEvent(g_MemCardWork.eventSwSpERROR_14);
    CloseEvent(g_MemCardWork.eventSwSpTIMOUT_18);
    CloseEvent(g_MemCardWork.eventSwSpNEW_1C);
    ExitCriticalSection();
}

void MemCard_HwEventsClose(void) // 0x800306C8
{
    EnterCriticalSection();
    CloseEvent(g_MemCardWork.eventHwSpIOE_20);
    CloseEvent(g_MemCardWork.eventHwSpERROR_24);
    CloseEvent(g_MemCardWork.eventHwSpTIMOUT_28);
    CloseEvent(g_MemCardWork.eventHwSpNEW_2C);
    CloseEvent(g_MemCardWork.eventHwSpUNKNOWN_30);
    ExitCriticalSection();
}

s32 MemCard_SwEventsTest(void) // 0x80030734
{
    if (TestEvent(g_MemCardWork.eventSwSpERROR_14) == 1)
    {
        return EvSpERROR;
    }

    if (TestEvent(g_MemCardWork.eventSwSpTIMOUT_18) == 1)
    {
        return EvSpTIMOUT;
    }

    if (TestEvent(g_MemCardWork.eventSwSpNEW_1C) == 1)
    {
        return EvSpNEW;
    }

    if (TestEvent(g_MemCardWork.eventSwSpIOE_10) == 1)
    {
        return EvSpIOE;
    }

    return 0;
}

void MemCard_SwEventsReset(void) // 0x800307BC
{
    TestEvent(g_MemCardWork.eventSwSpERROR_14);
    TestEvent(g_MemCardWork.eventSwSpTIMOUT_18);
    TestEvent(g_MemCardWork.eventSwSpNEW_1C);
    TestEvent(g_MemCardWork.eventSwSpIOE_10);
}

s32 MemCard_HwEventsTest(void) // 0x80030810
{
    return g_MemCardWork.lastEventHw_34;
}

void MemCard_HwEventsReset(void) // 0x80030820
{
    TestEvent(g_MemCardWork.eventHwSpERROR_24);
    TestEvent(g_MemCardWork.eventHwSpTIMOUT_28);
    TestEvent(g_MemCardWork.eventHwSpNEW_2C);
    TestEvent(g_MemCardWork.eventHwSpIOE_20);
    TestEvent(g_MemCardWork.eventHwSpUNKNOWN_30);

    g_MemCardWork.lastEventHw_34 = 0;
}

void MemCard_HwEventSpIOE(void) // 0x80030884
{
    g_MemCardWork.lastEventHw_34 = EvSpIOE;
}

void MemCard_HwEventSpERROR(void) // 0x80030894
{
    g_MemCardWork.lastEventHw_34 = EvSpERROR;
}

void MemCard_HwEventSpNEW(void) // 0x800308A4
{
    g_MemCardWork.lastEventHw_34 = EvSpNEW;
}

void MemCard_HwEventSpTIMOUT(void) // 0x800308B4
{
    g_MemCardWork.lastEventHw_34 = EvSpTIMOUT;
}

void MemCard_HwEventSpUNKNOWN(void) // 0x800308C4
{
    g_MemCardWork.lastEventHw_34 = EvSpUNKNOWN;
}

s32 MemCard_StateResult(void) // 0x800308D4
{
    return g_MemCardWork.stateResult_C;
}

bool Savegame_CardRequest(e_MemCardIoMode mode, s32 deviceId, s_CardDirectory* outDir, char* filename, s32 createBlockCount, s32 fileOffset, void* outBuf, s32 bufSize) // 0x800308E4
{
    if (!Savegame_CardIsIdle())
    {
        return false;
    }

    g_MemCardWork.MemCardIoMode_38 = mode;

    switch (mode)
    {
        case MemCardIoMode_Init:
        case MemCardIoMode_DirRead:
            g_MemCardWork.state_4     = CardState_Init;
            g_MemCardWork.stateStep_8 = 0;
            break;

        case MemCardIoMode_Read:
        case MemCardIoMode_Write:
            g_MemCardWork.state_4     = CardState_FileOpen;
            g_MemCardWork.stateStep_8 = 0;
            break;

        case MemCardIoMode_Create:
            g_MemCardWork.state_4     = CardState_FileCreate;
            g_MemCardWork.stateStep_8 = 0;
            break;

        default:
            break;
    }

    g_MemCardWork.deviceId_3C      = deviceId;
    g_MemCardWork.cardDirectory_40 = outDir;

    Savegame_DevicePathGenerate(deviceId, g_MemCardWork.filePath_44);
    strcat(g_MemCardWork.filePath_44, filename);

    g_MemCardWork.createBlockCount_60 = createBlockCount;
    g_MemCardWork.seekOffset_64       = fileOffset;
    g_MemCardWork.dataBuffer_68       = outBuf;
    g_MemCardWork.dataSize_6C         = bufSize;
    g_MemCardWork.hasNewDevice_70     = false;
    return true;
}

s32 Savegame_CardIsIdle(void) // 0x800309FC
{
    return g_MemCardWork.state_4 == CardState_Idle;
}

void Savegame_CardUpdate(void) // 0x80030A0C
{
    switch (g_MemCardWork.state_4)
    {
        case CardState_Idle:
            // @hack Probably some optimized out code here.
            g_MemCardWork.stateResult_C += 0;
            break;

        case CardState_Init:
            g_MemCardWork.stateResult_C = Savegame_CardState_Init();
            break;

        case CardState_Check:
            g_MemCardWork.stateResult_C = Savegame_CardState_Check();
            break;

        case CardState_Load:
            g_MemCardWork.stateResult_C = Savegame_CardState_Load();
            break;

        case CardState_DirRead:
            g_MemCardWork.stateResult_C = Savegame_CardState_DirRead();
            break;

        case CardState_FileCreate:
            g_MemCardWork.stateResult_C = Savegame_CardState_FileCreate();
            break;

        case CardState_FileOpen:
            g_MemCardWork.stateResult_C = Savegame_CardState_FileOpen();
            break;

        case CardState_FileReadWrite:
            g_MemCardWork.stateResult_C = Savegame_CardState_FileReadWrite();
            break;

        default:
            break;
    }
}

s32 Savegame_CardState_Init(void) // 0x80030AD8
{
    s32 channel;
    s32 result;

    result  = MemCardResult_Success;
    channel = ((g_MemCardWork.deviceId_3C & (1 << 2)) << 2) + (g_MemCardWork.deviceId_3C & ((1 << 0) | (1 << 1)));

    switch (g_MemCardWork.stateStep_8)
    {
        case 0:
            g_MemCardWork.retryCount_78 = 0;
            g_MemCardWork.field_7C      = 0;
            g_MemCardWork.stateStep_8   = 1;

        case 1:
            MemCard_SwEventsReset();

            if (_card_info(channel) == 1)
            {
                g_MemCardWork.stateStep_8++;
            }
            else
            {
                g_MemCardWork.retryCount_78++;
            }
            break;

        case 2:
            switch (MemCard_SwEventsTest())
            {
                case EvSpIOE: // Connected.
                    if (g_MemCardWork.MemCardIoMode_38 == MemCardIoMode_Init)
                    {
                        result                 = MemCardResult_InitComplete;
                        g_MemCardWork.state_4     = CardState_Idle;
                        g_MemCardWork.stateStep_8 = 0;
                    }
                    else if (!((g_MemCardWork.devicesPending_0 >> g_MemCardWork.deviceId_3C) & (1 << 0)))
                    {
                        g_MemCardWork.state_4     = CardState_DirRead;
                        g_MemCardWork.stateStep_8 = 0;
                    }
                    else
                    {
                        g_MemCardWork.state_4     = CardState_Check;
                        g_MemCardWork.stateStep_8 = 0;
                    }
                    break;

                case EvSpNEW: // "No writing after connection"
                    g_MemCardWork.hasNewDevice_70 = true;

                    if (g_MemCardWork.MemCardIoMode_38 == MemCardIoMode_Init)
                    {
                        result                 = MemCardResult_InitError;
                        g_MemCardWork.state_4     = CardState_Idle;
                        g_MemCardWork.stateStep_8 = 0;
                    }
                    else
                    {
                        g_MemCardWork.state_4     = CardState_Check;
                        g_MemCardWork.stateStep_8 = 0;
                    }
                    break;

                case EvSpTIMOUT: // Not connected.
                    result                 = MemCardResult_NotConnected;
                    g_MemCardWork.state_4     = CardState_Idle;
                    g_MemCardWork.stateStep_8 = 0;
                    break;

                case EvSpERROR: // Error.
                    g_MemCardWork.stateStep_8 = 1;
                    break;
            }
            break;
    }

    return result;
}

s32 Savegame_CardState_Check(void) // 0x80030C88
{
    s32 channel;
    s32 result;

    result  = MemCardResult_Success;
    channel = ((g_MemCardWork.deviceId_3C & (1 << 2)) << 2) + (g_MemCardWork.deviceId_3C & ((1 << 0) | (1 << 1)));

    switch (g_MemCardWork.stateStep_8)
    {
        case 0:
            g_MemCardWork.retryCount_78 = 0;
            g_MemCardWork.field_7C      = 0;
            g_MemCardWork.stateStep_8   = 1;

        case 1:
            MemCard_HwEventsReset();

            if (_card_clear(channel) == 1)
            {
                g_MemCardWork.stateStep_8++;
            }
            break;

        case 2:
            switch (MemCard_HwEventsTest())
            {
                case EvSpIOE: // Completed.
                    g_MemCardWork.state_4     = CardState_Load;
                    g_MemCardWork.stateStep_8 = 0;
                    break;

                case EvSpTIMOUT: // Card not connected.
                    result                 = MemCardResult_NotConnected;
                    g_MemCardWork.state_4     = CardState_Idle;
                    g_MemCardWork.stateStep_8 = 0;
                    break;

                case EvSpNEW:   // New card detected.
                case EvSpERROR: // Error.
                    g_MemCardWork.stateStep_8 = 1;
                    break;
            }
            break;
    }

    return result;
}

s32 Savegame_CardState_Load(void) // 0x80030DC8
{
    s32 channel;
    s32 result;

    result  = MemCardResult_Success;
    channel = ((g_MemCardWork.deviceId_3C & (1 << 2)) << 2) + (g_MemCardWork.deviceId_3C & ((1 << 0) | (1 << 1)));

    switch (g_MemCardWork.stateStep_8)
    {
        case 0:
            g_MemCardWork.retryCount_78 = 0;
            g_MemCardWork.field_7C      = 0;
            g_MemCardWork.stateStep_8   = 1;

        case 1:
            MemCard_SwEventsReset();

            if (_card_load(channel) == 1)
            {
                g_MemCardWork.stateStep_8++;
                if (!(g_MemCardWork.deviceId_3C & (1 << 2)))
                {
                    g_MemCardWork.devicesPending_0 |= 0xF;
                }
                else
                {
                    g_MemCardWork.devicesPending_0 |= 0xF0;
                }
            }
            break;

        case 2:
            switch (MemCard_SwEventsTest())
            {
                case EvSpIOE: // Read completed.
                    g_MemCardWork.state_4           = CardState_DirRead;
                    g_MemCardWork.stateStep_8       = 0;
                    g_MemCardWork.devicesPending_0 &= ~(1 << g_MemCardWork.deviceId_3C);
                    break;

                case EvSpNEW: // Uninitialized card.
                    g_MemCardWork.devicesPending_0 |= 1 << g_MemCardWork.deviceId_3C;
                    if (g_MemCardWork.retryCount_78 < 3)
                    {
                        g_MemCardWork.retryCount_78++;
                        g_MemCardWork.stateStep_8 = 1;
                    }
                    else
                    {
                        result                 = MemCardResult_LoadError;
                        g_MemCardWork.state_4     = CardState_Idle;
                        g_MemCardWork.stateStep_8 = 0;
                    }
                    break;

                case EvSpTIMOUT: // Not connected.
                    result                 = MemCardResult_NotConnected;
                    g_MemCardWork.state_4     = CardState_Idle;
                    g_MemCardWork.stateStep_8 = 0;
                    break;

                case EvSpERROR: // Error.
                    g_MemCardWork.stateStep_8 = 1;
                    break;
            }
            break;
    }

    return result;
}

s32 Savegame_CardState_DirRead(void) // 0x80030F7C
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
            Savegame_DevicePathGenerate(g_MemCardWork.deviceId_3C, filePath);
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

        strcpy(g_MemCardWork.cardDirectory_40->filenames_0[i], fileInfo.name);
        g_MemCardWork.cardDirectory_40->blockCounts_13B[i] = (fileInfo.size + (8192 - 1)) / 8192;
    }

    result = (g_MemCardWork.hasNewDevice_70 == true) ? MemCardResult_NewDevice : MemCardResult_NoNewDevice;

    g_MemCardWork.state_4     = CardState_Idle;
    g_MemCardWork.stateStep_8 = 0;

    return result;
}

s32 Savegame_CardState_FileCreate(void) // 0x800310B4
{
    s32 result;

    result = MemCardResult_Success;

    switch (g_MemCardWork.stateStep_8)
    {
        case 0:
            g_MemCardWork.retryCount_78 = 0;
            g_MemCardWork.field_7C      = 0;
            g_MemCardWork.stateStep_8   = 1;

        case 1:
            g_MemCardWork.fileHandle_74 = open(g_MemCardWork.filePath_44, (g_MemCardWork.createBlockCount_60 << 16) | O_CREAT);
            if (g_MemCardWork.fileHandle_74 == NO_VALUE)
            {
                if (g_MemCardWork.retryCount_78++ >= 15)
                {
                    result                 = MemCardResult_FileCreateError;
                    g_MemCardWork.state_4     = CardState_Idle;
                    g_MemCardWork.stateStep_8 = 0;
                    break;
                }
            }
            else
            {
                close(g_MemCardWork.fileHandle_74);
                g_MemCardWork.state_4     = CardState_FileOpen;
                g_MemCardWork.stateStep_8 = 0;
            }
            break;
    }

    return result;
}

s32 Savegame_CardState_FileOpen(void) // 0x80031184
{
    s32 mode;
    s32 result;

    result = MemCardResult_Success;

    switch (g_MemCardWork.stateStep_8)
    {
        case 0:
            g_MemCardWork.retryCount_78 = 0;
            g_MemCardWork.field_7C      = 0;
            g_MemCardWork.stateStep_8   = 1;

        case 1:
            switch (g_MemCardWork.MemCardIoMode_38)
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

            g_MemCardWork.fileHandle_74 = open(g_MemCardWork.filePath_44, mode | O_NOWAIT);
            if (g_MemCardWork.fileHandle_74 == NO_VALUE)
            {
                if (g_MemCardWork.retryCount_78++ >= 15)
                {
                    result                 = MemCardResult_FileOpenError;
                    g_MemCardWork.state_4     = CardState_Idle;
                    g_MemCardWork.stateStep_8 = 0;
                    break;
                }
            }
            else
            {
                g_MemCardWork.state_4     = CardState_FileReadWrite;
                g_MemCardWork.stateStep_8 = 0;
            }
            break;
    }

    return result;
}

s32 Savegame_CardState_FileReadWrite(void) // 0x80031260
{
    s32 result;
    s32 ioResult;

    result = MemCardResult_Success;

    switch (g_MemCardWork.stateStep_8)
    {
        case 0:
            g_MemCardWork.retryCount_78 = 0;
            g_MemCardWork.field_7C      = 0;
            g_MemCardWork.stateStep_8   = 1;

        case 1:
            if (lseek(g_MemCardWork.fileHandle_74, g_MemCardWork.seekOffset_64, SEEK_SET) == NO_VALUE)
            {
                if (g_MemCardWork.retryCount_78++ >= 15)
                {
                    result                 = MemCardResult_FileSeekError;
                    g_MemCardWork.state_4     = CardState_Idle;
                    g_MemCardWork.stateStep_8 = 0;
                }
            }
            else
            {
                g_MemCardWork.retryCount_78 = 0;
                g_MemCardWork.stateStep_8++;
            }
            break;

        case 2:
            MemCard_SwEventsReset();

            switch (g_MemCardWork.MemCardIoMode_38)
            {
                case MemCardIoMode_Read:
                    ioResult = read(g_MemCardWork.fileHandle_74, g_MemCardWork.dataBuffer_68, g_MemCardWork.dataSize_6C);
                    break;

                case MemCardIoMode_Write:
                case MemCardIoMode_Create:
                    ioResult = write(g_MemCardWork.fileHandle_74, g_MemCardWork.dataBuffer_68, g_MemCardWork.dataSize_6C);
                    break;

                default:
                    ioResult = NO_VALUE;
                    break;
            }

            if (ioResult == NO_VALUE)
            {
                if (g_MemCardWork.retryCount_78++ >= 15)
                {
                    result                 = MemCardResult_FileIoError;
                    g_MemCardWork.state_4     = CardState_Idle;
                    g_MemCardWork.stateStep_8 = 0;
                    close(g_MemCardWork.fileHandle_74);
                }
            }
            else
            {
                g_MemCardWork.stateStep_8++;
            }
            break;

        case 3:
            switch (MemCard_SwEventsTest())
            {
                case EvSpIOE: // Completed.
                    result                 = MemCardResult_FileIoComplete;
                    g_MemCardWork.state_4     = CardState_Idle;
                    g_MemCardWork.stateStep_8 = 0;
                    close(g_MemCardWork.fileHandle_74);
                    break;

                case EvSpTIMOUT: // Card not connected.
                    result                 = MemCardResult_NotConnected;
                    g_MemCardWork.state_4     = CardState_Idle;
                    g_MemCardWork.stateStep_8 = 0;
                    close(g_MemCardWork.fileHandle_74);
                    break;

                case EvSpNEW: // New card detected.
                    result                 = MemCardResult_FileIoError;
                    g_MemCardWork.state_4     = CardState_Idle;
                    g_MemCardWork.stateStep_8 = 0;
                    close(g_MemCardWork.fileHandle_74);

                case EvSpERROR: // Error.
                    g_MemCardWork.stateStep_8 = 1;
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

const s32 unused_Rodata_80024C98 = 0x8E080000;
