#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/hanged_scratcher.h"

#define scratcherProps scratcher->properties_E4.hangedScratcher

void Ai_HangedScratcher_Update(s_SubCharacter* scratcher, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    // Initialize.
    if (scratcher->model_0.controlState_2 == HangedScratcherControl_None)
    {
        Ai_HangedScratcher_Init(scratcher);
    }

    sharedFunc_800CFF74_5_s00(scratcher);
    Ai_HangedScratcher_ControlUpdate(scratcher);
    sharedFunc_800D26D8_5_s00(scratcher);
    sharedFunc_800D2844_5_s00(scratcher, anmHdr, coords);
    sharedFunc_800D2C18_5_s00(scratcher);
    sharedFunc_800D3300_5_s00(scratcher);
}

void Ai_HangedScratcher_Init(s_SubCharacter* scratcher)
{
    s32    i;
    q19_12 radiusMax;
    q19_12 radiusMin;

    scratcherProps.flags_E8 = 0;
    Chara_PropertiesClear(scratcher);

    scratcher->health_B0 = Q12(350.0f);
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        scratcher->health_B0 = Q12_MULT_PRECISE(scratcher->health_B0, Q12(1.35f)); // 472.44873f
    }

    scratcher->moveSpeed_38    = Q12(0.0f);
    scratcher->fallSpeed_34    = Q12(0.0f);
    scratcher->headingAngle_3C = scratcher->rotation_24.vy;
    scratcher->rotation_24.vx  = Q12_ANGLE(0.0f);

    ModelAnim_AnimInfoSet(&scratcher->model_0.anim_4, HANGED_SCRATCHER_ANIM_INFOS);
    Chara_DamageClear(scratcher);

    // Handle state step.
    switch (scratcher->model_0.stateStep_3)
    {
        case HangedScratcherStateStep_3:
        case HangedScratcherStateStep_9:
            if (scratcher->model_0.stateStep_3 == HangedScratcherStateStep_3)
            {
                scratcher->model_0.controlState_2 = HangedScratcherControl_2;
            }
            else if (scratcher->model_0.stateStep_3 == HangedScratcherStateStep_7) // @unused This will never run? Meant to be `HangedScratcherStateStep_9`?
            {
                scratcher->model_0.controlState_2 = HangedScratcherControl_16;
            }
            else
            {
                scratcher->model_0.controlState_2 = HangedScratcherControl_1;
            }

            Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_14, true), 222);
            scratcher->position_18.vy = Q12(-3.6f);
            scratcher->rotation_24.vz = Q12_ANGLE(180.0f);

        default:
            break;

        case HangedScratcherStateStep_7:
        case HangedScratcherStateStep_14:
            scratcher->model_0.controlState_2 = HangedScratcherControl_5;
            Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_15, true), 232);
            scratcher->position_18.vy = Q12(0.0f);
            scratcher->rotation_24.vz = Q12_ANGLE(0.0f);
            break;

        case HangedScratcherStateStep_17:
            scratcherProps.timer_EA = Q12(1.2f);

        case HangedScratcherStateStep_6:
            scratcher->model_0.controlState_2 = HangedScratcherControl_6;
            Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_15, true), 232);
            scratcher->position_18.vy = Q12(0.0f);
            scratcher->rotation_24.vz = Q12_ANGLE(0.0f);
            break;

        case HangedScratcherStateStep_18:
        case HangedScratcherStateStep_19:
        case HangedScratcherStateStep_20:
            scratcher->model_0.controlState_2 = HangedScratcherControl_14;
            scratcher->position_18.vy         = Q12(0.0f);
            scratcher->rotation_24.vz         = Q12_ANGLE(0.0f);

            switch (scratcher->model_0.stateStep_3)
            {
                case HangedScratcherStateStep_18:
                    Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_1, true), 0);
                    break;

                case HangedScratcherStateStep_19:
                    Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_2, true), 51);
                    break;

                case HangedScratcherStateStep_20:
                    Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_3, true), 87);
                    break;
            }
            break;
    }

    scratcherProps.positionX_F4 = scratcher->position_18.vx;
    scratcherProps.positionZ_F8 = scratcher->position_18.vz;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        radiusMax = Q12(2.7f);
        radiusMin = Q12(2.4f);
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        radiusMax = Q12(3.0f);
        radiusMin = Q12(2.8f);
    }
    else
    {
        radiusMax = Q12(3.8f);
        radiusMin = Q12(3.6f);
    }

    // TODO: Use `Rng_GenerateInt`.
    scratcherProps.radiusMax_10C = (Rng_Rand16() % (radiusMax >> 2)) + ((radiusMax * 3) >> 2);
    scratcherProps.radiusMin_10E = (Rng_Rand16() % (radiusMin >> 2)) + ((radiusMin * 3) >> 2);
    scratcher->flags_3E         |= CharaFlag_Unk9 | CharaFlag_Unk3;
}

void sharedFunc_800CFF74_5_s00(s_SubCharacter* scratcher)
{
    s_Collision coll;
    q19_12      prevMoveSpeed;
    q3_12       prevHeadingAngle;

    if (scratcher->damage_B4.amount_C > Q12(0.0f) && scratcher->health_B0 > Q12(0.0f))
    {
        scratcher->health_B0                = MAX(Q12(0.0f), scratcher->health_B0 - scratcher->damage_B4.amount_C);
        scratcher->damage_B4.position_0.vx += (scratcher->moveSpeed_38 * Math_Sin(scratcher->headingAngle_3C)) >> 14; // TODO: Weird shift?
        scratcher->damage_B4.position_0.vz += (scratcher->moveSpeed_38 * Math_Cos(scratcher->headingAngle_3C)) >> 14;

        prevMoveSpeed              = scratcher->moveSpeed_38;
        scratcher->moveSpeed_38    = FP_TO(Math_Vector2MagCalc(scratcher->damage_B4.position_0.vx, scratcher->damage_B4.position_0.vz), Q12_SHIFT) / Q12(4.0f);
        prevHeadingAngle           = scratcher->headingAngle_3C;
        scratcher->headingAngle_3C = ratan2(scratcher->damage_B4.position_0.vx, scratcher->damage_B4.position_0.vz);

        switch (scratcher->model_0.controlState_2)
        {
            case HangedScratcherControl_4:
                g_SysWork.field_2284[3] &= ~(1 << 1);

            case HangedScratcherControl_1:
            case HangedScratcherControl_2:
            case HangedScratcherControl_3:
            case HangedScratcherControl_9:
                Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);

                if (scratcher->health_B0 == Q12(0.0f) && coll.field_8 == 7)
                {
                    scratcher->health_B0 = 1;

                    if (Rng_GenerateUInt(0, 15) < 12)
                    {
                        scratcher->moveSpeed_38    = prevMoveSpeed;
                        scratcher->headingAngle_3C = prevHeadingAngle;

                        Chara_DamageClear(scratcher);
                        return;
                    }
                }

                if (ABS(scratcher->position_18.vx - g_SysWork.playerWork_4C.player_0.position_18.vx) > Q12(0.2f) &&
                    ABS(scratcher->position_18.vz - g_SysWork.playerWork_4C.player_0.position_18.vz) > Q12(0.2f))
                {
                    if (coll.field_8 != 7 && (Rng_Rand16() & 0xF) < 4)
                    {
                        scratcherProps.flags_E8 |= HangedScratcherFlag_1;
                    }
                }

                scratcher->model_0.controlState_2  = HangedScratcherControl_9;
                scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_8, false);
                break;

            case HangedScratcherControl_15:
                g_SysWork.field_2284[3] &= ~(1 << 1);

            case HangedScratcherControl_5:
            case HangedScratcherControl_6:
            case HangedScratcherControl_7:
            case HangedScratcherControl_10:
                if (scratcher->health_B0 > Q12(100.0f))
                {
                    scratcher->model_0.controlState_2  = HangedScratcherControl_10;
                    scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_9, false);
                }
                else
                {
                    scratcher->model_0.controlState_2  = HangedScratcherControl_12;
                    scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_23, false);
                }

                break;

            case HangedScratcherControl_11:
                if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_12, true))
                {
                    scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_21, false);
                }

            case HangedScratcherControl_8:
                scratcher->fallSpeed_34 += FP_TO(scratcher->damage_B4.position_0.vy, Q12_SHIFT) / Q12(4.0f);
                break;

            case HangedScratcherControl_12:
                if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_13, true))
                {
                    scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_22, false);
                }
        }

        scratcherProps.timer_EA  = 0;
        scratcherProps.flags_E8 |= HangedScratcherFlag_4;
    }

    Chara_DamageClear(scratcher);
}

void Ai_HangedScratcher_ControlUpdate(s_SubCharacter* scratcher)
{
    s32 animStatus;

    animStatus = scratcher->model_0.anim_4.status_0;
    if (animStatus != ANIM_STATUS(HangedScratcherAnim_4, true) &&
        animStatus != ANIM_STATUS(HangedScratcherAnim_5, true))
    {
        scratcher->field_44.field_0 = 0;
    }

    // Handle control state.
    switch (scratcher->model_0.controlState_2)
    {
        case HangedScratcherControl_None:
            break;

        case HangedScratcherControl_1:
            Ai_HangedScratcher_Control_1(scratcher);
            break;

        case HangedScratcherControl_2:
            Ai_HangedScratcher_Control_2(scratcher);
            break;

        case HangedScratcherControl_3:
            Ai_HangedScratcher_Control_3(scratcher);
            break;

        case HangedScratcherControl_4:
            Ai_HangedScratcher_Control_4(scratcher);
            break;

        case HangedScratcherControl_5:
            Ai_HangedScratcher_Control_5(scratcher);
            break;

        case HangedScratcherControl_6:
            Ai_HangedScratcher_Control_6(scratcher);
            break;

        case HangedScratcherControl_7:
            Ai_HangedScratcher_Control_7(scratcher);
            break;

        case HangedScratcherControl_8:
            Ai_HangedScratcher_Control_8(scratcher);
            break;

        case HangedScratcherControl_9:
            Ai_HangedScratcher_Control_9(scratcher);
            break;

        case HangedScratcherControl_10:
            Ai_HangedScratcher_Control_10(scratcher);
            break;

        case HangedScratcherControl_11:
            Ai_HangedScratcher_Control_11(scratcher);
            break;

        case HangedScratcherControl_12:
            Ai_HangedScratcher_Control_12(scratcher);
            break;

        case HangedScratcherControl_13:
            Ai_HangedScratcher_Control_13(scratcher);
            break;

        case HangedScratcherControl_14:
            Ai_HangedScratcher_Control_14(scratcher);
            break;

        case HangedScratcherControl_15:
            Ai_HangedScratcher_Control_15(scratcher);
            break;

        case HangedScratcherControl_16:
            Ai_HangedScratcher_Control_16(scratcher);
            break;
    }
}

void Ai_HangedScratcher_Control_16(s_SubCharacter* scratcher)
{
    if (scratcherProps.field_104 != 0)
    {
        scratcher->model_0.controlState_2  = HangedScratcherControl_7;
        scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_18, false);
    }
}

void Ai_HangedScratcher_Control_1(s_SubCharacter* scratcher)
{
    q19_12 distToPlayer;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);

    // TODO: Invert to return early instead?
    if (distToPlayer < Q12(1.0f) &&
        !func_800700F8(scratcher, &g_SysWork.playerWork_4C.player_0) &&
        (((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3) == 2 && func_8006FD90(scratcher, 1, Q12(2.0f), Q12(1.5f))) ||
         ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) &&
          (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)) &&
          func_8006FD90(scratcher, 1, Q12(1.5f), Q12(0.3f)))))
    {
        scratcher->model_0.controlState_2  = HangedScratcherControl_3;
        scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_17, false);
    }
}

void Ai_HangedScratcher_Control_2(s_SubCharacter* chara)
{
    q19_12 distToPlayer;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - chara->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - chara->position_18.vz);

    Chara_MoveSpeedUpdate(chara, Q12(4.0f));

    if (distToPlayer < Q12(5.0f) || (distToPlayer < Q12(20.0f) && Rng_Rand16() == 0))
    {
        chara->model_0.controlState_2  = HangedScratcherControl_3;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_17, false);
    }
}

void Ai_HangedScratcher_Control_3(s_SubCharacter* scratcher)
{
    q19_12 distToPlayer;
    q3_12  angleDeltaToPlayer;
    q3_12  targetRotDelta;
    q19_12 playerPosYDelta;

    distToPlayer       = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       scratcher->rotation_24.vy);
    angleDeltaToPlayer = ABS(angleDeltaToPlayer);

    if (angleDeltaToPlayer < TIMESTEP_ANGLE(1, 2))
    {
        Chara_MoveSpeedUpdate4(scratcher, Q12(4.0f), scratcherProps.radiusMax_10C);

        scratcherProps.timer_EA = Q12(0.0f);
    }
    else
    {
        if (angleDeltaToPlayer < Q12_ANGLE(60.0f) && distToPlayer > Q12(2.0f))
        {
            Chara_MoveSpeedUpdate4(scratcher, Q12(4.0f), scratcherProps.radiusMax_10C);
        }
        else if (angleDeltaToPlayer < Q12_ANGLE(120.0f) && distToPlayer > Q12(4.0f))
        {
            Chara_MoveSpeedUpdate4(scratcher, Q12(4.0f), scratcherProps.radiusMax_10C / 2);
        }
        else
        {
            Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));
        }

        scratcherProps.timer_EA += g_DeltaTime;
        if (distToPlayer > Q12(7.5f) && scratcherProps.timer_EA > Q12(1.8f))
        {
            scratcherProps.targetHeadingAngle_EC = Chara_HeadingAngleGet(scratcher,
                                                                         Q12(5.0f),
                                                                         g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                                         g_SysWork.playerWork_4C.player_0.position_18.vz,
                                                                         Q12_ANGLE(360.0f),
                                                                         true);
            if (scratcherProps.targetHeadingAngle_EC == Q12_ANGLE(360.0f))
            {
                scratcherProps.targetHeadingAngle_EC = scratcher->rotation_24.vy;
            }

            scratcherProps.timer_EA = Q12(0.0f);
        }
        else if (distToPlayer > Q12(3.0f) && scratcherProps.timer_EA > Q12(0.6f))
        {
            scratcherProps.targetHeadingAngle_EC = Chara_HeadingAngleGet(scratcher,
                                                                         Q12(1.5f),
                                                                         g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                                         g_SysWork.playerWork_4C.player_0.position_18.vz,
                                                                         Q12_ANGLE(360.0f),
                                                                         true);
            if (scratcherProps.targetHeadingAngle_EC == Q12_ANGLE(360.0f))
            {
                scratcherProps.targetHeadingAngle_EC = scratcher->rotation_24.vy;
            }

            scratcherProps.timer_EA = Q12(0.0f);
        }
        else
        {
            scratcherProps.targetHeadingAngle_EC = Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18);
            scratcherProps.timer_EA              = Q12(0.0f);
        }

        targetRotDelta = func_8005BF38(scratcherProps.targetHeadingAngle_EC - scratcher->rotation_24.vy);
        if (ABS(targetRotDelta) > TIMESTEP_ANGLE(1, 2))
        {
            if (targetRotDelta > Q12_ANGLE(0.0f))
            {
                scratcher->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.5f));
            }
            else
            {
                scratcher->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.5f));
            }
        }
    }

    if (sharedFunc_800D3214_5_s00(scratcher))
    {
        scratcher->model_0.controlState_2  = HangedScratcherControl_8;
        scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_16, false);
        scratcher->moveSpeed_38            = Q12(0.0f);

        scratcherProps.flags_E8 |= HangedScratcherFlag_1;
    }
    else
    {
        if (!Chara_HasFlag(&g_SysWork.playerWork_4C.player_0, 8) && !(g_SysWork.field_2284[3] & (1 << 1)))
        {
            if (g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f) &&
                distToPlayer < Q12(1.0f) && angleDeltaToPlayer < Q12_ANGLE(30.0f))
            {
                playerPosYDelta = scratcher->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy;
                if (playerPosYDelta < Q12(-3.5f))
                {
                    if (playerPosYDelta > Q12(-3.7f))
                    {
                        scratcher->model_0.controlState_2  = HangedScratcherControl_4;
                        scratcherProps.timer_EA            = Q12(0.0f);
                        scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_4, false);
                        g_SysWork.field_2284[3]           |= HangedScratcherFlag_1;
                        return;
                    }
                }
            }
        }

        if (distToPlayer > Q12(20.0f) && !Rng_GenerateInt(0, 31)) // 1 in 32 chance.
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_2;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_14, false);
        }
    }
}

void Ai_HangedScratcher_Control_4(s_SubCharacter* scratcher)
{
    VECTOR3 attackPos; // Q19.12
    q19_12  distToPlayer;
    q3_12   angleDeltaToPlayer;
    q3_12   angleDeltaToPlayerAbs;

    distToPlayer          = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                                g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
    angleDeltaToPlayer    = func_8005BF38(Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                          scratcher->rotation_24.vy);
    angleDeltaToPlayerAbs = ABS(angleDeltaToPlayer);

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 98, 103))
    {
        if (angleDeltaToPlayerAbs > TIMESTEP_ANGLE(1, 2))
        {
            if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
            {
                scratcher->rotation_24.vy += Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.5f);
            }
            else
            {
                scratcher->rotation_24.vy -= Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.5f);
            }
        }

        if (distToPlayer > Q12(0.2f))
        {
            scratcher->moveSpeed_38 = Q12(1.0f);
        }
        else
        {
            scratcher->moveSpeed_38 = Q12(0.0f);
        }

        scratcher->field_44.field_0 = 1;
    }
    else
    {
        scratcher->moveSpeed_38 = Q12(0.0f);

        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 104, 105))
        {
            attackPos.vx             = scratcher->position_18.vx;
            attackPos.vy             = Q12(-1.45f);
            attackPos.vz             = scratcher->position_18.vz;
            scratcherProps.flags_E8 |= HangedScratcherFlag_5;

            // TODO: 44 is `WEAPON_ATTACK`?
            func_8008A0E4(1, 44, scratcher, &attackPos, &g_SysWork.playerWork_4C.player_0, scratcher->rotation_24.vy,
                          ratan2(distToPlayer, (g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_6) - attackPos.vy));
        }
        else if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == HangedScratcherAnim_14)
        {
            if (distToPlayer > Q12(6.0f) && !Rng_GenerateInt(0, 15)) // 1 in 16 chance.
            {
                scratcher->model_0.controlState_2  = HangedScratcherControl_3;
                scratcherProps.timer_EA            = Q12(0.0f);
                scratcher->model_0.anim_4.status_0 = ANIM_STATUS(17, false);
                g_SysWork.field_2284[3]           &= ~(1 << 1);
            }
            else
            {
                scratcherProps.timer_EA += g_DeltaTime;

                if (scratcherProps.timer_EA > Q12(3.0f) && !Rng_GenerateInt(0, 7))
                {
                    scratcherProps.timer_EA           = Q12(0.0f);
                    scratcher->model_0.controlState_2 = HangedScratcherControl_2;
                    g_SysWork.field_2284[3]          &= ~(1 << 1);
                }
            }
        }
    }
}

void Ai_HangedScratcher_Control_5(s_SubCharacter* scratcher)
{
    if (Vw_AabbVisibleInScreenCheck(MIN_OFFSET(scratcher->position_18.vx, Q12(0.5f), Q12(0.5f)),
                                    MAX_OFFSET(scratcher->position_18.vx, Q12(0.5f), Q12(0.5f)),
                                    MIN_OFFSET(scratcher->position_18.vy, Q12(1.0f), Q12(0.0f)),
                                    MAX_OFFSET(scratcher->position_18.vy, Q12(1.0f), Q12(0.0f)),
                                    MIN_OFFSET(scratcher->position_18.vz, Q12(0.5f), Q12(0.5f)),
                                    MAX_OFFSET(scratcher->position_18.vz, Q12(0.5f), Q12(0.5f))) ||
        Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                            g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) < Q12(1.0f))
    {
        if (func_800700F8(scratcher, &g_SysWork.playerWork_4C.player_0))
        {
            return;
        }

        if (((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3) == 0x2 && func_8006FD90(scratcher, 1, Q12(1.5f), Q12(0.5f))) ||
            (((u8)g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x2) &&
             ((u8)g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x1) && func_8006FD90(scratcher, 1, Q12(1.2f), Q12(0.3f))))
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_7;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_18, false);
        }
    }
}

void Ai_HangedScratcher_Control_6(s_SubCharacter* scratcher)
{
    q19_12 distToPlayer;
    u16    temp_v1;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);

    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (scratcherProps.timer_EA == Q12(0.0f) &&
        scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_15, true))
    {
        if (distToPlayer < Q12(12.0f) && !Rng_GenerateInt(0, 127)) // 1 in 128 chance.
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_7;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_18, false);
        }
        else if (distToPlayer < Q12(6.0f) && !Rng_GenerateInt(0, 15)) // 1 in 16 chance.
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_7;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_18, false);
        }
    }

    // @bug Weird function pointer check, code will never run?
    if (&sharedFunc_800D3214_5_s00 == NULL && distToPlayer > Q12(24.0f))
    {
        scratcher->model_0.controlState_2 = HangedScratcherControl_None;
        scratcher->model_0.stateStep_3    = 3;
    }

    temp_v1                 = scratcherProps.timer_EA;
    scratcherProps.timer_EA = MAX(Q12(0.0f), temp_v1 - g_DeltaTime);
}

void Ai_HangedScratcher_Control_7(s_SubCharacter* scratcher)
{
    q19_12 distToPlayer;
    q3_12  angleDeltaToPlayer;
    q3_12  angleDeltaToPlayerAbs;
    q19_12 angleToPlayer;
    bool   cond;
    q3_12  targetRotDelta;

    distToPlayer          = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                                g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
    angleDeltaToPlayer    = func_8005BF38(Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                          scratcher->rotation_24.vy);
    angleDeltaToPlayerAbs = ABS(angleDeltaToPlayer);
    angleToPlayer         = Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18);

    if (distToPlayer > Q12(16.0f))
    {
        scratcher->model_0.controlState_2  = HangedScratcherControl_6;
        scratcherProps.timer_EA            = Q12(0.5f);
        scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_15, false);
        scratcherProps.field_EE            = 37;
        return;
    }

    cond = func_800700F8(scratcher, &g_SysWork.playerWork_4C.player_0);

    if (angleDeltaToPlayerAbs < TIMESTEP_ANGLE(1, 3) && !cond)
    {
        Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcherProps.radiusMin_10E);
        scratcherProps.timer_EA = Q12(0.0f);
    }
    else
    {
        if (!cond)
        {
            if (angleDeltaToPlayerAbs < Q12_ANGLE(45.0f) && distToPlayer > Q12(2.0f))
            {
                Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcherProps.radiusMin_10E);
            }
            else if (angleDeltaToPlayerAbs < Q12_ANGLE(90.0f) && distToPlayer > Q12(4.0f))
            {
                Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcherProps.radiusMin_10E / 2);
            }
            else
            {
                Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));
            }
        }
        else
        {
            Chara_MoveSpeedUpdate4(scratcher, Q12(2.0f), scratcherProps.radiusMin_10E);
        }

        scratcherProps.timer_EA += g_DeltaTime;

        if (distToPlayer < Q12(2.0f) && !cond)
        {
            scratcherProps.timer_EA              = Q12(0.0f);
            scratcherProps.targetHeadingAngle_EC = angleToPlayer;
        }
        else if (scratcherProps.timer_EA > Q12(0.6f) ||
                 (scratcherProps.timer_EA > Q12(0.3f) &&
                  cond && !Rng_GenerateInt(0, 7))) // 1 in 8 chance.
        {
            scratcherProps.timer_EA = Q12(0.0f);

            scratcherProps.targetHeadingAngle_EC = Chara_HeadingAngleGet(scratcher, Q12(1.0f), g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz, Q12_ANGLE(360.0f), true);
            if (scratcherProps.targetHeadingAngle_EC == Q12_ANGLE(360.0f))
            {
                scratcherProps.targetHeadingAngle_EC = scratcher->rotation_24.vy - Q12_ANGLE(180.0f);
            }
        }

        targetRotDelta = func_8005BF38(scratcherProps.targetHeadingAngle_EC - scratcher->rotation_24.vy);
        if (ABS(targetRotDelta) > TIMESTEP_ANGLE(1, 3))
        {
            if (targetRotDelta > Q12_ANGLE(0.0f))
            {
                scratcher->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
            else
            {
                scratcher->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
        }
        else
        {
            scratcher->rotation_24.vy = scratcherProps.targetHeadingAngle_EC;
        }
    }

    if (!cond && !(g_SysWork.field_2284[3] & 2) && !(g_SysWork.playerWork_4C.player_0.flags_3E & CharaFlag_Unk4) &&
        g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
    {
        if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) < Q12(1.2f))
        {
            if (ABS(func_8005BF38(Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                  scratcher->rotation_24.vy)) < Q12_ANGLE(20.0f))
            {
                scratcher->model_0.controlState_2  = HangedScratcherControl_15;
                g_SysWork.field_2284[3]           |= 1 << 1;
                scratcherProps.timer_EA            = Q12(0.0f);
                scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_5, false);
            }
        }
    }
}

void Ai_HangedScratcher_Control_8(s_SubCharacter* scratcher)
{
    if (scratcherProps.flags_E8 & HangedScratcherFlag_0)
    {
        scratcher->fallSpeed_34 += g_GravitySpeed >> 1;

        if (FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT) == 259)
        {
            sharedData_800DE28C_5_s00 = Q12(0.0f);
        }
        else
        {
            sharedData_800DE28C_5_s00 = Q12(15.0f);
        }
    }
    else
    {
        sharedData_800DE28C_5_s00 = Q12(12.0f);
    }

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 245, 256))
    {
        scratcher->rotation_24.vz = MAX(Q12(0.0f), scratcher->rotation_24.vz - TIMESTEP_SCALE_60_FPS(g_DeltaTime, 45));
    }

    if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == HangedScratcherAnim_15)
    {
        scratcher->moveSpeed_38 = Q12(0.0f);

        if (scratcher->health_B0 > Q12(100.0f))
        {
            scratcher->model_0.controlState_2 = HangedScratcherControl_6;
            scratcherProps.timer_EA           = Q12(0.5f);
        }
        else
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_12;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_11, false);
            scratcherProps.field_EE            = 31;
        }
    }
}

void Ai_HangedScratcher_Control_9(s_SubCharacter* scratcher)
{
    s_Collision coll;

    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == HangedScratcherAnim_14 &&
        scratcher->moveSpeed_38 == Q12(0.0f))
    {
        Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);
        if (scratcher->health_B0 > Q12(100.0f) || coll.field_8 == 7)
        {
            if (scratcherProps.flags_E8 & HangedScratcherFlag_1)
            {
                scratcher->model_0.controlState_2  = HangedScratcherControl_8;
                scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_16, false);
            }
            else if (!Rng_GenerateInt(0, 7)) // 1 in 8 chance.
            {
                scratcher->model_0.controlState_2  = HangedScratcherControl_3;
                scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_17, false);
            }
        }
        else
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_11;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_10, false);
        }
    }
}

void Ai_HangedScratcher_Control_10(s_SubCharacter* scratcher)
{
    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == HangedScratcherAnim_15 &&
        scratcher->moveSpeed_38 == Q12(0.0f) &&
        Rng_GenerateInt(0, 7) == 0) // 1 in 8 chance.
    {
        scratcher->model_0.controlState_2  = HangedScratcherControl_7;
        scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_18, false);
    }
}

void Ai_HangedScratcher_Control_11(s_SubCharacter* scratcher)
{
    if (scratcherProps.flags_E8 & HangedScratcherFlag_0)
    {
        scratcher->fallSpeed_34 += g_GravitySpeed >> 1;

        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 176, 184))
        {
            sharedData_800DE28C_5_s00 = Q12(10.0f);
        }
        else
        {
            sharedData_800DE28C_5_s00 = Q12(0.0f);
        }
    }
    else
    {
        Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

        if (ANIM_STATUS_IDX_GET(scratcher->model_0.anim_4.status_0) == HangedScratcherAnim_10)
        {
            if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 176, 185))
            {
                scratcher->model_0.anim_4.time_4        = Q12(186.0f);
                scratcher->model_0.anim_4.keyframeIdx_8 = 186;
            }

            sharedData_800DE28C_5_s00 = Q12(8.0f);
        }
    }

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 191, 193))
    {
        Character_AnimSet(scratcher, ANIM_STATUS(HangedScratcherAnim_12, true), 202);
        scratcher->rotation_24.vz = Q12_ANGLE(0.0f);
        return;
    }

    if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_12, true))
    {
        scratcher->flags_3E |= CharaFlag_Unk2;

        if (scratcher->health_B0 <= Q12(0.0f))
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_13;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_6, false);
        }
    }
}

void Ai_HangedScratcher_Control_12(s_SubCharacter* scratcher)
{
    q19_12 animDur;
    q19_12 animDurScaled;

    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 192, 199))
    {
        animDur       = HANGED_SCRATCHER_ANIM_INFOS[scratcher->model_0.anim_4.status_0].duration_8.constant;
        animDurScaled = (Q12_MULT_PRECISE(animDur, g_DeltaTime) * Q12(0.7f)) / Q12(7.0f);

        scratcherProps.offsetX_F0 += FP_FROM(animDurScaled * Math_Sin(scratcher->rotation_24.vy), Q12_SHIFT);
        scratcherProps.offsetZ_F2 += FP_FROM(animDurScaled * Math_Cos(scratcher->rotation_24.vy), Q12_SHIFT);
    }

    if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_13, true))
    {
        scratcher->flags_3E |= CharaFlag_Unk2;

        if (scratcher->health_B0 <= Q12(0.0f))
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_13;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_7, false);
        }
    }
}

void Ai_HangedScratcher_Control_13(s_SubCharacter* scratcher)
{
    Chara_MoveSpeedUpdate(scratcher, Q12(4.0f));

    if (scratcher->health_B0 == Q12(0.0f))
    {
        if (g_SysWork.targetNpcIdx_2353 != Chara_NpcIdxGet(scratcher))
        {
            scratcher->health_B0     = NO_VALUE;
            scratcher->flags_3E     &= ~CharaFlag_Unk2;
            scratcher->field_E1_0    = 0;
            scratcherProps.flags_E8 |= HangedScratcherFlag_9;
        }
    }

    // TODO: Weird 32-bit flags access, maybe `if` is checking both `flags_E8` and `field_EA`?
    if (scratcher->moveSpeed_38 == Q12(0.0f) &&
        !(*(u32*)&scratcherProps.flags_E8 & (HangedScratcherFlag_0 | HangedScratcherFlag_2)))
    {
        func_800622B8(3, scratcher, ANIM_STATUS(HangedScratcherAnim_4, false), 8);
        scratcherProps.flags_E8 |= HangedScratcherFlag_2;
        Savegame_EnemyStateUpdate(scratcher);
    }
}

void Ai_HangedScratcher_Control_14(s_SubCharacter* scratcher)
{
    s_Collision coll;
    VECTOR3     sfxPos;

    if ((scratcherProps.flags_E8 & HangedScratcherFlag_7) &&
        scratcher->model_0.anim_4.status_0 < ANIM_STATUS(HangedScratcherAnim_4, false))
    {
        HANGED_SCRATCHER_ANIM_INFOS[scratcher->model_0.anim_4.status_0].duration_8.constant = Q12(9.6f);
    }
    else
    {
        HANGED_SCRATCHER_ANIM_INFOS[scratcher->model_0.anim_4.status_0].duration_8.constant = Q12(0.0f);
    }

    if (FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT) == 51)
    {
        scratcher->model_0.anim_4.flags_2 &= ~AnimFlag_Visible;
    }
    else
    {
        scratcher->model_0.anim_4.flags_2 |= AnimFlag_Visible;
    }

    if (!(scratcherProps.flags_E8 & HangedScratcherFlag_6))
    {
        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 42, 44))
        {
            scratcherProps.flags_E8 |= HangedScratcherFlag_6;

            Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);
            if (coll.field_8 == 11)
            {
                func_8005DC1C(Sfx_Unk1582, &scratcher->position_18, Q8(0.5f), 0);
            }
            else
            {
                func_8005DC1C(Sfx_Unk1581, &scratcher->position_18, Q8(0.5f), 0);
            }
        }

        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 84, 86))
        {
            scratcherProps.flags_E8 |= HangedScratcherFlag_6;

            sfxPos.vx = scratcher->position_18.vx;
            sfxPos.vy = scratcher->position_18.vy;
            sfxPos.vz = scratcher->position_18.vz + Q12(0.6f);

            Collision_Get(&coll, sfxPos.vx, sfxPos.vz);
            if (coll.field_8 == 11)
            {
                func_8005DC1C(Sfx_Unk1582, &sfxPos, Q8(0.5f), 0);
            }
            else
            {
                func_8005DC1C(Sfx_Unk1581, &sfxPos, Q8(0.5f), 0);
            }
        }

        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 94, 96))
        {
            scratcherProps.flags_E8 |= HangedScratcherFlag_6;

            sfxPos.vx = scratcher->position_18.vx;
            sfxPos.vy = scratcher->position_18.vy;
            sfxPos.vz = scratcher->position_18.vz - Q12(1.0f);

            Collision_Get(&coll, sfxPos.vx, sfxPos.vz);
            if (coll.field_8 == 11)
            {
                func_8005DC1C(Sfx_Unk1582, &sfxPos, Q8(0.5f), 0);
            }
            else
            {
                func_8005DC1C(Sfx_Unk1581, &sfxPos, Q8(0.5f), 0);
            }
        }
    }

    if (!(scratcherProps.flags_E8 & HangedScratcherFlag_8) &&
        ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 52, 54))
    {
        scratcherProps.flags_E8 |= HangedScratcherFlag_8;

        sfxPos.vx = scratcher->position_18.vx;
        sfxPos.vy = scratcher->position_18.vy + Q12(0.5f);
        sfxPos.vz = scratcher->position_18.vz + Q12(1.5f);
        func_8005DC1C(Sfx_Unk1577, &sfxPos, Q8(0.5f), 0);
    }
}

void Ai_HangedScratcher_Control_15(s_SubCharacter* scratcher)
{
    VECTOR3 attackPos;
    q19_12  distToPlayer;
    q3_12   angleDeltaToPlayer;

    distToPlayer       = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(scratcher->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       scratcher->rotation_24.vy);

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 116, 123) &&
        distToPlayer > Q12(1.0f) && angleDeltaToPlayer < Q12_ANGLE(20.0f))
    {
        scratcher->moveSpeed_38 = Q12(1.0f);
    }
    else
    {
        scratcher->moveSpeed_38 = Q12(0.0f);
    }

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 116, 128))
    {
        if (ABS(angleDeltaToPlayer) > TIMESTEP_ANGLE(1, 4))
        {
            if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
            {
                scratcher->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.125f));
            }
            else
            {
                scratcher->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.125f));
            }
        }
        else
        {
            scratcher->rotation_24.vy = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                               g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz);
        }
    }

    if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 124, 130))
    {
        if (scratcher->field_44.field_0 == 0)
        {
            scratcher->field_44.field_0 = 1;
        }

        attackPos.vx = scratcher->position_18.vx;
        attackPos.vy = scratcher->position_18.vy - Q12(0.8f);
        attackPos.vz = scratcher->position_18.vz;

        scratcherProps.flags_E8 |= HangedScratcherFlag_5;

        // TODO: 45 is `WEAPON_ATTACK`?
        func_8008A0E4(1, 45, scratcher, &attackPos, &g_SysWork.playerWork_4C.player_0, scratcher->rotation_24.vy, Q12_ANGLE(90.0f));
    }

    if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_15, true))
    {
        if (scratcherProps.timer_EA == Q12(0.0f))
        {
            g_SysWork.field_2284[3] &= ~(1 << 1);
        }

        scratcherProps.timer_EA += g_DeltaTime;

        if (scratcherProps.timer_EA > Q12(2.5f) ||
            (scratcherProps.timer_EA > Q12(0.8f) &&
             !Rng_GenerateInt(0, 31))) // 1 in 32 chance.
        {
            scratcher->model_0.controlState_2  = HangedScratcherControl_7;
            scratcher->model_0.anim_4.status_0 = ANIM_STATUS(HangedScratcherAnim_18, false);
        }
    }
    else
    {
        scratcherProps.timer_EA = Q12(0.0f);
    }
}

void sharedFunc_800D26D8_5_s00(s_SubCharacter* scratcher)
{
    s_800C4590  sp10;
    s_Collision coll;
    u8          flag1Val;

    scratcher->rotation_24.vy  = func_8005BF38(scratcher->rotation_24.vy);
    scratcher->headingAngle_3C = scratcher->rotation_24.vy;

    switch (scratcher->model_0.controlState_2)
    {
        case HangedScratcherControl_5:
        case HangedScratcherControl_6:
        case HangedScratcherControl_7:
        case HangedScratcherControl_10:
        case HangedScratcherControl_12:
        case HangedScratcherControl_13:
            scratcher->fallSpeed_34 += g_GravitySpeed;
            break;
    }

    func_8005CB20(scratcher, &sp10, scratcherProps.offsetX_F0, scratcherProps.offsetZ_F2);

    scratcherProps.offsetZ_F2 = Q12(0.0f);
    scratcherProps.offsetX_F0 = Q12(0.0f);

    flag1Val = scratcherProps.flags_E8 & HangedScratcherFlag_0;

    if (scratcher->position_18.vy == sp10.field_C)
    {
        scratcherProps.flags_E8 &= ~HangedScratcherFlag_0;

        if (flag1Val)
        {
            if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_10, true))
            {
                Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);
                if (coll.field_8 == 11)
                {
                    func_8005DC1C(Sfx_Unk1582, &scratcher->position_18, Q8(0.5f), 0);
                }
                else
                {
                    func_8005DC1C(Sfx_Unk1581, &scratcher->position_18, Q8(0.5f), 0);
                }
            }
            else if (scratcher->model_0.anim_4.status_0 == ANIM_STATUS(HangedScratcherAnim_16, true))
            {
                Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);
                if (coll.field_8 == 11)
                {
                    func_8005DC1C(Sfx_Unk1582, &scratcher->position_18, Q8(0.25f), 0);
                }
                else
                {
                    func_8005DC1C(Sfx_Unk1581, &scratcher->position_18, Q8(0.25f), 0);
                }
            }
        }
    }
    else
    {
        scratcherProps.flags_E8 |= HangedScratcherFlag_0;
    }
}

void sharedFunc_800D2844_5_s00(s_SubCharacter* scratcher, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;
    q19_12      newAnimDur;

#define curAnimInfo HANGED_SCRATCHER_ANIM_INFOS[scratcher->model_0.anim_4.status_0]

    scratcher->rotation_24.vy = func_8005BF38(scratcher->rotation_24.vy);

    switch (scratcher->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(HangedScratcherAnim_4, true):
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
            {
                curAnimInfo.duration_8.constant = Q12(19.5f);
            }
            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
            {
                curAnimInfo.duration_8.constant = Q12(19.5f);
            }
            else
            {
                curAnimInfo.duration_8.constant = Q12(26.0f);
            }
            break;

        case ANIM_STATUS(HangedScratcherAnim_5, false):
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
            {
                curAnimInfo.duration_8.constant = Q12(12.0f);
            }
            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
            {
                curAnimInfo.duration_8.constant = Q12(8.0f);
            }
            else
            {
                curAnimInfo.duration_8.constant = Q12(18.0f);
            }
            break;

        case ANIM_STATUS(HangedScratcherAnim_5, true):
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
            {
                curAnimInfo.duration_8.constant = Q12(23.0f);
            }
            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
            {
                curAnimInfo.duration_8.constant = Q12(15.0f);
            }
            else
            {
                curAnimInfo.duration_8.constant = Q12(34.0f);
            }
            break;

        case ANIM_STATUS(HangedScratcherAnim_9, true):
            if (FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT) != 173)
            {
                curAnimInfo.duration_8.constant = Q12(12.0f);
                break;
            }

            curAnimInfo.duration_8.constant = Q12(4.5f);
            break;

        case ANIM_STATUS(HangedScratcherAnim_23, true):
            if (FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT) == 173)
            {
                curAnimInfo.duration_8.constant = Q12(3.0f);
            }
            else
            {
                curAnimInfo.duration_8.constant = Q12(9.0f);
            }
            break;

        case ANIM_STATUS(HangedScratcherAnim_11, true):
            if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 192, 193))
            {
                curAnimInfo.duration_8.constant = Q12(2.5f);
            }
            else
            {
                curAnimInfo.duration_8.constant = Q12(4.5f);
            }
            break;

        case ANIM_STATUS(HangedScratcherAnim_10, true):
        case ANIM_STATUS(HangedScratcherAnim_16, true):
            curAnimInfo.duration_8.constant = sharedData_800DE28C_5_s00;
            break;

        case ANIM_STATUS(HangedScratcherAnim_14, true):
        case ANIM_STATUS(HangedScratcherAnim_15, true):
            switch (scratcher->model_0.controlState_2)
            {
                case 1:
                    curAnimInfo.duration_8.constant = Q12(1.2f);
                    break;

                case 5:
                    curAnimInfo.duration_8.constant = Q12(2.4f);
                    break;

                default:
                    curAnimInfo.duration_8.constant = Q12(3.5f);
                    break;
            }
            break;

        case ANIM_STATUS(HangedScratcherAnim_17, true):
            curAnimInfo.duration_8.constant = MAX(Q12(2.0f), Q12_MULT_PRECISE(scratcher->moveSpeed_38, Q12(4.4f)));
            break;

        case ANIM_STATUS(HangedScratcherAnim_18, true):
            newAnimDur = Q12_MULT_PRECISE(scratcher->moveSpeed_38, Q12(6.0f));
            if (scratcher->rotation_24.vy != scratcherProps.field_FC)
            {
                newAnimDur = MAX(Q12(9.0f), newAnimDur);
            }

            curAnimInfo.duration_8.constant = newAnimDur;
            break;
    }

    Math_MatrixTransform(&scratcher->position_18, &scratcher->rotation_24, coords);

    animInfo = &curAnimInfo;
    animInfo->updateFunc_0(&scratcher->model_0, anmHdr, coords, animInfo);
    scratcherProps.field_FC = scratcher->rotation_24.vy;

#undef curAnimInfo
}

// Likely internal to this func, can keep in .c instead of .h.
extern s_Keyframe sharedData_800D9500_5_s00[];
extern s_Keyframe sharedData_800D9654_5_s00;
extern s_Keyframe sharedData_800D9668_5_s00;
extern s_Keyframe sharedData_800D967C_5_s00[];
extern s_Keyframe sharedData_800D96F4_5_s00;
extern s_Keyframe sharedData_800D9708_5_s00[];
extern s_Keyframe sharedData_800D97F8_5_s00;
extern s_Keyframe sharedData_800D980C_5_s00;
extern s_Keyframe sharedData_800D9820_5_s00[];
extern s_Keyframe sharedData_800D99D8_5_s00;
extern s_Keyframe sharedData_800D99EC_5_s00;
extern s_Keyframe sharedData_800D9A00_5_s00[];
extern s_Keyframe sharedData_800D9A64_5_s00;
extern s_Keyframe sharedData_800D9A78_5_s00[];
extern s_Keyframe sharedData_800D9AF0_5_s00;
extern s_Keyframe sharedData_800D9B04_5_s00;
extern s_Keyframe sharedData_800D9B18_5_s00;
extern s_Keyframe sharedData_800D9B2C_5_s00[];

#define CopyData(arg0, data)                  \
{                                             \
    s32 __temp;                               \
                                              \
    arg0->field_C8.field_0 = data.field_0;    \
                                              \
    __temp                 = data.field_2;    \
    arg0->field_C8.field_2 = __temp;          \
    arg0->field_C8.field_4 = data.field_4;    \
                                              \
    __temp                   = data.field_6;  \
    arg0->field_C8.field_6   = __temp;        \
    arg0->field_D8.offsetX_4 = data.field_10; \
                                              \
    __temp                   = data.field_12; \
    arg0->field_D8.offsetZ_6 = __temp;        \
    arg0->field_D4.radius_0  = data.field_8;  \
    arg0->field_D8.offsetX_0 = data.field_C;  \
                                              \
    __temp                   = data.field_E;  \
    arg0->field_D8.offsetZ_2 = __temp;        \
                                              \
    __temp                 = data.field_A;    \
    arg0->field_D4.field_2 = __temp;          \
}

void sharedFunc_800D2C18_5_s00(s_SubCharacter* scratcher)
{
    s32 relKeyframeIdx;
    s32 keyframeIdx0;
    s32 keyframeIdx1;

    #define animKeyframeIdx FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT)

    // Handle animation status.
    switch (scratcher->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(HangedScratcherAnim_4, false):
            func_80070400(scratcher, &sharedData_800D980C_5_s00, sharedData_800D9500_5_s00);
            break;

        case ANIM_STATUS(HangedScratcherAnim_4, true):
            scratcherProps.field_EE = 9;

            relKeyframeIdx = animKeyframeIdx - 98;
            func_80070400(scratcher, &sharedData_800D9500_5_s00[relKeyframeIdx], &sharedData_800D9500_5_s00[relKeyframeIdx + 1]);
            break;

        case ANIM_STATUS(HangedScratcherAnim_10, false):
            func_80070400(scratcher, &sharedData_800D980C_5_s00, sharedData_800D9708_5_s00);
            break;

        case ANIM_STATUS(HangedScratcherAnim_10, true):
            scratcherProps.field_EE = 21;

            relKeyframeIdx = animKeyframeIdx - 176;
            keyframeIdx0   = relKeyframeIdx - ((relKeyframeIdx >= 12) ? 1 : 0) - ((relKeyframeIdx >= 14) ? 1 : 0);
            keyframeIdx1   = (relKeyframeIdx + 1) - ((relKeyframeIdx >= 11) ? 1 : 0) - ((relKeyframeIdx >= 13) ? 1 : 0) - ((relKeyframeIdx >= 14) ? 1 : 0);

            func_80070400(scratcher, &sharedData_800D9708_5_s00[keyframeIdx0], &sharedData_800D9708_5_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(HangedScratcherAnim_12, false):
            if (scratcherProps.field_EE == 21)
            {
                func_80070400(scratcher, &sharedData_800D97F8_5_s00, &sharedData_800D9668_5_s00);
            }
            else
            {
                CopyData(scratcher, sharedData_800D9668_5_s00);
            }
            break;

        case ANIM_STATUS(HangedScratcherAnim_21, true):
            scratcherProps.field_EE = 43;

        case ANIM_STATUS(HangedScratcherAnim_6, false):
        case ANIM_STATUS(HangedScratcherAnim_6, true):
        case ANIM_STATUS(HangedScratcherAnim_12, true):
        case ANIM_STATUS(HangedScratcherAnim_19, false):
        case ANIM_STATUS(HangedScratcherAnim_19, true):
        case ANIM_STATUS(HangedScratcherAnim_21, false):
            CopyData(scratcher, sharedData_800D9668_5_s00);
            break;

        case ANIM_STATUS(HangedScratcherAnim_8, false):
            CopyData(scratcher, sharedData_800D967C_5_s00[0]);
            break;

        case ANIM_STATUS(HangedScratcherAnim_8, true):
            scratcherProps.field_EE = 17;

            relKeyframeIdx = animKeyframeIdx - 154;

            // TODO: Could these `if`s be flattened?
            if (relKeyframeIdx < 7)
            {
                if (relKeyframeIdx < 3)
                {
                    keyframeIdx0 = (relKeyframeIdx == 2 ? 1 : 0);
                }
                else
                {
                    keyframeIdx0 = 2;
                }
            }
            else
            {
                keyframeIdx0 = animKeyframeIdx - 158;
            }

            if (relKeyframeIdx < 6)
            {
                if (relKeyframeIdx >= 3)
                {
                    keyframeIdx1 = 2;
                }
                else
                {
                    keyframeIdx1 = relKeyframeIdx;
                }
            }
            else
            {
                keyframeIdx1 = (relKeyframeIdx - 3) - ((relKeyframeIdx == 10) ? 1 : 0);
            }

            func_80070400(scratcher, &sharedData_800D967C_5_s00[keyframeIdx0], &sharedData_800D967C_5_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(HangedScratcherAnim_14, false):
            if (scratcherProps.field_EE == 9)
            {
                func_80070400(scratcher, &sharedData_800D9654_5_s00, &sharedData_800D980C_5_s00);
            }
            else if (scratcherProps.field_EE == 17)
            {
                func_80070400(scratcher, &sharedData_800D96F4_5_s00, &sharedData_800D980C_5_s00);
            }
            else
            {
                CopyData(scratcher, sharedData_800D980C_5_s00);
            }
            break;

        case ANIM_STATUS(HangedScratcherAnim_17, true):
            scratcherProps.field_EE = 35;

        case ANIM_STATUS(HangedScratcherAnim_14, true):
        case ANIM_STATUS(HangedScratcherAnim_17, false):
            CopyData(scratcher, sharedData_800D980C_5_s00);
            break;

        case ANIM_STATUS(HangedScratcherAnim_16, false):
            func_80070400(scratcher, &sharedData_800D980C_5_s00, sharedData_800D9820_5_s00);
            break;

        case ANIM_STATUS(HangedScratcherAnim_16, true):
            scratcherProps.field_EE = 33;

            relKeyframeIdx = animKeyframeIdx - 244;
            func_80070400(scratcher, &sharedData_800D9820_5_s00[relKeyframeIdx], &sharedData_800D9820_5_s00[relKeyframeIdx + 1]);
            break;

        case ANIM_STATUS(HangedScratcherAnim_13, false):
            if (scratcherProps.field_EE == 23)
            {
                func_80070400(scratcher, &sharedData_800D9AF0_5_s00, &sharedData_800D99EC_5_s00);
            }
            else
            {
                CopyData(scratcher, sharedData_800D99EC_5_s00);
            }
            break;

        case ANIM_STATUS(HangedScratcherAnim_22, true):
            scratcherProps.field_EE = 45;

        case ANIM_STATUS(HangedScratcherAnim_7, false):
        case ANIM_STATUS(HangedScratcherAnim_7, true):
        case ANIM_STATUS(HangedScratcherAnim_13, true):
        case ANIM_STATUS(HangedScratcherAnim_20, false):
        case ANIM_STATUS(HangedScratcherAnim_20, true):
        case ANIM_STATUS(HangedScratcherAnim_22, false):
            CopyData(scratcher, sharedData_800D99EC_5_s00);
            break;

        case ANIM_STATUS(HangedScratcherAnim_9, false):
        case ANIM_STATUS(HangedScratcherAnim_23, false):
            CopyData(scratcher, sharedData_800D9A00_5_s00[0]);
            break;

        case ANIM_STATUS(HangedScratcherAnim_9, true):
        case ANIM_STATUS(HangedScratcherAnim_23, true):
            scratcherProps.field_EE = 19;

            relKeyframeIdx = animKeyframeIdx - 166;
            keyframeIdx0   = relKeyframeIdx - ((relKeyframeIdx > 0) ? 1 : 0) - ((relKeyframeIdx >= 4) ? 1 : 0) - ((relKeyframeIdx >= 5) ? 1 : 0);
            keyframeIdx1   = relKeyframeIdx - ((relKeyframeIdx >= 3) ? 1 : 0) - ((relKeyframeIdx >= 4) ? 1 : 0) - ((relKeyframeIdx >= 8) ? 1 : 0);

            func_80070400(scratcher, &sharedData_800D9A00_5_s00[keyframeIdx0], &sharedData_800D9A00_5_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(HangedScratcherAnim_11, false):
            if (scratcherProps.field_EE == 31)
            {
                func_80070400(scratcher, &sharedData_800D9B04_5_s00, sharedData_800D9A78_5_s00);
            }
            else
            {
                func_80070400(scratcher, &sharedData_800D9A64_5_s00, sharedData_800D9A78_5_s00);
            }
            break;

        case ANIM_STATUS(HangedScratcherAnim_11, true):
            scratcherProps.field_EE = 23;

            relKeyframeIdx = animKeyframeIdx - 192;
            keyframeIdx0   = relKeyframeIdx - ((relKeyframeIdx >= 2) ? 1 : 0) - ((relKeyframeIdx >= 8) ? 1 : 0);
            keyframeIdx1   = (relKeyframeIdx + 1) - ((relKeyframeIdx > 0) ? 1 : 0) - ((relKeyframeIdx >= 7) ? 1 : 0) - ((relKeyframeIdx >= 8) ? 1 : 0);

            func_80070400(scratcher, &sharedData_800D9A78_5_s00[keyframeIdx0], &sharedData_800D9A78_5_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(HangedScratcherAnim_15, false):
            if (scratcherProps.field_EE == 33)
            {
                func_80070400(scratcher, &sharedData_800D99D8_5_s00, &sharedData_800D9B04_5_s00);
            }
            else if (scratcherProps.field_EE == 19)
            {
                func_80070400(scratcher, &sharedData_800D9A64_5_s00, &sharedData_800D9B04_5_s00);
            }
            else
            {
                CopyData(scratcher, sharedData_800D9B04_5_s00);
            }
            break;

        case ANIM_STATUS(HangedScratcherAnim_15, true):
        case ANIM_STATUS(HangedScratcherAnim_18, false):
        case ANIM_STATUS(HangedScratcherAnim_18, true):
            CopyData(scratcher, sharedData_800D9B04_5_s00);
            break;

        case ANIM_STATUS(HangedScratcherAnim_1, false):
        case ANIM_STATUS(HangedScratcherAnim_1, true):
        case ANIM_STATUS(HangedScratcherAnim_2, false):
        case ANIM_STATUS(HangedScratcherAnim_2, true):
        case ANIM_STATUS(HangedScratcherAnim_3, false):
        case ANIM_STATUS(HangedScratcherAnim_3, true):
        case ANIM_STATUS(HangedScratcherAnim_24, false):
        case ANIM_STATUS(HangedScratcherAnim_24, true):
        case ANIM_STATUS(HangedScratcherAnim_25, false):
        case ANIM_STATUS(HangedScratcherAnim_25, true):
        case ANIM_STATUS(HangedScratcherAnim_26, false):
        case ANIM_STATUS(HangedScratcherAnim_26, true):
            CopyData(scratcher, sharedData_800D9B18_5_s00);
            break;

        case ANIM_STATUS(5, false):
            CopyData(scratcher, sharedData_800D9B2C_5_s00[0]);
            break;

        case ANIM_STATUS(HangedScratcherAnim_5, true):
            relKeyframeIdx = animKeyframeIdx - 116;
            func_80070400(scratcher, &sharedData_800D9B2C_5_s00[relKeyframeIdx], &sharedData_800D9B2C_5_s00[relKeyframeIdx + 1]);
            break;
    }

    func_8005C814(&scratcher->field_D8, scratcher);

    if (!(scratcherProps.flags_E8 & HangedScratcherFlag_9))
    {
        if (!(scratcher->flags_3E & (1 << 1)) && scratcher->health_B0 > Q12(0.0f) &&
            (scratcherProps.flags_E8 & HangedScratcherFlag_1) && (scratcherProps.flags_E8 & HangedScratcherFlag_0))
        {
            scratcher->field_E1_0 = 4;
        }
        else
        {
            scratcher->field_E1_0 = 2;
        }
    }

    #undef animKeyframeIdx
}

bool sharedFunc_800D3214_5_s00(s_SubCharacter* scratcher)
{
    s_Collision coll;

    Collision_Get(&coll, scratcher->position_18.vx, scratcher->position_18.vz);

#ifdef MAP5_S00
    if (coll.field_8 != 7)
    {
        if (scratcher->position_18.vx > Q12(-40.0f))
        {
            return scratcher->position_18.vz > Q12(-9.0f);
        }
        else if (scratcher->position_18.vx > Q12(-80.0f))
        {
            if (scratcher->position_18.vx <= Q12(-57.0f))
            {
                if (scratcher->position_18.vx >= Q12(-62.0f))
                {
                    if (scratcher->position_18.vz > Q12(-10.0f))
                    {
                        return true;
                    }

                    return scratcher->position_18.vz < Q12(-14.0f);
                }
            }
        }
        else if (scratcher->position_18.vz <= Q12(-89.0f))
        {
            return (scratcher->position_18.vx >= Q12(-89.0f));
        }
    }

    return false;
#else
    // M6S03 version.
    if (coll.field_8 != 7)
    {
        if (scratcher->position_18.vx < 0)
        {
            if (scratcher->position_18.vz < Q12(38.0f))
            {
                return true;
            }

            if (scratcher->position_18.vz < Q12(57.0f))
            {
                return false;
            }

            if (scratcher->position_18.vz <= Q12(63.0f))
            {
                if (scratcher->position_18.vx >= Q12(-22.0f))
                {
                    return scratcher->position_18.vx > Q12(-18.0f);
                }
            }
            else
            {
                return false;
            }
        }
        else if (scratcher->position_18.vz > Q12(40.0f))
        {
            if (scratcher->position_18.vz <= Q12(63.0f))
            {
                if (scratcher->position_18.vz >= Q12(57.0f))
                {
                    if (scratcher->position_18.vx >= Q12(18.0f))
                    {
                        return scratcher->position_18.vx > Q12(22.0f);
                    }

                    return true;
                }
            }

            return false;
        }
        else if (scratcher->position_18.vz <= Q12(23.0f))
        {
            if (scratcher->position_18.vz >= Q12(17.0f))
            {
                if (scratcher->position_18.vx >= Q12(18.0f))
                {
                    return scratcher->position_18.vx > Q12(22.0f);
                }

                return true;
            }

            return false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
#endif
}

void sharedFunc_800D3300_5_s00(s_SubCharacter* scratcher)
{
    #define animKeyframeIdx FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT)

    if (scratcherProps.timer_100 != Q12(0.0f))
    {
        if (scratcherProps.timer_100 > Q12(0.0f))
        {
            scratcherProps.timer_100 -= g_DeltaTime;
            if (scratcherProps.timer_100 <= Q12(0.0f))
            {
                scratcherProps.timer_100 = Q12(0.0f);
            }
        }
        else
        {
            scratcherProps.timer_100 += g_DeltaTime;
            if (scratcherProps.timer_100 >= Q12(0.0f))
            {
                scratcherProps.timer_100 = Q12(0.75f);
                func_8005DC1C(Sfx_Unk1580, &scratcher->position_18, Q8(0.5f), 0);
            }
        }
    }
    else
    {
        if (scratcherProps.flags_E8 & HangedScratcherFlag_5)
        {
            if (scratcherProps.flags_E8 & HangedScratcherFlag_0)
            {
                func_8005DC1C(Sfx_Unk1584, &scratcher->position_18, Q8(0.5f), 0);
            }
            else
            {
                func_8005DC1C(Sfx_Unk1579, &scratcher->position_18, Q8(0.5f), 0);
            }

            scratcherProps.timer_100 = Q12(0.5f);
        }
        else
        {
            if (scratcherProps.flags_E8 & HangedScratcherFlag_4)
            {
                scratcherProps.timer_100 = Q12(-0.3f);
            }
        }

        switch (scratcher->model_0.controlState_2)
        {
            case 1:
            case 16:
                if (scratcherProps.timer_108 == Q12(0.0f))
                {
                    if (!Rng_GenerateInt(0, 511)) // 1 in 512 chance.
                    {
                        if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                                g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) > Q12(6.5f))
                        {
                            scratcherProps.timer_108 = Rng_GenerateInt(Q12(3.5f), Q12(8.0f) - 1);
                            func_8005DC1C(Sfx_Unk1583, &scratcher->position_18, Q8(0.5f), 0);
                        }
                    }
                }
                else
                {
                    scratcherProps.timer_108 -= g_DeltaTime;
                    if (scratcherProps.timer_108 < Q12(0.0f))
                    {
                        scratcherProps.timer_108 = Q12(0.0f);
                    }
                }
                break;

            case 2:
            case 3:
            case 5:
            case 6:
            case 7:
                if (scratcherProps.timer_108 == Q12(0.0f))
                {
                    if (!Rng_GenerateUInt(0, 255)) // 1 in 256 chance.
                    {
                        if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                                g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) > Q12(4.5f))
                        {
                            scratcherProps.timer_108 = Rng_GenerateInt(Q12(3.5f), Q12(7.5f) - 1);
                            func_8005DC1C(Sfx_Unk1583, &scratcher->position_18, Q8(0.5f), 0);
                        }
                    }
                }
                else
                {
                    scratcherProps.timer_108 -= g_DeltaTime;
                    if (scratcherProps.timer_108 < Q12(0.0f))
                    {
                        scratcherProps.timer_108 = Q12(0.0f);
                    }
                }
                break;
        }
    }

    scratcherProps.flags_E8 &= ~(HangedScratcherFlag_4 | HangedScratcherFlag_5);

    // TODO: Can the `+ 88` etc below be added into the Rng macro calls? Couldn't match with that yet.
    if (scratcher->model_0.anim_4.status_0 == 35)
    {
        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 272, 273))
        {
            if (scratcherProps.field_103 == 0)
            {
                func_8005DD44(Sfx_Unk1578, &scratcher->position_18, Q8(0.125f),
                              Rng_GenerateUInt(0, 15) + ((FP_TO(scratcher->moveSpeed_38, Q12_SHIFT) / Q12(3.0f)) >> 5) + 88);
                scratcherProps.field_103 = 1;
            }
        }
        else
        {
            scratcherProps.field_103 = 0;
        }

        if (animKeyframeIdx == 276 || animKeyframeIdx == 267)
        {
            if (scratcherProps.field_102 == 0)
            {
                func_8005DD44(Sfx_Unk1578, &scratcher->position_18, Q8(0.125f),
                              Rng_GenerateUInt(0, 15) + ((FP_TO(scratcher->moveSpeed_38, Q12_SHIFT) / Q12(3.0f)) >> 5) + 88);
                scratcherProps.field_102 = 1;
            }
        }
        else
        {
            scratcherProps.field_102 = 0;
        }
    }
    else if (scratcher->model_0.anim_4.status_0 == 37)
    {
        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 285, 286))
        {
            if (scratcherProps.field_103 == 0)
            {
                func_8005DD44(Sfx_Unk1578, &scratcher->position_18, Q8(0.5f),
                              Rng_GenerateUInt(0, 15) + ((FP_TO(scratcher->moveSpeed_38, Q12_SHIFT) / Q12(2.8f)) >> 5) + 120);
                scratcherProps.field_103 = 1;
            }
        }
        else
        {
            scratcherProps.field_103 = 0;
        }

        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 277, 278))
        {
            if (scratcherProps.field_102 == 0)
            {
                func_8005DD44(Sfx_Unk1578, &scratcher->position_18, Q8(0.5f),
                              Rng_GenerateUInt(0, 15) + ((FP_TO(scratcher->moveSpeed_38, Q12_SHIFT) / Q12(2.8f)) >> 5) + 120);
                scratcherProps.field_102 = 1;
            }
        }
        else
        {
            scratcherProps.field_102 = 0;
        }
    }
    else if (scratcher->model_0.anim_4.status_0 == 3)
    {
        if (scratcherProps.field_103 < 3)
        {
            s32 temp_v1 = (scratcherProps.field_103 + 1) * 11;
            if (animKeyframeIdx >= temp_v1 && (animKeyframeIdx < temp_v1 + 2))
            {
                func_8005DD44(Sfx_Unk1578, &scratcher->position_18, Q8(0.5f), -16);
                scratcherProps.field_103++;
            }
        }
    }
    else
    {
        scratcherProps.field_102 = 0;
        scratcherProps.field_103 = 0;
    }

    #undef animKeyframeIdx
}

#undef scratcherProps
