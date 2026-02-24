#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map3/map3_s04.h"
#include "maps/characters/lisa.h"
#include "bodyprog/sound_system.h"

#include "maps/shared/sharedFunc_800D88AC_0_s00.h" // 0x800D1374

#include "maps/shared/sharedFunc_800D88C0_0_s00.h" // 0x800D1388

#include "maps/shared/sharedFunc_800D8904_0_s00.h" // 0x800D13CC

#include "maps/shared/sharedFunc_800D891C_0_s00.h" // 0x800D13E4

#include "maps/shared/sharedFunc_800D8928_0_s00.h" // 0x800D13F0

#include "maps/shared/sharedFunc_800D893C_0_s00.h" // 0x800D1404

#include "maps/shared/sharedFunc_800D8950_0_s00.h" // 0x800D1418

#include "maps/shared/sharedFunc_800D8964_0_s00.h" // 0x800D142C

#include "maps/shared/sharedFunc_800D8A00_0_s00.h" // 0x800D14C8

#include "maps/shared/sharedFunc_800D9064_0_s00.h" // 0x800D1B2C

#include "maps/shared/sharedFunc_800D9078_0_s00.h" // 0x800D1B40

#include "maps/shared/sharedFunc_800D908C_0_s00.h" // 0x800D1B54

#include "maps/shared/sharedFunc_800D9188_0_s00.h" // 0x800D1C50

#include "maps/shared/Anim_StartKeyframeIdxGet.h" // 0x800D1CFC

#include "maps/shared/sharedFunc_800D923C_0_s00.h" // 0x800D1D1C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D1D7C

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D1D8C

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800D1E24

#include "maps/shared/Map_RoomBgmInit_3_s02_CondTrue.h" // 0x800D1E58

#include "maps/shared/Map_RoomBgmInit_3_s02_CondFalse.h" // 0x800D1E98

void func_800D2128(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D2130

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "~J1(3.6)\tFinally. ~N\n\t\t\tSomeone_else_who's_OK. ",
    "~J1(1.0)\tWho_are_you? ",
    "~J1(3.1)\tMy_name's_Lisa_Garland. ~N\n\t\t\tWhat's_yours? ",
    "~J1(1.2)\tHarry_Mason. ~E ",
    "~J0(4.7)\tHarry,_tell_me ~N\n\t\t\twhat's_happening_here? ~N\n\t\t\tWhere_is_everybody? ",
    "~J0(2.7)\tI_must_have_gotten_knocked_out. ",
    "~J0(3.2)\tWhen_I_came_to, ~N\n\t\t\teveryone_was_gone. ",
    "~J0(1.3)\tIt's_awful... ~E ",
    "~J1(3.8)\tSo_you_don't_know ~N\n\t\t\tanything_either.__Great. ",
    "~J1(2.5)\tI_just_don't_get_it. ~E ",
    "~J1(4.0)\tIt's_like_this_is ~N\n\t\t\tall_some_kind_of_bad_dream. ",
    "~J1(2.8)\tYeah. ~N\n\t\t\tA_living_nightmare. ~E ",
    "~J1(3.6)\tLet_me_ask_you,_have_you_seen ~N\n\t\t\ta_little_girl_around_here? ",
    "~J1(2.8)\tShort,_black_hair. ~N\n\t\t\tSeven_years_old. ",
    "~J1(3.8)\tA_seven-year-old_girl? ~N\n\t\t\tWhat?_She's_your_daughter? ",
    "~J1(1.2)\tYes. ",
    "~J1(3.0)\tA_seven-year-old_girl... ",
    "~J1(4.8)\tI_can't_say_that_I_have. ~N\n\t\t\tI_was_unconscious_all_this_time. ",
    "~J1(1.3)\tI'm_sorry. ~E ",
    "~J1(2.2)\tThat's_alright. ",
    "~J1(3.8)\tDo_you_know_anything_about_all ~N\n\t\t\tthat_weird_stuff_in_the_basement? ",
    "~J1(3.8)\tNo.__Why? ~N\n\t\t\tIs_there_something_down_there? ",
    "~J1(2.7)\tYou_don't_know? ~N\n\t\t\tDon't_you_work_here? ",
    "~J1(4.0)\tWe're_under_strict_orders_never_to ~N\n\t\t\tenter_the_basement_storeroom. ",
    "~J1(2.0)\tSo_I_really_don't_know. ~E ",
    "~J1(2.0)\tWhat_did_you_say_was_down_there? ",
    "~J1(1.7)\tWell,_it's... ~E ",
    "~J0(0.8)\t~E ",
    "~J0(2.5)\tDamn! ~N\n\t\t\tMy_head...  ",
    "~J0(2.5)\tWhat's_wrong? ~N\n\t\t\tHarry...? ~E ",
    "~J0(2.6)\tHarry, ~N\n\t\t\tlet_me_help_you. ~E ",
    "~J0(1.0)\t~E ",
    "\tThere_is_ a_ ~C2 Plate_of_[Queen] ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tUsed_the_ ~C2 Examination_room_key ~C7 . ~E ",
    "\tThere_is_a_broken ~N\n\tvending_machine. ~E ",
    "\tNothing_unusual. ~E ",
    "\tThe_refrigerator_is_empty. ~E ",
    "\tNothing_helpful. ~E ",
    "\tNothing_useful ~N\n\tin_the_desk_drawer. ~E ",
    "\tA_sound_is_heard ~N\n\tfrom_beyond_the_door. ~E "
};

const VECTOR3 D_800CB1E0 = { 0x0000E800, 0xFFFFF000, 0x0008BE66 };

void func_800D21C4(void) // 0x800D21C4
{
    s32     i;
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    if (!Savegame_EventFlagGet(EventFlag_232) && g_MapEventData->pointOfInterestIdx_5 == 5)
    {
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
        {
            if ((g_SysWork.npcs_1A0[i].model_0.charaId_0 > Chara_None && g_SysWork.npcs_1A0[i].model_0.charaId_0 < Chara_LockerDeadBody) &&
                g_SysWork.npcs_1A0[i].health_B0 > Q12(0.0f))
            {
                break;
            }
        }

        if (i != ARRAY_SIZE(g_SysWork.npcs_1A0))
        {
            g_DeltaTime = Q12(0.0f);
        }

        switch (g_SysWork.sysStateStep_C[0])
        {
            case 0:
                Player_ControlFreeze();
                func_8005DC1C(Sfx_DoorLocked, &sfxPos, Q8(0.5f), 0);
                SysWork_StateStepIncrement(0);

            case 1:
                SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
                break;

            case 2:
                MapMsg_DisplayAndHandleSelection(false, 12, false, false, 0, false);
                break;

            case 3:
                SysWork_StateStepIncrement(0);

            case 4:
            case 6:
                func_8005DC1C(Sfx_Unk1529, &D_800CB1E0, Q8(0.5f), 0);
                SysWork_StateStepIncrement(0);

            case 5:
                SysWork_StateStepIncrementDelayed(Q12(0.2f), false);
                break;

            case 7:
                SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
                break;

            case 8:
                MapMsg_DisplayAndHandleSelection(false, 54, false, false, 0, false);
                break;

            case 9:
                SysWork_StateStepIncrement(0);

            default:
                Player_ControlUnfreeze(false);
                SysWork_StateSetNext(SysState_Gameplay);
                Savegame_EventFlagSet(EventFlag_232);
                break;
        }
    }
    else
    {
        Map_MessageWithSfx(0xC, Sfx_DoorLocked, &sfxPos);
    }
}

void func_800D2470(void) // 0x800D2470
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 52:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S04_HealthDrink0;
            break;

        case 53:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S04_HealthDrink1;
            break;

        case 54:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S04_HealthDrink2;
            break;

        case 55:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S04_HealthDrink3;
            break;

        case 56:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M3S04_HandgunBullets;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D250C(void) // 0x800D250C
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_ExaminationRoomKey, 1);
    Map_MessageWithSfx(48, Sfx_UseKey, &sfxPos);

    Savegame_EventFlagSet(EventFlag_258);
    Savegame_MapMarkingSet(MapMarkFlag_AltHospital1F_WomensBathroomBroken);
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800D25D0

void func_800D2668(void) // 0x800D2668
{
    typedef enum _EventState
    {
        EventState_Skip = 25
    } e_EventState;

    s32       i;
    SVECTOR3* tmpSvec;

    // Skip.
    if (g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4 &&
        g_SysWork.sysStateStep_C[0] >= 2 && g_SysWork.sysStateStep_C[0] < 23)
    {
        SysWork_StateStepSet(0, EventState_Skip);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800D5A48[0] = Q12(2.2f);
            D_800D5A48[1] = Q12(2.1f);
            D_800D5A48[2] = Q12(2.6f);
            D_800D5A3C = 0;

            Fs_QueueStartRead(FILE_ANIM_HSPTL3_DMS, FS_BUFFER_11);
            Chara_Load(0, Chara_Lisa, &g_SysWork.npcCoords_FC0[0], -1, NULL, NULL);
            Chara_ProcessLoads();
            Chara_Spawn(Chara_Lisa, 0, Q12(4.4f), Q12(269.9f), 0, 3);

            sharedFunc_800D88AC_0_s00(&g_SysWork.npcs_1A0[0]);
            DmsHeader_FixOffsets(FS_BUFFER_11);

            g_SysWork.field_30 = 20;
            ScreenFade_ResetTimestep();
            g_SysWork.flags_22A4 |= SysFlag2_3;
            Game_TurnFlashlightOn();

            g_SysWork.field_235C = NULL;
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightIntensity_2378 = Q12(0.7f);
            Math_Vector3Set(&g_SysWork.pointLightPosition_2360, Q12(58.34f), Q12(-1.93f), Q12(141.8f));

            // @hack
            // Math_SetSVectorFast(&g_SysWork.pointLightRot_2370, Q12_ANGLE(-15.0f), Q12_ANGLE(-177.0f), Q12_ANGLE(0.0f));
            *((s32*) (&(&g_SysWork.pointLightRot_2370)->vx)) = ((s32) (0xff56 & 0xFFFF)) | ((s32) (0xf823 << 16));
            tmpSvec = &g_SysWork.pointLightRot_2370;
            *((s16*) (&tmpSvec->vz)) = 0;

            func_8008D438();
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();

            D_800D5A40 = 0;
            D_800D5A4E = 0;

            SysWork_StateStepIncrement(0);
            break;

        case 1:
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 5, false);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 51, false);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 3:
            Map_MessageWithAudio(15, &D_800D5A3C, &D_800D599C);
            break;

        case 4:
            func_80085EB8(0, g_SysWork.npcs_1A0, 6, false);
            SysWork_StateStepIncrement(0);

        case 5:
            Map_MessageWithAudio(19, &D_800D5A3C, &D_800D599C);
            SysWork_StateStepIncrementAfterTime(&D_800D5A40, Q12(10.0f), Q12(1.0f), Q12(21.0f), true, false);
            break;

        case 6:
            D_800D5A40 = Q12(22.0f);

            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 7, false);
            SysWork_StateStepIncrement(0);
            break;

        case 7:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            break;

        case 8:
            SysWork_StateStepIncrement(0);

        case 9:
            Map_MessageWithAudio(23, &D_800D5A3C, &D_800D599C);
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(0.7f), false);
            break;

        case 11:
            Map_MessageWithAudio(25, &D_800D5A3C, &D_800D599C);
            break;

        case 12:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        case 13:
            Map_MessageWithAudio(27, &D_800D5A3C, &D_800D599C);
            break;

        case 14:
            Map_MessageWithAudio(34, &D_800D5A3C, &D_800D599C);
            Savegame_EventFlagSet(EventFlag_298);
            break;

        case 15:
            Map_MessageWithAudio(40, &D_800D5A3C, &D_800D599C);
            break;

        case 16:
            SysWork_StateStepIncrement(0);

        case 17:
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 0x7D, false);
            func_80085EB8(0, &g_SysWork.npcs_1A0[0], 8, false);
            SD_Call(Sfx_Unk1522);

            D_800D5A4E++;

            SysWork_StateStepIncrement(0);

        case 18:
            Map_MessageWithAudio(42, &D_800D5A3C, &D_800D599C);
            SysWork_StateStepIncrementAfterTime(&D_800D5A40, Q12(9.0f), Q12(23.0f), Q12(139.0f), true, false);
            break;

        case 19:
            SysWork_StateStepIncrementDelayed(Q12(0.5f), false);
            SysWork_StateStepIncrementAfterTime(&D_800D5A40, Q12(9.0f), Q12(23.0f), Q12(139.0f), true, false);
            break;

        case 20:
            Map_MessageWithAudio(43, &D_800D5A3C, &D_800D599C);
            SysWork_StateStepIncrementAfterTime(&D_800D5A40, Q12(9.0f), Q12(23.0f), Q12(139.0f), true, false);
            break;

        case 21:
            Map_MessageWithAudio(45, &D_800D5A3C, &D_800D599C);
            SysWork_StateStepIncrementDelayed(Q12(2.2f), false);
            SysWork_StateStepIncrementAfterTime(&D_800D5A40, Q12(9.0f), Q12(23.0f), Q12(139.0f), true, false);

            if (g_SysWork.sysStateStep_C[0] != 21)
            {
                SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(1.0f), false);
            }
            break;

        case 22:
            Map_MessageWithAudio(45, &D_800D5A3C, &D_800D599C);
            SysWork_StateStepIncrementAfterTime(&D_800D5A40, Q12(9.0f), Q12(23.0f), Q12(139.0f), true, false);
            break;

        case 23:
            SysWork_StateStepIncrementAfterFade(1, true, 0, 0, false);
            SysWork_StateStepIncrementAfterTime(&D_800D5A40, Q12(9.0f), Q12(23.0f), Q12(139.0f), true, false);
            break;

        case 24:
            Map_MessageWithAudio(46, &D_800D5A3C, &D_800D599C);
            Savegame_EventFlagSet(EventFlag_299);
            break;

        case EventState_Skip:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            sharedFunc_800D2EF4_0_s00();
            func_80088F94(g_SysWork.npcs_1A0, 0, 0);

            D_800D5A40 = NO_VALUE;

            Savegame_EventFlagSet(EventFlag_294);
            Savegame_MapMarkingSet(MapMarkFlag_AltHospital1F_WomensBathroomBroken);
            func_8008D448();
            break;
    }

    if (D_800D5A4E != Q12(0.0f))
    {
        D_800D5A4E += g_DeltaTime >> 1;
        if (D_800D5A4E > Q12(1.0f))
        {
            D_800D5A4E = Q12(1.0f);
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1522, 0, -(D_800D5A4E >> 4), 0);

        i = 0;
        while (i < 3)
        {
            if (D_800D5A48[i] != 0)
            {
                D_800D5A48[i] -= g_DeltaTime;

                if ((D_800D5A48[i] << 16) <= 0)
                {
                    D_800D5A48[i] = 0;
                    SD_Call(Sfx_Unk1522);
                    D_800D5A4E = 1;
                }
                break;
            }

            i++;
        }
    }

    if (D_800D5A40 >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800D5A40, FS_BUFFER_11);
        Dms_CharacterGetPosRot(&g_SysWork.npcs_1A0[0].position_18, &g_SysWork.npcs_1A0[0].rotation_24, "LISA", D_800D5A40, FS_BUFFER_11);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800D5A20, &D_800D5A30, NULL, D_800D5A40, FS_BUFFER_11));
        vcUserCamTarget(&D_800D5A20, NULL, true);
        vcUserWatchTarget(&D_800D5A30, NULL, true);
    }
}

void func_800D2E58(void) // 0x800D2E58
{
    Event_ItemTake(InventoryItemId_PlateOfQueen, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S04_PickupPlateOfQueen, 47);
}

INCLUDE_RODATA("maps/map3_s04/nonmatchings/map3_s04_2", sharedData_800CB088_3_s01);

INCLUDE_RODATA("maps/map3_s04/nonmatchings/map3_s04_2", sharedData_800CB094_3_s01);

#include "maps/shared/sharedFunc_800D15F0_3_s01.h" // 0x800D2E84

void Map_WorldObjectsInit(void) // 0x800D3BD0
{
    WorldObjectNoRotInit(&g_WorldObject_Plate, "PLATE_NE", 100.0f, 0.0f, 60.0f);

    WorldObjectInit(&g_WorldObject_SavePad, D_800A99E4.savePadName_4, 102.5972f, -0.8191f, 58.7896f, 0.0f, 86.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[0], "DR1L_HID", 19.1f, 0.0f, 59.1f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[1], "DR1R_HID", 19.1f, 0.0f, 59.1f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[2], "DR3L_HID", 19.1f, 0.0f, 59.1f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[3], "DR3R_HID", 19.1f, 0.0f, 59.1f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[4], "DR2L_HID", 19.1f, 0.0f, 59.1f);
    WorldObjectNoRotInit(&g_WorldObject_Dr[5], "DR2R_HID", 19.1f, 0.0f, 59.1f);

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

// Rodata at the end of this file. TODO: Inline once all users are decompiled.
extern SVECTOR3 D_800CB35C;
extern VECTOR3 D_800CB364;
extern VECTOR3 D_800CB370;

void Map_WorldObjectsUpdate(void) // 0x800D3DA4
{
    s32    cellZ0;
    s32    cellX0;
    s32    projCellZ0;
    s32    projCellX0;
    s32    i;
    q19_12 drZ;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    cellZ0 = g_SysWork.playerWork_4C.player_0.position_18.vz / CHUNK_CELL_SIZE;
    cellX0 = g_SysWork.playerWork_4C.player_0.position_18.vx / CHUNK_CELL_SIZE;

    if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(0.0f))
    {
        projCellX0 = cellX0 + 17;
    }
    else
    {
        projCellX0 = cellX0 + 15;
    }

    if (g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(0.0f))
    {
        projCellZ0 = cellZ0 + 17;
    }
    else
    {
        projCellZ0 = cellZ0 + 15;
    }

    switch (PACKED_CELL_XZ(projCellX0, projCellZ0))
    {
        case PACKED_CELL_XZ(19, 18):
            if (!Savegame_EventFlagGet(EventFlag_M3S04_PickupPlateOfQueen))
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Plate.object_0, &g_WorldObject_Plate.position_1C, &D_800CB35C);
            }

            WorldGfx_ObjectAdd(&g_WorldObject_SavePad.object_0, &g_WorldObject_SavePad.position_1C, &g_WorldObject_SavePad.rotation_28);
            break;

        case PACKED_CELL_XZ(17, 18):
            if (g_SysWork.sysState_8 == SysState_Gameplay && g_WorldObject_Dr->position_1C.vz != Q12(59.1f))
            {
                drZ = Q12(59.1f);

                for (i = ARRAY_SIZE(g_WorldObject_Dr) - 1; i >= 0; i--)
                {
                    g_WorldObject_Dr[i].position_1C.vz = drZ;
                }
            }

            for (i = 0; i < ARRAY_SIZE(g_WorldObject_Dr); i++)
            {
                WorldGfx_ObjectAdd(&g_WorldObject_Dr[i].object_0, &g_WorldObject_Dr[i].position_1C, &D_800CB35C);
            }
            break;
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_300))
        {
            if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(101.5f) &&
                g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(59.0f))
            {
                func_8005DC1C(Sfx_Unk1530, &D_800CB364, Q8_CLAMPED(1.0f), 2);
                Savegame_EventFlagSet(EventFlag_300);

                if (g_SavegamePtr->ovlEnemyStates[g_SavegamePtr->mapOverlayId_A4] & (1 << 2))
                {
                    g_SavegamePtr->ovlEnemyStates[g_SavegamePtr->mapOverlayId_A4] &= ~(1 << 3);
                }
            }
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_316))
        {
            if (Savegame_EventFlagGet(EventFlag_301) && g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(104.0f))
            {
                if (!Vw_AabbVisibleInScreenCheck(Q12(139.0f), Q12(142.0f), Q12(-3.0f), Q12(0.0f), Q12(98.8f), Q12(99.0f)))
                {
                    func_8005DC1C(Sfx_Unk1528, &D_800CB370, 0xFF, 2);
                    Savegame_EventFlagSet(EventFlag_316);
                }
            }

            if (g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(100.0f))
            {
                Savegame_EventFlagSet(EventFlag_301);
            }
        }
    }

    if (g_Controller0->btnsClicked_10 & ControllerFlag_R3)
    {
        SD_Call(Sfx_Unk1529);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S04_HealthDrink0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S04_HandgunBullets))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }
}

void func_800D43B8(void) // 0x800D43B8
{
    if (Savegame_EventFlagGet(EventFlag_300))
    {
        func_80088FF4(Chara_PuppetDoctor, 2, 1);
        func_80088FF4(Chara_PuppetDoctor, 3, 1);
    }
}

INCLUDE_RODATA("maps/map3_s04/nonmatchings/map3_s04_2", D_800CB35C);

INCLUDE_RODATA("maps/map3_s04/nonmatchings/map3_s04_2", D_800CB364);

INCLUDE_RODATA("maps/map3_s04/nonmatchings/map3_s04_2", D_800CB370);
