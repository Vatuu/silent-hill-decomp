#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/save_system.h"

#include <libapi.h>

/** It is possible that more functions from `bodyprog.c` are
* actually functions from `save_system`.
*/

s32 func_8002E94C(s32 arg0, s32 arg1, s32 fileIdx, s32 saveIdx) // 0x8002E94C
{
    //s_800B5508_sub* ptr; // TODO: Use this instead.
    s32* ptr;

    if (D_800B5508[8].field_0 != 0) 
    {
        return 0;
    }

    D_800B5508[8].field_0 = arg0;
    ptr                   = &D_800B5508[8].field_0;

    // TODO: Use this instead.
    /*ptr->field_4   = arg1;
    ptr->fileIdx_8 = fileIdx;
    ptr->saveIdx_C = saveIdx;
    ptr->field_10  = 0;
    ptr->field_14  = 1;*/

    ptr[1] = arg1;
    ptr[2] = fileIdx;
    ptr[3] = saveIdx;
    ptr[4] = 0;
    ptr[5] = 1;
    return 1;
}

// Used in `SAVELOAD.BIN`
s32 func_8002E990() // 0x8002E990
{
    return D_800B55FC;
}

s32 func_8002E9A0(s32 idx) // 0x8002E9A0
{
    s32 ret;
    s32 i;

    ret = 0;

    for (i = 0; i < 15; i++)
    {
        ret |= D_800B5508[idx].field_4[i] << (i * 2);
    }

    return ret;
}

s32 func_8002E9EC(s32 arg0, s32 fileIdx, s32 saveIdx) // 0x8002E9EC
{
    s32 var0;
    s32 var1;
    s32 var2;

    var0 = D_800B5508[arg0].field_14;
    var1 = fileIdx << 8; 
    var2 = (saveIdx * 12) + 4; 
    return var0 + var1 + var2;
}

s32 func_8002EA28(s32 idx) // 0x8002EA28
{
    s32 ret;
    s32 i;

    ret = 0;

    for (i = 0; i < 15; i++)
    {
        if (D_800B5508[idx].field_4[i] != 0)
        {
            ret++;
        }
    }

    return ret;
}

s32 func_8002EA78(s32 idx) // 0x8002EA78
{
    return D_800B5508[idx].field_18 - func_8002EA28(idx);
}

s32 func_8002EABC(s32* arg0, s32* arg1, s32* arg2) // 0x8002EABC
{
    VECTOR vec; // Vaguely assumed to be a `VECTOR`.
    s32 i;
    s32 ret;

    ret = 0;

    *arg0 = 0;
    *arg1 = 0;
    *arg2 = 0;

    for (i = 0; i < 8; i++) 
    {
        if (D_800B5508[i].field_0 == 3) 
        {
            func_8002FE70(i, &vec);

            if (ret < vec.vx) 
            {
                *arg0 = i;

                *arg1 = vec.vy;
                *arg2 = vec.vz;

                ret = vec.vx;
            }
        }
    }

    return ret != 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_8002EB88);

void func_8002ECE0(s_800B55E8* arg0) // 0x8002ECE0
{
    if (func_8003030C(arg0->field_4) != 0)
    {
        arg0->field_14 = 11;
        D_800B5508[arg0->field_4].field_0 = 3;

        func_8002E730(arg0->field_4);

        D_800B5508[arg0->field_4].field_18 = 15;
    }
    else
    {
        arg0->field_14 = 10;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_8002ED7C);

s32 func_8002F278(s32 arg0, s_func_8002F278* arg1) // 0x8002F278
{
    s32 ret;
    s32 i; 

    ret = 15;
    for (i = 0; i < 15; i++) 
    {
        ret -= arg1->field_13B[i];
    }

    return ret + func_8002EA28(arg0);
}

// Related to saves. Seems to constantly write to `D_800B55FC`.
INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_8002F2C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_8002F61C);

void func_8002FB64(s_func_8002FB64 *arg0) // 0x8002FB64
{
    s32 i;

    bzero(arg0, sizeof(s_func_8002FB64));

    for (i = 0; i < 11; i++)
    {
        arg0->field_0[i][1] = 0;
    }

    Savegame_ChecksumUpdate(&arg0->field_FC, (s8*)arg0, sizeof(s_func_8002FB64));
}

void Savegame_UserConfigCopyWithChecksum(s_ShSaveUserConfigContainer* dest, s_ShSaveUserConfig* src) // 0x8002FBB4
{
    bzero(dest, sizeof(s_ShSaveUserConfigContainer));
    dest->config_0 = *src;
    Savegame_ChecksumUpdate(&dest->footer_7C, &dest->config_0, sizeof(s_ShSaveUserConfigContainer));
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_8002FC3C);

void Savegame_CopyWithChecksum(s_ShSavegameContainer* dest, s_ShSavegame* src) // 0x8002FCCC
{
    bzero(dest, sizeof(s_ShSavegameContainer));
    memcpy(&dest->savegame_0, src, sizeof(s_ShSavegame));
    Savegame_ChecksumUpdate(&dest->footer_27C, &dest->savegame_0, sizeof(s_ShSavegameContainer));
}

void func_8002FD5C(s32 arg0, s32 arg1, s32 arg2) // 0x8002FD5C
{ 
    s_func_8002FB64* ptr;

    ptr = (s_func_8002FB64*)D_800B5508[arg0].field_14;
    ptr = &ptr[arg1];

    func_8002FDB0(arg0, arg1, arg2); 
    Savegame_ChecksumUpdate(&ptr->field_FC, ptr, sizeof(s_func_8002FB64));  
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_8002FDB0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_8002FE70);

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
    int i        = 0;

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

    memcpy(dest, "BA", 3);

    strcat(dest, "SLUS-00707");
    strcat(dest, "SILENT");

    buf[0] = '0' + (saveIdx / 10);
    buf[1] = '0' + (saveIdx % 10);
    buf[2] = 0;

    strcat(dest, buf);
}

void func_800300B4(s_PsxSaveBlock* saveBlock, s8 blockCount, s32 saveIdx) // 0x800300B4
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

s32 func_80030288(s32 deviceId) // 0x80030288
{
    u8 cardBuf[128];

    memset(cardBuf, 0xFF, 128);

    func_80030820();
    _new_card();
    _card_write(((deviceId & 0x4) * 4) | (deviceId & 0x3), 0, cardBuf);

    D_800B5488.field_0 |= 1 << D_800B5488.field_3C;

    return func_80030810() != 0;
}

s32 func_8003030C(s32 deviceId) // 0x8003030C
{
    #define BUF_SIZE 16

    char buf[BUF_SIZE];

    Savegame_DevicePathGenerate(deviceId, buf);

    return format(buf);
}

s32 func_80030334(s32 deviceId, char* fileName) // 0x80030334
{
    #define BUF_SIZE 32

    char buf[BUF_SIZE];

    Savegame_DevicePathGenerate(deviceId, buf);

    strcat(buf, fileName);

    return erase(buf);
}

s32 func_80030370(s32 deviceId, char* prevName, char* newName) // 0x80030370
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

void func_800303E4() // 0x800303E4
{
    InitCARD(0);
    StartCARD();
    D_800B5488.field_0 = NO_VALUE;
}

void func_80030414() // 0x80030414
{
    func_80030444();
    func_8003045C();
    func_80030530();
}

void func_80030444() // 0x80030444
{
    s_800B5488* var = &D_800B5488;

    var->field_4 = 0;
    var->field_8 = 0;
    var->field_C = 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_8003045C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030530);

void func_80030640() // 0x80030640
{
    func_80030668();
    func_800306C8();
}

void func_80030668() // 0x80030668
{
    EnterCriticalSection();
    CloseEvent(D_800B5488.event_10);
    CloseEvent(D_800B5488.event_14);
    CloseEvent(D_800B5488.event_18);
    CloseEvent(D_800B5488.event_1C);
    ExitCriticalSection();
}

void func_800306C8() // 0x800306C8
{
    EnterCriticalSection();
    CloseEvent(D_800B5488.event_20);
    CloseEvent(D_800B5488.event_24);
    CloseEvent(D_800B5488.event_28);
    CloseEvent(D_800B5488.event_2C);
    CloseEvent(D_800B5488.event_30);
    ExitCriticalSection();
}

s32 func_80030734() // 0x80030734
{
    if (TestEvent(D_800B5488.event_14) == 1)
    {
        return 1 << 15;
    }

    if (TestEvent(D_800B5488.event_18) == 1)
    {
        return 1 << 8;
    }

    if (TestEvent(D_800B5488.event_1C) == 1)
    {
        return 1 << 13;
    }

    if (TestEvent(D_800B5488.event_10) == 1)
    {
        return 1 << 2;
    }

    return 0;
}

void func_800307BC() // 0x800307BC
{
    TestEvent(D_800B5488.event_14);
    TestEvent(D_800B5488.event_18);
    TestEvent(D_800B5488.event_1C);
    TestEvent(D_800B5488.event_10);
} 

s32 func_80030810() // 0x80030810
{
    return D_800B5488.field_34;
}

void func_80030820() // 0x80030820
{
    TestEvent(D_800B5488.event_24);
    TestEvent(D_800B5488.event_28);
    TestEvent(D_800B5488.event_2C);
    TestEvent(D_800B5488.event_20);
    TestEvent(D_800B5488.event_30);

    D_800B5488.field_34 = 0;
}

void func_80030884() // 0x80030884
{
    D_800B5488.field_34 = 4;
}

void func_80030894() // 0x80030894
{
    D_800B5488.field_34 = 0x8000;
}

void func_800308A4() // 0x800308A4
{
    D_800B5488.field_34 = 0x2000;
}

void func_800308B4() // 0x800308B4
{
    D_800B5488.field_34 = 0x100;
}

void func_800308C4() // 0x800308C4
{
    D_800B5488.field_34 = 0x200;
}

s32 func_800308D4() // 0x800308D4
{
    return D_800B5488.field_C;
}

s32 func_800308E4(s32 arg0, s32 arg1, s32 arg2, char* str, s32 arg4, s32 arg5, s32 arg6, s32 arg7) // 0x800308E4
{
    if (!func_800309FC())
    {
        return 0;
    }

    D_800B5488.field_38 = arg0;

    switch (arg0)
    {
        case 0:
        case 1:
            D_800B5488.field_4 = 1;
            D_800B5488.field_8 = 0;
            break;

        case 2:
        case 3:
            D_800B5488.field_4 = 6;
            D_800B5488.field_8 = 0;
            break;

        case 4:
            D_800B5488.field_4 = 5;
            D_800B5488.field_8 = 0;
            break;

        default:
            break;
    }

    D_800B5488.field_3C = arg1;
    D_800B5488.field_40 = arg2;

    Savegame_DevicePathGenerate(arg1, &D_800B5488.field_44);
    strcat(&D_800B5488.field_44, str);

    D_800B5488.field_60 = arg4;
    D_800B5488.field_64 = arg5;
    D_800B5488.field_68 = arg6;
    D_800B5488.field_6C = arg7;
    D_800B5488.field_70 = 0;
    return 1;
}

s32 func_800309FC() // 0x800309FC
{
    return D_800B5488.field_4 == 0;
}

void func_80030A0C() // 0x80030A0C
{
    switch (D_800B5488.field_4)
    {
        case 0:
            // HACK: Probably some optimized out code here.
            D_800B5488.field_C += 0;
            break;

        case 1:
            D_800B5488.field_C = func_80030AD8();
            break;

        case 2:
            D_800B5488.field_C = func_80030C88();
            break;

        case 3:
            D_800B5488.field_C = func_80030DC8();
            break;

        case 4:
            D_800B5488.field_C = func_80030F7C();
            break;

        case 5:
            D_800B5488.field_C = func_800310B4();
            break;

        case 6:
            D_800B5488.field_C = func_80031184();
            break;

        case 7:
            D_800B5488.field_C = func_80031260();
            break;

        default:
            break;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030AD8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030C88);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030DC8);

s32 func_80030F7C() // 0x80030F7C
{
    struct DIRENTRY  fileInfo;
    struct DIRENTRY* curFile;
    char             filePath[16];
    s32              retval;
    s32              i;

    for (i = 0; i < 15; i++)
    {
        *D_800B5488.field_40->fileNames_0[i]    = D_80024B64; // `00` byte near start of bodyprog rodata, far from `save.c` rodata section?
        D_800B5488.field_40->blockCounts_13B[i] = 0;
    }

    for (i = 0; i < 15; i++)
    {
        if (i == 0)
        {
            Savegame_DevicePathGenerate(D_800B5488.field_3C, filePath);
            strcat(filePath, "*");
            curFile = firstfile(filePath, &fileInfo);
        }
        else
        {
            curFile = nextfile(&fileInfo);
        }

        if (curFile == NULL)
            break;

        strcpy(&D_800B5488.field_40->fileNames_0[i], fileInfo.name);
        D_800B5488.field_40->blockCounts_13B[i] = (fileInfo.size + (8192 - 1)) / 8192;
    }

    retval = (D_800B5488.field_70 == 1) ? 5 : 6;

    D_800B5488.field_4 = 0;
    D_800B5488.field_8 = 0;

    return retval;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_800310B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80031184);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80031260);

void Savegame_DevicePathGenerate(s32 deviceId, char* result) // 0x800314A4
{
    strcpy(result, "buXX:");

    result[2] = '0' + ((deviceId & (1 << 2)) >> 2); // Packed device ID?
    result[3] = '0' + (deviceId & 3);
}
