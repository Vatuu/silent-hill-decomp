#include "game.h"

#include <libpad.h>
#include <strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "main/fsqueue.h"

u8 D_800AFD04 = 0;
u8 D_800AFD05 = 0;
// 2 bytes of padding.

bool (*D_800AFD08[])(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* ptr, u32* arg3) = 
{
    func_80089A30,
    func_80089BB8,
    func_80089DF0,
    func_8008973C,
    func_80089D0C
};

s16 D_800AFD1C[] = // Used by `func_8008A3E0`.
{
    0x1000, 0x1000, 0x800, 0x555,
    0x400,  0x333,  0x2AA, 0x249,
    0x200,  0x1C7,  0x199, 0x174,
    0x155,  0x13B,  0x124, 0x111
};

void func_80085D78(bool reset) // 0x80085D78
{
    if (reset)
    {
        SysWork_StateStepIncrement(1);
    }
    else
    {
        SysWork_StateStepIncrement(0);
    }
}

void func_80085DC0(bool arg0, s32 sysStateStep) // 0x80085DC0
{
    if (arg0)
    {
        SysWork_StateStepSet(1, sysStateStep);
    }
    else
    {
        SysWork_StateStepSet(0, sysStateStep);
    }
}

void func_80085DF0(void) // 0x80085DF0
{
    g_SysWork.timer_2C += g_DeltaTime1;

    if (g_MapOverlayHeader.func_EC() != NULL || g_SysWork.timer_2C > Q12(1.0f))
    {
        SysWork_StateStepIncrement(0);
    }
}

void SysWork_StateStepIncrementDelayed(q19_12 delay, bool reset) // 0x80085E6C
{
    g_SysWork.timer_2C += g_DeltaTime1;
    if (delay < g_SysWork.timer_2C)
    {
        func_80085D78(reset);
    }
}

void func_80085EB8(u32 arg0, s_SubCharacter* chara, s32 arg2, bool reset) // 0x80085EB8
{
    s32 result;

    switch (arg0)
    {
        case 0:
            if (chara == &g_SysWork.player_4C.chara_0)
            {
                g_MapOverlayHeader.func_D4(arg2);
            }
            else 
            {
                g_MapOverlayHeader.func_124(chara);
            }
            break;

        case 1:
            if (chara == &g_SysWork.player_4C.chara_0)
            {
                result = g_MapOverlayHeader.func_E8(chara);
                if (result == 1) 
                {
                    func_80085D78(reset);
                }
            }
            else
            {
                result = g_MapOverlayHeader.func_138(chara);
                if (result == 1)
                {
                    func_80085D78(reset);
                }
            }
            break;

        case 2:
            if (chara == &g_SysWork.player_4C.chara_0)
            {
                g_MapOverlayHeader.func_DC();
            }
            else
            {
                g_MapOverlayHeader.func_12C(chara);
            }
            break;

        case 3:
            if (chara == &g_SysWork.player_4C.chara_0)
            {
                g_MapOverlayHeader.func_E4(chara, arg2);
            }
            else 
            {
                g_MapOverlayHeader.func_134(chara);
            }
            break;

        case 4:
            if (chara == &g_SysWork.player_4C.chara_0)
            {
                g_MapOverlayHeader.func_E4(chara, arg2);
                g_MapOverlayHeader.func_D8();
            }
            else 
            {
                g_MapOverlayHeader.func_128(chara);
            }
            break;
    }
}

void func_8008605C(e_EventFlag eventFlagIdx, s32 stepTrue, s32 stepFalse, bool stepSecondary) // 0x8008605C
{
    if (!Savegame_EventFlagGet(eventFlagIdx))
    {
        func_80085DC0(stepSecondary, stepFalse);
    }
    else
    {
        func_80085DC0(stepSecondary, stepTrue);
    }
}

void MapMsg_DisplayAndHandleSelection(bool hasSelection, s32 mapMsgIdx, s32 step0, s32 step1, s32 step2, bool stepSecondary) // 0x800860B0
{
    s32 mapMsgState;

    mapMsgState = Gfx_MapMsg_Draw(mapMsgIdx);
    if (mapMsgState <= MapMsgState_Idle)
    {
        return;
    }
    
    if (!hasSelection)
    {
        func_80085D78(stepSecondary);
        return;
    }

    if (mapMsgState == MapMsgState_SelectEntry0)
    {
        func_80085DC0(stepSecondary, step0);
    }
    if (mapMsgState == MapMsgState_SelectEntry1)
    {
        func_80085DC0(stepSecondary, step1);
    }
    if (mapMsgState == MapMsgState_SelectEntry2)
    {
        func_80085DC0(stepSecondary, step2);
    }
}

void SysWork_StateStepIncrementAfterFade(s32 stateStep, bool cond, s32 fadeType, q19_12 fadeTimestep, bool reset) // 0x8008616C
{
    typedef enum _FadeType
    {
        FadeType_Black = 0,
        FadeType_White = 1,
        FadeType_Unk2  = 2, // TODO: Investigate. Some state machine flow logic when this is used.
        FadeType_Unk3  = 3  // TODO: Investigate.
    } s_FadeType;

    s32 activeStateStep;

    // If `stateStep != 2`, `field_14` dictates what happens. This field is manipulated often in map event functions.
    if (stateStep != 2)
    {
        activeStateStep = stateStep;
    }
    else
    {
        activeStateStep = g_SysWork.sysStateStep_C[2];
    }

    switch (activeStateStep)
    {
        case 0:
            if (fadeType != FadeType_Unk2)
            {
                g_ScreenFadeTimestep = fadeTimestep;
            }

            if (cond)
            {
                if (fadeType == FadeType_Black)
                {
                    ScreenFade_Start(false, false, false);
                }
                else if (fadeType == FadeType_White)
                {
                    ScreenFade_Start(false, false, true);
                }
                else
                {
                    g_SysWork.field_30 = 18;

                    if (fadeType == FadeType_Unk3)
                    {
                        g_SysWork.flags_22A4 |= 1 << 3;
                    }
                }
            }
            else if (fadeType == FadeType_Black)
            {
                ScreenFade_Start(false, true, false);
            }
            else if (fadeType == FadeType_White)
            {
                ScreenFade_Start(false, true, true);
            }
            else
            {
                g_SysWork.field_30 = 22;
            }

            if (stateStep != 0)
            {
                SysWork_StateStepIncrement(2);
            }
            break;

        case 1:
            if (fadeType < FadeType_Unk2)
            {
                if (cond || g_Screen_FadeStatus != activeStateStep)
                {
                    if (cond == activeStateStep && ScreenFade_IsFinished())
                    {
                        func_80085D78(reset);
                    }
                    break;
                }
            }
            else if ((cond || g_SysWork.field_30 != activeStateStep) && !(cond == activeStateStep && g_SysWork.field_30 == 21))
            {
                break;
            }

            func_80085D78(reset);
            break;
    }
}

const RECT D_8002AB10 =  // 0x8002AB10 .rodata
{
    SCREEN_POSITION_X(100.0f), 256,
    (SCREEN_WIDTH / 5) * 3, SCREEN_HEIGHT
};

void func_800862F8(s32 stateStep, e_FsFile fileIdx, bool reset) // 0x800862F8
{
    s32 activeStateStep;

    if (stateStep == 7)
    {
        activeStateStep = g_SysWork.sysStateStep_C[2];
    }
    else
    {
        activeStateStep = stateStep;
        if (activeStateStep == 8)
        {
            activeStateStep = 1;
            if (g_SysWork.sysStateStep_C[2] == 0)
            {
                activeStateStep = 4;
            }
        }
    }

    switch (activeStateStep)
    {
        case 0:
            Fs_QueueStartReadTim(fileIdx, FS_BUFFER_1, &g_ItemInspectionImg);

            if (stateStep != 0)
            {
                SysWork_StateStepIncrement(2);

                if (Fs_QueueDoThingWhenEmpty())
                {
                    func_80085D78(reset);
                }
            }
            break;

        case 1:
            if (Fs_QueueDoThingWhenEmpty())
            {
                func_80085D78(reset);
            }
            break;

        case 2:
            Gfx_BackgroundSpriteDraw_2(&g_ItemInspectionImg);
            break;

        case 3:
            DrawSync(SyncMode_Wait);
            StoreImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(SyncMode_Wait);
            break;

        case 4:
            Fs_QueueStartReadTim(fileIdx, FS_BUFFER_1, &D_800A9A04);

            if (stateStep == 8)
            {
                SysWork_StateStepSet(2, 1);
            }
            break;

        case 5:
            Gfx_BackgroundSpriteDraw_2(&D_800A9A04);
            break;

        case 6:
            LoadImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(SyncMode_Wait);
            break;
    }
}

void func_80086470(u32 stateStep, e_InventoryItemId itemId, s32 itemCount, bool reset) // 0x80086470
{
    s32 activeStateStep;

    if (stateStep == 6 && g_SysWork.sysStateStep_C[2] == 0)
    {
        SysWork_StateStepSet(2, 2);
    }

    activeStateStep = stateStep;

    if (stateStep >= 2)
    {
        if (stateStep == 2)
        {
            activeStateStep = 3;
        }
        else if (stateStep == 3)
        {
            activeStateStep = 2;
        }
        else
        {
            activeStateStep = g_SysWork.sysStateStep_C[2];
        }
    }

    switch (activeStateStep)
    {
        case 0:
            GameFs_UniqueItemModelLoad(itemId);
            
            if (stateStep == 0)
            {
                SysWork_StateStepIncrement(1);
                g_SysWork.sysStateStep_C[1]--;
            }

            SysWork_StateStepIncrement(2);

        case 1:
            if (!Fs_QueueDoThingWhenEmpty())
            {
                break;
            }

            func_80054A04(itemId);

            if (stateStep == 1 || stateStep == 4)
            {
                func_80085D78(reset);
                break;
            }

            SysWork_StateStepIncrement(2);

        case 2:
            SysWork_StateStepSet(2, 0);

            if (stateStep == 3 || stateStep == 6)
            {
                Inventory_AddSpecialItem(itemId, itemCount);
            }
            break;
    }
}

void func_800865FC(bool isPos, s32 idx0, s32 idx1, q3_12 angleY, q19_12 offsetOrPosX, q19_12 offsetOrPosZ) // 0x800865FC
{
    if (!isPos) 
    {
        D_800C4640[idx0][idx1].vx = g_SysWork.player_4C.chara_0.position_18.vx + offsetOrPosX;
        D_800C4640[idx0][idx1].vy = g_SysWork.player_4C.chara_0.position_18.vy;
        D_800C4640[idx0][idx1].vz = g_SysWork.player_4C.chara_0.position_18.vz + offsetOrPosZ;

        D_800C4700[idx0] = angleY;
    }
    else if (isPos == true)
    {
        D_800C4640[idx0][idx1].vx = offsetOrPosX;
        D_800C4640[idx0][idx1].vy = g_SysWork.player_4C.chara_0.position_18.vy;
        D_800C4640[idx0][idx1].vz = offsetOrPosZ;

        D_800C4700[idx0] = angleY;
    }
}

void func_800866D4(s32 arg0, s32 arg1, bool reset) // 0x800866D4
{
    if (g_MapOverlayHeader.func_D0(arg0, &D_800C4640, D_800C4700[0], arg1) == 1)
    {
        func_80085D78(reset);
    }
}

void func_80086728(s_SubCharacter* chara, s32 arg1, s32 arg2, bool reset) // 0x80086728
{
    if (g_MapOverlayHeader.func_13C(chara, arg1, &D_800C46A0, D_800C4702, arg2) == 1)
    {
        func_80085D78(reset);
    }
}

void func_8008677C(s_SubCharacter* chara, s32 arg1, s32 arg2) // 0x8008677C
{
    g_MapOverlayHeader.func_13C(chara, arg1, &D_800C46A0, D_800C4702, arg2);
}

void func_800867B4(s32 state, s32 idx) // 0x800867B4
{
    switch (state)
    {
        case 0:
            DrawSync(SyncMode_Wait);
            StoreImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(SyncMode_Wait);

            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_FullscreenMapTimFileIdxs[idx], FS_BUFFER_2, &g_MapImg);
            Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_MapMarkingTimFileIdxs[idx], FS_BUFFER_1, &g_MapMarkerAtlasImg);

            Screen_Init(SCREEN_WIDTH, true);
            GsSwapDispBuff();
            Fs_QueueWaitForEmpty();
            break;

        case 1:
            Gfx_BackgroundSpriteDraw(&g_MapImg);
            break;

        case 2:
            LoadImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(SyncMode_Wait);
            Screen_Init(SCREEN_WIDTH, false);
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
    return FP_MULTIPLY(arg0, Math_Sin(arg1 + ((arg2 * D_800C4710[idx]) / arg3)), Q12_SHIFT);
}

void Map_MessageWithAudio(s32 mapMsgIdx, u8* soundIdx, u16* soundsIdxs) // 0x800869E4
{
    s32 mapMsgState;

    g_SysWork.sysFlags_22A0 |= SysFlag_5;

    mapMsgState = Gfx_MapMsg_Draw(mapMsgIdx);
    if (mapMsgState == MapMsgState_SelectEntry0)
    {
        SysWork_StateStepIncrement(0);
    }
    else if (mapMsgState == MapMsgState_Finish)
    {
        Sd_EngineCmd(soundsIdxs[*soundIdx]);
        *soundIdx += 1;
    }
}

void Camera_PositionSet(VECTOR3* pos, q19_12 offsetOrPosX, q19_12 offsetOrPosY, q19_12 offsetOrPosZ,
                        q19_12 accelXz, q19_12 accelY, q19_12 speedXzMax, q19_12 speedYMax, bool warp) // 0x80086A94
{
    VECTOR3         posTarget;
    VC_CAM_MV_PARAM camMoveParams;

    // Set position target.
    if (pos != NULL)
    {
        posTarget.vx = pos->vx + offsetOrPosX;
        posTarget.vy = pos->vy + offsetOrPosY;
        posTarget.vz = pos->vz + offsetOrPosZ;
    }
    else
    {
        posTarget.vx = offsetOrPosX;
        posTarget.vy = offsetOrPosY;
        posTarget.vz = offsetOrPosZ;
    }

    // Set acceleration on XZ plane.
    if (accelXz == Q12(0.0f))
    {
        camMoveParams.accel_xz = cam_mv_prm_user.accel_xz;
    }
    else
    {
        camMoveParams.accel_xz = accelXz;
    }

    // Set acceleration on Y axis.
    if (accelY == Q12(0.0f))
    {
        camMoveParams.accel_y = cam_mv_prm_user.accel_y;
    }
    else
    {
        camMoveParams.accel_y = accelY;
    }

    // Set max speed on XZ plane.
    if (speedXzMax == Q12(0.0f))
    {
        camMoveParams.max_spd_xz = cam_mv_prm_user.max_spd_xz;
    }
    else
    {
        camMoveParams.max_spd_xz = speedXzMax;
    }

    // Set max speed on Y axis.
    if (speedYMax == Q12(0.0f))
    {
        camMoveParams.max_spd_y = cam_mv_prm_user.max_spd_y;
    }
    else
    {
        camMoveParams.max_spd_y = speedYMax;
    }

    // Set camera position target.
    vcUserCamTarget(&posTarget, &camMoveParams, warp);
}

void Camera_LookAtSet(VECTOR3* lookAt, q19_12 lookAtOffsetOrPosX, q19_12 lookAtOffsetOrPosY, q19_12 lookAtOffsetOrPosZ,
                      q19_12 angularAccelX, q19_12 angularAccelY, q19_12 angularSpeedXMax, q19_12 angularSpeedYMax, bool warp) // 0x80086B70
{
    VECTOR3           lookAtTarget;
    VC_WATCH_MV_PARAM camLookAtMoveParams;

    // Set look-at target.
    if (lookAt != NULL)
    {
        lookAtTarget.vx = lookAt->vx + lookAtOffsetOrPosX;
        lookAtTarget.vy = lookAt->vy + lookAtOffsetOrPosY;
        lookAtTarget.vz = lookAt->vz + lookAtOffsetOrPosZ;
    }
    else
    {
        lookAtTarget.vx = lookAtOffsetOrPosX;
        lookAtTarget.vy = lookAtOffsetOrPosY;
        lookAtTarget.vz = lookAtOffsetOrPosZ;
    }

    // Set angular acceleration on X axis.
    if (angularAccelX == FP_ANGLE(0.0f))
    {
        camLookAtMoveParams.ang_accel_x = deflt_watch_mv_prm.ang_accel_x;
    }
    else
    {
        camLookAtMoveParams.ang_accel_x = angularAccelX;
    }

    // Set angular acceleration on Y axis.
    if (angularAccelY == FP_ANGLE(0.0f))
    {
        camLookAtMoveParams.ang_accel_y = deflt_watch_mv_prm.ang_accel_y;
    }
    else
    {
        camLookAtMoveParams.ang_accel_y = angularAccelY;
    }

    // Set max angular speed on X axis.
    if (angularSpeedXMax == FP_ANGLE(0.0f))
    {
        camLookAtMoveParams.max_ang_spd_x = deflt_watch_mv_prm.max_ang_spd_x;
    }
    else
    {
        camLookAtMoveParams.max_ang_spd_x = angularSpeedXMax;
    }
    
    // Set max angular speed on Y axis.
    if (angularSpeedYMax == FP_ANGLE(0.0f))
    {
        camLookAtMoveParams.max_ang_spd_y = deflt_watch_mv_prm.max_ang_spd_y;
    }
    else
    {
        camLookAtMoveParams.max_ang_spd_y = angularSpeedYMax;
    }

    // Set camera flags and rotation target.
    vcWorkSetFlags(0, VC_VISIBLE_CHARA_F);
    vcUserWatchTarget(&lookAtTarget, &camLookAtMoveParams, warp);
}

void func_80086C58(s_SubCharacter* chara, s32 arg1) // 0x80086C58
{
    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            func_80085EB8(0, chara, arg1, false);

            SysWork_StateStepIncrement(1);
            break;

        case 1:
            func_80085EB8(1, chara, 0, true);
            break;

        default:
            SysWork_StateStepIncrement(0);
            break;
    }
}

void func_80086D04(s_SubCharacter* chara) // 0x80086D04
{
    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            func_80085EB8(3, chara, 0, false);
            SysWork_StateStepIncrement(1);
            break;

        case 1:
            func_80085EB8(1, chara, 0, true);
            break;

        default:
            SysWork_StateStepIncrement(0);
            break;
    }
}

void func_80086DA8(e_FsFile fileIdx, q19_12 fadeTimestep) // 0x80086DA8
{
    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            SysWork_StateStepIncrementAfterFade(0, true, 0, fadeTimestep, false);
            SysWork_StateStepIncrement(1);

        case 1:
            func_800862F8(7, fileIdx, true);
            break;

        default:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;
    }
}

void func_80086E50(e_FsFile fileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1) // 0x80086E50
{
    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            SysWork_StateStepIncrementAfterFade(0, true, 0, fadeTimestep0, false);
            SysWork_StateStepIncrement(1);

        case 1:
            func_800862F8(7, fileIdx, true);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), true);
            break;

        default:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, fadeTimestep1, false);
    }
}

void func_80086F44(q19_12 fadeTimestep0, q19_12 fadeTimestep1) // 0x80086F44
{
    if (g_SysWork.sysStateStep_C[1] == 0)
    {
        func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
        SysWork_StateStepIncrementAfterFade(2, true, 0, fadeTimestep1, true);
        return;
    }

    SysWork_StateStepIncrementAfterFade(0, false, 0, fadeTimestep0, false);
    SysWork_StateStepIncrement(0);
}

void Map_MessageWithSfx(s32 mapMsgIdx, e_SfxId sfxId, VECTOR3* sfxPos) // 0x80086FE8
{
    s32 i;

    if (!(g_SysWork.flags_22A4 & (1 << 5)))
    {
        // Run through NPCs.
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
        {
            if (g_SysWork.npcs_1A0[i].model_0.charaId_0 >= Chara_Harry &&
                g_SysWork.npcs_1A0[i].model_0.charaId_0 <= Chara_MonsterCybil &&
                g_SysWork.npcs_1A0[i].health_B0 > Q12(0.0f))
            {
                break;
            }
        }

        if (i != ARRAY_SIZE(g_SysWork.npcs_1A0))
        {
            g_DeltaTime0 = Q12(0.0f);
        }
    }

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            g_MapOverlayHeader.freezePlayerControl_C8();
            func_8005DC1C(sfxId, sfxPos, Q8_CLAMPED(0.5f), 0);

            SysWork_StateStepIncrement(1);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), true);
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, mapMsgIdx, 0, 0, 0, true);
            break;

        default:
            g_MapOverlayHeader.unfreezePlayerControl_CC(0);

            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_8008716C(e_InventoryItemId itemId, q19_12 fadeTimestep0, q19_12 fadeTimestep1) // 0x8008716C
{
    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            g_MapOverlayHeader.freezePlayerControl_C8();
            SysWork_StateStepIncrementAfterFade(0, true, 0, fadeTimestep0, false);
            SysWork_StateStepIncrement(1);

        case 1:
            func_800862F8(7, itemId, true);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), true);
            break;

        case 3:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, fadeTimestep1, true);
            break;

        case 4:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);

            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SysWork_StateStepIncrement(1);
            }
            break;

        case 5:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, fadeTimestep1, true);
            break;

        default:
            SysWork_StateStepIncrementAfterFade(0, false, 0, fadeTimestep0, false);
            g_MapOverlayHeader.unfreezePlayerControl_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapMsg_DisplayWithTexture(e_FsFile textureFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx) // 0x80087360
{
    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            g_MapOverlayHeader.freezePlayerControl_C8();
            SysWork_StateStepIncrementAfterFade(0, true, 0, fadeTimestep0, false);
            SysWork_StateStepIncrement(1);

        case 1:
            func_800862F8(7, textureFileIdx, true);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), true);
            break;

        case 3:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, fadeTimestep1, true);
            break;

        case 4:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            MapMsg_DisplayAndHandleSelection(false, mapMsgIdx, 0, 0, 0, true);
            break;
        
        case 5:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, fadeTimestep1, true);
            break;

        default:
            SysWork_StateStepIncrementAfterFade(0, false, 0, fadeTimestep0, false);
            g_MapOverlayHeader.unfreezePlayerControl_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_80087540(e_FsFile textureFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx0, s32 mapMsgIdx1) // 0x80087540
{
    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            g_MapOverlayHeader.freezePlayerControl_C8();
            SysWork_StateStepIncrementAfterFade(0, true, 0, fadeTimestep0, false);
            SysWork_StateStepIncrement(1);

        case 1:
            func_800862F8(7, textureFileIdx, true);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), true);
            break;

        case 3:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, fadeTimestep1, true);
            break;

        case 4:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            
            if (mapMsgIdx0 != MapMsgCode_None)
            {
                MapMsg_DisplayAndHandleSelection(false, mapMsgIdx0, 0, 0, 0, true);
                break;
            }

            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 |
                                                 g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SysWork_StateStepIncrement(1);
            }
            break;

        case 5:
            g_BackgroundColor = 48;
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            MapMsg_DisplayAndHandleSelection(false, mapMsgIdx1, 0, 0, 0, true);
            break;

        case 6:
            g_BackgroundColor = 48;

            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, fadeTimestep1, true);
            break;

        default:
            SysWork_StateStepIncrementAfterFade(0, false, 0, fadeTimestep0, false);
            g_MapOverlayHeader.unfreezePlayerControl_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_ItemTake(e_InventoryItemId itemId, s32 itemCount, e_EventFlag eventFlagIdx, s32 mapMsgIdx) // 0x800877B8
{
    s32 i            = itemId;
    s32 mapMsgIdxCpy = mapMsgIdx;

    if (!(g_SysWork.flags_22A4 & (1 << 5)))
    {
        // Run through NPCs.
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
        {
            if (g_SysWork.npcs_1A0[i].model_0.charaId_0 >= Chara_Harry && g_SysWork.npcs_1A0[i].model_0.charaId_0 <= Chara_MonsterCybil &&
                g_SysWork.npcs_1A0[i].health_B0 > Q12(0.0f))
            {
                break;
            }
        }
        
        if (i != ARRAY_SIZE(g_SysWork.npcs_1A0))
        {
            g_DeltaTime0 = Q12(0.0f);
        }
    }

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0: // Freeze player and start loading item model.
            g_MapOverlayHeader.freezePlayerControl_C8();
            func_80086470(0, itemId, 0, false);

            SysWork_StateStepIncrement(1);

        case 1: // Loading model.
            func_80086470(1, itemId, 0, true);
            break;

        case 2:
            // `Gfx_PickupItemAnimate` scales model up and returns `false`,
            // then starts rotating it and returns `true`.
            if (Gfx_PickupItemAnimate(itemId))
            {
                MapMsg_DisplayAndHandleSelection(true, mapMsgIdxCpy, 3, NO_VALUE, 0, true); // 3 is "Yes", `NO_VALUE` is "No".
            }

            // Flag pickup item as collected.
            Savegame_EventFlagSet(eventFlagIdx);
            break;

        case 3: // "Yes" selected.
            func_80086470(3, itemId, itemCount, false);
            SysWork_StateStepIncrement(1);

        default:
            // Flag pickup item as uncollected. Selecting 'No' sets `field_10` to `NO_VALUE`.
            if (g_SysWork.sysStateStep_C[1] == NO_VALUE)
            {
                Savegame_EventFlagClear(eventFlagIdx);
            }

            g_MapOverlayHeader.unfreezePlayerControl_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_CommonItemTake(u32 pickupType, e_EventFlag eventFlagIdx) // 0x800879FC
{
    #define EASY_DIFFICULTY_AMMO_COUNT_MULT_MIN 2

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
            Event_ItemTake(InventoryItemId_FirstAidKit, DEFAULT_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_FirstAidSelect);
            break;

        case CommonPickupItemId_HealthDrink:
            Event_ItemTake(InventoryItemId_HealthDrink, DEFAULT_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_HealthDrinkSelect);
            break;

        case CommonPickupItemId_Ampoule:
            Event_ItemTake(InventoryItemId_Ampoule, DEFAULT_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_AmpouleSelect);
            break;

        case CommonPickupItemId_HandgunBullets:
            Event_ItemTake(InventoryItemId_HandgunBullets, ammoCountMult * HANDGUN_AMMO_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_HandgunAmmoSelect);
            break;

        case CommonPickupItemId_ShotgunShells:
            Event_ItemTake(InventoryItemId_ShotgunShells, ammoCountMult * SHOTGUN_AMMO_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_ShotgunAmmoSelect);
            break;

        case CommonPickupItemId_RifleShells:
            Event_ItemTake(InventoryItemId_RifleShells, ammoCountMult * RIFLE_AMMO_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_RifleAmmoSelect);
            break;
    }
}

void Event_MapTake(s32 mapFlagIdx, e_EventFlag eventFlagIdx, s32 mapMsgIdx) // 0x80087AF4
{
    static const RECT D_8002ABA4 = {
        SCREEN_POSITION_X(100.0f), 256,
        SCREEN_WIDTH / 2, SCREEN_HEIGHT
    };

    s32 mapFlagIdxCpy;

    g_DeltaTime0  = Q12(0.0f);
    mapFlagIdxCpy = mapFlagIdx;

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            g_MapOverlayHeader.freezePlayerControl_C8();
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_FullscreenMapTimFileIdxs[mapFlagIdx]);
            SysWork_StateStepIncrement(1);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), true);
            break;

        case 2:
            DrawSync(SyncMode_Wait);
            StoreImage(&D_8002ABA4, IMAGE_BUFFER);
            DrawSync(SyncMode_Wait);
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_FullscreenMapTimFileIdxs[mapFlagIdx], FS_BUFFER_2, &g_MapImg);
            Screen_Init(SCREEN_WIDTH, true);

            g_IntervalVBlanks = 1;

            GsSwapDispBuff();
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Fs_QueueWaitForEmpty();

            SysWork_StateStepIncrement(1);

        case 3:
            g_BackgroundColor = 88;

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            MapMsg_DisplayAndHandleSelection(true, mapMsgIdx, 4, 5, 0, true); // 4 is "No", 5 is "Yes".
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
            }

            Savegame_EventFlagSet(eventFlagIdx);
            SysWork_StateStepIncrement(1);

        case 5:
            g_BackgroundColor = 88;

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), true);
            break;

        default:
            LoadImage(&D_8002ABA4, IMAGE_BUFFER);
            DrawSync(SyncMode_Wait);
            Screen_Init(SCREEN_WIDTH, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            g_MapOverlayHeader.unfreezePlayerControl_CC(0);
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

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            if (!func_800358A8(arg0))
            {
                SysWork_StateStepSet(1, 3);
                break;
            }

            g_SysWork.sysFlags_22A0 |= SysFlag_7;
            SysWork_StateStepIncrement(1);
            break;
        
        case 1:
            g_SysWork.sysFlags_22A0 |= SysFlag_7;
            Sd_EngineCmd(23);

            SysWork_StateStepIncrement(1);
            break;
        
        case 2:
            g_SysWork.sysFlags_22A0 |= SysFlag_7;
            
            if (!func_80045BC8())
            {
                func_800358DC(arg0);

                SysWork_StateStepIncrement(1);
            }
            break;
        
        case 3:
            SysWork_StateStepIncrement(0); // Resets `field_10` to 0.
            break;
    }
}

void func_80088028(void) // 0x80088028
{
    func_80087EDC(0);
}

void func_80088048(void) // 0x80088048
{
    if (func_80045B28())
    {
        return;
    }

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            func_80035E1C();
            Sd_EngineCmd(18);
            SysWork_StateStepIncrement(1);
            break;

        case 1:
            if (!func_80045BC8())
            {
                SysWork_StateStepIncrement(0); // Resets `field_10` to 0.
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

    switch (g_SysWork.sysStateStep_C[1])
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

            SysWork_StateStepIncrement(1);
            break;

        case 1:
            if (!func_80045BC8())
            {
                SysWork_StateStepIncrement(0); // Resets `field_10` to 0.
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

    setSemiTrans(poly, false);

    addPrim(g_OrderingTable0[g_ActiveBufferIdx].org, poly);
    poly++;

    GsOUT_PACKET_P = (PACKET*)poly;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80088370); // 0x80088370

bool Chara_Load(s32 modelIdx, s8 charaId, GsCOORDINATE2* coords, s8 forceFree, s_LmHeader* lmHdr, s_FsImageDesc* tex) // 0x80088C7C
{
    func_80035338(modelIdx + 1, charaId, NULL, coords);
    WorldGfx_CharaLmBufferAssign(forceFree);
    WorldGfx_CharaLoad(charaId, modelIdx, lmHdr, tex);
    return true;
}

bool Chara_ProcessLoads(void) // 0x80088D0C
{
    Fs_QueueWaitForEmpty();
    WorldGfx_CharaModelProcessAllLoads();
    return true;
}

void func_80088D34(s32 idx) // 0x80088D34
{
    idx++;
    Anim_BoneInit(D_800A992C[idx].animFile1_8, D_800A992C[idx].npcCoords_14);
}

s32 Chara_Spawn(e_CharacterId charaId, s32 arg1, q19_12 posX, q19_12 posZ, q3_12 rotY, u32 stateStep) // 0x80088D78
{
    s_Collision     coll;
    s32             i;
    s32             var_a0;
    s32             arg1_1;
    s_SubCharacter* var_s6;

    if (charaId <= Chara_MonsterCybil && arg1 < 0x40)
    {
        arg1_1 = 0x1F;
        arg1_1 = arg1 & arg1_1;
    }
    else
    {
        arg1_1 = 0;
    }

    if (charaId <= Chara_MonsterCybil)
    {
        if (HAS_FLAG(&g_SysWork.field_228C, arg1_1))
        {
            for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
            {
                if (g_SysWork.npcs_1A0[i].field_40 == arg1_1)
                {
                    return i;
                }
            }

            return ARRAY_SIZE(g_SysWork.npcs_1A0);
        }

        var_a0 = 0;
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
        {
            if (g_SysWork.npcs_1A0[i].model_0.charaId_0 != Chara_None)
            { 
                var_a0++;
            }
        }

        if (var_a0 >= g_SysWork.field_2280)
        {
            return 0;
        }
    }

    // Run through NPC slots.
    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
    {
        // Skip occupied slot.
        if (g_SysWork.npcs_1A0[i].model_0.charaId_0 != Chara_None)
        {
            continue;
        }

        bzero(&g_SysWork.npcs_1A0[i], sizeof(s_SubCharacter));

        g_SysWork.npcs_1A0[i].model_0.charaId_0 = charaId;
        g_SysWork.npcs_1A0[i].field_40 = arg1_1;

        if (charaId <= Chara_MonsterCybil && arg1 < 64)
        {
            SET_FLAG(&g_SysWork.field_228C, arg1_1);
        }

        SET_FLAG(&g_SysWork.flags_2290, i);

        g_SysWork.npcs_1A0[i].model_0.state_2     = 0;
        g_SysWork.npcs_1A0[i].model_0.stateStep_3 = stateStep;

        g_SysWork.npcs_1A0[i].position_18.vx = posX;
        Collision_Get(&coll, posX, posZ);
        g_SysWork.npcs_1A0[i].position_18.vy = coll.groundHeight_0;
        g_SysWork.npcs_1A0[i].position_18.vz = posZ;
        g_SysWork.npcs_1A0[i].rotation_24.vy = rotY;

        var_s6                          = &g_SysWork.npcs_1A0[i];
        var_s6->model_0.anim_4.flags_2 |= AnimFlag_Visible;

        return i;
    }

    return ARRAY_SIZE(g_SysWork.npcs_1A0);
}

void func_80088F94(s_SubCharacter* chara, s32 unused1, s32 unsued2) // 0x80088F94
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

void func_80088FF4(e_CharacterId charaId, s32 spawnIdx, s32 spawnFlags) // 0x80088FF4
{
    s_MapPoint2d* mapPoint;

    mapPoint                         = &g_MapOverlayHeader.charaSpawns_24C[D_800A98FC[charaId] - 1][spawnIdx];
    mapPoint->data.spawnInfo.flags_6 = spawnFlags;
}

void func_80089034(e_CharacterId charaId, s32 spawnIdx, q19_12 posX, q19_12 posZ) // 0x80089034
{
    s_MapPoint2d* mapPoint0;
    s_MapPoint2d* mapPoint1;

    mapPoint0              = &g_MapOverlayHeader.charaSpawns_24C[D_800A98FC[charaId] - 1][spawnIdx];
    mapPoint0->positionX_0 = posX;

    mapPoint1              = &g_MapOverlayHeader.charaSpawns_24C[D_800A98FC[charaId] - 1][spawnIdx];
    mapPoint1->positionZ_8 = posZ;
}

void func_80089090(s32 arg0) // 0x80089090
{
    func_80089524(&g_SysWork.field_2514, arg0);
}

void func_800890B8(void) // 0x800890B8
{
    func_8009E198(&g_SysWork.field_2514, 0);
    func_8009E310(&g_SysWork.field_2514, g_SysWork.field_2514.head_18.unk_8, 2);
    func_8009EBB8(&g_SysWork.field_2514, g_SysWork.field_2514.head_18.unk_18, 16);

    g_SysWork.field_2510 = func_8009E4F8();

    func_8009E7D8(g_SysWork.field_2510);
    func_8009E97C(g_SysWork.field_2510);
}

s32 func_80089128(void) // 0x80089128
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

const s_8002AC04 D_8002AC04[] = {
    // 2nd field is used as index into `D_800AFD08` funcptr array.
    // Seems each function takes different kind of params in 5th/6th fields:
    // #0 5th field is some kind of index/counter.
    // #1 5th field is pointer to another `D_8002AC04` entry.
    // #2 5th field points to some data that comes after this array.
    // #3 5th field is always 0.
    // #4 5th field is index/counter.
    { NULL, { .func_8008973C_data = { 3, 2, 0, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 3, 3, 0, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 3, 1, 0, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 3, 0, 0, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 3, 4, 0, 0, 0 } } },
    { &D_8002AC04[22], { .func_8008973C_data = { 0, 0, 0, 5, 0 } } },
    { &D_8002AC04[25], { .func_8008973C_data = { 0, 32, 0, 6, 0 } } },
    { &D_8002AC04[26], { .func_8008973C_data = { 0, 32, 0, 7, 0 } } },
    { &D_8002AC04[27], { .func_8008973C_data = { 0, 32, 0, 8, 0 } } },
    { &D_8002AC04[23], { .func_8008973C_data = { 0, 32, 0, 9, 0 } } },
    { &D_8002AC04[24], { .func_8008973C_data = { 0, 32, 0, 10, 0 } } },
    { &D_8002AC04[5], { .func_8008973C_data = { 1, 0, 0, &D_8002AC04[6], 0 } } },
    { &D_8002AC04[31], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[34], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[37], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[40], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[43], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[46], { .func_8008973C_data = { 0, 32, 0, 12, 0 } } },
    { &D_8002AC04[28], { .func_8008973C_data = { 0, 32, 0, 18, 0 } } },
    { &D_8002AC04[29], { .func_8008973C_data = { 0, 32, 0, 19, 0 } } },
    { NULL, { .func_8008973C_data = { 4, 0, NO_VALUE, 20, -255 } } },
    { NULL, { .func_8008973C_data = { 4, 1, NO_VALUE, 21, -255 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF70, 0x2D, 9, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF64, 0x180, 0x30, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF5C, 0x90, 0x18, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF54, 0x5A, 0xF, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF48, 0x96, 0xF, 1, 1 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF3C, 0x60, 0xC, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF3C, 0x60, 0xC, 1, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 1, NO_VALUE, &D_8002AF34, 0x4B, 0xF, 1, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF2C, 0x258, 0xF, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF28, 0x1E0, 0xF, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF24, 0x1A4, 0xF, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF20, 0x168, 0xF, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF20, 0x10E, 0xF, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { NULL, { .func_8008973C_data = { 0, 0, 0x0000, 0, 0 } } },
    { &D_8002AC04[47], { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF08, 0xB40, 0xF, 0, 0 } } },
    { &D_8002AC04[47], { .func_80089DF0_data = { 2, 0, NO_VALUE, &D_8002AF04, 0x1E, 0xF, 0, 0 } } },
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
    
    func_800892DC(21, D_800AFD04 + 32);
}

void func_800893D0(q19_12 arg0) // 0x800893D0
{
    u32 var;

    if (arg0 > Q12(25.0f))
    {
        var = 200;
    }
    else if (arg0 < Q12(5.0f))
    {
        var = 100;
    }
    else 
    {
        var = ((arg0 + Q12(15.0f)) / Q12(5.0f)) * 25;
    }
    
    func_800892DC(10, var);
}

void func_8008944C(void) // 0x8008944C
{
    func_800892DC(19, 0xA0);
}

void func_80089470(void) // 0x80089470
{
    func_800892DC(19, 0xA0);
}

void func_80089494(void) // 0x80089494
{
    func_800892DC(9, 0xA0);
}

void func_800894B8(s32 arg0) // 0x800894B8
{
    func_800892DC(9, arg0);
}

void func_800894DC(void) // 0x800894DC
{
    func_800892DC(9, 0xE0);
}

void func_80089500(void) // 0x80089500
{
    func_800892DC(9, 0xA0);
}

bool func_80089524(s_SysWork_2514* arg0, s32 padInfoMode) // 0x80089524
{
    s32             padState;
    bool            cond;
    u8              socket;
    s_SysWork_2514* temp;

    socket = arg0->field_0;
    PadInfoMode(socket, 2, 0);

    padState = PadGetState(socket);
    cond     = PadInfoMode(socket, 3, 0) == padInfoMode;
    if (!cond && padState == 6)
    {
        PadSetMainMode(socket, padInfoMode, 0);

        cond = PadSetMainMode(socket, 1, 0);

        temp            = &g_SysWork.field_2514;
        temp->field_2_4 = 0;
        temp->field_2_3 = 0;
    }

    return cond;
}

s32 func_800895E4(s_SysWork_2514* arg0, s_8002AC04* arg1, u8 arg2) // 0x800895E4
{
    u32 sp10;

    sp10 = arg2;

    if (arg1 == NULL)
    {
        return 0;
    }

    return D_800AFD08[arg1->field_4.funcIdx_4](arg0, 0, arg1, &sp10);
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

        if (D_800AFD08[ptr1->field_4.funcIdx_4](arg0, arg1, ptr1, &arg3) == 0)
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

bool func_8008973C(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* ptr, u32* arg3)
{
    if (!arg0 || arg1)
    {
        return false;
    }

    if (ptr == NULL || ptr->field_4.func_8008973C_data.funcIdx_4 != 3)
    {
        return false;
    }

    switch (ptr->field_4.func_8008973C_data.field_5)
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
            func_8008989C(arg0, ptr->field_4.func_8008973C_data.field_6, ptr->field_4.func_8008973C_data.field_C);
            break;

        case 6:
            func_8008992C(arg0, ptr->field_4.func_8008973C_data.field_6, ptr->field_4.func_8008973C_data.field_C);
            break;

        case 7:
            func_800899BC(arg0, ptr->field_4.func_8008973C_data.field_8);
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

bool func_80089A30(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u32* arg3) // 0x80089A30
{
    s32                temp_s3;
    s_SysWork_2514_18* next;
    s_SysWork_2514_18* head;
    s_SysWork_2514_18* current;
    s_func_8009ECCC*   ptr;

    ptr = arg1;

    if (arg0 == NULL)
    {
        return false;
    }

    if (arg2 == NULL)
    {
        return false;
    }

    if (arg2->field_4.funcIdx_4 != 0)
    {
        return false;
    }

    temp_s3 = arg2->field_4.func_80089A30_data.field_8;

    if (arg2->field_4.func_80089A30_data.field_5_5 || arg2->field_4.func_80089A30_data.field_5_6)
    {
        current = arg0->head_18.next_0;
        head    = &arg0->head_18;

        if (arg2->field_4.func_80089A30_data.field_5_5)
        {
            while (current != head)
            {
                if (current->field_C == temp_s3)
                {
                    if (ptr != NULL)
                    {
                        ptr->field_10 = NULL;
                    }

                    return false;
                }

                current = current->next_0;
            }
        }
        else
        {
            while (current != head)
            {
                next = current->next_0;
                if ((ptr == NULL || current != ptr) && current->field_C == temp_s3)
                {
                    func_8009EC1C(arg0, current);
                }
                current = next;
            }
        }
    }

    if (ptr == NULL)
    {
        ptr = func_8009ECCC(arg0, arg2->field_4.func_80089A30_data.field_C);
        if (ptr == NULL)
        {
            return false;
        }
        ptr->field_14_16 = *arg3;
    }

    ptr->field_10   = arg2->field_0;
    ptr->field_14_0 = 0;
    ptr->field_C    = temp_s3;

    if (arg2->field_4.func_80089A30_data.field_5_7)
    {
        ptr->field_1C = arg2->field_4.func_80089A30_data.field_6;
    }

    return true;
}

bool func_80089BB8(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u32* arg3) // 0x80089BB8
{
    s_func_8009ECCC* temp_a0;
    s_func_8009ECCC* temp_v0;
    u32              var_s1;

    if (arg0 == NULL || arg2 == NULL)
    {
        return false;
    }

    if (arg2->field_4.funcIdx_4 != 1)
    {
        return false;
    }

    if (arg1 == NULL)
    {
        var_s1 = arg2->field_4.func_80089BB8_data.field_C;
        arg1   = func_8009ECCC(arg0, var_s1);
        if (arg1 == NULL)
        {
            return false;
        }
        arg1->field_14_16 = *arg3;
    }
    else
    {
        if (arg1->field_10 != arg2)
        {
            arg1->field_10 = NULL;
            return false;
        }
        else
        {
            var_s1 = arg1->field_8;
        }
    }

    arg1->field_10   = arg2->field_0;
    arg1->field_14_0 = 0;

    if (arg2->field_4.func_80089BB8_data.field_5_7)
    {
        arg1->field_1C = arg2->field_4.func_80089BB8_data.field_6;
    }

    temp_v0 = func_8009ECCC(arg0, var_s1);
    if (temp_v0 != NULL)
    {
        temp_a0                   = temp_v0->field_0;
        temp_a0->field_4          = temp_v0->field_4;
        temp_a0->field_4->field_0 = temp_a0;

        temp_a0          = arg1->field_0;
        temp_v0->field_4 = arg1;
        temp_v0->field_0 = temp_a0;
        temp_a0->field_4 = temp_v0;

        arg1->field_0 = temp_v0;

        temp_v0->field_10    = arg2->field_4.func_80089BB8_data.field_8;
        temp_v0->field_14_0  = 0;
        temp_v0->field_C     = arg1->field_C;
        temp_v0->field_14_16 = arg1->field_14_16;
        temp_v0->field_1C    = arg1->field_1C;
    }

    return true;
}

bool func_80089D0C(s_SysWork_2514* arg0, s_func_8009ECCC* arg1, s_8002AC04* arg2, u32* arg3) // 0x80089D0C
{
    if (arg0 == NULL || arg2 == NULL)
    {
        return false;
    }

    if (arg2->field_4.func_80089D0C_data.funcIdx_4 == 4)
    {
        if (arg1 != NULL)
        {
            arg1->field_14_24 = arg2->field_4.func_80089D0C_data.field_5 & 0x7F;
            arg1->field_1E    = arg2->field_4.func_80089D0C_data.field_6;
            arg1->field_10    = arg2->field_0;
            arg1->field_14_31 = 1;
            arg1->field_18    = arg1->field_14_16 << 24;
            return false;
        }
        else
        {
            arg1 = func_8009ECCC(arg0, arg2->field_4.func_80089D0C_data.field_C);
            if (arg1 != NULL)
            {
                arg1->field_10    = arg2;
                arg1->field_14_16 = *arg3;
                arg1->field_C     = arg2->field_4.func_80089D0C_data.field_8;
                return true;
            }
        }
    }

    return false;
}

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_80089DF0); // 0x80089DF0

INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008A058); // 0x8008A058

s32 func_8008A0CC(void) // 0x8008A0CC
{
    return 0;
}

s64 func_8008A0D4(void) // 0x8008A0D4
{
    return 0;
}

s32 func_8008A0E4(s32 arg0, s32 weaponAttack, s_SubCharacter* chara, VECTOR3* pos, s32 arg4, s16 arg5, s16 arg6) // 0x8008A0E4
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

    if (g_DeltaTime0 == Q12(0.0f) || g_SysWork.sysState_8 != SysState_Gameplay)
    {
        return NO_VALUE;
    }

    if (chara == &g_SysWork.player_4C.chara_0)
    {
        anim1                       = D_800297B8;
        anim0                       = g_MapOverlayHeader.animInfos_34;
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

    chara->field_46 = weaponAttack;
    if (!(modelAnim->status_0 & (1 << 0)))
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
    chara->field_5C = *pos;
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

    if (chara->model_0.charaId_0 != Chara_Harry)
    {
        if (g_SysWork.player_4C.chara_0.attackReceived_41 != NO_VALUE)
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
            if (g_SysWork.field_275C > Q12(256.0f))
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
    if (g_SysWork.field_275C > Q12(256.0f))
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

void func_8008B398(void) // 0x8008B398
{
    func_8008B3E4(0);
    func_8008B438(0, 0, 0);
    func_8008B438(1, 0, 0);
    func_8008B40C(0, 0);
}

void func_8008B3E4(s32 vol) // 0x8008B3E4
{
    func_8008B474(0, vol, 0);
}

void func_8008B40C(s32 vol, s32 soundType) // 0x8008B40C
{
    func_8008B474(3, vol, soundType);
}

void func_8008B438(s32 arg0, s32 vol, s32 soundType) // 0x8008B438
{
    bool cond;

    cond = arg0 != 0;
    if (func_8008B474(2 - cond, vol, soundType))
    {
        func_80089314(cond);
    }
}

bool func_8008B474(s32 arg0, s32 vol, s32 soundType) // 0x8008B474
{
    s32 unkVol;
    s32 cond;
    u16 sfxId;

    unkVol = 0;
    sfxId = 0;
    switch (arg0)
    {
        case 0:
            sfxId = Sfx_Unk1300;
            unkVol = g_SysWork.field_2760;
            soundType = 0;
            break;

        case 1:
            sfxId = Sfx_Unk1301;
            unkVol = g_SysWork.field_275C;
            break;

        case 2:
            sfxId = Sfx_Unk1302;
            unkVol = g_SysWork.field_275C;
            break;

        case 3:
            sfxId = Sfx_Unk1303;
            unkVol = g_SysWork.field_2764;
            break;
    }

    cond = unkVol == Q12(0.0f);

    if (g_DeltaTime0 == Q12(0.0f))
    {
        vol = 0;
    }

    if (vol >= 0)
    {
        if (vol != 0)
        {
            if (vol > Q8_CLAMPED(1.0f))
            {
                unkVol = Q12(511.0f);
            }
            else
            {
                unkVol = FP_TO(vol, Q12_SHIFT) + Q12(256.0f);
            }
        }
        else
        {
            unkVol = 0;
        }
    }
    else
    {
        unkVol -= g_DeltaTime0 << 9;
        if (unkVol < 0)
        {
            unkVol = 0;
        }
    }

    if (unkVol == 0)
    {
        func_8004690C(sfxId);
    }
    else if (cond)
    {
        // NOTE: func_8005DC1C calls func_8005DC3C. `soundType` is `pitch` when calling `func_8005DC3C` directly.
        if (unkVol > Q12(256.0f))
        {
            func_8005DC1C(sfxId, &g_SysWork.player_4C.chara_0.position_18, FP_FROM(unkVol - Q12(256.0f), Q12_SHIFT), soundType);
        }
        else
        {
            func_8005DC1C(sfxId, &g_SysWork.player_4C.chara_0.position_18, Q8_CLAMPED(0.0f), soundType);
        }
    }
    else
    {
        if (unkVol > Q12(256.0f))
        {
            func_8005DC3C(sfxId, &g_SysWork.player_4C.chara_0.position_18, FP_FROM(unkVol - Q12(256.0f), Q12_SHIFT), 4, soundType);
        }
        else
        {
            func_8005DC3C(sfxId, &g_SysWork.player_4C.chara_0.position_18, 0, 4, soundType);
        }
    }

    switch (arg0)
    {
        case 0:
            g_SysWork.field_2760 = unkVol;
            break;

        case 1:
        case 2:
            g_SysWork.field_275C = unkVol;
            break;

        case 3:
            g_SysWork.field_2764 = unkVol;
    }

    return unkVol > Q12(256.0f);
}

void func_8008B664(VECTOR3* pos, u32 caseVar) // 0x8008B664
{
    s32 sfxId;

    sfxId = 0;
    switch (caseVar)
    {
        case 0:
        case 6:
        case 10:
        case 16:
        case 20:
        case 26:
            sfxId = Sfx_Unk1297;
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
            sfxId = Sfx_Unk1296;
            break;

        case 32:
        case 33:
        case 34:
            sfxId = Sfx_Unk1286;
            break;

        case 2:
        case 5:
        case 15:
        case 25:
            if (g_SysWork.field_275C > Q12(256.0f))
            {
                func_8008B3E4(128);
                break;
            }

        case 8:
        case 9:
            sfxId = Sfx_Unk1316;
            break;

        case 35:
    }

    if (sfxId != 0)
    {
        func_8005DC1C(sfxId, pos, Q8_CLAMPED(0.75f), 0);
    }
}

/** Main attack handling function. */
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008B714); // 0x8008B714

s32 func_8008BF84(s_MainCharacter* arg0, s32 arg1, s_800AD4C8* arg2, s32 arg3) // 0x8008BF84
{
    s_SubCharacter*  sp10;
    s32              sp14;
    s32              sp18;
    s32              sp1C;
    s32              sp20;
    s32              sp24;
    s32              sp28;
    s32              sp2C;
    s32              sp30;
    s32              sp34;
    s32              sp38;
    s32              sp3C;
    s32              sp40;
    s32              sp44;
    s32              sp48;
    s32              sp4C;
    s32              sp50;
    s32              sp54;
    s32              sp58;
    s32              sp5C;
    s32              temp_s5;
    s32              temp_s6;
    s32              temp_a0;
    s32              temp_a0_2;
    s32              temp_a0_3;
    s32              temp_lo_5;
    s32              temp_s0;
    s32              temp_s1;
    s32              temp_s2;
    s32              temp_s3;
    s32              temp_t2;
    s32              temp_t3;
    s32              temp_t4;
    s32              temp_t4_2;
    s32              temp_t5;
    s32              temp_v0_5;
    s32              temp_v0_6;
    s32              temp_v0_7;
    s32              temp_v0_8;
    s32              var_a1_2;
    s32              var_fp;
    s32              var_s1;
    s32              var_s7;
    s32              var_t1;
    s32              var_t2;
    s32              var_v0;
    s32              var_v0_3;
    s32              var_v0_6;
    s32              var_v1;
    s_MainCharacter* var_a1;
    s32              temp_a2;
    u16              temp_v1;
    s32              temp2;
    s32              temp4;

    sp28 = arg0->chara_0.characterCount_68.vx;
    sp2C = arg0->chara_0.characterCount_68.vy;
    sp30 = arg0->chara_0.characterCount_68.vz;

    sp20 = Math_Sin(arg1);
    sp24 = Math_Cos(arg1);

    D_800C4788[0].vx = 0;
    D_800C4788[0].vy = 0;
    D_800C4788[0].vz = 0;

    sp34   = arg0->chara_0.field_8C.vx;
    var_fp = arg0->chara_0.field_8C.vz;

    sp44 = 0;
    sp38 = 0;
    sp48 = 0;
    sp3C = 0;
    sp4C = 0;
    sp40 = 0;

    var_s7           = arg0->chara_0.field_8C.vy;
    D_800C4788[1].vy = var_s7;

    temp_t4          = FP_MULTIPLY_PRECISE(sp34, sp24, Q12_SHIFT) - FP_MULTIPLY_PRECISE(var_fp, sp20, Q12_SHIFT);
    D_800C4788[1].vx = temp_t4;

    temp_a0          = FP_MULTIPLY_PRECISE(sp34, sp20, Q12_SHIFT) + FP_MULTIPLY_PRECISE(var_fp, sp24, Q12_SHIFT);
    D_800C4788[1].vz = temp_a0;

    temp4 = var_s7;

    if (temp_t4 > 0)
    {
        sp38 = temp_t4;
    }
    else if (temp_t4 < 0)
    {
        sp44 = temp_t4;
    }

    if (sp3C < temp4)
    {
        sp3C = temp4;
    }
    else if (temp4 < sp48)
    {
        sp48 = temp4;
    }

    if (sp40 < temp_a0)
    {
        sp40 = temp_a0;
    }
    else if (temp_a0 < sp4C)
    {
        sp4C = temp_a0;
    }

    temp_v1   = *(u16*)&arg2->field_6;
    temp_a0_2 = *(u16*)&arg2->field_8;
    temp_a2   = *(u16*)&arg2->unk_A;

    var_v0    = (sp38 - sp44);
    temp_v0_7 = (sp3C - sp48);
    var_v0_6  = (sp40 - sp4C);

    if (var_v0 < temp_v1)
    {
        sp38 += *(u16*)&arg2->field_6 >> 1;
        sp44 -= *(u16*)&arg2->field_6 >> 1;
    }

    if (temp_v0_7 < temp_a0_2)
    {
        sp3C += *(u16*)&arg2->field_8 >> 1;
        sp48 -= *(u16*)&arg2->field_8 >> 1;
    }

    if (var_v0_6 < temp_a2)
    {
        sp40 += *(u16*)&arg2->unk_A >> 1;
        sp4C -= *(u16*)&arg2->unk_A >> 1;
    }

    if (arg0 == &g_SysWork.player_4C)
    {
        var_a1 = arg0 + 1;
        var_v0 = 6;
        var_v1 = 1;
    }
    else
    {
        var_a1 = &g_SysWork.player_4C;
        var_v0 = 1;
        var_v1 = -1;
    }

    sp18 = var_v1;
    sp10 = &var_a1->chara_0;
    sp14 = 0;

    sp50 = arg0->chara_0.position_18.vx;
    sp54 = arg0->chara_0.position_18.vz;

    temp2  = arg0->chara_0.position_18.vy;
    temp2 += arg0->chara_0.field_C8;

    D_800C47C8[0].vx = sp50;
    D_800C47C8[0].vy = temp2;
    D_800C47C8[0].vz = sp54;

    for (sp1C = var_v0; sp1C > 0; sp1C--, sp10++, sp18 *= 2)
    {
        if ((g_SysWork.sysState_8 == SysState_GameOver) || (g_SysWork.player_4C.chara_0.health_B0 <= 0) ||
            (sp10 == arg0) || (sp10->model_0.charaId_0 == 0) || (sp10->health_B0 < 0) || !sp10->field_E1_0)
        {
            continue;
        }

        D_800C47E8.vx = sp10->position_18.vx + sp10->field_D8.offsetX_0;
        D_800C47E8.vy = sp10->position_18.vy;
        D_800C47E8.vz = sp10->position_18.vz + sp10->field_D8.offsetZ_2;

        if (Math_Distance2dGet(&arg0->chara_0.position_18, &D_800C47E8) > 0x3000)
        {
            continue;
        }

        temp_s1 = sp10->position_18.vx;
        var_v1  = sp10->position_18.vy;
        temp_s2 = sp10->position_18.vz;

        temp_s0 = sp10->field_D8.offsetX_0;
        temp_s3 = sp10->field_D8.offsetZ_2;

        temp_s1 += temp_s0;

        var_v1  += sp10->field_C8;
        temp_s2 += temp_s3;

        D_800C47C8[1].vy = var_v1;
        temp_s3          = sp10->field_D6;

        temp_v0_5 = ratan2(temp_s1 - sp50, temp_s2 - sp54);
        temp_v0_6 = Math_Sin(temp_v0_5);
        temp_s0   = FP_MULTIPLY_PRECISE(temp_s3, temp_v0_6, Q12_SHIFT);

        var_s1 = Math_Cos(temp_v0_5);

        sp50 = temp_s1 - temp_s0;

        D_800C47C8[1].vx = sp50;
        sp54             = temp_s2 - FP_MULTIPLY_PRECISE(temp_s3, var_s1, Q12_SHIFT);

        D_800C47C8[1].vz = sp54;
        var_v1           = func_8006D90C(&D_800C47F8, &D_800C47C8[0], &D_800C47C8[1]);

        if (var_v1 != false)
        {
            var_v1 = true;
        }

        if (var_v1 == true)
        {
            continue;
        }

        temp_t4_2  = sp10->position_18.vx;
        temp_t4_2 += sp10->field_D8.offsetX_0;

        var_v1   = temp_t4_2 - sp28;
        temp_t5  = sp10->position_18.vz;
        temp_t5 += sp10->field_D8.offsetZ_2;

        temp_v0_8 = temp_t5 - sp30;

        sp58    = sp10->position_18.vy;
        temp_s6 = sp10->field_CC;
        temp_s5 = sp10->field_C8;

        temp_t3   = sp58 - sp2C;
        temp_t2   = FP_MULTIPLY_PRECISE(var_v1, sp24, Q12_SHIFT) - FP_MULTIPLY_PRECISE(temp_v0_8, sp20, Q12_SHIFT);
        temp_a0_3 = FP_MULTIPLY_PRECISE(var_v1, sp20, Q12_SHIFT) + FP_MULTIPLY_PRECISE(temp_v0_8, sp24, Q12_SHIFT);

        if ((temp_t3 < (sp48 - temp_s6)) || ((sp3C - temp_s5) < temp_t3))
        {
            continue;
        }

        temp_s3  = sp10->field_D6;
        var_a1_2 = 0;

        if (temp_t2 < sp44)
        {
            var_a1_2 = sp44 - temp_t2;
        }
        else if (sp38 < temp_t2)
        {
            var_a1_2 = temp_t2 - sp38;
        }

        var_v1 = 0;

        if (temp_a0_3 < sp4C)
        {
            var_v1 = sp4C - temp_a0_3;
        }
        else if (sp40 < temp_a0_3)
        {
            var_v1 = temp_a0_3 - sp40;
        }

        if (var_a1_2 | var_v1)
        {
            if (var_a1_2 == 0)
            {
                if (temp_s3 < var_v1)
                {
                    continue;
                }
            }
            else
            {
                if (var_v1 == 0)
                {
                    if (temp_s3 < var_a1_2)
                    {
                        continue;
                    }
                }
                else
                {
                    var_v0_3 = FP_MULTIPLY_PRECISE(var_a1_2, var_a1_2, Q12_SHIFT) + FP_MULTIPLY_PRECISE(var_v1, var_v1, Q12_SHIFT);
                    if (FP_MULTIPLY_PRECISE(temp_s3, temp_s3, Q12_SHIFT) < var_v0_3)
                    {
                        continue;
                    }
                }
            }
        }

        var_v0 = sp34;
        if (var_v0 < 0)
        {
            var_v0 += 3;
        }
        sp34 -= var_v0 >> 2;

        var_v0 = var_s7;
        if (var_v0 < 0)
        {
            var_v0 += 3;
        }
        var_s7 -= var_v0 >> 2;

        var_v0 = var_fp;
        if (var_v0 < 0)
        {
            var_v0 += 3;
        }
        var_fp -= var_v0 >> 2;

        sp34   += sp28;
        var_s7 += sp2C;
        var_fp += sp30;

        sp5C = (temp_s5 + temp_s6) / 2;

        temp_s2 = sp34 - temp_t4_2;
        var_s1  = var_fp - temp_t5;
        temp_s0 = var_s7 - (sp58 + sp5C);

        var_t1 = func_8008A058(func_80080540(temp_s2, 0, var_s1));
        var_t2 = (temp_s6 - temp_s5) / 2;

        if (var_t2 < 0)
        {
            var_t2 = 0;
        }

        for (temp_t3 = 2; (var_t2 < temp_s0 || temp_s0 < -var_t2 || temp_s3 < var_t1) && temp_t3 > 0; temp_t3--)
        {
            if (temp_s3 < var_t1)
            {
                temp_lo_5 = FP_TO(temp_s3, Q12_SHIFT) / var_t1;
                var_t1    = temp_s3;
                temp_s2   = FP_MULTIPLY_PRECISE(temp_lo_5, temp_s2, Q12_SHIFT);
                temp_s0   = FP_MULTIPLY_PRECISE(temp_lo_5, temp_s0, Q12_SHIFT);
                var_s1    = FP_MULTIPLY_PRECISE(temp_lo_5, var_s1, Q12_SHIFT);
            }
            else if (var_t2 < temp_s0)
            {
                temp_lo_5 = FP_TO(var_t2, Q12_SHIFT) / temp_s0;
                temp_s0   = var_t2;
                var_t1    = FP_MULTIPLY_PRECISE(temp_lo_5, var_t1, Q12_SHIFT);
                temp_s2   = FP_MULTIPLY_PRECISE(temp_lo_5, temp_s2, Q12_SHIFT);
                var_s1    = FP_MULTIPLY_PRECISE(temp_lo_5, var_s1, Q12_SHIFT);
            }
            else if (temp_s0 < -var_t2)
            {
                temp_lo_5 = FP_TO(-var_t2, Q12_SHIFT) / temp_s0;
                temp_s0   = -var_t2;
                var_t1    = FP_MULTIPLY_PRECISE(temp_lo_5, var_t1, Q12_SHIFT);
                temp_s2   = FP_MULTIPLY_PRECISE(temp_lo_5, temp_s2, Q12_SHIFT);
                var_s1    = FP_MULTIPLY_PRECISE(temp_lo_5, var_s1, Q12_SHIFT);
            }
        }

        D_800C47B8.vx = temp_t4_2 + temp_s2;
        D_800C47B8.vy = (sp58 + sp5C) + temp_s0;
        D_800C47B8.vz = temp_t5 + var_s1;

        if (func_8008B714(&arg0->chara_0, sp10, &D_800C47B8, arg3))
        {
            sp14 |= sp18;
        }
    }

    arg0->chara_0.field_4C |= sp14;
    return sp14;
}

void DmsHeader_FixOffsets(s_DmsHeader* dmsHdr) // 0x8008C9A0
{
    s_DmsEntry* curEntry;

    if (dmsHdr->isLoaded_0)
    {
        return;
    }

    dmsHdr->isLoaded_0 = true;

    // Add memory address of DMS header to offsets in `dmsHdr`.
    dmsHdr->intervalPtr_8 = (u8*)dmsHdr->intervalPtr_8 + (u32)dmsHdr;
    dmsHdr->characters_18 = (u8*)dmsHdr->characters_18 + (u32)dmsHdr;

    DmsEntry_FixOffsets(&dmsHdr->camera_1C, dmsHdr);

    for (curEntry = dmsHdr->characters_18;
         curEntry < &dmsHdr->characters_18[dmsHdr->characterCount_1];
         curEntry++)
    {
        DmsEntry_FixOffsets(curEntry, dmsHdr);
    }
}

void DmsEntry_FixOffsets(s_DmsEntry* entry, s_DmsHeader* dmsHdr) // 0x8008CA44
{
    entry->keyframes_C.character = (u32)entry->keyframes_C.character + (u32)dmsHdr;
    entry->svectorPtr_8          = (u32)entry->svectorPtr_8 + (u32)dmsHdr;
}

s_DmsInterval* func_8008CA60(volatile s32 unused, s32 idx, s_DmsHeader* dmsHdr) // 0x8008CA60
{
    return &dmsHdr->intervalPtr_8[idx];
}

void Dms_CharacterGetPosRot(VECTOR3* pos, SVECTOR3* rot, const char* charaName, q19_12 time, s_DmsHeader* dmsHdr) // 0x8008CA74
{
    s32 charaIdx;

    charaIdx = Dms_CharacterFindIdxByName(charaName, dmsHdr);
    if (charaIdx == NO_VALUE)
    {
        // Character not found in DMS.
        Math_Vector3Zero(pos);
        Math_SVectorZero(rot);

        Gfx_DebugStringPosition(SCREEN_POSITION_X(15.75f), SCREEN_POSITION_Y(37.5f));

#ifdef DEBUG
        // Code seen in 98-12-16 build.
        Gfx_DebugStringDraw(charName);
        Gfx_DebugStringDraw(" doesn't exist in dms.");
#endif
    }
    else
    {
        Dms_CharacterGetPosRotByIdx(pos, rot, charaIdx, time, dmsHdr);
    }
}

s32 Dms_CharacterFindIdxByName(char* name, s_DmsHeader* dmsHdr) // 0x8008CB10
{
    s32 i;

    for (i = 0; i < dmsHdr->characterCount_1; i++)
    {
        if (!strncmp(name, dmsHdr->characters_18[i].name_4, 4))
        {
            return i;
        }
    }

    return NO_VALUE;
}

void Dms_CharacterGetPosRotByIdx(VECTOR3* pos, SVECTOR3* rot, s32 charaIdx, q19_12 time, s_DmsHeader* dmsHdr) // 0x8008CB90
{
    s_DmsEntry*             charaEntry;
    s32                     keyframePrev;
    s32                     keyframeNext;
    s32                     alpha;
    s_DmsKeyframeCharacter* keyframes;
    s_DmsKeyframeCharacter  curFrame;

    charaEntry = &dmsHdr->characters_18[charaIdx];
    func_8008D1D0(&keyframePrev, &keyframeNext, &alpha, time, charaEntry, dmsHdr);

    keyframes = charaEntry->keyframes_C.character;
    Dms_CharacterKeyframeInterpolate(&curFrame, &keyframes[keyframePrev], &keyframes[keyframeNext], alpha);

    // Set position.
    pos->vx = Q8_TO_Q12(curFrame.position_0.vx + dmsHdr->origin_C.vx);
    pos->vy = Q8_TO_Q12(curFrame.position_0.vy + dmsHdr->origin_C.vy);
    pos->vz = Q8_TO_Q12(curFrame.position_0.vz + dmsHdr->origin_C.vz);

    // Set rotation.
    rot->vx = curFrame.rotation_6.vx;
    rot->vy = curFrame.rotation_6.vy;
    rot->vz = curFrame.rotation_6.vz;
}

void Dms_CharacterKeyframeInterpolate(s_DmsKeyframeCharacter* result, s_DmsKeyframeCharacter* frame0, s_DmsKeyframeCharacter* frame1, s32 alpha) // 0x8008CC98
{
    // Low-precision lerp between positions?
    result->position_0.vx = frame0->position_0.vx + FP_MULTIPLY_PRECISE(frame1->position_0.vx - frame0->position_0.vx, alpha, Q12_SHIFT);
    result->position_0.vy = frame0->position_0.vy + FP_MULTIPLY_PRECISE(frame1->position_0.vy - frame0->position_0.vy, alpha, Q12_SHIFT);
    result->position_0.vz = frame0->position_0.vz + FP_MULTIPLY_PRECISE(frame1->position_0.vz - frame0->position_0.vz, alpha, Q12_SHIFT);

    // Higher-precision lerp between rotations?
    result->rotation_6.vx = Math_LerpFixed12(frame0->rotation_6.vx, frame1->rotation_6.vx, alpha);
    result->rotation_6.vy = Math_LerpFixed12(frame0->rotation_6.vy, frame1->rotation_6.vy, alpha);
    result->rotation_6.vz = Math_LerpFixed12(frame0->rotation_6.vz, frame1->rotation_6.vz, alpha);
}

q3_12 func_8008CDBC(q3_12 angle) // 0x8008CDBC
{
    return (96 * Math_Cos(angle / 2)) / Math_Sin(angle / 2);
}

s32 Dms_CameraGetTargetPos(VECTOR3* posTarget, VECTOR3* lookAtTarget, u16* arg2, q19_12 time, s_DmsHeader* dmsHdr) // 0x8008CE1C
{
    s32                 keyframePrev;
    s32                 keyframeNext;
    s32                 alpha;
    s_DmsKeyframeCamera curFrame;
    s32                 camProjValue;
    s_DmsEntry*         camEntry;

    camEntry = &dmsHdr->camera_1C;

    func_8008D1D0(&keyframePrev, &keyframeNext, &alpha, time, camEntry, dmsHdr);
    camProjValue = Dms_CameraKeyframeInterpolate(&curFrame, &camEntry->keyframes_C.camera[keyframePrev], &camEntry->keyframes_C.camera[keyframeNext], alpha);

    posTarget->vx = Q8_TO_Q12(curFrame.positionTarget_0.vx + dmsHdr->origin_C.vx);
    posTarget->vy = Q8_TO_Q12(curFrame.positionTarget_0.vy + dmsHdr->origin_C.vy);
    posTarget->vz = Q8_TO_Q12(curFrame.positionTarget_0.vz + dmsHdr->origin_C.vz);

    lookAtTarget->vx = Q8_TO_Q12(curFrame.lookAtTarget_6.vx + dmsHdr->origin_C.vx);
    lookAtTarget->vy = Q8_TO_Q12(curFrame.lookAtTarget_6.vy + dmsHdr->origin_C.vy);
    lookAtTarget->vz = Q8_TO_Q12(curFrame.lookAtTarget_6.vz + dmsHdr->origin_C.vz);

    if (arg2 != NULL)
    {
        *arg2 = curFrame.field_C[0];
    }

    // `camProjValue` comes from `curFrame.field_C[1]`, return value is passed to `vcChangeProjectionValue`.
    return camProjValue;
}

bool func_8008CF54(SVECTOR3* rot0, SVECTOR3* rot1) // 0x8008CF54
{
    #define ANGLE_EPSILON FP_ANGLE(360.0f / 16.0f) // 22.5 degrees

    if (ABS(rot0->vx - rot1->vx) > ANGLE_EPSILON ||
        ABS(rot0->vy - rot1->vy) > ANGLE_EPSILON ||
        ABS(rot0->vz - rot1->vz) > ANGLE_EPSILON)
    {
        return true;
    }

    return false;
}

s32 Dms_CameraKeyframeInterpolate(s_DmsKeyframeCamera* result, const s_DmsKeyframeCamera* frame0, const s_DmsKeyframeCamera* frame1, s32 alpha) // 0x8008CFEC
{
    result->positionTarget_0.vx = frame0->positionTarget_0.vx + FP_MULTIPLY_PRECISE(frame1->positionTarget_0.vx - frame0->positionTarget_0.vx, alpha, Q12_SHIFT);
    result->positionTarget_0.vy = frame0->positionTarget_0.vy + FP_MULTIPLY_PRECISE(frame1->positionTarget_0.vy - frame0->positionTarget_0.vy, alpha, Q12_SHIFT);
    result->positionTarget_0.vz = frame0->positionTarget_0.vz + FP_MULTIPLY_PRECISE(frame1->positionTarget_0.vz - frame0->positionTarget_0.vz, alpha, Q12_SHIFT);

    result->lookAtTarget_6.vx = frame0->lookAtTarget_6.vx + FP_MULTIPLY_PRECISE(frame1->lookAtTarget_6.vx - frame0->lookAtTarget_6.vx, alpha, Q12_SHIFT);
    result->lookAtTarget_6.vy = frame0->lookAtTarget_6.vy + FP_MULTIPLY_PRECISE(frame1->lookAtTarget_6.vy - frame0->lookAtTarget_6.vy, alpha, Q12_SHIFT);
    result->lookAtTarget_6.vz = frame0->lookAtTarget_6.vz + FP_MULTIPLY_PRECISE(frame1->lookAtTarget_6.vz - frame0->lookAtTarget_6.vz, alpha, Q12_SHIFT);

    result->field_C[0] = Math_LerpFixed12(frame0->field_C[0], frame1->field_C[0], alpha);
    result->field_C[1] = frame0->field_C[1] + FP_MULTIPLY_PRECISE(frame1->field_C[1] - frame0->field_C[1], alpha, Q12_SHIFT);

    return result->field_C[1];
}

void func_8008D1D0(s32* prevKeyframe, s32* nextKeyframe, q19_12* alpha, q19_12 time, s_DmsEntry* camEntry, s_DmsHeader* dmsHdr) // 0x8008D1D0
{
    s32 prevVal;
    s32 nextVal;

    prevVal = 0;
    nextVal = 0;
    
    switch (Dms_IntervalStateGet(time, dmsHdr))
    {
        case DmsIntervalState_Interpolating:
            prevVal = FP_FROM(time, Q12_SHIFT);
            nextVal = prevVal + 1;
            *alpha  = Q12_FRACT(time);
            break;

        case DmsIntervalState_SingleFrame:
            prevVal = FP_FROM(time, Q12_SHIFT);
            nextVal = prevVal;
            *alpha  = Q12(0.0f);
            break;

        case DmsIntervalState_Ending:
            prevVal = FP_FROM(time, Q12_SHIFT) - 1;
            nextVal = prevVal + 1;
            *alpha  = Q12_FRACT(time) + Q12(1.0f);
            break;
    }

    *prevKeyframe = func_8008D330(prevVal, camEntry);
    *nextKeyframe = func_8008D330(nextVal, camEntry);
}

u32 Dms_IntervalStateGet(q19_12 time, s_DmsHeader* dmsHdr)
{
    s32            frameTime;
    s_DmsInterval* curInterval;

    frameTime = FP_FROM(time, Q12_SHIFT);

    for (curInterval = dmsHdr->intervalPtr_8;
         curInterval < &dmsHdr->intervalPtr_8[dmsHdr->intervalCount_2];
         curInterval++)
    {
        if (frameTime != ((curInterval->startKeyframeIdx_0 + curInterval->frameCount_2) - 1))
        {
            continue;
        }

        if (curInterval->frameCount_2 > 1)
        {
            return DmsIntervalState_Ending;
        }

        return DmsIntervalState_SingleFrame;
    }

    return DmsIntervalState_Interpolating;
}

s32 func_8008D330(s32 arg0, s_DmsEntry* camEntry) // 0x8008D330
{
    s32       keyframeIdx0;
    s32       keyframeIdx1;
    SVECTOR3* curVec;

    keyframeIdx0 = arg0;
    for (curVec = camEntry->svectorPtr_8; curVec < &camEntry->svectorPtr_8[camEntry->svectorCount_2]; curVec++)
    {

        if (arg0 < curVec->vx)
        {
            break;
        }

        if (arg0 <= curVec->vy)
        {
            keyframeIdx0 = curVec->vz;
            break;
        }

        keyframeIdx0 -= curVec->vy - curVec->vx;
    }

    if (keyframeIdx0 >= 0)
    {
        if ((camEntry->keyframeCount_0 - 1) >= keyframeIdx0)
        {
            keyframeIdx1 = keyframeIdx0;
        }
        else
        {
            keyframeIdx1 = camEntry->keyframeCount_0 - 1;
        }
    }
    else
    {
        keyframeIdx1 = 0;
    }

    return keyframeIdx1;
}

s32 Math_LerpFixed12(s16 from, s16 to, q19_12 alpha) // 0x8008D3D4
{
    return FP_ANGLE_NORM_S((s32)(FP_MULTIPLY_PRECISE(FP_ANGLE_NORM_S(to - from), alpha, Q12_SHIFT)) + from);
}

void func_8008D41C(void) // 0x8008D41C
{
    D_800C4818.field_0 = 0;
    D_800C4818.field_1 = 0;
    D_800C4818.field_2 = 0;
    D_800C4818.field_A = 0;
}

void func_8008D438(void) // 0x8008D438
{
    D_800C4818.field_0 = 1;
}

void func_8008D448(void) // 0x8008D448
{
    D_800C4818.field_0 = 0;
}

void func_8008D454(void) // 0x8008D454
{
    D_800C4818.field_1 = 1;
}

void func_8008D464(void) // 0x8008D464
{
    D_800C4818.field_1 = 0;
}

void func_8008D470(s16 arg0, SVECTOR* rot, VECTOR3* pos, s_WaterZone* waterZones) // 0x8008D470
{
    s32          var;
    s_WaterZone* waterZone;

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
        waterZone = Map_WaterZoneGet(Q12_TO_Q4(pos->vx), Q12_TO_Q4(pos->vz), waterZones);
        if (waterZone != NULL)
        {
            func_8008E5B4();

            if (waterZone->isEnabled_0 == true)
            {
                var = waterZone->illumination_2 << 8; // TODO: What's the format?
                func_8008E794(pos, D_800C4818.field_20, var);
                func_8008EA68(rot, pos, var);
            }
        }
    }
}

void func_8008D5A0(VECTOR3* arg0, s16 arg1) // 0x8008D5A0
{
    RECT      sp10;
    bool      cond;
    DR_MOVE*  packet;
    TILE*     tile;
    GsOT_TAG* ot;

    packet         = GsOUT_PACKET_P;
    tile           = GsOUT_PACKET_P + 24;
    GsOUT_PACKET_P = GsOUT_PACKET_P + 40;
    ot             = &g_OrderingTable0[g_ActiveBufferIdx].org[(arg0->vz + 2) >> 3];

    cond = false;
    if (arg0->vx >= (-g_GameWork.gsScreenWidth_588 >> 1) && (g_GameWork.gsScreenWidth_588 >> 1) >= arg0->vx)
    {
        if (arg0->vy >= (-g_GameWork.gsScreenHeight_58A >> 1) && (g_GameWork.gsScreenHeight_58A >> 1) >= arg0->vy &&
            arg0->vz >= 0)
        {
            cond = arg1 > 0x354;
        }
    }

    if (cond)
    {
        SetTile(tile);
        tile->r0 = 0xFF;
        tile->g0 = 0xFF;
        tile->b0 = 0xFF;
        tile->x0 = arg0->vx;
        tile->y0 = arg0->vy;
        tile->w  = 1;
        tile->h  = 1;
        AddPrim(ot, tile);

        sp10.x = arg0->vx + (g_GameWork.gsScreenWidth_588 / 2);
        sp10.y = arg0->vy + (g_GameWork.gsScreenHeight_58A / 2);
        if (g_ActiveBufferIdx == 1)
        {
            sp10.y += 32;
        }
        else
        {
            sp10.y += 256;
        }
    }
    else
    {
        sp10.x = 784;
        sp10.y = 113;
    }

    sp10.h = 8;
    sp10.w = 8;

    SetDrawMove(packet, &sp10, (g_ActiveBufferIdx * 8) + 784, 112);
    AddPrim(g_OrderingTable0[g_ActiveBufferIdx].org + 5, packet);
}

void func_8008D78C(void) // 0x8008D78C
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

s32 func_8008D850(void) // 0x8008D850
{
    s16 rectX;
    RECT rect;
    s_8008D850 unk; 

    rectX = 784;
    if (g_ActiveBufferIdx == 0)
    {
        rectX = 792;
    }

    rect.y = 112;
    rect.w = 2;
    rect.x = rectX;
    rect.h = 1;
    
    DrawSync(SyncMode_Wait);
    StoreImage2(&rect, &unk.field_0);
    DrawSync(SyncMode_Wait);

    return (unk.field_0 & 0x7FFF) == 0x7FFF;
}

s32 func_8008D8C0(s16 x0, s32 x1, s32 x2) // 0x8008D8C0
{
    s32 temp0;
    s32 temp1;
    s32 res;

    // TODO: What Q format are the array values?

    static s32 Y_ARRAY_0[2] = {
        0,
        0x1000
    };

    static s32 Y_ARRAY_1[7] = {
        0x4000,
        0x14CC,
        0x0E66,
        0x0B33,
        0x0800,
        0x0599,
        0x0333
    };

    static s32 Y_ARRAY_2[7] = {
        0x0266,
        0x0333,
        0x0400,
        0x04CC,
        0x0599,
        0x0800,
        0x14CC
    };

    temp0 = vwOresenHokan(&Y_ARRAY_0, ARRAY_SIZE(Y_ARRAY_0), x0, 0, Q8(16.0f));
    temp1 = vwOresenHokan(&Y_ARRAY_1, ARRAY_SIZE(Y_ARRAY_1), x1, Q8(0.8f), Q8(13.0f));
    res   = FP_MULTIPLY(vwOresenHokan(&Y_ARRAY_2, ARRAY_SIZE(Y_ARRAY_2), x2, Q8(3.335f), Q8(7.425f)), // Yucky floats, maybe these aren't distances?
                        FP_MULTIPLY(temp0, temp1, Q12_SHIFT),
                        Q12_SHIFT);

    return (res > Q8(24.0f)) ? Q8(24.0f) : res;
}

// Used by `func_8008D990`.
s16 D_800AFD7C[] = {
    0xF839, 0xF889, 0xFA39, 0xFAE4,
    0xFD56, 0xFDC8, 0xFF56, 0xFFEA,
    0x38, 0x18E, 0x1C7, 0x2AA,
    0x4E3, 0x64F, 0x688, 0x6E3
};

s_FsImageDesc img0 = { .tPage = { 0, 13 } }; // 0x800AFD9C

// TODO: Fix problem with `hack_vcSetWatchTgtXzPos_fix`.
#ifdef NON_MATCHING
void func_8008D990(s32 arg0, s32 arg1, VECTOR3* arg2, s32 arg3, s32 arg4) // 0x8008D990
{
    s32       sp20;
    s32       sp24;
    s32       sp28;
    s32       sp2C;
    s16       temp_v0_7;
    s32       temp_a0;
    s32       temp_a0_4;
    s32       temp_a0_5;
    s32       temp_a1;
    s32       temp_a1_2;
    s32       temp_a1_5;
    s32       temp_a2;
    s32       temp_a2_3;
    s32       temp_a3_2;
    s16       temp_s0_3;
    s32       temp_s0_6;
    s16       temp_s1;
    s32       temp_s2_2;
    s32       temp_t0;
    s32       temp_v0_11;
    s32       temp_v0_13;
    s32       temp_v0_3;
    s32       temp_v0_5;
    s32       temp_v0_9;
    s32       temp_v1_10;
    s32       temp_v1_12;
    s32       temp_v1_4;
    s32       temp_v1_6;
    s32       temp_v1_8;
    s16       var_s3;
    s32       i;
    POLY_FT4* poly;
    GsOT_TAG* temp_s2;
    GsOT_TAG* temp_s7;

    DVECTOR D_8002B2BC[] = {
        { 0x0000, 0xFFFC },
        { 0xFFD1, 0x002B },
        { 0x002F, 0x002B },
        { 0x0000, 0x005A }
    };

    // TODO: 512 is probably a screen constant.
    if (arg2->vx < ((-g_GameWork.gsScreenWidth_588  >> 1) - 512) || ((g_GameWork.gsScreenWidth_588  >> 1) + 512) < arg2->vx ||
        arg2->vy < ((-g_GameWork.gsScreenHeight_58A >> 1) - 512) || ((g_GameWork.gsScreenHeight_58A >> 1) + 512) < arg2->vy)
    {
        return;
    }

    temp_s1   = FP_MULTIPLY(Math_Sin(arg4), Math_Cos(arg3), Q12_SHIFT);
    temp_s0_3 = FP_MULTIPLY(Math_Sin(arg4), Math_Sin(arg3), Q12_SHIFT);

    poly = (POLY_FT4*)GsOUT_PACKET_P;

    temp_s7 = &g_OrderingTable0[g_ActiveBufferIdx].org[1];
    temp_s2 = &g_OrderingTable0[g_ActiveBufferIdx].org[arg2->vz >> 3];

    SetPolyFT4(poly);

    poly->tpage = 0x2C;
    poly->clut  = 0x18C;

    setUV4(poly, 0, 0, 0x3F, 0, 0, 0x3F, 0x3F, 0x3F);

    temp_a1 = (arg1 + 0x3000) >> 2;

    setRGB0(poly, FP_MULTIPLY(temp_a1, 0x28, Q12_SHIFT), FP_MULTIPLY(temp_a1, 0x28, Q12_SHIFT), FP_MULTIPLY(temp_a1, 0x28, Q12_SHIFT));
    setSemiTrans(poly, 1);

    temp_a2   = arg2->vx + FP_MULTIPLY(temp_s1, 5, Q12_SHIFT);
    temp_a0   = FP_MULTIPLY(temp_a1, 0x1E, Q12_SHIFT);
    temp_a1_2 = arg2->vy + FP_MULTIPLY(temp_s0_3, 5, Q12_SHIFT);

    setXY4(poly,
           temp_a2 - temp_a0, temp_a1_2 - temp_a0,
           temp_a2 + temp_a0, temp_a1_2 - temp_a0,
           temp_a2 - temp_a0, temp_a1_2 + temp_a0,
           temp_a2 + temp_a0, temp_a1_2 + temp_a0);

    if (arg0)
    {
        AddPrim(temp_s7, poly);
    }
    else
    {
        if (arg4 > 0x400)
        {
            AddPrim(temp_s2, poly);
        }
        else
        {
            AddPrim(temp_s2 + 7, poly);
        }
    }

    poly++;

    SetPolyFT4(poly);

    poly->tpage = 0x2C;
    poly->clut  = 0x18C;

    setUV4(poly, 0, 0, 0x3F, 0, 0, 0x3F, 0x3F, 0x3F);
    setRGB0(poly, 0x10, 0x10, 0x10);
    setSemiTrans(poly, 1);

    temp_v0_3 = arg2->vx;
    temp_v1_4 = arg2->vy;

    setXY4(poly,
           temp_v0_3 - 11, temp_v1_4 - 11,
           temp_v0_3 + 11, temp_v1_4 - 11,
           temp_v0_3 - 11, temp_v1_4 + 11,
           temp_v0_3 + 11, temp_v1_4 + 11);

    if (arg0)
    {
        AddPrim(temp_s7, poly);
    }
    else
    {
        if (arg4 > 0x400)
        {
            AddPrim(temp_s2, poly);
        }
        else
        {
            AddPrim(temp_s2 + 7, poly);
        }
    }

    poly++;

    SetPolyFT4(poly);
    setSemiTrans(poly, 1);

    temp_v0_5 = FP_MULTIPLY(MIN(arg1 * 2, 0x1000), 0x30, Q12_SHIFT);
    setRGB0(poly, temp_v0_5, temp_v0_5, temp_v0_5);

    poly->tpage = 0x2C;
    poly->clut  = 0x18C;

    setUV4(poly, 0, 0, 0x3F, 0, 0, 0x3F, 0x3F, 0x3F);

    temp_t0   = arg2->vx + FP_MULTIPLY(temp_s1, 9, Q12_SHIFT - 1);
    temp_a2_3 = FP_MULTIPLY((arg1 + 0x3000) >> 2, 0x30, Q12_SHIFT);
    temp_a3_2 = arg2->vy + FP_MULTIPLY(temp_s0_3, 9, Q12_SHIFT - 1);

    setXY4(poly,
           temp_t0 - temp_a2_3, temp_a3_2 - temp_a2_3,
           temp_t0 + temp_a2_3, temp_a3_2 - temp_a2_3,
           temp_t0 - temp_a2_3, temp_a3_2 + temp_a2_3,
           temp_t0 + temp_a2_3, temp_a3_2 + temp_a2_3);

    AddPrim(temp_s7, poly);
    poly++;

    if (!arg1)
    {
        GsOUT_PACKET_P = (PACKET*)poly;
        return;
    }

    sp20 = ((-arg4 >> 1) + ((arg2->vx + arg2->vy) * 4)) + 0x2AA;
    sp24 = (arg2->vz * 4) + ((arg2->vx + arg2->vy) * 16);

    for (i = 0; i < 16; i++)
    {
        temp_v0_7 = D_800AFD7C[i] + sp20;

        var_s3 = FP_MULTIPLY((Math_Cos(temp_v0_7 - arg3) + 0x1B33), (Math_Cos((temp_v0_7 * 0xC) + sp24) + 0x1000) >> 1, Q12_SHIFT);
        var_s3 = MIN(var_s3, 0x1800);

        temp_s1   = Math_Sin(temp_v0_7);
        temp_s0_3 = Math_Cos(temp_v0_7);

        SetPolyFT4(poly);

        poly->tpage = 0x2C;
        poly->clut  = 0x14C;

        setUV4(poly, 0x20, 0x40, 0x3F, 0x40, 0x20, 0x5F, 0x3F, 0x5F);
        setSemiTrans(poly, 1);

        temp_v0_9 = (arg1 * var_s3) >> 0x12;
        setRGB0(poly, temp_v0_9, temp_v0_9, temp_v0_9);

        temp_a0_4 = arg2->vy;
        temp_v1_6 = arg2->vx;

        setXY4(poly,
               temp_v1_6 + FP_FROM(D_8002B2BC[0].vx * temp_s0_3 - D_8002B2BC[0].vy * temp_s1, Q12_SHIFT),
               temp_a0_4 + FP_FROM(D_8002B2BC[0].vx * temp_s1 + D_8002B2BC[0].vy * temp_s0_3, Q12_SHIFT),
               temp_v1_6 + FP_FROM(D_8002B2BC[1].vx * temp_s0_3 - D_8002B2BC[1].vy * temp_s1, Q12_SHIFT),
               temp_a0_4 + FP_FROM(D_8002B2BC[1].vx * temp_s1 + D_8002B2BC[1].vy * temp_s0_3, Q12_SHIFT),
               temp_v1_6 + FP_FROM(D_8002B2BC[2].vx * temp_s0_3 - D_8002B2BC[2].vy * temp_s1, Q12_SHIFT),
               temp_a0_4 + FP_FROM(D_8002B2BC[2].vx * temp_s1 + D_8002B2BC[2].vy * temp_s0_3, Q12_SHIFT),
               temp_v1_6 + FP_FROM(D_8002B2BC[3].vx * temp_s0_3 - D_8002B2BC[3].vy * temp_s1, Q12_SHIFT),
               temp_a0_4 + FP_FROM(D_8002B2BC[3].vx * temp_s1 + D_8002B2BC[3].vy * temp_s0_3, Q12_SHIFT));

        addPrim(temp_s7, poly);
        poly++;
    }

    sp28 = 0x3F;
    sp2C = 0x40;

    SetPolyFT4(poly);

    setRGB0(poly, FP_MULTIPLY(arg1, 32, Q12_SHIFT), FP_MULTIPLY(arg1, 0x30, Q12_SHIFT), FP_MULTIPLY(arg1, 32, Q12_SHIFT));

    poly->tpage = 0x2C;
    poly->clut  = 0x1CC;

    setUV4(poly, 0x40, 0, 0x7F, 0, 0x40, 0x3F, 0x7F, 0x3F);
    setSemiTrans(poly, 1);

    temp_s2_2 = (arg1 + 0x3000) >> 2;
    temp_a1_5 = FP_MULTIPLY(temp_s2_2, 0x10, Q12_SHIFT);
    temp_a0_5 = FP_MULTIPLY(arg2->vx, 0x333, Q12_SHIFT);
    setSemiTrans(poly, 1);
    temp_v1_8 = FP_MULTIPLY(arg2->vy, 0x333, Q12_SHIFT);

    setXY4(poly,
           temp_a0_5 - temp_a1_5, temp_v1_8 - temp_a1_5,
           temp_a0_5 + temp_a1_5, temp_v1_8 - temp_a1_5,
           temp_a0_5 - temp_a1_5, temp_v1_8 + temp_a1_5,
           temp_a0_5 + temp_a1_5, temp_v1_8 + temp_a1_5);

    addPrim(temp_s7, poly);
    poly++;

    SetPolyFT4(poly);

    temp_s0_6 = FP_MULTIPLY(arg1, 0x18, Q12_SHIFT);
    setRGB0(poly, ((u32)arg1 * 7) >> 9, ((u32)arg1 * 0x13) >> 0xB, temp_s0_6);

    poly->tpage = 0x2C;
    poly->clut  = 0x1CC;

    setUV4(poly, 0x40, 0, 0x7F, 0, 0x40, 0x3F, 0x7F, 0x3F);
    setSemiTrans(poly, 1);

    temp_v1_10 = FP_MULTIPLY(arg2->vx, -0x4CC, Q12_SHIFT);
    temp_v0_11 = FP_MULTIPLY(arg2->vy, -0x4CC, Q12_SHIFT);

    setXY4(poly,
           temp_v1_10 - FP_MULTIPLY(temp_s2_2, 0x1C, Q12_SHIFT), temp_v0_11 - FP_MULTIPLY(temp_s2_2, 0x1C, Q12_SHIFT),
           temp_v1_10 + FP_MULTIPLY(temp_s2_2, 0x1C, Q12_SHIFT), temp_v0_11 - FP_MULTIPLY(temp_s2_2, 0x1C, Q12_SHIFT),
           temp_v1_10 - FP_MULTIPLY(temp_s2_2, 0x1C, Q12_SHIFT), temp_v0_11 + FP_MULTIPLY(temp_s2_2, 0x1C, Q12_SHIFT),
           temp_v1_10 + FP_MULTIPLY(temp_s2_2, 0x1C, Q12_SHIFT), temp_v0_11 + FP_MULTIPLY(temp_s2_2, 0x1C, Q12_SHIFT));

    addPrim(temp_s7, poly);
    poly++;

    SetPolyFT4(poly);

    setRGB0(poly, (u32)arg1 >> 6, temp_s0_6, ((u32)arg1 * 0x2F) >> 11);

    poly->tpage = 0x4C;
    poly->clut  = 0x18C;

    setUV4(poly, 0, 0, 0x3F, 0, 0, 0x3F, 0x3F, 0x3F);
    setSemiTrans(poly, 1);

    temp_v0_13 = arg2->vx;
    temp_v1_12 = arg2->vy;

    setXY4(poly,
           temp_v0_13 - 10, temp_v1_12 - 10,
           temp_v0_13 + 10, temp_v1_12 - 10,
           temp_v0_13 - 10, temp_v1_12 + 10,
           temp_v0_13 + 10, temp_v1_12 + 10);

    addPrim(temp_s7, poly);
    poly++;
    GsOUT_PACKET_P = (PACKET*)poly;
}
#else
INCLUDE_ASM("asm/bodyprog/nonmatchings/bodyprog_80085D78", func_8008D990); // 0x8008D990
#endif

void func_8008E4EC(s_LmHeader* lmHdr) // 0x8008E4EC
{
    func_80056504(lmHdr, D_8002B2CC.str, &img0, 1);
}

s_WaterZone* Map_WaterZoneGet(q27_4 posX, q27_4 posZ, s_WaterZone* waterZones)
{
    s_WaterZone* curWaterZone;

    if (waterZones == NULL)
    {
        return NULL;
    }

    for (curWaterZone = waterZones; curWaterZone->isEnabled_0; curWaterZone++)
    {
        if (posX >= curWaterZone->minX_4 && posX < curWaterZone->maxX_6 &&
            posZ >= curWaterZone->minZ_8 && posZ < curWaterZone->maxZ_A)
        {
            return curWaterZone;
        }
    }

    return NULL;
}

void func_8008E5B4(void) // 0x8008E5B4
{
    typedef struct
    {
        GsOT_TAG  tag_0;
        DR_AREA   area_4;
        DR_OFFSET offset_10;
        POLY_FT4  poly_1C[2];
        DR_ENV    env_6C;
    } s_func_8008E5B4;

    static RECT D_800AFDA4 = { 832, 224, 32, 32 };
    static s32  D_800AFDAC = 0;

    DRAWENV          drawEnv;
    s32              temp_v0;
    s_func_8008E5B4* packet;

    GetDrawEnv(&drawEnv);
    packet         = GsOUT_PACKET_P;
    GsOUT_PACKET_P = &packet[1];

    setlen(packet, 0);
    TermPrim(packet);

    SetDrawArea(&packet->area_4, &D_800AFDA4);
    SetDrawOffset(&packet->offset_10, (u16*)&D_800AFDA4);
    SetDrawEnv(&packet->env_6C, &drawEnv);

    if (g_DeltaTime0 != Q12(0.0f))
    {
        D_800AFDAC++;
    }

    setRGBC0(&packet->poly_1C[1], 128, 128, 128, 0x0);
    setRGBC0(&packet->poly_1C[0], 128, 128, 128, 0x0);

    setPolyFT4(&packet->poly_1C[0]);
    setPolyFT4(&packet->poly_1C[1]);
    setSemiTrans(&packet->poly_1C[1], true);

    packet->poly_1C[1].tpage = 45;
    packet->poly_1C[0].tpage = 45;

    setXY0Fast(&packet->poly_1C[1], 0, 0);
    setXY0Fast(&packet->poly_1C[0], 0, 0);
    setXY1Fast(&packet->poly_1C[1], 32, 0);
    setXY1Fast(&packet->poly_1C[0], 32, 0);
    setXY2Fast(&packet->poly_1C[1], 0, 32);
    setXY2Fast(&packet->poly_1C[0], 0, 32);
    setXY3Fast(&packet->poly_1C[1], 32, 32);
    setXY3Fast(&packet->poly_1C[0], 32, 32);

    packet->poly_1C[1].clut = 14;
    packet->poly_1C[0].clut = 14;

    temp_v0               = (D_800AFDAC >> 1) & 0x1F;
    packet->poly_1C[0].u0 = 0;
    packet->poly_1C[0].v0 = temp_v0;
    packet->poly_1C[0].u1 = 32;
    packet->poly_1C[0].v1 = temp_v0;
    packet->poly_1C[0].u2 = 0;
    packet->poly_1C[0].v2 = temp_v0 + 32;
    packet->poly_1C[0].u3 = 32;
    packet->poly_1C[0].v3 = temp_v0 + 32;

    temp_v0               = ((D_800AFDAC + 1) >> 2) & 0x1F;
    packet->poly_1C[1].u0 = temp_v0;
    packet->poly_1C[1].v0 = 8;
    packet->poly_1C[1].u1 = temp_v0 + 32;
    packet->poly_1C[1].v1 = 8;
    packet->poly_1C[1].u2 = temp_v0;
    packet->poly_1C[1].v2 = 40;
    packet->poly_1C[1].u3 = temp_v0 + 32;
    packet->poly_1C[1].v3 = 40;

    AddPrim(packet, &packet->env_6C);
    AddPrim(packet, &packet->poly_1C[1]);
    AddPrim(packet, &packet->poly_1C[0]);
    AddPrim(packet, &packet->area_4);
    AddPrim(packet, &packet->offset_10);

    DrawOTag((u32*)packet);
}

void func_8008E794(VECTOR3* posXz, q3_12 angle, q19_12 posY) // 0x8008E794
{
    VECTOR    sp10;
    VECTOR    sp20; // Q23.8
    MATRIX    sp30;
    s32       sp50;
    q19_12    angle0;
    q20_12    sinAngle0;
    POLY_FT4* poly;

    static SVECTOR svec0 = {};

    memset(&sp20, 0, 16);
    sp20.vx = Q12_TO_Q8(posXz->vx);
    sp20.vy = Q12_TO_Q8(posY * 2) - Q12_TO_Q8(posXz->vy);
    sp20.vz = Q12_TO_Q8(posXz->vz);
    sp10    = sp20;

    sp30 = GsWSMATRIX;
    ApplyMatrixLV(&GsWSMATRIX, &sp10, &sp30.t);
    sp30.t[0] += GsWSMATRIX.t[0];
    sp30.t[1] += GsWSMATRIX.t[1];
    sp30.t[2] += GsWSMATRIX.t[2];
    SetTransMatrix(&sp30);

    if ((RotTransPers(&svec0, &sp20, &sp50, &sp50) * 4) >= 128)
    {
        poly = GsOUT_PACKET_P;
        SetPolyFT4(poly);
        setSemiTrans(poly, true);

        angle0 = angle - FP_ANGLE(40.0f);
        if (angle0 > FP_ANGLE(90.0f))
        {
            angle0 = FP_ANGLE(90.0f);
        }

        if (Math_Sin(angle0) >= Q12(0.0f))
        {
            sinAngle0 = Math_Sin(angle0);
        }
        else
        {
            sinAngle0 = Q12(0.0f);
        }

        poly->r0    = sinAngle0 >> 6;
        poly->g0    = (sinAngle0 * 7) >> 9;
        poly->b0    = (sinAngle0 * 5) >> 9;
        poly->tpage = 45;
        poly->clut  = 78;
        poly->u0    = 64;
        poly->u1    = 64;
        poly->v0    = 31;
        poly->v1    = 0;
        poly->u2    = 127;
        poly->v2    = 31;
        poly->u3    = 127;
        poly->v3    = 0;
        poly->x0    = sp20.vx - 24;
        poly->y0    = ((u32)sp20.vx >> 16) - 48; // Are these hacks? Can't think of any other solutions.
        poly->x1    = sp20.vx + 24;
        poly->y1    = ((u32)sp20.vx >> 16) - 48;
        poly->x2    = sp20.vx - 24;
        poly->y2    = ((u32)sp20.vx >> 16) + 48;
        poly->x3    = sp20.vx + 24;
        poly->y3    = ((u32)sp20.vx >> 16) + 48;

        AddPrim(g_OrderingTable0[g_ActiveBufferIdx].org + 641, poly);
        GsOUT_PACKET_P = poly + 1;
    }
}

void func_8008EA68(SVECTOR* arg0, VECTOR3* posXz, q19_12 posY) // 0x8008EA68
{
    typedef struct
    {
        POLY_G4 g4[2];
        POLY_G3 g3[2];
    } s_func_8008EA68;

    SVECTOR          sp28[5];
    GsCOORDINATE2    sp50;
    MATRIX           spA0;
    SVECTOR          spC0; // Q3.8 | Rotation?
    s32              spC8;
    s32              spCC;
    s16              angle1;
    q3_12            angle;
    q19_12           angle0;
    s32              temp_s0_2;
    s16              temp_s1;
    s32              temp_s2;
    s32              temp_v0_2;
    s32              temp_v0_3;
    s32              temp_v1_2;
    s32              i;
    s32              temp;
    PACKET*          packet;
    s_func_8008EA68* poly;
    GsOT_TAG*        spD0;
    GsOT_TAG*        spD4;
    GsOT_TAG*        ot;

    ot         = g_OrderingTable0[g_ActiveBufferIdx].org;
    sp50.flg   = false;
    sp50.coord = GsIDMATRIX;

    spD0 = &ot[641];
    spD4 = &ot[639];

    angle1  = ratan2(arg0->vx, arg0->vz);
    sp50.coord.m[0][0] =  Math_Cos(angle1);
    sp50.coord.m[2][2] =  Math_Cos(angle1);
    sp50.coord.m[0][2] =  Math_Sin(angle1);
    sp50.coord.m[2][0] = -Math_Sin(angle1);

    sp50.super = NULL;
    sp50.coord.t[0] = Q12_TO_Q8(posXz->vx);
    sp50.coord.t[1] = Q12_TO_Q8(posY);
    sp50.coord.t[2] = Q12_TO_Q8(posXz->vz);

    func_80049AF8(&sp50, &spA0);
    SetRotMatrix(&spA0);
    SetTransMatrix(&spA0);

    spC0.vx = Q8(0.0f);
    spC0.vy = Q8(0.0f);
    spC0.vz = Q8(0.7f);
    RotTransPers(&spC0.vx, &spC8, &spCC, &spCC);

    packet     = GsOUT_PACKET_P;
    sp28[1].vy = 0;
    sp28[0].vy = 0;
    sp28[3].vy = 0x33;
    sp28[2].vy = 0x33;

    for (i = 0, angle = 0; i < 8; i++, angle += FP_ANGLE(45.0f))
    {
        temp_s1   = Math_Sin(angle);
        angle0    = angle + FP_ANGLE(45.0f);
        temp_s2   = Math_Cos(angle);
        temp_s0_2 = Math_Sin(angle0);
        temp_v0_2 = Math_Cos(angle0);

        sp28[0].vx = FP_MULTIPLY((s16)temp_s1, 0x33, 10);
        sp28[0].vz = FP_MULTIPLY((s16)temp_s2, 0x33, 10) + 0x133;
        sp28[1].vx = FP_MULTIPLY((s16)temp_s0_2, 0x33, 10);
        sp28[1].vz = FP_MULTIPLY((s16)temp_v0_2, 0x33, 10) + 0x133;
        sp28[2].vx = FP_MULTIPLY((s16)temp_s1, 0x233, Q12_SHIFT);
        sp28[2].vz = FP_MULTIPLY((s16)temp_s2, 0x233, Q12_SHIFT) + 0x180;
        sp28[3].vx = FP_MULTIPLY((s16)temp_s0_2, 0x233, Q12_SHIFT);
        sp28[3].vz = FP_MULTIPLY((s16)temp_v0_2, 0x233, Q12_SHIFT) + 0x180;

        poly = packet;

        temp = 0;

        *(s32*)&poly->g4[0].r0 = 0xC1214;
        *(s32*)&poly->g4[0].r1 = 0xC1214;
        *(s32*)&poly->g4[0].r3 = 0x40404;
        *(s32*)&poly->g4[0].r2 = 0x40404;

        *(s32*)&poly->g3[0].r0 = 0xC1618;
        *(s32*)&poly->g3[0].r2 = 0xC1214;
        *(s32*)&poly->g3[0].r1 = 0xC1214;

        *(s32*)&poly->g4[1].r0 = 0x40804;
        *(s32*)&poly->g4[1].r1 = 0x40804;
        *(s32*)&poly->g4[1].r3 = PACKED_COLOR(0, 0, 0, 0x0);
        *(s32*)&poly->g4[1].r2 = PACKED_COLOR(0, 0, 0, 0x0);

        *(s32*)&poly->g3[1].r0 = 0x40808;
        *(s32*)&poly->g3[1].r2 = 0x40804;
        *(s32*)&poly->g3[1].r1 = 0x40804;

        setPolyG4(&poly->g4[0]);
        setPolyG3(&poly->g3[0]);
        setPolyG4(&poly->g4[1]);
        setSemiTrans(&poly->g4[1], true);
        setPolyG3(&poly->g3[1]);
        setSemiTrans(&poly->g3[1], true);

        *(s32*)&poly->g3[1].x0 = *(s32*)&spC8;
        *(s32*)&poly->g3[0].x0 = *(s32*)&spC8;

        RotTransPers4(&sp28[0], &sp28[1], &sp28[2], &sp28[3], &poly->g4[0].x0, &poly->g4[0].x1, &poly->g4[0].x2, &poly->g4[0].x3, &spCC, &spCC);

        temp_v0_3 = *(s32*)&poly->g4[0].x0;
        temp_v1_2 = *(s32*)&poly->g4[0].x1;

        *(s32*)&poly->g3[1].x1 = temp_v0_3;
        *(s32*)&poly->g3[0].x1 = temp_v0_3;
        *(s32*)&poly->g4[1].x0 = temp_v0_3;

        *(s32*)&poly->g3[1].x2 = temp_v1_2;
        *(s32*)&poly->g3[0].x2 = temp_v1_2;
        *(s32*)&poly->g4[1].x1 = temp_v1_2;

        *(s32*)&poly->g4[1].x2 = *(s32*)&poly->g4[0].x2;
        *(s32*)&poly->g4[1].x3 = *(s32*)&poly->g4[0].x3;

        AddPrim(spD0, &poly->g4[0]);
        AddPrim(spD0, &poly->g3[0]);
        AddPrim(spD4, &poly->g4[1]);
        AddPrim(spD4, &poly->g3[1]);

        poly++;
        packet = poly;
    }

    SetDrawTPage((DR_TPAGE*)packet, temp, 1, 32);
    AddPrim(spD4, packet);
    packet        += sizeof(DR_TPAGE);
    GsOUT_PACKET_P = packet;
}

void func_8008EF18(void) {} // 0x8008EF18

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80085D78", hack_vcSetWatchTgtXzPos_fix);

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80085D78", D_8002B2BC);

INCLUDE_RODATA("asm/bodyprog/nonmatchings/bodyprog_80085D78", D_8002B2CC);
