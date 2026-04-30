#include "bodyprog/bodyprog.h"
#include "bodyprog/dms.h"
#include "bodyprog/gfx/map_effects.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player.h"
#include "main/rng.h"
#include "maps/map0/map0_s00.h"
#include "maps/particle.h"
#include "maps/characters/cheryl.h"
#include "inline_no_dmpsx.h"

// Enemy character used on this map changes depending on the region.
#if VERSION_REGION_IS(NTSC)
    #define ENEMY_CHARA_ID Chara_GreyChild
#elif VERSION_REGION_IS(NTSCJ)
    #define ENEMY_CHARA_ID Chara_Mumbler
#endif

#include "../src/maps/chara_util.c" // 0x800D88AC

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D929C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D92AC

void Map_RoomBgmInit(bool arg0) // 0x800D94F8
{
    s32    i;
    q19_12 var1;
    s32    flags;
    u32    saveByte;

    // @hack Not used directly, but gets merged with  `Savegame_EventFlagGet` macros below.
    saveByte = g_SavegamePtr->eventFlags_168[0];
    var1     = Q12(0.1f);
    flags    = 1 << 8;

    if (g_SysWork.playerWork.player.health > 0 && (!(Savegame_EventFlagGet(EventFlag_23) && !Savegame_EventFlagGet(EventFlag_20))))
    {
        for (i = 1; i < 7; i++)
        {
            if (Savegame_EventFlagGet(D_800DF300[i]))
            {
                flags |= 1 << i;
            }
        }
    }
    else
    {
        Savegame_EventFlagClear(EventFlag_20);
        var1 = Q12(0.3f);
    }

    Bgm_Update(flags, var1, &D_800DF2F8);
}

void GameBoot_LoadScreen_StageString(void) // 0x800D95D4
{
    ScreenFade_Start(false, true, false);

    Text_Debug_PositionSet(100, 100);
    Text_Debug_Draw("STAGE 0-0");
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/map_msg_common.h"
#if VERSION_REGION_IS(NTSC)
    /* 15 */ "~J0(2.5)\tCheryl.__Where_could_you_be? ~E ",
    /* 16 */ "~J0(1.5)\tIt's_strange... ",
    /* 17 */ "~J0(2.0)\tIt's_quiet.__Too_quiet. ",
    /* 18 */ "~J0(3.0)\tThis_place_is ~N\n\t\t\tlike_a_ghost_town. ~E ",
    /* 19 */ "~J0(3.0)\tCheryl. ~E ",
    /* 20 */ "~J0(1.5)\tFootsteps? ~E ",
    /* 21 */ "~J0(2.8)\tCheryl? ~N\n\t\t\tIs_that_Cheryl!? ~E ",
    /* 22 */ "~J0(1.2)\tWhere_are_you_going? ~E ",
    /* 23 */ "~J0(1.8)\tHey_wait...stop! ~E ",
    /* 24 */ "\tI'd_better_follow_Cheryl... ~E ",
    /* 25 */ "\tThat's_strange, ~N\n\tit's_getting_darker. ~E ",
    /* 26 */ "\tA_dead_end? ~N\n\tWhat_the_hell!? ~E ",
    /* 27 */ "~J0(1.6)\tWhat_is_this? ",
    /* 28 */ "~J0(2.5)\tWhat's_going_on_here!? ~E ",
    /* 29 */ "\tWhat's_this? ~E ",
    /* 30 */ "\t......better_than_nothing, ~N\n\tI_guess. ~E ",
    /* 31 */ "\tWhat? ~N\n\tWhat's_this_doing_here? ~E ",
    /* 32 */ "\tBlocked_by_a_fence? ~E ",
    /* 33 */ "\tA_broken_wheelchair? ~N\n\tWhat's_this_doing_here? ~E ",
    /* 34 */ "\tWhat_the..? ~N\n\tWhat_is_it? ~E ",
    /* 35 */ "\tThe_street_is_blocked.",
    /* 36 */ "\tCan't_get_out_of_town ~N\n\tthrough_here. ~E ",
    /* 37 */ "\tMy_car... ~N\n\ttoo_banged_up_to_drive. ",
    /* 38 */ "\tWhere's_Cheryl? ~N\n\tHope_she's_safe. ~E "
#elif VERSION_REGION_IS(NTSCJ)
    /* 15 */ "~J0(2.5)\tシェリル……どこへ行ったんだ？ ~E ",
    /* 16 */ "~J0(1.5)\tおかしい…… ",
    /* 17 */ "~J0(2.0)\t……静かだ　静かすぎる ",
    /* 18 */ "~J0(3.0)\tまるで人のいない町のようだ…… ~E ",
    /* 19 */ "~J0(3.0)\tシェリル…… ~E ",
    /* 20 */ "~J0(1.5) \t……足音？ ~E ",
    /* 21 */ "~J0(2.8)\tシェリル……？ ~N\n\t\t\tシェリルなのか！？ ~E ",
    /* 22 */ "~J0(1.2)\tどこへ行くんだ？ ~E ",
    /* 23 */ "~J0(1.8)\t待つんだ……待ってくれ！ ~E ",
    /* 24 */ "\tシェリルを追わなくては…… ~E ",
    /* 25 */ "\tおかしい……暗くなってきたな ~E ",
    /* 26 */ "\t行き止まり……？ ~N\n\tそんな馬鹿な！ ~E ",
    /* 27 */ "~J0(1.6)\tこれは何だ？ ",
    /* 28 */ "~J0(2.5)\tさっきからいったい ~N\n\t\t\tどうなってるんだ！？ ~E ",
    /* 29 */ "\tこれは……？ ~E ",
    /* 30 */ "\t……ないよりは　ましか ~E ",
    /* 31 */ "\t何で……こんなものが…… ~E ",
    /* 32 */ "\t金網で道がふさがれている！ ~E ",
    /* 33 */ "\t壊れた車椅子だ　なぜこんなところに？ ~E ",
    /* 34 */ "\t何だ……？　これは…… ~E ",
    /* 35 */ "\t道がふさがれている ~N\n\tここから町を出ることはできないな ~E ",
    /* 36 */ // TODO: JAP versions concatenate 35+36 into single string? Code would need adjustment too with `#ifdef`.
    /* 37 */ "\t乗ってきた車だ ~N\n\t壊れて動かなくなっている ",
    /* 38 */ "\t……シェリルはどこに行ったのだろう？ ~N\n\t無事ならいいのだが…… ~E "
#endif
};

void func_800D9610(void) // 0x800D9610
{
    VECTOR3 sfxPos = {
        MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionX,
        Q12(-1.2f),
        MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionZ
    };

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            func_8005DC1C(Sfx_Unk1355, &sfxPos, Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(0.1f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

extern q19_12  g_Cutscene_Timer;
extern VECTOR3 g_CameraPositionTarget;
extern VECTOR3 g_CameraLookAtTarget;

void MapEvent_CutsceneOpening(void) // 0x0x800D9748
{
    typedef enum _EventState
    {
        EventState_Initialize = 0,
        EventState_LoadChunks = 1,
        EventState_2          = 2,
        EventState_3          = 3,
        EventState_4          = 4,
        EventState_5          = 5,
        EventState_6          = 6,
        EventState_7          = 7,
        EventState_8          = 8,
        EventState_9          = 9,
        EventState_10         = 10,
        EventState_11         = 11,
        EventState_12         = 12,
        EventState_13         = 13
    } e_EventState;

    bool skip;

    // Skip.
    skip = false;
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.skip) &&
        g_SysWork.sysStateSteps[0] >= EventState_3 &&
        g_SysWork.sysStateSteps[0] <  EventState_13)
    {
        skip = true;
        SysWork_StateStepReset();
    }

    // Control cutscene.
    switch (g_SysWork.sysStateSteps[0])
    {
        case EventState_Initialize:
            Player_ControlFreeze();
            Fs_QueueStartRead(FILE_ANIM_OPEN_DMS, FS_BUFFER_16);

            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();

            g_SysWork.flags_22A4 |= UnkSysFlag_3;

            Sd_PlaySfx(Sfx_Unk1361, 0, 0x90);
            SysWork_StateStepIncrement(0);

        case EventState_LoadChunks:
            if (Fs_QueueChunksLoad())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case EventState_2:
            // Load Cheryl character.
            Dms_HeaderFixOffsets((s_DmsHeader*)FS_BUFFER_16);
            Chara_Load(0, Chara_Cheryl, g_SysWork.npcBoneCoords, 0, NULL, NULL);

            SysWork_StateStepIncrementAfterFade(false, false, 0, Q12(3.0f), false);
            g_Cutscene_Timer = Q12(0.0f);

            SysWork_StateStepIncrement(0);
            break;

        case EventState_3:
            func_80085EB8(0, &g_SysWork.playerWork.player, 53, false);
            SysWork_StateStepIncrement(0);

        case EventState_4:
            g_Cutscene_Timer = MIN(g_Cutscene_Timer + Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f)), Q12(22.0f));
            if (g_Cutscene_Timer >= Q12(22.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case EventState_5:
            func_80085EB8(0, &g_SysWork.playerWork.player, 74, false);
            SysWork_StateStepIncrement(0);

        case EventState_6:
            g_Cutscene_Timer = MIN(g_Cutscene_Timer + Q12_MULT_PRECISE(g_DeltaTime, Q12(8.0f)), Q12(26.0f));
            if (g_Cutscene_Timer >= Q12(26.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case EventState_7:
            g_Cutscene_Timer = MIN((g_Cutscene_Timer + Q12_MULT_PRECISE(g_DeltaTime, Q12(4.0f))), Q12(72.0f));
            MapMsg_DisplayAndHandleSelection(false, 15, false, false, 0, false); // "Cheryl. Where could you be?"
            break;

        case EventState_8:
            g_Cutscene_Timer = MIN((g_Cutscene_Timer + Q12_MULT_PRECISE(g_DeltaTime, Q12(4.0f))), Q12(72.0f));
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case EventState_9:
            g_Cutscene_Timer = MIN((g_Cutscene_Timer + Q12_MULT_PRECISE(g_DeltaTime, Q12(4.0f))), Q12(72.0f));
            MapMsg_DisplayAndHandleSelection(false, 16, false, false, 0, false); // "It's strange..."
            break;

        case EventState_10:
            g_Cutscene_Timer = MIN(g_Cutscene_Timer + Q12_MULT_PRECISE(g_DeltaTime, Q12(4.0f)), Q12(72.0f));
            if (g_Cutscene_Timer >= Q12(72.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case EventState_11:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case EventState_12:
            MapMsg_DisplayAndHandleSelection(false, 19, false, false, 0, false); // "Cheryl."
            break;

        case EventState_13:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        default:
            g_Cutscene_Timer = NO_VALUE;

            if (skip)
            {
                // Restore player control.
                Player_ControlUnfreeze(true);
                SysWork_StateSetNext(SysState_Gameplay);

                if (ScreenFade_IsFinished())
                {
                    SysWork_StateStepIncrementAfterFade(false, false, 0, Q12(0.0f), false);
                }
            }
            else
            {
                // Restore player control.
                Player_ControlUnfreeze(false);
                SysWork_StateSetNext(SysState_Gameplay);
            }

            SysWork_StateStepIncrementAfterFade(false, false, 2, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);

            // Load Cheryl character.
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Cheryl, 0, Q12(-29.5f), Q12(128.7f), Q12(-0.3125f), 1);
            break;
    }

    // Control player and camera.
    if (g_Cutscene_Timer >= Q12(0.0f))
    {
        Dms_CharacterTransformGet(&g_SysWork.playerWork.player.position, &g_SysWork.playerWork.player.rotation, "HERO", g_Cutscene_Timer, (s_DmsHeader*)FS_BUFFER_16);
        vcChangeProjectionValue(Dms_CameraTargetGet(&g_CameraPositionTarget, &g_CameraLookAtTarget, NULL, g_Cutscene_Timer, (s_DmsHeader*)FS_BUFFER_16));
        vcUserCamTarget(&g_CameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_CameraLookAtTarget, NULL, true);
    }
}

void MapEvent_CutsceneCherylFootsteps0(void) // 0x800D9D98
{
    Cheryl_DistantFootstepSfxPlay();

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(3.0f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            func_800865FC(false, 0, 0, Q12_ANGLE(180.0f), Q12(0.0f), Q12(0.0f));
            SysWork_StateStepIncrement(0);

        case 4:
            func_800866D4(53, 1, false);
            break;

        case 5:
            MapMsg_DisplayAndHandleSelection(false, 20, 0, 0, 0, false); // "Footsteps?"
            break;

        case 6:
            func_800865FC(true, 0, 0, Q12_ANGLE(180.0f),  Q12(-11.0f), Q12(141.0f));
            func_800865FC(true, 0, 1, Q12_ANGLE(180.0f),  Q12(-11.5f), Q12(137.0f));
            func_800865FC(true, 0, 2, Q12_ANGLE(180.0f),  Q12(-9.0f),  Q12(133.0f));
            func_800865FC(true, 0, 3, Q12_ANGLE(-135.0f), Q12(-10.5f), Q12(130.0f));
            func_800865FC(true, 0, 4, Q12_ANGLE(-90.0f),  Q12(-14.0f), Q12(129.0f));
            func_800865FC(true, 0, 5, Q12_ANGLE(-90.0f),  Q12(-18.0f), Q12(129.5f));
            SysWork_StateStepIncrement(0);

        case 7:
            func_800866D4(54, 6, false);
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapEvent_CutsceneCherylFootsteps1(void) // 0x800DA028
{
    Cheryl_DistantFootstepSfxPlay();

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(3.0f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            func_800865FC(false, 0, 0, Q12_ANGLE(-135.0f), Q12(0.0f), Q12(0.0f));
            SysWork_StateStepIncrement(0);

        case 4:
            func_800866D4(53, 1, false);
            break;

        case 5:
            MapMsg_DisplayAndHandleSelection(false, 20, 0, 0, 0, false); // "Footsteps?"
            break;

        case 6:
            func_800865FC(true, 0, 0, Q12_ANGLE(180.0f), Q12(-6.0f),  Q12(135.0f));
            func_800865FC(true, 0, 1, Q12_ANGLE(-90.0f), Q12(-7.0f),  Q12(131.0f));
            func_800865FC(true, 0, 2, Q12_ANGLE(-90.0f), Q12(-11.0f), Q12(128.0f));
            func_800865FC(true, 0, 3, Q12_ANGLE(-90.0f), Q12(-17.5f), Q12(129.5f));
            SysWork_StateStepIncrement(0);

        case 7:
            func_800866D4(54, 4, false);
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

void MapEvent_CutsceneCherylFootsteps2(void) // 0x800DA254
{
    Cheryl_DistantFootstepSfxPlay();

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(3.0f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            func_800865FC(false, 0, 0, Q12_ANGLE(-112.5f), Q12(0.0f), Q12(0.0f));
            SysWork_StateStepIncrement(0);

        case 4:
            func_800866D4(53, 1, false);
            break;

        case 5:
            MapMsg_DisplayAndHandleSelection(false, 20, 0, 0, 0, false); // "Footsteps?"
            break;

        case 6:
            func_800865FC(true, 0, 0, Q12_ANGLE(-135.0f), Q12(5.0f),   Q12(129.0f));
            func_800865FC(true, 0, 1, Q12_ANGLE(-90.0f),  Q12(-6.0f),  Q12(128.0f));
            func_800865FC(true, 0, 2, Q12_ANGLE(-90.0f),  Q12(-17.5f), Q12(129.5f));
            SysWork_StateStepIncrement(0);

        case 7:
            func_800866D4(54, 3, false);
            break;

        default:
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

void Cheryl_DistantFootstepSfxPlay(void) // 0x800DA454
{
    VECTOR3 sfxPos;
    q3_12   angleToTarget;
    s32     temp_s0;
    q19_12  sinAngleToTarget;
    s32     temp_v0_5;
    s32     temp_v1;
    s32     var_a3;

    #define playerChara g_SysWork.playerWork.player

    if (Math_Vector2MagCalc(Q12(-29.5f) - playerChara.position.vx,
                            Q12(128.7f) - playerChara.position.vz) >= Q12(16.0f))
    {
        D_800DFAB8 += g_DeltaTime;
        if (D_800DFAB8 > Q12(0.8f))
        {
            angleToTarget = ratan2(Q12(-29.5f) - playerChara.position.vx,
                                   Q12(128.7f) - playerChara.position.vz);
            sinAngleToTarget = Math_Sin(angleToTarget);

            sfxPos.vy = Q12(0.0f);
            sfxPos.vx = playerChara.position.vx + (sinAngleToTarget * 16);
            sfxPos.vz = playerChara.position.vz + (Math_Cos((q19_12)angleToTarget) * 16);
            func_8005DD44(Sfx_CherylFootstep, &sfxPos, Rng_GenerateUInt(75, 106), Rng_GenerateInt(-16, 15));

            D_800DFAB8 = Q12(0.0f);
        }
    }

    #undef playerChara
}

void MapEvent_CutsceneCherylSpotted(void) // 0x800DA5A0
{
    q19_12 prevPlayerPosX;
    q19_12 prevPlayerPosZ;

    #define cherylChara g_SysWork.npcs[0]

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            // Warp camera.
            Camera_PositionSet(NULL,
                               Q12(-22.0f), Q12(-2.4f), Q12(130.1f),
                               Q12(0.0f), Q12(0.0f),
                               Q12(0.0f), Q12(0.0f),
                               true);
            Camera_LookAtSet(&cherylChara.position,
                             Q12(0.0f), Q12(-1.0f), Q12(0.0f),
                             Q12(0.0f), Q12(0.0f),
                             Q12(0.0f), Q12(0.0f),
                             true);
            break;

        case 1:
        case 2:
            func_800868DC(0);
            func_800868DC(1);
            func_800868DC(2);
            break;

        case 4:
        case 5:
        case 6:
            // Move camera.
            Camera_PositionSet(NULL,
                               Q12(-22.0f) - func_800868F4(Q12(4.0f),  Q12(5.0f), 0),
                               Q12(-2.4f)  - func_800868F4(Q12(-1.5f), Q12(5.0f), 1),
                               Q12(130.1f) - func_800868F4(Q12(4.0f),  Q12(5.0f), 2),
                               Q12(0.0f), Q12(0.0f),
                               Q12(0.0f), Q12(0.0f),
                               false);
            Camera_LookAtSet(&cherylChara.position,
                             Q12(0.0f), Q12(-1.0f), Q12(0.0f),
                             Q12(0.0f), Q12(0.0f),
                             Q12(0.0f), Q12(0.0f),
                             false);
            break;

        case 3:
            // Warp camera.
            Camera_LookAtSet(&cherylChara.position,
                             Q12(0.0f), Q12(-1.0f), Q12(0.0f),
                             Q12(0.0f), Q12(0.0f),
                             Q12(0.0f), Q12(0.0f),
                             false);
            break;

        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        default:
            vcReturnPreAutoCamWork(D_800DFAC2);
            D_800DFAC2 = 0;
            break;
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            sharedFunc_800D88AC_0_s00(&cherylChara);
            func_800865FC(true, 1, 0, Q12_ANGLE(-135.0f), Q12(-35.0f), Q12(120.0f));

            prevPlayerPosX = g_SysWork.playerWork.player.position.vx;
            prevPlayerPosZ = g_SysWork.playerWork.player.position.vz;

            g_Cutscene_MapMsgAudioIdx = 0;

            // Temporarily warp player to initialize required chunks.
            g_SysWork.playerWork.player.position.vx = Q12(-40.0f);
            g_SysWork.playerWork.player.position.vz = Q12(127.0f);
            Ipd_CloseRangeChunksInit();
            g_SysWork.playerWork.player.position.vx = prevPlayerPosX;
            g_SysWork.playerWork.player.position.vz = prevPlayerPosZ;

            SysWork_StateStepIncrement(0);
            break;

        case 1:
            Particle_SystemUpdate(0, g_SavegamePtr->mapOverlayId_A4, 0);
            SysWork_StateStepIncrement(0);

        case 2:
            Map_MessageWithAudio(21, &g_Cutscene_MapMsgAudioIdx, g_Cutscene_MapMsgAudioCmds); // "Cheryl? Is that Cheryl!?"
            break;

        case 3:
            cherylChara.properties.player.headingAngle_124 = Q12(1.8f);

            func_80086728(&cherylChara, 2, 1, 0);
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 4:
            cherylChara.properties.player.headingAngle_124 = Q12(1.8f);
            func_80086728(&cherylChara, 2, 1, 0);
            break;

        case 5:
            g_SysWork.playerWork.player.position.vx = Q12(-26.0f);
            g_SysWork.playerWork.player.position.vz = Q12(127.0f);
            g_SysWork.playerWork.player.rotation.vy = Q12_ANGLE(-135.0f);

            func_800865FC(true, 0, 0, Q12_ANGLE(-135.0f), Q12(-29.0f), Q12(125.0f));
            SysWork_StateStepIncrement(0);

        case 6:
            func_800866D4(54, 1, false);
            break;

        case 7:
            if (Ipd_ChunkInitCheck())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 8:
            Map_MessageWithAudio(22, &g_Cutscene_MapMsgAudioIdx, g_Cutscene_MapMsgAudioCmds); // "Where are you going?"
            break;

        case 9:
            func_800865FC(true, 1, 0, Q12_ANGLE(-112.5f), Q12(-36.0f), Q12(119.5f));
            SysWork_StateStepIncrement(0);

        case 10:
            cherylChara.properties.player.headingAngle_124 = Q12(0.55f);
            func_80086728(&cherylChara, 1, 1, 0);
            break;

        case 11:
            Map_MessageWithAudio(23, &g_Cutscene_MapMsgAudioIdx, g_Cutscene_MapMsgAudioCmds); // "Hey wait...stop!"
            break;

        default:
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_4);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            sharedFunc_800D88C0_0_s00(&cherylChara, false);
            break;
    }

    #undef cherylChara
}

void MapEvent_CutsceneCherylRedirect0(void) // 0x800DAA68
{
    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800865FC(false, 0, 0, Q12_ANGLE(180.0f), Q12(0.0f), Q12(-1.0f));
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 24, 0, 0, 0, false); // "I'd better follow Cheryl..."
            break;

        case 4:
            func_800866D4(54, 1, false);
            break;

        default:
            // Restore player control.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

void MapEvent_CutsceneCherylRedirect1(void) // 0x800DAB8C
{
    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800865FC(false, 0, 0, Q12_ANGLE(90.0f), Q12(1.0f), Q12(0.0f));
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 24, 0, 0, 0, false); // "I'd better follow Cheryl..."
            break;

        case 4:
            func_800866D4(54, 1, false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

void MapEvent_CutsceneCherylRedirect2(void) // 0x800DACB0
{
    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800865FC(false, 0, 0, Q12_ANGLE(-90.0f), Q12(-1.0f), Q12(0.0f));
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 24, 0, 0, 0, false); // "I'd better follow Cheryl..."
            break;

        case 4:
            func_800866D4(54, 1, false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
    }
}

void MapEvent_CutsceneCherylRedirect3(void) // 0x800DADD4
{
    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800865FC(false, 0, 0, Q12(0.375f), Q12(0.7f), Q12(-0.7f));
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 24, 0, 0, 0, false); // "I'd better follow Cheryl..."
            break;

        case 4:
            func_800866D4(54, 1, false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapEvent_CutsceneCherylIntoTheAlley(void) // 0x800DAEFC
{
    q19_12 camPosY;
    q19_12 camPosZ;
    q19_12 playerOffsetZ0;
    q19_12 playerOffsetZ1;

    #define playerChara g_SysWork.playerWork.player
    #define cherylChara g_SysWork.npcs[0]

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            // Freeze player.
            Player_ControlFreeze();

            // Warp Cheryl to starting position in the alley.
            cherylChara.position.vx = Q12(-62.0f);
            cherylChara.rotation.vy = Q12_ANGLE(180.0f);
            cherylChara.position.vz = playerChara.position.vz - Q12(19.0f);

            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_800865FC(false, 0, 0, Q12_ANGLE(180.0f), Q12(0.0f), Q12(0.0f));

            // Warp camera.
            Camera_PositionSet(&playerChara.position,
                               Q12(0.24f), Q12(-4.06f), Q12(-5.0f),
                               Q12(0.0f), Q12(0.0f),
                               Q12(0.0f), Q12(0.0f),
                               true);
            Camera_LookAtSet(&playerChara.position,
                             Q12(-0.72f), Q12(-2.11f), Q12(-1.63f),
                             Q12(0.0f), Q12(0.0f),
                             Q12(0.0f), Q12(0.0f),
                             true);
            SysWork_StateStepIncrement(0);

        case 3:
            func_800866D4(53, 1, false);
            break;

        case 4:
            func_800865FC(true, 0, 0,
                         Q12_ANGLE(180.0f),
                         Q12(-62.0f), playerChara.position.vz - Q12(10.0f));
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 5:
            func_800866D4(54, 1, false);
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 6:
            func_800866D4(54, 1, false);

            camPosY        = Q12_MULT(Math_Cos(playerChara.rotation.vy), Q12(0.6f)) - Q12(1.84f);
            playerOffsetZ0 = Q12_MULT(Math_Cos(playerChara.rotation.vy), Q12(2.0f)) + Q12(4.0f);

            if ((playerChara.position.vz + playerOffsetZ0) < Q12(130.0f))
            {
                playerOffsetZ1 = Q12_MULT(Math_Cos(playerChara.rotation.vy), Q12(2.0f)) + Q12(4.0f);
                camPosZ        = playerChara.position.vz + playerOffsetZ1;
            }
            else
            {
                camPosZ = Q12(130.0f);
            }

            // Warp camera.
            Camera_PositionSet(NULL,
                               Q12(-62.0f), camPosY, camPosZ,
                               Q12(0.0f), Q12(0.0f),
                               Q12(0.0f), Q12(0.0f),
                               g_WarpCamera0);
            Camera_LookAtSet(NULL,
                             playerChara.position.vx, Q12(-0.7f), playerChara.position.vz - Q12(5.0f),
                             Q12(0.0f), Q12(0.0f),
                             Q12(0.0f), Q12(0.0f),
                             g_WarpCamera0);

            g_WarpCamera0 = false;
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            Savegame_EventFlagSet(EventFlag_7);
            Savegame_EventFlagSet(EventFlag_8);

            func_800865FC(true, 1, 0, Q12_ANGLE(180.0f), Q12(-62.0f), Q12(49.0f));
    }

    #undef playerChara
    #undef cherylChara
}

void func_800DB26C(void) // 0x800DB26C
{
    #define playerChara g_SysWork.playerWork.player
    #define cherylChara g_SysWork.npcs[0]

    // Warp camera.
    if (g_SysWork.sysStateSteps[0] == 0)
    {
        Camera_PositionSet(NULL,
                           Q12(-62.0f), Q12(-2.24f), Q12(117.0f),
                           Q12(0.0f), Q12(0.0f),
                           Q12(0.0f), Q12(0.0f),
                           true);
        Camera_LookAtSet(NULL,
                         Q12(-62.0f), Q12(-0.7f), Q12(104.0f),
                         Q12(0.0f), Q12(0.0f),
                         Q12(0.0f), Q12(0.0f),
                         true);
        func_800868DC(2);
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 2, Q12(0.0f), false);
            func_800865FC(true, 0, 0, Q12_ANGLE(-90.0f), Q12(-60.5f), playerChara.position.vz);

            // Warp Cheryl.
            cherylChara.position.vx = Q12(-62.0f);
            cherylChara.rotation.vy = Q12_ANGLE(180.0f);
            cherylChara.position.vz = playerChara.position.vz - Q12(9.0f);

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_800866D4(54, 1, false);
            break;

        case 3:
            g_DeltaTime >>= 1; // `/ 2`.

            func_800865FC(false, 0, 0, Q12_ANGLE(-135.0f), Q12(0.0f), Q12(0.0f));
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 4:
            g_DeltaTime >>= 1; // `/ 2`.

            Savegame_EventFlagSet(EventFlag_8);
            func_800866D4(54, 1, false);
            break;

        case 5:
            g_DeltaTime >>= 1;
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        default:
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_7);

            func_800865FC(true, 1, 0, Q12_ANGLE(180.0f), Q12(-62.0f), Q12(49.0f));
            Player_ControlUnfreeze(false);

            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    #undef playerChara
    #undef cherylChara
}

void MapEven_CutsceneAlleyGetsDarker(void) // 0x800DB514
{
    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800DFB5C = Q12(0.0f);
            D_800DFB60 = 0;

            GameFs_FlameGfxLoad();
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, true, 2, Q12(0.0f), false);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            SysWork_StateStepIncrement(0);

        case 4:
            MapMsg_DisplayAndHandleSelection(false, 25, 0, 0, 0, false); // "That's strange, it's getting darker."
            break;

        case 5:
            func_8008605C(EventFlag_16, 6, 5, false);
            break;

        case 6:
            if (D_800DFB60)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

            if (Fs_QueueChunksLoad())
            {
                D_800DFB60++;
                Chara_Load(1, ENEMY_CHARA_ID, &g_SysWork.npcBoneCoords[0], 0, NULL, NULL);
            }

        case 7:
            sharedFunc_800D209C_0_s00();
            SysWork_StateStepIncrement(0);

        case 8:
            func_80085EB8(1, &g_SysWork.playerWork.player, 0, false);
            break;

        case 9:
            Gfx_MapEffectsUpdate(10, 10, PrimitiveType_S32, &D_800DFB5C, 0, Q12(0.5f));
            SysWork_StateStepIncrement(0);

        case 10:
            D_800DFB5C += g_DeltaTime;

            if (D_800DFB5C > Q12(0.5f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 11:
            Savegame_EventFlagSet(EventFlag_17);
            MapMsg_DisplayAndHandleSelection(false, 30, 0, 0, 0, false); // "......better than nothing, I guess."
            break;

        default:
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);

            Chara_ProcessLoads();
            Chara_Spawn(ENEMY_CHARA_ID, 0, Q12(-252.0f), Q12(223.0f), Q12_ANGLE(180.0f), 5);
            Chara_Spawn(ENEMY_CHARA_ID, 1, Q12(-254.0f), Q12(221.0f), Q12_ANGLE(135.0f), 5);
            Chara_Spawn(ENEMY_CHARA_ID, 2, Q12(-259.0f), Q12(232.0f), Q12_ANGLE(0.0f),   5);
            break;
    }

    if (D_800DFB60 == 0)
    {
        if (Fs_QueueChunksLoad())
        {
            D_800DFB60++;
            Chara_Load(1, ENEMY_CHARA_ID, &g_SysWork.npcBoneCoords[0], 0, NULL, NULL);
        }
    }
}

void func_800DB870(void) // 0x800DB870
{
    typedef enum _EventState
    {
        EventState_Freeze     = 0,
        EventState_1          = 1,
        EventState_MsgDeadEnd = 2,
        EventState_Unfreeze   = 3
    } e_EventState;

    switch (g_SysWork.sysStateSteps[0])
    {
        case EventState_Freeze:
            // Freeze player.
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case EventState_1:
            func_80085DF0();
            break;

        case EventState_MsgDeadEnd:
            MapMsg_DisplayAndHandleSelection(false, 26, 0, 0, 0, false); // "A dead end? What the hell!?"
            break;

        default: // `EventState_Unfreeze`
            // Restore player control.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void MapEvent_CutsceneAlleyNightmare(void) // 0x800DB94C
{
    typedef enum _EventState
    {
        EventState_Initialize     = 0,
        EventState_1              = 1,
        EventState_2              = 2,
        EventState_3              = 3,
        EventState_LookAtDeadBody = 4
    } e_EventState;

    MATRIX  neck_lwm;
    SVECTOR offset;
    VECTOR  camPos; // Q19.12
    s32     i;

    // Control player and camera movement.
    switch (g_SysWork.sysStateSteps[0])
    {
        case EventState_3:
            // Warp camera.
            if (D_800DFACC == 0)
            {
                Camera_PositionSet(NULL,
                                   Q12(-254.63f), Q12(-0.77f), Q12(219.56f),
                                   Q12(0.0f), Q12(0.0f),
                                   Q12(0.0f), Q12(0.0f),
                                   true);
                Camera_LookAtSet(&g_SysWork.playerWork.player.position,
                                 Q12(0.0f), Q12(-0.6f), Q12(0.0f),
                                 Q12(0.0f), Q12(0.0f),
                                 Q12(0.0f), Q12(0.0f),
                                 true);
                D_800DFACC++;
            }

            // Warp camera.
            Camera_LookAtSet(&g_SysWork.playerWork.player.position,
                             Q12(0.0f), Q12(-0.6f), Q12(0.0f),
                             Q12(0.0f), Q12(0.0f),
                             Q12(0.0f), Q12(0.039f),
                             false);
            break;

        case EventState_LookAtDeadBody:
            if (D_800DFACC == 1)
            {
                bool warpCam = D_800DFACC;

                // Make player invisible.
                Model_AnimFlagsClear(&g_SysWork.playerWork.player.model, AnimFlag_Visible);

                // Warp camera.
                Camera_PositionSet(NULL,
                                   Q12(-250.81f), Q12(-0.32f), Q12(218.59f),
                                   Q12(0.0f), Q12(0.0f),
                                   Q12(0.0f), Q12(0.0f),
                                   warpCam);
                Camera_LookAtSet(NULL,
                                 Q12(-247.13f), Q12(-0.56f), Q12(217.04f),
                                 Q12(0.0f), Q12(0.0f),
                                 Q12(0.0f), Q12(0.0f),
                                 warpCam);

                // Warp player.
                Math_Vector3Set(&g_SysWork.playerWork.player.position, Q12(-251.12f), Q12(0.0f), Q12(218.56f));

                D_800DFACC++;
            }
            else
            {
                Math_SetSVectorFast(&offset, 0, -38, 0);

                Vw_CoordHierarchyMatrixCompute(&g_SysWork.playerBoneCoords[HarryBone_Head], &neck_lwm);

                // Load transformation matrix.
                gte_SetRotMatrix(&neck_lwm);
                gte_SetTransMatrix(&neck_lwm);

                // Transform offset into world-space.
                gte_ldv0(&offset);
                gte_rtv0tr();
                gte_stlvnl(&camPos);

                // Extract `camPos` from result.
                camPos.vx = Q8_TO_Q12(camPos.vx);
                camPos.vy = Q8_TO_Q12(camPos.vy);
                camPos.vz = Q8_TO_Q12(camPos.vz);

                // Set camera to look toward handing dead body.
                Camera_PositionSet(NULL,
                                   camPos.vx, camPos.vy, camPos.vz,
                                   Q12(0.0f), Q12(3.0f),
                                   Q12(0.0f), Q12(0.0f),
                                   false);
                Camera_LookAtSet(NULL,
                                 Q12(-247.43f), Q12(-1.0298f), Q12(217.34f),
                                 Q12(0.0f), Q12(0.0f),
                                 Q12(0.0f), Q12(0.0f),
                                 false);
            }
            break;

        case EventState_Initialize:
        case EventState_1:
        case EventState_2:
            break;

        default:
            // Restore player control.
            Model_AnimFlagsSet(&g_SysWork.playerWork.player.model, AnimFlag_Visible);
            vcReturnPreAutoCamWork(true);
            break;
    }

    // Control audio, messages, and game states.
    switch (g_SysWork.sysStateSteps[0])
    {
        case EventState_Initialize:
            Player_ControlFreeze();

            Map_PlaceIpdAtCell(FILE_BG_THRF908_IPD, -7, 6);
            Sd_SfxStop(Sfx_Unk1358);
            Sd_PlaySfx(Sfx_Unk1359, 0, 208);
            func_800865FC(true, 0, 0, Q12_ANGLE(180.0f), Q12(-252.0f), Q12(219.0f));
            func_800865FC(true, 0, 1, Q12_ANGLE(112.5f), Q12(-251.0f), Q12(218.5f));

            D_800DFB61 = 0;

            SysWork_StateStepIncrement(0);

        case EventState_1:
            SysWork_StateStepIncrementAfterFade(2, true, 2, Q12(0.0f), false);
            break;

        case EventState_2:
            func_80085DF0();
            break;

        case EventState_3:
            func_800866D4(53, 2, 0);
            break;

        case EventState_LookAtDeadBody:
            Map_MessageWithAudio(27, &D_800DFB61, &D_800DFAC8); // "What is this?"
            break;

        default:
            // Restore player control.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            // Make all Grey Children aggressive.
            for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs); i++)
            {
                if (g_SysWork.npcs[i].model.charaId == ENEMY_CHARA_ID)
                {
                    g_SysWork.npcs[i].model.controlState = 0;
                    g_SysWork.npcs[i].model.stateStep    = 6;
                }
            }
            break;
    }
}

void func_800DBE00(void) // 0x800DBE00
{
    Sd_SfxStop(Sfx_Unk1359);
    Sd_SfxStop(Sfx_Unk1361);
    Sd_SfxStop(Sfx_Unk1360);

    SD_Call(22);
    func_800892A4(4);

    SysWork_StateSetNext(SysState_Gameplay);
    g_SysWork.playerWork.player.position.vy = Q12(0.0f);
}

void Map_WorldObjectsInit(void) // 0x800DBE68
{
    s32 rotXy;

    WorldObject_ModelNameSet(&D_800E3A5C[0], "WHEEL1_H");
    WorldObject_ModelNameSet(&D_800E3A5C[1], "WHEEL2_H");

    D_800E3A9C.vx = Q12(-268.32f);
    D_800E3A9C.vy = Q12(-0.44f);
    D_800E3A9C.vz = Q12(245.72f);

    rotXy = 0xFAE4FE17; // @hack `vx` and `vy` combined into `s32`.
    D_800E3AAC.vz = 0;

    Savegame_EventFlagClear(EventFlag_188);
    *(s32*)&D_800E3AAC.vx = rotXy;
}

void Map_WorldObjectsUpdate(void) // 0x800DBF08
{
    VECTOR3 viewPos;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    vwGetViewPosition(&viewPos);

    if (Savegame_EventFlagGet(EventFlag_4) && !Savegame_EventFlagGet(EventFlag_13))
    {
        if (!Savegame_EventFlagGet(EventFlag_6))
        {
            func_800DC33C();
        }
        else if (!Savegame_EventFlagGet(EventFlag_9))
        {
            func_800DC694();
        }
        else if (!Savegame_EventFlagGet(EventFlag_11))
        {
            func_800DC8D8();
        }

        func_800DCA30();
    }

    if (Savegame_EventFlagGet(EventFlag_13) && !Savegame_EventFlagGet(EventFlag_16))
    {
        func_800DCC54();
    }

    if (Savegame_EventFlagGet(EventFlag_17))
    {
        func_800DD0CC();
    }

    if (!Savegame_EventFlagGet(EventFlag_24))
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -7, -1, -7) &&
            (PLAYER_IN_MAP_CHUNK(vz, 1, 6, -1, 6) || PLAYER_IN_MAP_CHUNK(vz, 1, 7, -1, 7)))
        {
            // Spin wheelchair wheel?
            D_800E3AAC.vz += Q12_MULT_PRECISE(g_DeltaTime, (Q12_ANGLE(-90.0f) - (Rng_Rand16() & 0x1FF)));
            WorldGfx_ObjectAdd(&D_800E3A5C[0], &D_800E3A9C, &D_800E3AAC);
            WorldGfx_ObjectAdd(&D_800E3A5C[1], &D_800E3A9C, &D_800E3AAC);

            if (g_SysWork.bgmStatusFlags & BgmStatusFlag_6)
            {
                Savegame_EventFlagClear(EventFlag_188);
            }

            if (!Savegame_EventFlagGet(EventFlag_188))
            {
                Sd_SfxStop(Sfx_Unk1361);
                SD_Call(Sfx_Unk1358);
                Savegame_EventFlagSet(EventFlag_188);
            }

            if (!Savegame_EventFlagGet(EventFlag_24))
            {
                func_8005DE0C(Sfx_Unk1358, &D_800E3A9C, Q8(0.25f), Q12(8.0f), 0);
            }
        }
    }
}

void MapEvent_GreyChildrenSpawn(void) // 0x800DC1E8
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (Savegame_EventFlagGet(EventFlag_17) && g_SysWork.npcs[0].model.charaId == Chara_None)
    {
        if (PLAYER_IN_MAP_CHUNK(vx, 1, -7, -1, -7) && PLAYER_IN_MAP_CHUNK(vz, 1, 7, -1, 7))
        {
            Chara_Spawn(ENEMY_CHARA_ID, 0, Q12(-252.0f), Q12(223.0f), Q12_ANGLE(180.0f), 5);
            Chara_Spawn(ENEMY_CHARA_ID, 1, Q12(-254.0f), Q12(221.0f), Q12_ANGLE(135.0f), 5);
            Chara_Spawn(ENEMY_CHARA_ID, 2, Q12(-259.0f), Q12(232.0f), Q12_ANGLE(0.0f),   5);
        }
    }
}

void func_800DC33C(void) // 0x800DC33C
{
    VECTOR3 camPos;
    s16     temp_a0;
    s16     var_s1;
    q19_12  temp_a0_2;
    s32     temp_v1;
    s32     var_a0;
    s32     var_a2;
    s32     var_v1_2;

    if (!Savegame_EventFlagGet(EventFlag_5))
    {
        func_800865FC(true, 1, 0, Q12_ANGLE(180.0f), Q12(-62.0f), Q12(108.0f));
        sharedFunc_800D88AC_0_s00(&g_SysWork.npcs[0]);

        Savegame_EventFlagSet(EventFlag_5);
    }

    vwGetViewPosition(&camPos);
    if (Math_Vector2MagCalc(g_SysWork.npcs[0].position.vx - camPos.vx,
                            g_SysWork.npcs[0].position.vz - camPos.vz) <= Q12(16.5f) &&
        g_SysWork.npcs[0].position.vx >= Q12(-58.0f))
    {
        if (!(g_SysWork.flags_22A4 & UnkSysFlag_MenuOpen))
        {
            if (!Vw_AabbVisibleInScreenCheck(g_SysWork.npcs[0].position.vx - Q12(1.0f),
                                             g_SysWork.npcs[0].position.vx + Q12(1.0f),
                                             g_SysWork.npcs[0].position.vy - Q12(1.5f),
                                             g_SysWork.npcs[0].position.vy,
                                             g_SysWork.npcs[0].position.vz - Q12(1.0f),
                                             g_SysWork.npcs[0].position.vz + Q12(1.0f)))
            {
block7:
                g_SysWork.npcs[0].position.vz = 1;
                g_SysWork.npcs[0].position.vx = 1;
                g_SysWork.npcs[0].properties.player.headingAngle_124 = Q12_ANGLE(0.0f);

                sharedFunc_800D88C0_0_s00(&g_SysWork.npcs[0], false);

                Savegame_EventFlagSet(EventFlag_6);
                return;
            }
        }

        var_s1 = Math_AngleNormalizeSigned(ratan2(g_SysWork.npcs[0].position.vx - g_SysWork.playerWork.player.position.vx,
                                      g_SysWork.npcs[0].position.vz - g_SysWork.playerWork.player.position.vz) -
                               g_SysWork.playerWork.player.headingAngle);

        temp_a0 = Math_AngleNormalizeSigned(ratan2(Q12(-62.0f) - g_SysWork.playerWork.player.position.vx,
                                       Q12(106.0f) - g_SysWork.playerWork.player.position.vz) -
                                g_SysWork.playerWork.player.headingAngle);

        if (ABS(var_s1) > ABS(temp_a0))
        {
            var_s1 = temp_a0;
        }
        var_a0 = var_s1 << 16;

        // TODO: Why shift 16?
        temp_a0_2 = (g_SysWork.playerWork.player.moveSpeed * Math_Cos(var_a0 >> 16) * 16) >> 16;
        if (temp_a0_2 > Q12(1.8f))
        {
            D_800DFAD0 = temp_a0_2 + Q12(0.9f);
        }
        else if (D_800DFAD0 > Q12(1.8f))
        {
            var_a2 = Q12(1.8f);
            temp_v1 = D_800DFAD0 - Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.5f);
            if (temp_v1 >= Q12(1.8f))
            {
                var_a2 = temp_v1;
            }
            D_800DFAD0 = var_a2;
        }
        else
        {
            var_v1_2 = D_800DFAD0 + Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.5f);
            if (var_v1_2 > Q12(1.8f))
            {
                var_v1_2 = Q12(1.8f);
            }
            D_800DFAD0 = var_v1_2;
        }

        g_SysWork.npcs[0].properties.player.headingAngle_124 = D_800DFAD0;
        func_8008677C(&g_SysWork.npcs[0], 2, 1);
        return;
    }

    // TODO: Remove `goto`.
    goto block7;
}

void func_800DC694(void) // 0x800DC694
{
    q19_12 mag;
    s32    temp_a0_2;
    s32    temp_v1;
    s32    var_a2;
    s32    var_v1;

    mag = Math_Vector2MagCalc(g_SysWork.npcs[0].position.vx - g_SysWork.playerWork.player.position.vx,
                              (g_SysWork.npcs[0].position.vz - g_SysWork.playerWork.player.position.vz) - Q12(2.0f));

    if (!Savegame_EventFlagGet(EventFlag_7))
    {
        sharedFunc_800D88AC_0_s00(&g_SysWork.npcs[0]);
        return;
    }

    if (mag <= Q12(14.5f) && g_SysWork.npcs[0].position.vz >= Q12(49.0f))
    {
        if (!(g_SysWork.flags_22A4 & UnkSysFlag_MenuOpen))
        {
            if (!Vw_AabbVisibleInScreenCheck(g_SysWork.npcs[0].position.vx - Q12(1.0f),
                                             g_SysWork.npcs[0].position.vx + Q12(1.0f),
                                             g_SysWork.npcs[0].position.vy - Q12(1.5f),
                                             g_SysWork.npcs[0].position.vy,
                                             g_SysWork.npcs[0].position.vz - Q12(1.0f),
                                             g_SysWork.npcs[0].position.vz + Q12(1.0f)))
            {
block7:
                g_SysWork.npcs[0].position.vz = 1;
                g_SysWork.npcs[0].position.vx = 1;

                sharedFunc_800D88C0_0_s00(&g_SysWork.npcs[0], false);

                Savegame_EventFlagSet(EventFlag_9);
                return;
            }
        }

        temp_a0_2 = Q12_MULT(g_SysWork.playerWork.player.moveSpeed, Math_Cos(g_SysWork.playerWork.player.headingAngle + Q12_ANGLE(180.0f)));
        if (temp_a0_2 > Q12(1.8f))
        {
            D_800DFAD4 = temp_a0_2 + Q12(0.6f);
        }
        else if (D_800DFAD4 > Q12(1.8f))
        {
            var_a2 = Q12(1.8f);
            temp_v1 = D_800DFAD4 - Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.5f);
            if (temp_v1 >= Q12(1.8f))
            {
                var_a2 = temp_v1;
            }
            D_800DFAD4 = var_a2;
        }
        else
        {
            var_v1 = D_800DFAD4 + Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.5f);
            if (var_v1 > Q12(1.8f))
            {
                var_v1 = Q12(1.8f);
            }
            D_800DFAD4 = var_v1;
        }

        g_SysWork.npcs[0].properties.player.headingAngle_124 = D_800DFAD4;

        func_8008677C(&g_SysWork.npcs[0], 2, 1);
        return;
    }

// TODO: Remvoe `goto`.
block_7:
    goto block7;
}

void func_800DC8D8(void) // 0x800DC8D8
{
    q19_12 mag;

    mag = Math_Vector2MagCalc(g_SysWork.npcs[0].position.vx - g_SysWork.playerWork.player.position.vx,
                              (g_SysWork.npcs[0].position.vz - g_SysWork.playerWork.player.position.vz) - Q12(2.0f));

    if (!Savegame_EventFlagGet(EventFlag_10))
    {
        g_SysWork.npcs[0].position.vx = Q12(-61.0f);
        g_SysWork.npcs[0].position.vz = Q12(48.0f);
        g_SysWork.npcs[0].rotation.vy = Q12_ANGLE(90.0f);

        if (mag < Q12(14.8f))
        {
            sharedFunc_800D88AC_0_s00(&g_SysWork.npcs[0]);

            Savegame_EventFlagSet(EventFlag_10);

            func_800865FC(true, 1, 0, Q12_ANGLE(90.0f), Q12(-57.0f), Q12(47.0f));
        }
    }
    else
    {
        g_SysWork.npcs[0].properties.player.headingAngle_124 = Q12(1.8f);

        func_8008677C(&g_SysWork.npcs[0], 2, 1);

        if (g_SysWork.npcs[0].position.vx > Q12(-58.0f))
        {
            Savegame_EventFlagSet(EventFlag_11);
            g_SysWork.npcs[0].model.charaId = Chara_None;

            func_8005DC1C(Sfx_Unk1354, &QVECTOR3(-57.0f, -1.0f, 47.0f), Q8(0.5f), 0);
        }
    }
}

void func_800DCA30(void) // 0x800DCA30
{
    q19_12 camPosX;
    q19_12 camPosY;
    q19_12 camPosZ;
    q19_12 playerPosX;
    q19_12 playerPosZ;
    q3_12  playerRotY;
    float  four; // @hack Permuter find.

    playerPosX = g_SysWork.playerWork.player.position.vx;
    playerPosZ = g_SysWork.playerWork.player.position.vz;
    playerRotY = g_SysWork.playerWork.player.rotation.vy;

    if (Savegame_EventFlagGet(EventFlag_8))
    {
        // Warp camera.
        if (playerPosZ < Q12(48.0f) && playerPosX > Q12(-59.0f))
        {
            Camera_PositionSet(NULL,
                               Q12(-60.55f), Q12(-0.51f), Q12(47.63f),
                               Q12(0.0f), Q12(0.0f),
                               Q12(0.0f), Q12(0.0f),
                               g_WarpCamera);
            Camera_LookAtSet(NULL,
                             Q12(-56.91f), Q12(-1.26f), Q12(46.14f),
                             Q12(0.0f), Q12(0.0f),
                             Q12(0.0f), Q12(0.0f),
                             g_WarpCamera);
            g_WarpCamera = false;
            return;
        }

        // Warp camera.
        if (playerPosZ < Q12(100.0f) || (playerPosZ < Q12(121.0f) && playerPosX < Q12(-58.0f)))
        {
            four = 4.0f;

            camPosY  = Q12_MULT(Math_Cos(playerRotY), Q12(0.2f)) - Q12(1.8f);
            camPosZ  = playerPosZ;
            camPosZ += Q12_MULT(Math_Cos(playerRotY), Q12(2.0f)) + Q12(four);
            camPosX  = MAX(MIN(Q12(-61.5f), playerPosX), Q12(-63.5f));

            Camera_PositionSet(NULL,
                               camPosX, camPosY, camPosZ,
                               Q12(0.0f), Q12(0.0f),
                               Q12(0.0f), Q12(0.0f),
                               !g_WarpCamera);
            Camera_LookAtSet(NULL,
                             playerPosX, Q12(-0.7f), playerPosZ - Q12(5.0f),
                             Q12(0.0f), Q12(0.0f),
                             Q12(0.0f), Q12(0.0f),
                             !g_WarpCamera);
            g_WarpCamera = true;
            return;
        }

        vcReturnPreAutoCamWork(g_WarpCamera);
        g_WarpCamera = false;
    }
}

void func_800DCC54(void) // 0x800DCC54
{
    if (D_800DFADC == NO_VALUE)
    {
        Gfx_MapEffectsUpdate(6, 6, PrimitiveType_S32, &D_800DFADC, Q12(0.0f), Q12(100.0f));
        D_800DFADC = Q12(0.0f);

        Sd_PlaySfx(Sfx_Unk1359, 0, Q8(7.0f / 8.0f));
    }

    if (Savegame_EventFlagGet(EventFlag_14))
    {
        if (!Savegame_EventFlagGet(EventFlag_18))
        {
            sharedFunc_800D0B18_0_s00(6);
            Savegame_EventFlagSet(EventFlag_18);
            Sd_PlaySfx(Sfx_Unk1359, 0, Q8(0.75f));

            D_800DFADC = Q12(60.0f);
        }

        D_800DFADC = func_800DCF38(D_800DFADC);
    }
    else
    {
        D_800DFADC = func_800DCDA8();
    }

    if (D_800DFADC >= Q12(80.0f))
    {
        Savegame_EventFlagSet(EventFlag_15);
    }

    if (D_800DFADC >= Q12(100.0f))
    {
        Savegame_EventFlagSet(EventFlag_16);
    }
}

s32 func_800DCDA8(void) // 0x800DCDA8
{
    s16 sp20;
    s32 i;
    s32 var_s2;
    s16 var_s5;
    s32 var_s4;
    s32 temp_v1_3;

    var_s4 = 0;
    var_s5 = 0;
    var_s2 = 0;

    for (i = 0; i < 5; i++)
    {
        temp_v1_3 = func_8005C478(&sp20,
                                  g_SysWork.playerWork.player.position.vx, g_SysWork.playerWork.player.position.vz,
                                  D_800DFAE0[i].vx, D_800DFAE0[i].vy,
                                  D_800DFAE0[i + 1].vx, D_800DFAE0[i + 1].vy);

        if (i == 0)
        {
            var_s4 = temp_v1_3;
            var_s5 = sp20;
            var_s2 = 0;
        }
        else if (temp_v1_3 < var_s4)
        {
            var_s4 = temp_v1_3;
            var_s5 = sp20;
            var_s2 = i;
        }
    }

    return Q12_MULT_PRECISE(D_800DFAE0[var_s2 + 1].vz - D_800DFAE0[var_s2].vz, var_s5) + D_800DFAE0[var_s2].vz;
}

s32 func_800DCF38(s32 arg0) // 0x800DCF38
{
    s16 sp20;
    s32 var_t0;
    s32 var_v0;

    var_t0 = 0;

    if (g_SysWork.sysState == SysState_EventCallback)
    {
        if (!Savegame_EventFlagGet(EventFlag_15))
        {
            return arg0;
        }
    }
    else
    {
        if (!Savegame_EventFlagGet(EventFlag_15))
        {
            if (g_SysWork.playerWork.player.position.vx < Q12(-200.0f))
            {
                func_8005C478(&sp20,
                              g_SysWork.playerWork.player.position.vx, g_SysWork.playerWork.player.position.vz,
                              D_800DFB28[0].vx, D_800DFB28[0].vy, D_800DFB28[1].vx, D_800DFB28[1].vy);

                var_v0 = Q12_MULT_PRECISE(D_800DFB28[1].vz - D_800DFB28[0].vz, sp20) + Q12(60.0f);
                var_t0 = D_800DFB28[0].vz + var_v0;
            }

            return MAX(var_t0, arg0);
        }
    }

    return Q12_MULT_PRECISE(g_DeltaTime, Q12(9.0f)) + arg0;
}

void func_800DD0CC(void) // 0x800DD0CC
{
    s32 vecs[2];

    if (D_800DFB40 == NO_VALUE)
    {
        Gfx_MapEffectsUpdate(6, 6, PrimitiveType_S32, &D_800DFB40, 0, Q12(100.0f));
        D_800DFB40 = 0;
    }

    D_800DFB44.field_0 += g_DeltaTime;

    vecs[0] = FP_MULTIPLY(D_800DFB44.field_0, D_800DFB48.field_0, 6);
    if (vecs[0] >= Q12(1.0f))
    {
        D_800DFB44.field_0 = 0;
        D_800DFB48.field_0 = Rng_GenerateUInt(32, 95);
        D_800DFB48.field_1 = Rng_GenerateUInt(32, 63);
        vecs[0]           &= Q12_FRACT(vecs[0]);
    }

    vecs[0] = Q12_MULT(D_800DFB48.field_1, Math_Sin(D_800DFB44.field_2));
    D_800DFB44.field_2 += g_DeltaTime;

    vecs[1] = FP_MULTIPLY(D_800DFB44.field_2, D_800DFB48.field_2, 6);
    if (vecs[1] >= Q12(1.0f))
    {
        D_800DFB44.field_2 = 0;
        D_800DFB48.field_2 = Rng_GenerateUInt(32, 95);
        vecs[1]           &= Q12_FRACT(vecs[1]);
    }

    D_800DFB40 = MAX(Q12(0.0f), Q12_MULT((FP_MULTIPLY(vecs[0], Q12(4.5f), 6) + Q12(2.5f)), Math_Sin(vecs[1])) + Q12(4.0f));
}
