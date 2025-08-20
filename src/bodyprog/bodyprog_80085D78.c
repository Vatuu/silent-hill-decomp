#include "game.h"

#include <libpad.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math.h"
#include "main/fsqueue.h"

void func_80085D78(bool arg0) // 0x80085D78
{
    if (arg0)
    {
        g_SysWork.timer_2C = 0;
        g_SysWork.field_14 = 0;
        g_SysWork.field_10++;
        return;
    }

    SysWork_StateStepIncrement();
}

void func_80085DC0(bool arg0, s32 sysStateStep) // 0x80085DC0
{
    if (arg0)
    {
        g_SysWork.field_10 = sysStateStep;
        g_SysWork.timer_2C = 0;
        g_SysWork.field_14 = 0;
    }
    else
    {
        SysWork_NextStateStepSet(sysStateStep);
    }
}

void func_80085DF0() // 0x80085DF0
{
    g_SysWork.timer_2C += g_DeltaTime1;

    if (g_MapOverlayHeader.func_EC() != NULL || g_SysWork.timer_2C > 4096)
    {
        SysWork_StateStepIncrement();
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

void func_80085EB8(u32 arg0, s_SubCharacter* chara0, s_SubCharacter* chara1, bool arg3) // 0x80085EB8
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
                g_MapOverlayHeader.func_DC();
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

void func_8008605C(s32 arg0, s32 arg1, s32 arg2, bool arg3) // 0x8008605C
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

void func_800860B0(bool arg0, s32 mapMsgIdx, s32 arg2, s32 arg3, s32 sysStateStep, bool arg5) // 0x800860B0
{
    s32 var;

    var = Gfx_MapMsg_Draw(mapMsgIdx);
    if (var <= 0)
    {
        return;
    }
    
    if (!arg0)
    {
        func_80085D78(arg5);
        return;
    }

    if (var == 1)
    {
        func_80085DC0(arg5, arg2);
    }
    if (var == 2)
    {
        func_80085DC0(arg5, arg3);
    }
    if (var == 3)
    {
        func_80085DC0(arg5, sysStateStep);
    }
}

void func_8008616C(s32 arg0, bool arg1, s32 arg2, s32 arg3, bool arg4) // 0x8008616C
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
            // `arg2` determines what `arg3` is, which could be a time value or picked up item count?
            if (arg2 != 2)
            {
                D_800B5C30 = arg3;
            }

            if (arg1)
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

const RECT D_8002AB10 =  // 0x8002AB10 .rodata
{
    SCREEN_POSITION_X(100.0f), 256,
    (SCREEN_WIDTH / 5) * 3, SCREEN_HEIGHT
};

void func_800862F8(s32 arg0, s32 itemId, bool arg2) // 0x800862F8
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
            Fs_QueueStartReadTim(itemId, FS_BUFFER_1, &g_ItemInspectionImg);

            if (arg0 != 0)
            {
                g_SysWork.field_14++;
                
                if (Fs_QueueDoThingWhenEmpty())
                {
                    func_80085D78(arg2);
                }
            }
            break;

        case 1:
            if (Fs_QueueDoThingWhenEmpty())
            {
                func_80085D78(arg2);
            }
            break;

        case 2:
            func_80031AAC(&g_ItemInspectionImg);
            break;

        case 3:
            DrawSync(0);
            StoreImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(0);
            break;

        case 4:
            Fs_QueueStartReadTim(itemId, FS_BUFFER_1, &D_800A9A04);

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

void func_80086470(u32 switchVar, s32 itemId, s32 itemCount, bool arg3) // 0x80086470
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
            if (!Fs_QueueDoThingWhenEmpty())
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
                Inventory_AddSpecialItem(itemId, itemCount & 0xFF);
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

            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + D_800A99B4[idx], FS_BUFFER_2, &g_MapImg);
            Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + D_800A99CC[idx], FS_BUFFER_1, &g_MapMarkerAtlasImg);

            Gfx_Init(SCREEN_WIDTH, 1);
            GsSwapDispBuff();
            Fs_QueueWaitForEmpty();
            break;

        case 1:
            Gfx_BackgroundSpriteDraw(&g_MapImg);
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
    return (arg0 * Math_Sin(arg1 + ((arg2 * D_800C4710[idx]) / arg3))) >> 12;
}

void func_800869E4(s32 mapMsgIdx, u8* arg1, u16* arg2) // 0x800869E4
{
    s32 ret;

    g_SysWork.field_22A0 |= 1 << 5;

    ret = Gfx_MapMsg_Draw(mapMsgIdx);
    if (ret == 1)
    {
        SysWork_StateStepIncrement();
    }
    else if (ret == NO_VALUE)
    {
        Sd_EngineCmd(arg2[*arg1]);
        *arg1 += 1;
    }
}

void Camera_TranslationSet(VECTOR3* pos, s32 xPosOffset, s32 yPosOffset, s32 zPosOffset,
                           s32 xzAccel, s32 yAccel, s32 xzSpeedMax, s32 ySpeedMax, s32 warpCam) // 0x80086A94
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
    if (xzAccel == FP_METER(0.0f))
    {
        camTranslationParams.accel_xz = cam_mv_prm_user.accel_xz;
    }
    else
    {
        camTranslationParams.accel_xz = xzAccel;
    }

    // Set acceleration on Y axis.
    if (yAccel == FP_METER(0.0f))
    {
        camTranslationParams.accel_y = cam_mv_prm_user.accel_y;
    }
    else
    {
        camTranslationParams.accel_y = yAccel;
    }

    // Set max speed on XZ plane.
    if (xzSpeedMax == FP_METER(0.0f))
    {
        camTranslationParams.max_spd_xz = cam_mv_prm_user.max_spd_xz;
    }
    else
    {
        camTranslationParams.max_spd_xz = xzSpeedMax;
    }

    // Set max speed on Y axis.
    if (ySpeedMax == FP_METER(0.0f))
    {
        camTranslationParams.max_spd_y = cam_mv_prm_user.max_spd_y;
    }
    else
    {
        camTranslationParams.max_spd_y = ySpeedMax;
    }

    // Set camera position target.
    vcUserCamTarget(&posTarget, &camTranslationParams, warpCam);
}

void Camera_RotationSet(VECTOR3* lookAt, s32 xLookAtOffset, s32 yLookAtOffset, s32 zLookAtOffset,
                        s32 xAngularAccel, s32 yAngularAccel, s32 xAngularSpeedMax, s32 yAngularSpeedMax, bool warpLookAt) // 0x80086B70
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
    if (xAngularAccel == FP_ANGLE(0.0f))
    {
        camRotParams.ang_accel_x = deflt_watch_mv_prm.ang_accel_x;
    }
    else
    {
        camRotParams.ang_accel_x = xAngularAccel;
    }

    // Set angular acceleration on Y axis.
    if (yAngularAccel == FP_ANGLE(0.0f))
    {
        camRotParams.ang_accel_y = deflt_watch_mv_prm.ang_accel_y;
    }
    else
    {
        camRotParams.ang_accel_y = yAngularAccel;
    }

    // Set max angular speed on X axis.
    if (xAngularSpeedMax == FP_ANGLE(0.0f))
    {
        camRotParams.max_ang_spd_x = deflt_watch_mv_prm.max_ang_spd_x;
    }
    else
    {
        camRotParams.max_ang_spd_x = xAngularSpeedMax;
    }
    
    // Set max angular speed on Y axis.
    if (yAngularSpeedMax == FP_ANGLE(0.0f))
    {
        camRotParams.max_ang_spd_y = deflt_watch_mv_prm.max_ang_spd_y;
    }
    else
    {
        camRotParams.max_ang_spd_y = yAngularSpeedMax;
    }

    // Set camera flags and rotation target.
    vcWorkSetFlags(0, VC_VISIBLE_CHARA_F);
    vcUserWatchTarget(&lookAtTarget, &camRotParams, warpLookAt);
}

void func_80086C58(s_SubCharacter* chara0, s_SubCharacter* chara1) // 0x80086C58
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_80085EB8(0, chara0, chara1, 0);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;

        case 1:
            func_80085EB8(1, chara0, NULL, 1);
            break;

        default:
            SysWork_StateStepIncrement();
            break;
    }
}

void func_80086D04(s_SubCharacter* chara) // 0x80086D04
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_80085EB8(3, chara, NULL, 0);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;
            break;

        case 1:
            func_80085EB8(1, chara, NULL, 1);
            break;

        default:
            SysWork_StateStepIncrement();
            break;
    }
}

void func_80086DA8(s32 itemId, s32 arg1) // 0x80086DA8
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_8008616C(0, true, 0, arg1, false);
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, itemId, true);
            break;

        default:
            func_8008616C(1, true, 0, 0, false);
            break;
    }
}

void func_80086E50(s32 itemId, s32 arg1, s32 arg2) // 0x80086E50
{
    switch (g_SysWork.field_10)
    {
        case 0:
            func_8008616C(0, true, 0, arg1, false);
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, itemId, true);
            break;

        case 2:
            func_8008616C(1, true, 0, 0, true);
            break;

        default:
            func_800862F8(2, InventoryItemId_Unequipped, false);
            func_8008616C(2, false, 0, arg2, false);
    }
}

void func_80086F44(s32 arg0, s32 arg1) // 0x80086F44
{
    if (g_SysWork.field_10 == 0)
    {
        func_800862F8(2, InventoryItemId_Unequipped, false);
        func_8008616C(2, true, 0, arg1, true);
        return;
    }

    func_8008616C(0, false, 0, arg0, false);
    SysWork_StateStepIncrement();
}

void func_80086FE8(s32 mapMsgIdx, s32 sfx, VECTOR3* pos) // 0x80086FE8
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
            func_8005DC1C(sfx, pos, 0x80, 0);
            
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_80085E6C(0x333, 1);
            break;
        
        case 2:
            func_800860B0(false, mapMsgIdx, 0, 0, 0, true);
            break;

        default:
            g_MapOverlayHeader.func_CC(0);

            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_8008716C(s32 itemId, s32 arg1, s32 arg2) // 0x8008716C
{
    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_8008616C(0, true, 0, arg1, false);
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, itemId, true);
            break;

        case 2:
            func_8008616C(1, true, 0, 0, true);
            break;

        case 3:
            func_800862F8(2, InventoryItemId_Unequipped, false);
            func_8008616C(2, false, 0, arg2, true);
            break;

        case 4:
            func_800862F8(2, InventoryItemId_Unequipped, false);

            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.field_10++;
            }
            break;

        case 5:
            func_800862F8(2, InventoryItemId_Unequipped, false);
            func_8008616C(2, true, 0, arg2, true);
            break;

        default:
            func_8008616C(0, false, 0, arg1, false);
            g_MapOverlayHeader.func_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_80087360(s32 itemId, s32 arg1, s32 arg2, s32 mapMsgIdx) // 0x80087360
{
    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_8008616C(0, true, 0, arg1, false);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, itemId, true);
            break;

        case 2:
            func_8008616C(1, true, 0, 0, true);
            break;

        case 3:
            func_800862F8(2, InventoryItemId_Unequipped, false);
            func_8008616C(2, false, 0, arg2, true);
            break;

        case 4:
            func_800862F8(2, InventoryItemId_Unequipped, false);
            func_800860B0(false, mapMsgIdx, 0, 0, 0, true);
            break;
        
        case 5:
            func_800862F8(2, InventoryItemId_Unequipped, false);
            func_8008616C(2, true, 0, arg2, true);
            break;

        default:
            func_8008616C(0, false, 0, arg1, false);
            g_MapOverlayHeader.func_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_80087540(s32 itemId, s32 itemCount, s32 arg2, s32 mapMsgIdx0, s32 mapMsgIdx1) // 0x80087540
{
    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_8008616C(0, true, 0, itemCount, false);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_800862F8(7, itemId, true);
            break;

        case 2:
            func_8008616C(1, true, 0, 0, true);
            break;

        case 3:
            func_800862F8(2, InventoryItemId_Unequipped, false);
            func_8008616C(2, false, 0, arg2, true);
            break;

        case 4:
            func_800862F8(2, InventoryItemId_Unequipped, false);
            
            if (mapMsgIdx0 != MapMsgCode_None)
            {
                func_800860B0(false, mapMsgIdx0, 0, 0, 0, true);
                break;
            }

            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                g_SysWork.timer_2C = 0;
                g_SysWork.field_14 = 0;
                g_SysWork.field_10++;
            }
            break;

        case 5:
            D_800A8E58 = 0x30;
            func_800862F8(2, InventoryItemId_Unequipped, false);

            func_800860B0(false, mapMsgIdx1, 0, 0, 0, true);
            break;

        case 6:
            D_800A8E58 = 0x30;

            func_800862F8(2, InventoryItemId_Unequipped, false);
            func_8008616C(2, true, 0, arg2, true);
            break;

        default:
            func_8008616C(0, false, 0, itemCount, false);
            g_MapOverlayHeader.func_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_ItemTake(s32 itemId, s32 itemCount, s32 globalPickupId, s32 mapMsgIdx) // 0x800877B8
{
    s32 i            = itemId;
    s32 mapMsgIdxCpy = mapMsgIdx;

    if (!(g_SysWork.flags_22A4 & (1 << 5)))
    {
        // Traverse NPCs.
        for (i = 0; i < NPC_COUNT_MAX; i++)
        {
            if (!(g_SysWork.npcs_1A0[i].model_0.charaId_0 >= Chara_Hero &&
                  g_SysWork.npcs_1A0[i].model_0.charaId_0 <= Chara_MonsterCybil) ||
                g_SysWork.npcs_1A0[i].health_B0 <= Q19_12(0.0f))
            {
                continue;
            }

            break;
        }
        
        if (i != NPC_COUNT_MAX)
        {
            g_DeltaTime0 = FP_TIME(0.0f);
        }
    }

    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            func_80086470(0, itemId, 0, false);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_80086470(1, itemId, 0, true);
            break;

        case 2: // "Yes" entry selected?
            if (func_80054AD8(itemId))
            {
                func_800860B0(true, mapMsgIdxCpy, 3, NO_VALUE, 0, true);
            }

            // Flag pickup item as collected.
            g_SavegamePtr->eventFlags_168[globalPickupId >> 5] |= 1 << (globalPickupId & 0x1F);
            break;

        case 3:
            func_80086470(3, itemId, itemCount, false);
            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        default: // "No" entry selected?
            // Flag pickup item as uncollected.
            if (g_SysWork.field_10 == NO_VALUE)
            {
                g_SavegamePtr->eventFlags_168[globalPickupId >> 5] &= ~(1 << (globalPickupId & 0x1F));
            }

            g_MapOverlayHeader.func_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_CommonItemTake(u32 pickupType, s32 globalPickupId) // 0x800879FC
{
    #define EASY_DIFFICULTY_AMMO_COUNT_MULT_MIN 2
    #define HANDGUN_AMMO_COUNT_BASE             15
    #define SHOTGUN_AMMO_COUNT_BASE             6
    #define RIFLE_AMMO_COUNT_BASE               6

    s32 ammoCountMult;

    // Compute ammo count multiplier.
    ammoCountMult = g_GameWork.config_0.optExtraBulletAdjust_2D + 1;
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        ammoCountMult = CLAMP(ammoCountMult, EASY_DIFFICULTY_AMMO_COUNT_MULT_MIN, ammoCountMult);
    }

    // Handle item pickup.
    switch (pickupType)
    {
        case CommonPickupItemId_FirstAidKit:
            Event_ItemTake(InventoryItemId_FirstAidKit, 1, globalPickupId, 5);
            break;

        case CommonPickupItemId_HealthDrink:
            Event_ItemTake(InventoryItemId_HealthDrink, 1, globalPickupId, 6);
            break;

        case CommonPickupItemId_Ampoule:
            Event_ItemTake(InventoryItemId_Ampoule, 1, globalPickupId, 7);
            break;

        case CommonPickupItemId_HandgunBullets:
            Event_ItemTake(InventoryItemId_HandgunBullets, ammoCountMult * HANDGUN_AMMO_COUNT_BASE, globalPickupId, 8);
            break;

        case CommonPickupItemId_ShotgunShells:
            Event_ItemTake(InventoryItemId_ShotgunShells, ammoCountMult * SHOTGUN_AMMO_COUNT_BASE, globalPickupId, 10);
            break;

        case CommonPickupItemId_RifleShells:
            Event_ItemTake(InventoryItemId_RifleShells, ammoCountMult * RIFLE_AMMO_COUNT_BASE, globalPickupId, 9);
            break;
    }
}

void func_80087AF4(s32 mapFlagIdx, s32 eventFlagIdx, s32 mapMsgIdx) // 0x80087AF4
{
    static const RECT D_8002ABA4 =
    {
        SCREEN_POSITION_X(100.0f), 256,
        SCREEN_WIDTH / 2, SCREEN_HEIGHT
    };

    s32 mapFlagIdxCpy;

    g_DeltaTime0  = FP_TIME(0.0f);
    mapFlagIdxCpy = mapFlagIdx;

    switch (g_SysWork.field_10)
    {
        case 0:
            g_MapOverlayHeader.func_C8();
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B4[mapFlagIdx]);

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 1:
            func_8008616C(2, true, 0, 0, true);
            break;

        case 2:
            DrawSync(0);
            StoreImage(&D_8002ABA4, IMAGE_BUFFER);
            DrawSync(0);
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + D_800A99B4[mapFlagIdx], FS_BUFFER_2, &g_MapImg);
            Gfx_Init(0x140, 1);

            g_IntervalVBlanks = 1;

            GsSwapDispBuff();
            func_8008616C(0, false, 0, 0, false);
            Fs_QueueWaitForEmpty();

            g_SysWork.timer_2C = 0;
            g_SysWork.field_14 = 0;
            g_SysWork.field_10++;

        case 3:
            D_800A8E58 = 0x58;

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            func_800860B0(true, mapMsgIdx, 4, 5, 0, true);
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

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            func_8008616C(2, true, 0, 0, true);
            break;

        default:
            LoadImage(&D_8002ABA4, IMAGE_BUFFER);
            DrawSync(0);
            Gfx_Init(0x140, 0);
            func_8008616C(0, false, 0, 0, false);
            g_MapOverlayHeader.func_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_80087EA8(s32 cmd) // 0x80087EA8
{
    if (!func_800358A8(cmd))
    {
        return;
    }

    func_800358DC(cmd);
}

void func_80087EDC(s32 arg0) // 0x80087EDC
{
    if (func_80045B28() || !Fs_QueueDoThingWhenEmpty())
    {
        return;
    }
    
    switch (g_SysWork.field_10)
    {
        case 0:
            if (!func_800358A8(arg0))
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
                Sd_EngineCmd(22);
            }
            else
            {
                Sd_EngineCmd(23);
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

bool Chara_Load(s32 arg0, s8 charaId, GsCOORDINATE2* coord, s8 arg3, s_PlmHeader* plmHeader, s_FsImageDesc* texture) // 0x80088C7C
{
    func_80035338(arg0 + 1, charaId, NULL, coord);
    func_8003D5B4(arg3);
    func_8003D6E0(charaId, arg0, plmHeader, texture);
    return true;
}

bool func_80088D0C() // 0x80088D0C
{
    Fs_QueueWaitForEmpty();
    func_8003D95C();
    return true;
}

void func_80088D34(s32 idx) // 0x80088D34
{
    idx++;
    func_800445A4(D_800A992C[idx].animFile1_8, D_800A992C[idx].npcCoords_14);
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

void func_80088FF4(s32 groupIdx, s32 spawnIdx, s32 spawnFlags) // 0x80088FF4
{
    s_SpawnInfo* spawn;

    spawn          = &g_MapOverlayHeader.charaSpawns_24C[D_800A98FC[groupIdx] - 1][spawnIdx];
    spawn->flags_6 = spawnFlags;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089034); // 0x80089034

void func_80089090(s32 arg0) // 0x80089090
{
    func_80089524(&g_SysWork.field_2514, arg0);
}

void func_800890B8() // 0x800890B8
{
    func_8009E198(&g_SysWork.field_2514, 0);
    func_8009E310(&g_SysWork.field_2514, g_SysWork.field_2514.head_18.unk_8, 2);
    func_8009EBB8(&g_SysWork.field_2514, g_SysWork.field_2514.head_18.unk_18, 16);

    g_SysWork.field_2510 = func_8009E4F8();

    func_8009E7D8(g_SysWork.field_2510);
    func_8009E97C(g_SysWork.field_2510);
}

s32 func_80089128() // 0x80089128
{
    s32              temp_s0;
    s32              var_s3;
    s32              var_s5;
    s32              var_s6;
    s_func_8009ECCC* temp_v0;
    s_func_8009ECCC* var_s0;
    s_func_8009ECCC* temp_s1;
    s_SysWork_2514*  var_s2;
    
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

        if (!func_80089644(var_s2, var_s0, var_s6 & 0xFFFF, var_s3))
        {
            func_8009EC1C(var_s2, var_s0);
        }

        var_s0 = temp_s1;
    }

    func_8009E718(var_s2);

    return var_s5;
}

// Forward declare pointers used below.
extern const u32 D_8002AF04[];
extern const u32 D_8002AF08[];
extern const u32 D_8002AF20[];
extern const u32 D_8002AF24[];
extern const u32 D_8002AF28[];
extern const u32 D_8002AF2C[];
extern const u32 D_8002AF34[];
extern const u32 D_8002AF3C[];
extern const u32 D_8002AF48[];
extern const u32 D_8002AF54[];
extern const u32 D_8002AF5C[];
extern const u32 D_8002AF64[];
extern const u32 D_8002AF70[];

const s_8002AC04 D_8002AC04[] =
{
    // 2nd field is used as index into `D_800AFD08` funcptr array.
    // Seems each function takes different kind of params in 5th/6th fields:
    // #0 5th field is some kind of index/counter.
    // #1 5th field is pointer to another `D_8002AC04` entry.
    // #2 5th field points to some data that comes after this array.
    // #3 5th field is always 0.
    // #4 5th field is index/counter.
    { NULL, 3, 2, 0, 0, {} },
    { NULL, 3, 3, 0, 0, {} },
    { NULL, 3, 1, 0, 0, {} },
    { NULL, 3, 0, 0, 0, {} },
    { NULL, 3, 4, 0, 0, {} },
    { &D_8002AC04[22], 0, 0, 0, 5, {} },
    { &D_8002AC04[25], 0, 32, 0, 6, {} },
    { &D_8002AC04[26], 0, 32, 0, 7, {} },
    { &D_8002AC04[27], 0, 32, 0, 8, {} },
    { &D_8002AC04[23], 0, 32, 0, 9, {} },
    { &D_8002AC04[24], 0, 32, 0, 10, {} },
    { &D_8002AC04[5], 1, 0, 0, &D_8002AC04[6], {} },
    { &D_8002AC04[31], 0, 32, 0, 12, {} },
    { &D_8002AC04[34], 0, 32, 0, 12, {} },
    { &D_8002AC04[37], 0, 32, 0, 12, {} },
    { &D_8002AC04[40], 0, 32, 0, 12, {} },
    { &D_8002AC04[43], 0, 32, 0, 12, {} },
    { &D_8002AC04[46], 0, 32, 0, 12, {} },
    { &D_8002AC04[28], 0, 32, 0, 18, {} },
    { &D_8002AC04[29], 0, 32, 0, 19, {} },
    { NULL, 4, 0, 0xFFFF, 20, { .u32 = -255 } },
    { NULL, 4, 1, 0xFFFF, 21, { .u32 = -255 } },
    { NULL, 2, 1, 0xFFFF, &D_8002AF70, { 0x2D, 9, 1, 0 } },
    { NULL, 2, 1, 0xFFFF, &D_8002AF64, { 0x180, 0x30, 1, 0 } },
    { NULL, 2, 1, 0xFFFF, &D_8002AF5C, { 0x90, 0x18, 1, 0 } },
    { NULL, 2, 1, 0xFFFF, &D_8002AF54, { 0x5A, 0xF, 1, 0 } },
    { NULL, 2, 1, 0xFFFF, &D_8002AF48, { 0x96, 0xF, 1, 1 } },
    { NULL, 2, 1, 0xFFFF, &D_8002AF3C, { 0x60, 0xC, 1, 0 } },
    { NULL, 2, 1, 0xFFFF, &D_8002AF3C, { 0x60, 0xC, 1, 0 } },
    { NULL, 2, 1, 0xFFFF, &D_8002AF34, { 0x4B, 0xF, 1, 0 } },
    { NULL, 0, 0, 0x0000, 0, {} },
    { NULL, 2, 0, 0xFFFF, &D_8002AF2C, { 0x258, 0xF, 0, 0 } },
    { NULL, 0, 0, 0x0000, 0, {} },
    { NULL, 0, 0, 0x0000, 0, {} },
    { NULL, 2, 0, 0xFFFF, &D_8002AF28, { 0x1E0, 0xF, 0, 0 } },
    { NULL, 0, 0, 0x0000, 0, {} },
    { NULL, 0, 0, 0x0000, 0, {} },
    { NULL, 2, 0, 0xFFFF, &D_8002AF24, { 0x1A4, 0xF, 0, 0 } },
    { NULL, 0, 0, 0x0000, 0, {} },
    { NULL, 0, 0, 0x0000, 0, {} },
    { NULL, 2, 0, 0xFFFF, &D_8002AF20, { 0x168, 0xF, 0, 0 } },
    { NULL, 0, 0, 0x0000, 0, {} },
    { NULL, 0, 0, 0x0000, 0, {} },
    { NULL, 2, 0, 0xFFFF, &D_8002AF20, { 0x10E, 0xF, 0, 0 } },
    { NULL, 0, 0, 0x0000, 0, {} },
    { NULL, 0, 0, 0x0000, 0, {} },
    { &D_8002AC04[47], 2, 0, 0xFFFF, &D_8002AF08, { 0xB40, 0xF, 0, 0 } },
    { &D_8002AC04[47], 2, 0, 0xFFFF, &D_8002AF04, { 0x1E, 0xF, 0, 0 } },
};

// TODO: Figure out what kind of data this is. The array above has some entries pointing to it, all of them using funcptr #2 (`func_80089DF0`).
// Not sure why they'd all be different sizes though.
const u32 D_8002AF04[] = { 0 };
const u32 D_8002AF08[] = { 0x8000184, 0x61000003, 0x81000000, 1, 0x181, 0x10000 };
const u32 D_8002AF20[] = { 0x184 };
const u32 D_8002AF24[] = { 0x308 };
const u32 D_8002AF28[] = { 0x610 };
const u32 D_8002AF2C[] = { 0xC010, 0 };
const u32 D_8002AF34[] = { 0x80008080, 0x80 };
const u32 D_8002AF3C[] = { 0xFFFFFF, 0xFFFFFF00, 0 };
const u32 D_8002AF48[] = { 0x468CA0A0, 0x1E28323C, 0xA14};
const u32 D_8002AF54[] = { 0xAFC8C8C8, 0x4B96};
const u32 D_8002AF5C[] = { 0x309060C0, 0xC048A8 };
const u32 D_8002AF64[] = { 0x143C2850, 0xA321E46, 0x50};
const u32 D_8002AF70[] = { 0xC4E0E0A8, 0x54A8, 0};

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

void func_800893D0(q19_12 arg0) // 0x800893D0
{
    u32 var;

    if (arg0 > FP_TO(25, Q12_SHIFT))
    {
        var = 200;
    }
    else if (arg0 < FP_TO(5, Q12_SHIFT))
    {
        var = 100;
    }
    else 
    {
        var = ((arg0 + FP_TO(15, Q12_SHIFT)) / FP_TO(5, Q12_SHIFT)) * 25;
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

s32 func_800895E4(s_SysWork_2514* arg0, s_8002AC04* arg1, u8 arg2) // 0x800895E4
{
    u32 sp10;

    sp10 = arg2;

    if (arg1 == NULL)
    {
        return 0;
    }

    return D_800AFD08[arg1->field_4](arg0, 0, arg1, &sp10);
}

bool func_80089644(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s32 arg2, u32 arg3) // 0x80089644
{
    u32                var1;
    s_func_80089644_1* ptr0;
    s_8002AC04*        ptr1;

    arg3             *= 5;
    arg1->field_18    = 0;
    arg1->field_14_31 = 0;
    while (true)
    {
        ptr1 = arg1->field_10;
        if (!ptr1)
        {
            break;
        }

        if (D_800AFD08[ptr1->field_4](arg0, arg1, ptr1, &arg3) == 0)
        {
            break;
        }
    }

    if (arg1->field_14_31 && (arg2 & arg1->field_1E))
    {
        var1 = arg1->field_18;
        ptr0 = &arg0->field_C->field_0[arg1->field_14_24 << 3];
        if (ptr0->field_4 < var1)
        {
            ptr0->field_4 = var1;
        }
    }

    return arg1->field_10 != NULL;
}

bool func_8008973C(s_SysWork_2514* arg0, s32 arg1, s_8002AC04* ptr, u32* arg3)
{
    if (!arg0 || arg1)
    {
        return false;
    }

    if (ptr == NULL || ptr->field_4 != 3)
    {
        return false;
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
            func_8008989C(arg0, ptr->field_6, ptr->field_C.u32);
            break;

        case 6:
            func_8008992C(arg0, ptr->field_6, ptr->field_C.u32);
            break;

        case 7:
            func_800899BC(arg0, ptr->field_8);
            break;
    }

    return true;
}

void func_80089840(s_SysWork_2514* arg0) // 0x80089840
{
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* curr;
    s_SysWork_2514_18* head;

    if (arg0 == NULL)
    {
        return;
    }

    curr = arg0->head_18.next_0;
    head = &arg0->head_18;

    while (curr != head)
    {
        next = curr->next_0;
        func_8009EC1C(arg0, curr);
        curr = next;
    }
}

void func_8008989C(s_SysWork_2514* arg0, u16 arg1, s32 (*arg2)(u16, s32)) // 0x8008989C
{
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* head;
    s_SysWork_2514_18* curr;

    if (arg0 == NULL)
    {
        return;
    }

    curr = arg0->head_18.next_0;
    head = &arg0->head_18;

    while (curr != head)
    {
        next = curr->next_0;

        if (arg2(curr->field_1E, arg1) != 0)
        {
            func_8009EC1C(arg0, curr);
        }

        curr = next;
    }
}

void func_8008992C(s_SysWork_2514* arg0, u16 arg1, s32 (*arg2)(u16, s32)) // 0x8008992C
{
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* head;
    s_SysWork_2514_18* curr;

    if (arg0 == NULL)
    {
        return;
    }

    curr = arg0->head_18.next_0;
    head = &arg0->head_18;

    while (curr != head)
    {
        next = curr->next_0;

        if (arg2(curr->field_1C, arg1) != 0)
        {
            func_8009EC1C(arg0, curr);
        }

        curr = next;
    }
}   

void func_800899BC(s_SysWork_2514* arg0, s32 arg1) // 0x800899BC
{
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* head;
    s_SysWork_2514_18* curr;

    if (arg0 == NULL)
    {
        return;
    }

    curr = arg0->head_18.next_0;
    head = &arg0->head_18;

    while (curr != head)
    {
        next = curr->next_0;

        if (curr->field_C == arg1)
        {
            func_8009EC1C(arg0, curr);
        }

        curr = next;
    }
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089A30); // 0x80089A30

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089BB8); // 0x80089BB8

bool func_80089D0C(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u8* arg3) // 0x80089D0C
{
    if (arg0 == NULL || arg2 == NULL)
    {
        return false;
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
            return false;
        }
        else
        {
            arg1 = func_8009ECCC(arg0, arg2->field_C);
            if (arg1 != NULL)
            {
                arg1->field_10    = arg2;
                arg1->field_14_16 = *arg3;
                arg1->field_C     = arg2->field_8;
                return true;
            }
        }
    }

    return false;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089DF0); // 0x80089DF0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A058); // 0x8008A058

s32 func_8008A0CC() // 0x8008A0CC
{
    return 0;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A0D4); // 0x8008A0D4

s32 func_8008A0E4(s32 arg0, s16 arg1, s_SubCharacter* chara, s_PlayerCombat* combat, s32 arg4, s16 arg5, s16 arg6) // 0x8008A0E4
{
    s32          var_t1;
    s32          temp_a1;
    s32          var_a0;
    s32          ret;
    s32          var_v0_2;
    s32          count;
    s_AnimInfo*  anim0;
    s_AnimInfo*  anim1;
    s_ModelAnim* modelAnim;

    var_t1    = chara->field_44;
    modelAnim = &chara->model_0.anim_4;

    if (g_DeltaTime0 == 0 || g_SysWork.sysState_8 != SysState_Gameplay)
    {
        return NO_VALUE;
    }

    if (chara == &g_SysWork.player_4C.chara_0)
    {
        anim1                       = D_800297B8;
        anim0                       = g_MapOverlayHeader.animInfo_34;
        modelAnim->animInfo_C       = anim1;
        modelAnim->maybeSomeState_1 = 76;
        modelAnim->animInfo_10      = anim0;
        modelAnim                   = &g_SysWork.player_4C.extra_128.model_0.anim_4;
        modelAnim->animInfo_C       = anim1;
        modelAnim->animInfo_10      = anim0;
        modelAnim->maybeSomeState_1 = 76;
    }

    if (arg0 <= 0)
    {
        var_t1          = 0;
        chara->field_44 = 0;
    }

    chara->field_46 = arg1;
    if (!(modelAnim->animIdx_0 & (1 << 0)))
    {
        chara->field_44 = 0;
        chara->field_4C = 0;
    }
    else if (!var_t1 && arg0 > 0)
    {
        chara->field_44 = 1;
        chara->field_4C = 0;
    }

    chara->field_47 = 100;
    chara->field_50 = arg5;
    chara->field_52 = arg6;
    chara->field_5C = combat->field_0;
    temp_a1         = func_8008A3E0(chara);
    ret             = NO_VALUE;

    if (chara == &g_SysWork.player_4C.chara_0)
    {
        count    = 6;
        var_v0_2 = 1;
    }
    else
    {
        count    = 1;
        var_v0_2 = NO_VALUE;
    }

    if (temp_a1 != 0)
    {
        var_a0 = var_v0_2;
        if (count > 0)
        {
            while (count > 0)
            {
                if (temp_a1 & var_a0)
                {
                    ret = count;
                    break;
                }

                var_a0 *= 2; // Or `<<= 1`.
                count--;
            }
        }
    }

    if (chara->model_0.charaId_0 != Chara_Hero)
    {
        if (g_SysWork.player_4C.chara_0.field_41 != NO_VALUE)
        {
            ret = 0;
        }
        else
        {
            ret = NO_VALUE;
        }
    }

    return ret;
}

const s32 g_rodataPad_8002AF9C[2] = { 0, 0 }; // TODO: Might indicate split nearby?

u8 func_8008A270(s32 idx) // 0x8008A270
{
    switch (idx)
    {
        case 2:
        case 5:
        case 12:
        case 15:
        case 22:
        case 25:
            if (g_SysWork.field_275C > 0x100000)
            {
                return 0;
            }
            break;

        default:
            break;
    }

    return D_800AD4C8[idx].field_E;
}

u8 func_8008A2E0(s32 arg0)
{
    if (g_SysWork.field_275C > 0x100000)
    {
        switch (arg0)
        {
            case 5:
            case 25:
                return 18;

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

s32 func_8008A35C(s_800AD4C8* arg0, s32 arg1) // 0x8008A35C
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

void func_8008B15C(s_SubCharacter* chara) // 0x8008B15C
{
    s32 temp_s2;
    s32 temp_s3;
    s32 i;

    temp_s3 = chara->field_50;
    temp_s2 = chara->field_52;

    chara->field_54 = temp_s3; 
    chara->field_56 = temp_s2;

    for (i = 1; i > 0; i--)
    {
        func_8008B1DC(chara, temp_s3, temp_s2); 
        chara->field_80 = chara->field_5C;
    }
}

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
void func_8008B664(VECTOR3* pos, u32 caseVar) // 0x8008B664
{
    s32 sfx;

    sfx = 0;
    switch (caseVar)
    {
        case 0:
        case 6:
        case 10:
        case 16:
        case 20:
        case 26:
            sfx = 0x511;
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
            sfx = 0x510;
            break;

        case 32:
        case 33:
        case 34:
            sfx = 0x506;
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
            sfx = 0x524;
            break;

        case 35:
        default:
            break;
    }

    if (sfx != 0)
    {
        func_8005DC1C(sfx, pos, 0xC0, 0);
    }
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B664); // 0x8008B664
#endif

/** This does something the color of the Hyper Blaster beam. Calls
 * `Game_HyperBlasterBeamColorGet`, which returns the color the player is currently using.
 */
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B714); // 0x8008B714

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008BF84); // 0x8008BF84

void DmsHeader_FixOffsets(s_DmsHeader* header) // 0x8008C9A0
{
    s_DmsEntry* chara;

    if (header->isLoaded_0)
    {
        return;
    }

    header->isLoaded_0 = true;

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
    entry->svectorPtr_8          = (u32)entry->svectorPtr_8 + (u32)header;
}

s_DmsInterval* func_8008CA60(volatile s32 unused, s32 idx, s_DmsHeader* header) // 0x8008CA60
{
    return &header->intervalPtr_8[idx];
}

void Dms_CharacterGetPosRot(VECTOR3* pos, SVECTOR3* rot, char* charaName, s32 time, s_DmsHeader* header) // 0x8008CA74
{
    s32 charaIdx;

    charaIdx = Dms_CharacterFindIdxByName(charaName, header);
    if (charaIdx == NO_VALUE)
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
        Dms_CharacterGetPosRotByIdx(pos, rot, charaIdx, time, header);
    }
}

s32 Dms_CharacterFindIdxByName(char* name, s_DmsHeader* header) // 0x8008CB10
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

void Dms_CharacterGetPosRotByIdx(VECTOR3* pos, SVECTOR3* rot, s32 charaIdx, s32 time, s_DmsHeader* header) // 0x8008CB90
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
    return (96 * Math_Cos(angle / 2)) / Math_Sin(angle / 2);
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

s32 func_8008D330(s32 arg0, s_DmsEntry* camEntry) // 0x8008D330
{
    SVECTOR3* vec;
    s32       t0;
    s32       retval;

    t0  = arg0;
    vec = camEntry->svectorPtr_8;

    for (; vec < &camEntry->svectorPtr_8[camEntry->svectorCount_2]; vec++)
    {

        if (arg0 < vec->vx)
        {
            break;
        }

        if (arg0 <= vec->vy)
        {
            t0 = vec->vz;
            break;
        }

        t0 -= vec->vy - vec->vx;
    }

    if (t0 >= 0)
    {
        if ((camEntry->keyframeCount_0 - 1) >= t0)
        {
            retval = t0;
        }
        else
        {
            retval = camEntry->keyframeCount_0 - 1;
        }
    }
    else
    {
        retval = 0;
    }

    return retval;
}

s32 Math_LerpFixed12(s16 from, s16 to, s32 alpha) // 0x8008D3D4
{
    return FP_ANGLE_NORM_S((s32)(FP_MULTIPLY_PRECISE(FP_ANGLE_NORM_S(to - from), alpha, Q12_SHIFT)) + from);
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
    s32         var;
    s_8008E51C* ptr;

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
        var1               = 0;
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

s32 func_8008D8C0(s16 x0, s32 x1, s32 x2) // 0x8008D8C0
{
    s32 temp0;
    s32 temp1;
    s32 res;

    temp0 = vwOresenHokan(&D_800AFD3C, 2, x0, 0, FP_FLOAT_TO(16.0f, Q8_SHIFT));
    temp1 = vwOresenHokan(&D_800AFD44, 7, x1, FP_FLOAT_TO(0.8f, Q8_SHIFT), FP_FLOAT_TO(13.0f, Q8_SHIFT));
    res   = FP_MULTIPLY(vwOresenHokan(&D_800AFD60, 7, x2, FP_FLOAT_TO(3.335f, Q8_SHIFT), FP_FLOAT_TO(7.425f, Q8_SHIFT)), // Yucky floats, maybe these aren't distances?
                        FP_MULTIPLY(temp0, temp1, Q12_SHIFT),
                        Q12_SHIFT);

    return (res > FP_FLOAT_TO(24.0f, Q8_SHIFT)) ? FP_FLOAT_TO(24.0f, Q8_SHIFT) : res;
}

// Large function.
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D990); // 0x8008D990

void func_8008E4EC(s_PlmHeader* plmHeader) // 0x8008E4EC
{
    func_80056504(plmHeader, D_8002B2CC.str, &D_800AFD9C, 1);
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E51C); // 0x8008E51C

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E5B4); // 0x8008E5B4

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008E794); // 0x8008E794

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008EA68); // 0x8008EA68

void func_8008EF18() {}
