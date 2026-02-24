#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/fsqueue.h"

VECTOR3 D_800C4640[2][8];
q3_12 D_800C4700[8];
q19_12 D_800C4710[6];

// ========================================
// EVENT AND INTERACTIONS RELATED
// ========================================

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
    g_SysWork.timer_2C += g_DeltaTimeRaw;
    if (g_MapOverlayHeader.playerMoveDistIsZero_EC() != NULL || g_SysWork.timer_2C > Q12(1.0f))
    {
        SysWork_StateStepIncrement(0);
    }
}

void SysWork_StateStepIncrementDelayed(q19_12 delay, bool reset) // 0x80085E6C
{
    g_SysWork.timer_2C += g_DeltaTimeRaw;
    if (delay < g_SysWork.timer_2C)
    {
        func_80085D78(reset);
    }
}

void func_80085EB8(u32 arg0, s_SubCharacter* chara, s32 arg2, bool reset) // 0x80085EB8
{
    s32 keyframeState; // TODO: Not final name, only an indication.

    switch (arg0)
    {
        case 0:
            if (chara == &g_SysWork.playerWork_4C.player_0)
            {
                g_MapOverlayHeader.func_D4(arg2);
            }
            else
            {
                g_MapOverlayHeader.func_124(chara);
            }
            break;

        case 1:
            if (chara == &g_SysWork.playerWork_4C.player_0)
            {
                keyframeState = g_MapOverlayHeader.func_E8(chara);
                if (keyframeState == 1)
                {
                    func_80085D78(reset);
                }
            }
            else
            {
                keyframeState = g_MapOverlayHeader.func_138(chara);
                if (keyframeState == 1)
                {
                    func_80085D78(reset);
                }
            }
            break;

        case 2:
            if (chara == &g_SysWork.playerWork_4C.player_0)
            {
                g_MapOverlayHeader.playerAnimLock_DC();
            }
            else
            {
                g_MapOverlayHeader.func_12C(chara);
            }
            break;

        case 3:
            if (chara == &g_SysWork.playerWork_4C.player_0)
            {
                g_MapOverlayHeader.playerAnimUnlock_E4(chara, arg2);
            }
            else
            {
                g_MapOverlayHeader.func_134(chara);
            }
            break;

        case 4:
            if (chara == &g_SysWork.playerWork_4C.player_0)
            {
                g_MapOverlayHeader.playerAnimUnlock_E4(chara, arg2);
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
                        g_SysWork.flags_22A4 |= SysFlag2_3;
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
        D_800C4640[idx0][idx1].vx = g_SysWork.playerWork_4C.player_0.position_18.vx + offsetOrPosX;
        D_800C4640[idx0][idx1].vy = g_SysWork.playerWork_4C.player_0.position_18.vy;
        D_800C4640[idx0][idx1].vz = g_SysWork.playerWork_4C.player_0.position_18.vz + offsetOrPosZ;

        D_800C4700[idx0] = angleY;
    }
    else if (isPos == true)
    {
        D_800C4640[idx0][idx1].vx = offsetOrPosX;
        D_800C4640[idx0][idx1].vy = g_SysWork.playerWork_4C.player_0.position_18.vy;
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
    if (g_MapOverlayHeader.func_13C(chara, arg1, &D_800C4640[1][0], D_800C4700[1], arg2) == 1)
    {
        func_80085D78(reset);
    }
}

void func_8008677C(s_SubCharacter* chara, s32 arg1, s32 arg2) // 0x8008677C
{
    g_MapOverlayHeader.func_13C(chara, arg1, &D_800C4640[1][0], D_800C4700[1], arg2);
}

void func_800867B4(s32 state, s32 paperMapFileIdx) // 0x800867B4
{
    switch (state)
    {
        case 0:
            DrawSync(SyncMode_Wait);
            StoreImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(SyncMode_Wait);

            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[paperMapFileIdx], FS_BUFFER_2, &g_PaperMapImg);
            Fs_QueueStartReadTim(FILE_TIM_MR_0TOWN_TIM + g_PaperMapMarkingFileIdxs[paperMapFileIdx], FS_BUFFER_1, &g_PaperMapMarkingAtlasImg);

            Screen_Init(SCREEN_WIDTH, true);
            GsSwapDispBuff();
            Fs_QueueWaitForEmpty();
            break;

        case 1:
            Gfx_BackgroundSpriteDraw(&g_PaperMapImg);
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
    D_800C4710[idx] += g_DeltaTime;
    D_800C4710[idx]  = (arg1 < D_800C4710[idx]) ? arg1 : D_800C4710[idx];

    return (arg0 * D_800C4710[idx]) / arg1;
}

s32 func_8008694C(s32 arg0, s16 arg1, s16 arg2, s32 arg3, s32 idx)
{
    D_800C4710[idx] += g_DeltaTime;
    D_800C4710[idx] = (arg3 < D_800C4710[idx]) ? arg3 : D_800C4710[idx];
    return Q12_MULT(arg0, Math_Sin(arg1 + ((arg2 * D_800C4710[idx]) / arg3)));
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
        SD_Call(soundsIdxs[*soundIdx]);
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
    if (angularAccelX == Q12_ANGLE(0.0f))
    {
        camLookAtMoveParams.ang_accel_x = deflt_watch_mv_prm.ang_accel_x;
    }
    else
    {
        camLookAtMoveParams.ang_accel_x = angularAccelX;
    }

    // Set angular acceleration on Y axis.
    if (angularAccelY == Q12_ANGLE(0.0f))
    {
        camLookAtMoveParams.ang_accel_y = deflt_watch_mv_prm.ang_accel_y;
    }
    else
    {
        camLookAtMoveParams.ang_accel_y = angularAccelY;
    }

    // Set max angular speed on X axis.
    if (angularSpeedXMax == Q12_ANGLE(0.0f))
    {
        camLookAtMoveParams.max_ang_spd_x = deflt_watch_mv_prm.max_ang_spd_x;
    }
    else
    {
        camLookAtMoveParams.max_ang_spd_x = angularSpeedXMax;
    }

    // Set max angular speed on Y axis.
    if (angularSpeedYMax == Q12_ANGLE(0.0f))
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

    if (!(g_SysWork.flags_22A4 & SysFlag2_5))
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
            g_DeltaTime = Q12(0.0f);
        }
    }

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            g_MapOverlayHeader.playerControlFreeze_C8();
            func_8005DC1C(sfxId, sfxPos, Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(1);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(0.2f), true);
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, mapMsgIdx, 0, 0, 0, true);
            break;

        default:
            g_MapOverlayHeader.playerControlUnfreeze_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_8008716C(e_FsFile texFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1) // 0x8008716C
{
    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            g_MapOverlayHeader.playerControlFreeze_C8();
            SysWork_StateStepIncrementAfterFade(0, true, 0, fadeTimestep0, false);
            SysWork_StateStepIncrement(1);

        case 1:
            func_800862F8(7, texFileIdx, true);
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
            g_MapOverlayHeader.playerControlUnfreeze_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapMsg_DisplayWithTexture(e_FsFile texFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx) // 0x80087360
{
    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            g_MapOverlayHeader.playerControlFreeze_C8();
            SysWork_StateStepIncrementAfterFade(0, true, 0, fadeTimestep0, false);
            SysWork_StateStepIncrement(1);

        case 1:
            func_800862F8(7, texFileIdx, true);
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
            g_MapOverlayHeader.playerControlUnfreeze_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapMsg_DisplayWithTexture1(e_FsFile texFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx0, s32 mapMsgIdx1) // 0x80087540
{
    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            g_MapOverlayHeader.playerControlFreeze_C8();
            SysWork_StateStepIncrementAfterFade(0, true, 0, fadeTimestep0, false);
            SysWork_StateStepIncrement(1);

        case 1:
            func_800862F8(7, texFileIdx, true);
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
            g_MapOverlayHeader.playerControlUnfreeze_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_ItemTake(e_InventoryItemId itemId, s32 itemCount, e_EventFlag eventFlagIdx, s32 mapMsgIdx) // 0x800877B8
{
    s32 i            = itemId;
    s32 mapMsgIdxCpy = mapMsgIdx;

    if (!(g_SysWork.flags_22A4 & SysFlag2_5))
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
            g_DeltaTime = Q12(0.0f);
        }
    }

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0: // Freeze player and start loading item model.
            g_MapOverlayHeader.playerControlFreeze_C8();
            func_80086470(0, itemId, 0, false);

            SysWork_StateStepIncrement(1);

        case 1: // Load model.
            func_80086470(1, itemId, 0, true);
            break;

        case 2:
            // `Gfx_PickupItemAnimate` increases model scale and returns `false`, then starts rotating it and returns `true`.
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

            g_MapOverlayHeader.playerControlUnfreeze_CC(0);
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
    static const RECT RECT = {
        SCREEN_POSITION_X(100.0f), 256,
        SCREEN_WIDTH / 2, SCREEN_HEIGHT
    };

    s32 mapFlagIdxCpy;

    g_DeltaTime   = Q12(0.0f);
    mapFlagIdxCpy = mapFlagIdx;

    switch (g_SysWork.sysStateStep_C[1])
    {
        case 0:
            g_MapOverlayHeader.playerControlFreeze_C8();
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[mapFlagIdx]);
            SysWork_StateStepIncrement(1);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), true);
            break;

        case 2:
            DrawSync(SyncMode_Wait);
            StoreImage(&RECT, IMAGE_BUFFER);
            DrawSync(SyncMode_Wait);
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[mapFlagIdx], FS_BUFFER_2, &g_PaperMapImg);
            Screen_Init(SCREEN_WIDTH, true);

            g_IntervalVBlanks = 1;

            GsSwapDispBuff();
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Fs_QueueWaitForEmpty();

            SysWork_StateStepIncrement(1);

        case 3:
            g_BackgroundColor = 88;

            Gfx_BackgroundSpriteDraw(&g_PaperMapImg);
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

            Gfx_BackgroundSpriteDraw(&g_PaperMapImg);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), true);
            break;

        default:
            LoadImage(&RECT, IMAGE_BUFFER);
            DrawSync(SyncMode_Wait);
            Screen_Init(SCREEN_WIDTH, false);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);

            g_MapOverlayHeader.playerControlUnfreeze_CC(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}
