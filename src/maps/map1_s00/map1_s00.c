#include "bodyprog/bodyprog.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/map1/map1_s00.h"

INCLUDE_RODATA("asm/maps/map1_s00/nonmatchings/map1_s00", D_800C9578);

INCLUDE_RODATA("asm/maps/map1_s00/nonmatchings/map1_s00", g_MapOverlayHeader);

#include "maps/shared/sharedFunc_800CB6B0_0_s00.h" // 0x800CB7A8

#include "maps/shared/sharedFunc_800CBBBC_0_s00.h" // 0x800CBC34

#include "maps/shared/sharedFunc_800CBC94_0_s00.h" // 0x800CBD0C

#include "maps/shared/Particle_Update.h" // 0x800CC018

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800CEB24_0_s00); // 0x800CC59C

#include "maps/shared/sharedFunc_800CF2A4_0_s01.h" // 0x800CC914

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800CEFD0_1_s02); // 0x800CCA64

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800CFFF8_0_s00); // 0x800CCE2C

#include "maps/shared/sharedFunc_800CE954_7_s03.h" // 0x800CCF40

#include "maps/shared/sharedFunc_800D01BC_0_s00.h" // 0x800CCF48

#include "maps/shared/sharedFunc_800CF9A8_0_s01.h" // 0x800CD000

#include "maps/shared/sharedFunc_800D08B8_0_s00.h" // 0x800CD088

#include "maps/shared/sharedFunc_800D0A60_0_s00.h" // 0x800CD208

#include "maps/shared/sharedFunc_800D0B18_0_s00.h" // 0x800CD2C0

#include "maps/shared/sharedFunc_800D0E04_0_s00.h" // 0x800CD458

#include "maps/shared/sharedFunc_800CFFD8_0_s01.h" // 0x800CD478

#include "maps/shared/sharedFunc_800D0850_0_s01.h" // 0x800CDCF0

#include "maps/shared/sharedFunc_800CDAA8_0_s02.h" // 0x800CE0DC

#include "maps/shared/sharedFunc_800D1C38_0_s00.h" // 0x800CE610

#include "maps/shared/sharedFunc_800D209C_0_s00.h" // 0x800CEA3C

#include "maps/shared/sharedFunc_800D20D8_0_s00.h" // 0x800CEA78

#include "maps/shared/sharedFunc_800D20E4_0_s00.h" // 0x800CEA84

#include "maps/shared/sharedFunc_800D2244_0_s00.h" // 0x800CEBE4

s32 func_800CEDBC() // 0x800CEDBC
{
    return 0;
}

#include "maps/shared/sharedFunc_800D2C7C_0_s00.h" // 0x800CEDC4

#include "maps/shared/sharedFunc_800D2D2C_0_s00.h" // 0x800CEE74

#include "maps/shared/sharedFunc_800D2D44_0_s00.h" // 0x800CEE8C

#include "maps/shared/sharedFunc_800D2D6C_0_s00.h" // 0x800CEEB4

#include "maps/shared/sharedFunc_800D2D84_0_s00.h" // 0x800CEECC

#include "maps/shared/sharedFunc_800D2DAC_0_s00.h" // 0x800CEEF4

#include "maps/shared/sharedFunc_800D2E50_0_s00.h" // 0x800CEF98

#include "maps/shared/sharedFunc_800D2E60_0_s00.h" // 0x800CEFA8

void func_800CEFB4(void) {}

void func_800CEFBC(void) {}

void func_800CEFC4(void) {}

void func_800CEFCC(void) {}

void func_800CEFD4(void) {}

s32 func_800CEFDC() // 0x800CEFDC
{
    return 0;
}

void func_800CEFE4(void) {}

#include "maps/shared/sharedFunc_800D2EA4_0_s00.h" // 0x800CEFEC

#include "maps/shared/sharedFunc_800D2EB4_0_s00.h" // 0x800CEFFC

#include "maps/shared/sharedFunc_800D2EF4_0_s00.h" // 0x800CF03C

#include "maps/shared/Ai_LarvalStalker_Update.h" // 0x800CF050

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800CF168_1_s00); // 0x800CF168

#include "maps/shared/sharedFunc_800D140C_1_s00.h" // 0x800D140C

#include "maps/shared/sharedFunc_800D1524_1_s00.h" // 0x800D1524

#include "maps/shared/Ai_LarvalStalker_Init.h" // 0x800D16FC

#include "maps/shared/sharedFunc_800D17BC_1_s00.h" // 0x800D17BC

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D1DBC_1_s00); // 0x800D1DBC

#include "maps/shared/Ai_Stalker_Update.h" // 0x800D24F8

#include "maps/shared/Ai_Stalker_Init.h" // 0x800D268C

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D3308_0_s00); // 0x800D28F8

#include "maps/shared/sharedFunc_800D3B44_0_s00.h" // 0x800D3134

void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara) {} // 0x800D34E4

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D4924_0_s00); // 0x800D34EC

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D492C_0_s00); // 0x800D40BC

#include "maps/shared/sharedFunc_800D5098_0_s00.h" // 0x800D4828

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D54A8_0_s00); // 0x800D4C38

#include "maps/shared/sharedFunc_800D5B48_0_s00.h" // 0x800D52D8

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D5C64_0_s00); // 0x800D53F4

#include "maps/shared/sharedFunc_800D5FCC_0_s00.h" // 0x800D575C

#include "maps/shared/sharedFunc_800D63D0_0_s00.h" // 0x800D5B60

#include "maps/shared/sharedFunc_800D654C_0_s00.h" // 0x800D5CDC

#include "maps/shared/sharedFunc_800D6554_0_s00.h" // 0x800D5CE4

#include "maps/shared/sharedFunc_800D670C_0_s00.h" // 0x800D5E9C

#include "maps/shared/sharedFunc_800D67FC_0_s00.h" // 0x800D5F8C

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D6970_0_s00); // 0x800D6100

INCLUDE_ASM("asm/maps/map1_s00/nonmatchings/map1_s00", sharedFunc_800D70C4_0_s00); // 0x800D6854

#include "maps/shared/sharedFunc_800D7BE8_0_s00.h" // 0x800D7378

#include "maps/shared/sharedFunc_800D7E04_0_s00.h" // 0x800D7594

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D7748

#include "maps/shared/sharedFunc_800D7758_1_s00.h" // 0x800D7758

void func_800D77F8(void) // 0x800D77F8
{
    u16 flags;

    if (g_SavegamePtr->mapRoomIdx_A5 == 23)
    {
        flags = 1 << 5;
        if (Savegame_EventFlagGet(EventFlag_71) && Savegame_EventFlagGet(EventFlag_72))
        {
            flags = 0x1FE;
        }
    }
    else
    {
        flags = D_800DCC54[g_SavegamePtr->mapRoomIdx_A5];
    }

    func_80035F4C(flags, Q12(0.1f), &D_800DCC4C);
}

void func_800D7864(void) {}

void func_800D786C(void) // 0x800D786C
{
    VECTOR3 vec = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    func_80086FE8(11, Sfx_Unk1334, &vec); // "Lock is jammed."
}

void func_800D7900(void) // 0x800D7900
{
    VECTOR3 vec = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    func_80086FE8(12, Sfx_Unk1344, &vec); // "It's locked."
}

void func_800D7994(void) // 0x800D7994
{
    VECTOR3 vec = { MAP_POINTS[g_MapEventParam->field_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventParam->field_5].positionZ_8 };

    func_80086FE8(13, Sfx_Unk1342, &vec); // "It's unlocked."
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tThe_tower_door_is_locked. ~E ",
    "\tThe_hands_are_stopped_at_10:00. ~E ",
    "\tThe_hands_are_stopped_at_12:00. ~E ",
    "\tThe_hands_are_stopped_at_5:00. ~E ",
    "\t~C3 A_Golden_Sun ~E ",
    "\t~C3 A_Silver_Moon ~E ",
    "\tThe_door_won't_open. ~E ",
    "~L4 ~M ~C3 10:00 ~N\n\t[Alchemy_laboratory] ~N\n\t~N\n\tGold_in_an_old_man's_palm. ~N\n\tThe_future_hidden_in_his_fist. ~N\n\tExchange_for_sage's_water. ~E ",
    "~L4 ~M ~C3 12:00 ~N\n\t[A_place_with_songs_and_sound] ~N\n\t~N\n\tA_silver_guidepost_is ~N\n\tuntapped_in_lost_tongues. ~N\n\tAwakening_at_the_ordained_order. ~E ",
    "~L4 ~M ~C3 5:00 ~N\n\t[Darkness_that_brings ~N\n\tthe_choking_heat] ~N\n\t~N\n\tFlames_render_the_silence, ~N\n\tawakening_the_hungry_beast. ~N\n\tOpen_time's_door_to_beckon_prey. ~E ",
    "\tIt's_written_in_blood. ~E ",
    "\tCheryl_might_be_here. ~N\n\tI_should_search_for_her. ~E ",
    "\tA_picture_of_a_door. ",
    "\tI_don't_know_who_drew_it, ~N\n\tbut_it_is_certainly_in_bad_taste. ~E ",
    "\tThere_is_a_switch. ~N\n\tDo_you_want_to_press_the_switch? ~S4 ",
    "\tNothing_appears_to_happen. ~E ",
    "\tThe_boiler_is_working. ~E ",
    "\tIt_appears_to_be_broken. ~E ",
    "\tThe_valve_is_tightly_shut. ~N\n\tCan't_move_it. ",
    "\tDon't_know_what_it_is_for, ~N\n\tbetter_leave_it_alone. ~E ",
    "\tNothing_special_is_written. ~E ",
    "\tNothing_useful ~N\n\tin_the_desk_drawer. ~E ",
    "~H\tThere_is_a_ ~C5 School_map ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tMoore,_Ranaldo,_Gordon... ~N\n\tThis_must_be_the_list_of_teachers. ~E ",
    "\tNothing_inside. ~E "
};

void func_800D7A28(void) // 0x800D7A28
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 94:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S00_HandgunBullets0;
            break;

        case 95:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S00_HandgunBullets1;
            break;

        case 96:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S00_HandgunBullets2;
            break;

        case 97:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M1S00_HealthDrink;
            break;

        case 98:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M1S00_FirstAidKit;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800D7AC4(void) // 0x800D7AC4
{
    g_DeltaTime0 = Q12(0.0f);
    func_80087360(FILE_TIM_GOLD1_TIM, Q12(2.5f), Q12(2.0f), 19);
}

void func_800D7AF8(void) // 0x800D7AF8
{
    g_DeltaTime0 = Q12(0.0f);
    func_80087360(FILE_TIM_GOLD2_TIM, Q12(2.5f), Q12(2.0f), 19);
}

void func_800D7B2C(void) // 0x800D7B2C
{
    g_DeltaTime0 = Q12(0.0f);

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8008616C(false, true, 0, Q12(2.5f), false);
            SysWork_StateStepIncrement();
            
        case 1:
            func_800862F8(7, FILE_TIM_GOLD1_TIM, false);
            break;

        case 2:
            func_8008616C(true, true, 0, 0, false);
            break;

        case 3:
            func_800862F8(3, 0, false);
            func_8008616C(false, false, 0, Q12(2.0f), false);
            SysWork_StateStepIncrement();

        case 4:
            func_800862F8(2, 0, false);
            func_800862F8(8, FILE_TIM_GOLD2_TIM, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            func_8008616C(true, false, 0, 0, false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            func_80085E6C(Q12(0.5f), false);
            break;

        case 7:
            Sd_EngineCmd(Sfx_Unk1416);
            SysWork_StateStepIncrement();

        case 8:
            Gfx_BackgroundSpritesTransition(&g_ItemInspectionImg, &D_800A9A04, g_SysWork.field_28);

            g_SysWork.field_28 += Q12(0.0625f);
            if (g_SysWork.field_28 > Q12(1.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 9:
            Sd_EngineCmd(Sfx_Unk1419);
            SysWork_StateStepIncrement();

        case 10:
            func_800862F8(5, 0, false);
            func_80085E6C(Q12(1.0f), false);
            break;

        case 11:
            func_800862F8(5, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 19, 0, 0, 0, false); // "A golden sun..."
            break;

        case 12:
            func_800862F8(5, 0, false);
            func_8008616C(2, true, 0, Q12(2.0f), false);
            break;

        default:
            func_800862F8(6, 0, false);
            func_8008616C(false, false, 0, Q12(2.5f), false);
            Savegame_EventFlagSet(EventFlag_71);

            g_SavegamePtr->mapMarkingFlags_1D4[8] |= 1;

            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D7E48(void) // 0x800D7E48
{
    g_DeltaTime0 = Q12(0.0f);
    func_80087360(FILE_TIM_SILVER1_TIM, Q12(2.5f), Q12(2.0f), 20);
}

void func_800D7E7C(void) // 0x800D7E7C
{
    g_DeltaTime0 = Q12(0.0f);
    func_80087360(FILE_TIM_SILVER2_TIM, Q12(2.5f), Q12(2.0f), 20);
}

void func_800D7EB0(void) // 0x800D7EB0
{
    g_DeltaTime0 = Q12(0.0f);

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8008616C(false, true, 0, Q12(2.5f), false);
            SysWork_StateStepIncrement();

        case 1:
            func_800862F8(7, FILE_TIM_SILVER1_TIM, false);
            break;

        case 2:
            func_8008616C(true, true, 0, 0, false);
            break;

        case 3:
            func_800862F8(3, 0, false);
            func_8008616C(false, false, 0, Q12(2.0f), false);
            SysWork_StateStepIncrement();

        case 4:
            func_800862F8(2, 0, false);
            func_800862F8(8, FILE_TIM_SILVER2_TIM, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            func_8008616C(true, false, 0, 0, false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            func_80085E6C(Q12(0.5f), false);
            break;

        case 7:
            Sd_EngineCmd(1416);
            SysWork_StateStepIncrement();

        case 8:
            Gfx_BackgroundSpritesTransition(&g_ItemInspectionImg, &D_800A9A04, g_SysWork.field_28);

            g_SysWork.field_28 += Q12(0.0625f);
            if (g_SysWork.field_28 > Q12(1.0f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 9:
            Sd_EngineCmd(Sfx_Unk1419);
            SysWork_StateStepIncrement();

        case 10:
            func_800862F8(5, 0, false);
            func_80085E6C(Q12(1.0f), false);
            break;

        case 11:
            func_800862F8(5, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 20, 0, 0, 0, false); // "A silver moon..."
            break;

        case 12:
            func_800862F8(5, 0, false);
            func_8008616C(2, true, 0, Q12(2.0f), false);
            break;

        default:
            func_800862F8(6, 0, false);
            func_8008616C(false, false, 0, Q12(2.5f), false);
            Savegame_EventFlagSet(EventFlag_72);

            g_SavegamePtr->mapMarkingFlags_1D4[8] |= 1;

            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D81CC(void) // 0x800D81CC
{
    g_DeltaTime0 = Q12(0.0f);

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();

        case 1:
            func_80085E6C(1128, false);
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 15, false, false, 0, false); // "The tower door is locked.""
            break;

        case 3:
            if (Savegame_EventFlagGet(EventFlag_72))
            {
                 func_80086E50(FILE_TIM_CLOCK5_TIM, Q12(3.0f), Q12(2.0f));
            }
            else
            {
                if (Savegame_EventFlagGet(EventFlag_71))
                {
                    func_80086E50(FILE_TIM_CLOCK12_TIM, Q12(3.0f), Q12(2.0f));
                }
                else
                {
                    func_80086E50(FILE_TIM_CLOCK_TIM, Q12(3.0f), Q12(2.0f));
                }
            }
            break;

        case 4:
            func_800862F8(2, 0, false);

            if (Savegame_EventFlagGet(EventFlag_72))
            {
                 MapMsg_DisplayAndHandleSelection(false, 18, false, false, 0, false); // "Hands are stopped at 5:00."
            }
            else
            {
                if (Savegame_EventFlagGet(EventFlag_71))
                {
                    MapMsg_DisplayAndHandleSelection(false, 17, false, false, 0, false); // "Hands are stopped at 12:00."
                }
                else
                {
                    MapMsg_DisplayAndHandleSelection(false, 16, false, false, 0, false); // "Hands are stopped at 10:00.""
                }
            }
            break;

        case 5:
            func_80086F44(Q12(3.0f), Q12(2.0f));
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D8354(void) // 0x800D8354
{
    VECTOR3 soundPos;
    VECTOR3 pos;

    do {} while (0); // @hack permuter find.

    pos.vx = MAP_POINTS[g_MapEventParam->field_5].positionX_0;
    pos.vy = Q12(-1.2f);
    pos.vz = MAP_POINTS[g_MapEventParam->field_5].positionZ_8;
    g_DeltaTime0 = 0;
    soundPos = pos;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            func_8005DC1C(Sfx_Unk1344, &soundPos, 0x80, 0);
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 12, 0, 0, 0, false); // "It's locked.""
            break;

        case 3:
            func_80086E50(FILE_TIM_PAPER1_TIM, Q12(3.0f), Q12(2.0f));
            break;

        case 4:
            func_800862F8(2, 0, false);

            if (g_Controller0->btnsClicked_10 & (g_GameWorkPtr->config_0.controllerConfig_0.enter_0 | g_GameWorkPtr->config_0.controllerConfig_0.cancel_2))
            {
                SysWork_StateStepIncrement();
                break;
            }
            break;

        case 5:
            func_80086F44(Q12(3.0f), Q12(2.0f));
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D853C(void) // 0x800D853C
{
    func_80087540(FILE_TIM_PAPER1_TIM, Q12(2.5f), Q12(1.5f), 25, 22);
}

void func_800D8570(void) // 0x800D8570
{
    func_80087540(FILE_TIM_PAPER2_TIM, Q12(2.5f), Q12(1.5f), 25, 23);
}

void func_800D85A4(void) // 0x800D85A4
{
    func_80087540(FILE_TIM_PAPER3_TIM, Q12(2.5f), Q12(1.5f), 25, 24);
}

void func_800D85D8(void) // 0x800D85D8
{
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 3 && g_SysWork.sysStateStep_C[0] < 5)
    {
        ScreenFade_ResetTimestep();
        SysWork_NextStateStepSet(NO_VALUE);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            Camera_PositionSet(NULL, Q12(-56.41f), Q12(-5.67f), Q12(-55.39f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-56.4f), Q12(-1.8699f), Q12(-54.16f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            g_SysWork.player_4C.chara_0.position_18.vy = Q12(-2.3f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(0.0f);

            func_8008616C(0, false, 0, Q12(1.5f), false);
            func_80085EB8(0u, &g_SysWork.player_4C.chara_0, 88, false);
            SysWork_StateStepIncrement();

        case 3:
            func_80085E6C(Q12(3.5f), false);
            g_SysWork.player_4C.chara_0.position_18.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.3f), Q12_SHIFT);
            break;

        case 4:
            g_SysWork.player_4C.chara_0.position_18.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.3f), Q12_SHIFT);
            func_8008616C(2, true, 0, Q12(1.5f), false);
            break;

        default:
            if (Savegame_EventFlagGet(EventFlag_78))
            {
                g_SysWork.player_4C.chara_0.position_18.vx = Q12(-60.0f);
                g_SysWork.player_4C.chara_0.position_18.vy = Q12(0.0f);
                g_SysWork.player_4C.chara_0.position_18.vz = Q12(-63.7f);
                g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(0.0f);

                Savegame_EventFlagClear(EventFlag_184);
                Savegame_EventFlagClear(EventFlag_78);
            } 
            else if (Savegame_EventFlagGet(EventFlag_81))
            {
                g_SysWork.player_4C.chara_0.position_18.vx = Q12(-60.0f);
                g_SysWork.player_4C.chara_0.position_18.vy = Q12(0.6f);
                g_SysWork.player_4C.chara_0.position_18.vz = Q12(-56.3f);
                g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(180.0f);

                Savegame_EventFlagClear(EventFlag_185);
                Savegame_EventFlagClear(EventFlag_81);
            }

            func_8008616C(0, false, 0, Q12(1.5f), false);
            sharedFunc_800D2244_0_s00(true);
            SysWork_StateSetNext(SysState_Gameplay);
            vcReturnPreAutoCamWork(true);
            break;
    }
}

void func_800D8948(void) // 0x800D8948
{
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 4 && g_SysWork.sysStateStep_C[0] < 6)
    {
        ScreenFade_ResetTimestep();
        SysWork_NextStateStepSet(NO_VALUE);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            Savegame_EventFlagClear(EventFlag_82);
            Savegame_EventFlagClear(EventFlag_79);
            Savegame_EventFlagClear(EventFlag_80);

            func_8008616C(0, true, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement();
            
        case 1:
            func_80085DF0();
            break;

        case 2:
            func_8008616C(1, true, 0, 0, false);
            break;

        case 3:
            Camera_PositionSet(NULL, Q12(-56.74f), Q12(-1.7698f), Q12(-55.13f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-55.43f), Q12(-5.5f), Q12(-54.56f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            g_SysWork.player_4C.chara_0.position_18.vx = Q12(-56.34f);
            g_SysWork.player_4C.chara_0.position_18.vy = Q12(-2.276f);
            g_SysWork.player_4C.chara_0.position_18.vz = Q12(-55.1f);
            g_SysWork.player_4C.chara_0.rotation_24.vy = FP_ANGLE(0.0f);

            func_8008616C(0, false, 0, Q12(1.5f), false);
            func_80085EB8(0, &g_SysWork.player_4C.chara_0, 87, false);

            if (g_MapEventParam->field_5 == 16)
            {
                Savegame_EventFlagSet(EventFlag_79);
            }
            else if (g_MapEventParam->field_5 == 17)
            {
                Savegame_EventFlagSet(EventFlag_80);
            }

            SysWork_StateStepIncrement();

        case 4:
            func_80085E6C(Q12(3.5f), false);

            g_SysWork.player_4C.chara_0.rotation_24.vy = 0;
            g_SysWork.player_4C.chara_0.position_18.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(-0.3f), Q12_SHIFT);
            break;

        case 5:
            g_SysWork.player_4C.chara_0.position_18.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(-0.3f), Q12_SHIFT);
            func_8008616C(2, true, 0, Q12(1.5f), false);
            break;

        default:
            sharedFunc_800D2244_0_s00(true);
            SysWork_StateSetNext(SysState_Gameplay);

            g_SysWork.player_4C.chara_0.position_18.vy = 0;
            break;
        }
}

void func_800D8CC4(void) // 0x800D8CC4
{
    func_80087360(FILE_TIM_RECEPPIC_TIM, Q12(0.0f), Q12(0.0f), 27);
}

void Event_Boiler0(void) // 0x800D8CF0
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            g_SysWork.silentYesSelection_2350_4 = 1;
            MapMsg_DisplayAndHandleSelection(true, 29, 3, -1, 0, false); // Do you want to press the switch?
            break;

        case 3:
            func_8005DC1C(Sfx_Unk1420, &QVECTOR3(20.5f, -1.2f, -17.5f), 0x80, 0);
            Savegame_EventFlagSet(EventFlag_83);
            SysWork_StateStepIncrement();
    
        case 4:
            func_80085E6C(Q12(1.0f), false);
            break;

        case 5:
            D_800DD718 += g_DeltaTime0;
            if ((D_800DD718 % Q12(0.8499f)) < Q12(0.45f))
            {
                g_WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &(SVECTOR3){});
            }

            if (D_800DD718 > Q12(3.5f))
            {
                SysWork_StateStepIncrement();
            }
            break;

        case 6:
            func_8005DC1C(Sfx_Unk1422, &QVECTOR3(18.8f, 4.0f, -17.5f), 0x80, 0);
            SysWork_StateStepIncrement();

        case 7:
            Savegame_EventFlagSet(EventFlag_73);
            func_80085E6C(Q12(1.5f), false);
            break;

        case 8:
            SysWork_NextStateStepSet(NO_VALUE);
            Savegame_EventFlagSet(EventFlag_84);
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    if (Savegame_EventFlagGet(EventFlag_73))
    {
        func_800894B8(0x70);
    }
    else if (Savegame_EventFlagGet(EventFlag_83))
    {
        func_800894B8(0x90);
    }
}

void Event_Boiler1(void) // 0x0x800D8FE0
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();
            
        case 1:
            func_80085DF0();
            break;

        case 2:
            g_SysWork.silentYesSelection_2350_4 = 1;
            MapMsg_DisplayAndHandleSelection(true, 29, 3, -1, 0, false); // Do you want to press the switch?
            break;

        case 3:
            func_8005DC1C(Sfx_Unk1420, &QVECTOR3(20.5f, -1.2f, -17.5f), 0x80, 0);
            SysWork_StateStepIncrement();

        case 4:
            func_80085E6C(Q12(0.5f), false);
            break;
        case 5:
            MapMsg_DisplayAndHandleSelection(false, 30, 0, 0, 0, false); // Nothing appears to happen.
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void Event_Boiler2(void) // 0x800D9148
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            sharedFunc_800D20E4_0_s00();
            SysWork_StateStepIncrement();

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(false, 31, 0, 0, 0, false); // The boiler is working.
            break;

        default:
            sharedFunc_800D2244_0_s00(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }

    func_800894B8(0x60); // Hex?
}

void func_800D922C(void) // 0x800D922C
{
    Event_MapTake(6, EventFlag_M1S00_PickupMap, 37);
}

void func_800D9254(void) // 0x800D9254
{
    g_BackgroundColor = 104;
    func_80087360(FILE_TIM_USCBOOK_TIM, Q12(0.0f), Q12(0.0f), 38);
}

void func_800D928C(void) // 0x800D928C
{
    sharedFunc_800D20E4_0_s00();
    sharedFunc_800D2244_0_s00(false);
    SysWork_StateSetNext(SysState_Gameplay);
}

void Map_WorldObjectsInit(void)
{
    D_800E1180 = 0;
    D_800E1182 = 0;

    WorldObjectPositionInit(&g_WorldObject9.pose_1C, 133.294f, -0.8614f, 19.04f, 0.0f, 162.6f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObject9.object_0, "PICT00_H");

    Math_Vector3Set(&g_WorldObject1[0].position_1C, Q12(133.63f), Q12(-0.816f), Q12(17.089f));
    WorldObject_ModelNameSet(&g_WorldObject1[0].object_0, "PAPER1_H");

    Math_Vector3Set(&g_WorldObject1[1].position_1C, Q12(133.991f), Q12(-0.8f), Q12(16.307f));
    WorldObject_ModelNameSet(&g_WorldObject1[1].object_0, "NOTE_HID");

    Math_Vector3Set(&g_WorldObject1[2].position_1C, Q12(133.6f), Q12(-1.7f), Q12(16.0f));
    WorldObject_ModelNameSet(&g_WorldObject1[2].object_0, "TINORI1_");

    Math_Vector3Set(&g_WorldObject1[3].position_1C, Q12(133.6f), Q12(-1.19f), Q12(18.2f));
    WorldObject_ModelNameSet(&g_WorldObject1[3].object_0, "TINORI2_");

    Math_Vector3Set(&g_WorldObject1[4].position_1C, Q12(134.486f), Q12(-1.19f), Q12(18.2f));
    WorldObject_ModelNameSet(&g_WorldObject1[4].object_0, "TINORI3_");

    Math_Vector3Set(&g_WorldObject1[5].position_1C, Q12(134.4f), Q12(-0.91f), Q12(17.9568f));
    WorldObject_ModelNameSet(&g_WorldObject1[5].object_0, "GRID2_HI");

    Math_Vector3Set(&g_WorldObject2.position_1C, Q12(-12.2f), Q12(-1.0999f), Q12(-67.88f));
    WorldObject_ModelNameSet(&g_WorldObject2.object_0, "GOLD_HID");

    Math_Vector3Set(&g_WorldObject3.position_1C, Q12(-13.5198f), Q12(-1.0999f), Q12(-69.0999f));
    WorldObject_ModelNameSet(&g_WorldObject3.object_0, "SILVER_H");

    Math_Vector3Set(&g_WorldObject4.position_1C, Q12(-12.72f), Q12(-1.0f), Q12(-68.5999f));
    WorldObject_ModelNameSet(&g_WorldObject4.object_0, "ANA3_HID");

    Math_Vector3Set(&g_WorldObject5.position_1C, Q12(-12.7898f), Q12(-1.0f), Q12(-69.6199f));
    WorldObject_ModelNameSet(&g_WorldObject5.object_0, "ANA2_HID");

    Math_Vector3Set(&g_WorldObject6[0].position_1C, Q12(20.4568f), Q12(-0.8345f), Q12(-17.97f));
    WorldObject_ModelNameSet(&g_WorldObject6[0].object_0, "REDX_HID");

    Math_Vector3Set(&g_WorldObject6[1].position_1C, Q12(19.5799f), Q12(0.0f), Q12(-18.3f));
    WorldObject_ModelNameSet(&g_WorldObject6[1].object_0, "R_HIDE_I");

    Math_Vector3Set(&g_WorldObject0.position_1C, Q12(19.5799f), Q12(0.0f), Q12(-18.3f));
    WorldObject_ModelNameSet(&g_WorldObject0.object_0, "G_HIDE_I");

    WorldObjectPositionInit(&g_WorldObject7.pose_1C, 61.8531f, -0.805f, 140.6099f, 0.0f, 92.9f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObject7.object_0, D_800A99E4.savePadName_4);

    WorldObjectPositionInit(&g_WorldObject8.pose_1C, 96.9405f, -0.3365f, 21.0918f, 0.0f, 66.8f, 0.0f);
    WorldObject_ModelNameSet(&g_WorldObject8.object_0, "MAP_HIDE");

    func_8004EE94(InventoryItemId_NoteToSchool, 1);
    Savegame_EventFlagSet(EventFlag_147);
    if (g_SavegamePtr->gameDifficulty_260 == -1)
    {
        func_80088FF4(Chara_GreyChild, 3, 0);
        func_80088FF4(Chara_GreyChild, 9, 0);
    }
    if (g_SavegamePtr->gameDifficulty_260 == 1)
    {
        func_80088FF4(Chara_GreyChild, 10, 11);
        func_80088FF4(Chara_GreyChild, 11, 3);
        func_80088FF4(Chara_GreyChild, 12, 3);
        func_80088FF4(Chara_GreyChild, 13, 3);
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x0x800DBF08
{
    s32 i;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (!Savegame_EventFlagGet(EventFlag_226))
    {
        Savegame_EventFlagSet(EventFlag_226);
        func_8003A16C();
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (Savegame_EventFlagGet(EventFlag_71))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject2.object_0, &g_WorldObject2.position_1C, &(SVECTOR3){});
        }
        else
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject4.object_0, &g_WorldObject4.position_1C, &(SVECTOR3){});
        }

        if (Savegame_EventFlagGet(EventFlag_72))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject3.object_0, &g_WorldObject3.position_1C, &(SVECTOR3){});
        }
        else
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject5.object_0, &g_WorldObject5.position_1C, &(SVECTOR3){});
        }
        
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (!D_800E1180)
        {
            D_800E1180 = 1;
            Sd_PlaySfx(Sfx_Unk1359, 0, 232);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, -2, -1, -2))
    {
        if (D_800E1180 == 1)
        {
            D_800E1180 = 2;
            Sd_PlaySfx(Sfx_Unk1359, 0, 216);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        g_WorldGfx_ObjectAdd(&g_WorldObject7.object_0, &g_WorldObject7.pose_1C.position_0, &g_WorldObject7.pose_1C.rotation_C);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 0, 0, -1, 1) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (Savegame_EventFlagGet(EventFlag_72))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject6[1].object_0, &g_WorldObject6[1].position_1C, &(SVECTOR3){});
            func_80064F04(&QVECTOR3(20.58f, -1.14f, -17.41f), 0, 0x385);
        }
        else
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject6[0].object_0, &g_WorldObject6[0].position_1C, &(SVECTOR3){});
        }

        if (Savegame_EventFlagGet(EventFlag_73))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &(SVECTOR3){});
        }

        if (Savegame_EventFlagGet(EventFlag_72))
        {
            if (D_800E1182 == 0)
            {
                Sd_EngineCmd(Sfx_Unk1430);
            }

            if (!Savegame_EventFlagGet(EventFlag_84))
            {
                if (Savegame_EventFlagGet(EventFlag_83))
                {
                    D_800E1182 += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.15f), Q12_SHIFT);
                    if (D_800E1182 > Q12(1.0f))
                    {
                        D_800E1182 = Q12(1.0f);
                    }
                }
                else
                {
                    D_800E1182 = Q12(0.0999f);
                }
            }
            else
            {
                D_800E1182 = Q12(1.0f);
            }

            func_8005DE0C(Sfx_Unk1430, &QVECTOR3(18.8f, -1.0f, -17.5f), D_800E1182 >> 5, Q12(24.0f), 0);
        }
    }

    else if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        if (Savegame_EventFlagGet(EventFlag_84))
        {
            if (!D_800E1182)
            {
                Sd_EngineCmd(Sfx_Unk1430);
            }

            D_800E1182 = Q12(0.2f);
            func_8005DE0C(Sfx_Unk1430, &QVECTOR3(52.0f, -1.0f, -16.0f), 25, Q12(16.0f), 0);
        }
    }
    else
    {
        if (D_800E1182)
        {
            func_8004690C(Sfx_Unk1430);
        }

        D_800E1182 = 0;
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        g_WorldGfx_ObjectAdd(&g_WorldObject9.object_0, &g_WorldObject9.pose_1C.position_0, &g_WorldObject9.pose_1C.rotation_C);
        for (i = 0; i < 6; i++)
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject1[i].object_0, &g_WorldObject1[i].position_1C, &(SVECTOR3){});
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_PickupMap))
        {
            g_WorldGfx_ObjectAdd(&g_WorldObject8.object_0, &g_WorldObject8.pose_1C.position_0, &g_WorldObject8.pose_1C.rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_HandgunBullets0))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }     
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 3, -1, 3) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_HandgunBullets1))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1], &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 4, -1, 4) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_HandgunBullets2))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[2], &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_HealthDrink))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[3], &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, 2, -1, 2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S00_FirstAidKit))
        {
            g_WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectPoses[4], &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }
}

void func_800DA3FC(void) // 0x800DA3FC
{
    if (Savegame_EventFlagGet(EventFlag_M1S01_PickupSilverMedallion))
    {
        func_80088FF4(Chara_GreyChild, 0, 3);
        func_80088FF4(Chara_GreyChild, 1, 3);
    }
}
