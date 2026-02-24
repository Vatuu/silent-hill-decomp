#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "bodyprog/item_screens.h"
#include "bodyprog/sound_system.h"
#include "main/rng.h"
#include "maps/map1/map1_s03.h"
#include "maps/particle.h"
#include "maps/characters/creeper.h"
#include "maps/characters/locker_dead_body.h"
#include "maps/characters/player.h"
#include "maps/characters/stalker.h"

#include "maps/shared/sharedFunc_800CBA4C_1_s02.h" // 0x800CBCE0

#include "maps/shared/sharedFunc_800CBC98_1_s02.h" // 0x800CBF2C

#include "maps/shared/sharedFunc_800CBD58_1_s02.h" // 0x800CBFEC

#include "maps/shared/sharedFunc_800CBDA8_1_s02.h" // 0x800CC03C

#include "maps/shared/sharedFunc_800CCE60_1_s02.h" // 0x800CD0F4

void func_800CDCE0(s32 arg0, s32 arg1, s32 arg2) // 0x800CDCE0
{
    s16 tmp0;
    s16 offsetX; // } Implied Q8.
    s16 offsetZ; // }
    s32 zOff2;
    s32 i;

    switch (D_800E3A40[arg1].idx_14)
    {
        case 0:
            sharedData_800DFB7C_0_s00[arg0].field_0.vx_0 = D_800E3A40[arg1].vx_0;
            sharedData_800DFB7C_0_s00[arg0].field_4.vz_4 = D_800E3A40[arg1].vz_4;
            break;

        case 1:
            // TODO: Not sure if this fits any RNG macro?
            tmp0 = (Rng_Rand16() % D_800E3A40[arg1].field_C) - (D_800E3A40[arg1].field_C >> 1);
            sharedData_800DFB7C_0_s00[arg0].field_0.vx_0 = D_800E3A40[arg1].vx_0 + FP_FROM((tmp0 * Math_Sin(D_800E3A40[arg1].field_A)), Q12_SHIFT);
            zOff2 = FP_FROM((tmp0 * Math_Cos(D_800E3A40[arg1].field_A)), Q12_SHIFT);
            sharedData_800DFB7C_0_s00[arg0].field_4.vz_4 = D_800E3A40[arg1].vz_4 + zOff2;
            break;

        case 2:
            for (i = 0; i < 8; i++)
            {
                offsetX = Rng_GenerateInt(-D_800E3A40[arg1].field_C, D_800E3A40[arg1].field_C - 1);
                offsetZ = Rng_GenerateInt(-D_800E3A40[arg1].field_C, D_800E3A40[arg1].field_C - 1);
                if ((SQUARE(offsetX) + SQUARE(offsetZ)) < (D_800E3A40[arg1].field_C * D_800E3A40[arg1].field_C))
                {
                    break;
                }
            }

            if (i == 8)
            {
                offsetZ = 0;
                offsetX = 0;
            }

            sharedData_800DFB7C_0_s00[arg0].field_0.vx_0 = D_800E3A40[arg1].vx_0 + offsetX;
            sharedData_800DFB7C_0_s00[arg0].field_4.vz_4 = D_800E3A40[arg1].vz_4 + offsetZ;
            break;

        case 3:
            offsetX = Rng_GenerateUInt(0, Q12_ANGLE(360.0f) - 1);
            sharedData_800DFB7C_0_s00[arg0].field_0.vx_0 = D_800E3A40[arg1].vx_0 + FP_FROM((D_800E3A40[arg1].field_C * Math_Sin(offsetX)), Q12_SHIFT);
            zOff2 = FP_FROM((D_800E3A40[arg1].field_C * Math_Cos(offsetX)), Q12_SHIFT);
            sharedData_800DFB7C_0_s00[arg0].field_4.vz_4 = D_800E3A40[arg1].vz_4 + zOff2;
            break;

        case 4:
            offsetX = Rng_AddGeneratedUInt(D_800E3A40[arg1].field_A, Q12_ANGLE(-90.0f), Q12_ANGLE(90.0f) - 1);
            sharedData_800DFB7C_0_s00[arg0].field_0.vx_0 = D_800E3A40[arg1].vx_0 + FP_FROM((D_800E3A40[arg1].field_C * Math_Sin(offsetX)), Q12_SHIFT);
            zOff2 = FP_FROM((D_800E3A40[arg1].field_C * Math_Cos(offsetX)), Q12_SHIFT);
            sharedData_800DFB7C_0_s00[arg0].field_4.vz_4 = D_800E3A40[arg1].vz_4 + zOff2;
            break;
    }

    sharedData_800DFB7C_0_s00[arg0].vy_8 = D_800E3A40[arg1].field_8;

    if (arg2 == 0)
    {
        sharedData_800DFB7C_0_s00[arg0].field_C.s_0.field_0 = Rng_GenerateInt(0, D_800E3A40[arg1].field_10 - 1);
    }
    else
    {
        sharedData_800DFB7C_0_s00[arg0].field_C.s_0.field_0 = sharedData_800DFB7C_0_s00[arg0].field_C.field_0 - D_800E3A40[arg1].field_10;
    }

    sharedData_800DFB7C_0_s00[arg0].field_C.s_1.field_2  = Rng_GenerateUInt(0, 3);
    sharedData_800DFB7C_0_s00[arg0].field_C.s_1.field_3  = Rng_GenerateUInt(96, 159);
    sharedData_800DFB7C_0_s00[arg0].field_10.s_2.field_0 = arg1;
}

void func_800CE0CC(s32 arg0) // 0x800CE0CC
{
    s32 idx;
    s32 i;

    for (i = 0; i < D_800E3A40[arg0].field_12; i++)
    {
        idx = func_8005E7E0(28);
        if (idx == NO_VALUE)
        {
            break;
        }

        func_800CDCE0(idx, arg0, 0);
    }
}

bool func_800CE164(POLY_FT4** poly, s32 idx) // 0x800CE164
{
    typedef struct
    {
        s_func_8005E89C field_0;
        SVECTOR         field_12C;
        DVECTOR         field_134;
        s32             field_138;
    } s_ScratchData;

    s_ScratchData* scratch = PSX_SCRATCH;
    s32            idx2;
    s32            var_lo;
    s32            var_a2;
    s32            var_a1;
    s32            rgbColor;

    sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 += g_DeltaTime;

    idx2 = sharedData_800DFB7C_0_s00[idx].field_10.s_2.field_0;
    if ((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0 > D_800E3A40[idx2].field_10)
    {
        func_800CDCE0(idx, idx2, 1);
        return false;
    }

    Math_SetSVectorFastSum(&scratch->field_12C,
                           (sharedData_800DFB7C_0_s00[idx].field_0.vx_0 >> 4) - (u16)scratch->field_0.field_0.vx,
                           ((s32)sharedData_800DFB7C_0_s00[idx].vy_8 >> 4) - scratch->field_0.field_0.vy,
                           (sharedData_800DFB7C_0_s00[idx].field_4.vz_4 >> 4) - scratch->field_0.field_0.vz);

    gte_ldv0(&scratch->field_12C);
    gte_rtps();
    gte_stsxy(&scratch->field_134.vx);
    gte_stsz(&scratch->field_138);

    var_lo = FP_TO((u16)sharedData_800DFB7C_0_s00[idx].field_C.s_0.field_0, Q12_SHIFT) / D_800E3A40[idx2].field_10;

    setPolyFT4(*poly);

    var_a2 = (FP_FROM(Q12_MULT_PRECISE(D_800E3A40[idx2].field_E * sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_3, Math_Sin(var_lo >> 2)), Q12_SHIFT) * scratch->field_0.field_2C) / scratch->field_138;
    var_a1 = (var_a2 * (0x800 - ABS(scratch->field_0.field_30.vx))) >> 10;

    setXY0Fast(*poly, (u16)scratch->field_134.vx - var_a2, scratch->field_134.vy - var_a1);
    setXY1Fast(*poly, (u16)scratch->field_134.vx + var_a2, scratch->field_134.vy - var_a1);
    setXY2Fast(*poly, (u16)scratch->field_134.vx - var_a2, scratch->field_134.vy);
    setXY3Fast(*poly, (u16)scratch->field_134.vx + var_a2, scratch->field_134.vy);

    *(u32*)&(*poly)->u0 = ((sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 13) + 0xE0000);
    *(u32*)&(*poly)->u1 = ((sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 13) + 0x2D003F);
    *(u16*)&(*poly)->u2 = ((sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 13) | 0x1F00);
    *(u16*)&(*poly)->u3 = ((sharedData_800DFB7C_0_s00[idx].field_C.s_1.field_2 << 13) | 0x1F3F);

    setSemiTrans(*poly, true);

    if (var_lo < 0x800)
    {
        rgbColor = Q12_MULT_PRECISE((var_lo * 2), 0x80);
    }
    else
    {
        rgbColor = 0x80 - Q12_MULT_PRECISE(((var_lo - 0x800) * 2), 0x80);
    }

    rgbColor = (rgbColor * func_80055D78(sharedData_800DFB7C_0_s00[idx].field_0.vx_0, sharedData_800DFB7C_0_s00[idx].vy_8, sharedData_800DFB7C_0_s00[idx].field_4.vz_4)) >> 7;

    setRGB0Fast(*poly, rgbColor, rgbColor, rgbColor);

    addPrim(&g_OrderingTable0[g_ActiveBufferIdx].org[(scratch->field_138 + 256) >> 3], *poly);

    *poly += 1;

    return true;
}

#include "maps/shared/sharedFunc_800CE5D4_1_s03.h" // 0x800CE5D4

#include "maps/shared/sharedFunc_800CE688_1_s03.h" // 0x800CE688

#include "../src/maps/particle.c"

#include "../src/maps/characters/player.c"

// TODO: Move this line into separate `Chara_Stalker` split.
#include "../src/maps/characters/stalker.c" // 0x800D2DC0

// TODO: Move this line into separate `Chara_Creeper` split.
#include "../src/maps/characters/creeper.c" // 0x800D8010

void Ai_LockerDeadBody_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords) // 0x800DA284
{
    s_AnimInfo* animInfo;

    if (chara->model_0.controlState_2 == ModelState_Uninitialized)
    {
        chara->model_0.anim_4.alpha_A = Q12(0.0f);
        Character_AnimSet(chara, ANIM_STATUS(LockerDeadBodyAnim_2, true), 0);
        chara->model_0.controlState_2++;
        chara->position_18.vy = Q12(0.0f);
    }

    if (!Savegame_EventFlagGet(EventFlag_105))
    {
        chara->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
        chara->field_E1_0              = 0;
        return;
    }

    chara->model_0.anim_4.flags_2 |= AnimFlag_Visible;

    if (!Savegame_EventFlagGet(EventFlag_106))
    {
        if (chara->model_0.anim_4.status_0 == ANIM_STATUS(LockerDeadBodyAnim_2, true))
        {
            chara->model_0.anim_4.status_0 = ANIM_STATUS(LockerDeadBodyAnim_1, true);
        }

        chara->field_E1_0 = 0;
    }
    else
    {
        Character_AnimSet(chara, ANIM_STATUS(LockerDeadBodyAnim_3, true), 16);
        chara->field_E1_0 = 3;
    }

    Math_MatrixTransform(&chara->position_18, &chara->rotation_24, coords);

    animInfo = &LOCKER_DEAD_BODY_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);

    chara->field_C8.field_0   = Q12(-0.3f);
    chara->field_D8.offsetX_4 = Q12(0.06f);
    chara->field_D8.offsetZ_6 = Q12(0.93f);
    chara->field_C8.field_2   = Q12(0.0f);
    chara->field_C8.field_4   = Q12(0.0f);
    chara->field_C8.field_6   = Q12(0.0f);
    chara->field_D8.offsetX_0 = Q12(0.0f);
    chara->field_D8.offsetZ_2 = Q12(0.0f);
    chara->field_D4.field_2   = Q12(0.0f);
    chara->field_D4.radius_0   = Q12(0.33f);

    func_8005C814(&chara->field_D8, chara);
}

#include "maps/shared/sharedFunc_800D929C_0_s00.h" // 0x800DA424

#include "maps/shared/Map_RoomIdxGet.h" // 0x800DA434

#include "maps/shared/Map_RoomBgmInit_1_s02.h" // 0x800DA4D4

void func_800DA630(void) {}

#include "maps/shared/MapEvent_DoorJammed.h" // 0x800DA638

#include "maps/shared/MapEvent_DoorLocked.h" // 0x800DA6CC

#include "maps/shared/MapEvent_DoorUnlocked.h" // 0x800DA760

void func_800DA7F4(void) // 0x800DA7F4
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_LibraryReserveKey, 1);
    Map_MessageWithSfx(37, Sfx_UseKey, &sfxPos); // "Used the Library reverse key."
    Savegame_MapMarkingSet(MapMarkFlag_AltSchool2F_LibraryReserveArrows);
}

void func_800DA8B0(void) // 0x800DA8B0
{
    VECTOR3 sfxPos = { MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionX_0, Q12(-1.2f), MAP_POINTS[g_MapEventData->pointOfInterestIdx_5].positionZ_8 };

    Player_ItemRemove(InventoryItemId_ClassroomKey, 1);
    Map_MessageWithSfx(38, Sfx_UseKey, &sfxPos); // "Used classroom key."
}

const char* MAP_MESSAGES[] = {
    #include "maps/shared/mapMsg_common.h"
    "\tWhat's_this? ~E ",
    "\t[The_Monster_Lurks] ~N\n\tis_the_book's_title. ~E ",
    "~C3\tChapter_3: ~N\n\t\t__[Manifestation_of_Delusions] ",
    "~C3\t...Poltergeists_are_among_these. ~N\n\t\tNegative_emotions,_like_fear, ",
    "~C3\tworry_or_stress_manifest ~N\n\t\tinto_external_energy_with ~N\n\t\tphysical_effects. ",
    "~C3\tNightmares_have,_in_some_cases, ~N\n\t\tbeen_shown_to_trigger_them. ",
    "~C3\tHowever,_such_phenomena_do_not ~N\n\t\tappear_to_happen_to_just_anyone. ",
    "~C3\tAlthough_it's_not_clear_why, ~N\n\t\tadolescents,_especially_girls, ~N\n\t\tare_prone_to_such_occurrences. ~E ",
    "~C3\tHearing_this,_the_hunter ~N\n\t\tarmed_with_bow_and_arrow_said, ~N\n\t\t[I_will_kill_the_lizard.] ",
    "~C3\tBut_upon_meeting_his_opponent, ~N\n\t\the_held_back,_taunting, ~N\n\t\t[Who's_afraid_of_a_reptile?] ",
    "~C3\tAt_this,_the_furious_lizard ~N\n\t\thissed,_[I'll_swallow_you_up ~N\n\t\tin_a_single_bite!] ",
    "~C3\tThen_the_huge_creature ~N\n\t\tattacked,_jaws_opened_wide. ",
    "~C3\tThis_was_what_the_man_wanted. ~N\n\t\tCalmly_drawing_his_bow,_he_shot ~N\n\t\tinto_the_lizard's_gaping_mouth. ",
    "~C3\tEffortlessly,_the_arrow_flew, ~N\n\t\tpiercing_the_defenseless_maw, ",
    "~C3\tand_the_lizard_fell_down_dead. ~E ",
    "\tThis_is_from_an_old_fairy_tale. ~N\n\tI_remember_reading_it_as_a_kid. ~E ",
    "\tThere's_a_drainage_valve. ~N\n\tNothing_unusual. ~E ",
    "\tThere's_a_hanging_key. ~N\n\tIt's_just_out_of_reach. ~E ",
    "\tThe_key_went_down_the_drain. ~E ",
    "\tThe_ball_is_stuffed ~N\n\tinside_the_pipe. ~E ",
    "\tNothing_special. ~E ",
    "\tUsed_the_ ~C2 Rubber_ball ~C7 . ~E ",
    "\tUsed_the_ ~C2 Library_reserve_key ~C7 . ~E ",
    "\tUsed_the_ ~C2 Classroom_key ~C7 . ~E ",
    "\tNo_useful_books. ~E ",
    "\tThere_is_a_drainage_valve. ~N\n\tDo_you_want_to_open_it? ~S4 ",
    "\tIt_drains_into_the_wrong_hole. ~N\n\tMaybe_I_could_plug ~N\n\tthat_up_somehow. ~E ",
    "\tNothing_useful_in_the_locker. ~E ",
    "\tNothing_inside. ~E ",
    "\tThere_is_a_ ~C2 Library_reserve_key ~C7 . ~N\n\tTake_it? ~S4 ",
    "\tA_body_is_slumped_over. ~E ",
    "~J0(1.0)\tWhat? ~E ",
    "~J0(2.5)\tThat_light!? ~E "
};

void func_800DA950(void) // 0x800DA950
{
    u32 pickupType;
    s32 eventFlagIdx;

    pickupType   = CommonPickupItemId_FirstAidKit;
    eventFlagIdx = 0;

    switch (g_MapEventData->pointOfInterestIdx_5)
    {
        case 84:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M1S03_ShotgunShells0;
            break;

        case 85:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S03_HandgunBullets0;
            break;

        case 86:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M1S03_HealthDrink0;
            break;

        case 87:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S03_HandgunBullets1;
            break;

        case 88:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S03_HandgunBullets2;
            break;

        case 89:
            pickupType   = CommonPickupItemId_ShotgunShells;
            eventFlagIdx = EventFlag_M1S03_ShotgunShells1;
            break;

        case 90:
            pickupType   = CommonPickupItemId_HandgunBullets;
            eventFlagIdx = EventFlag_M1S03_HandgunBullets3;
            break;

        case 91:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M1S03_HealthDrink1;
            break;

        case 92:
            pickupType   = CommonPickupItemId_HealthDrink;
            eventFlagIdx = EventFlag_M1S03_HealthDrink2;
            break;

        case 93:
            pickupType   = CommonPickupItemId_FirstAidKit;
            eventFlagIdx = EventFlag_M1S03_FirstAidKit;
            break;
    }

    Event_CommonItemTake(pickupType, eventFlagIdx);
}

void func_800DAA28(void) // 0x800DAA28
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
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            if (g_MapEventData->pointOfInterestIdx_5 == 19 || g_MapEventData->pointOfInterestIdx_5 == 20)
            {
                if (g_MapEventData->activationType_4_4 == TriggerActivationType_Item)
                {
                    Savegame_EventFlagSet(EventFlag_M1S02_UsedRubberBall);
                    MapMsg_DisplayAndHandleSelection(false, 36, false, false, 0, false); // "Used rubber ball."
                }
                else
                {
                    MapMsg_DisplayAndHandleSelection(false, 35, false, false, 0, false); // "Nothing special."
                }
            }
            else if (g_MapEventData->pointOfInterestIdx_5 == 17 || g_MapEventData->pointOfInterestIdx_5 == 18)
            {
                if (Savegame_EventFlagGet(EventFlag_M1S02_PickupClassroomKey))
                {
                    MapMsg_DisplayAndHandleSelection(false, 35, false, false, 0, false); // "Nothing special."
                }
                else
                {

                    MapMsg_DisplayAndHandleSelection(false, 33, false, false, 0, false); // "There's a hanging key."
                }
            }
            break;

        case 4:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800DABC4(void) // 0x800DABC4
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            if (g_MapEventData->pointOfInterestIdx_5 == 17 || g_MapEventData->pointOfInterestIdx_5 == 18)
            {
                if (Savegame_EventFlagGet(EventFlag_M1S03_KeyDownTheDrain))
                {
                    func_800862F8(false, FILE_TIM_HOLEKEY1_TIM, false);
                }
                else
                {
                    func_800862F8(false, FILE_TIM_HOLEKEY0_TIM, false);
                    Savegame_EventFlagSet(EventFlag_112);
                }
            }
            else if (g_MapEventData->pointOfInterestIdx_5 == 19 || g_MapEventData->pointOfInterestIdx_5 == 20)
            {
                if (g_MapEventData->activationType_4_4 == TriggerActivationType_Item || Savegame_EventFlagGet(EventFlag_M1S02_UsedRubberBall))
                {
                    func_800862F8(false, FILE_TIM_BALLHOLE_TIM, false);
                }
                else
                {
                    func_800862F8(false, FILE_TIM_BALLHOL1_TIM, false);
                }
            }

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(false, true, 0, 0, false);
            SysWork_StateStepIncrement(0);

        case 4:
            func_800862F8(true, 0, false);
            break;

        case 5:
            SysWork_StateStepIncrementAfterFade(1, true, 0, 0, false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 7:
            func_800862F8(2, 0, false);
            if (g_MapEventData->pointOfInterestIdx_5 == 19 || g_MapEventData->pointOfInterestIdx_5 == 20)
            {
                if (g_MapEventData->activationType_4_4 == TriggerActivationType_Item)
                {
                    Savegame_EventFlagSet(EventFlag_M1S02_UsedRubberBall);
                    MapMsg_DisplayAndHandleSelection(false, 36, false, false, 0, false);
                }
                else
                {
                    if (Savegame_EventFlagGet(EventFlag_M1S02_UsedRubberBall))
                    {
                        MapMsg_DisplayAndHandleSelection(false, 34, false, false, 0, false); // "The ball is stuffed inside the pipe."
                    }
                    else
                    {
                        MapMsg_DisplayAndHandleSelection(false, 35, false, false, 0, false); // "Nothing special."
                    }
                }
            }
            else
            {
                if (Savegame_EventFlagGet(EventFlag_M1S02_PickupClassroomKey))
                {
                    MapMsg_DisplayAndHandleSelection(false, 35, false, false, 0, false); // "Nothing special."
                }
                else
                {
                    if (!Savegame_EventFlagGet(EventFlag_M1S03_KeyDownTheDrain))
                    {
                        MapMsg_DisplayAndHandleSelection(false, 32, false, false, 0, false); // "There's a hanging key."
                    }
                    else
                    {
                        MapMsg_DisplayAndHandleSelection(false, 33, false, false, 0, false); // "The key went down the drain."
                    }
                }
            }
            break;

        case 8:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 9:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 10:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

const VECTOR3 D_800CBAA4 = { 0xFFFF5800, 0xFFFFF800, 0xFFFF319A };

const VECTOR3 D_800CBAB0 = { 0xFFFF5CCD, 0x00000000, 0xFFFF2A67 };

void func_800DAF18(void) // 0x800DAF18
{
    VECTOR3       sp28;
    VECTOR3       sp38;
    VECTOR3       sp48;
    MATRIX        sp58;
    VECTOR        sp78;
    s32           temp_s0_2;
    s32           temp_s2;
    s32           temp_v1_9;
    s32           i;
    s32           var_v0;
    s32           var_v0_2;
    s32           var_v1;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800E20FC = 0;
            D_800E2100 = 0;

            Savegame_MapMarkingSet(MapMarkFlag_AltSchoolRF_ValveSign);

            D_800E2101                  = 0;
            g_SysWork.field_28          = 0;
            g_SysWork.sysStateStep_C[1] = 0;
            g_SysWork.timer_2C          = 0;
            g_SysWork.sysStateStep_C[2] = 0;
            g_SysWork.sysStateStep_C[0]++;

        case 1:
            func_80085DF0();
            break;

        case 2:
            MapMsg_DisplayAndHandleSelection(true, 0x28, 4, 3, 0, false);
            break;

        case 3:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;

        case 4:
            SysWork_StateStepIncrementAfterFade(0, true, 2, 0, false);

            sharedData_800E30C8_1_s02.field_0[0]  = -0xA333;
            sharedData_800E30C8_1_s02.field_10[0] = -0x599;
            sharedData_800E30C8_1_s02.field_18[0] = -0xD599;
            sharedData_800E30C8_1_s02.field_28[0] = 0x733;
            sharedData_800E30C8_1_s02.field_30[0] = 1;
            sharedData_800E30C8_1_s02.field_3C[0] = 0x2E1;
            sharedData_800E30C8_1_s02.field_44[0] = 0x400;
            sharedData_800E30C8_1_s02.field_4C[0] = 0x1800;
            sharedData_800E30C8_1_s02.field_5C[0] = 0x2E1;
            sharedData_800E30C8_1_s02.field_64[0] = 0x400;
            sharedData_800E30C8_1_s02.field_6c[0] = 0;

            sharedData_800E30C8_1_s02.field_0[1]  = -0xA400;
            sharedData_800E30C8_1_s02.field_10[1] = 0x199;
            sharedData_800E30C8_1_s02.field_18[1] = -0xCFAE;
            sharedData_800E30C8_1_s02.field_28[1] = 0x4EB8;
            sharedData_800E30C8_1_s02.field_30[1] = 0;
            sharedData_800E30C8_1_s02.field_34[1] = 0x800;
            sharedData_800E30C8_1_s02.field_3C[1] = 0x4CC;
            sharedData_800E30C8_1_s02.field_44[1] = 0x800;
            sharedData_800E30C8_1_s02.field_4C[1] = 0x999;
            sharedData_800E30C8_1_s02.field_5C[1] = 0x4CC;
            sharedData_800E30C8_1_s02.field_64[1] = 0x800;
            sharedData_800E30C8_1_s02.field_6c[1] = 0xCCC;

            D_800E3A40[0].vx_0     = -0xA333;
            D_800E3A40[0].field_8  = 0x1EB;
            D_800E3A40[0].field_C  = 0x147;
            D_800E3A40[0].vz_4     = -0xD599;
            D_800E3A40[0].idx_14   = 2;
            D_800E3A40[0].field_12 = 0x28;
            D_800E3A40[0].field_E  = 0x400;
            D_800E3A40[0].field_10 = 0x4CC;

            D_800E3A40[1].vx_0     = -0xA400;
            D_800E3A40[1].vz_4     = -0x11B85;
            D_800E3A40[1].field_C  = 0xCC;
            D_800E3A40[1].field_12 = 0x28;

            if (Savegame_EventFlagGet(EventFlag_M1S02_UsedRubberBall))
            {
                sharedData_800E30C8_1_s02.field_0[2]  = -0xA199;
                sharedData_800E30C8_1_s02.field_10[2] = 0x214;
                sharedData_800E30C8_1_s02.field_28[2] = 0x6D1E;
                sharedData_800E30C8_1_s02.field_34[2] = 0xC00;
                sharedData_800E30C8_1_s02.field_74    = 0x96;
                sharedData_800E30C8_1_s02.field_18[2] = -0x11C00;
                sharedData_800E30C8_1_s02.field_30[2] = 0;
                sharedData_800E30C8_1_s02.field_3C[2] = 0x4CC;
                sharedData_800E30C8_1_s02.field_44[2] = 0x800;
                sharedData_800E30C8_1_s02.field_4C[2] = 0x999;
                sharedData_800E30C8_1_s02.field_5C[2] = 0x4CC;
                sharedData_800E30C8_1_s02.field_64[2] = 0x800;
                sharedData_800E30C8_1_s02.field_6c[2] = 0xCCC;
                sharedData_800E30C8_1_s02.field_78    = 3;

                D_800E3A40[1].field_8  = 0x385;
                D_800E3A40[1].idx_14   = 4;
                D_800E3A40[1].field_A  = 0;
                D_800E3A40[1].field_E  = 0x333;
                D_800E3A40[1].field_10 = 0x599;
                D_800E3A40[2].field_C  = 0xF5;
                D_800E3A40[2].vx_0     = -0x10DC2;
                D_800E3A40[2].vz_4     = -0x11C00;
                D_800E3A40[2].field_8  = 0x333;
                D_800E3A40[2].idx_14   = 3;
                D_800E3A40[2].field_12 = 0x3C;
                D_800E3A40[2].field_E  = 0x333;
                D_800E3A40[2].field_10 = 0x333;
            }
            else
            {
                sharedData_800E30C8_1_s02.field_74 = 0x50;
                sharedData_800E30C8_1_s02.field_78 = 2;
                D_800E3A40[1].field_8              = 0x333;
                D_800E3A40[1].idx_14               = 3;
                D_800E3A40[1].field_E              = 0x266;
                D_800E3A40[1].field_10             = 0x333;
            }

            sharedData_800E30C8_1_s02.field_28[sharedData_800E30C8_1_s02.field_78] = 0x800;
            sharedData_800E30C8_1_s02.field_10[sharedData_800E30C8_1_s02.field_78] = 0x28F;
            sharedData_800E30C8_1_s02.field_3C[sharedData_800E30C8_1_s02.field_78] = 0x199;
            sharedData_800E30C8_1_s02.field_5C[sharedData_800E30C8_1_s02.field_78] = 0x1EB;
            sharedData_800E30C8_1_s02.field_64[sharedData_800E30C8_1_s02.field_78] = 0x4CC;

            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = -0xB733;
            g_SysWork.playerWork_4C.player_0.position_18.vz = -0xCF33;
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = 0x400;

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Camera_PositionSet(NULL, -0xC614, -0x1333, -0xE11E, 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, -0x93D7, -0xC28, -0xBA14, 0, 0, 0, 0, true);

            g_SysWork.field_28          = 0;
            g_SysWork.sysStateStep_C[1] = 0;
            g_SysWork.timer_2C          = 0;
            g_SysWork.sysStateStep_C[2] = 0;
            g_SysWork.sysStateStep_C[0]++;

        case 5:
            SysWork_StateStepIncrementDelayed(Q12(1.5f), false);
            break;

        case 6:
            D_800E20FE                  = 0;
            g_SysWork.field_28          = 0;
            g_SysWork.sysStateStep_C[1] = 0;
            g_SysWork.timer_2C          = 0;
            g_SysWork.sysStateStep_C[2] = 0;
            g_SysWork.sysStateStep_C[0]++;

        case 7:
            D_800E20FE++;
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 107);
            break;

        case 8:
            sharedFunc_800CBC98_1_s02();
            func_800CE0CC(0);
            func_800CE0CC(1);

            if (Savegame_EventFlagGet(EventFlag_M1S02_UsedRubberBall))
            {
                func_800CE0CC(2);
            }

            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, AnimFlag_Visible);

            func_8008D438();
            Camera_PositionSet(NULL, D_800E1F88[0].vx, D_800E1F88[0].vy, D_800E1F88[0].vz, 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, D_800E1FC4[0].vx, D_800E1FC4[0].vy, D_800E1FC4[0].vz, 0, 0, 0, 0, true);

            D_800E20FA                  = 0;
            g_SysWork.field_28          = 0;
            g_SysWork.sysStateStep_C[1] = 0;
            g_SysWork.timer_2C          = 0;
            g_SysWork.sysStateStep_C[2] = 0;
            g_SysWork.sysStateStep_C[0]++;

        case 9:
            D_800E20FA += g_DeltaTime;

            for (i = 1; i < 6; i++)
            {
                if (D_800E20FA < D_800E1F7C[i])
                {
                    break;
                }
            }

            if (i == 6 || (!Savegame_EventFlagGet(EventFlag_M1S02_UsedRubberBall) && i > 3))
            {
                g_SysWork.field_28          = 0;
                g_SysWork.sysStateStep_C[1] = 0;
                g_SysWork.timer_2C          = 0;
                g_SysWork.sysStateStep_C[2] = 0;
                g_SysWork.sysStateStep_C[0]++;
            }
            else
            {
                var_v1 = i >> 1;

                if (Savegame_EventFlagGet(EventFlag_M1S02_UsedRubberBall))
                {
                    var_v1 += 2;
                }

                if (i & 1)
                {
                    sp28.vx = D_800E1F88[var_v1].vx;
                    sp28.vy = D_800E1F88[var_v1].vy;
                    sp28.vz = D_800E1F88[var_v1].vz;

                    sp38.vx = D_800E1FC4[var_v1].vx;
                    sp38.vy = D_800E1FC4[var_v1].vy;
                    sp38.vz = D_800E1FC4[var_v1].vz;
                }
                else
                {
                    sp28.vx = D_800E1F88[var_v1 - 1].vx + (((D_800E1F88[var_v1].vx - D_800E1F88[var_v1 - 1].vx) * (D_800E20FA - D_800E1F7C[i - 1])) / (D_800E1F7C[i] - D_800E1F7C[i - 1]));
                    sp28.vy = D_800E1F88[var_v1 - 1].vy + (((D_800E1F88[var_v1].vy - D_800E1F88[var_v1 - 1].vy) * (D_800E20FA - D_800E1F7C[i - 1])) / (D_800E1F7C[i] - D_800E1F7C[i - 1]));
                    sp28.vz = D_800E1F88[var_v1 - 1].vz + (((D_800E1F88[var_v1].vz - D_800E1F88[var_v1 - 1].vz) * (D_800E20FA - D_800E1F7C[i - 1])) / (D_800E1F7C[i] - D_800E1F7C[i - 1]));

                    sp38.vx = D_800E1FC4[var_v1 - 1].vx + (((D_800E1FC4[var_v1].vx - D_800E1FC4[var_v1 - 1].vx) * (D_800E20FA - D_800E1F7C[i - 1])) / (D_800E1F7C[i] - D_800E1F7C[i - 1]));
                    sp38.vy = D_800E1FC4[var_v1 - 1].vy + (((D_800E1FC4[var_v1].vy - D_800E1FC4[var_v1 - 1].vy) * (D_800E20FA - D_800E1F7C[i - 1])) / (D_800E1F7C[i] - D_800E1F7C[i - 1]));
                    sp38.vz = D_800E1FC4[var_v1 - 1].vz + (((D_800E1FC4[var_v1].vz - D_800E1FC4[var_v1 - 1].vz) * (D_800E20FA - D_800E1F7C[i - 1])) / (D_800E1F7C[i] - D_800E1F7C[i - 1]));
                }

                // Warp camera.
                Camera_PositionSet(&sp28, 0, 0, 0, 0, 0, 0, 0, true);
                Camera_LookAtSet(&sp38, 0, 0, 0, 0, 0, 0, 0, true);

                g_SysWork.field_236C               = NULL;
                g_SysWork.pointLightRot_2370.vx = -ratan2(sp38.vy - sp28.vy,
                                                             SquareRoot0(SQUARE((sp38.vx - sp28.vx) >> 6) + SQUARE((sp38.vz - sp28.vz) >> 6)) << 6);

                g_SysWork.pointLightRot_2370.vy = ratan2(sp38.vx - sp28.vx, sp38.vz - sp28.vz);
                g_SysWork.pointLightRot_2370.vz = 0;
                g_SysWork.field_235C               = NULL;
                g_SysWork.pointLightPosition_2360.vx = sp28.vx;
                g_SysWork.pointLightPosition_2360.vy = MAX(-0x1800, sp28.vy);
                g_SysWork.pointLightPosition_2360.vz = sp28.vz;
            }
            break;

        case 10:
            if (Savegame_EventFlagGet(EventFlag_M1S02_UsedRubberBall))
            {
                g_SysWork.field_28          = 0;
                g_SysWork.sysStateStep_C[1] = 0;
                g_SysWork.timer_2C          = 0;
                g_SysWork.sysStateStep_C[2] = 0;
                g_SysWork.sysStateStep_C[0]++;
            }
            else
            {
                MapMsg_DisplayAndHandleSelection(false, 0x29, false, false, 0, false);
            }
            break;

        case 11:
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, AnimFlag_Visible);

            func_8008D448();
            Game_FlashlightAttributesFix();
            Camera_PositionSet(NULL, -0xC614, -0x1333, -0xE11E, 0, 0, 0, 0, true);
            Camera_LookAtSet(NULL, -0x93D7, -0xC28, -0xBA14, 0, 0, 0, 0, true);
            sharedFunc_800CBD58_1_s02();

            if (Savegame_EventFlagGet(EventFlag_M1S02_UsedRubberBall))
            {
                Savegame_EventFlagSet(EventFlag_M1S03_KeyDownTheDrain);
            }

            D_800E2101                  = 0;
            D_800E20FE                  = 0;
            g_SysWork.field_28          = 0;
            g_SysWork.sysStateStep_C[1] = 0;
            g_SysWork.timer_2C          = 0;
            g_SysWork.sysStateStep_C[2] = 0;
            g_SysWork.sysStateStep_C[0]++;

        case 12:
            D_800E20FE++;
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 108);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            vcReturnPreAutoCamWork(true);
            sharedFunc_800D2EF4_0_s00();
            break;
    }

    if (g_SysWork.sysStateStep_C[0] == 7 || g_SysWork.sysStateStep_C[0] == 12)
    {
        Vw_CoordHierarchyMatrixCompute(&g_SysWork.playerBoneCoords_890[10], &sp58);

        gte_SetRotMatrix(&sp58);
        gte_SetTransMatrix(&sp58);
        gte_ldv0(&D_800E1F74);
        gte_rt();
        gte_stlvnl(&sp78);

        temp_s2 = ratan2((sp78.vy * 0x10) + 0xB33, (sp78.vz * 0x10) + 0xCEB8);
        if (D_800E20FE > 2)
        {
            var_v0 = FP_FROM(g_SysWork.playerWork_4C.player_0.model_0.anim_4.time_4, Q12_SHIFT) - Player_AnimGetSomething();
        }
        else
        {
            var_v0 = 0;
        }

        if (var_v0 >= 6 && var_v0 < 0x25)
        {
            if ((g_SysWork.sysStateStep_C[0] == 7 && func_8005BF38(D_800E20F8 - temp_s2) < 0) ||
                (g_SysWork.sysStateStep_C[0] == 12 && func_8005BF38(D_800E20F8 - temp_s2) > 0))
            {
                if (D_800E2101 == 0)
                {
                    func_8005DC1C(0x5B7, &D_800CBAA4, 0x80, 0);
                    D_800E2101++;
                }
                else if (!(D_800E2101 & 1) && D_800E2101 < 8)
                {
                    func_8005DC1C(0x5B6, &D_800CBAA4, 0x80, 0);

                    if (D_800E2101 == 2)
                    {
                        if (g_SysWork.sysStateStep_C[0] == 0xC)
                        {
                            Sd_SfxStop(0x5B9);
                            D_800E2100 = 0;
                        }
                        else if (g_SysWork.sysStateStep_C[0] == 7)
                        {
                            SD_Call(0x5B9);
                            D_800E2100 = 1;
                        }
                    }

                    D_800E2101++;
                }

                g_WorldObject5.rotation_28.vx += func_8005BF38(D_800E20F8 - temp_s2);

                if (D_800E2100 != 0)
                {
                    D_800E20FC -= func_8005BF38(D_800E20F8 - temp_s2);

                    if (D_800E20FC < 0)
                    {
                        D_800E20FC = 0;
                    }

                    if (D_800E20FC > 0xFF0)
                    {
                        D_800E20FC = 0xFF0;
                    }
                }
            }
            else if (D_800E2101 & 1)
            {
                D_800E2101++;
            }
        }

        D_800E20F8 = temp_s2;
    }

    if (D_800E2100 != 0)
    {
        temp_s0_2 = Sound_StereoBalanceGet(&D_800CBAB0) >> 1;
        vwGetViewPosition(&sp48);

        temp_v1_9 = Math_Vector3MagCalc((((g_SysWork.playerWork_4C.player_0.position_18.vx + sp48.vx) >> 1) + 0xA333),
                                        ((g_SysWork.playerWork_4C.player_0.position_18.vy + sp48.vy) >> 1),
                                        (((g_SysWork.playerWork_4C.player_0.position_18.vz + sp48.vz) >> 1) + 0xD599));

        if (temp_v1_9 < 0x1000)
        {
            var_v0_2 = D_800E20FC;
        }
        else
        {
            var_v0_2 = temp_v1_9;
            if (var_v0_2 > 0x11000)
            {
                var_v0_2 = 0;
            }
            else
            {
                var_v0_2 = Q12_MULT_PRECISE(D_800E20FC, 0x1000 - (FP_TO(var_v0_2 - 0x1000, Q12_SHIFT) / 0x10000));
            }
        }

        var_v0_2 = ~(var_v0_2 >> 4);
        Sd_SfxAttributesUpdate(1465, temp_s0_2, var_v0_2, 0);
    }
}

void func_800DBEC8(void) // 0x800DBEC8
{
    typedef enum _EventState
    {
        EventState_BookFirstTime = 3,
        EventState_BookAgain     = 6
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
            func_8008605C(EventFlag_M1S03_MonsterLurksBookRead, EventState_BookAgain, EventState_BookFirstTime, false);
            break;

        case 3:
            MapMsg_DisplayAndHandleSelection(false, 15, false, false, 0, false); // "What's this?"
            break;

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(0.6f), false);
            break;

        case 5:
            MapMsg_DisplayAndHandleSelection(false, 16, false, false, 0, false); // "The Monster Lurks is the book's title."
            break;

        case EventState_BookAgain:
            func_800862F8(0, FILE_TIM_LMONSTER_TIM, false);
            SysWork_StateStepIncrementAfterFade(false, true, false, false, false);
            SysWork_StateStepIncrement(0);

        case 7:
            func_800862F8(1, 0, false);
            break;

        case 8:
            SysWork_StateStepIncrementAfterFade(1, true, false, false, false);
            break;

        case 9:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, false, false, false);
            break;

        case 10:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 17, false, false, 0, false); // "Chapter3: ..."
            break;

        case 11:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, false, false, false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_M1S03_MonsterLurksBookRead);
            SysWork_StateStepIncrementAfterFade(0, false, false, false, false);
            break;
    }
}

void func_800DC0F8(void) // 0x800DC0F8
{
    typedef enum _EventState
    {
        EventState_Flag117True  = NO_VALUE,
        EventState_Flag117False = 8,
    } e_EventState;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_LIBRBOOK_TIM, false);
            SysWork_StateStepIncrementAfterFade(false, true, 0, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            SysWork_StateStepIncrementAfterFade(1, true, 0, 0, false);
            break;

        case 3:
            func_800862F8(1, 0, false);
            break;

        case 4:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 5:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 23, false, false, 0, false); // "Hearing this, the hunter armed with bow..."
            break;

        case 6:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 7:
            SysWork_StateStepIncrementAfterFade(false, false, 0, 0, false);
            func_8008605C(EventFlag_117, EventState_Flag117True, EventState_Flag117False, false);
            break;

        case EventState_Flag117False:
            SysWork_StateStepIncrementAfterFade(1, false, 0, 0, false);
            break;

        case 9:
            MapMsg_DisplayAndHandleSelection(false, 30, false, false, 0, false); // "This is from an old fairy tale."
            break;

        default: // `EventState_Flag117True`
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_117);
            break;
    }
}

void func_800DC2E4(void) // 0x800DC2E4
{
    MapMsg_DisplayWithTexture(FILE_TIM_LOCKER1_TIM, Q12(2.5f), Q12(2.5f), 43); // "Nothing inside."
}

void func_800DC310(void) // 0x800DC310
{
    typedef enum _EventState
    {
        EventState_LockerOpenWait = 9,
        EventState_LockerOpen     = 10,
        EventState_Skip           = 13
    } e_EventState;

    if ((g_Controller0->btnsClicked_10 & g_GameWorkPtr->config_0.controllerConfig_0.skip_4) &&
        g_SysWork.sysStateStep_C[0] >= 3 && g_SysWork.sysStateStep_C[0] < 11)
    {
        ScreenFade_ResetTimestep();
        Savegame_EventFlagSet(EventFlag_101);
        Savegame_EventFlagSet(EventFlag_102);
        Savegame_EventFlagSet(EventFlag_M1S03_LockerOpened);
        SysWork_StateStepSet(0, EventState_Skip);
    }

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            Savegame_EventFlagSet(EventFlag_100);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            // Warp player.
            g_SysWork.playerWork_4C.player_0.position_18.vx = Q12(-59.36f);
            g_SysWork.playerWork_4C.player_0.position_18.vz = Q12(18.37f);
            g_SysWork.playerWork_4C.player_0.moveSpeed_38 = Q12(0.0f);
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = Q12_ANGLE(90.0f);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-60.16f), Q12(-2.7f), Q12(19.76f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-58.13f), Q12(-0.04f), Q12(17.57f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            SysWork_StateStepIncrement(0);

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 2, 0, false);
            break;

        case 4:
            SysWork_StateStepIncrementDelayed(Q12(1.0f), false);
            break;

        case 5:
            Savegame_EventFlagSet(EventFlag_101);
            SysWork_StateStepIncrement(0);

        case 6:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 85);
            break;

        case 7:
            Savegame_EventFlagSet(EventFlag_102);
            func_80085EB8(0, &g_SysWork.playerWork_4C.player_0, 86, false);
            SysWork_StateStepIncrement(0);

        case 8:
            SysWork_StateStepIncrementDelayed(Q12(2.0f), false);
            break;

        case EventState_LockerOpenWait:
            func_8008605C(EventFlag_M1S03_LockerOpened, EventState_LockerOpen, EventState_LockerOpenWait, false);
            break;

        case EventState_LockerOpen:
            func_80086E50(FILE_TIM_LOCKER1_TIM, Q12(3.0f), Q12(1.5f));
            break;

        case 11:
            func_800862F8(2, 0, false);
            MapMsg_DisplayAndHandleSelection(false, 43, 0, 0, 0, false); // "Nothing inside."
            break;

        case 12:
            func_80086F44(Q12(1.5f), Q12(3.0f));
            break;

        case EventState_Skip:
            func_80085EB8(4, &g_SysWork.playerWork_4C.player_0, 0, false);
            Savegame_EventFlagSet(EventFlag_104);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-60.63f), Q12(-4.14f), Q12(17.42f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-60.0f), Q12(0.0f), Q12(18.5f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            SysWork_StateStepIncrement(0);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);

            if (ScreenFade_IsFinished())
            {
                SysWork_StateStepIncrementAfterFade(0, false, 0, 0, false);
            }
            break;
    }
}

void func_800DC780(void) // 0x800DC780
{
    typedef enum _EventState
    {
        EventState_Flag106False = 4,
        EventState_Flag106True  = 5
    } e_EventState;

    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            SysWork_StateStepIncrement(0);

        case 1:
            Savegame_EventFlagSet(EventFlag_105);

            // Warp camera.
            Camera_PositionSet(NULL, Q12(-59.93f), Q12(0.0f), Q12(20.18f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
            Camera_LookAtSet(NULL, Q12(-62.99f), Q12(-2.29f), Q12(21.37f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);

            // Warp player.
            g_SysWork.playerWork_4C.player_0.rotation_24.vy = ratan2(Q12(-61.4f) - g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                                Q12(20.8f)  - g_SysWork.playerWork_4C.player_0.position_18.vz);

            func_8008D438();
            Model_AnimFlagsClear(&g_SysWork.playerWork_4C.player_0.model_0, AnimFlag_Visible);
            SysWork_StateStepIncrement(0);

        case 2:
            SysWork_StateStepIncrementDelayed(Q12(0.7f), false);
            break;

        case 3:
            func_8005DC1C(Sfx_Unk1466, &QVECTOR3(-60.3f, 0.0f, 20.2f), Q8(0.5f), 0);
            SysWork_StateStepIncrement(0);

        case EventState_Flag106False:
            func_8008605C(EventFlag_106, EventState_Flag106True, EventState_Flag106False, false);
            break;

        case EventState_Flag106True:
            SysWork_StateStepIncrementDelayed(Q12(0.8f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            Savegame_EventFlagSet(EventFlag_107);
            Model_AnimFlagsSet(&g_SysWork.playerWork_4C.player_0.model_0, AnimFlag_Visible);
            func_8008D448();
            break;
    }
}

void func_800DC9A0(void) // 0x800DC9A0
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_80086470(0, InventoryItemId_LibraryReserveKey, 0, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            func_80086470(1, InventoryItemId_LibraryReserveKey, 0, false);
            break;

        case 4:
            Savegame_EventFlagSet(EventFlag_M1S03_PickupLibraryReserveKey);
            if (Gfx_PickupItemAnimate(InventoryItemId_LibraryReserveKey))
            {
                MapMsg_DisplayAndHandleSelection(true, 44, 5, 6, 0, false);
            }
            if (g_SysWork.sysStateStep_C[0] == 6)
            {
                Savegame_EventFlagClear(EventFlag_M1S03_PickupLibraryReserveKey);
            }
            break;

        case 5:
            func_80086470(3, InventoryItemId_LibraryReserveKey, 1, false);
            SysWork_StateStepIncrement(0);

        case 6:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

void func_800DCB54(void) // 0x800DCB54
{
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();
            func_800862F8(0, FILE_TIM_BALLHOLE_TIM, false);
            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 59);
            break;

        case 3:
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 4:
            func_8005DC1C(Sfx_Unk1461, &QVECTOR3(-10.5f, 0.0f, -17.5f), Q8(0.5f), 0);
            Savegame_EventFlagSet(EventFlag_M1S02_UsedRubberBall);
            SysWork_StateStepIncrement(0);

        case 5:
            func_800862F8(1, 0, false);
            break;

        case 6:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 7:
            MapMsg_DisplayAndHandleSelection(false, 36, 0, 0, 0, false); // "Used the rubber ball."
            func_800862F8(2, 0, false);
            break;

        case 8:
            func_800862F8(2, 0, false);
            SysWork_StateStepIncrementAfterFade(2, true, 0, 0, false);
            break;

        case 9:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);
            break;

        case 10:
            func_80086C58(&g_SysWork.playerWork_4C.player_0, 60);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            break;
    }
}

#include "maps/shared/SysWork_StateStepIncrementAfterTime.h" // 0x800DCD44

void func_800DCDDC(void) // 0x800DCDDC
{
    s32 pitch;
    s32 tmp0;
    s32 tmp1;
    s32 cos0;
    s32 sin0;

    tmp0 = D_800E201C;
    tmp1 = tmp0 >> 2;
    sin0 = Math_Sin(tmp1);
    cos0 = Math_Cos(tmp0 >> 4);
    pitch = ((sin0 * 2) + cos0 + Math_Cos(Math_Sin(tmp1 * 2))) >> 9;

    if (g_SysWork.sysStateStep_C[0] >= 10)
    {
        D_800E2018 -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.5f));
        if (D_800E2018 < 0)
        {
            D_800E2018 = 0;
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800E2018 >> 4), pitch);
    }
    else if (g_SysWork.sysStateStep_C[0] > 0)
    {
        D_800E2018 += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.25f));
        if (D_800E2018 > Q12(0.9961f))
        {
            D_800E2018 = Q12(0.9961f);
        }

        Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, ~(D_800E2018 >> 4), pitch);
    }
    switch (g_SysWork.sysStateStep_C[0])
    {
        case 0:
            Player_ControlFreeze();

            D_800E2102 = 0;

            Fs_QueueStartReadTim(FILE_TIM_ENBAN_TIM, FS_BUFFER_1, &D_800E2004);
            Fs_QueueStartRead(FILE_ANIM_UFO1_DMS, FS_BUFFER_13);

            D_800E617C = NO_VALUE;
            ScreenFade_ResetTimestep();

            SD_Call(Sfx_Unk1467);
            Sd_SfxAttributesUpdate(Sfx_Unk1467, 0, Q8_CLAMPED(1.0f), 0);

            D_800E2018 = 0;
            D_800E201C = 0;

            SysWork_StateStepIncrement(0);

        case 1:
            func_80085DF0();
            break;

        case 2:
            if (Fs_QueueDoThingWhenEmpty())
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 3:
            D_800E617C = 0;

            SysWork_StateStepIncrementAfterFade(0, true, 3, 0, false);
            DmsHeader_FixOffsets((s_DmsHeader*)FS_BUFFER_13);
            func_8003D03C();
            sharedFunc_800D2EB4_0_s00();
            Game_TurnFlashlightOn();
            SysWork_StateStepIncrement(0);

        case 4:
            SysWork_StateStepIncrementAfterFade(2, false, 0, 0, false);

        case 5:
            Map_MessageWithAudio(46, &D_800E2102, D_800E2000); // "What?"
            break;


        case 6:
            SysWork_StateStepIncrementAfterTime(&D_800E617C, Q12(40.0f), Q12(0.0f), Q12(30.0f), true, true);
            sharedFunc_800CE5D4_1_s03(&D_800E200C, Q12(0.5f), Q12(0.05f), 0);
            break;
        case 7:
            MapMsg_DisplayAndHandleSelection(false, 47, 0, 0, 0, false); // "That light!?"
            sharedFunc_800CE5D4_1_s03(&D_800E200C, Q12(0.5f), Q12(0.05f), 0);
            break;

        case 8:
            func_80080B58(&g_SysWork.playerBoneCoords_890[2], &(SVECTOR3){ 0, 0, 0 }, &QVECTOR3(-13.91f, -11.5f, 22.11f));
            sharedFunc_800CE5D4_1_s03(&D_800E200C, Q12(0.5f), Q12(0.05f), 0);
            SysWork_StateStepIncrementDelayed(0x2800, false);
            break;

        case 9:
            sharedFunc_800CE5D4_1_s03(&D_800E200C, Q12(0.5f), Q12(0.05f), 0);

            g_SysWork.field_28 += g_DeltaTime;
            if (g_SysWork.field_28 > Q12(4.0f))
            {
                D_800E200C.vx += Q12_MULT_PRECISE(g_DeltaTime, Q12(-1.2f));
                D_800E200C.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12(-0.4f));
            }

            if (g_SysWork.field_28 > Q12(6.0f))
            {
                SysWork_StateStepIncrement(0);
            }
            break;

        case 10:
            SysWork_StateStepIncrementDelayed(Q12(2.5f), false);
            break;

        default:
            Player_ControlUnfreeze(false);
            SysWork_StateSetNext(SysState_Gameplay);
            SysWork_StateStepIncrementAfterFade(0, false, 2, 0, false);
            vcReturnPreAutoCamWork(true);

            Savegame_EventFlagSet(EventFlag_456);
            func_80086470(3, InventoryItemId_ChannelingStone, 1, false);
            func_8003D01C();
            sharedFunc_800D2EF4_0_s00();

            D_800E617C = NO_VALUE;

            Sd_SfxStop(Sfx_Unk1467);
            break;
    }

    D_800E201C += g_DeltaTime;
    if (D_800E617C >= Q12(0.0f))
    {
        Dms_CharacterGetPosRot(&g_SysWork.playerWork_4C.player_0.position_18, &g_SysWork.playerWork_4C.player_0.rotation_24, "HERO", D_800E617C, (s_DmsHeader*)FS_BUFFER_13);
        vcChangeProjectionValue(Dms_CameraGetTargetPos(&D_800E6160, &D_800E6170, NULL, D_800E617C, (s_DmsHeader*)FS_BUFFER_13));
        vcUserCamTarget(&D_800E6160, NULL, true);
        vcUserWatchTarget(&D_800E6170, NULL, true);
    }
}

void Map_WorldObjectsInit(void) // 0x800DD3AC
{
    D_800E62D0 = 0;
    D_800E638C = 0;

    WorldObjectNoRotInit(&g_WorldObject6, "BALL_HID", -10.25f, 0.2f, -17.75f);

    WorldObjectInit(&g_WorldObject5, "VALVE_HI", -10.49f, -0.7f, -12.92f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject0, "TOBIRA00", -58.81f, -1.4f, 18.02f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject1, "TOBIRA01", -58.81f, -1.4f, 18.02f, 0.0f, 0.0f, 0.0f);

    WorldObjectInit(&g_WorldObject2, "TOBIRA2_", -61.0f, -1.05f, 20.97f, 0.0f, 0.0f, 0.0f);

    WorldObjectNoRotInit(&g_WorldObject3, "HAKO1_HI", -58.81f, -1.4f, 18.02f);

    WorldObjectNoRotInit(&g_WorldObject4, "HAKO2_HI", -61.0f, -0.9f, 20.97f);

    WorldObjectInit(&g_WorldObject7, "KEY_HIDE", -60.3184f, -0.00732422f, 20.23f, 0.0f, 53.2f, 5.3f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        func_80088FF4(Chara_GreyChild, 1, 0);
        func_80088FF4(Chara_GreyChild, 5, 0);
        func_80088FF4(Chara_GreyChild, 6, 0);
        func_80088FF4(Chara_GreyChild, 7, 0);
        func_80088FF4(Chara_Creeper, 5, 0);
        func_80088FF4(Chara_Creeper, 6, 0);
    }

    WorldObject_ModelNameSet(&g_CommonWorldObjects[0], D_800A99E4.firstAidKitName_8);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[1], D_800A99E4.healthDrinkName_C);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[2], D_800A99E4.ampouleName_10);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[3], D_800A99E4.handgunBulletsName_14);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[4], D_800A99E4.shotgunShellsName_18);
    WorldObject_ModelNameSet(&g_CommonWorldObjects[5], D_800A99E4.rifleShellsName_1C);
}

void Map_WorldObjectsUpdate(void) // 0x800DD688
{
    s32 x;
    MAP_CHUNK_CHECK_VARIABLE_DECL();

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, -1, 0, 0))
    {
        WorldGfx_ObjectAdd(&g_WorldObject5.object_0, &g_WorldObject5.position_1C, &g_WorldObject5.rotation_28);

        if (Savegame_EventFlagGet(EventFlag_M1S02_UsedRubberBall))
        {
            WorldGfx_ObjectAdd(&g_WorldObject6.object_0, &g_WorldObject6.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 0, 0, -1, 1))
    {
            func_800DE828();

            if (Savegame_EventFlagGet(EventFlag_107) && !Savegame_EventFlagGet(EventFlag_M1S03_PickupLibraryReserveKey))
            {
                WorldGfx_ObjectAdd(&g_WorldObject7.object_0, &g_WorldObject7.position_1C, &g_WorldObject7.rotation_28);
            }

            if ((g_SysWork.playerWork_4C.player_0.position_18.vx < Q12(-57.5f)) && (g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(21.6f)))
            {
                if (!Savegame_EventFlagGet(EventFlag_100))
                {
                    if (g_SysWork.playerWork_4C.player_0.position_18.vx > Q12(-60.0f))
                    {
                        if (D_800E62D0 == 2)
                        {
                            D_800E62D0 = 0;
                        }

                        // Warp camera.
                        Camera_PositionSet(NULL, Q12(-61.18f), Q12(-3.0f), g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(0.49f),
                                           Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), D_800E62D0 == 0);
                        Camera_LookAtSet(NULL, Q12(-58.48f), Q12(-0.31f), g_SysWork.playerWork_4C.player_0.position_18.vz - Q12(0.72f),
                                         Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), D_800E62D0 == 0);

                        D_800E62D0 = 1;
                    }
                    else
                    {
                        Camera_PositionSet(NULL, Q12(-58.48f), Q12(-1.88f), Q12(22.3f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
                        Camera_LookAtSet(NULL, Q12(-60.88f), Q12(-1.23f), Q12(19.16f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
                        D_800E62D0 = 2;
                    }
                }
                else if (Savegame_EventFlagGet(EventFlag_107))
                {
                    if (g_SysWork.playerWork_4C.player_0.position_18.vz > Q12(18.6f))
                    {
                        // Warp camera.
                        Camera_PositionSet(NULL, Q12(-60.27f), Q12(-0.41f), g_SysWork.playerWork_4C.player_0.position_18.vz - Q12(2.25f),
                                           Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), D_800E62D0 == 0);
                        Camera_LookAtSet(NULL, Q12(-59.75f), Q12(-1.09f), g_SysWork.playerWork_4C.player_0.position_18.vz + Q12(1.65f),
                                         Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), D_800E62D0 == 0);

                        D_800E62D0 = 1;
                    }
                    else
                    {
                        D_800E62D0 = 0;

                        // Warp camera.
                        Camera_PositionSet(NULL, Q12(-60.15f), Q12(-3.3f), Q12(20.52f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
                        Camera_LookAtSet(NULL, Q12(-59.98f), Q12(-0.85f), Q12(17.36f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
                    }
                }
            }
            else
            {
                if (D_800E62D0 == 2)
                {
                    D_800E62D0 = 1;
                }

                vcReturnPreAutoCamWork(D_800E62D0);
                D_800E62D0 = 0;
            }
    }

    if (Savegame_EventFlagGet(EventFlag_104) && !Savegame_EventFlagGet(EventFlag_105))
    {
        // Warp camera.
        Camera_PositionSet(NULL, Q12(-60.63f), Q12(-4.14f), Q12(17.42f), Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), true);
        if (g_SysWork.playerWork_4C.player_0.position_18.vz < Q12(18.5f))
        {
            Camera_LookAtSet(NULL, Q12(-60.0f), Q12(0.0f), Q12(18.5f),
                             Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);
        }
        else
        {
            Camera_LookAtSet(NULL, Q12(-60.0f), Q12(0.0f), g_SysWork.playerWork_4C.player_0.position_18.vz,
                             Q12(0.0f), Q12(0.0f), Q12(0.0f), Q12(0.0f), false);
        }

        D_800E62D0 = 0;
    }

    if (!Savegame_EventFlagGet(EventFlag_53) &&
        PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        x = g_SysWork.playerWork_4C.player_0.position_18.vx;
        if (x < Q12(-100.0f))
        {
            D_800E638C += g_DeltaTime;
        }
        else if (x < Q12(-99.0f))
        {
            D_800E638C += Q12_MULT_PRECISE(g_DeltaTime, (x + Q12(100.0f)));
        }

        if ((D_800E6388 == 0 && D_800E638C > Q12(2.5f)) ||
            (D_800E6388 == 1 && D_800E638C > Q12(4.0f)) ||
            (D_800E6388 == 2 && D_800E638C > Q12(4.6f)) ||
            (D_800E6388 == 3 && D_800E638C > Q12(7.4f)) ||
            (D_800E6388 == 4 && D_800E638C > Q12(8.6f)) ||
            (D_800E6388 == 5 && D_800E638C > Q12(9.3f)))
        {
            func_8005DC1C(0x5BC, &QVECTOR3(-96.1f, -1.2f, 141.8f), 0xFF, 2);
            D_800E6388++;
        }
    }
    else if (D_800E6388)
    {
        Savegame_EventFlagSet(EventFlag_53);
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 3, -1, 3))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S03_ShotgunShells0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[0].position_0, &g_CommonWorldObjectPoses[0].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S03_HandgunBullets0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[1].position_0, &g_CommonWorldObjectPoses[1].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -1, 0, 0) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S03_HealthDrink0))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[2].position_0, &g_CommonWorldObjectPoses[2].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S03_HandgunBullets1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[3].position_0, &g_CommonWorldObjectPoses[3].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S03_HandgunBullets2))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[4].position_0, &g_CommonWorldObjectPoses[4].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -4, -1, -4) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S03_ShotgunShells1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[5], &g_CommonWorldObjectPoses[5].position_0, &g_CommonWorldObjectPoses[5].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S03_HandgunBullets3))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[3], &g_CommonWorldObjectPoses[6].position_0, &g_CommonWorldObjectPoses[6].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S03_HealthDrink1))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[7].position_0, &g_CommonWorldObjectPoses[7].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -2, -1, -2) && PLAYER_IN_MAP_CHUNK(vz, 1, 2, -1, 2))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S03_HealthDrink2))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[1], &g_CommonWorldObjectPoses[8].position_0, &g_CommonWorldObjectPoses[8].rotation_C);
        }
    }

    if (PLAYER_IN_MAP_CHUNK(vx, 1, -3, -1, -3) && PLAYER_IN_MAP_CHUNK(vz, 1, 4, -1, 4))
    {
        if (!Savegame_EventFlagGet(EventFlag_M1S03_FirstAidKit))
        {
            WorldGfx_ObjectAdd(&g_CommonWorldObjects[0], &g_CommonWorldObjectPoses[9].position_0, &g_CommonWorldObjectPoses[9].rotation_C);
        }
    }
}

void func_800DE624(void) // 0x800DE624
{
    q19_12 playerHealth;

    if (Savegame_EventFlagGet(EventFlag_M1S02_PickupClassroomKey) && g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        func_80088FF4(Chara_GreyChild, 9, 3);
        func_80088FF4(Chara_GreyChild, 10, 3);
    }

    if (Savegame_EventFlagGet(EventFlag_M1S03_PickupLibraryReserveKey))
    {
        if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
        {
            func_80088FF4(Chara_GreyChild, 12, 3);
        }

        if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
        {
            func_80088FF4(Chara_GreyChild, 13, 3);
            func_80088FF4(Chara_GreyChild, 11, 7);
        }

        func_80088FF4(Chara_GreyChild, 14, 11);
        func_80088FF4(Chara_GreyChild, 15, 3);
    }

    playerHealth = g_SysWork.playerWork_4C.player_0.health_B0;
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        playerHealth -= Q12(50.0f);
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        playerHealth -= Q12(25.0f);
    }

    if (playerHealth > Q12(20.0f))
    {
        func_80088FF4(Chara_Creeper, 0, 3);
    }
    else
    {
        func_80088FF4(Chara_Creeper, 0, 0);
    }

    if (playerHealth > Q12(60.0f))
    {
        func_80088FF4(Chara_Creeper, 1, 3);
        func_80088FF4(Chara_Creeper, 2, 3);
    }
    else
    {
        func_80088FF4(Chara_Creeper, 1, 0);
        func_80088FF4(Chara_Creeper, 2, 0);
    }

    if (playerHealth > Q12(80.0f))
    {
        func_80088FF4(Chara_Creeper, 3, 3);
        func_80088FF4(Chara_Creeper, 4, 3);
    }
    else
    {
        func_80088FF4(Chara_Creeper, 3, 0);
        func_80088FF4(Chara_Creeper, 4, 0);
    }
}

void func_800DE828(void) // 0x800DE828
{
    s32 tmp0;
    s32 tmp1;

    const static VECTOR3 sfxPos = VECTOR3(-58.81f, -1.4f, 18.02f);

    if (g_DeltaTime == Q12(0.0f))
    {
        if (Savegame_EventFlagGet(EventFlag_105))
        {
            WorldGfx_ObjectAdd(&g_WorldObject4.object_0, &g_WorldObject4.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }

        if (Savegame_EventFlagGet(EventFlag_101) && Savegame_EventFlagGet(EventFlag_102))
        {
            WorldGfx_ObjectAdd(&g_WorldObject3.object_0, &g_WorldObject3.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }

        WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &g_WorldObject0.rotation_28);
        WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &g_WorldObject1.rotation_28);
        WorldGfx_ObjectAdd(&g_WorldObject2.object_0, &g_WorldObject2.position_1C, &g_WorldObject2.rotation_28);
    }
    else
    {
        if (Savegame_EventFlagGet(EventFlag_105) && !Savegame_EventFlagGet(EventFlag_106))
        {
            if (D_800E20EE == 6)
            {
                func_800892A4(18);
                func_8005DC1C(Sfx_Unk1460, &g_WorldObject2.position_1C, Q8_CLAMPED(1.0f), 2);

                D_800E20E8 = Q12_ANGLE(-11.3f);
                D_800E20EE = 7;
                D_800E20EC = 0;
            }

            g_WorldObject2.rotation_28.vy += D_800E20E8;

            if (D_800E20E8 == Q12_ANGLE(-11.3f))
            {
                if (g_WorldObject2.rotation_28.vy < Q12_ANGLE(-168.8f))
                {
                    g_WorldObject2.rotation_28.vy = Q12_ANGLE(-168.8f);
                    D_800E20E8 = Q12_ANGLE(2.9f);

                    func_8005DC1C(Sfx_Unk1434, &g_WorldObject2.position_1C, Q8_CLAMPED(1.0f), 2);
                }
            }
            else if ((g_WorldObject2.rotation_28.vy < Q12_ANGLE(-168.8f) && D_800E20E8 < 0) ||
                     (g_WorldObject2.rotation_28.vy >= Q12_ANGLE(-157.45f) && D_800E20E8 > 0))
            {
                tmp1 = -D_800E20E8 >> 1;
                D_800E20E8 = tmp1;
                if (ABS(tmp1) == 1)
                {
                    D_800E20E8 = 0;
                }
            }

            if (D_800E20E8 == 0)
            {
                Savegame_EventFlagSet(EventFlag_106);
            }

            WorldGfx_ObjectAdd(&g_WorldObject4.object_0, &g_WorldObject4.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }
        else if (Savegame_EventFlagGet(EventFlag_106))
        {
            g_WorldObject2.rotation_28.vy = Q12_ANGLE(-157.4f);
            WorldGfx_ObjectAdd(&g_WorldObject4.object_0, &g_WorldObject4.position_1C, &(SVECTOR3){ 0, 0, 0 });
        }

        if (!Savegame_EventFlagGet(EventFlag_101) || !Savegame_EventFlagGet(EventFlag_102))
        {
            if (D_800E20E8 == 0)
            {
                if (!Rng_GenerateUInt(0, 31)) // 1 in 32 chance.
                {
                    D_800E20E8 = -Rng_GenerateUInt(2, 9);
                }
            }

            if (D_800E20E8 != 0)
            {
                if (ABS(D_800E20E8) == 1)
                {
                    g_WorldObject1.rotation_28.vy += D_800E20E8;
                }
                g_WorldObject1.rotation_28.vy += D_800E20E8;

                if (D_800E20E8 > 0)
                {
                    if (g_WorldObject1.rotation_28.vy > 0)
                    {
                        func_8005DC1C(Sfx_Unk1435, &sfxPos, Q8_CLAMPED(0.5f), 0);
                        g_WorldObject1.rotation_28.vy = 0;

                        if (D_800E20E8 >= 8 && !Rng_GenerateUInt(0, 3)) // 1 in 4 chance.
                        {
                            D_800E20E8 = 0;
                        }
                        else
                        {
                            D_800E20E8 = (Rng_GenerateUInt(0, 3) - D_800E20E8) + 1;
                        }
                        D_800E20E8 = MIN(D_800E20E8, 0);
                    }
                }
                else if (g_WorldObject1.rotation_28.vy < Q12_ANGLE(-1.8f))
                {
                    func_8005DC1C(Sfx_Unk1435, &sfxPos, Q8_CLAMPED(0.5f), 0);

                    D_800E20E8 = ~Rng_GenerateUInt(0, 3) - D_800E20E8;
                    D_800E20E8 = MAX(D_800E20E8, 1);
                }
            }
        }
        else if (!Savegame_EventFlagGet(EventFlag_M1S03_LockerOpened) || D_800E20EE == 5)
        {
            switch (D_800E20EE)
            {
                case 0:
                    D_800E20E8 = Q12_ANGLE(-1.45f);
                    D_800E20EC = 0;
                    D_800E20EE = 1;

                case 1:
                    g_WorldObject1.rotation_28.vy += D_800E20E8;
                    if (g_WorldObject1.rotation_28.vy <  Q12_ANGLE(-2.9f))
                    {
                        func_800892DC(18, 0x60);
                        func_8005DC1C(Sfx_Unk1434, &sfxPos, Q8(0.7657f), 2);

                        g_WorldObject1.rotation_28.vy = Q12_ANGLE(-2.9f);
                        D_800E20E8 = Q12_ANGLE(1.45f);
                        D_800E20EE = 2;
                    }
                    break;

                case 2:
                    D_800E20E8 -= 2;
                    g_WorldObject1.rotation_28.vy += D_800E20E8;

                    if (g_WorldObject1.rotation_28.vy > 0)
                    {
                        func_8005DC1C(Sfx_Unk1434, &sfxPos, Q8(0.7657f), 2);
                        do
                        {
                            D_800E20E8 = Q12(-10.0f);
                            g_WorldObject1.rotation_28.vy = 0;
                            D_800E20EE = 3;
                        }
                        while (0); // @hack permuter find.
                    }
                    break;

                case 3:
                    D_800E20EC += g_DeltaTime;
                    if (D_800E20EC > Q12(3.0f))
                    {
                        D_800E20EE = 4;
                    }
                    break;

                case 4:
                case 5:
                    D_800E20E8 += Q12_MULT_PRECISE(g_DeltaTime, Q12(4.0f));
                    if (D_800E20E8 <= Q12(-2.0f))
                    {
                        tmp0 = D_800E20E8;
                    }
                    else
                    {
                        tmp0 = Q12(-2.0f);
                    }

                    D_800E20E8 = tmp0;
                    g_WorldObject1.rotation_28.vy += FP_FROM(tmp0, Q12_SHIFT);

                    WorldGfx_ObjectAdd(&g_WorldObject3.object_0, &g_WorldObject3.position_1C, &(SVECTOR3){ 0, 0, 0 });

                    if (D_800E20EE == 4)
                    {
                        if (g_WorldObject1.rotation_28.vy < Q12_ANGLE(-5.7f))
                        {
                            func_8005DC1C(Sfx_Unk1436, &g_WorldObject1.position_1C, 0x80, 0);
                            D_800E20EE = 5;
                        }
                    }

                    if (g_WorldObject1.rotation_28.vy < Q12_ANGLE(-39.4f))
                    {
                        Savegame_EventFlagSet(EventFlag_M1S03_LockerOpened);
                    }

                    if (Savegame_EventFlagGet(EventFlag_104) || ScreenFade_IsFinished() || g_WorldObject1.rotation_28.vy < -0x300)
                    {
                        g_WorldObject1.rotation_28.vy = Q12_ANGLE(-67.5f);
                        D_800E20EE = 6;
                    }
                    break;

                default:
                    break;
            }
        }
        else
        {
            g_WorldObject1.rotation_28.vy = Q12_ANGLE(-157.5f);
            WorldGfx_ObjectAdd(&g_WorldObject3.object_0, &g_WorldObject3.position_1C, &(SVECTOR3){ 0, 0, 0 });

            if (!Savegame_EventFlagGet(EventFlag_105))
            {
                D_800E20EE = 6;
            }
        }

        g_WorldObject0.rotation_28.vy = g_WorldObject1.rotation_28.vy;
        WorldGfx_ObjectAdd(&g_WorldObject0.object_0, &g_WorldObject0.position_1C, &g_WorldObject0.rotation_28);
        WorldGfx_ObjectAdd(&g_WorldObject1.object_0, &g_WorldObject1.position_1C, &g_WorldObject1.rotation_28);
        WorldGfx_ObjectAdd(&g_WorldObject2.object_0, &g_WorldObject2.position_1C, &g_WorldObject2.rotation_28);
    }
}
