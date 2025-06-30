#include "game.h"

#include "bodyprog/bodyprog.h"
#include "bodyprog/save_system.h"

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

void func_8002FD5C(s32 arg0, s32 arg1, s32 arg2) 
{ 
    s_func_8002FB64* var_s0;

    var_s0 = (s_func_8002FB64*)D_800B5508[arg0].field_14;
    var_s0 = &var_s0[arg1];

    func_8002FDB0(arg0, arg1, arg2); 
    Savegame_ChecksumUpdate(&var_s0->field_FC, var_s0, sizeof(s_func_8002FB64));  
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030000);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_800300B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030288);

void func_8003030C(s32 arg0) // 0x8003030C
{
    s_80024C90 sp10;
    s_80024C90 unused; 

    func_800314A4(arg0, &sp10); 

    format(&sp10);
}

void func_80030334(s32 arg0, s32 arg1) // 0x80030334
{
    s_80024C90 sp10;
    s_80024C90 unused1;
    s_80024C90 unused2;
    s_80024C90 unused3;

    func_800314A4(arg0, &sp10); 

    strcat(&sp10, arg1); 
    erase(&sp10); 
} 

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030370);

void func_800303E4()
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030668);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_800306C8);

s32 func_80030734() // 0x80030734
{
    if (TestEvent(D_800B5488.field_14) == 1)
    {
        return 1 << 15;
    }

    if (TestEvent(D_800B5488.field_18) == 1)
    {
        return 1 << 8;
    }

    if (TestEvent(D_800B5488.field_1C) == 1)
    {
        return 1 << 13;
    }

    if (TestEvent(D_800B5488.field_10) == 1)
    {
        return 1 << 2;
    }

    return 0;
}

void func_800307BC() // 0x800307BC
{
    TestEvent(D_800B5488.field_14);
    TestEvent(D_800B5488.field_18);
    TestEvent(D_800B5488.field_1C);
    TestEvent(D_800B5488.field_10);
} 

s32 func_80030810() // 0x80030810
{
    return D_800B54BC;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030820);

void func_80030884() // 0x80030884
{
    D_800B54BC = 4;
}

void func_80030894() // 0x80030894
{
    D_800B54BC = 0x8000;
}

void func_800308A4() // 0x800308A4
{
    D_800B54BC = 0x2000;
}

void func_800308B4() // 0x800308B4
{
    D_800B54BC = 0x100;
}

void func_800308C4() // 0x800308C4
{
    D_800B54BC = 0x200;
}

s32 func_800308D4() // 0x800308D4
{
    return D_800B5494.field_0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_800308E4);

s32 func_800309FC() // 0x800309FC
{
    return D_800B548C == 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030A0C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030AD8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030C88);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030DC8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80030F7C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_800310B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80031184);

INCLUDE_ASM("asm/bodyprog/nonmatchings/save", func_80031260);

void func_800314A4(s32 arg0, s_80024C90* arg1) // 0x800314A4
{
    *arg1 = D_80024C90;

    arg1->field_2 = ((arg0 & (1 << 2)) >> 2) + 48;
    arg1->field_3 = (arg0 & 0x3) + 48;
}
