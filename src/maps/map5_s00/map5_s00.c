#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/particle.h"
#include "maps/characters/creeper.h"
#include "maps/characters/player.h"
#include "maps/characters/hanged_scratcher.h"
#include "maps/map5/map5_s00.h"

INCLUDE_RODATA("maps/map5_s00/nonmatchings/map5_s00", D_800C9578);

INCLUDE_RODATA("maps/map5_s00/nonmatchings/map5_s00", g_MapOverlayHeader);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800CB0D8);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800CB25C);

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

#include "maps/shared/Ai_HangedScratcher_Update.h" // 0x800CFC24

#include "maps/shared/Ai_HangedScratcher_Init.h" // 0x800CFCA8

#include "maps/shared/sharedFunc_800CFF74_5_s00.h" // 0x800CFF74

#include "maps/shared/Ai_HangedScratcher_ControlUpdate.h" // 0x800D029C

#include "maps/shared/Ai_HangedScratcher_Control_16.h" // 0x800D03F8

#include "maps/shared/Ai_HangedScratcher_Control_1.h" // 0x800D041C

#include "maps/shared/Ai_HangedScratcher_Control_2.h" // 0x800D0514

#include "maps/shared/Ai_HangedScratcher_Control_3.h"

#include "maps/shared/Ai_HangedScratcher_Control_4.h"

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", Ai_HangedScratcher_Control_5);

#include "maps/shared/Ai_HangedScratcher_Control_6.h"

#include "maps/shared/Ai_HangedScratcher_Control_7.h"

#include "maps/shared/Ai_HangedScratcher_Control_8.h"

#include "maps/shared/Ai_HangedScratcher_Control_9.h"

#include "maps/shared/Ai_HangedScratcher_Control_10.h" // 0x800D1C0C

#include "maps/shared/Ai_HangedScratcher_Control_11.h" // 0x800D1CE4

#include "maps/shared/Ai_HangedScratcher_Control_12.h"

#include "maps/shared/Ai_HangedScratcher_Control_13.h"

#include "maps/shared/Ai_HangedScratcher_Control_14.h"

#include "maps/shared/Ai_HangedScratcher_Control_15.h"

#include "maps/shared/sharedFunc_800D26D8_5_s00.h" // 0x800D26D8

#include "maps/shared/sharedFunc_800D2844_5_s00.h"

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", sharedFunc_800D2C18_5_s00); // 0x800D2C18

#include "maps/shared/sharedFunc_800D3214_5_s00.h" // 0x800D3214

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", sharedFunc_800D3300_5_s00); // 0x800D3300

// TODO: Move this line into separate `Chara_Creeper` split.
#include "../src/maps/characters/creeper.c" // 0x800D387C

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D5B00);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D5CC4);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D5D90);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D5EA8);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D5EE8);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D61D4);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D62C8);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D631C);

s32 func_800D63DC(s32* screenXy) // 0x800D63DC
{
    SVECTOR vec;
    s32     p;

    vec.vx = 0;
    vec.vy = 0;
    vec.vz = 0;
    return RotTransPers(&vec, screenXy, &p, &p);
}

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D6414);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D6490);

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800D64F8

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D6508);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D6790);

void func_800D67EC(void) {}

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D67F4);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D6888);

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tUsed_the_ ~C2 Sewer_key ~C7 . ~E ",
    "\tUsed_the_ ~C2 Sewer_exit_key ~C7 . ~E ",
    "\tThere_is_a_ ~C2 Sewer_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tThere_is_a_ ~C2 Sewer_exit_key ~C7 ~N\n\tin_the_water._Take_it? ~S4 ",
    "\tGot_to_find_Cheryl. ~N\n\tNo_time_to_go_back. ~E ",
    "~H\tThere_is_a_ ~C5 Sewer_map ~N\n\t(connecting_to_resort_area) ~C7 . ~N\n\tTake_it? ~S4 "
};

void MapEvent_CommonItemTake(void) // 0x800D691C
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventParam->field_5)
    {
        case 38:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M5S00_ShotgunShells;
            break;

        case 39:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S00_HealthDrink0;
            break;

        case 40:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M5S00_HandgunBullets0;
            break;

        case 41:
            pickupType   = CommonPickupItemId_RifleShells;
            eventFlagIdx = EventFlag_M5S00_RifleShells;
            break;

        case 42:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M5S00_FirstAidKit0;
            break;

        case 43:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M5S00_FirstAidKit1;
            break;

        case 44:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M5S00_HealthDrink1;
            break;

        case 45:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M5S00_HandgunBullets1;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D69DC);

void MapEvent_SewerKeyTake(void) // 0x800D6AD4
{
    Event_ItemTake(InventoryItemId_SewerKey, DEFAULT_PICKUP_ITEM_COUNT, EventFlag_M5S00_PickupSewerKey, 17);
}

void func_800D6B00(void) // 0x800D6B00
{
    VECTOR3 vec;
    s32     i;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            D_800DAB78 = Q12(-0.5f);
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
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 5:
            g_SysWork.sysFlags_22A0 |= 1 << 0;
            func_800862F8(7, FILE_TIM_DRAINKEY_TIM, false);
            break;

        case 6:
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 7:
            SysWork_StateStepIncrement(0);

        case 8:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(1, false, 0, Q12(0.0f), false);
            break;

        case 9:
            func_800862F8(2, 0, false);
            g_SysWork.silentYesSelection_2350_4 = true;
            MapMsg_DisplayAndHandleSelection(true, 18, 10, 11, 0, false);
            break;

        case 10:
            Savegame_EventFlagSet(EventFlag_354);

            func_80086470(3u, InventoryItemId_SewerExitKey, 1, false);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-92.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(7.7f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(0.0f);

            for (i = 0; i < ARRAY_SIZE(D_800DAB7C); i++)
            {
                D_800DAB7C[i] = Chara_Spawn(Chara_HangedScratcher, i, Q12(-93.3f), Q12(7.1f), FP_ANGLE(180.0f), 18 + i);
            }

            if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
            {
                Chara_Spawn(Chara_HangedScratcher, 14, Q12(-94.3f), Q12(-5.5f), FP_ANGLE(0.0f), 7U);
            }

            g_SysWork.field_30 = 20;

            Sd_PlaySfx(Sfx_Unk1575, 0, Q8_CLAMPED(0.5f));
            SysWork_StateStepIncrement(0);

        case 11:
            func_80086F44(0, 0);
            break;

        case 12:
            func_8008605C(EventFlag_354, 13, 16, false);
            break;

        case 13:
            // Warp camera.
            Camera_PositionSet(NULL, Q12(-88.04f), Q12(-1.29f), Q12(6.26f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-91.77f), Q12(-0.89f), Q12(7.63f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            g_SysWork.pointLightIntensity_2378 = Q12(2.0f);

            SysWork_StateStepIncrement(0);

            vec = QVECTOR3(-91.3f, 0.3f, 8.5f);
            func_800D6490(&vec);

        case 14:
            if (D_800DAB78 < Q12(1.5f) && (D_800DAB78 + g_DeltaTime0) > Q12(1.5f))
            {
                func_80085EB8(0u, &g_SysWork.playerWork_4C.player_0, 114, false);
            }

            D_800DAB78 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.6f, 12);

            if (D_800DAB78 > Q12(3.55f))
            {
                SysWork_StateStepIncrement(0);
            }
            else if (D_800DAB78 > Q12(2.5f))
            {
                g_SysWork.npcs_1A0[D_800DAB7C[2]].properties_E4.dummy.properties_E8[0].val8[0] |= (1 << 7);
            }
            else if (D_800DAB78 > Q12(1.25f))
            {
                g_SysWork.npcs_1A0[D_800DAB7C[1]].properties_E4.dummy.properties_E8[0].val8[0] |= (1 << 7);
            }
            else if (D_800DAB78 > Q12(-0.1f))
            {
                g_SysWork.npcs_1A0[D_800DAB7C[0]].properties_E4.dummy.properties_E8[0].val8[0] |= (1 << 7);
            }

            func_800D6414();
            break;

        case 15:
            vcReturnPreAutoCamWork(true);
            g_SysWork.pointLightIntensity_2378 = Q12(1.0f);
            SysWork_StateStepIncrementAfterFade(0, false, 2, Q12(0.0f), false);

            g_SysWork.npcs_1A0[D_800DAB7C[0]].model_0.controlState_2     = ModelState_Uninitialized;
            g_SysWork.npcs_1A0[D_800DAB7C[0]].model_0.stateStep_3 = 17;
            g_SysWork.npcs_1A0[D_800DAB7C[0]].position_18.vx     += Q12(-0.1878f);
            g_SysWork.npcs_1A0[D_800DAB7C[0]].position_18.vz     += Q12(0.245f);
            g_SysWork.npcs_1A0[D_800DAB7C[0]].rotation_24.vy      = FP_ANGLE(112.5f);

            g_SysWork.npcs_1A0[D_800DAB7C[1]].model_0.controlState_2     = ModelState_Uninitialized;
            g_SysWork.npcs_1A0[D_800DAB7C[1]].model_0.stateStep_3 = 17;
            g_SysWork.npcs_1A0[D_800DAB7C[1]].position_18.vx     += Q12(1.8128f);
            g_SysWork.npcs_1A0[D_800DAB7C[1]].position_18.vz     += Q12(0.799f);
            g_SysWork.npcs_1A0[D_800DAB7C[1]].rotation_24.vy      = FP_ANGLE(180.0f);

            g_SysWork.npcs_1A0[D_800DAB7C[2]].model_0.controlState_2     = ModelState_Uninitialized;
            g_SysWork.npcs_1A0[D_800DAB7C[2]].model_0.stateStep_3 = 17;
            g_SysWork.npcs_1A0[D_800DAB7C[2]].position_18.vx     += Q12(0.6531f);
            g_SysWork.npcs_1A0[D_800DAB7C[2]].position_18.vz     += Q12(-1.2493f);
            g_SysWork.npcs_1A0[D_800DAB7C[2]].rotation_24.vy      = FP_ANGLE(0.0f);

            g_SysWork.playerWork_4C.player_0.position_18.vz += Q12(-1.2f);

            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case 16:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800D732C(void) // 0x800D732C
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 3)
    {
        ScreenFade_ResetTimestep();
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            // Warp player.
            Player_ControlFreeze();
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(56.789f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-2.02f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(60.02f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(-90.0f);
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(58.49f), Q12(1.18f), Q12(59.07f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(56.67f), Q12(-2.3f), Q12(59.86f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0u, &g_SysWork.playerWork_4C.player_0, 88, false);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            // Move player.
            g_SysWork.playerWork_4C.player_0.position_18.vy += Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 0.4f);

            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);

            // Move player.
            g_SysWork.playerWork_4C.player_0.position_18.vy += Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 0.4f);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(16.7f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(0.0f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(52.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(90.0f);

            vcReturnPreAutoCamWork(true);
            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(0.0f), false);
            Savegame_EventFlagSet(EventFlag_355);
            func_8003A16C();
            break;
    }
}

void func_800D75FC(void) // 0x800D75FC
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 6)
    {
        ScreenFade_ResetTimestep();
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            if (g_SysWork.sysStateStep_C[0] == 2)
            {
                g_SysWork.field_28 += g_DeltaTime1;
                if (g_SysWork.field_28 > Q12(1.0f))
                {
                    SysWork_StateStepSet(0, 3);
                }
            }
            break;

        case 3:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(56.773f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-1.444f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(60.036f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(-90.0f);
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(57.29f), Q12(-0.86f), Q12(59.36f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(55.07f), Q12(-4.0f), Q12(60.29f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 87, false);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, -0.4f, 12);
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, -0.4f, 12);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_356);
            Savegame_EventFlagClear(EventFlag_357);
            break;
    }
}

void func_800D7940(void) // 0x800D7940
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 6)
    {
        ScreenFade_ResetTimestep();
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);

            if (g_SysWork.sysStateStep_C[0] == 2)
            {
                g_SysWork.field_28 += g_DeltaTime1;
                if (g_SysWork.field_28 > Q12(1.0f))
                {
                    SysWork_StateStepSet(0, 3);
                }
            }
            break;

        case 3:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(56.769f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-2.07f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(60.012f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(-90.0f);
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(57.09f), Q12(-5.76f), Q12(60.59f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(55.96f), Q12(-2.01f), Q12(59.78f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 88, false);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.4f, 12);
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.4f, 12);
            break;

        default:
            Player_ControlUnfreeze(true);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_357);
            Savegame_EventFlagClear(EventFlag_356);
            break;
    }
}

void func_800D7C84(void) // 0x800D7C84
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 6)
    {
        ScreenFade_ResetTimestep();
        SysWork_StateStepReset();
    }

    g_SysWork.sysFlags_22A0 |= SysFlag_1;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrementAfterFade(0, true, 0, Q12(0.0f), false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 3:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-22.234f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-1.734f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(60.508f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(-90.0f);
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-20.39f), Q12(-3.84f), Q12(63.99f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-22.56f), Q12(-2.83f), Q12(60.78f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 87, false);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, -0.4f, 12);
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, -0.4f, 12);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_358);
            Savegame_EventFlagClear(EventFlag_359);
            break;
    }
}

void func_800D7F88(void) // 0x800D7F88
{
    // Skip.
    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] > 0 && g_SysWork.sysStateStep_C[0] < 6)
    {
        ScreenFade_ResetTimestep();
        SysWork_StateStepReset();
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            ScreenFade_ResetTimestep();
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, Q12(0.0f), false);
            break;

        case 3:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-22.245f);
            g_SysWork.playerWork_4C.player_0.position_18.vy = Q12(-2.439f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(60.488f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = FP_ANGLE(-90.0f);
            Game_TurnFlashlightOn();

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-21.29f), Q12(-0.04f), Q12(62.13f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-22.91f), Q12(-3.23f), Q12(60.34f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 88, false);

            SysWork_StateStepIncrementAfterFade(0, false, 0, Q12(1.5f), false);
            SysWork_StateStepIncrement(0);

        case 4:
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.37f, 12);
            SysWork_StateStepIncrementDelayed(Q12(3.8f), false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(2, true, 0, Q12(1.5f), false);
            g_SysWork.playerWork_4C.player_0.position_18.vy += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.4f, 12);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagClear(EventFlag_360);
            Savegame_EventFlagClear(EventFlag_358);
            Savegame_EventFlagSet(EventFlag_359);
            break;
    }
}

void MapEvent_MapTake(void) // 0x800D8280
{
    Event_MapTake(13, EventFlag_M5S00_PickupMap, 20);
}

void Map_WorldObjectsInit(void) // 0x800D82A8
{
    WorldObjectInit(&g_WorldObject_Map, "MAP_NEAR", 41.2f, -0.7f, -48.7f, 0.0f, -100.1f, 0.0f);

    func_800CB0D8();

    WorldObjectInit(&g_WorldObject_SavePad0, D_800A99E4.savePadName_4, 40.503f, -0.709f, -48.7925f, 0.0f, 5.7f, 0.0f);

    WorldObjectInit(&g_WorldObject_SavePad1, D_800A99E4.savePadName_4, -86.469f, -1.041f, -103.4905f, 0.0f, 206.3f, 0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        func_80088FF4(Chara_Creeper, 0, 0);
        func_80088FF4(Chara_Creeper, 1, 0);
        func_80088FF4(Chara_Creeper, 4, 0);
        func_80088FF4(Chara_Creeper, 7, 0);
        func_80088FF4(Chara_Creeper, 12, 0);
        g_SysWork.npcId_2280 = 3;
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        func_80088FF4(Chara_Creeper, 5, 12);
        func_80088FF4(Chara_Creeper, 6, 12);
        func_80088FF4(Chara_Creeper, 7, 0);
        func_80088FF4(Chara_Creeper, 8, 13);
        func_80088FF4(Chara_Creeper, 9, 13);
        g_SysWork.npcId_2280 = 4;
    }
    else
    {
        g_SysWork.npcId_2280 = 4;
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D84D8);

INCLUDE_ASM("maps/map5_s00/nonmatchings/map5_s00", func_800D8DFC);

INCLUDE_RODATA("maps/map5_s00/nonmatchings/map5_s00", D_800CB0CC);
