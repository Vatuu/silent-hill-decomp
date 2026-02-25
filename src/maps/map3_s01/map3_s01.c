#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/map3/map3_s01.h"
#include "maps/particle.h"
#include "maps/characters/creeper.h"
#include "maps/characters/player.h"

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_Creeper` split.
#include "../src/maps/characters/creeper.c" // 0x800CEE4C

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D10C0

#include "maps/shared/Map_RoomIdxGet.h" // 0x800D10D0

#include "maps/shared/Map_RoomBgmInit_CheckCond.h" // 0x800D1178

#include "maps/shared/Map_RoomBgmInit_3_s00_CondTrue.h" // 0x800D11AC

#include "maps/shared/Map_RoomBgmInit_3_s00_CondFalse.h" // 0x800D11EC

void func_800D138C(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800D1394

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800D1428

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tThe_elevator_doesn't ~N\n\tappear_to_be_working. ~E ",
    "\tA_glass_vial_lies_shattered. ",
    "\tIt's_not_just_broken. ~N\n\tIt_looks_smashed_on_purpose. ~E ",
    "\tThe_remaining_liquid_is_emptied ~N\n\tinto_the_ ~C2 Plastic_bottle ~C7 . ",
    "\tNow_what_have_we_here? ~E ",
    "\tA_glass_vial_lies_shattered. ~E ",
    "\tThere_is_a_ ~C2 Plastic_bottle ~C7 . ~N\n\tTake_it? ~S4 ",
    "~H\tThere_is_a_ ~C5 Hospital_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "~H\tThere_is_a ~N\n\t~C5 Hospital_basement_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Basement_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "~C3\tThe_in-house_generator ~N\n\t\tpowers_elevators,_ICUs ~N\n\t\tand_operating_rooms_only. ",
    "\tDo_you_want_to_press_the_switch? ~S4 ",
    "\tThe_generator_is_on. ~E ",
    "\tUsed_the_ ~C2 Basement_key ~C7 _. ~E ",
    "\tI_should_search_the_hospital. ~E ",
    "\tThese_are_phones_and_phonebooks. ~N\n\tNo_need_to_examine_this. ~E ",
    "\tThere's_a_vending_machine. ~N\n\tIt_doesn't_work. ~E ",
    "\tThe_shelves_are_all_messed_up. ~N\n\tWho_did_this? ~E ",
    "\tBooks_are_scattered ~N\n\taround_the_desk. ~N\n\tNothing_else_special_here. ~E ",
    "\tThe_phone's_out. ~N\n\tCan't_get_a_dial_tone. ~E ",
    "\tThere's_a_white_board. ~N\n\tNothing_special_written_here. ~E ",
    "\tThere_is_a_newspaper. ",
    "\tThis_article's_been ~N\n\tclipped_out... ~E ",
    "\tThe_refrigerator_is_empty. ~E ",
    "\tNothing_unusual. ~E ",
    "\tNothing_helpful. ~E "
};

void func_800D14BC(void) // 0x800D14BC
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 101:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M3S01_HealthDrink;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D1500(void) // 0x800D1500
{
    Event_CommonItemTake(CommonPickupItemId_FirstAidKit, EventFlag_M3S00_FirstAidKit);
}

void func_800D1524(void) // 0x800D1524
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_BasementKey, 1);
    Map_MessageWithSfx(28, Sfx_UseKey, &sfxPos); // "Used basement key."

    Savegame_EventFlagSet(EventFlag_MapMark_585);
    Savegame_EventFlagSet(EventFlag_M3S01_BasementDoorOpen);
}

INCLUDE_RODATA("maps/map3_s01/nonmatchings/map3_s01", sharedData_800CB088_3_s01);

INCLUDE_RODATA("maps/map3_s01/nonmatchings/map3_s01", sharedData_800CB094_3_s01);

INCLUDE_RODATA("maps/map3_s01/nonmatchings/map3_s01", sharedData_800CB0A0_3_s01);

#include "maps/shared/sharedFunc_800D15F0_3_s01.h" // 0x800D15F0

void MapEvent_UnknownLiquidInteract(void) // 0x800D23AC
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_SHATVIAL_TIM, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            func_800862F8(1, 0, false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 7:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 16, 0, 0, 0, false); // "A glass vial lies shattered."
            break;

        case 8:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(0.0f), false);
            break;

        case 9:
            SysWork_StateStepIncrementAfterFade(2, false, 0, Q12(0.0f), false);
            break;

        case 10:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_204);
            break;
    }
}

void MapEvent_UseBottleOnLiquid(void) // 0x800D25A8
{
    typedef enum _EventState
    {
        EventState_0     = 0,
        EventState_1     = 1,
        EventState_2     = 2,
        EventState_SfxId = 3,
        EventState_Msg   = 4,
        EventState_5     = 5
    } e_EventState;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case EventState_0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case EventState_1:
            func_80085DF0();
            break;

        case EventState_2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case EventState_SfxId:
            func_8005DC1C(Sfx_Unk1493, &QVECTOR3(141.6f, -0.0999f, 20.75f), Q8_CLAMPED(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case EventState_Msg:
            MapMsg_DisplayAndHandleSelection(false, 18, 0, 0, 0, false); // "The remaining liquid is emptied into the Plastic bottle."
            break;

        case EventState_5:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_M3S01_PickupUnknownLiquid);

            // Replace Plastic Bottle with Unknown Liquid in inventory.
            Player_ItemRemove(InventoryItemId_PlasticBottle, 1);
            func_80086470(3, InventoryItemId_UnknownLiquid, DEFAULT_PICKUP_ITEM_COUNT, false);
            break;
    }
}

void MapEvent_PlasticBottleTake(void) // 0x800D2720
{
    Event_ItemTake(InventoryItemId_PlasticBottle, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S01_PickupPlasticBottle, 21);
}

void MapEvent_MapTake0(void) // 0x800D274C
{
    Event_MapTake(17, EventFlag_M3S00_PickupMap, 22);
}

void MapEvent_MapTake1(void) // 0x800D2774
{
    Event_MapTake(16, EventFlag_M3S01_PickupMap, 23);
}

void func_800D279C(void) // 0x800D279C
{
    Event_ItemTake(InventoryItemId_BasementKey, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M3S01_PickupBasementKey, 24);
}

void MapEvent_Generator0(void) // 0x800D27C8
{
    typedef enum _EventState
    {
        EventState_PressSwitch     = 3,
        EventState_DontPressSwitch = NO_VALUE
    } e_EventState;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            g_SysWork.silentYesSelection_2350_4 = true;
            MapMsg_DisplayAndHandleSelection(true, 25, EventState_PressSwitch, EventState_DontPressSwitch, 0, false); // "Do you want to press the switch?"
            break;

        case EventState_PressSwitch:
            func_8005DC1C(Sfx_Unk1494, &QVECTOR3(140.5f, -0.5f, -20.6f), Q8_CLAMPED(0.5f), 0);
            SD_Call(Sfx_Unk1495);
            Savegame_EventFlagSet(EventFlag_M3S01_GeneratorOn);

            g_GeneratorMakeNoise = true;

            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        case 5:
            Savegame_EventFlagSet(EventFlag_M3S01_GeneratorOn);
            g_GeneratorMakeNoise = true;
            SysWork_StateStepIncrement(0);

        default: // `EventState_DontPressSwitch`
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
    if (Savegame_EventFlagGet(EventFlag_M3S01_GeneratorOn))
    {
        func_800894B8(144);
    }
}

void func_800D29A4(void) // 0x800D29A4
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 27, 0, 0, 0, false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    func_800894B8(0x60); // Hex?
}

void func_800D2A88(void) // 0x800D2A88
{
    if (g_SysWork.sysStateStep_C[1] == 0)
    {
        func_8005DC1C(Sfx_MenuMap, &QVECTOR3(61.72f, -0.8f, 100.5098f), Q8_CLAMPED(0.5f), 0);
    }

    MapMsg_DisplayWithTexture(Sfx_Unk1916, Q12(0.0f), Q12(0.0f), 36);
    Savegame_EventFlagSet(EventFlag_203);
}

void Map_WorldObjectsInit(void) // 0x800D2AF4
{
    D_800D8734 = 0;
    g_GeneratorMakeNoise = false;

    WorldObjectNoRotInit(&g_WorldObject1, "BOT_HIDE", 20.3f, 0.0f, 59.25f);

    WorldObjectInit(&g_WorldObject2, "MAP_HIDE", 60.0f, 0.0f, 60.0f, 0.0f, 9.7f, 0.0f);

    WorldObjectInit(&g_WorldObject5, "KEY_HIDE", 100.3f, 0.0f, 58.9f, 0.0f, 72.8f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject3[0], "BT3_HIDE", 59.1f, 0.0f, 19.1f);

    WorldObjectNoRotInit(&g_WorldObject3[1], "BT4_HIDE", 59.1f, 0.0f, 19.1f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[0], "DR1L_HID", 59.1f, 0.0f, 19.1f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[1], "DR1R_HID", 59.1f, 0.0f, 19.1f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[2], "DR3L_HID", 59.1f, 0.0f, 19.1f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[3], "DR3R_HID", 59.1f, 0.0f, 19.1f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[4], "DR2L_HID", 59.1f, 0.0f, 19.1f);

    WorldObjectNoRotInit(&g_WorldObject_Dr[5], "DR2R_HID", 59.1f, 0.0f, 19.1f);

    WorldObjectInit(&g_WorldObject6, D_800A99E4.savePadName_4, 26.0f, -1.0198f, 144.5498f, 0.0f, 163.8f, 0.0f);

    WorldObjectInit(&g_WorldObject7, "MAP_HIDE", 24.6f, -1.56f, 143.16f, 0.0f, 180.0f, 0.0f);

    WorldObjectInit(&g_WorldObject8, "MAP2_HID", 24.6f, -1.56f, 143.16f, 0.0f, 180.0f, 0.0f);

    WorldObjectInit(&g_WorldObject9, D_800A99E4.firstAidKitName_8, 27.6f, -0.45f, 143.6f, 0.0f, -90.0f, 0.0f);

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800D2E54
{
    s32    i;
    q19_12 posZ;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S01_PickupPlasticBottle))
        {
            WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S01_PickupMap))
        {
            WorldGfx_ObjectAdd(&g_WorldObject2.object_0, &g_WorldObject2.position_1C, &g_WorldObject2.rotation_28);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S01_PickupBasementKey))
        {
            WorldGfx_ObjectAdd(&g_WorldObject5.object_0, &g_WorldObject5.position_1C, &g_WorldObject5.rotation_28);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (D_800D8734 != 1)
        {
            Gfx_MapInitMapEffectsUpdate(7, 4);
            Game_TurnFlashlightOff();
            D_800D8734 = 1;
        }
    }

    if ((PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0)) ||
        (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1)))
    {
        if (D_800D8734 != 2)
        {
            Gfx_MapInitMapEffectsUpdate(13, 13);
            Game_TurnFlashlightOff();
            D_800D8734 = 2;
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (D_800D8734 != 3)
        {
            Gfx_MapInitMapEffectsUpdate(2, 2);
            D_800D8734 = 3;
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (D_800D8734 != 4)
        {
            D_800D8734 = 4;

            Gfx_MapInitMapEffectsUpdate(4, 4);

            g_SysWork.field_235C = NULL;
            g_SysWork.pointLightPosition_2360.vx = Q12(59.1f);
            g_SysWork.pointLightPosition_2360.vy = Q12(-3.0f);
            g_SysWork.pointLightPosition_2360.vz = Q12(19.1f);
            g_SysWork.field_236C = NULL;
            g_SysWork.pointLightRot_2370.vx = Q12_ANGLE(-90.0f);
            g_SysWork.pointLightRot_2370.vy = Q12_ANGLE(0.0f);
            g_SysWork.pointLightRot_2370.vz = Q12_ANGLE(0.0f);
            g_SysWork.pointLightIntensity_2378 = Q12(0.7f);

            func_8008D438();

            posZ = Q12(19.1f);
            for (i = 5; i >= 0; i--)
            {
                g_WorldObject_Dr[i].position_1C.vz = posZ;
            }
        }

        for (i = 0; i < ARRAY_SIZE(g_WorldObject_Dr); i++)
        {
            WorldGfx_ObjectAdd(&g_WorldObject_Dr[i].object_0, &g_WorldObject_Dr[i].position_1C, &(SVECTOR3){ 0, 0, 0 });
        }

        if (Savegame_EventFlagGet(EventFlag_MapMark_AltHospital2F_OperatingPrepRoomArrow) && Savegame_EventFlagGet(EventFlag_MapMark_AltHospital2F_CorridorMidArrows))
        {
            WorldGfx_ObjectAdd(&g_WorldObject3[1].object_0, &g_WorldObject3[1].position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
        else
        {
            WorldGfx_ObjectAdd(&g_WorldObject3[0].object_0, &g_WorldObject3[0].position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (D_800D8734 != 5)
        {
            Gfx_MapInitMapEffectsUpdate(2, 2);
            D_800D8734 = 5;
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (D_800D8734 != 6)
        {
            Gfx_MapInitMapEffectsUpdate(2, 2);
            D_800D8734 = 6;
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (Savegame_EventFlagGet(EventFlag_M3S01_GeneratorOn))
        {
            if (!g_GeneratorMakeNoise)
            {
                SD_Call(Sfx_Unk1503);
                g_GeneratorMakeNoise++;
            }
            else if (g_GeneratorMakeNoise == true)
            {
                func_8005DE0C(Sfx_Unk1495, &D_800D4CE4, 0x80, Q12(16.0f), 0);
                func_8005DE0C(Sfx_Unk1503, &D_800D4CE4, 0x80, Q12(16.0f), 0);
            }
        }
    }
    else
    {
        if (g_GeneratorMakeNoise == true)
        {
            Sd_SfxStop(Sfx_Unk1495);
            Sd_SfxStop(Sfx_Unk1503);
            g_GeneratorMakeNoise = false;
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        WorldGfx_ObjectAdd(&g_WorldObject6.object_0, &g_WorldObject6.position_1C, &g_WorldObject6.rotation_28);

        if (!Savegame_EventFlagGet(EventFlag_M3S00_PickupMap))
        {
            WorldGfx_ObjectAdd(&g_WorldObject7.object_0, &g_WorldObject7.position_1C, &g_WorldObject7.rotation_28);
        }
        else
        {
            WorldGfx_ObjectAdd(&g_WorldObject8.object_0, &g_WorldObject8.position_1C, &g_WorldObject8.rotation_28);
        }

        if (!Savegame_EventFlagGet(EventFlag_M3S00_FirstAidKit))
        {
            WorldGfx_ObjectAdd(&g_WorldObject9.object_0, &g_WorldObject9.position_1C, &g_WorldObject9.rotation_28);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M3S01_HealthDrink))
        {
            WorldGfx_ObjectAdd(&g_WorldObjectA, &g_WorldObjectAPos.position_0, &g_WorldObjectAPos.rotation_C);
        }
    }
}
