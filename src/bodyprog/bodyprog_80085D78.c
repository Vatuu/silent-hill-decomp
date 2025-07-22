#include "game.h"

#include <libpad.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

void func_80085D78(s32 arg0) // 0x80085D78
{
    if (arg0 != 0)
    {
        g_SysWork.timer_2C = 0;
        g_SysWork.field_14 = 0;
        g_SysWork.field_10++;
        return;
    }

    g_SysWork.field_28 = 0;
    g_SysWork.field_10 = 0;
    g_SysWork.timer_2C = 0;
    g_SysWork.field_14 = 0;
    g_SysWork.sysStateStep_C++;
}

void func_80085DC0(s32 arg0, s32 sysStateStep) // 0x80085DC0
{
    if (arg0 != 0)
    {
        g_SysWork.field_10 = sysStateStep;
        g_SysWork.timer_2C = 0;
        g_SysWork.field_14 = 0;
    }
    else
    {
        g_SysWork.sysStateStep_C = sysStateStep;
        g_SysWork.field_28       = 0;
        g_SysWork.field_10       = 0;
        g_SysWork.timer_2C       = 0;
        g_SysWork.field_14       = 0;
    }
}

void func_80085DF0() // 0x80085DF0
{
    g_SysWork.timer_2C += g_DeltaTime1;

    if (g_MapOverlayHeader.func_EC() != NULL || g_SysWork.timer_2C > 4096)
    {
        g_SysWork.field_28 = 0;
        g_SysWork.field_10 = 0;
        g_SysWork.timer_2C = 0;
        g_SysWork.field_14 = 0;
        g_SysWork.sysStateStep_C++;
    }
}

void func_80085E6C(s32 arg0, s32 arg1) // 0x80085E6C
{
    s32 unkTime;

    unkTime            = g_SysWork.timer_2C + g_DeltaTime1;
    g_SysWork.timer_2C = unkTime;

    if (arg0 < unkTime)
    {
        func_80085D78(arg1);
    }
}

void func_80085EB8(u32 arg0, s_SubCharacter* chara0, s_SubCharacter* chara1, s32 arg3) // 0x80085EB8
{
    s32 res;

    switch (arg0)
    {
        case 0:
            if (chara0 == &g_SysWork.player_4C.chara_0)
            {
                g_MapOverlayHeader.func_D4(chara1);
            }
            else 
            {
                g_MapOverlayHeader.func_124(chara0);
            }
            break;

        case 1:
            if (chara0 == &g_SysWork.player_4C.chara_0)
            {
                res = g_MapOverlayHeader.func_E8(chara0);
                if (res == 1) 
                {
                    func_80085D78(arg3);
                }
            }
            else
            {
                res = g_MapOverlayHeader.func_138(chara0);
                if (res == 1)
                {
                    func_80085D78(arg3);
                }
            }
            break;

        case 2:
            if (chara0 == &g_SysWork.player_4C.chara_0)
            {
                g_MapOverlayHeader.func_DC(chara0);
            }
            else
            {
                g_MapOverlayHeader.func_12C(chara0);
            }
            break;

        case 3:
            if (chara0 == &g_SysWork.player_4C.chara_0)
            {
                g_MapOverlayHeader.func_E4(chara0, chara1);
            }
            else 
            {
                g_MapOverlayHeader.func_134(chara0);
            }
            break;

        case 4:
            if (chara0 == &g_SysWork.player_4C.chara_0)
            {
                g_MapOverlayHeader.func_E4(chara0, chara1);
                g_MapOverlayHeader.func_D8();
            }
            else 
            {
                g_MapOverlayHeader.func_128(chara0);
            }
            break;
    }
}

void func_8008605C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x8008605C
{
    if (!(g_SavegamePtr->eventFlags_168[arg0 >> 5] & (u32)(1 << (arg0 & 0x1F))))
    {
        func_80085DC0(arg3, arg2);
    }
    else
    {
        func_80085DC0(arg3, arg1);
    }
}

void func_800860B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 sysStateStep, s32 arg5) // 0x800860B0
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

void func_8008616C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x8008616C
{
    s32 caseVar;
    s32 var0;
    s32 var1;

    if (arg0 != 2)
    {
        caseVar = arg0;
    }
    else
    {
        caseVar = g_SysWork.field_14;
    }

    switch (caseVar)
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
                    g_Gfx_ScreenFade = 3;
                }
                else if (arg2 == 1)
                {
                    g_Gfx_ScreenFade = 11;
                }
                else
                {
                    g_SysWork.field_30 = 18;

                    if (arg2 == 3)
                    {
                        g_SysWork.flags_22A4 |= 1 << 3;
                    }
                }
            }
            else if (arg2 == 0)
            {
                g_Gfx_ScreenFade = 7;
            }
            else if (arg2 == 1)
            {
                g_Gfx_ScreenFade = 15;
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
                if (arg1 != 0 || g_Gfx_ScreenFade != caseVar)
                {
                    if (arg1 == caseVar && (g_Gfx_ScreenFade & 0x7) == 5)
                    {
                        func_80085D78(arg4);
                    }
                    break;
                }
            }
            else if ((arg1 != 0 || g_SysWork.field_30 != caseVar) && !(arg1 == caseVar && g_SysWork.field_30 == 21))
            {
                break;
            }

            func_80085D78(arg4);
            break;
    }
}

const RECT D_8002AB10 = { 320, 256, 192, 240 }; // 0x8002AB10 .rodata

void func_800862F8(s32 arg0, s32 arg1, s32 arg2) // 0x800862F8
{
    s32 switchVar;

    if (arg0 == 7)
    {
        switchVar = g_SysWork.field_14;
    }
    else
    {
        switchVar = arg0;
        if (switchVar == 8)
        {
            switchVar = 1;
            if (g_SysWork.field_14 == 0)
            {
                switchVar = 4;
            }
        }
    }

    switch (switchVar)
    {
        case 0:
            Fs_QueueStartReadTim(arg1, FS_BUFFER_1, &D_800A902C);

            if (arg0 != 0)
            {
                g_SysWork.field_14++;
                
                if (Fs_QueueDoThingWhenEmpty() != 0)
                {
                    func_80085D78(arg2);
                }
            }
            break;

        case 1:
            if (Fs_QueueDoThingWhenEmpty() != 0)
            {
                func_80085D78(arg2);
            }
            break;

        case 2:
            func_80031AAC(&D_800A902C);
            break;

        case 3:
            DrawSync(0);
            StoreImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(0);
            break;

        case 4:
            Fs_QueueStartReadTim(arg1, FS_BUFFER_1, &D_800A9A04);

            if (arg0 == 8)
            {
                g_SysWork.field_14 = 1;
            }
            break;

        case 5:
            func_80031AAC(&D_800A9A04);
            break;

        case 6:
            LoadImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(0);
            break;

        default:
            break;
    }
}

void func_80086470(u32 switchVar, s32 itemId, s32 itemCount, s32 arg3) // 0x80086470
{
    s32 switchVarCpy;

    if (switchVar == 6 && g_SysWork.field_14 == 0)
    {
        g_SysWork.field_14 = 2;
    }

    switchVarCpy = switchVar;

    if (switchVar >= 2)
    {
        if (switchVar == 2)
        {
            switchVarCpy = 3;
        }
        else if (switchVar == 3)
        {
            switchVarCpy = 2;
        }
        else
        {
            switchVarCpy = g_SysWork.field_14;
        }
    }

    switch (switchVarCpy)
    {
        case 0:
            GameFs_UniqueItemModelLoad(itemId);
            
            if (switchVar == 0)
            {
                g_SysWork.field_10 += 0;
                g_SysWork.timer_2C  = 0;
                g_SysWork.field_14  = 0;
            }

            g_SysWork.field_14++;

        case 1:
            if (Fs_QueueDoThingWhenEmpty() == 0)
            {
                break;
            }

            func_80054A04(itemId);

            if (switchVar == 1 || switchVar == 4)
            {
                func_80085D78(arg3);
                break;
            }

            g_SysWork.field_14++;

        case 2:
            g_SysWork.field_14 = 0;
            
            if (switchVar == 3 || switchVar == 6)
            {
                func_80054CAC(itemId, itemCount & 0xFF);
            }
            break;

        default:
            break;
    }
}

void func_800865FC(s32 arg0, s32 idx0, s32 idx1, s16 arg3, s32 arg4, s32 arg5) // 0x800865FC
{
    if (arg0 == 0) 
    {
        D_800C4640[idx0][idx1].vx = g_SysWork.player_4C.chara_0.position_18.vx + arg4;
        D_800C4640[idx0][idx1].vy = g_SysWork.player_4C.chara_0.position_18.vy;
        D_800C4640[idx0][idx1].vz = g_SysWork.player_4C.chara_0.position_18.vz + arg5;

        D_800C4700[idx0] = arg3;
    }
    else if (arg0 == 1)
    {
        D_800C4640[idx0][idx1].vx = arg4;
        D_800C4640[idx0][idx1].vy = g_SysWork.player_4C.chara_0.position_18.vy;
        D_800C4640[idx0][idx1].vz = arg5;

        D_800C4700[idx0] = arg3;
    }
}

void func_800866D4(s32 arg0, s32 arg1, s32 arg2) // 0x800866D4
{
    if (g_MapOverlayHeader.func_D0(arg0, &D_800C4640, D_800C4700[0], arg1) == 1)
    {
        func_80085D78(arg2);
    }
}

void func_80086728(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x80086728
{
    if (g_MapOverlayHeader.func_13C(arg0, arg1, &D_800C46A0, D_800C4702, arg2) == 1)
    {
        func_80085D78(arg3);
    }
}

void func_8008677C(s32 arg0, s32 arg1, s32 arg2) // 0x8008677C
{
    g_MapOverlayHeader.func_13C(arg0, arg1, &D_800C46A0, D_800C4702, arg2);
}

void func_800867B4(s32 caseParam, s32 idx) // 0x800867B4
{
    switch (caseParam)
    {
        case 0:
            DrawSync(0);
            StoreImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(0);

            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + D_800A99B4[idx], FS_BUFFER_2, &D_800A901C);
            Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + D_800A99CC[idx], FS_BUFFER_1, &D_800A9024);

            Gfx_Init(SCREEN_WIDTH, 1);
            GsSwapDispBuff();
            Fs_QueueWaitForEmpty();
            break;

        case 1:
            Gfx_BackgroundSpriteDraw(&D_800A901C);
            break;

        case 2:
            LoadImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(0);
            Gfx_Init(SCREEN_WIDTH, 0);
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
    D_800C4710[idx]  = (arg1 < D_800C4710[idx]) ? arg1 : D_800C4710[idx];

    return (arg0 * D_800C4710[idx]) / arg1;
}

s32 func_8008694C(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 idx)
{
    D_800C4710[idx] += g_DeltaTime0;
    D_800C4710[idx] = (arg3 < D_800C4710[idx]) ? arg3 : D_800C4710[idx];
    return (arg0 * shRsin(arg1 + ((arg2 * D_800C4710[idx]) / arg3))) >> 12;
}

void func_800869E4(u8* arg0, u8* arg1, u16* arg2) // 0x800869E4
{
    s32 ret;

    g_SysWork.field_22A0 |= 1 << 5;

    ret = func_800365B8(arg0);
    if (ret == 1)
    {
        g_SysWork.field_28 = 0;
        g_SysWork.field_10 = 0;
        g_SysWork.timer_2C = 0;
        g_SysWork.field_14 = 0;
        g_SysWork.sysStateStep_C++;
    }
    else if (ret == NO_VALUE)
    {
        Sd_EngineCmd(arg2[*arg1]);
        *arg1 += 1;
    }
}

void Camera_TranslationSet(VECTOR3* pos, s32 xPosOffset, s32 yPosOffset, s32 zPosOffset,
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

void Camera_RotationSet(VECTOR3* lookAt, s32 xLookAtOffset, s32 yLookAtOffset, s32 zLookAtOffset,
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

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;

        case 1:
            func_80085EB8(1, arg0, 0, 1);
            break;

        default:
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
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
            
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;

        case 1:
            func_80085EB8(1, arg0, 0, 1);
            break;

        default:
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
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
            g_SysWork.timer_2C = 0;
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
            g_SysWork.timer_2C = 0;
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

void func_80086F44(s32 arg0, s32 arg1) // 0x80086F44
{
    if (g_SysWork.field_10 == 0)
    {
        func_800862F8(2, 0, 0);
        func_8008616C(2, 1, 0, arg1, 1);
        return;
    }

    func_8008616C(0, 0, 0, arg0, 0);
    g_SysWork.field_28 = 0;
    g_SysWork.field_10 = 0;
    g_SysWork.timer_2C = 0;
    g_SysWork.field_14 = 0;
    g_SysWork.sysStateStep_C++;
}

void func_80086FE8(s32 arg0, s32 arg1, s32 arg2) // 0x80086FE8
{
    s32 i;
    
    if (!(g_SysWork.flags_22A4 & (1 << 5)))
    {
        // Run through NPCs.
        for (i = 0; i < NPC_COUNT_MAX; i++)
        {
            // NPC type is >=24 or health is 0.
            if ((u32)((u8)g_SysWork.npcs_1A0[i].model_0.charaId_0 - 1) >= 24 ||
                g_SysWork.npcs_1A0[i].health_B0 <= 0)
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
            g_MapOverlayHeader.func_C8();
            func_8005DC1C(arg1, arg2, 0x80, 0);
            
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_80085E6C(0x333, 1);
            break;
        
        case 2:
            func_800860B0(0, arg0, 0, 0, 0, 1);
            break;

        default:
            g_MapOverlayHeader.func_CC(0);

            g_SysWork.sysState_8 = 0;
            g_SysWork.timer_24 = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28 = 0;
            g_SysWork.field_10 = 0;
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            break;
    }
}

void func_8008716C(s32 arg0, s32 arg1, s32 arg2) // 0x8008716C
{
    s32 var;

    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_8008616C(0, 1, 0, arg1, 0);
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, arg0, 1);
            break;

        case 2:
            func_8008616C(1, 1, 0, 0, 1);
            break;

        case 3:
            func_800862F8(2, 0, 0);

            var = 0;
            func_8008616C(2, var, 0, arg2, 1);
            break;

        case 4:
            func_800862F8(2, 0, 0);

            if (g_ControllerPtrConst->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                        g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.field_10++;
            }
            break;

        case 5:
            func_800862F8(2, 0, 0);

            var = 1;
            func_8008616C(2, var, 0, arg2, 1);
            break;

        default:
            func_8008616C(0, 0, 0, arg1, 0);
            g_MapOverlayHeader.func_CC(0);

            g_SysWork.sysState_8     = 0;
            g_SysWork.timer_24       = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28       = 0;
            g_SysWork.field_10       = 0;
            g_SysWork.timer_2C       = 0;
            g_SysWork.field_14       = 0;
            break;
    }
}

void func_80087360(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x80087360
{
    s32 var;

    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_8008616C(0, 1, 0, arg1, 0);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, arg0, 1);
            break;

        case 2:
            func_8008616C(1, 1, 0, 0, 1);
            break;

        case 3:
            func_800862F8(2, 0, 0);

            var = 0;
            func_8008616C(2, var, 0, arg2,1);
            break;

        case 4:
            func_800862F8(2, 0, 0);
            func_800860B0(0, arg3, 0, 0, 0, 1);
            break;
        
        case 5:
            func_800862F8(2, 0, 0);

            var = 1;
            func_8008616C(2, var, 0, arg2, 1);
            break;

        default:
            func_8008616C(0, 0, 0, arg1, 0);
            g_MapOverlayHeader.func_CC(0);

            g_SysWork.sysState_8     = 0;
            g_SysWork.timer_24       = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28       = 0;
            g_SysWork.field_10       = 0;
            g_SysWork.timer_2C       = 0;
            g_SysWork.field_14       = 0;
            break;
    }
}

void func_80087540(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) // 0x80087540
{
    s32 var;

    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_8008616C(0, 1, 0, arg1, 0);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, arg0, 1);
            break;

        case 2:
            func_8008616C(1, 1, 0, 0, 1);
            break;

        case 3:
            func_800862F8(2, 0, 0);
            func_8008616C(2, 0, 0, arg2, 1);
            break;

        case 4:
            func_800862F8(2, 0, 0);
            
            if (arg3 != 0)
            {
                var = arg3;
                func_800860B0(0, var, 0, 0, 0, 1);
                break;
            }

            if (g_ControllerPtrConst->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                        g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.field_10++;
            }
            break;

        case 5:
            D_800A8E58 = 0x30;
            func_800862F8(2, 0, 0);

            var = arg4;
            func_800860B0(0, var, 0, 0, 0, 1);
            break;

        case 6:
            D_800A8E58 = 0x30;

            func_800862F8(2, 0, 0);
            func_8008616C(2, 1, 0, arg2, 1);
            break;

        default:
            func_8008616C(0, 0, 0, arg1, 0);
            g_MapOverlayHeader.func_CC(0);

            g_SysWork.sysState_8     = 0;
            g_SysWork.timer_24       = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28       = 0;
            g_SysWork.field_10       = 0;
            g_SysWork.timer_2C       = 0;
            g_SysWork.field_14       = 0;
            break;
    }
}

void func_800877B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) // 0x800877B8
{
    s32 i   = arg0;
    s32 var = arg3;

    if (!(g_SysWork.flags_22A4 & (1 << 5)))
    {
        // Traverse NPCs.
        for (i = 0; i < NPC_COUNT_MAX; i++)
        {
            if ((u32)((u8)g_SysWork.npcs_1A0[i].model_0.charaId_0 - 1) >= 24 ||
                g_SysWork.npcs_1A0[i].health_B0 <= 0)
            {
                continue;
            }

            break;
        }
        
        if (i != 6)
        {
            g_DeltaTime0 = 0;
        }
    }

    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_80086470(0, arg0, 0, 0);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_80086470(1, arg0, 0, 1);
            break;

        case 2:
            if (func_80054AD8(arg0) != 0)
            {
                func_800860B0(1, var, 3, NO_VALUE, 0, 1);
            }

            g_SavegamePtr->eventFlags_168[arg2 >> 5] |= 1 << (arg2 & 0x1F);
            break;

        case 3:
            func_80086470(3, arg0, arg1, 0);
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        default:    
            if (g_SysWork.field_10 == NO_VALUE)
            {
                g_SavegamePtr->eventFlags_168[arg2 >> 5] &= ~(1 << (arg2 & 0x1F));
            }

            g_MapOverlayHeader.func_CC(0);
            g_SysWork.sysState_8     = 0;
            g_SysWork.timer_24       = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28       = 0;
            g_SysWork.field_10       = 0;
            g_SysWork.timer_2C       = 0;
            g_SysWork.field_14       = 0;
            break;
    }
}

void func_800879FC(u32 arg0, s32 arg1) // 0x800879FC
{
    s32 var0;
    s32 var1;
    s32 var2;
    s32 newBulletAdjust;
    s32 var4;

    newBulletAdjust = g_GameWork.config_0.optExtraBulletAdjust_2D + 1;
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        var4 = 2;
        if (newBulletAdjust >= var4)
        {
            var4 = newBulletAdjust;
        }

        newBulletAdjust = var4;
    }

    switch (arg0)
    {
        case 0:
            var0 = InventoryItemId_FirstAidKit;
            var1 = 1;
            var2 = 5;
            func_800877B8(var0, var1, arg1, var2);
            break;

        case 1:
            var0 = InventoryItemId_HealthDrink;
            var1 = 1;
            var2 = 6;
            func_800877B8(var0, var1, arg1, var2);
            break;

        case 2:
            var0 = InventoryItemId_Ampoule;
            var1 = 1;
            var2 = 7;

            func_800877B8(var0, var1, arg1, var2);
            break;

        case 3:
            var0 = InventoryItemId_HandgunBullets;
            var1 = newBulletAdjust * 15;
            var2 = 8;
            func_800877B8(var0, var1, arg1, var2);
            break;

        case 5:
            var0 = InventoryItemId_ShotgunShells;
            var1 = newBulletAdjust * 6;
            var2 = 10;
            func_800877B8(var0, var1, arg1, var2);
            break;

        case 4:
            var0 = InventoryItemId_RifleShells;
            var1 = newBulletAdjust * 6;
            var2 = 9;
            func_800877B8(var0, var1, arg1, var2);
            break;

        default:
            break;
    }
}

// TODO: RODATA migration.
#ifdef NON_MATCHING
void func_80087AF4(s32 mapFlagIdx, s32 eventFlagIdx, s32 arg2) // 0x80087AF4
{
    s32 mapFlagIdxCpy;

    g_DeltaTime0  = 0;
    mapFlagIdxCpy = mapFlagIdx;

    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            Fs_QueueStartSeek(D_800A99B4[mapFlagIdx] + 0x768);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_8008616C(2, 1, 0, 0, 1);
            break;

        case 2:
            DrawSync(0);
            StoreImage(&D_8002ABA4, IMAGE_BUFFER);
            DrawSync(0);
            Fs_QueueStartReadTim(D_800A99B4[mapFlagIdx] + 0x768, FS_BUFFER_2, &D_800A901C);
            Gfx_Init(0x140, 1);

            g_IntervalVBlanks = 1;

            GsSwapDispBuff();
            func_8008616C(0, 0, 0, 0, 0);
            Fs_QueueWaitForEmpty();

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 3:
            D_800A8E58 = 0x58;

            func_800314EC(&D_800A901C);
            func_800860B0(1, arg2, 4, 5, 0, 1);
            break;

        case 4:
            mapFlagIdxCpy                                            = mapFlagIdx >> 5;
            ((s32*)&g_SavegamePtr->hasMapsFlags_164)[mapFlagIdxCpy] |= 1 << (mapFlagIdx & 0x1F); // Maybe union?

            switch (mapFlagIdx)
            {
                case 6:
                    g_SavegamePtr->hasMapsFlags_164 |= 0x1FA0;
                    break;

                case 17:
                    g_SavegamePtr->hasMapsFlags_164 |= 1 << 18;
                    g_SavegamePtr->hasMapsFlags_164 |= 1 << 19;
                    g_SavegamePtr->hasMapsFlags_164 |= 1 << 21;
                    g_SavegamePtr->hasMapsFlags_164 |= 1 << 22;
                    g_SavegamePtr->hasMapsFlags_164 |= 1 << 23;
                    break;

                case 16:
                    g_SavegamePtr->hasMapsFlags_164 |= 1 << 20;
                    break;

                case 13:
                    g_SavegamePtr->hasMapsFlags_164 |= 1 << 14;
                    break;

                case 2:
                    g_SavegamePtr->hasMapsFlags_164 |= 1 << 3;
                    break;

                default:
                    break;
            }

            g_SavegamePtr->eventFlags_168[eventFlagIdx >> 5] |= 1 << (eventFlagIdx & 0x1F);
            g_SysWork.timer_2C                                = 0;
            g_SysWork.field_14                                = 0;
            g_SysWork.field_10++;

        case 5:
            D_800A8E58 = 0x58;

            func_800314EC(&D_800A901C);
            func_8008616C(2, 1, 0, 0, 1);
            break;

        default:
            LoadImage(&D_8002ABA4, IMAGE_BUFFER);
            DrawSync(0);
            Gfx_Init(0x140, 0);
            func_8008616C(0, 0, 0, 0, 0);
            g_MapOverlayHeader.func_CC(0);

            g_SysWork.sysState_8     = 0;
            g_SysWork.timer_24       = 0;
            g_SysWork.sysStateStep_C = 0;
            g_SysWork.field_28       = 0;
            g_SysWork.field_10       = 0;
            g_SysWork.timer_2C       = 0;
            g_SysWork.field_14       = 0;
            break;
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80087AF4); // 0x80087AF4
#endif

void func_80087EA8(s32 cmd) // 0x80087EA8
{
    if (func_800358A8(cmd) == 0)
    {
        return;
    }

    func_800358DC(cmd);
}

void func_80087EDC(s32 arg0) // 0x80087EDC
{
    if (func_80045B28() || Fs_QueueDoThingWhenEmpty() == 0)
    {
        return;
    }
    
    switch (g_SysWork.field_10)
    {
        case 0:
            if (func_800358A8(arg0) == 0)
            {
                g_SysWork.field_10 = 3;
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                return;
            }
            
            g_SysWork.timer_2C    = 0;
            g_SysWork.field_14    = 0;
            g_SysWork.field_22A0 |= 1 << 7;
            g_SysWork.field_10++;
            return;
        
        case 1:
            g_SysWork.field_22A0 |= 1 << 7;
            Sd_EngineCmd(23);
            
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            return;
        
        case 2:
            g_SysWork.field_22A0 |= 1 << 7;
            
            if (!func_80045BC8())
            {
                func_800358DC(arg0);
                
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.field_10++;
            }
            break;
        
        case 3:
            SysWork_StateStepIncrement(); // Resets `field_10` to 0.
            break;

        default:
            break;
    }
}

void func_80088028() // 0x80088028
{
    func_80087EDC(0);
}

void func_80088048() // 0x80088048
{
    if (func_80045B28())
    {
        return;
    }

    switch (g_SysWork.field_10)
    {
        case 0:
            func_80035E1C();
            Sd_EngineCmd(18);
            
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;

        case 1:
            if (!func_80045BC8())
            {
                SysWork_StateStepIncrement(); // Resets `field_10` to 0.
            }
            break;

        default:
            break;
    }
}

void func_800880F0(s32 arg0) // 0x800880F0
{
    if (func_80045B28())
    {
        return;
    }

    switch (g_SysWork.field_10)
    {
        case 0:
            func_80035E1C();

            if (arg0 == 0)
            {
                Sd_EngineCmd(0x16);
            }
            else
            {
                Sd_EngineCmd(0x17);
            }

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;

        case 1:
            if (!func_80045BC8())
            {
                SysWork_StateStepIncrement(); // Resets `field_10` to 0.
            }
            break; 
    }
}

void func_800881B8(s32 x0, s16 y0, s32 x1, s16 y1, s16 arg4, s16 arg5, s16 arg6, s32 arg7, s32 arg8, u32 arg9, s16 argA, s32 argB) // 0x800881B8
{
    POLY_FT4* poly;

    poly = (POLY_FT4*)GsOUT_PACKET_P;
    setPolyFT4(poly);

    setXY0Fast(poly, x0 - x1, y0 - y1);
    setXY1Fast(poly, x0 + x1, y0 - y1);
    setXY2Fast(poly, x0 - x1, y0 + y1);
    setXY3Fast(poly, x0 + x1, y0 + y1);

    *(u32*)(&poly->u0) = arg4 + (arg5 << 8) + (getClut(arg9, argA) << 16);
    *(u32*)(&poly->u1) = (arg4 + arg6) + (arg5 << 8) + (getTPage(0, 0, argB << 6, (((argB >> 4) & 1) << 8)) << 16);
    *(u16*)(&poly->u2) = arg4 + ((arg5 + arg7) << 8);
    *(u16*)(&poly->u3) = (arg4 + arg6) + ((arg5 + arg7) << 8);

    *(u16*)(&poly->r0) = arg8 + (arg8 << 8);
    poly->b0 = arg8;

    setSemiTrans(poly, 0);

    addPrim(g_ObjectTable0[g_ObjectTableIdx].org, poly);
    poly++;

    GsOUT_PACKET_P = (PACKET*)poly;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088370); // 0x80088370

s32 Chara_Load(s32 arg0, s8 arg1, s32 arg2, s8 arg3, s32 arg4, s32 arg5) // 0x80088C7C
{
    func_80035338(arg0 + 1, arg1, 0, arg2);
    func_8003D5B4(arg3);
    func_8003D6E0(arg1, arg0, arg4, arg5);
    return 1;
}

s32 func_80088D0C() // 0x80088D0C
{
    Fs_QueueWaitForEmpty();
    func_8003D95C();
    return 1;
}

void func_80088D34(s32 idx) // 0x80088D34
{
    idx++;
    func_800445A4(D_800A992C[idx].field_8, D_800A992C[idx].field_14);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", Chara_Spawn); // 0x80088D78

void func_80088F94(s_SubCharacter* chara) // 0x80088F94
{
    u8   temp0;
    s32* temp1;

    if (chara == NULL)
    {
        return;
    }

    if (chara->model_0.charaId_0 <= Chara_MonsterCybil)
    {
        temp0   = chara->field_40;
        temp1   = &(&g_SysWork.field_228C)[(temp0 << 24) >> 29];
        *temp1 &= ~(1 << (temp0 & 0x1F));
    }

    chara->model_0.charaId_0 = Chara_None;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088FF4); // 0x80088FF4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089034); // 0x80089034

void func_80089090(s32 arg0) // 0x80089090
{
    func_80089524(&g_SysWork.field_2514, arg0);
}

void func_800890B8() // 0x800890B8
{
    func_8009E198(&g_SysWork.field_2514, 0);
    func_8009E310(&g_SysWork.field_2514, g_SysWork.field_2514.field_20, 2);
    func_8009EBB8(&g_SysWork.field_2514, g_SysWork.field_2514.field_30, 16);

    g_SysWork.field_2510 = func_8009E4F8();

    func_8009E7D8(g_SysWork.field_2510);
    func_8009E97C(g_SysWork.field_2510);
}

s32 func_80089128() // 0x80089128
{
    s32             temp_s0;
    s32             temp_s1;
    s32             temp_v0;
    s32             var_s0;
    s_SysWork_2514* var_s2;
    s32             var_s3;
    s32             var_s5;
    s32             var_s6;

    var_s2 = &g_SysWork.field_2514;

    temp_s0 = g_SysWork.field_2510;

    if (!var_s2->field_2_0)
    {
        func_800890B8();
    }

    if (g_GameWork.config_0.optVibrationEnabled_21)
    {
        func_8009E2A0(var_s2);
        var_s2->field_1 = 1 << 7;
    }
    else
    {
        func_8009E2D8(var_s2);
        var_s2->field_1 = 0;
    }

    if (PadChkVsync())
    {
        func_8009E61C(var_s2, func_8009E550(var_s2, temp_s0), temp_s0);
    }

    var_s5 = 0;

    var_s2->field_C->field_4 = 0;
    var_s2->field_C->field_C = 0;

    temp_v0 = func_8009ED74(var_s2);
    var_s0  = func_8009ED7C(temp_v0);

    if (!var_s2->field_2_1)
    {
        var_s3 = g_VBlanks;
    }
    else
    {
        var_s3 = 0;
    }

    var_s6 = 0xFFFF;

    for (; var_s0 != temp_v0; var_s5++)
    {
        temp_s1 = func_8009ED7C(var_s0);

        if (func_80089644(var_s2, var_s0, var_s6 & 0xFFFF, var_s3) == 0)
        {
            func_8009EC1C(var_s2, var_s0);
        }

        var_s0 = temp_s1;
    }

    func_8009E718(var_s2);

    return var_s5;
}

void func_800892A4(s32 idx) // 0x800892A4
{
    func_800895E4(&g_SysWork.field_2514, &D_8002AC04[idx], 0x80);
}

void func_800892DC(s32 idx, u8 arg1) // 0x800892DC
{
    func_800895E4(&g_SysWork.field_2514, &D_8002AC04[idx], arg1);
}

void func_80089314(s32 arg0) // 0x80089314
{
    s32 var0;
    s32 var1;

    var0        = 24;
    D_800AFD05 += g_VBlanks;
    
    if (arg0 != 0)
    {
        var0 = 6;
    }
    
    if ((s32)D_800AFD05 >= var0)
    {
        var0 = func_80080514();
        if (arg0 != 0)
        {
            var1 = ((var0 * 16) >> 12) + 20;
        }
        else
        {
            var1 = ((var0 * 20) >> 12) + 60;
        }
        
        D_800AFD04 = (D_800AFD04 + var1) & 0x7F;
    }
    
    func_800892DC(0x15, D_800AFD04 + 32);
}

void func_800893D0(s32 arg0) // 0x800893D0
{
    u32 var;

    if (arg0 > FP_TO(25, Q12_SHIFT)) // 25 in Q19.12.
    {
        var = 200;
    }
    else if (arg0 < FP_TO(5, Q12_SHIFT)) // 5 in Q19.12.
    {
        var = 100;
    }
    else 
    {
        var = ((arg0 + FP_TO(15, Q12_SHIFT)) / FP_TO(5, Q12_SHIFT)) * 25; // 15 and 5 in Q19.12.
    }
    
    func_800892DC(10, var);
}

void func_8008944C() // 0x8008944C
{
    func_800892DC(19, 0xA0);
}

void func_80089470() // 0x80089470
{
    func_800892DC(19, 0xA0);
}

void func_80089494() // 0x80089494
{
    func_800892DC(9, 0xA0);
}

void func_800894B8(s32 arg0) // 0x800894B8
{
    func_800892DC(9, arg0);
}

void func_800894DC() // 0x800894DC
{
    func_800892DC(9, 0xE0);
}

void func_80089500() // 0x80089500
{
    func_800892DC(9, 0xA0);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089524); // 0x80089524

s32 func_800895E4(s_SysWork_2514* arg0, s_8002AC04* arg1, u8 arg2)
{
    u32 sp10;

    sp10 = arg2;

    if (arg1 == NULL)
    {
        return 0;
    }

    return D_800AFD08[arg1->field_4](arg0, 0, arg1, &sp10);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089644); // 0x80089644

// TODO: Rodata migration.
#ifdef NON_MATCHING
s32 func_8008973C(s_SysWork_2514* arg0, s32 arg1, s_8002AC04* ptr, u32* arg3)
{
    if (!arg0 || arg1)
    {
        return 0;
    }

    if (ptr == NULL || ptr->field_4 != 3)
    {
        return 0;
    }

    switch (ptr->field_5)
    {
        case 0:
            func_8009E2A0(arg0);
            break; 

        case 1:
            func_8009E2D8(arg0);
            break;

        case 2:
            func_8009E268(arg0);
            break;

        case 3:
            func_8009E230(arg0);
            break;

        case 4:
            func_80089840(arg0);
            break;

        case 5:
            func_8008989C(arg0, ptr->field_6, ptr->field_C);
            break;

        case 6:
            func_8008992C(arg0, ptr->field_6, ptr->field_C);
            break;

        case 7:
            func_800899BC(arg0, ptr->field_8);
            break;
    }

    return 1;
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008973C);
#endif

void func_80089840(s_func_80089840* arg0) // 0x80089840
{
    s32* temp_s0;
    s32* var_a1;
    s32* temp_s1;

    if (arg0 == NULL)
    {
        return;
    }

    var_a1  =  arg0->field_18;
    temp_s1 = &arg0->field_18;
    if (var_a1 != temp_s1)
    {
        do
        {
            temp_s0 = *var_a1;
            func_8009EC1C(arg0, var_a1);
            var_a1 = temp_s0;
        }
        while (var_a1 != temp_s1);
    }
}

void func_8008989C(s_SysWork_2514* arg0, u16 arg1, s32 (*arg2)(u16, s32)) // 0x8008989C
{
    s_func_8008989C* ptr0;
    s_func_8008989C* ptr1;
    s_func_8008989C* ptr2;

    if (arg0 != NULL)
    {
        ptr2 = arg0->field_18;
        ptr1 = (s_func_8008989C*)&arg0->field_18;

        while (ptr2 != ptr1)
        {
            ptr0 = ptr2->field_0;

            if (arg2(ptr2->field_1E, arg1) != 0)
            {
                func_8009EC1C(arg0, ptr2);
            }

            ptr2 = ptr0;
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008992C); // 0x8008992C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_800899BC); // 0x800899BC

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089A30); // 0x80089A30

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089BB8); // 0x80089BB8

s32 func_80089D0C(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u8* arg3) // 0x80089D0C
{
    if (arg0 == NULL || arg2 == NULL)
    {
        return 0;
    }

    if (arg2->field_4 == 4)
    {
        if (arg1 != NULL)
        {
            arg1->field_14_24 = arg2->field_5 & 0x7F;
            arg1->field_1E    = arg2->field_6;
            arg1->field_10    = arg2->field_0;
            arg1->field_14_31 = 1;
            arg1->field_18    = arg1->field_14_16 << 24;
            return 0;
        }
        else
        {
            arg1 = func_8009ECCC(arg0, arg2->field_C);
            if (arg1 != NULL)
            {
                arg1->field_10    = arg2;
                arg1->field_14_16 = *arg3;
                arg1->field_C     = arg2->field_8;
                return 1;
            }
        }
    }

    return 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089DF0); // 0x80089DF0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A058); // 0x8008A058

s32 func_8008A0CC()
{
    return 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A0D4); // 0x8008A0D4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A0E4); // 0x8008A0E4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A270); // 0x8008A270

// TODO: RODATA migration
#ifdef NON_MATCHING
u8 func_8008A2E0(s32 arg0)
{
    if (g_SysWork.field_275C > 0x100000)
    {
        switch (arg0)
        {
            case 5:
            case 25:
                return 0x12;

            case 15:
                return 15;

            case 2:
            case 12:
            case 22:
                return 13;

            default:
                break;
        }
    }

    return D_800AD4C8[arg0].field_F;
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A2E0); // 0x8008A2E0
#endif

s32 func_8008A35C(s_8008A35C* arg0, s32 arg1) // 0x8008A35C
{
    s32 var;
    s32 res;

    var = arg0->field_E + arg0->field_F;
    res = 0;
    if (arg1 >= arg0->field_E)
    {
        res = (arg1 < var);
    }

    return res;
}

void func_8008A384(s_SubCharacter* chara) // 0x8008A384
{
    chara->flags_3E &= ~CharaFlag_Unk8;
}

void func_8008A398(s_SubCharacter* chara) // 0x8008A398
{
    chara->flags_3E |= CharaFlag_Unk8;
}

void func_8008A3AC(s_SubCharacter* chara) // 0x8008A3AC
{
    if (!(chara->flags_3E & CharaFlag_Unk8))
    {
        chara->field_44 = 0;
        func_8008A3E0();
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A3E0); // 0x8008A3E0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B15C); // 0x8008B15C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B1DC); // 0x8008B1DC

void func_8008B398() // 0x8008B398
{
    func_8008B3E4(0);
    func_8008B438(0, 0, 0);
    func_8008B438(1, 0, 0);
    func_8008B40C(0, 0);
}

void func_8008B3E4(s32 arg0) // 0x8008B3E4
{
    func_8008B474(0, arg0, 0);
}

void func_8008B40C(s32 arg0, s32 arg1) // 0x8008B40C
{
    func_8008B474(3, arg0, arg1);
}

void func_8008B438(s32 arg0, s32 arg1, s32 arg2) // 0x8008B438
{
    s32 cond;

    cond = arg0 != 0;
    if (func_8008B474(2 - cond, arg1, arg2) != 0)
    {
        func_80089314(cond);
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B474); // 0x8008B474

// TODO: RODATA migration.
#ifdef NON_MATCHING
void func_8008B664(s32 arg0, u32 caseVar) // 0x8008B664
{
    s32 var;

    var = 0;
    switch (caseVar)
    {
        case 0:
        case 6:
        case 10:
        case 16:
        case 20:
        case 26:
            var = 0x511;
            break;

        case 1:
        case 4:
        case 7:
        case 11:
        case 14:
        case 17:
        case 21:
        case 24:
        case 27:
            var = 0x510;
            break;

        case 32:
        case 33:
        case 34:
            var = 0x506;
            break;

        case 2:
        case 5:
        case 15:
        case 25:
            if (g_SysWork.field_275C > 0x100000)
            {
                func_8008B3E4(0x80);
                break;
            }

        case 8:
        case 9:
            var = 0x524;
            break;

        case 35:
        default:
            break;
    }

    if (var != 0)
    {
        func_8005DC1C(var, arg0, 0xC0, 0);
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B664); // 0x8008B664
#endif

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B714); // 0x8008B714

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008BF84); // 0x8008BF84

void DmsHeader_FixOffsets(s_DmsHeader* header) // 0x8008C9A0
{
    s_DmsEntry* chara;

    if (header->isLoaded_0)
    {
        return;
    }

    header->isLoaded_0 = 1;

    // Add memory addr of DMS header to offsets in header.
    header->intervalPtr_8 = (u8*)header->intervalPtr_8 + (u32)header;
    header->characters_18 = (u8*)header->characters_18 + (u32)header;

    DmsEntry_FixOffsets(&header->camera_1C, header);

    for (chara = header->characters_18;
         chara < &header->characters_18[header->characterCount_1];
         chara++)
    {
        DmsEntry_FixOffsets(chara, header);
    }
}

void DmsEntry_FixOffsets(s_DmsEntry* entry, s_DmsHeader* header) // 0x8008CA44
{
    entry->keyframes_C.character = (u32)entry->keyframes_C.character + (u32)header;
    entry->svectorPtr_8 = (u32)entry->svectorPtr_8 + (u32)header;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CA60); // 0x8008CA60

void Dms_CharacterGetPosRot(VECTOR3* pos, SVECTOR* rot, char* charName, s32 time, s_DmsHeader* header) // 0x8008CA74
{
    s32 charIdx;

    charIdx = Dms_CharacterFindIndexByName(charName, header);
    if (charIdx == NO_VALUE)
    {
        // Character not found in DMS.
        Math_Vector3Zero(pos);
        Math_SVectorZero(rot);

        Gfx_DebugStringPosition(SCREEN_POSITION_X(15.75f), SCREEN_POSITION_Y(37.5f));

#ifdef DEBUG
        // Only seen in prototypes.
        Gfx_DebugStringDraw(charName);
        Gfx_DebugStringDraw(" doesn't exist in dms.");
#endif
    }
    else
    {
        Dms_CharacterGetPosRotByIndex(pos, rot, charIdx, time, header);
    }
}

s32 Dms_CharacterFindIndexByName(char* name, s_DmsHeader* header) // 0x8008CB10
{
    s32 i;

    for (i = 0; i < header->characterCount_1; i++)
    {
        if (!strncmp(name, header->characters_18[i].name_4, 4))
        {
            return i;
        }
    }

    return NO_VALUE;
}

void Dms_CharacterGetPosRotByIndex(VECTOR3* pos, SVECTOR3* rot, s32 charaIdx, s32 time, s_DmsHeader* header) // 0x8008CB90
{
    s_DmsEntry*             charaEntry;
    s32                     keyframePrev;
    s32                     keyframeNext;
    s32                     alpha;
    s_DmsKeyframeCharacter* keyframes;
    s_DmsKeyframeCharacter  curFrame;

    charaEntry = &header->characters_18[charaIdx];
    func_8008D1D0(&keyframePrev, &keyframeNext, &alpha, time, charaEntry, header);

    keyframes = charaEntry->keyframes_C.character;
    Dms_CharacterKeyframeInterpolate(&curFrame, &keyframes[keyframePrev], &keyframes[keyframeNext], alpha);

    pos->vx = FP_TO(curFrame.position_0.vx + header->origin_C.vx, Q4_SHIFT);
    pos->vy = FP_TO(curFrame.position_0.vy + header->origin_C.vy, Q4_SHIFT);
    pos->vz = FP_TO(curFrame.position_0.vz + header->origin_C.vz, Q4_SHIFT);
    rot->vx = curFrame.rotation_6.vx;
    rot->vy = curFrame.rotation_6.vy;
    rot->vz = curFrame.rotation_6.vz;
}

void Dms_CharacterKeyframeInterpolate(s_DmsKeyframeCharacter* result, s_DmsKeyframeCharacter* frame0, s_DmsKeyframeCharacter* frame1, s32 alpha) // 0x8008CC98
{
    // Low-precision lerp between positions?
    result->position_0.vx = frame0->position_0.vx + FP_MULTIPLY(frame1->position_0.vx - frame0->position_0.vx, (s64)alpha, Q12_SHIFT);
    result->position_0.vy = frame0->position_0.vy + FP_MULTIPLY(frame1->position_0.vy - frame0->position_0.vy, (s64)alpha, Q12_SHIFT);
    result->position_0.vz = frame0->position_0.vz + FP_MULTIPLY(frame1->position_0.vz - frame0->position_0.vz, (s64)alpha, Q12_SHIFT);

    // Higher-precision lerp between rotations?
    result->rotation_6.vx = Math_LerpFixed12(frame0->rotation_6.vx, frame1->rotation_6.vx, alpha);
    result->rotation_6.vy = Math_LerpFixed12(frame0->rotation_6.vy, frame1->rotation_6.vy, alpha);
    result->rotation_6.vz = Math_LerpFixed12(frame0->rotation_6.vz, frame1->rotation_6.vz, alpha);
}

s16 func_8008CDBC(s16 angle) // 0x8008CDBC
{
    return (96 * shRcos(angle / 2)) / shRsin(angle / 2);
}

s32 Dms_CameraGetTargetPos(VECTOR3* posTarget, VECTOR3* lookAtTarget, u16* arg2, s32 time, s_DmsHeader* header) // 0x8008CE1C
{
    s_DmsEntry*         camEntry;
    s32                 keyframePrev;
    s32                 keyframeNext;
    s32                 alpha;
    s_DmsKeyframeCamera curFrame;
    s32                 camProjValue;

    camEntry = &header->camera_1C;

    func_8008D1D0(&keyframePrev, &keyframeNext, &alpha, time, camEntry, header);
    camProjValue = Dms_CameraKeyframeInterpolate(&curFrame, &camEntry->keyframes_C.camera[keyframePrev], &camEntry->keyframes_C.camera[keyframeNext], alpha);

    posTarget->vx = FP_TO(curFrame.posTarget_0.vx + header->origin_C.vx, Q4_SHIFT);
    posTarget->vy = FP_TO(curFrame.posTarget_0.vy + header->origin_C.vy, Q4_SHIFT);
    posTarget->vz = FP_TO(curFrame.posTarget_0.vz + header->origin_C.vz, Q4_SHIFT);

    lookAtTarget->vx = FP_TO(curFrame.lookAtTarget_6.vx + header->origin_C.vx, Q4_SHIFT);
    lookAtTarget->vy = FP_TO(curFrame.lookAtTarget_6.vy + header->origin_C.vy, Q4_SHIFT);
    lookAtTarget->vz = FP_TO(curFrame.lookAtTarget_6.vz + header->origin_C.vz, Q4_SHIFT);

    if (arg2 != NULL)
    {
        *arg2 = curFrame.field_C[0];
    }

    // `camProjValue` comes from `curFrame.field_C[1]`, return value is passed to `vcChangeProjectionValue`.
    return camProjValue;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008CF54); // 0x8008CF54

s32 Dms_CameraKeyframeInterpolate(s_DmsKeyframeCamera* result, s_DmsKeyframeCamera* frame0, s_DmsKeyframeCamera* frame1, s32 alpha) // 0x8008CFEC
{
    result->posTarget_0.vx = frame0->posTarget_0.vx + FP_MULTIPLY(frame1->posTarget_0.vx - frame0->posTarget_0.vx, (s64)alpha, Q12_SHIFT);
    result->posTarget_0.vy = frame0->posTarget_0.vy + FP_MULTIPLY(frame1->posTarget_0.vy - frame0->posTarget_0.vy, (s64)alpha, Q12_SHIFT);
    result->posTarget_0.vz = frame0->posTarget_0.vz + FP_MULTIPLY(frame1->posTarget_0.vz - frame0->posTarget_0.vz, (s64)alpha, Q12_SHIFT);

    result->lookAtTarget_6.vx = frame0->lookAtTarget_6.vx + FP_MULTIPLY(frame1->lookAtTarget_6.vx - frame0->lookAtTarget_6.vx, (s64)alpha, Q12_SHIFT);
    result->lookAtTarget_6.vy = frame0->lookAtTarget_6.vy + FP_MULTIPLY(frame1->lookAtTarget_6.vy - frame0->lookAtTarget_6.vy, (s64)alpha, Q12_SHIFT);
    result->lookAtTarget_6.vz = frame0->lookAtTarget_6.vz + FP_MULTIPLY(frame1->lookAtTarget_6.vz - frame0->lookAtTarget_6.vz, (s64)alpha, Q12_SHIFT);

    result->field_C[0] = Math_LerpFixed12(frame0->field_C[0], frame1->field_C[0], alpha);
    result->field_C[1] = frame0->field_C[1] + FP_MULTIPLY(frame1->field_C[1] - frame0->field_C[1], (s64)alpha, Q12_SHIFT);

    return result->field_C[1];
}

void func_8008D1D0(s32* keyframePrev, s32* keyframeNext, s32* alpha, s32 time, s_DmsEntry* camEntry, s_DmsHeader* header) // 0x8008D1D0
{
    s32 prevVal;
    s32 nextVal;

    prevVal = 0;
    nextVal = 0;
    
    switch (func_8008D2C4(time, header))
    {
        case 0:
            prevVal = FP_FROM(time, Q12_SHIFT);
            nextVal = prevVal + 1;
            *alpha = time & 0xFFF;
            break;

        case 1:
            prevVal = FP_FROM(time, Q12_SHIFT);
            nextVal = prevVal;
            *alpha = 0;
            break;

        case 2:
            prevVal = FP_FROM(time, Q12_SHIFT) - 1;
            nextVal = prevVal + 1;
            *alpha = (time & 0xFFF) + 0x1000;
            break;

        default:
            break;
    }

    *keyframePrev = func_8008D330(prevVal, camEntry);
    *keyframeNext = func_8008D330(nextVal, camEntry);
}

// Dms_IntervalGetStatus?
u32 func_8008D2C4(s32 time, s_DmsHeader* header)
{
    s_DmsInterval* interval;

    time = FP_FROM(time, Q12_SHIFT);

    for (interval = header->intervalPtr_8;
         interval < &header->intervalPtr_8[header->intervalCount_2];
         interval++)
    {
        if (time != ((interval->start + interval->duration) - 1))
        {
            continue;
        }

        if (interval->duration > 1)
        {
            return 2;
        }

        return 1;
    }

    return 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D330); // 0x8008D330

s32 Math_LerpFixed12(s16 from, s16 to, s32 alpha) // 0x8008D3D4
{
    // TODO: Shifts are similar to `shAngleRegulate`, but that doesn't seem to work here.
    return ((s32)(FP_MULTIPLY((((to - from) << 20) >> 20), (s64)alpha, 12) + from) << 20) >> 20;
}

void func_8008D41C() // 0x8008D41C
{
    D_800C4818.field_0 = 0;
    D_800C4818.field_1 = 0;
    D_800C4818.field_2 = 0;
    D_800C4818.field_A = 0;
}

void func_8008D438() // 0x8008D438
{
    D_800C4818.field_0 = 1;
}

void func_8008D448() // 0x8008D448
{
    D_800C4818.field_0 = 0;
}

void func_8008D454() // 0x8008D454
{
    D_800C4818.field_1 = 1;
}

void func_8008D464() // 0x8008D464
{
    D_800C4818.field_1 = 0;
}

void func_8008D470(s16 arg0, SVECTOR* rot, VECTOR3* pos, s32 arg3) // 0x8008D470
{
    s_8008E51C* ptr;
    s32 var;

    if (D_800C4818.field_0 == 0)
    {
        func_800410D8(&D_800C4818.field_C, &D_800C4818.field_1C, &D_800C4818.field_20, rot, pos);

        if ((ReadGeomScreen() >> 1) < D_800C4818.field_C.vz)
        {
            D_800C4818.field_2 = 1;
            D_800C4818.field_8 = func_8008D8C0(arg0, D_800C4818.field_C.vz, D_800C4818.field_20);
            func_8008D5A0(&D_800C4818.field_C, D_800C4818.field_20);
        }
        else
        {
            return;
        }
    }

    if (D_800C4818.field_1 == 0)
    {
        ptr = func_8008E51C(FP_FROM(pos->vx, Q8_SHIFT), FP_FROM(pos->vz, Q8_SHIFT), arg3);
        if (ptr != NULL)
        {
            func_8008E5B4();

            if (ptr->field_0 == 1)
            {
                var = FP_TO(ptr->field_2, Q8_SHIFT);
                func_8008E794(pos, D_800C4818.field_20, var);
                func_8008EA68(rot, pos, var);
            }
        }
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D5A0); // 0x8008D5A0

void func_8008D78C()
{
    s32 var0;
    s32 var1;

    if (D_800C4818.field_2 == 0)
    {
        return;
    }

    D_800C4818.field_2 = 0;

    if (D_800C4818.field_0 != 0)
    {
        return;
    }

    var1 = func_8008D850();
    if (var1 != 0)
    {
        var0 = D_800C4818.field_8 - D_800C4818.field_A;
    }
    else
    {
        var0 = -D_800C4818.field_A;
    }

    D_800C4818.field_A += var0 >> 1;

    if (vcRetCamMvSmoothF() == 0)
    {
        D_800C4818.field_A = 0;
        var1 = 0;
    }

    func_8008D990(var1, D_800C4818.field_A, &D_800C4818.field_C, D_800C4818.field_1C, D_800C4818.field_20);
}

s32 func_8008D850() // 0x8008D850
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

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D8C0); // 0x8008D8C0

// Large function.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D990); // 0x8008D990

void func_8008E4EC(s32 arg) // 0x8008E4EC
{
    func_80056504(arg, &D_8002B2CC, &D_800AFD9C, 1);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E51C); // 0x8008E51C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E5B4); // 0x8008E5B4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E794); // 0x8008E794

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008EA68); // 0x8008EA68

void func_8008EF18() {}
