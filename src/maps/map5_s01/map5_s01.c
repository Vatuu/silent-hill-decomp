#include "bodyprog/bodyprog.h"
#include "bodyprog/dms.h"
#include "bodyprog/events/bodyprog_data_800A99B4.h"
#include "bodyprog/events/radio.h"
#include "bodyprog/gfx/map_effects.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/map5/map5_s01.h"
#include "maps/particle.h"
#include "maps/characters/air_screamer.h"
#include "maps/characters/player.h"
#include "maps/characters/romper.h"

// TODO: Move this line into separate `Chara_Romper` split.
#include "../src/maps/characters/romper.c" // 0x800E786C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800EB460

#include "maps/shared/Map_RoomIdxGet.h" // 0x800EB470

void func_800EB6B0(void) // 0x800EB6B0
{
    s32    temp_v0;
    q19_12 posX;
    q19_12 posZ;
    q19_12 newPosComp;
    s32    var_v1;
    s32    temp_s1;

    posX  = g_SysWork.playerWork.player.position.vx;
    posZ  = g_SysWork.playerWork.player.position.vz;
    temp_s1 = D_800EFC80[g_SavegamePtr->mapRoomIdx_A5];

    if (g_SavegamePtr->mapRoomIdx_A5 == 10)
    {
        posX += Q12(150.0f);
        posZ  = Q12(-25.0f) - posZ;
        if (posX < posZ)
        {
            newPosComp = posX;
        }
        else
        {
            newPosComp = posZ;
        }

        newPosComp /= 2;
    }
    else
    {
        if (posZ > Q12(-120.0f))
        {
            posX = posX - Q12(16.0f);
            posZ = Q12(-48.0f) - posZ;
            if (posX < posZ)
            {
                newPosComp = posX;
            }
            else
            {
                newPosComp = posZ;
            }
        }
        else
        {
            if (posX > Q12(0.0f))
            {
                posX = posX - Q12(16.0f);
            }
            else
            {
                posX = Q12(-52.0f) - posX;
            }

            posZ = Q12(-144.0f) - posZ;

            if (posZ < posX)
            {
                newPosComp = posX;
            }
            else
            {
                newPosComp = posZ;
            }
        }
    }

    D_800EFC7C += g_DeltaTime;
    if (newPosComp < Q12(0.0f))
    {
        newPosComp = Q12(0.0f);
    }
    else if (newPosComp >= Q12(32.0f))
    {
        newPosComp = Q12(32.0f) - 1;
    }

    temp_v0 = (Math_Sin(D_800EFC7C / 12) + Q12(2.0f)) / 2;
    var_v1  = Q12_MULT_PRECISE(newPosComp, temp_v0);

    D_800EFC74.limits[4] = var_v1 / Q12(0.5f);
    Bgm_Update(temp_s1, Q12(0.2f), &D_800EFC74);
}

void GameBoot_LoadScreen_StageString(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800EB87C

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800EB910

const char* MAP_MESSAGES[] = {
    #include "maps/shared/map_msg_common.h"
    "~H\tThere_is_a_ ~C5 Resort_area_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tNothing_unusual. ~E ",
    "\tUsed_the_ ~C2 Kaufmann_key ~C7 . ~E ",
    "~J0(1.0)\tWhat? ~E ",
    "~J0(2.5)\tThat_light!? ~E "
};

void MapEvent_CommonItemTake(void) // 0x800EB9A4
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx)
    {
        case 40:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M5S01_RifleShells0;
            break;

        case 41:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M5S01_HandgunBullets;
            break;

        case 42:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M5S01_FirstAidKit;
            break;

        case 43:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S01_HealthDrink;
            break;

        case 44:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M5S01_RifleShells1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800EBA40(void) // 0x800EBA40
{
    s32 i;
    s32 j;

    Game_RadioSoundStop();

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            D_800F0358 = 0;
            D_800F0354 = 0;

            for (i = 0; i < ARRAY_SIZE(D_800F0350); i++)
            {
                D_800F0350[i] = 10;
            }

            SysWork_StateStepIncrement(0);

        case 1:
            func_800862F8(7, FILE_TIM_DORPANEL_TIM, false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            Screen_BackgroundImgDraw(&g_ItemInspectionImg);
            break;

        case 4:
            Screen_BackgroundImgDraw(&g_ItemInspectionImg);

            D_800F0354 += (g_Controller0->sticks_24.sticks_0.leftX * 16384) / 75;
            D_800F0354  = CLAMP_RANGE(D_800F0354, Q12(-160.0f), Q12(160.0f));

            D_800F0358 += (g_Controller0->sticks_24.sticks_0.leftY * 16384) / 75;
            D_800F0358  = CLAMP_RANGE(D_800F0358, Q12(-120.0f), Q12(120.0f));

            Game_TimerUpdate();
            Gfx_CursorDraw((s16)(FP_FROM(D_800F0354, Q12_SHIFT) + 8), FP_FROM(D_800F0358, Q12_SHIFT) + 8, 8, 8, 0, 64, 32, 32, 128, 192, 0, 12);

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.cancel_2)
            {
                SysWork_StateStepSet(0, 7);
                break;
            }

            if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.enter_0)
            {
                for (i = 0; i < ARRAY_SIZE(D_800F0158); i++)
                {
                    if ((D_800F0158[i].field_0 - 160) > FP_FROM(D_800F0354, Q12_SHIFT) ||
                        (D_800F0158[i].field_0 - 114) < FP_FROM(D_800F0354, Q12_SHIFT))
                    {
                        continue;
                    }

                    if ((D_800F0158[i].field_1 - 120) > FP_FROM(D_800F0358, Q12_SHIFT) ||
                        (D_800F0158[i].field_1 - 74) < FP_FROM(D_800F0358, Q12_SHIFT))
                    {
                        continue;
                    }

                    Sd_PlaySfx(Sfx_Unk1586, 0, Q8(0.5f));

                    if (i < 11)
                    {
                        for (j = 0; j < (ARRAY_SIZE(D_800F0350) - 1); j++)
                        {
                            D_800F0350[j] = D_800F0350[j + 1];
                        }

                        D_800F0350[3] = i;
                        break;
                    }

                    for (j = 0; j < ARRAY_SIZE(D_800F0350); j++)
                    {
                        if (D_800F0170[j] != D_800F0350[j])
                        {
                            break;
                        }
                    }

                    if (j == 4)
                    {
                        Savegame_EventFlagSet(EventFlag_387);
                        SysWork_StateStepIncrement(0);
                    }
                    else
                    {
                        for (j = 0; j < ARRAY_SIZE(D_800F0350); j++)
                        {
                            D_800F0350[j] = 10;
                        }
                    }
                    break;
                }
            }
            break;

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            Screen_BackgroundImgDraw(&g_ItemInspectionImg);
            break;

        case 6:
            Sd_PlaySfx(Sfx_Unk1587, 0, Q8(0.5f));
            SysWork_StateStepIncrement(0);

        case 7:
            Screen_BackgroundImgDraw(&g_ItemInspectionImg);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            func_80037154();
            break;
    }
}

void MapEvent_MapTake(void) // 0x800EBF48
{
    Event_MapTake(4, EventFlag_M5S01_PickupMap, 15);
}

void func_800EBF70(void) // 0x800EBF70
{
    VECTOR3 camPos;    // Q19.12
    VECTOR3 canLookAt; // Q19.12
    s16     temp_v0;
    s16     temp;

    temp = 0x1D9;

    if (g_SysWork.sysStateSteps[0] > 2)
    {
        Game_RadioSoundStop();
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800CD818();

            g_SysWork.field_30 = 20;

            SysWork_StateStepIncrementAfterFade(0, true, 2, 0, false);

            g_SysWork.playerWork.player.position.vx = Q12(52.0f);
            g_SysWork.playerWork.player.position.vz = Q12(-57.8f);
            g_SysWork.playerWork.player.rotation.vy = Q12_ANGLE(107.6f);

            camPos.vx = Q12(49.8f);
            camPos.vy = Q12(-1.5f);
            camPos.vz = Q12(-60.0f);

            canLookAt.vx = Q12(52.5f);
            canLookAt.vy = Q12(-1.3f);
            canLookAt.vz = Q12(-57.9f);

            Camera_PositionSet(&camPos, 0, 0, 0, 0, 0, 0, 0, true);
            Camera_LookAtSet(&canLookAt, 0, 0, 0, 0, 0, 0, 0, true);
            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 3:
            if (Fs_QueueDoThingWhenEmpty())
            {
                g_SysWork.bgmStatusFlags |= BgmStatusFlag_Pause;

                func_800CD860();
                SysWork_StateStepIncrement(0);
            }

        case 4:
            g_SysWork.bgmStatusFlags |= BgmStatusFlag_Pause;
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 5:
            Game_TimerUpdate();
            g_SysWork.bgmStatusFlags |= BgmStatusFlag_Pause;

            temp_v0 = func_800CD20C();
            if (!(g_Controller0->btnsClicked_10 & g_GameWorkPtr->config.controllerConfig.cancel_2))
            {
                if (temp != temp_v0)
                {
                    break;
                }

                Savegame_EventFlagSet(EventFlag_371);
                Sd_PlaySfx(Sfx_Unk1588, 0, Q8(0.5f));
            }

            SysWork_StateStepIncrement(0);
            break;

        case 6:
            g_SysWork.bgmStatusFlags |= BgmStatusFlag_Pause;

            func_800CD20C();
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);

        default:
            // Return to gameplay.
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            vcReturnPreAutoCamWork(true);
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            func_80037154();
            break;
    }
}

void func_800EC2D8(void) // 0x800EC2D8
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx].positionZ_8 };

    Player_ItemRemove(InvItemId_KaufmannKey, 1);
    Map_MessageWithSfx(17, Sfx_UseKey, &sfxPos); // "Used the Kaufmann key."
    Savegame_EventFlagSet(EventFlag_M5S01_KaufmannKeyUsed);
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800EC394

void func_800EC42C(void) // 0x800EC42C
{
    s32    mulZ;
    s32    mulX;
    s32    pitch;
    s32    tmp0;
    s32    tmp1;
    q19_12 sin0;
    q19_12 sin1;

    tmp0 = D_800F0360;
    sin0 = Math_Sin(tmp0 >> 2);
    sin1 = Math_Sin(tmp0 >> 3);
    tmp1 = ((sin0 * 2) + sin1) + Math_Sin(Math_Cos(tmp0 >> 4));
    pitch = tmp1 >> 8;
    D_800F0360 += g_DeltaTime;

    if (g_SysWork.sysStateSteps[0] >= 10)
    {
        D_800F035E -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.5f));
        if (D_800F035E < 0)
        {
            D_800F035E = 0;
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800F035E >> 4), pitch);
    }
    else if (g_SysWork.sysStateSteps[0] > 0)
    {
        D_800F035E += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
        if (D_800F035E > Q12(0.9961f))
        {
            D_800F035E = Q12(0.9961f);
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800F035E >> 4), pitch);
    }

    switch (g_SysWork.sysStateSteps[0])
    {
        case 0:
            Player_ControlFreeze();
            Fs_QueueStartReadTim(FILE_TIM_ENBAN_TIM, FS_BUFFER_1, &D_800F0178);
            Fs_QueueStartRead(FILE_ANIM_UFO3_DMS, FS_BUFFER_13);

            g_Cutscene_Timer = NO_VALUE;

            ScreenFade_ResetTimestep();
            SD_Call(Sfx_Unk1467);
            Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, Q8_CLAMPED(1.0f), 0);

            D_800F035E = 0;
            D_800F0360 = 0;
            D_800F035D = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            if (Fs_QueueDoThingWhenEmpty() != false)
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 3:
            g_Cutscene_Timer = 0;

            SysWork_StateStepIncrementAfterFade(0, true, 3, 0, false);
            Dms_HeaderFixOffsets((s_DmsHeader* )FS_BUFFER_13);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Game_TurnFlashlightOn();

            D_800F035C = 0;

            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 5:
            Map_MessageWithAudio(18, &D_800F035C, &D_800F0174);
            break;

        case 6:
            SysWork_StateStepIncrementAfterTime(&g_Cutscene_Timer, Q12(40.0f), Q12(0.0f), Q12(30.0f), true, true);
    block_18:
            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(0.5f), Q12(0.05f), 0);
            break;

        case 7:
            MapMsg_DisplayAndHandleSelection(false, 19, 0, 0, 0, false);
            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(0.5f), Q12(0.05f), 0);
            break;

        case 8:
            func_80080B58(&g_SysWork.playerBoneCoords[HarryBone_Head], &(SVECTOR3){ 0, 0, 0 }, &QVECTOR3(-196.53f, -14.25f, -9.73f));
            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(1.0f), Q12(0.1f), 1);
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 9:
            g_SysWork.field_28 += g_DeltaTime;

            switch (g_SysWork.field_28 / Q12(0.1f))
            {
                case 0:
                case 1:
                case 2:
                case 3:
                    mulZ = Q12(0.0f);
                    mulX = Q12(0.0f);
                    break;

                case 4:
                case 5:
                case 6:
                case 11:
                case 12:
                case 13:
                case 18:
                case 19:
                case 20:
                    mulX = Q12(-0.9f);
                    mulZ = Q12(1.0f);
                    break;

                case 7:
                case 8:
                case 9:
                case 10:
                case 14:
                case 15:
                case 16:
                case 17:
                case 21:
                case 22:
                case 23:
                case 24:
                    mulX = Q12(1.2f);
                    mulZ = Q12(1.0f);
                    break;

                case 25:
                    if (D_800F035D == 0)
                    {
                        D_800F0180.vy = Q12(-13.0f);
                        D_800F0180.vz = Q12(2.5f);
                        D_800F035D++;
                    }

                case 26:
                case 27:
                case 31:
                case 32:
                case 33:
                case 37:
                case 38:
                case 39:
                case 43:
                case 44:
                case 45:
                    mulX = Q12(-1.2f);
                    mulZ = Q12(-1.2f);
                    break;

                case 28:
                case 29:
                case 30:
                case 34:
                case 35:
                case 36:
                case 40:
                case 41:
                case 42:
                    mulX = Q12(1.2f);
                    mulZ = Q12(-1.2f);
                    break;

                case 46:
                    if (D_800F035D == 1)
                    {
                        D_800F0180.vy = Q12(-15.75f);
                        D_800F0180.vz = Q12(-12.25f);
                        D_800F035D++;
                    }

                case 59:
                    mulX = Q12(0.0f);
                    mulZ = Q12(-1.6f);
                    break;

                case 47:
                case 48:
                case 49:
                case 56:
                case 57:
                case 58:
                    mulX = Q12(0.6f);
                    mulZ = Q12(-1.6f);
                    break;

                case 50:
                case 51:
                case 52:
                case 53:
                case 54:
                case 55:
                    mulX = Q12(-0.6f);
                    mulZ = Q12(-1.6f);
                    break;

                default:
                    mulZ = Q12(0.0f);
                    mulX = Q12(0.0f);
                    SysWork_StateStepIncrement(0);
                    break;
            }

            D_800F0180.vy += Q12_MULT_PRECISE(g_DeltaTime, mulX * 4);
            D_800F0180.vz += Q12_MULT_PRECISE(g_DeltaTime, mulZ * 4);

            sharedFunc_800CE5D4_1_s03(&D_800F0180, Q12(0.5f), Q12(0.05f), 0);
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        default:
            // Return to gameplay.
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);

            vcReturnPreAutoCamWork(true);
            Savegame_EventFlagSet(EventFlag_458);
            func_80086470(3, InvItemId_ChannelingStone, 1, false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            g_Cutscene_Timer = NO_VALUE;

            Sd_SfxStop(Sfx_Unk1467);
            break;
    }

    if (g_Cutscene_Timer >= Q12(0.0f))
    {
        Dms_CharacterTransformGet(&g_SysWork.playerWork.player.position, &g_SysWork.playerWork.player.rotation, "HERO", g_Cutscene_Timer, (s_DmsHeader*)FS_BUFFER_13);

        g_SysWork.playerWork.player.position.vx -= Q12(20.0f);

        vcChangeProjectionValue(Dms_CameraTargetGet(&g_Cutscene_CameraPositionTarget, &g_Cutscene_CameraLookAtTarget, NULL, g_Cutscene_Timer, (s_DmsHeader*)FS_BUFFER_13));

        g_Cutscene_CameraPositionTarget.vx -= Q12(20.0f);
        g_Cutscene_CameraLookAtTarget.vx -= Q12(20.0f);

        vcUserCamTarget(&g_Cutscene_CameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_Cutscene_CameraLookAtTarget, NULL, true);
    }
}

void Map_WorldObjectsInit(void) // 0x800ECB58
{
    WorldObjectNoRotInit(&g_WorldObject0, "RSRMAP_H", -46.5f, 0.0f, 2.5f);

    WorldObjectInit(&g_WorldObject1, "FOOK_HID", 52.15f, -1.359f, -57.925f, 0.0f, 0.0f, 5.8f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        g_SysWork.npcFlagsId = 3;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        g_SysWork.npcFlagsId = 4;
    }
    else
    {
        g_SysWork.npcFlagsId = 5;
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4[2]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4[3]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4[4]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4[5]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4[6]);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4[7]);
}

void Map_WorldObjectsUpdate(void) // 0x800ECC8C
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if ((PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1)) ||
        (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0)))
    {
            if (!Savegame_EventFlagGet(EventFlag_M5S01_PickupMap))
            {
                WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &(SVECTOR3){ 0, 0, 0 });
            }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
            if (!Savegame_EventFlagGet(EventFlag_371))
            {
                WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &g_WorldObject1.rotation_28);
            }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_RifleShells0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[0].position, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_HandgunBullets))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1].position, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_FirstAidKit))
        {
            WorldGfx_ObjectAdd(g_CommonWorldObjects, &g_CommonWorldObjectPoses[2].position, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -5, -1, -5))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_HealthDrink))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[3].position, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -5, -1, -5))
    {
        if (!Savegame_EventFlagGet(EventFlag_M5S01_RifleShells1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[4], &g_CommonWorldObjectPoses[4].position, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }
}
