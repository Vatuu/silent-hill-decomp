#include <libapi.h>

#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map2/map2_s01.h"
#include "maps/characters/dahlia.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800CDDA0

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800CDDB4

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800CDDF8

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800CDE10

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800CDE1C

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800CDE30

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800CDE44

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800CDE58

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800CDEF4

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800CE558

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800CE56C

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800CE580

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800CE67C

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800CE730

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800CE750

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800CE7B0

#include "maps/shared/Map_RoomIdxGet.h" // 0x800CE7C0

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800CE858

#include "maps/shared/Map_RoomBgmInit_0_s02_CondTrue.h" // 0x800CE88C

#include "maps/shared/Map_RoomBgmInit_0_s02_CondFalse.h" // 0x800CE908

void Gfx_LoadingScreen_StageString(void) {} // 0x800CEB94

void func_800CEB9C(void) // 0x800CEB9C
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Map_MessageWithSfx(MapMsgIdx_DoorJammed, Sfx_DoorJammed, &sfxPos);
}

void func_800CEC30(void) // 0x800CEC30
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    if (g_MapEventData->pointOfInterestIdx_5 == 2)
    {
        if (Savegame_EventFlagGet(EventFlag_180))
        {
            Map_MessageWithSfx(38, Sfx_Unk1486, &sfxPos);

            if (g_SysWork.sysState_8 == SysState_Gameplay)
            {
                Savegame_EventFlagSet(EventFlag_180);
            }
        }
        else
        {
            Map_MessageWithSfx(MapMsgIdx_DoorLocked, Sfx_Unk1486, &sfxPos);
        }
    }
    else
    {
        Map_MessageWithSfx(MapMsgIdx_DoorLocked, Sfx_DoorLocked, &sfxPos);
    }
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J1(1.9)\tWere_you_ringing_that_bell? ",
    "~J1(5.3)\tI've_been_expecting_you. ~N\n\t\t\tIt_was_foretold_by_Gyromancy. ",
    "~J1(1.8)\tWhat_are_you_talking_about? ~E ",
    "~J1(2.2)\tI_knew_you'd_come. ",
    "~J1(2.4)\tYou_want_the_girl,_right? ",
    "~J1(0.9)\tThe_girl? ",
    "~J1(1.7)\tYou're_talking_about_Cheryl? ",
    "~J1(2.8)\tI_see_everything. ~E ",
    "~J0(2.1)\tYou_know_something!? ~N\n\t\t\tTell_me! ~E ",
    "~J0(1.1)\tStay_back! ~E ",
    "~J1(4.0)\tNothing_is_to_be_gained_from ~N\n\t\t\tfloundering_about_at_random.  ",
    "~J1(2.3)\tYou_must_follow_the_path. ",
    "~J1(4.0)\tThe_path_of_the_hermit, ~N\n\t\t\tconcealed_by_Flauros... ",
    "~J1(3.6)\tWhat? ~N\n\t\t\tWhat_are_you_talking_about? ~E ",
    "~J0(4.0)\tHere,_the_Flauros, ~N\n\t\t\ta_cage_of_peace. ",
    "~J0(3.3)\tIt_can_break_through ~N\n\t\t\tthe_walls_of_darkness, ",
    "~J0(3.8)\tand_counteract_the_wrath_of ~N\n\t\t\tthe_underworld. ",
    "~J0(3.0)\tThese_will_help_you. ~E ",
    "~J0(4.2)\tMake_haste_to_the_hospital ~N\n\t\t\tbefore_it's_too_late. ~E ",
    "~J0(2.4)\tWait! ~N\n\t\t\tDon't_go_yet! ~E ",
    "\tThere_is_a_ ~C2 [Flauros] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Drawbridge_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tBible. ~E ",
    "\tIt_won't_open. ",
    "\tIt_must_be_locked ~N\n\tfrom_the_other_side. ~E ",
    "\tThere's_a_collection_box. ~N\n\tNothing_inside. ~E ",
    "\tThere's_a_newspaper. ~N\n\tNothing_special. ~E ",
    "\tThere's_a_picture_on_the_wall. ~N\n\tNothing_special. ~E ",
    "\tThere's_a_candle_stand. ~N\n\tNothing_special. ~E "
};

void func_800CED44(void) // 0x800CED44
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 25:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M2S01_HealthDrink;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800CED88(void) // 0x800CED88
{
    typedef enum _EventState
    {
        EventState_Skip = 31
    } e_EventState;

    s32             step;
    s_SubCharacter* dahlia;

    #define dahliaChara (&g_SysWork.npcs_1A0[0])
    #define playerChara (&g_SysWork.playerWork_4C.player_0)

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < EventState_Skip)
    {
        SysWork_StateStepSet(0, EventState_Skip);
    }

    step = g_SysWork.sysStateStep_C[0];
    switch (step)
    {
        case 0:
            Player_ControlFreeze();
            Fs_QueueStartRead(FILE_ANIM_CHRC_DMS, FS_BUFFER_15);
            Fs_QueueWaitForEmpty();
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_15);
            Chara_Load(0, Chara_Dahlia, &g_SysWork.npcCoords_FC0[0], CHARA_FORCE_FREE_ALL, NULL, NULL);
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Dahlia, 0, Q12(20.0f), Q12(23.5f), 0, 3);
            sharedFunc_800D88AC_0_s00(dahliaChara);

            g_Timer0 = Q12(0.0f);
            g_SysWork.field_30 = 20;
            g_SysWork.flags_22A4 |= SysFlag2_3;

            func_80085EB8(0, playerChara, 51, false);
            func_80085EB8(0, dahliaChara, 0, false);
            func_8003D03C();

            Savegame_EventFlagSet(EventFlag_182);
            g_MapMsgSoundIdx = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 2:
            Map_MessageWithAudio(15, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 3:
            Map_MessageWithAudio(18, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 4:
            Map_MessageWithAudio(23, &g_MapMsgSoundIdx, g_MapMsgSounds);
            SysWork_StateStepIncrementDelayed(Q12(1.2f), false);
            break;

        case 5:
            func_80085EB8(0, playerChara, 113, false);
            SysWork_StateStepIncrement(0);

        case 6:
            Map_MessageWithAudio(23, &g_MapMsgSoundIdx, g_MapMsgSounds);

            if (g_Timer0 < Q12(1.0f))
            {
                g_Timer0 = Q12(1.0f);
                break;
            }

            g_Timer0 += Q12_MULT_PRECISE(g_DeltaTime, Q12(5.0f));
            if (g_Timer0 > Q12(23.0f))
            {
                g_Timer0 = Q12(23.0f);
            }
            break;

        case 7:
            Map_MessageWithAudio(0x18, &g_MapMsgSoundIdx, g_MapMsgSounds);

            if (g_Timer0 < Q12(1.0f))
            {
                g_Timer0 = Q12(1.0f);
                break;
            }

            g_Timer0 += Q12_MULT_PRECISE(g_DeltaTime, Q12(5.0f));
            if (g_Timer0 > Q12(23.0f))
            {
                g_Timer0 = Q12(23.0f);
            }
            break;

        case 8:
            func_80085EB8(4, playerChara, 0, false);
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 9:
            Map_MessageWithAudio(25, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 10:
            func_80085EB8(0, dahliaChara, 9, false);
            SysWork_StateStepIncrement(0);

        case 11:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 12:
            func_80085EB8(1, dahliaChara, 0, false);
            Map_MessageWithAudio(29, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 13:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            Map_MessageWithAudio(29, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;

        case 14:
            func_80085EB8(0, dahliaChara, 10, false);
            SysWork_StateStepIncrement(0);

        case 15:
            func_80085EB8(1, dahliaChara, 0, false);
            Map_MessageWithAudio(29, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;
        case 16:
            SysWork_StateStepIncrement(0);

        case 17:
            Map_MessageWithAudio(29, &g_MapMsgSoundIdx, g_MapMsgSounds);
            break;
        case 18:
            func_80085EB8(0, dahliaChara, 8, false);
            SysWork_StateStepIncrement(0);

        case 19:
            Map_MessageWithAudio(33, &g_MapMsgSoundIdx, g_MapMsgSounds);

            if (g_Timer0 >= Q12(142.0f))
            {
                g_Timer0 += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));

                if (g_Timer0 > Q12(165.0f))
                {
                    g_Timer0 = Q12(165.0f);
                }
                break;
            }

            g_Timer0 = Q12(142.0f);
            break;

        case 20:
            SysWork_StateStepIncrementDelayed(Q12(0.3f), false);

            if (g_Timer0 < Q12(142.0f))
            {
                g_Timer0 = Q12(142.0f);
                break;
            }

            g_Timer0 += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
            if (g_Timer0 > Q12(165.0f))
            {
                g_Timer0 = Q12(165.0f);
            }
            break;

        case 21:
            func_80085EB8(0, dahliaChara, 1, false);
            SysWork_StateStepIncrement(0);

        case 22:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);

            if (g_Timer0 >= Q12(166.0f))
            {
                g_Timer0 += Q12_MULT_PRECISE(g_DeltaTime, Q12(15.0f));

                if (g_Timer0 > Q12(180.0f))
                {
                    g_Timer0 = Q12(180.0f);
                }
                break;
            }

            g_Timer0 = Q12(166.0f);
            break;

        case 23:
            func_80085EB8(0, playerChara, 111, false);
            SysWork_StateStepIncrement(0);

        case 24:
            Map_MessageWithAudio(34, &g_MapMsgSoundIdx, g_MapMsgSounds);

            if (g_Timer0 < Q12(166.0f))
            {
                g_Timer0 = Q12(166.0f);
                break;
            }

            g_Timer0 += Q12_MULT_PRECISE(g_DeltaTime, Q12(15.0f));
            if (g_Timer0 > Q12(253.0f))
            {
                g_Timer0 = Q12(253.0f);
            }
            break;

        case 25:
            if (g_Timer0 < Q12(166.0f))
            {
                g_Timer0 = Q12(166.0f);
            }
            else
            {
                g_Timer0 += Q12_MULT_PRECISE(g_DeltaTime, Q12(15.0f));
                if (g_Timer0 > Q12(253.0f))
                {
                    g_Timer0 = Q12(253.0f);
                    SysWork_StateStepIncrement(0);
                }
            }
            break;

        case 26:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 27:
            func_8005DC1C(Sfx_Unk1323, &QVECTOR3(12.0f, -1.2f, 24.0f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case 28:
            SysWork_StateStepIncrementDelayed(Q12(1.2f), false);
            break;

        case 29:
            func_8005DC1C(Sfx_Unk1324, &QVECTOR3(12.0f, -1.2f, 24.0f), Q8_CLAMPED(0.5f), 0);
            func_80088F94(dahliaChara, 0, 0);
            SysWork_StateStepIncrement(0);

        case 30:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case EventState_Skip:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);

            if (g_SysWork.sysStateStep_C[0] != EventState_Skip)
            {
                g_Timer0 = Q12(253.0f);
            }
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            Savegame_EventFlagSet(EventFlag_179);
            Savegame_EventFlagSet(EventFlag_176);
            Savegame_EventFlagSet(EventFlag_MapMark_FogCentralTown_HospitalCircle);
            Savegame_EventFlagSet(EventFlag_MapMark_AltCentralTown_HospitalCircle);

            func_80088F94(dahliaChara, 0, 0);

            g_Timer0 = NO_VALUE;

            SD_Call(19);
            func_8003D01C();
            break;
    }

    if (step < 15)
    {
        if (step >= 10)
        {
            if (g_Timer0 < Q12(24.0f))
            {
                g_Timer0 = Q12(24.0f);
            }
            else
            {
                g_Timer0 += Q12_MULT_PRECISE(g_DeltaTime, Q12(10.0f));
                if (g_Timer0 > Q12(141.0f))
                {
                    g_Timer0 = Q12(141.0f);
                }
            }

            if (step > 13)
            {
                dahlia = dahliaChara;
                if ((dahlia->model_0.anim_4.time_4 - Q12(Anim_StartKeyframeIdxGet(dahlia))) <= Q12(30.0f) &&
                    (dahlia->model_0.anim_4.time_4 - Q12(Anim_StartKeyframeIdxGet(dahlia))) >= Q12(21.0f))
                {
                    Savegame_EventFlagSet(EventFlag_176);
                }
            }
        }
    }

    if (g_Timer0 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&playerChara->position_18, (SVECTOR3*)&playerChara->rotation_24, "HERO", g_Timer0, (s_DmsHeader*)FS_BUFFER_15);
        Dms_CharacterGetPosRot(&dahliaChara->position_18, (SVECTOR3*)&dahliaChara->rotation_24, "DAHLIA", g_Timer0, (s_DmsHeader*)FS_BUFFER_15);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&g_CameraPositionTarget, &g_CameraLookAtTarget, NULL, g_Timer0, (s_DmsHeader*)FS_BUFFER_15));
        vcUserCamTarget(&g_CameraPositionTarget, NULL, true);
        vcUserWatchTarget(&g_CameraLookAtTarget, NULL, true);
    }
}

void func_800CF798(void) // 0x800CF798
{
    Event_ItemTake(InventoryItemId_Flauros, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S01_PickupFlauros, 35);
}

void func_800CF7C4(void) // 0x800CF7C4
{
    Event_ItemTake(InventoryItemId_DrawbridgeKey, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M2S01_PickupDrawbridgeKey, 36);
}

extern u8 D_800D177C;
extern s_WorldObjectModel g_CommonWorldObjects[6];
extern s_WorldObjectDesc g_WorldObject_SavePad;
extern s_WorldObjectDesc g_WorldObject_Key;
extern s_WorldObjectDesc g_WorldObject_Item;
extern s_WorldObjectPose g_CommonWorldObjectPoses[1];

void Map_WorldObjectsInit(void)
{
    Gfx_MapInitMapEffectsUpdate(1, 1);

    WorldObjectNoRotInit(&g_WorldObject_Item, "ITEM_HID", 19.8289f, -1.3633f, 24.0735f);

    WorldObjectInit(&g_WorldObject_Key, "KEY_HIDE", 20.073f, -0.858f, 24.1469f, 0.0f, 23.0f, 0.0f);

    WorldObjectInit(&g_WorldObject_SavePad, D_800A99E4.savePadName_4, 18.3345f, -0.9102f, 14.1985f, 0.0f, 10.5f, 0.0f);

    D_800D177C = 0;

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800CF938
{
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
            if (Savegame_EventFlagGet(EventFlag_176) && !Savegame_EventFlagGet(EventFlag_M2S01_PickupFlauros))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Item.object_0, &g_WorldObject_Item.position_1C, &(SVECTOR3){ 0, 0, 0 });
            }

            if (!Savegame_EventFlagGet(EventFlag_M2S01_PickupDrawbridgeKey))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Key.object_0, &g_WorldObject_Key.position_1C, &g_WorldObject_Key.rotation_28);
                Savegame_EventFlagClear(EventFlag_MapMark_OldTown_BalkanChurchCheck);
            }
            else
            {
                Savegame_EventFlagSet(EventFlag_MapMark_OldTown_BalkanChurchCheck);
            }

            WorldGfx_ObjectAdd(&g_WorldObject_SavePad.object_0, &g_WorldObject_SavePad.position_1C, &g_WorldObject_SavePad.rotation_28);
    }

    if (D_800D177C == 0)
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S01_PickupDrawbridgeKey))
        {
            if (PLAYER_NEAR_POS(vx, 20.0f, 0.7f) && PLAYER_NEAR_POS(vz, 23.9f, 0.5f))
            {
                Camera_PositionSet(NULL, Q12(19.57f), Q12(-2.91f), Q12(23.91f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
                Camera_LookAtSet(NULL, Q12(20.69f), Q12(0.92f), Q12(24.22f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
                D_800D177C = 1;
            }
        }
    }
    else
    {
        // NOTE: This macro uses `>` comparison, but this part of the code apparently uses `>=`
        // which would require a separate macro or slightly larger number to compensate.
        if (!(PLAYER_NEAR_POS(vx, 20.0f, 1.2004f) && PLAYER_NEAR_POS(vz, 23.9f, 1.0004f)))
        {
            vcReturnPreAutoCamWork(true);
            D_800D177C = 0;
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M2S01_HealthDrink))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }
}
