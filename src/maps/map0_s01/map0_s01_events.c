#include "bodyprog/bodyprog.h"
#include "bodyprog/gfx/screen_draw.h"
#include "bodyprog/math/math.h"
#include "main/rng.h"
#include "maps/map0/map0_s01.h"
#include "maps/shared.h"

extern VECTOR3 g_CutsceneCameraLookAtTarget;
extern s32 g_Timer0;
extern u8 g_SoundCmdIdx;
extern const VECTOR3 D_800CC8FC;
extern const char D_800CC908[];
extern const char D_800CC910[];

void Event_CafeCutscene()
{
    #define CUTSCENE_SKIP_STATE 52

    u8              temp_s0_5;
    s_SubCharacter* chara0;
    s_SubCharacter* chara1;

    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C[0] > 5 && g_SysWork.sysStateStep_C[0] < 47)
    {
        SysWork_NextStateStepSet(CUTSCENE_SKIP_STATE);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            
            g_SysWork.field_30 = 20;
            g_Screen_FadeStatus = SCREEN_FADE_STATUS(ScreenFadeState_ResetTimeStep, false);
            g_SysWork.flags_22A4 |= 1 << 3;
            g_SavegamePtr->flags_AC &= ~(1 << 0);
            g_SysWork.flags_22A4 |= (1 << 5) | (1 << 9);
            g_SoundCmdIdx = 0;
            D_800DE250 = 0;
            D_800DE251 = 0;
            
            Fs_QueueStartRead(FILE_ANIM_CAFE_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets(FS_BUFFER_11);
            Chara_Load(0, Chara_Cybil, &g_SysWork.npcCoords_FC0[0], NO_VALUE, NULL, NULL);
            func_80088D0C();
            Chara_Spawn(Chara_Cybil, 0, FP_METER(4.4f), FP_METER(269.9f), FP_METER(0.0f), 2);
            
            g_Timer0 = 0;
            SysWork_StateStepIncrement();
        
        case 1:
            func_80087EDC(9);
            break;
        
        case 2:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 77, false);
            func_8008616C(0, false, 0, FP_TIME(0.0f), false);
            func_800D2054();
            SysWork_StateStepIncrement();
            break;
        
        case 3:
            func_80085EB8(2, &g_SysWork.player_4C.chara_0, NULL, false);
            SysWork_StateStepIncrement();
        
        case 4:
            func_8008616C(1, false, 0, FP_TIME(0.0f), false);
            break;
        
        case 5:
            func_80085EB8(3, &g_SysWork.player_4C.chara_0, NULL, false);
            SysWork_StateStepIncrement();
        
        case 6:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(7.8f), FP_TIME(0.0f), FP_TIME(5.0f), false, true);
            break;
        
        case 7:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(7.8f), FP_TIME(0.0f), FP_TIME(26.0f), true, false);
            func_800869E4(15, &g_SoundCmdIdx, g_SoundCmds); // "Was I dreaming?"
            break;
        
        case 8:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(7.8f), FP_TIME(0.0f), FP_TIME(26.0f), true, true);
            break;
        
        case 9:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 78, false);
            D_800DE250 = 1;
            SysWork_StateStepIncrement();
        
        case 10:
        case 11:
        case 12:
        case 13:
            switch (g_SysWork.sysStateStep_C[0])
            {
                case 10:
                    func_800869E4(16, &g_SoundCmdIdx, g_SoundCmds); // "How do you feel?"
                    break;

                case 11:
                    func_800869E4(17, &g_SoundCmdIdx, g_SoundCmds); // "Like I've been hit..."
                    break;

                case 12:
                    if (g_Timer0 == FP_TIME(48.0f) && D_800DE251 == 2)
                    {
                        SysWork_NextStateStepSet(13);
                    }
                    break;

                case 13:
                    func_800869E4(18, &g_SoundCmdIdx, g_SoundCmds); // "Glad to hear it."
                    break;
            }

            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(4.0f), FP_TIME(27.0f), FP_TIME(48.0f), true, false);

            if (D_800DE251 == 0 && g_Timer0 > FP_TIME(38.0f))
            {
                func_80085EB8(0, &g_SysWork.npcs_1A0[0], 10, false);
                func_80085EB8(0, &g_SysWork.player_4C.chara_0, 110, false);
                
                D_800DE251++;
            }

            temp_s0_5 = D_800DE251;
            if (D_800DE251 == 1 && sharedFunc_800D8964_0_s00(&g_SysWork.npcs_1A0[0]) == temp_s0_5)
            {
                func_80085EB8(0, &g_SysWork.npcs_1A0[0], 0xB, false);
                D_800DE251++;
            }
            break;

        case 14:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(3.0f), FP_TIME(49.0f), FP_TIME(139.0f), true, false);
            func_800869E4(25, &g_SoundCmdIdx, g_SoundCmds); // "Have you seen a little girl?"
            break;

        case 15:
            g_Timer0 = FP_TIME(140.0f);
            SysWork_StateStepIncrement();

        case 16:
            func_800869E4(35, &g_SoundCmdIdx, g_SoundCmds); // "What's your name?"
            break;

        case 17:
            func_80085E6C(FP_TIME(1.2f), false);
            break;

        case 18:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 93, false);
            SysWork_StateStepIncrement();

        case 19:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(141.0f), FP_TIME(152.0f), false, true);
            break;

        case 20:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 53, false);
            SysWork_StateStepIncrement();

        case 21:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(141.0f), FP_TIME(159.0f), true, true);
            func_8004729C(4108);
            break;

        case 22:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 7, false);
            Sd_EngineCmd(4108);
            SysWork_StateStepIncrement();

        case 23:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(160.0f), FP_TIME(173.0f), true, false);
            MapMsg_DisplayAndHandleSelection(false, 43, 0, 0, 0, false);
            Gfx_DebugStringPosition(30, 30);
            break;

        case 24:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x47, false);
            SysWork_StateStepIncrement();

        case 25:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(174.0f), FP_TIME(184.0f), true, false);
            func_800869E4(44, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 26:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 51, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 8, 0);
            SysWork_StateStepIncrement();

        case 27:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(185.0f), FP_TIME(194.0f), true, false);
            func_800869E4(45, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 28:
            g_Timer0 = FP_TIME(195.0f);

            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            SysWork_StateStepIncrement();

        case 29:
            func_800869E4(46, &g_SoundCmdIdx, g_SoundCmds); // "It's dangerous out there."
            break;

        case 30:
            func_80085E6C(FP_TIME(1.5f), false);
            break;

        case 31:
            func_800869E4(49, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 32:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);
            SysWork_StateStepIncrement();

        case 33:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(20.0f), FP_TIME(207.0f), FP_TIME(222.0f), true, true);
            break;

        case 34:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 6, false);
            SysWork_StateStepIncrement();

        case 35:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(5.0f), FP_TIME(223.0f), FP_TIME(251.0f), true, false);
            func_800869E4(51, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 36:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(5.0f), FP_TIME(223.0f), FP_TIME(251.0f), true, false);
            func_80085E6C(FP_TIME(0.6f), false);
            break;

        case 37:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(5.0f), FP_TIME(223.0f), FP_TIME(251.0f), true, false);
            func_800869E4(55, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 38:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 9, false);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x4C, false);
            SysWork_StateStepIncrement();

        case 39:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(252.0f), FP_TIME(280.0f), true, false);
            func_800869E4(57, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 40:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(252.0f), FP_TIME(280.0f), true, true);
            break;

        case 41:
            func_80085EB8(0, g_SysWork.npcs_1A0, 5, false);
            SysWork_StateStepIncrement();

        case 42:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(281.0f), FP_TIME(296.0f), true, true);
            break;

        case 43:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 0x33, false);
            g_Timer0 = FP_TIME(297.0f);
            SysWork_StateStepIncrement();

        case 44:
            func_800869E4(58, &g_SoundCmdIdx, g_SoundCmds);
            break;

        case 45:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 90, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 1, false);
            SysWork_StateStepIncrement();

        case 46:
            sharedFunc_800DA8E8_0_s01(&g_Timer0, FP_TIME(10.0f), FP_TIME(298.0f), FP_TIME(308.0f), true, true);
            break;

        case 47:
            D_800DE250 = 0;

            func_8005DC1C(Sfx_Unk1357, &D_800CC8FC, FP_VOLUME(0.5f), 0);
            SysWork_StateStepIncrement();

        case 48:
            func_80088F94(g_SysWork.npcs_1A0,0 ,0);
            Sd_EngineCmd(19);
            Chara_Load(0, Chara_AirScreamer, &g_SysWork.npcCoords_FC0[0], NO_VALUE, 0, 0);
            func_80086470(3, InventoryItemId_Handgun, HANDGUN_AMMO_PICKUP_ITEM_COUNT, false);
            SysWork_StateStepIncrement();

        case 49:
            func_8008616C(2, true, 0, FP_TIME(0.0f), false);
            break;

        case 50:
            g_Timer0 = FP_TIME(308.0);
            func_80085E6C(FP_TIME(0.5f), false);
            break;

        case 51:
            SysWork_StateStepReset();
            break;

        case CUTSCENE_SKIP_STATE:
            func_8008616C(2, true, 0, FP_TIME(0.0f), false);
            break;

        case 53:
            //SysWork_NextStateStepSet(48); // TODO: Doesn't match?
            g_SysWork.sysStateStep_C[0] = 48;
            g_SysWork.field_28          = 0;
            g_SysWork.sysStateStep_C[1] = 0;
            g_SysWork.timer_2C          = 0;
            g_SysWork.sysStateStep_C[2] = 0;
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);

            vcReturnPreAutoCamWork(1);
            func_8008616C(0, false, 2, FP_TIME(0.0f), false);
            func_8008616C(0, false, 0, FP_TIME(0.0f), false);
            Sd_EngineCmd(23);

            Savegame_EventFlagSet(EventFlag_49);
            g_Timer0 = NO_VALUE;
            break;
    }

    if (g_Timer0 >= FP_TIME(0.0f))
    {
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPositionTarget, &g_CutsceneCameraLookAtTarget, NULL, g_Timer0, FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAtTarget, NULL, true);
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, &D_800CC908, g_Timer0, FS_BUFFER_11);

        if (D_800DE250 != 0)
        {
            chara0 = &g_SysWork.npcs_1A0[0];
            chara0->model_0.anim_4.flags_2 |= AnimFlag_Visible;
            Dms_CharacterGetPosRot(&chara0->position_18, &chara0->rotation_24, &D_800CC910, g_Timer0, FS_BUFFER_11);
            return;
        }

        chara1 = &g_SysWork.npcs_1A0[0];
        chara1->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
    }
}

void Event_ToBeContinued(void) // 0x800DB790
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();

        case 1:
            func_8008616C(0, true, 0, FP_TIME(0.0f), false);
            func_800862F8(0, FILE_TIM_CONTINUE_TIM, false);
            SysWork_StateStepIncrement();

        case 2:
            func_8008616C(1, true, 0, FP_TIME(0.0f), false);
            return;

        case 3:
            func_800862F8(1, FILE_1ST_2ZANKO80_TIM, false);
            return;

        case 4:
            func_8008616C(0, false, 0, FP_TIME(2.0f), false);
            SysWork_StateStepIncrement();

        case 5:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SysWork_StateStepIncrement();
            }

            func_80085E6C(FP_TIME(4.0f), false);

            if (g_SysWork.sysStateStep_C[0] == 7)
            {
                g_SysWork.sysStateStep_C[0] = 6;
            }
            break;

        case 7:
            func_800862F8(7, FILE_TIM_COMESOON_TIM, false);
            break;

        case 8:
            func_8008616C(0, false, 0, FP_TIME(1.5f), false);
            func_8004690C(Sfx_Unk1321);
            func_8004690C(Sfx_Unk1322);
            SysWork_StateStepIncrement();

        case 9:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SysWork_StateStepIncrement();
            }

            func_80085E6C(FP_TIME(4.0f), false);

            if (g_SysWork.sysStateStep_C[0] == 11)
            {
                g_SysWork.sysStateStep_C[0] = 10;
                break;
            }
            break;

        case 6:
        case 10:
            func_800862F8(2, FILE_1ST_2ZANKO80_TIM, false);
            func_8008616C(2, true, 0, FP_TIME(1.5f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);
            Game_WarmBoot();

            g_SysWork.field_22A0 |= 1 << 0;
            break;
    }
}

const VECTOR3 D_800CCA1C =
{
    0x00000CCC,
    0xFFFFE99A,
    0x0010BB33,
};

const VECTOR3 D_800CCA28 =
{
    0x000004CC,
    0xFFFFE99A,
    0x0010BB33,
};

const VECTOR3 D_800CCA34 =
{
    0x00000CCC,
    0xFFFFE334,
    0x0010BB33,
};

const VECTOR3 D_800CCA40 =
{
    0x00000CCC,
    0xFFFFE99A,
    0x00111E66,
};

const VECTOR3 D_800CCA4C =
{
    0x000004CC,
    0xFFFFE99A,
    0x00111E66,
};

const VECTOR3 D_800CCA58 =
{
    0x00000CCC,
    0xFFFFE334,
    0x00108199,
};

const char D_800CCA64[] = "BIRD";

#define EventPositionInit(eventPos, x, y, z, arg4, arg5) \
    EventPositionSet(eventPos, FP_METER(x), FP_METER(y), FP_METER(z), arg4, arg5)

static inline void EventPositionSet(s_EventPosition* eventPos, s32 x, s32 y, s32 z, s32 arg4, s16 arg5)
{
    Math_Vector3Set(&eventPos->position_0, x, y, z);
    eventPos->field_C  = arg4;
    eventPos->field_10 = arg5;
}

void Event_AirScreamerIntroCutscene() // 0x800DBAA0
{
    s32 var_a1;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8003A16C();

            Savegame_EventFlagSet(EventFlag_50);

            Sd_EngineCmd(1321);
            Sd_EngineCmd(1322);

            Savegame_EventFlagSet(EventFlag_52);

            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = FP_METER(1.3f);
            g_SysWork.player_4C.chara_0.position_18.vz = FP_METER(269.7f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(5.0f);

            g_Timer0 = FP_TIME(26.0f);

            func_8008616C(0, true, 3, FP_TIME(0.0f), false);

            g_SoundCmdIdx = 0;
            SysWork_StateStepIncrement();

        case 1:
            func_80087EDC(30);
            break;

        case 2:
            func_80085DF0();
            break;

        case 3:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 91, 0);
            SysWork_StateStepIncrement();

        case 4:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(15.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(37.0f));
            if (g_Timer0 >= FP_TIME(37.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 5:
            func_800869E4(62, &g_SoundCmdIdx, &D_800DE124); // "What's that?"
            break;

        case 6:
            func_80085E6C(FP_TIME(0.5f), false);
            break;

        case 7:
            func_800869E4(63, &g_SoundCmdIdx, &D_800DE124); // "Huh? Radio?"
            break;

        case 8:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 92, false);
            SysWork_StateStepIncrement();

        case 9:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(15.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(52.0f));
            if (g_Timer0 >= FP_TIME(52.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 10:
            g_Timer0 = MAX(g_Timer0, FP_TIME(53.0f));
            D_800E23A1 = 0x80;
            Savegame_EventFlagSet(EventFlag_45);

            func_80085E6C(FP_TIME(1.5f), false);
            break;

        case 11:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 53, false);
            SysWork_StateStepIncrement();

        case 12:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(15.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(75.0f));

            if (g_Timer0 >= FP_TIME(75.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 13:
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 89, false);

            D_800E23A1 = 0xE0;
            Savegame_EventFlagSet(EventFlag_46);
            g_Timer0 = FP_TIME(76.0f);

            SysWork_StateStepIncrement();

        case 14:
            var_a1   = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(115.0f));
            if (g_Timer0 >= FP_TIME(115.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 15:
            func_800CCB8C(&D_800CCA1C, &D_800CCA28, 0x2800, 0xCC, 0x999, 0x666, 0x199, 0);
            func_8005DC1C(Sfx_Unk1373, &D_800CCA34, FP_VOLUME(0.5f), 0);
            SysWork_StateStepIncrement();

        case 16:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(146.0f));
            if (g_Timer0 >= FP_TIME(146.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 17:
            func_800CCB8C(&D_800CCA40, &D_800CCA4C, 0x3000, 0x147, 0x666, 0x666, 0xED, 0);
            func_8005DC1C(Sfx_Unk1374, &D_800CCA58, FP_VOLUME(0.5f), 0);
            func_8005DC1C(Sfx_Unk1375, &D_800CCA58, FP_VOLUME(0.5f), 0);
            SysWork_StateStepIncrement();

        case 18:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(147.0f));
            if (g_Timer0 >= FP_TIME(147.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 19:
            func_800D3AC0(g_SysWork.npcs_1A0);
            SysWork_StateStepIncrement();

        case 20:
            var_a1     = g_Timer0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_TIME(18.0f), Q12_SHIFT);
            g_Timer0 = MIN(var_a1, FP_TIME(154.0f));
            if (g_Timer0 >= FP_TIME(154.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 21:
            Savegame_EventFlagSet(EventFlag_47);
            func_800D39F4(g_SysWork.npcs_1A0);
            func_8008616C(0, false, 2, FP_TIME(0.0f), false);

            g_Timer0 = NO_VALUE;

            vcReturnPreAutoCamWork(1);

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);
            Player_FallBackward();

            g_SysWork.flags_22A4 &= ~(1 << 5);
            g_SysWork.flags_22A4 &= ~(1 << 9);
            break;
    }

    if (g_Timer0 >= FP_TIME(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.player_4C.chara_0.position_18, &g_SysWork.player_4C.chara_0.rotation_24, &D_800CC908, g_Timer0, FS_BUFFER_11);

        if (g_SysWork.sysStateStep_C[0] >= 20)
        {
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, D_800CCA64, g_Timer0, FS_BUFFER_11);
            g_SysWork.npcs_1A0[0].position_18.vx += FP_MULTIPLY(Math_Sin(g_SysWork.npcs_1A0[0].rotation_24.vy), FP_METER(0.2f), Q12_SHIFT);
            g_SysWork.npcs_1A0[0].position_18.vz += FP_MULTIPLY(Math_Cos(g_SysWork.npcs_1A0[0].rotation_24.vy), FP_METER(0.2f), Q12_SHIFT);
        }

        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPositionTarget, &g_CutsceneCameraLookAtTarget, NULL, g_Timer0, FS_BUFFER_11));
        vcUserCamTarget(&g_CutsceneCameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_CutsceneCameraLookAtTarget, NULL, true);
    }
}

void Event_PocketRadioItemTake() // 0x800DC34C
{
    Event_ItemTake(InventoryItemId_PocketRadio, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S01_PickupPocketRadio, 64);
    g_SavegamePtr->flags_AC |= 1 << 0;
}

void Event_FlashlightItemTake() // 0x800DC394
{
    Event_ItemTake(InventoryItemId_Flashlight, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S01_PickupFlashlight, 61);
    Game_TurnFlashlightOff();
}

void Event_MapItemTake() // 0x800DC3C8
{
    static const RECT IMG_BUFFER_RECT = { 320, 256, 160, 240 };

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            Fs_QueueStartSeek(FILE_TIM_MP_0TOWN_TIM + D_800A99B5);
            SysWork_StateStepIncrement();

        case 1:
            func_8008616C(2, true, 0, FP_TIME(0.0f), false);
            break;

        case 2:
            DrawSync(0);
            StoreImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Fs_QueueStartReadTim(FILE_TIM_MP_0TOWN_TIM + D_800A99B5, FS_BUFFER_2, &g_MapImg);
            Screen_Init(SCREEN_WIDTH, 1);

            g_IntervalVBlanks = 1;

            GsSwapDispBuff();
            func_8008616C(0, false, 0, FP_TIME(0.0f), false);
            Fs_QueueWaitForEmpty();
            SysWork_StateStepIncrement();

        case 3:
            g_BackgroundColor = 88;

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            MapMsg_DisplayAndHandleSelection(true, 59, 6, 4, 0, false);
            break;

        case 5:
            LoadImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Screen_Init(SCREEN_WIDTH, 0);
            func_8008616C(0, false, 0, FP_TIME(0.0f), false);
            SysWork_StateStepReset();
            break;

        case 6:
            g_SavegamePtr->hasMapsFlags_164 |= 1 << 1;

            Fs_QueueStartRead(FILE_ANIM_CAFE2_DMS, FS_BUFFER_11);
            SysWork_StateStepIncrement();

        case 4:
        case 7:
            g_BackgroundColor = 88;

            Gfx_BackgroundSpriteDraw(&g_MapImg);
            func_8008616C(2, true, 0, FP_TIME(0.0f), false);
            break;

        case 8:
            LoadImage(&IMG_BUFFER_RECT, IMAGE_BUFFER);
            DrawSync(0);
            Screen_Init(SCREEN_WIDTH, 0);
            func_8008616C(0, false, 0, FP_TIME(0.0f), false);
            SysWork_StateStepIncrement();

        case 9:
            func_80088D0C();
            SysWork_StateStepIncrement();

        case 10:
            // Set cutscene character.
            Chara_Spawn(Chara_AirScreamer, 0, FP_METER(0.0f), FP_METER(0.0f), FP_METER(0.0f), 12);
            DmsHeader_FixOffsets(FS_BUFFER_11);
            Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, D_800CCA64, 0, FS_BUFFER_11);

            // Set camera.
            vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CutsceneCameraPositionTarget, &g_CutsceneCameraLookAtTarget, NULL, 0, FS_BUFFER_11));
            vcUserCamTarget(&g_CutsceneCameraPositionTarget, NULL, true);
            vcUserWatchTarget(&g_CutsceneCameraLookAtTarget, NULL, true);

            // Warp player.
            g_SysWork.player_4C.chara_0.position_18.vx = FP_METER(4.585938f);
            g_SysWork.player_4C.chara_0.position_18.vz = FP_METER(267.285156f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(90.0f);

            // Set flags.
            g_SysWork.field_2290             |= 1 << 0;
            g_SysWork.field_228C             |= 1 << 0;
            Savegame_EventFlagSet(EventFlag_38);

            SysWork_StateStepIncrement();

        case 11:
            func_8008616C(1, false, 0, FP_TIME(0.0f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_KitchenKnifeItemTake() // 0x800DC830
{
    Event_ItemTake(InventoryItemId_KitchenKnife, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M0S01_PickupKitchenKnife, 60);
}

/** Presumably a pickup function. Maybe debug or something unused and commented out. */
void Event_EmptyFunction() {}

void Event_HealthItemTake() // 0x800DC864
{
    s32 eventFlagIdx;
    u32 pickupType;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 13:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M0S01_HealthDrink0;
            break;

        case 14:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M0S01_HealthDrink1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void Event_AirScreamerDeath() // 0x800DC8C8
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8004690C(Sfx_Unk1321);
            func_8004690C(Sfx_Unk1322);

            Savegame_EventFlagClear(EventFlag_52);
            g_SoundCmdIdx = 0;
            SysWork_StateStepIncrement();

        case 1:
            func_800869E4(68, &g_SoundCmdIdx, &D_800DE128); // This_is_not_a_dream!
            break;

        default:
            sharedFunc_800D2244_0_s00(0);
            SysWork_StateSetNext(SysState_Gameplay);

            Savegame_EventFlagSet(EventFlag_51);
            break;
    }
}

extern s_800BCE18_2BEC_0 D_800E23B0[1];
extern s_800BCE18_2BEC_0 D_800E23D0[1];
extern s_800BCE18_2BEC_0 D_800E23F0[3];
extern s_800BCE18_2BEC_0 D_800E2450[2];

extern s_EventPosition g_DefaultEventPosition;
extern s_EventThing g_EventThing4A0;
extern s_EventThing g_EventThing4D0;
extern s_EventThing g_EventThing500;
extern s_EventThing g_EventThing530;

void func_800DC9C8() // 0x800DC9C8
{
    D_800E23A1 = 224;
    Math_Vector3f(&g_DefaultEventPosition.position_0, 0.0f, 0.0f, 280.0f, Q12_SHIFT);

    func_8003C8F8(&D_800E23B0[0], "IN_BLD1_");
    func_8003C8F8(&D_800E23D0[0], "IN1_HIDE");
    func_8003C8F8(&D_800E23F0[0], "BRK_BLD1");
    func_8003C8F8(&D_800E23F0[1], "BRK_GLS1");
    func_8003C8F8(&D_800E23F0[2], "BRK_GLS2");
    func_8003C8F8(&D_800E2450[0], "OUT1_HID");
    func_8003C8F8(&D_800E2450[1], "OUT_BLD_");

    EventPositionInit(&g_EventThing4A0.eventPosition_1C, 5.089844f, -1.009766f, 274.119873f, 0x16C0000, 0);
    func_8003C8F8(&g_EventThing4A0.field_0, "KNIFE_HI");

    EventPositionInit(&g_EventThing4D0.eventPosition_1C, 5.179932f, -1.0f, 267.279785f, 0x4EEFFDE, 0);
    func_8003C8F8(&g_EventThing4D0.field_0, "FLASH_HI");

    EventPositionInit(&g_EventThing500.eventPosition_1C, 5.23999f, -1.0f, 267.209961f, 0x2880000, 0);
    func_8003C8F8(&g_EventThing500.field_0, "MAP_HIDE");

    EventPositionInit(&g_EventThing530.eventPosition_1C, 2.309815f, -0.599854f, 273.949951f, 0x6880000, 0);
    func_8003C8F8(&g_EventThing530.field_0, "RADIO_HI");

    if (Savegame_EventFlagGet(EventFlag_40) && !Savegame_EventFlagGet(EventFlag_47))
    {
        g_SysWork.flags_22A4 |= (1 << 5) | (1 << 9);

        Chara_Load(0, Chara_AirScreamer, &g_SysWork.npcCoords_FC0[0], NO_VALUE, NULL, NULL);

        if (Savegame_EventFlagGet(EventFlag_38))
        {
            func_80088D0C();
            Chara_Spawn(Chara_AirScreamer, 0, FP_METER(1048566.0f), FP_METER(280.0f), FP_METER(0.0f), 12);
            func_800D3A3C(&g_SysWork.npcs_1A0[0]);

            Fs_QueueStartRead(FILE_ANIM_CAFE2_DMS, FS_BUFFER_11);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_11);
        }
    }

    if (Savegame_EventFlagGet(EventFlag_159) && !Savegame_EventFlagGet(EventFlag_134))
    {
        func_8003ED74(6, 3);
    }

    g_Timer0 = 0;
    D_800E2560 = 0;

    // There are 6 NPCs max. Maybe related?
    func_8003C8F8(&D_800E2570[0], D_800A99E4.field_8);
    func_8003C8F8(&D_800E2570[1], D_800A99E4.field_C);
    func_8003C8F8(&D_800E2570[2], D_800A99E4.field_10);
    func_8003C8F8(&D_800E2570[3], D_800A99E4.field_14);
    func_8003C8F8(&D_800E2570[4], D_800A99E4.field_18);
    func_8003C8F8(&D_800E2570[5], D_800A99E4.field_1C);
}


INCLUDE_ASM("asm/maps/map0_s01/nonmatchings/map0_s01_events", func_800DCCF4); // Set in map `header.func_40`.

void func_800DD2EC(s32 arg0) // 0x800DD2EC // called by func_800DCCF4 only
{
    static const SVECTOR3 DEFAULT_ROT = {};

    s32 i;

    if (arg0 == 0)
    {
        for (i = 0; i <= 0; i++)
        {
            func_8003C92C(&D_800E23D0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
        }

        for (i = 0; i <= 0; i++)
        {
            func_8003C92C(&D_800E23B0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
        }

        return;
    }

    if (arg0 == 1)
    {
        for (i = 0; i < 2; i++)
        {
            func_8003C92C(&D_800E2450[i], &g_DefaultEventPosition, &DEFAULT_ROT);
        }

        return;
    }

    for (i = 0; i <= 0; i++)
    {
        func_8003C92C(&D_800E23D0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
    }

    for (i = 0; i < 3; i++)
    {
        func_8003C92C(&D_800E23F0[i], &g_DefaultEventPosition, &DEFAULT_ROT);
    }
}
