#include "game.h"

#include <libcd.h>

#include "bodyprog/bodyprog.h"
#include "screens/stream/stream.h"

void func_80035338(s32 arg0, s8 arg1, u32 arg2, s32 arg3); // arg3 type assumed.
void func_8003D5B4(s8 arg0);
void func_8003D6E0(s32 arg0, s32 arg1, s32 arg2, void* arg3);

void func_80085D78(s32 arg0)
{
    if (arg0 != 0)
    {
        g_SysWork.field_2C = 0;
        g_SysWork.field_14 = 0;
        g_SysWork.field_10++;
        return;
    }
    
    g_SysWork.field_28 = 0;
    g_SysWork.field_10 = 0;
    g_SysWork.field_2C = 0;
    g_SysWork.field_14 = 0;
    g_SysWork.sysStateStep_C++;
}

void func_80085DC0(s32 arg0, s32 sysStateStep)
{
    if (arg0 != 0)
    {
        g_SysWork.field_10 = sysStateStep;
        g_SysWork.field_2C = 0;
        g_SysWork.field_14 = 0;
    }
    else
    {
        g_SysWork.sysStateStep_C = sysStateStep;
        g_SysWork.field_28 = 0;
        g_SysWork.field_10 = 0;
        g_SysWork.field_2C = 0;
        g_SysWork.field_14 = 0;
    }
}

void func_80085DF0(void)
{
    g_SysWork.field_2C += D_800A8FEC;
    
    if (D_800C9668() != 0 || g_SysWork.field_2C > 4096)
    {
        g_SysWork.field_28 = 0;
        g_SysWork.field_10 = 0;
        g_SysWork.field_2C = 0;
        g_SysWork.field_14 = 0;
        g_SysWork.sysStateStep_C++;
    }
}

void func_80085E6C(s32 arg0, s32 arg1)
{
    s32 temp_v0;

    temp_v0 = g_SysWork.field_2C + D_800A8FEC;
    g_SysWork.field_2C = temp_v0;
    
    if (arg0 < temp_v0)
    {
        func_80085D78(arg1);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80085EB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008605C);

void func_800860B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 sysStateStep, s32 arg5)
{
    s32 temp_v0;

    temp_v0 = func_800365B8(arg1);
    if (temp_v0 <= 0)
    {
        return;
    }
    
    if (arg0 == 0)
    {
        func_80085D78(arg5);
        return;
    }

    if (temp_v0 == 1)
    {
        func_80085DC0(arg5, arg2);
    }
    if (temp_v0 == 2)
    {
        func_80085DC0(arg5, arg3);
    }
    if (temp_v0 == 3)
    {
        func_80085DC0(arg5, sysStateStep);
    }
}

// TODO: Get rid of gotos.
void func_8008616C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;

    if (arg0 != 2)
    {
        var_v1 = arg0;
    }
    else
    {
        var_v1 = g_SysWork.field_14;
    }

    // Irregular
    switch (var_v1)
    {
        case 0:
            if (arg2 != 2)
            {
                D_800B5C30 = arg3;
            }
            
            if (arg1 != 0)
            {
                if (arg2 == 0)
                {
                    D_800BCD0C = 3;
                }
                else if (arg2 == 1)
                {
                    D_800BCD0C = 11;
                }
                else
                {
                    g_SysWork.field_30 = 18;
                    if (arg2 == 3)
                    {
                        g_SysWork.flags_22A4 |= 8;
                    }
                }
            }
            else if (arg2 == 0)
            {
                D_800BCD0C = 7;
            }
            else if (arg2 == 1)
            {
                D_800BCD0C = 15;
            }
            else
            {
                g_SysWork.field_30 = 22;
            }
            
            if (arg0 != 0)
            {
                g_SysWork.field_14++;
                break;
            }
            
            break;
        
        case 1:
            if (arg2 < 2)
            {
                if (arg1 != 0 || D_800BCD0C != var_v1)
                {
                    if (arg1 == var_v1)
                    {
                        var_v1_2 = 5;
                        var_v0 = D_800BCD0C & 7;

                        if (var_v1_2 == var_v0)
                        {
                            func_80085D78(arg4);
                        }
                    }
                }
                else
                {
                    goto block_32;
                }
            }
            else if (arg1 != 0 || g_SysWork.field_30 != var_v1)
            {
                if (arg1 == var_v1)
                {
                    var_v1_2 = g_SysWork.field_30;
                    var_v0 = 21;
                    
                    if (var_v1_2 == var_v0)
                    {
                        goto block_32;
                    }
                }
            }
            else
            {
    block_32:
                func_80085D78(arg4);
            }
            
            break;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800862F8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80086470);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800865FC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800866D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80086728);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008677C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800867B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800868DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800868F4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008694C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800869E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80086A94);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80086B70);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80086C58);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80086D04);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80086DA8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80086E50);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80086F44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80086FE8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008716C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80087360);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80087540);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800877B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800879FC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80087AF4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80087EA8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80087EDC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088028);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088048);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800880F0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800881B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088370);

// arg2 type assumed.
s32 Chara_Load(s32 arg0, s8 arg1, s32 arg2, s8 arg3, s32 arg4, s32 arg5) // 0x80088C7C
{
    func_80035338(arg0 + 1, arg1, 0, arg2);
    func_8003D5B4(arg3);
    func_8003D6E0(arg1, arg0, arg4, arg5);
    return 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088D0C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088D34);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Chara_Spawn);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088F94);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088FF4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089034);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089090);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800890B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089128);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800892A4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800892DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089314);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800893D0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008944C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089470);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089494);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800894B8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800894DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089500);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089524);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800895E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089644);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008973C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089840);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008989C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008992C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800899BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089A30);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089BB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089D0C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089DF0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A058);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A0CC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A0D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A0E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A270);

// TODO: Has match on decomp.me, some issues getting it to build.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A2E0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A35C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A384);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A398);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A3AC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A3E0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B15C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B1DC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B398);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B3E4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B40C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B438);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B474);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B664);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B714);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008BF84);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008C9A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CA44);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CA60);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CA74);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CB10);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CB90);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CC98);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CDBC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CE1C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CF54);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CFEC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D1D0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D2C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D330);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D3D4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D41C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D438);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D448);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D454);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D464);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D470);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D5A0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D78C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D850);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D8C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D990);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E4EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E51C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E5B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E794);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008EA68);

void func_8008EF18(void) {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008EF20);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F048);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_DataRead);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F0BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F13C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_GameGlobalsUpdate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_GameGlobalsRestore);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_GameRandSeedUpdate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_GameRandSeedRestore);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_Start);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_Stop);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F434);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F470);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_ExitDemo);

void func_8008F518(void) {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F520);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_DemoRandSeedBackup);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_DemoRandSeedRestore);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_DemoRandSeedAdvance);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_Update);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_JoyUpdate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_PresentIntervalUpdate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_GameRandSeedSet);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F914);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F94C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800904F4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80090664);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8009134C);

void func_80091380(void) {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80091388);

void func_80091464(void) {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8009146C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800914C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8009151C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80091778);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800917C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8009185C);
