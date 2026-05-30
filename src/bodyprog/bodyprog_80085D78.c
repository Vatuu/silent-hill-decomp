#include "game.h"
#include "inline_no_dmpsx.h"

#include <psyq/libpad.h>
#include <psyq/strings.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/events/bodyprog_data_800A99B4.h"
#include "bodyprog/events/events_util.h"
#include "bodyprog/screen/screen_data.h"
#include "bodyprog/screen/screen_draw.h"
#include "bodyprog/screen/background_draw.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound/sound_system.h"
#include "main/fsqueue.h"

VECTOR3 D_800C4640[2][8];
q3_12   D_800C4700[8];
q19_12  D_800C4710[6];

// ========================================
// EVENT AND INTERACTIONS RELATED
// ========================================

void Event_SysStateStepIncrement(bool incSubStep) // 0x80085D78
{
    if (incSubStep)
    {
        SysWork_StateStepIncrement(1);
    }
    else
    {
        SysWork_StateStepIncrement(0);
    }
}

void Event_SysStateStepSet(bool setSubStep, s32 sysStateStep) // 0x80085DC0
{
    if (setSubStep)
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
    if (g_MapOverlayHdr.playerMoveDistIsZero() || g_SysWork.timer_2C > Q12(1.0f))
    {
        SysWork_StateStepIncrement(0);
    }
}

void Event_SysStateStepIncrementDelayed(q19_12 delay, bool incSubStep) // 0x80085E6C
{
    g_SysWork.timer_2C += g_DeltaTimeRaw;
    if (delay < g_SysWork.timer_2C)
    {
        Event_SysStateStepIncrement(incSubStep);
    }
}

void Event_CharaAnimCommandExecute(e_CharaAnimCommand cmd, s_SubCharacter* chara, s32 cmdArg, bool incSubStep) // 0x80085EB8
{
    s32 playbackState; // TODO: Not final name, only an indication.

    switch (cmd)
    {
        case CharaAnimCommand_SetState:
            if (chara == &g_SysWork.playerWork.player)
            {
                g_MapOverlayHdr.playerAnimStateSet(cmdArg);
            }
            else
            {
                g_MapOverlayHdr.charaAnimStateSet(chara, cmdArg);
            }
            break;

        case CharaAnimCommand_AwaitAnimEnd:
            if (chara == &g_SysWork.playerWork.player)
            {
                playbackState = g_MapOverlayHdr.playerAnimPlaybackStateGet();
                if (playbackState == AnimPlaybackState_End)
                {
                    Event_SysStateStepIncrement(incSubStep);
                }
            }
            else
            {
                playbackState = g_MapOverlayHdr.charaAnimPlaybackStateGet(chara);
                if (playbackState == AnimPlaybackState_End)
                {
                    Event_SysStateStepIncrement(incSubStep);
                }
            }
            break;

        case CharaAnimCommand_AnimLock:
            if (chara == &g_SysWork.playerWork.player)
            {
                g_MapOverlayHdr.playerAnimLock();
            }
            else
            {
                g_MapOverlayHdr.charaAnimLock(chara);
            }
            break;

        case CharaAnimCommand_AnimUnlock:
            if (chara == &g_SysWork.playerWork.player)
            {
                g_MapOverlayHdr.playerAnimUnlock();
            }
            else
            {
                g_MapOverlayHdr.charaAnimUnlock(chara);
            }
            break;

        case CharaAnimCommand_AnimReset:
            if (chara == &g_SysWork.playerWork.player)
            {
                g_MapOverlayHdr.playerAnimUnlock();
                g_MapOverlayHdr.playerAnimReset();
            }
            else
            {
                g_MapOverlayHdr.charaAnimReset(chara);
            }
            break;
    }
}

void Event_SysStateBranchOnFlag(e_EventFlag eventFlagIdx, s32 stepTrue, s32 stepFalse, bool setSubStep) // 0x8008605C
{
    if (!Savegame_EventFlagGet(eventFlagIdx))
    {
        Event_SysStateStepSet(setSubStep, stepFalse);
    }
    else
    {
        Event_SysStateStepSet(setSubStep, stepTrue);
    }
}

void Event_DisplayMapMsg(bool hasSelection, s32 mapMsgIdx, s32 step0, s32 step1, s32 step2, bool incSubStep) // 0x800860B0
{
    s32 mapMsgState;

    mapMsgState = Gfx_MapMsg_Draw(mapMsgIdx);
    if (mapMsgState <= MapMsgState_Idle)
    {
        return;
    }

    if (!hasSelection)
    {
        Event_SysStateStepIncrement(incSubStep);
        return;
    }

    if (mapMsgState == MapMsgState_SelectEntry0)
    {
        Event_SysStateStepSet(incSubStep, step0);
    }
    if (mapMsgState == MapMsgState_SelectEntry1)
    {
        Event_SysStateStepSet(incSubStep, step1);
    }
    if (mapMsgState == MapMsgState_SelectEntry2)
    {
        Event_SysStateStepSet(incSubStep, step2);
    }
}

void Event_ScreenFadeCommand(e_ScreenFadeCommand cmd, bool fadeOut, s32 fadeType, q19_12 fadeTimestep, bool incSubStep) // 0x8008616C
{
    typedef enum _FadeType
    {
        FadeType_Black = 0,
        FadeType_White = 1,
        FadeType_Unk2  = 2, // TODO: Investigate. Some state machine flow logic when this is used.
        FadeType_Unk3  = 3  // TODO: Investigate.
    } e_FadeType;

    e_ScreenFadeCommand activeCmd;

    // If `cmd == ScreenFadeCommand_Auto`, `sysStateSteps[2]` dictates the command. This field is manipulated often in map event functions.
    if (cmd != ScreenFadeCommand_Auto)
    {
        activeCmd = cmd;
    }
    else
    {
        activeCmd = g_SysWork.sysStateSteps[2];
    }

    switch (activeCmd)
    {
        case ScreenFadeCommand_Start:
            if (fadeType != FadeType_Unk2)
            {
                g_ScreenFadeTimestep = fadeTimestep;
            }

            if (fadeOut)
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
                    g_SysWork.cutsceneBorderState = 18;

                    if (fadeType == FadeType_Unk3)
                    {
                        g_SysWork.sysFlags |= SysFlag_CutsceneActive;
                    }
                }
            }
            else
            {
                if (fadeType == FadeType_Black)
                {
                    ScreenFade_Start(false, true, false);
                }
                else if (fadeType == FadeType_White)
                {
                    ScreenFade_Start(false, true, true);
                }
                else
                {
                    g_SysWork.cutsceneBorderState = 22;
                }
            }

            if (cmd != ScreenFadeCommand_Start) // `cmd` will only be different if `ScreenFadeCommand_Auto` was passed.
            {
                SysWork_StateStepIncrement(2);
            }
            break;

        case ScreenFadeCommand_Await:
            if (fadeType < FadeType_Unk2)
            {
                if ((fadeOut == false && ScreenFade_IsNone()) ||
                    (fadeOut == true  && ScreenFade_IsFinished()))
                {
                    Event_SysStateStepIncrement(incSubStep);
                }
            }
            else if ((fadeOut == false && g_SysWork.cutsceneBorderState == 1) ||
                     (fadeOut == true  && g_SysWork.cutsceneBorderState == 21))
            {
                Event_SysStateStepIncrement(incSubStep);
            }

            break;
    }
}

const RECT D_8002AB10 =  // 0x8002AB10 .rodata
{
    SCREEN_POSITION_X(100.0f), 256,
    (SCREEN_WIDTH / 5) * 3, SCREEN_HEIGHT
};

void Event_BgTextureCommand(e_BgTextureCommand cmd, e_FsFile fileIdx, bool incSubStep) // 0x800862F8
{
    e_BgTextureCommand activeCmd;

    if (cmd == BgTextureCommand_Auto)
    {
        activeCmd = g_SysWork.sysStateSteps[2];
    }
    else
    {
        activeCmd = cmd;
        if (activeCmd == BgTextureCommand_8)
        {
            activeCmd = BgTextureCommand_AwaitLoad;
            if (g_SysWork.sysStateSteps[2] == 0)
            {
                activeCmd = BgTextureCommand_QueueReadSecondary;
            }
        }
    }

    switch (activeCmd)
    {
        case BgTextureCommand_QueueRead:
            Fs_QueueStartReadTim(fileIdx, FS_BUFFER_1, &g_ItemInspectionImg);

            if (cmd != BgTextureCommand_QueueRead)
            {
                SysWork_StateStepIncrement(2);

                if (Fs_QueueChunksLoad())
                {
                    Event_SysStateStepIncrement(incSubStep);
                }
            }
            break;

        case BgTextureCommand_AwaitLoad:
            if (Fs_QueueChunksLoad())
            {
                Event_SysStateStepIncrement(incSubStep);
            }
            break;

        case BgTextureCommand_Draw:
            Screen_BackgroundImgDrawAlt(&g_ItemInspectionImg);
            break;

        case BgTextureCommand_StoreVram:
            DrawSync(SyncMode_Wait);
            StoreImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(SyncMode_Wait);
            break;

        case BgTextureCommand_QueueReadSecondary:
            Fs_QueueStartReadTim(fileIdx, FS_BUFFER_1, &D_800A9A04);

            if (cmd == BgTextureCommand_8)
            {
                SysWork_StateStepSet(2, BgTextureCommand_AwaitLoad);
            }
            break;

        case BgTextureCommand_DrawSecondary:
            Screen_BackgroundImgDrawAlt(&D_800A9A04);
            break;

        case BgTextureCommand_RestoreVram:
            LoadImage(&D_8002AB10, IMAGE_BUFFER_2);
            DrawSync(SyncMode_Wait);
            break;
    }
}

void Event_InvItemCommand(e_InvItemCommand cmd, e_InvItemId itemId, s32 itemCount, bool incSubStep) // 0x80086470
{
    // This func does weird remapping of the input `cmd` to `activeCmd`
    // `cmd` is also `u32` while `activeCmd` is `s32`, added internal enum here to help func make more sense.
    typedef enum _InvItemCommandInternal
    {
        InvItemCommandInternal_QueueLoad = 0,
        InvItemCommandInternal_AwaitLoad = 1,
        InvItemCommandInternal_AddItem   = 2, // Remapped from `InvItemCommand_AddItem` (3)
        InvItemCommandInternal_Nop       = 3, // Remapped from `InvItemCommand_Nop` (2)
        InvItemCommandInternal_Hack      = -1
    } e_InvItemCommandInternal;

    e_InvItemCommandInternal activeCmd;

    if (cmd == InvItemCommand_6 && g_SysWork.sysStateSteps[2] == 0)
    {
        SysWork_StateStepSet(2, InvItemCommandInternal_AddItem);
    }

    activeCmd = cmd;
    if (cmd >= InvItemCommand_Nop)
    {
        if (cmd == InvItemCommand_Nop)
        {
            activeCmd = InvItemCommandInternal_Nop;
        }
        else if (cmd == InvItemCommand_AddItem)
        {
            activeCmd = InvItemCommandInternal_AddItem;
        }
        else
        {
            activeCmd = g_SysWork.sysStateSteps[2];
        }
    }

    switch (activeCmd)
    {
        case InvItemCommandInternal_QueueLoad:
            GameFs_UniqueItemModelLoad(itemId);

            if (cmd == InvItemCommand_QueueLoad)
            {
                SysWork_StateStepIncrement(1);
                g_SysWork.sysStateSteps[1]--;
            }

            SysWork_StateStepIncrement(2);

        case InvItemCommandInternal_AwaitLoad:
            if (!Fs_QueueChunksLoad())
            {
                break;
            }

            func_80054A04(itemId);

            if (cmd == InvItemCommand_AwaitLoad || cmd == InvItemCommand_4)
            {
                Event_SysStateStepIncrement(incSubStep);
                break;
            }

            SysWork_StateStepIncrement(2);

        case InvItemCommandInternal_AddItem:
            SysWork_StateStepSet(2, 0);

            if (cmd == InvItemCommand_AddItem || cmd == InvItemCommand_6)
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
        D_800C4640[idx0][idx1].vx = g_SysWork.playerWork.player.position.vx + offsetOrPosX;
        D_800C4640[idx0][idx1].vy = g_SysWork.playerWork.player.position.vy;
        D_800C4640[idx0][idx1].vz = g_SysWork.playerWork.player.position.vz + offsetOrPosZ;

        D_800C4700[idx0] = angleY;
    }
    else if (isPos == true)
    {
        D_800C4640[idx0][idx1].vx = offsetOrPosX;
        D_800C4640[idx0][idx1].vy = g_SysWork.playerWork.player.position.vy;
        D_800C4640[idx0][idx1].vz = offsetOrPosZ;

        D_800C4700[idx0] = angleY;
    }
}

void func_800866D4(s32 arg0, s32 arg1, bool incSubStep) // 0x800866D4
{
    if (g_MapOverlayHdr.func_D0(arg0, &D_800C4640, D_800C4700[0], arg1) == 1)
    {
        Event_SysStateStepIncrement(incSubStep);
    }
}

void func_80086728(s_SubCharacter* chara, s32 arg1, s32 arg2, bool incSubStep) // 0x80086728
{
    if (g_MapOverlayHdr.func_13C(chara, arg1, &D_800C4640[1][0], D_800C4700[1], arg2) == 1)
    {
        Event_SysStateStepIncrement(incSubStep);
    }
}

void func_8008677C(s_SubCharacter* chara, s32 arg1, s32 arg2) // 0x8008677C
{
    g_MapOverlayHdr.func_13C(chara, arg1, &D_800C4640[1][0], D_800C4700[1], arg2);
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
            Screen_BackgroundImgDraw(&g_PaperMapImg);
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

void Event_DisplayMapMsgWithAudio(s32 mapMsgIdx, u8* audioIdx, const u16* audioCmds) // 0x800869E4
{
    s32 mapMsgState;

    g_SysWork.bgmStatusFlags |= BgmStatusFlag_VoiceDialog;

    mapMsgState = Gfx_MapMsg_Draw(mapMsgIdx);
    if (mapMsgState == MapMsgState_SelectEntry0)
    {
        SysWork_StateStepIncrement(0);
    }
    else if (mapMsgState == MapMsgState_Finish)
    {
        SD_Call(audioCmds[*audioIdx]);
        *audioIdx += 1;
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

void Event_CharaAnimPlayUntilEnd(s_SubCharacter* chara, s32 animState) // 0x80086C58
{
    switch (g_SysWork.sysStateSteps[1])
    {
        case 0:
            Event_CharaAnimCommandExecute(CharaAnimCommand_SetState, chara, animState, false);
            SysWork_StateStepIncrement(1);
            break;

        case 1:
            Event_CharaAnimCommandExecute(CharaAnimCommand_AwaitAnimEnd, chara, 0, true);
            break;

        default:
            SysWork_StateStepIncrement(0);
            break;
    }
}

void Event_CharaAnimUnlockPlayUntilEnd(s_SubCharacter* chara) // 0x80086D04
{
    switch (g_SysWork.sysStateSteps[1])
    {
        case 0:
            Event_CharaAnimCommandExecute(CharaAnimCommand_AnimUnlock, chara, 0, false);
            SysWork_StateStepIncrement(1);
            break;

        case 1:
            Event_CharaAnimCommandExecute(CharaAnimCommand_AwaitAnimEnd, chara, 0, true);
            break;

        default:
            SysWork_StateStepIncrement(0);
            break;
    }
}

void Event_BgTextureLoadFadeIn(e_FsFile fileIdx, q19_12 fadeTimestep) // 0x80086DA8
{
    switch (g_SysWork.sysStateSteps[1])
    {
        case 0:
            Event_ScreenFadeCommand(ScreenFadeCommand_Start, true, 0, fadeTimestep, false);
            SysWork_StateStepIncrement(1);

        case 1:
            Event_BgTextureCommand(BgTextureCommand_Auto, fileIdx, true);
            break;

        default:
            Event_ScreenFadeCommand(ScreenFadeCommand_Await, true, 0, Q12(0.0f), false);
            break;
    }
}

void Event_BgTextureFadeIn(e_FsFile fileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1) // 0x80086E50
{
    switch (g_SysWork.sysStateSteps[1])
    {
        case 0:
            Event_ScreenFadeCommand(ScreenFadeCommand_Start, true, 0, fadeTimestep0, false);
            SysWork_StateStepIncrement(1);

        case 1:
            Event_BgTextureCommand(BgTextureCommand_Auto, fileIdx, true);
            break;

        case 2:
            Event_ScreenFadeCommand(ScreenFadeCommand_Await, true, 0, Q12(0.0f), true);
            break;

        default:
            Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);
            Event_ScreenFadeCommand(ScreenFadeCommand_Auto, false, 0, fadeTimestep1, false);
    }
}

void func_80086F44(q19_12 fadeTimestep0, q19_12 fadeTimestep1) // 0x80086F44
{
    if (g_SysWork.sysStateSteps[1] == 0)
    {
        Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);
        Event_ScreenFadeCommand(ScreenFadeCommand_Auto, true, 0, fadeTimestep1, true);
        return;
    }

    Event_ScreenFadeCommand(ScreenFadeCommand_Start, false, 0, fadeTimestep0, false);
    SysWork_StateStepIncrement(0);
}

void Event_DisplayMapMsgWithSfx(s32 mapMsgIdx, e_SfxId sfxId, VECTOR3* sfxPos) // 0x80086FE8
{
    s32 i;

    if (!(g_SysWork.sysFlags & SysFlag_5))
    {
        // Run through NPCs.
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++)
        {
            if (g_SysWork.npcs[i].model.charaId >= Chara_Harry &&
                g_SysWork.npcs[i].model.charaId <= Chara_MonsterCybil &&
                g_SysWork.npcs[i].health > Q12(0.0f))
            {
                break;
            }
        }

        if (i != ARRAY_SIZE(g_SysWork.npcs))
        {
            g_DeltaTime = Q12(0.0f);
        }
    }

    switch (g_SysWork.sysStateSteps[1])
    {
        case 0:
            g_MapOverlayHdr.playerControlFreeze();
            Sfx_WithFlagsPlay(sfxId, sfxPos, Q8(0.5f), SfxFlag_None);
            SysWork_StateStepIncrement(1);

        case 1:
            Event_SysStateStepIncrementDelayed(Q12(0.2f), true);
            break;

        case 2:
            Event_DisplayMapMsg(false, mapMsgIdx, 0, 0, 0, true);
            break;

        default:
            g_MapOverlayHdr.playerControlUnfreeze(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_DisplayBgTexture(e_FsFile textureFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1) // 0x8008716C
{
    switch (g_SysWork.sysStateSteps[1])
    {
        case 0:
            g_MapOverlayHdr.playerControlFreeze();
            Event_ScreenFadeCommand(ScreenFadeCommand_Start, true, 0, fadeTimestep0, false);
            SysWork_StateStepIncrement(1);

        case 1:
            Event_BgTextureCommand(BgTextureCommand_Auto, textureFileIdx, true);
            break;

        case 2:
            Event_ScreenFadeCommand(ScreenFadeCommand_Await, true, 0, Q12(0.0f), true);
            break;

        case 3:
            Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);
            Event_ScreenFadeCommand(ScreenFadeCommand_Auto, false, 0, fadeTimestep1, true);
            break;

        case 4:
            Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);

            if (g_Controller0->clickedBtnFlags & (g_GameWorkPtr->config.controllerConfig.enter |
                                                 g_GameWorkPtr->config.controllerConfig.cancel))
            {
                SysWork_StateStepIncrement(1);
            }
            break;

        case 5:
            Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);
            Event_ScreenFadeCommand(ScreenFadeCommand_Auto, true, 0, fadeTimestep1, true);
            break;

        default:
            Event_ScreenFadeCommand(ScreenFadeCommand_Start, false, 0, fadeTimestep0, false);
            g_MapOverlayHdr.playerControlUnfreeze(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_DisplayMapMsgWithTexture(e_FsFile textureFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx) // 0x80087360
{
    switch (g_SysWork.sysStateSteps[1])
    {
        case 0:
            g_MapOverlayHdr.playerControlFreeze();
            Event_ScreenFadeCommand(ScreenFadeCommand_Start, true, 0, fadeTimestep0, false);
            SysWork_StateStepIncrement(1);

        case 1:
            Event_BgTextureCommand(BgTextureCommand_Auto, textureFileIdx, true);
            break;

        case 2:
            Event_ScreenFadeCommand(ScreenFadeCommand_Await, true, 0, Q12(0.0f), true);
            break;

        case 3:
            Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);
            Event_ScreenFadeCommand(ScreenFadeCommand_Auto, false, 0, fadeTimestep1, true);
            break;

        case 4:
            Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);
            Event_DisplayMapMsg(false, mapMsgIdx, 0, 0, 0, true);
            break;

        case 5:
            Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);
            Event_ScreenFadeCommand(ScreenFadeCommand_Auto, true, 0, fadeTimestep1, true);
            break;

        default:
            Event_ScreenFadeCommand(ScreenFadeCommand_Start, false, 0, fadeTimestep0, false);
            g_MapOverlayHdr.playerControlUnfreeze(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_DisplayMapMsgWithTexture1(e_FsFile textureFileIdx, q19_12 fadeTimestep0, q19_12 fadeTimestep1, s32 mapMsgIdx0, s32 mapMsgIdx1) // 0x80087540
{
    switch (g_SysWork.sysStateSteps[1])
    {
        case 0:
            g_MapOverlayHdr.playerControlFreeze();
            Event_ScreenFadeCommand(ScreenFadeCommand_Start, true, 0, fadeTimestep0, false);
            SysWork_StateStepIncrement(1);

        case 1:
            Event_BgTextureCommand(BgTextureCommand_Auto, textureFileIdx, true);
            break;

        case 2:
            Event_ScreenFadeCommand(ScreenFadeCommand_Await, true, 0, Q12(0.0f), true);
            break;

        case 3:
            Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);
            Event_ScreenFadeCommand(ScreenFadeCommand_Auto, false, 0, fadeTimestep1, true);
            break;

        case 4:
            Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);

            if (mapMsgIdx0 != MapMsgCode_None)
            {
                Event_DisplayMapMsg(false, mapMsgIdx0, 0, 0, 0, true);
                break;
            }

            if (g_Controller0->clickedBtnFlags & (g_GameWorkPtr->config.controllerConfig.enter |
                                                 g_GameWorkPtr->config.controllerConfig.cancel))
            {
                SysWork_StateStepIncrement(1);
            }
            break;

        case 5:
            g_Screen_BackgroundImgGamma = Q8(6.0f / 32.0f);
            Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);
            Event_DisplayMapMsg(false, mapMsgIdx1, 0, 0, 0, true);
            break;

        case 6:
            g_Screen_BackgroundImgGamma = Q8(6.0f / 32.0f);

            Event_BgTextureCommand(BgTextureCommand_Draw, 0, false);
            Event_ScreenFadeCommand(ScreenFadeCommand_Auto, true, 0, fadeTimestep1, true);
            break;

        default:
            Event_ScreenFadeCommand(ScreenFadeCommand_Start, false, 0, fadeTimestep0, false);
            g_MapOverlayHdr.playerControlUnfreeze(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_ItemTake(e_InvItemId itemId, s32 itemCount, e_EventFlag eventFlagIdx, s32 mapMsgIdx) // 0x800877B8
{
    s32 i            = itemId;
    s32 mapMsgIdxCpy = mapMsgIdx;

    if (!(g_SysWork.sysFlags & SysFlag_5))
    {
        // Run through NPCs.
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++)
        {
            if (g_SysWork.npcs[i].model.charaId >= Chara_Harry && g_SysWork.npcs[i].model.charaId <= Chara_MonsterCybil &&
                g_SysWork.npcs[i].health > Q12(0.0f))
            {
                break;
            }
        }

        if (i != ARRAY_SIZE(g_SysWork.npcs))
        {
            g_DeltaTime = Q12(0.0f);
        }
    }

    switch (g_SysWork.sysStateSteps[1])
    {
        case 0: // Freeze player and start loading item model.
            g_MapOverlayHdr.playerControlFreeze();
            Event_InvItemCommand(InvItemCommand_QueueLoad, itemId, 0, false);

            SysWork_StateStepIncrement(1);

        case 1: // Load model.
            Event_InvItemCommand(InvItemCommand_AwaitLoad, itemId, 0, true);
            break;

        case 2:
            // `Gfx_PickupItemAnimate` increases model scale and returns `false`, then starts rotating it and returns `true`.
            if (Gfx_PickupItemAnimate(itemId))
            {
                Event_DisplayMapMsg(true, mapMsgIdxCpy, 3, NO_VALUE, 0, true); // 3 is "Yes", `NO_VALUE` is "No".
            }

            // Flag pickup item as collected.
            Savegame_EventFlagSet(eventFlagIdx);
            break;

        case 3: // "Yes" selected.
            Event_InvItemCommand(InvItemCommand_AddItem, itemId, itemCount, false);
            SysWork_StateStepIncrement(1);

        default:
            // Flag pickup item as uncollected. Selecting 'No' sets `field_10` to `NO_VALUE`.
            if (g_SysWork.sysStateSteps[1] == NO_VALUE)
            {
                Savegame_EventFlagClear(eventFlagIdx);
            }

            g_MapOverlayHdr.playerControlUnfreeze(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_CommonItemTake(u32 pickupType, e_EventFlag eventFlagIdx) // 0x800879FC
{
    #define EASY_DIFFICULTY_AMMO_COUNT_MULT_MIN 2

    s32 ammoCountMult;

    // Compute ammo count multiplier.
    ammoCountMult = g_GameWork.config.extraBulletAdjust + 1;
    if (g_SavegamePtr->gameDifficulty == GameDifficulty_Easy)
    {
        ammoCountMult = CLAMP(ammoCountMult, EASY_DIFFICULTY_AMMO_COUNT_MULT_MIN, ammoCountMult);
    }

    // Handle item pickup.
    switch (pickupType)
    {
        case CommonPickupItemId_FirstAidKit:
            Event_ItemTake(InvItemId_FirstAidKit, DEFAULT_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_FirstAidSelect);
            break;

        case CommonPickupItemId_HealthDrink:
            Event_ItemTake(InvItemId_HealthDrink, DEFAULT_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_HealthDrinkSelect);
            break;

        case CommonPickupItemId_Ampoule:
            Event_ItemTake(InvItemId_Ampoule, DEFAULT_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_AmpouleSelect);
            break;

        case CommonPickupItemId_HandgunBullets:
            Event_ItemTake(InvItemId_HandgunBullets, ammoCountMult * HANDGUN_AMMO_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_HandgunAmmoSelect);
            break;

        case CommonPickupItemId_ShotgunShells:
            Event_ItemTake(InvItemId_ShotgunShells, ammoCountMult * SHOTGUN_AMMO_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_ShotgunAmmoSelect);
            break;

        case CommonPickupItemId_RifleShells:
            Event_ItemTake(InvItemId_RifleShells, ammoCountMult * RIFLE_AMMO_PICKUP_ITEM_COUNT, eventFlagIdx, MapMsgIdx_RifleAmmoSelect);
            break;
    }

    #undef EASY_DIFFICULTY_AMMO_COUNT_MULT_MIN
}

void Event_MapTake(s32 paperMapFlagIdx, e_EventFlag eventFlagIdx, s32 mapMsgIdx) // 0x80087AF4
{
    static const RECT RECT = {
        SCREEN_POSITION_X(100.0f), 256,
        SCREEN_WIDTH / 2, SCREEN_HEIGHT
    };

    s32 paperMapFlagIdxCpy;

    g_DeltaTime        = Q12(0.0f);
    paperMapFlagIdxCpy = paperMapFlagIdx;

    switch (g_SysWork.sysStateSteps[1])
    {
        case 0:
            g_MapOverlayHdr.playerControlFreeze();
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[paperMapFlagIdx]);
            SysWork_StateStepIncrement(1);

        case 1:
            Event_ScreenFadeCommand(ScreenFadeCommand_Auto, true, 0, Q12(0.0f), true);
            break;

        case 2:
            DrawSync(SyncMode_Wait);
            StoreImage(&RECT, IMAGE_BUFFER);
            DrawSync(SyncMode_Wait);
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + g_PaperMapFileIdxs[paperMapFlagIdx], FS_BUFFER_2, &g_PaperMapImg);
            Screen_Init(SCREEN_WIDTH, true);

            g_IntervalVBlanks = 1;

            GsSwapDispBuff();
            Event_ScreenFadeCommand(ScreenFadeCommand_Start, false, 0, Q12(0.0f), false);
            Fs_QueueWaitForEmpty();

            SysWork_StateStepIncrement(1);

        case 3:
            g_Screen_BackgroundImgGamma = Q8(11.0f / 32.0f);

            Screen_BackgroundImgDraw(&g_PaperMapImg);
            Event_DisplayMapMsg(true, mapMsgIdx, 4, 5, 0, true); // 4 is "No", 5 is "Yes".
            break;

        case 4:
            paperMapFlagIdxCpy                                         = paperMapFlagIdx >> 5;
            ((s32*)&g_SavegamePtr->paperMapFlags)[paperMapFlagIdxCpy] |= 1 << (paperMapFlagIdx & 0x1F); // TODO: Maybe union?

            switch (paperMapFlagIdx)
            {
                case 6:
                    g_SavegamePtr->paperMapFlags |= 0x1FA0;
                    break;

                case 17:
                    g_SavegamePtr->paperMapFlags |= 1 << 18;
                    g_SavegamePtr->paperMapFlags |= 1 << 19;
                    g_SavegamePtr->paperMapFlags |= 1 << 21;
                    g_SavegamePtr->paperMapFlags |= 1 << 22;
                    g_SavegamePtr->paperMapFlags |= 1 << 23;
                    break;

                case 16:
                    g_SavegamePtr->paperMapFlags |= 1 << 20;
                    break;

                case 13:
                    g_SavegamePtr->paperMapFlags |= 1 << 14;
                    break;

                case 2:
                    g_SavegamePtr->paperMapFlags |= 1 << 3;
                    break;
            }

            Savegame_EventFlagSet(eventFlagIdx);
            SysWork_StateStepIncrement(1);

        case 5:
            g_Screen_BackgroundImgGamma = Q8(11.0f / 32.0f);

            Screen_BackgroundImgDraw(&g_PaperMapImg);
            Event_ScreenFadeCommand(ScreenFadeCommand_Auto, true, 0, Q12(0.0f), true);
            break;

        default:
            LoadImage(&RECT, IMAGE_BUFFER);
            DrawSync(SyncMode_Wait);
            Screen_Init(SCREEN_WIDTH, false);
            Event_ScreenFadeCommand(ScreenFadeCommand_Start, false, 0, Q12(0.0f), false);

            g_MapOverlayHdr.playerControlUnfreeze(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}
