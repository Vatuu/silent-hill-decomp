#include "game.h"

#include <libcd.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math.h"
#include "bodyprog/vw_system.h"
#include "main/fsqueue.h"
#include "main/rng.h"
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

void func_80085DF0()
{
    g_SysWork.field_2C += g_DeltaTime1;
    
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
    s32 unkTime;

    unkTime = g_SysWork.field_2C + g_DeltaTime1;
    g_SysWork.field_2C = unkTime;
    
    if (arg0 < unkTime)
    {
        func_80085D78(arg1);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80085EB8);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008605C);

void func_800860B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 sysStateStep, s32 arg5)
{
    s32 ret;

    ret = func_800365B8(arg1);
    if (ret <= 0)
    {
        return;
    }
    
    if (arg0 == 0)
    {
        func_80085D78(arg5);
        return;
    }

    if (ret == 1)
    {
        func_80085DC0(arg5, arg2);
    }
    if (ret == 2)
    {
        func_80085DC0(arg5, arg3);
    }
    if (ret == 3)
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
                        g_SysWork.flags_22A4 |= (1 << 3);
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

void func_800867B4(s32 caseParam, s32 idx)
{
    switch (caseParam)
    {
        case 0:
            DrawSync(0);
            StoreImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(0);

            // TODO: What are these offsets?
            Fs_QueueStartReadTim(D_800A99B4[idx] + 0x768, FS_BUFFER_2, &D_800A901C);
            Fs_QueueStartReadTim(D_800A99CC[idx] + 0x776, FS_BUFFER_1, &D_800A9024);
            
            GFX_Init(0x140, 1);
            GsSwapDispBuff();
            Fs_QueueWaitForEmpty();
            break;
        
        case 1:
            func_800314EC(&D_800A901C);
            break;
        
        case 2:
            LoadImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(0);
            GFX_Init(0x140, 0);
            break;

        default:
            break;
    }
}

void func_800868DC(s32 idx)
{
    D_800C4710[idx] = 0;
}

s32 func_800868F4(s32 arg0, s32 arg1, s32 idx)
{
    D_800C4710[idx] += g_DeltaTime0;
    D_800C4710[idx] = (arg1 < D_800C4710[idx]) ? arg1 : D_800C4710[idx];
    
    return (arg0 * D_800C4710[idx]) / arg1;
}

s32 func_8008694C(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 idx)
{
    D_800C4710[idx] += g_DeltaTime0;
    D_800C4710[idx] = (arg3 < D_800C4710[idx]) ? arg3 : D_800C4710[idx];
    return (arg0 * shRsin(arg1 + ((arg2 * D_800C4710[idx]) / arg3))) >> 12;
}

// TODO: Matched, but checksum fails.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800869E4);
/*void func_800869E4(u8* arg1, u8* arg2, s16* arg3)
{
    s32 ret;

    g_SysWork.field_22A0 |= 0x20;
    
    ret = func_800365B8();
    if (ret == 1)
    {
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.sysStateStep_C++;
    }
    else if (ret == -1)
    {
        SD_EngineCmd(arg3[*arg2]);
        *arg2 += 1;
    }
}*/

void Camera_SetTranslation(VECTOR3* pos, s32 xPosOffset, s32 yPosOffset, s32 zPosOffset,
                           s32 xzAccel, s32 yAccel, s32 xzSpeedMax, s32 ySpeedMax, s32 warpCamFlag) // 0x80086A94
{
    VECTOR3         posTarget;
    VC_CAM_MV_PARAM camTranslationParams;

    // Set position target.
    if (pos != NULL)
    {
        posTarget.vx = pos->vx + xPosOffset;
        posTarget.vy = pos->vy + yPosOffset;
        posTarget.vz = pos->vz + zPosOffset;
    }
    else
    {
        posTarget.vx = xPosOffset;
        posTarget.vy = yPosOffset;
        posTarget.vz = zPosOffset;
    }

    // Set acceleration on XZ plane.
    if (xzAccel == 0)
    {
        camTranslationParams.accel_xz = cam_mv_prm_user.accel_xz;
    }
    else
    {
        camTranslationParams.accel_xz = xzAccel;
    }

    // Set acceleration on Y axis.
    if (yAccel == 0)
    {
        camTranslationParams.accel_y = cam_mv_prm_user.accel_y;
    }
    else
    {
        camTranslationParams.accel_y = yAccel;
    }

    // Set max speed on XZ plane.
    if (xzSpeedMax == 0)
    {
        camTranslationParams.max_spd_xz = cam_mv_prm_user.max_spd_xz;
    }
    else
    {
        camTranslationParams.max_spd_xz = xzSpeedMax;
    }

    // Set max speed on Y axis.
    if (ySpeedMax == 0)
    {
        camTranslationParams.max_spd_y = cam_mv_prm_user.max_spd_y;
    }
    else
    {
        camTranslationParams.max_spd_y = ySpeedMax;
    }

    // Set camera position target.
    vcUserCamTarget(&posTarget, &camTranslationParams, warpCamFlag);
}

void Camera_SetRotation(VECTOR3* lookAt, s32 xLookAtOffset, s32 yLookAtOffset, s32 zLookAtOffset,
                        s32 xAngularAccel, s32 yAngularAccel, s32 xAngularSpeedMax, s32 yAngularSpeedMax, s32 warpLookAtFlag) // 0x80086B70
{
    VECTOR3           lookAtTarget;
    VC_WATCH_MV_PARAM camRotParams;

    // Set look-at target.
    if (lookAt != NULL)
    {
        lookAtTarget.vx = lookAt->vx + xLookAtOffset;
        lookAtTarget.vy = lookAt->vy + yLookAtOffset;
        lookAtTarget.vz = lookAt->vz + zLookAtOffset;
    }
    else
    {
        lookAtTarget.vx = xLookAtOffset;
        lookAtTarget.vy = yLookAtOffset;
        lookAtTarget.vz = zLookAtOffset;
    }

    // Set angular acceleration on X axis.
    if (xAngularAccel == 0)
    {
        camRotParams.ang_accel_x = deflt_watch_mv_prm.ang_accel_x;
    }
    else
    {
        camRotParams.ang_accel_x = xAngularAccel;
    }

    // Set angular acceleration on Y axis.
    if (yAngularAccel == 0)
    {
        camRotParams.ang_accel_y = deflt_watch_mv_prm.ang_accel_y;
    }
    else
    {
        camRotParams.ang_accel_y = yAngularAccel;
    }

    // Set max angular speed on X axis.
    if (xAngularSpeedMax == 0)
    {
        camRotParams.max_ang_spd_x = deflt_watch_mv_prm.max_ang_spd_x;
    }
    else
    {
        camRotParams.max_ang_spd_x = xAngularSpeedMax;
    }
    
    // Set max angular speed on Y axis.
    if (yAngularSpeedMax == 0)
    {
        camRotParams.max_ang_spd_y = deflt_watch_mv_prm.max_ang_spd_y;
    }
    else
    {
        camRotParams.max_ang_spd_y = yAngularSpeedMax;
    }

    // Set camera flags and rotation target.
    vcWorkSetFlags(0, VC_VISIBLE_CHARA_F);
    vcUserWatchTarget(&lookAtTarget, &camRotParams, warpLookAtFlag);
}

void func_80086C58(s32 arg0, s32 arg1)
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_80085EB8(0, arg0, arg1, 0);
            
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;
        
        case 1:
            func_80085EB8(1, arg0, 0, 1);
            break;
        
        default:
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.sysStateStep_C++;
            break;
    }
}

void func_80086D04(s32 arg0)
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_80085EB8(3, arg0, 0, 0);
            
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;
        
        case 1:
            func_80085EB8(1, arg0, 0, 1);
            break;
        
        default:
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.sysStateStep_C++;
            break;
    }
}

void func_80086DA8(s32 arg0, s32 arg1)
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_8008616C(0, 1, 0, arg1, 0);
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
        
        case 1:
            func_800862F8(7, arg0, 1);
            break;
        
        default:
            func_8008616C(1, 1, 0, 0, 0);
            break;
    }
}

void func_80086E50(s32 arg0, s32 arg1, s32 arg2)
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_8008616C(0, 1, 0, arg1, 0);
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, arg0, 1);
            break;

        case 2:
            func_8008616C(1, 1, 0, 0, 1);
            break;

        default:
            func_800862F8(2, 0, 0);
            func_8008616C(2, 0, 0, arg2, 0);
    }
}

void func_80086F44(s32 arg0, s32 arg1)
{
    if (g_SysWork.field_10 == 0)
    {
        func_800862F8(2, 0, 0, arg0);
        func_8008616C(2, 1, 0, arg1, 1);
        return;
    }
    
    func_8008616C(0, 0, 0, arg0, 0);
    g_SysWork.field_28 = 0;
    g_SysWork.field_10 = 0;
    g_SysWork.field_2C = 0;
    g_SysWork.field_14 = 0;
    g_SysWork.sysStateStep_C++;
}

void func_80086FE8(s32 arg0, s32 arg1, s32 arg2)
{
    s32 i;
    
    if (!(g_SysWork.flags_22A4 & (1 << 5)))
    {
        // Run through NPCs.
        for (i = 0; i < NPC_COUNT_MAX; i++)
        {
            // NPC type is >=24 or health is 0.
            if ((u32)((u8)g_SysWork.characters_1A0[i].chara_type_0 - 1) >= 24 ||
                g_SysWork.characters_1A0[i].health_B0 <= 0)
            {
                continue;
            }

            break;
        }
        
        if (i != NPC_COUNT_MAX)
        {
            g_DeltaTime0 = 0;
        }
    }
    
    switch (g_SysWork.field_10)
    {
        case 0:
            D_800C9644();
            func_8005DC1C(arg1, arg2, 0x80, 0);
            
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
        
        case 1:
            func_80085E6C(0x333, 1);
            break;
        
        case 2:
            func_800860B0(0, arg0, 0, 0, 0, 1);
            break;
        
        default:
            D_800C9648(0);
            
            g_SysWork.sysState_8 = 0;
            g_SysWork.field_24 = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            break;
    }
}

// Requires jump table.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008716C);

// Requires jump table.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80087360);

// Requires jump table.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80087540);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800877B8);

// Requires jump table.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800879FC);

// Requires jump table.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80087AF4);

void func_80087EA8(s32 arg0)
{
    if (func_800358A8() == 0)
    {
        return;
    }
    
    func_800358DC(arg0);
}

void func_80087EDC(s32 arg0)
{
    if ((func_80045B28() & 0xFF) || Fs_QueueDoThingWhenEmpty() == 0)
    {
        return;
    }
    
    switch (g_SysWork.field_10)
    {
        case 0:
            if (func_800358A8(arg0) == 0)
            {
                g_SysWork.field_10 = 3;
                g_SysWork.field_2C = 0;
                g_SysWork.field_14 = 0;
                return;
            }
            
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_22A0 |= 1 << 7;
            g_SysWork.field_10++;
            return;
        
        case 1:
            g_SysWork.field_22A0 |= 1 << 7;
            SD_EngineCmd(23);
            
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            return;
        
        case 2:
            g_SysWork.field_22A0 |= 1 << 7;
            
            if (!(func_80045BC8() & 0xFFFF))
            {
                func_800358DC(arg0);
                
                g_SysWork.field_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.field_10++;
            }
            break;
        
        case 3:
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.sysStateStep_C++;
            break;

        default:
            break;
    }
}

void func_80088028(void)
{
    func_80087EDC(0);
}

void func_80088048(void)
{
    if (func_80045B28() & 0xFF)
    {
        return;
    }
    
    switch (g_SysWork.field_10)
    {
        case 0:
            func_80035E1C();
            SD_EngineCmd(18);
            
            g_SysWork.field_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;
            
        case 1:
            if (!(func_80045BC8() & 0xFFFF))
            {
                g_SysWork.field_28 = 0;
                g_SysWork.field_10 = 0;
                g_SysWork.field_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.sysStateStep_C++;
            }
            break;

        default:
            break;
    }
}

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

s32 func_80088D0C()
{
    Fs_QueueWaitForEmpty();
    func_8003D95C();
    return 1;
}

void func_80088D34(s32 idx)
{
    idx++; 
    func_800445A4(D_800A992C[idx].field_8, D_800A992C[idx].field_20);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Chara_Spawn);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088F94);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088FF4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089034);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089090);

void func_800890B8()
{
    func_8009E198(&g_SysWork.field_2514[0], 0);
    func_8009E310(&g_SysWork.field_2514[0], &g_SysWork.field_2514[8] , 2);
    func_8009EBB8(&g_SysWork.field_2514[0], &g_SysWork.field_2514[12], 16);
    
    g_SysWork.field_2510 = func_8009E4F8();
    
    func_8009E7D8(g_SysWork.field_2510);
    func_8009E97C(g_SysWork.field_2510);
}

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

void func_8008D78C()
{
    s32 var_v1;
    s32 var_s1;

    if (D_800C4818.field_2 == 0)
    {
        return;
    }
    D_800C4818.field_2 = 0;
    
    if (D_800C4818.field_0 != 0)
    {
        return;
    }
    
    var_s1 = func_8008D850();
    if (var_s1 != 0)
    {
        var_v1 = D_800C4818.field_8 - D_800C4818.field_A;
    }
    else
    {
        var_v1 = -D_800C4818.field_A;
    }
    
    D_800C4818.field_A += var_v1 >> 1;
    
    if (vcRetCamMvSmoothF() == 0)
    {
        D_800C4818.field_A = 0;
        var_s1 = 0;
    }
    
    func_8008D990(var_s1, D_800C4818.field_A, &D_800C4818.field_C, D_800C4818.field_1C, D_800C4818.field_20);
}

s32 func_8008D850()
{
    s16 rectX;
    RECT rect;
    s_8008D850 unk; 

    rectX = 784;
    if (g_ObjectTableIdx == 0)
    {
        rectX = 792;
    }

    rect.y = 112;
    rect.w = 2;
    rect.x = rectX;
    rect.h = 1;
    
    DrawSync(0);
    StoreImage2(&rect, &unk.field_0);
    DrawSync(0);

    return (unk.field_0 & 0x7FFF) == 0x7FFF;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D8C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D990);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E4EC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E51C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E5B4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E794);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008EA68);

void func_8008EF18() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008EF20);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F048);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_DataRead);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F0BC);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F13C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_GameGlobalsUpdate);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_GameGlobalsRestore);

void Demo_GameRandSeedUpdate() // 0x8008f33c
{
    g_Demo_PrevRandSeed = Rng_GetSeed();
    Rng_SetSeed(D_800AFDBC);
}

void Demo_GameRandSeedRestore() // 0x8008f370
{
    Rng_SetSeed(g_Demo_PrevRandSeed);
}

void Demo_Start() // 0x8008F398
{
    D_800AFDEC = 1;
    g_SysWork.flags_22A4 |= 2;
    
    Demo_GameGlobalsUpdate();
    Demo_GameRandSeedUpdate();
    
    g_GameWork.field_5A8 = 1;
    g_GameWork.field_5AC = 1;
}

void Demo_Stop() // 0x8008f3f0
{
    D_800AFDEC = 0;
    g_SysWork.flags_22A4 &= ~(1 << 1);
    
    Demo_GameGlobalsRestore(-3);
    Demo_GameRandSeedRestore();
}

s32 func_8008F434(s32 arg0)
{
    s32 caseVar = arg0 & ~1;

    switch (caseVar)
    {
        case 2:
        case 3:
        case 4:
        case 5:
        case 10:
        case 11:
        case 12:
        case 13:
            return 0;

        default:
            break;
    }

    return 1;
}

// TODO: Says D_800BCCB8 is an undefined reference.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F470);
/*s32 func_8008F470(s32 caseArg)
{
    switch (caseArg)
    {
        case 11:
            if (g_SysWork.sysState_8 == 13)
            {
                return -1;
            }
            else if (D_800BCCB8 == 16)
            {
                return -1;
            }

        case 12:
        case 13:
        case 14:
        case 15:
            return 1;
    
        case 18:
            return 1;
    
        default:
            break;
    }

    return 0;
}*/

void Demo_ExitDemo() // 0x8008F4E4
{
    D_800A9768 = 0xEA24;
    g_Demo_ControllerPacket = NULL;
    g_Demo_DemoStep = 0;
    g_SysWork.flags_22A4 |= 1 << 8;
}

void func_8008F518() {}

s32 func_8008F520()
{
    return 0;
}

void Demo_DemoRandSeedBackup() // 0x8008F528
{
    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        g_Demo_RandSeedBackup = Rng_GetSeed();
    }
}

void Demo_DemoRandSeedRestore() // 0x8008F560
{
    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        Rng_SetSeed(g_Demo_RandSeedBackup);
    }
}

void Demo_DemoRandSeedAdvance() // 0x8008F598
{
    #define SEED_OFFSET 0x3C6EF35F

    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        Rng_SetSeed(g_Demo_RandSeedBackup + SEED_OFFSET);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_Update);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Demo_JoyUpdate);

s32 Demo_PresentIntervalUpdate() // 0x8008F87C
{
    g_Demo_VideoPresentInterval = 1;
    
    if (g_Demo_ControllerPacket == NULL)
    {
        return 0;
    }
    
    g_Demo_VideoPresentInterval = g_Demo_ControllerPacket->field_9;
    return 1;
}

s32 Demo_GameRandSeedSet() // 0x8008F8A8
{
    if (!(g_SysWork.flags_22A4 & (1 << 1)))
    {
        return 1;
    }
    else if (g_Demo_ControllerPacket == NULL)
    {
        Rng_SetSeed(D_800AFDBC);
        return 0;
    }
    else
    {
        Rng_SetSeed(g_Demo_ControllerPacket->btns_held_C);
        return 1;
    }
}

s32 func_8008F914()
{
    if (g_SysWork.flags_22A4 & (1 << 1))
    {
        return func_8004393C();
    }
    
    return 1;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008F94C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800904F4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80090664);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8009134C);

void func_80091380() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80091388);

void func_80091464() {}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8009146C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800914C4);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8009151C);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80091778);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800917C0);

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8009185C);
