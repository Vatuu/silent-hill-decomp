#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/stalker.h"

#define stalkerProps stalker->properties_E4.stalker

void Ai_Stalker_Update(s_SubCharacter* stalker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        sharedData_800E3A20_0_s00 = Q12(350.0f);
        sharedData_800E3A24_0_s00 = Q12(100.0f);
        sharedData_800E3A28_0_s00 = Q12(3.0f);
        sharedData_800E3A2C_0_s00 = Q12(50.0f);
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        sharedData_800E3A20_0_s00 = Q12(350.0f);
        sharedData_800E3A24_0_s00 = Q12(100.0f);
        sharedData_800E3A28_0_s00 = Q12(0.0f);
        sharedData_800E3A2C_0_s00 = Q12(35.0f);
    }
    else
    {
        sharedData_800E3A20_0_s00 = Q12(600.0f);
        sharedData_800E3A24_0_s00 = Q12(180.0f);
        sharedData_800E3A28_0_s00 = Q12(6.0f);
        sharedData_800E3A2C_0_s00 = Q12(100.0f);
    }

    // Initialize.
    if (stalker->model_0.controlState_2 == StalkerControl_None)
    {
        Ai_Stalker_Init(stalker);
    }

    if (stalker->model_0.controlState_2 != StalkerControl_1)
    {
        if (g_DeltaTime0 != Q12(0.0f))
        {
            sharedFunc_800D3308_0_s00(stalker);
            Ai_Stalker_ControlUpdate(stalker);
            sharedFunc_800D67FC_0_s00(stalker);
        }

        sharedFunc_800D6970_0_s00(stalker, anmHdr, coords);
        sharedFunc_800D70C4_0_s00(stalker);

        if (g_DeltaTime0 != Q12(0.0f))
        {
            sharedFunc_800D7BE8_0_s00(stalker);
        }

        stalkerProps.flags_E8 &= ~StalkerFlag_WarpRotation;
    }
}

void Ai_Stalker_Init(s_SubCharacter* stalker)
{
    s32 i;

    stalkerProps.flags_E8 = StalkerFlag_None;
    Chara_PropertiesClear(stalker);
    stalker->health_B0 = sharedData_800E3A20_0_s00;

#ifdef MAP6_S03
    // Set health to 1.5x when not on easy difficulty.
    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        stalker->health_B0 = Q12_MULT_FLOAT_PRECISE(sharedData_800E3A20_0_s00, 1.5f);
    }
#endif

    stalker->moveSpeed_38   = Q12(0.0f);
    stalker->fallSpeed_34   = Q12(0.0f);
    stalker->rotation_24.vz = Q12_ANGLE(0.0f);
    stalker->rotation_24.vx = Q12_ANGLE(0.0f);
    //Character_AnimSet(stalker, ANIM_STATUS(StalkerAnim_30, true), 447); // TODO: Doesn't match?
    stalker->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_30, true);
    stalker->model_0.anim_4.time_4        = Q12(477.0f);
    stalker->model_0.anim_4.keyframeIdx_8 = 477;
    stalker->headingAngle_3C              = stalker->rotation_24.vy;

    // Handle state step.
    switch (stalker->model_0.stateStep_3)
    {
        case StalkerStateStep_11:
            stalkerProps.flags_E8 |= StalkerFlag_2;

        case StalkerStateStep_3:
            stalkerProps.timer_F8  = Q12(2.5f);
            stalkerProps.flags_E8 |= StalkerFlag_0;

        case StalkerStateStep_8:
            stalker->model_0.controlState_2 = StalkerControl_4;
            stalker->field_E1_0      = 3;
            break;

        case StalkerStateStep_7:
            stalker->model_0.controlState_2 = StalkerControl_4;
            stalkerProps.flags_E8   |= StalkerFlag_11;
            stalker->field_E1_0      = 3;
            break;

        case StalkerStateStep_6:
            stalker->model_0.controlState_2 = StalkerControl_2;
            stalker->flags_3E       |= CharaFlag_Unk3;
            stalkerProps.timer_F8    = Q12(1.0f);
            stalkerProps.flags_E8   |= StalkerFlag_0 | StalkerFlag_1;
            stalker->field_E1_0      = 3;
            stalker->flags_3E       &= ~CharaFlag_Unk5;
            break;

        case StalkerStateStep_5:
            stalker->model_0.controlState_2 = StalkerControl_1;
            stalker->field_E1_0      = 0;
            stalker->flags_3E       |= CharaFlag_Unk5;
            break;

        case StalkerStateStep_9:
            stalker->model_0.controlState_2              = StalkerControl_12;
            //Character_AnimSet(stalker, ANIM_STATUS(StalkerAnim_27, true), 427); // TODO: Doesn't match?
            stalker->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_27, true);
            stalker->model_0.anim_4.time_4        = Q12(427.0f);
            stalker->model_0.anim_4.keyframeIdx_8 = 427;
            stalkerProps.flags_E8                |= StalkerFlag_0;
            stalker->field_E1_0                   = 3;
            break;

        case StalkerStateStep_10:
            stalker->model_0.controlState_2              = StalkerControl_11;
            //Character_AnimSet(stalker, ANIM_STATUS(StalkerAnim_28, true), 442); // TODO: Doesn't match?
            stalker->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_28, true);
            stalker->model_0.anim_4.time_4        = Q12(443.0f);
            stalker->model_0.anim_4.keyframeIdx_8 = 443;
            stalker->field_E1_0                   = 3;
            break;

        case StalkerStateStep_17:
            stalker->model_0.controlState_2              = StalkerControl_13;
            //Character_AnimSet(stalker, ANIM_STATUS(StalkerAnim_14, true), 176); // TODO: Doesn't match?
            stalker->model_0.anim_4.status_0      = ANIM_STATUS(StalkerAnim_14, true);
            stalker->model_0.anim_4.time_4        = Q12(176.0f);
            stalker->model_0.anim_4.keyframeIdx_8 = 176;
            stalker->field_E1_0                   = 0;
            break;
    }

    stalker->model_0.stateStep_3    = 0;
    stalkerProps.sfxId_102          = NO_VALUE;
    stalkerProps.targetPositionX_F0 = stalker->position_18.vx;
    stalkerProps.targetPositionZ_F4 = stalker->position_18.vz;
    stalkerProps.health_110         = stalker->health_B0;

    ModelAnim_AnimInfoSet(&stalker->model_0.anim_4, STALKER_ANIM_INFOS);
    Chara_DamageClear(stalker);

#ifdef MAP6_S03
    stalker->flags_3E |= CharaFlag_Unk9;
#endif
}

void sharedFunc_800D3308_0_s00(s_SubCharacter* stalker)
{
    q3_12  angle;
    u16    keyframeIdx;
    q19_12 mag;
    q19_12 var_a0;
    q20_12 newHealth;

    var_a0 = stalkerProps.timer_10C - Q12_MULT_PRECISE(g_DeltaTime0, Q12(20.0f));
    stalkerProps.timer_10C = MAX(var_a0, Q12(0.0f));

    if (stalker->damage_B4.amount_C > Q12(0.0f) && stalker->health_B0 > Q12(0.0f))
    {
        sharedFunc_800D7E04_0_s00(stalker, Sfx_Unk1365);
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_34, true) ||
        stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_35, true))
    {
        stalker->damage_B4.amount_C = Q12(0.0f);
    }

    if (stalker->health_B0 > Q12(0.0f))
    {
        newHealth          = stalker->health_B0 + Q12_MULT_PRECISE(g_DeltaTime0, sharedData_800E3A28_0_s00);
        stalker->health_B0 = MIN(newHealth, stalkerProps.health_110);
    }

    if (stalker->damage_B4.amount_C > Q12(0.0f))
    {
        if (stalker->health_B0 > Q12(0.0f))
        {
            stalker->health_B0       = MAX(stalker->health_B0 - stalker->damage_B4.amount_C, Q12(0.0f));
            stalkerProps.health_110 -= stalker->damage_B4.amount_C >> 2;
            stalkerProps.flags_E8   |= StalkerFlag_0 | StalkerFlag_10;

            stalker->damage_B4.position_0.vx += Q12_MULT(stalker->moveSpeed_38, Math_Sin(stalker->headingAngle_3C)) >> 3;
            stalker->damage_B4.position_0.vz += Q12_MULT(stalker->moveSpeed_38, Math_Cos(stalker->headingAngle_3C)) >> 3;

            if (stalkerProps.flags_E8 & StalkerFlag_6)
            {
                mag          = Math_Vector2MagCalc(stalker->damage_B4.position_0.vx, stalker->damage_B4.position_0.vz);
                stalker->moveSpeed_38 = (mag << 12) / 0xC000;
            }
            else
            {
                mag          = Math_Vector2MagCalc(stalker->damage_B4.position_0.vx, stalker->damage_B4.position_0.vz);
                stalker->moveSpeed_38 = (mag << 12) / Q12(1.5f);
            }

            stalker->headingAngle_3C              = ratan2(stalker->damage_B4.position_0.vx, stalker->damage_B4.position_0.vz);
            stalkerProps.flags_E8                |= StalkerFlag_13;
            stalkerProps.timer_10C += stalker->damage_B4.amount_C;

            if (stalkerProps.timer_10C >= sharedData_800E3A2C_0_s00 ||
                (!(stalkerProps.flags_E8 & StalkerFlag_6) && stalker->health_B0 <= sharedData_800E3A24_0_s00))
            {
                stalkerProps.timer_10C = 0;

                angle = ABS(func_8005BF38(Math_AngleBetweenPositionsGet(stalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                          stalker->rotation_24.vy));

                if (stalkerProps.flags_E8 & StalkerFlag_6)
                {
                    if (stalker->model_0.anim_4.status_0 == 53)
                    {
                        stalkerProps.keyframeIdx_FC = NO_VALUE;
                        stalker->model_0.anim_4.status_0                       = 76;
                    }
                    else if (stalker->model_0.anim_4.status_0 == 35)
                    {
                        stalkerProps.keyframeIdx_FC = NO_VALUE;
                        stalker->model_0.anim_4.status_0                       = 78;
                    }
                    else if (stalker->model_0.anim_4.status_0 == 37)
                    {
                        stalkerProps.keyframeIdx_FC = NO_VALUE;
                        stalker->model_0.anim_4.status_0                       = 80;
                    }
                }
                else
                {
                    if (stalker->health_B0 > sharedData_800E3A24_0_s00 && !(stalkerProps.flags_E8 & 0x80))
                    {
                        if (stalker->model_0.controlState_2 == StalkerControl_5)
                        {
                            g_SysWork.field_2284[3] &= ~(1 << 1);
                        }

                        stalker->model_0.controlState_2 = StalkerControl_7;

                        if (ANIM_STATUS_IDX_GET(stalker->model_0.anim_4.status_0) < StalkerAnim_22 ||
                            ANIM_STATUS_IDX_GET(stalker->model_0.anim_4.status_0) > StalkerAnim_23)
                        {
                            if (angle >= Q12_ANGLE(60.0f))
                            {
                                stalker->model_0.anim_4.status_0 = 46;
                            }
                            else
                            {
                                stalker->model_0.anim_4.status_0 = 44;
                            }
                        }
                    }
                    else if (stalkerProps.flags_E8 & StalkerFlag_7)
                    {
                        stalker->model_0.controlState_2 = StalkerControl_9;

                        if (ANIM_STATUS_IDX_GET(stalker->model_0.anim_4.status_0) == 11)
                        {
                            if (stalker->model_0.anim_4.status_0 == 22)
                            {
                                stalkerProps.keyframeIdx_FC = 0;
                                stalker->model_0.anim_4.status_0                               = 76;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 106 &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 109)
                            {
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 107;
                                stalker->model_0.anim_4.status_0                       = 76;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 108 &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 113)
                            {
                                if (angle >= Q12_ANGLE(60.0f))
                                {
                                    stalker->model_0.anim_4.status_0 = 84;
                                }
                                else
                                {
                                    stalker->model_0.anim_4.status_0 = 2;
                                }

                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 107;

                                if (stalkerProps.keyframeIdx_FC == 2)
                                {
                                    stalkerProps.relKeyframeIdx_FE = 2;
                                }
                                else if (stalkerProps.keyframeIdx_FC == 3)
                                {
                                    stalkerProps.relKeyframeIdx_FE = 1;
                                }
                                else
                                {
                                    stalkerProps.relKeyframeIdx_FE = 0;
                                }
                            }
                            else
                            {
                                if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 112 &&
                                    FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 118)
                                {
                                    if (angle >= Q12_ANGLE(60.0f))
                                    {
                                        stalker->model_0.anim_4.status_0 = 86;
                                    }
                                    else
                                    {
                                        stalker->model_0.anim_4.status_0 = 6;
                                    }

                                    keyframeIdx = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);

                                    stalkerProps.keyframeIdx_FC = keyframeIdx - 107;

                                    if (keyframeIdx == 116 || keyframeIdx == 117)
                                    {
                                        stalkerProps.relKeyframeIdx_FE = 1;
                                    }
                                    else
                                    {
                                        stalkerProps.relKeyframeIdx_FE = 2;
                                    }
                                }
                                else
                                {
                                    if (angle >= Q12_ANGLE(60.0f))
                                    {
                                        stalker->model_0.anim_4.status_0 = 88;
                                    }
                                    else
                                    {
                                        stalker->model_0.anim_4.status_0 = 4;
                                    }

                                    stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 107;
                                }
                            }
                        }
                        else if (ANIM_STATUS_IDX_GET(stalker->model_0.anim_4.status_0) == StalkerAnim_12)
                        {
                            if (stalker->model_0.anim_4.status_0 == 24)
                            {
                                stalkerProps.keyframeIdx_FC = 0;
                            }
                            else
                            {
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 0x81;
                            }

                            if (stalker->model_0.anim_4.status_0 == 24 ||
                                (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 128 &&
                                 FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 136))
                            {
                                stalker->model_0.anim_4.status_0 = 78;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 135 &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 142)
                            {
                                stalker->model_0.anim_4.status_0                               = 8;
                                stalkerProps.relKeyframeIdx_FE = (12 - stalkerProps.keyframeIdx_FC) >> 1;
                            }
                            else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 141 &&
                                     FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 149)
                            {
                                stalker->model_0.anim_4.status_0 = 10;

                                switch (stalkerProps.keyframeIdx_FC)
                                {
                                    case 13:
                                        stalkerProps.relKeyframeIdx_FE = 5;
                                        break;

                                    case 14:
                                    case 15:
                                        stalkerProps.relKeyframeIdx_FE = 4;
                                        break;

                                    case 16:
                                    case 17:
                                        stalkerProps.relKeyframeIdx_FE = 3;
                                        break;

                                    default:
                                        stalkerProps.relKeyframeIdx_FE = 2;
                                        break;
                                }
                            }
                            else
                            {
                                stalker->model_0.anim_4.status_0                       = 10;
                                stalkerProps.relKeyframeIdx_FE = 1;
                            }
                        }
                        else
                        {
                            if (stalker->model_0.anim_4.status_0 == 26)
                            {
                                stalkerProps.keyframeIdx_FC = 0;
                                stalker->model_0.anim_4.status_0                       = 80;
                            }
                            else
                            {
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 158;

                                if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) == 0x9E || FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) == 159)
                                {
                                    stalker->model_0.anim_4.status_0 = 80;
                                }
                                else if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 160 ||
                                         FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 168)
                                {
                                    stalkerProps.relKeyframeIdx_FE = 0;
                                    stalker->model_0.anim_4.status_0 = 10;
                                }
                                else
                                {
                                    stalker->model_0.anim_4.status_0 = 91;
                                }
                            }
                        }

                        stalkerProps.flags_E8 &= ~(1 << 7);
                    }
                    else
                    {
                        stalker->model_0.controlState_2 = StalkerControl_9;

                        if (angle < Q12_ANGLE(60.0f))
                        {
                            if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) > 361 &&
                                FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) < 373)
                            {
                                if (FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) >= 364 &&
                                    FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) <= 367)
                                {
                                    stalkerProps.relKeyframeIdx_FE = 2;
                                }
                                else
                                {
                                    stalkerProps.relKeyframeIdx_FE = 1;
                                }

                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 362;
                            }
                            else
                            {
                                stalkerProps.relKeyframeIdx_FE = 0;
                            }

                            stalker->model_0.anim_4.status_0 = 48;
                        }
                        else
                        {
                            if (stalker->model_0.anim_4.status_0 == 23)
                            {
                                stalkerProps.relKeyframeIdx_FE = 23;
                                stalker->model_0.anim_4.status_0                       = 50;
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 107;
                            }
                            else if (stalker->model_0.anim_4.status_0 == 25)
                            {
                                stalkerProps.relKeyframeIdx_FE = 25;
                                stalker->model_0.anim_4.status_0                       = 50;
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 129;
                            }
                            else if (stalker->model_0.anim_4.status_0 == 27)
                            {
                                stalkerProps.relKeyframeIdx_FE = 27;
                                stalker->model_0.anim_4.status_0                       = 50;
                                stalkerProps.keyframeIdx_FC = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 158;
                            }
                            else
                            {
                                stalkerProps.relKeyframeIdx_FE = 83;
                                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_41, false);
                            }
                        }
                    }
                }

                stalkerProps.timer_F8  = Q12(0.0f);
                stalkerProps.flags_E8 &= 0xF7E7;
            }
        }
    }

    Chara_DamageClear(stalker);
}

void Ai_Stalker_ControlUpdate(s_SubCharacter* stalker)
{
    q3_12 angle;
    s32   temp_s1;
    s32   temp_v0;
    s32   temp_v0_2;
    s32   i;
    s32   angle1;
    s32   unkAnimStatus;
    s32   animStatus;

    if (stalkerProps.flags_E8 & StalkerFlag_10)
    {
        stalker->flags_3E |= CharaFlag_Unk3;
    }

    if (stalker->model_0.anim_4.status_0 != ANIM_STATUS(StalkerAnim_34, true))
    {
        animStatus = stalker->model_0.anim_4.status_0;

        if (animStatus > ANIM_STATUS(StalkerAnim_34, true))
        {
            unkAnimStatus = ANIM_STATUS(StalkerAnim_35, true);
            unkAnimStatus++; // } TODO: Hack.
            unkAnimStatus--; // }
        }
        else
        {
            unkAnimStatus = ANIM_STATUS(StalkerAnim_7, true);
        }

        if (animStatus != unkAnimStatus)
        {
            stalker->field_44.field_0 = 0;
        }
    }

    if (!(g_SysWork.sysFlags_22A0 & SysFlag_4))
    {
        g_SysWork.sysFlags_22A0 |= SysFlag_4;

        for (i = 4; i > 0; i--)
        {
            sharedData_800E39EC_0_s00[i] = sharedData_800E39EC_0_s00[i - 1];
            sharedData_800E3A0C_0_s00[i] = sharedData_800E3A0C_0_s00[i - 1];
        }

        // TODO: Use `Math_Vector2MagCalc`.
        temp_v0                      = ((g_SysWork.playerWork_4C.player_0.position_18.vx - sharedData_800E39E4_0_s00) >> 6);
        temp_v0_2                    = (g_SysWork.playerWork_4C.player_0.position_18.vz - sharedData_800E39E8_0_s00) >> 6;
        sharedData_800E39EC_0_s00[0] = (FP_TO(SquareRoot0(SQUARE(temp_v0) + SQUARE(temp_v0_2)), Q12_SHIFT) << 6) / g_DeltaTime0;
        sharedData_800E3A0C_0_s00[0] = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - sharedData_800E39E4_0_s00, g_SysWork.playerWork_4C.player_0.position_18.vz - sharedData_800E39E8_0_s00);
        sharedData_800E39E4_0_s00    = g_SysWork.playerWork_4C.player_0.position_18.vx;
        sharedData_800E39E8_0_s00    = g_SysWork.playerWork_4C.player_0.position_18.vz;

        if (sharedData_800DD5A6_0_s00 != 5)
        {
            sharedData_800DD5A6_0_s00++;
            sharedData_800E3A18_0_s00 = g_SysWork.playerWork_4C.player_0.position_18.vx;
            sharedData_800E3A1C_0_s00 = g_SysWork.playerWork_4C.player_0.position_18.vz;
        }
        else
        {
            angle1 = Q12_ANGLE(0.0f);
            for (i = 0; i < 4; i++)
            {
                angle1 += func_8005BF38(sharedData_800E3A0C_0_s00[i] - sharedData_800E3A0C_0_s00[i + 1]);
            }

            angle = sharedData_800E3A0C_0_s00[0] + (angle1 >> 2);

            angle1 = 0;
            for (i = 0; i < 4; i++)
            {
                angle1 += sharedData_800E39EC_0_s00[i] - sharedData_800E39EC_0_s00[i + 1];
            }

            temp_s1                   = sharedData_800E39EC_0_s00[0] + (angle1 >> 2);
            sharedData_800E3A18_0_s00 = ((temp_s1 * Math_Sin(angle)) >> 14) + g_SysWork.playerWork_4C.player_0.position_18.vx;
            sharedData_800E3A1C_0_s00 = ((temp_s1 * Math_Cos(angle)) >> 14) + g_SysWork.playerWork_4C.player_0.position_18.vz;
        }
    }

    // Handle control state.
    switch (stalker->model_0.controlState_2)
    {
        case StalkerControl_None:
            break;

        case StalkerControl_2:
            Ai_Stalker_Control_2(stalker);
            break;

        case StalkerControl_3:
            Ai_Stalker_Control_3(stalker);
            break;

        case StalkerControl_8:
            Ai_Stalker_Control_8(stalker);
            break;

        case StalkerControl_4:
            Ai_Stalker_Control_4(stalker);
            break;

        case StalkerControl_5:
            Ai_Stalker_Control_5(stalker);
            break;

        case StalkerControl_6:
            Ai_Stalker_Control_6(stalker);
            break;

        case StalkerControl_7:
            Ai_Stalker_Control_7(stalker);
            break;

        case StalkerControl_9:
            Ai_Stalker_Control_9(stalker);
            break;

        case StalkerControl_10:
            Ai_Stalker_Control_10(stalker);
            break;

        case StalkerControl_11:
            Ai_Stalker_Control_11(stalker);
            break;

        case StalkerControl_12:
            Ai_Stalker_Control_12(stalker);
            break;

        case StalkerControl_13:
            Ai_Stalker_Control_13(stalker);
            break;
    }
}

void Ai_Stalker_Control_2(s_SubCharacter* stalker)
{
#if defined(MAP0_S00)
    q3_12  angleDeltaToTargetHeading;
    q3_12  grabAngleDelta;
    q3_12  angleDeltaToPlayer;
    q19_12 distToPlayer;
    s32    i;

    // TODO: Doesn't match?
    //distToPlayer  = Math_Vector2MagCalc(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
    //                                 sharedData_800E3A1C_0_s00 - stalker->position_18.vz);
    distToPlayer   = SquareRoot0(SQUARE((sharedData_800E3A18_0_s00 - stalker->position_18.vx) >> 6) + SQUARE((sharedData_800E3A1C_0_s00 - stalker->position_18.vz) >> 6));
    distToPlayer <<= 6;
    angleDeltaToPlayer = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
                                              sharedData_800E3A1C_0_s00 - stalker->position_18.vz) -
                                       stalker->rotation_24.vy);

    if (distToPlayer > Q12(8.0f) && (stalkerProps.flags_E8 & StalkerFlag_0) && !(g_SysWork.flags_22A4 & SysFlag2_MenuOpen))
    {
        if (!Vw_AabbVisibleInScreenCheck(stalker->position_18.vx - Q12(1.0f), stalker->position_18.vx + Q12(1.0f),
                                         stalker->position_18.vy - Q12(1.8f), stalker->position_18.vy,
                                         stalker->position_18.vz - Q12(1.0f), stalker->position_18.vz - Q12(1.0f)))
        {
            stalkerProps.flags_E8 |= StalkerFlag_WarpRotation;
        }
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_30, true) &&
        !func_800700F8(stalker, &g_SysWork.playerWork_4C.player_0))
    {
        stalkerProps.timer_F8 = Q12(0.0f);

        if (stalkerProps.flags_E8 & StalkerFlag_WarpRotation)
        {
            stalker->rotation_24.vy = Math_AngleBetweenPositionsGet(stalker->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
        else
        {
            if (ABS(angleDeltaToPlayer) > Q12_ANGLE(90.0f))
            {
                Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
            }
            else
            {
                Chara_MoveSpeedUpdate3(stalker, Q12_ANGLE(180.0f), (Q12_ANGLE(90.0f) - ABS(angleDeltaToPlayer)) * 4);
            }
        }

        for (i = 3 + ((ABS(angleDeltaToPlayer) > Q12_ANGLE(90.0f)) ? 1 : 0); i > 0; i--)
        {
            if (TIMESTEP_ANGLE(1, 2) < ABS(angleDeltaToPlayer))
            {
                if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
                {
                    stalker->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(180.0f));
                }
                else
                {
                    stalker->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(180.0f));
                }

                angleDeltaToPlayer = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
                                                          sharedData_800E3A1C_0_s00 - stalker->position_18.vz) -
                                                   stalker->rotation_24.vy);
            }

            if (ABS(angleDeltaToPlayer) < TIMESTEP_ANGLE(1, 2) || distToPlayer > Q12(2.0f))
            {
                break;
            }
        }

        if ((g_SysWork.field_2284[3] & (1 << 0)) ||
            ( (stalkerProps.flags_E8 & StalkerFlag_2) && Rng_GenerateInt(0, 3) != 0) || // 1 in 4 chance.
            (!(stalkerProps.flags_E8 & StalkerFlag_2) && Rng_GenerateInt(0, 1) != 0))   // 1 in 2 chance.
        {
            if ( distToPlayer < Q12(0.9f) &&
                (distToPlayer > Q12(0.7f) || !Rng_GenerateInt(0, 3))) // 1 in 4 chance.
            {
                if (ABS(angleDeltaToPlayer) < Q12_ANGLE(90.0f) && g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
                {
                    stalker->model_0.controlState_2 = StalkerControl_5;
                    g_SysWork.field_2284[3] |= 1 << 1;

                    sharedFunc_800D7E04_0_s00(stalker, Sfx_Unk1364);

                    if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 493, 504))
                    {
                        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_37, true);
                        stalkerProps.keyframeIdx_FC      = ANIM_STATUS(StalkerAnim_14, true);
                        stalkerProps.relKeyframeIdx_FE   = 0;
                        return;
                    }

                    stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_7, false);
                    stalkerProps.keyframeIdx_FC = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 477);

                    if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 478, 481))
                    {
                        stalkerProps.relKeyframeIdx_FE = 1;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 482, 487))
                    {
                        stalkerProps.relKeyframeIdx_FE = 2;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 488, 490))
                    {
                        stalkerProps.relKeyframeIdx_FE = 3;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 491, 492))
                    {
                        stalkerProps.relKeyframeIdx_FE = 4;
                    }
                    else
                    {
                        stalkerProps.relKeyframeIdx_FE = 0;
                    }
                    return;
                }
            }
        }
        // Attack player if player is alive.
        else if (distToPlayer > Q12(0.5f) && distToPlayer < Q12(1.0f))
        {
            if (ABS(angleDeltaToPlayer) < Q12_ANGLE(60.0f))
            {
                if (g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
                {
                    stalker->model_0.controlState_2 = StalkerControl_6;

                    // Grab player in front or behind.
                    grabAngleDelta = func_8005BF38(g_SysWork.playerWork_4C.player_0.rotation_24.vy - stalker->rotation_24.vy);
                    if (ABS(grabAngleDelta) > Q12_ANGLE(90.0f))
                    {
                        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_34, false);
                    }
                    else
                    {
                        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_35, false);
                    }

                    stalkerProps.keyframeIdx_FC = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 477);
                    g_SysWork.field_2284[3]    |= (1 << 0) | (1 << 1);
                    return;
                }
            }
        }

        if (distToPlayer < Q12(0.7f))
        {
            stalker->model_0.controlState_2 = StalkerControl_4;
        }
    }
    else
    {
        Chara_MoveSpeedUpdate3(stalker, Q12(0.5f), Q12(1.0f));

        // Set target heading angle.
        if (stalkerProps.timer_F8 == Q12(0.0f))
        {
            stalkerProps.targetHeadingAngle_100 = Chara_HeadingAngleGet(stalker,
                                                                        Q12(2.0f),
                                                                        g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                                        g_SysWork.playerWork_4C.player_0.position_18.vz,
                                                                        Q12(1.0f),
                                                                        true);
            if (stalkerProps.targetHeadingAngle_100 == Q12_ANGLE(360.0f))
            {
                stalkerProps.targetHeadingAngle_100 = stalker->rotation_24.vy - Q12_ANGLE(180.0f);
            }
        }

        // Update timer.
        stalkerProps.timer_F8 += g_DeltaTime0;
        if (stalkerProps.timer_F8 > Q12(2.5f) && Rng_GenerateInt(0, 15) == 0) // 1 in 16 chance.
        {
            stalkerProps.timer_F8 = Q12(0.0f);
        }

        // Turn toward target heading angle.
        if (stalkerProps.flags_E8 & StalkerFlag_WarpRotation)
        {
            stalker->rotation_24.vy = stalkerProps.targetHeadingAngle_100;
        }
        else
        {
            angleDeltaToTargetHeading = func_8005BF38(stalkerProps.targetHeadingAngle_100 - stalker->rotation_24.vy);
            if (TIMESTEP_ANGLE(1, 2) < ABS(angleDeltaToTargetHeading))
            {
                if (angleDeltaToTargetHeading > Q12_ANGLE(0.0f))
                {
                    stalker->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(180.0f));
                }
                else
                {
                    stalker->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(180.0f));
                }
            }
        }
    }
#endif
}

void Ai_Stalker_Control_3(s_SubCharacter* stalker)
{
#if !defined(MAP0_S00)
    q3_12  grabAngleDelta;
    s16    angleDeltaToTargetHeading;
    q3_12  angleDeltaToPlayer;
    q19_12 distToPlayer;
    q19_12 radiusMax;
    q19_12 radiusMin;
    s32    i;
    bool   cond1;
    q25_6  temp;
    q19_12 temp2;

    distToPlayer  = Math_Vector2MagCalc(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
                                        sharedData_800E3A1C_0_s00 - stalker->position_18.vz);
    angleDeltaToPlayer = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
                                              sharedData_800E3A1C_0_s00 - stalker->position_18.vz) -
                                       stalker->rotation_24.vy);

    if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1))))
    {
        radiusMax = Q12(15.0f);
        radiusMin = Q12(5.5f);
        cond1  = func_8006FD90(stalker, 0, Q12(7.5f), Q12(7.5f));
    }
    else if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
#if defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP5_S02) || defined(MAP6_S03) || defined(MAP6_S04) || defined(MAP7_S02)
        radiusMax = Q12(16.0f);
        radiusMin = Q12(6.0f);
        cond1  = func_8006FD90(stalker, 0, Q12(8.0f), Q12(8.0f));
#else
        radiusMax = Q12(12.0f);
        radiusMin = Q12(4.5f);
        cond1  = func_8006FD90(stalker, 0, Q12(6.0f), Q12(6.0f));
#endif
    }
    else
    {
        radiusMax = Q12(0.8f);
#if defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP5_S02) || defined(MAP6_S03) || defined(MAP6_S04) || defined(MAP7_S02)
        radiusMin = Q12(1.2f);
#else
        radiusMin = Q12(1.0f);
#endif
        cond1 = func_8006FD90(stalker, 1, Q12(0.4f), Q12(0.4f));
    }

    if (cond1 || func_80070360(stalker, distToPlayer, Q12(1.0f)))
    {
        stalkerProps.targetPositionX_F0 = sharedData_800E3A18_0_s00;
        stalkerProps.targetPositionZ_F4 = sharedData_800E3A1C_0_s00;

        if (!(stalkerProps.flags_E8 & StalkerFlag_10))
        {
            stalkerProps.flags_E8 |= StalkerFlag_10;
            sharedFunc_800D7E04_0_s00(stalker, Sfx_Unk1363);
        }

        stalkerProps.timer_116 = Q12(0.0f);
    }
    else if (stalkerProps.flags_E8 & StalkerFlag_10)
    {
        stalkerProps.timer_116 += g_DeltaTime0;

        if (!Rng_GenerateUInt(0, 511) || stalkerProps.timer_116 > Q12(1.2f))
        {
            stalkerProps.timer_116 = Q12(0.0f);
            stalkerProps.flags_E8 &= ~StalkerFlag_10;
        }
    }

    if (distToPlayer > Q12(8.0f))
    {
        if ((stalkerProps.flags_E8 & StalkerFlag_0) &&
            (stalkerProps.flags_E8 & StalkerFlag_10) &&
            !(g_SysWork.flags_22A4 & SysFlag2_MenuOpen))
        {
            if (!Vw_AabbVisibleInScreenCheck(stalker->position_18.vx - Q12(1.0f), stalker->position_18.vx + Q12(1.0f),
                                             stalker->position_18.vy - Q12(1.8f), stalker->position_18.vy,
                                             stalker->position_18.vz - Q12(1.0f), stalker->position_18.vz - Q12(1.0f)))
            {
                stalkerProps.flags_E8 |= StalkerFlag_WarpRotation;
            }
        }
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_30, true) && !(stalkerProps.flags_E8 & StalkerFlag_8) &&
        !func_800700F8(stalker, &g_SysWork.playerWork_4C.player_0))
    {
        stalkerProps.timer_F8 = Q12(0.0f);

        if (!(stalkerProps.flags_E8 & StalkerFlag_13))
        {
            Chara_MoveSpeedUpdate3(stalker, Q12_ANGLE(180.0f), (Q12_ANGLE(180.0f) - ABS(angleDeltaToPlayer)) * 2);
        }

        if (stalkerProps.flags_E8 & StalkerFlag_WarpRotation)
        {
            stalker->rotation_24.vy = ratan2(stalkerProps.targetPositionX_F0 - stalker->position_18.vx,
                                             stalkerProps.targetPositionZ_F4 - stalker->position_18.vz);
        }
        else
        {
            for (i = 3 + ((ABS(angleDeltaToPlayer) > Q12_ANGLE(90.0f)) ? 1 : 0); i > 0; i--)
            {
                if (TIMESTEP_ANGLE(1, 3) < ABS(angleDeltaToPlayer))
                {
                    if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
                    {
                        stalker->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(90.0f));
                    }
                    else
                    {
                        stalker->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(90.0f));
                    }

                    angleDeltaToPlayer = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - stalker->position_18.vx,
                                                              sharedData_800E3A1C_0_s00 - stalker->position_18.vz) -
                                                       stalker->rotation_24.vy);
                }

                if (ABS(angleDeltaToPlayer) < TIMESTEP_ANGLE(1, 3) || distToPlayer > (radiusMin >> 2))
                {
                    break;
                }
            }
        }

        if ((g_SysWork.field_2284[3] & (1 << 0)) || func_80070320() ||
            ABS(stalker->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy) > Q12(0.3f) ||
            ( (stalkerProps.flags_E8 & StalkerFlag_2) &&  Rng_GenerateInt(0, 3)) || // 3 in 4 chance?
            (!(stalkerProps.flags_E8 & StalkerFlag_2) && !Rng_GenerateInt(0, 3)))   // 1 in 4 chance.
        {
            if (!(g_SysWork.playerWork_4C.player_0.flags_3E & CharaFlag_Unk4) &&
                distToPlayer < Q12(0.9f) && (distToPlayer > Q12(0.7f) || !Rng_GenerateInt(0, 3)) && // 1 in 4 chance.
                ABS(angleDeltaToPlayer) < Q12_ANGLE(90.0f) && g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
            {
                stalker->model_0.controlState_2 = StalkerControl_5;
                g_SysWork.field_2284[3] |= 1 << 1;

                sharedFunc_800D7E04_0_s00(stalker, Sfx_Unk1364);

                if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 493, 504))
                {
                    stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_37, true);
                    stalkerProps.keyframeIdx_FC      = ANIM_STATUS(StalkerAnim_14, true);
                    stalkerProps.relKeyframeIdx_FE   = 0;
                }
                else
                {
                    stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_7, false);
                    stalkerProps.keyframeIdx_FC = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 477);

                    if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 478, 481))
                    {
                        stalkerProps.relKeyframeIdx_FE = 1;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 482, 487))
                    {
                        stalkerProps.relKeyframeIdx_FE = 2;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 488, 490))
                    {
                        stalkerProps.relKeyframeIdx_FE = 3;
                    }
                    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 491, 492))
                    {
                        stalkerProps.relKeyframeIdx_FE = 4;
                    }
                    else
                    {
                        stalkerProps.relKeyframeIdx_FE = 0;
                    }
                }
            }
            else if (distToPlayer < Q12(0.7f))
            {
                stalker->model_0.controlState_2 = StalkerControl_4;
            }
        }
        else if (!(g_SysWork.playerWork_4C.player_0.flags_3E & CharaFlag_Unk4) &&
                 distToPlayer < Q12(1.0f) && distToPlayer > Q12(0.5f) &&
                 ABS(angleDeltaToPlayer) < Q12_ANGLE(60.0f) && g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
        {
            stalker->model_0.controlState_2 = StalkerControl_6;

            // Grab player in front or behind.
            grabAngleDelta = func_8005BF38(g_SysWork.playerWork_4C.player_0.rotation_24.vy - stalker->rotation_24.vy);
            if (ABS(grabAngleDelta) > Q12_ANGLE(90.0f))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_34, false);
            }
            else
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_35, false);
            }

            stalkerProps.keyframeIdx_FC = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 477);
            g_SysWork.field_2284[3]    |= (1 << 0) | (1 << 1);
            stalker->field_44.field_0   = 1;
        }
        else if (distToPlayer < Q12(0.7f))
        {
            stalker->model_0.controlState_2 = StalkerControl_4;
        }
    }
    else
    {
        if (!(stalkerProps.flags_E8 & StalkerFlag_13))
        {
            Chara_MoveSpeedUpdate3(stalker, Q12(0.5f), Q12(0.7f));
        }

        if (stalkerProps.timer_F8 == Q12(0.0f))
        {
            stalkerProps.targetHeadingAngle_100 = Chara_HeadingAngleGet(stalker,
                                                                        Q12(2.5f),
                                                                        stalkerProps.targetPositionX_F0,
                                                                        stalkerProps.targetPositionZ_F4,
                                                                        Q12(1.0f),
                                                                        true);
            if (stalkerProps.targetHeadingAngle_100 == Q12_ANGLE(360.0f))
            {
                stalkerProps.targetHeadingAngle_100 = stalker->rotation_24.vy - Q12_ANGLE(180.0f);
            }
        }

        stalkerProps.timer_F8 += g_DeltaTime0;
        if (stalkerProps.timer_F8 > Q12(3.0f) &&
            !Rng_GenerateInt(0, 15)) // 1 in 16 chance.
        {
            stalkerProps.timer_F8 = Q12(0.0f);
        }

        if (stalkerProps.flags_E8 & StalkerFlag_WarpRotation)
        {
            stalker->rotation_24.vy = stalkerProps.targetHeadingAngle_100;
        }
        else
        {
            angleDeltaToTargetHeading = func_8005BF38(stalkerProps.targetHeadingAngle_100 - stalker->rotation_24.vy);
            if (((g_DeltaTime0 >> 3) + 1) < ABS(angleDeltaToTargetHeading))
            {
                if (angleDeltaToTargetHeading > Q12_ANGLE(0.0f))
                {
                    stalker->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(90.0f));
                }
                else
                {
                    stalker->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(90.0f));
                }
            }
        }
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_30, true) && (radiusMax * 2) < distToPlayer)
    {
        temp = SquareRoot0(SQUARE(Q12_TO_Q6(stalker->position_18.vx - stalkerProps.targetPositionX_F0)) +
                           SQUARE(Q12_TO_Q6(stalker->position_18.vz - stalkerProps.targetPositionZ_F4)));
        temp2 = radiusMin >> 1;
        if (Q6_TO_Q12(temp) < temp2)
        {
            stalker->model_0.controlState_2 = StalkerControl_4;
        }
    }
#endif
}

void Ai_Stalker_Control_4(s_SubCharacter* stalker)
{
    q3_12  angle;
    q19_12 offsetX;
    q19_12 offsetZ;
    bool   condCombo;
    q19_12 distToPlayer;
    q19_12 distToTarget;
    q19_12 dist1;
    q19_12 deltaX;
    q19_12 deltaZ;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);

    if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1))))
    {
        dist1     = Q12(5.5f);
        condCombo = func_8006FD90(stalker, 0, Q12(7.5f), Q12(7.5f));
    }
    else if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
#if defined(MAP1_S00) || defined(MAP1_S01)
        dist1     = Q12(4.5f);
        condCombo = func_8006FD90(stalker, 0, Q12(12.f), Q12(0.0f));
#else
        dist1     = Q12(6.0f);
        condCombo = func_8006FD90(stalker, 0, Q12(16.0f), Q12(0.0f));
#endif
    }
    else
    {
#if defined(MAP1_S00) || defined(MAP1_S01)
        dist1 = Q12(1.0f);
#else
        dist1 = Q12(1.2f);
#endif
        condCombo = func_8006FD90(stalker, 1, Q12(0.4f), Q12(0.4f));
    }

    condCombo |= func_80070360(stalker, distToPlayer, Q12(0.8f));

    if (!(stalkerProps.flags_E8 & StalkerFlag_13))
    {
        if (stalkerProps.flags_E8 & StalkerFlag_11)
        {
            Chara_MoveSpeedUpdate3(stalker, Q12(0.5f), Q12(0.35f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(stalker, Q12(0.5f), Q12(0.7f));
        }
    }

    offsetX      = stalker->position_18.vx - stalkerProps.targetPositionX_F0;
    offsetZ      = stalker->position_18.vz - stalkerProps.targetPositionZ_F4;
    distToTarget = MAX(ABS(offsetX), ABS(offsetZ));

    if (!(stalker->properties_E4.player.afkTimer_E8 & 0x18))
    {
        if (!(Rng_GenerateInt(0, 511) && distToTarget <= Q12(4.0f)) || // 1 in 512 chance.
            (!Rng_GenerateInt(0, 127) &&                               // 1 in 128 chance.
             Rng_GenerateUInt(0, Q12(1.0f) - 1) < FP_TO(distToTarget, Q12_SHIFT) / Q12(4.0f)))
        {
            if (stalkerProps.flags_E8 & StalkerFlag_11)
            {
                deltaX = Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1) - offsetX;
                deltaZ = Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1) - offsetZ;
                stalkerProps.targetHeadingAngle_100 = ratan2(deltaX, deltaZ);
            }
            else
            {
                deltaX = Rng_GenerateInt(Q12(-4.0f), Q12(4.0f) - 1) - offsetX;
                deltaZ = Rng_GenerateInt(Q12(-4.0f), Q12(4.0f) - 1) - offsetZ;
                stalkerProps.targetHeadingAngle_100 = ratan2(deltaX, deltaZ);
            }

            stalkerProps.flags_E8 |= StalkerFlag_3;
        }
    }

    if (!(stalkerProps.flags_E8 & StalkerFlag_4) && func_8007029C(stalker, Q12(1.0f), stalker->rotation_24.vy))
    {
        stalkerProps.targetHeadingAngle_100 = func_8006F99C(stalker, Q12(3.5f), stalker->rotation_24.vy);
        if (stalkerProps.targetHeadingAngle_100 == StalkerFlag_WarpRotation)
        {
            stalkerProps.targetHeadingAngle_100 = stalker->rotation_24.vy + Q12_ANGLE(180.0f);
        }

        stalkerProps.flags_E8 |= StalkerFlag_4;
    }

    // Smoothly rotate toward target direction
    angle = func_8005BF38(stalkerProps.targetHeadingAngle_100 - stalker->rotation_24.vy);

    if (TIMESTEP_ANGLE(1, 4) < ABS(angle))
    {
        if (angle > Q12_ANGLE(0.0f))
        {
            stalker->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(45.0f));
        }
        else
        {
            stalker->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(45.0f));
        }
    }
    else
    {
        stalkerProps.flags_E8 &= ~(StalkerFlag_3 | StalkerFlag_4);
    }

    // Handle aggressive/chase mode.
    if (stalkerProps.flags_E8 & StalkerFlag_11)
    {
        if (!Rng_GenerateInt(0, 1023)) // 1 in 1024 chance.
        {
            stalkerProps.flags_E8 &= ~StalkerFlag_3;
        }

        if (!Rng_GenerateInt(0, 1023)) // 1 in 1024 chance.
        {
            stalkerProps.flags_E8 &= ~StalkerFlag_4;
        }

        if (distToPlayer < Q12(2.0f) && distToPlayer < dist1 && !func_800700F8(stalker, &g_SysWork.playerWork_4C.player_0))
        {
            stalkerProps.timer_F8  = Q12(5.0f);
            stalkerProps.flags_E8 |= StalkerFlag_0;
            stalkerProps.flags_E8 &= ~StalkerFlag_11;
        }
    }

    if ((stalkerProps.flags_E8 & StalkerFlag_0))
    {
        if ((stalkerProps.flags_E8 & StalkerFlag_10) || condCombo)
        {
            if (condCombo)
            {
                stalkerProps.targetPositionX_F0 = g_SysWork.playerWork_4C.player_0.position_18.vx;
                stalkerProps.targetPositionZ_F4 = g_SysWork.playerWork_4C.player_0.position_18.vz;
                stalkerProps.timer_116          = Q12(0.0f);
            }

            if (!(stalkerProps.flags_E8 & StalkerFlag_10))
            {
                stalkerProps.flags_E8 |= StalkerFlag_10;
                sharedFunc_800D7E04_0_s00(stalker, Sfx_Unk1363);
            }

            if (((!Rng_GenerateInt(0, 15) && stalkerProps.timer_F8 > Q12(1.0f)) && // 1 in 16 chance.
                 (stalkerProps.flags_E8 & StalkerFlag_1)) ||
                (!Rng_GenerateInt(0, 15) && stalkerProps.timer_F8 > Q12(2.5f)) ||  // 1 in 16 chance.
                (!Rng_GenerateInt(0, 31) && ((dist1 >> 1) < distToPlayer)))        // 1 in 32 chance.
            {
                if (stalkerProps.flags_E8 & StalkerFlag_1)
                {
                    stalker->model_0.controlState_2 = StalkerControl_2;
                }
                else
                {
                    stalker->model_0.controlState_2 = StalkerControl_3;
                }

                stalkerProps.flags_E8 &= ~(StalkerFlag_3 | StalkerFlag_4);
            }
            else
            {
                stalkerProps.timer_F8 += g_DeltaTime0;
            }
        }
    }

    if (!condCombo)
    {
        if (stalkerProps.flags_E8 & StalkerFlag_10)
        {
            stalkerProps.timer_116 += g_DeltaTime0;

            if (!Rng_GenerateInt(0, 4095) || stalkerProps.timer_116 > Q12(1.2f)) // 1 in 4096 chance.
            {
                stalkerProps.timer_116 = Q12(0.0f);
                stalkerProps.flags_E8 &= ~StalkerFlag_10;
            }
        }
    }
}

void Ai_Stalker_Control_5(s_SubCharacter* stalker)
{
    #define DIST_TO_PLAYER_MAX Q12(0.9f)
    #define MOVE_SPEED_MAX     Q12(0.7f)

    q3_12  angleDeltaToPlayer;
    q19_12 distToPlayer;
    q19_12 angle1;
    q19_12 newMoveSpeed0;
    s32    i;
    q19_12 newMoveSpeed1;

    if (ANIM_STATUS_IDX_GET(stalker->model_0.anim_4.status_0) == StalkerAnim_30)
    {
        stalker->model_0.controlState_2 = StalkerControl_4;
        g_SysWork.field_2284[3] &= ~(1 << 1);
        return;
    }

    if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 62, 64))
    {
        stalker->moveSpeed_38 = Q12(0.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 50, 61))
    {
        distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                           g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);

        for (i = 0; i < 6; i++)
        {
            angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(stalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                               stalker->rotation_24.vy);
            angle1 = TIMESTEP_ANGLE(3, 3); // @hack `(g_DeltaTime0 / 3) >> 3` should be same as `g_DeltaTime / 24`, but that doesn't match?
            if ((angleDeltaToPlayer >= Q12_ANGLE(0.0f) && angle1 <  angleDeltaToPlayer) ||
                (angleDeltaToPlayer <  Q12_ANGLE(0.0f) && angle1 < -angleDeltaToPlayer))
            {
                if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
                {
                    stalker->rotation_24.vy = Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 0.0833f) + stalker->rotation_24.vy;
                }
                else
                {
                    stalker->rotation_24.vy = stalker->rotation_24.vy - Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 0.0833f);
                }
            }
        }

        if (!(stalkerProps.flags_E8 & StalkerFlag_13))
        {
            if (distToPlayer > DIST_TO_PLAYER_MAX)
            {
                if (stalker->moveSpeed_38 > MOVE_SPEED_MAX)
                {
                    newMoveSpeed0 = stalker->moveSpeed_38 - Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 1.0f);
                    if (newMoveSpeed0 < MOVE_SPEED_MAX)
                    {
                        newMoveSpeed0 = MOVE_SPEED_MAX;
                    }
                }
                else
                {
                    newMoveSpeed0 = MOVE_SPEED_MAX;
                    newMoveSpeed1 = stalker->moveSpeed_38 + Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 1.0f);
                    if (newMoveSpeed1 <= MOVE_SPEED_MAX)
                    {
                        newMoveSpeed0 = newMoveSpeed1;
                    }
                }

                stalker->moveSpeed_38 = newMoveSpeed0;
                return;
            }

            if (distToPlayer < MOVE_SPEED_MAX)
            {
                if (stalker->moveSpeed_38 > -MOVE_SPEED_MAX)
                {
                    newMoveSpeed0 = stalker->moveSpeed_38 - Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 1.0f);
                    if (newMoveSpeed0 < -MOVE_SPEED_MAX)
                    {
                        newMoveSpeed0 = -MOVE_SPEED_MAX;
                    }
                }
                else
                {
                    newMoveSpeed0 = -MOVE_SPEED_MAX;
                    newMoveSpeed1 = stalker->moveSpeed_38 + Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 1.0f);
                    if (newMoveSpeed1 <= -MOVE_SPEED_MAX)
                    {
                        newMoveSpeed0 = newMoveSpeed1;
                    }
                }

                stalker->moveSpeed_38 = newMoveSpeed0;
                return;
            }

            Chara_MoveSpeedUpdate(stalker, Q12(6.0f));
        }
    }
    else
    {
        Chara_MoveSpeedUpdate(stalker, Q12(6.0f));
    }
}

void Ai_Stalker_Control_6(s_SubCharacter* stalker)
{
    VECTOR3 vec0;
    q3_12   angleDeltaToPlayer;
    q3_12   moveSpeed;
    q19_12  distToPlayer;
    s32     i;
    u32     animStatus;

    stalker->field_E1_0 = 3;
    Chara_MoveSpeedUpdate(stalker, Q12(1.5f));

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                               g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);

    moveSpeed = Q12(0.0f);
    angleDeltaToPlayer = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                              g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz) -
                                       stalker->rotation_24.vy);

    if (ABS(angleDeltaToPlayer) < Q12_ANGLE(45.0f))
    {
        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_34, true) && distToPlayer > Q12(0.53f))
        {
            moveSpeed = Q12_MULT_PRECISE(g_DeltaTime0, Q12(1.0f));
        }
        else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_35, true) && distToPlayer > Q12(0.38f))
        {
            moveSpeed = Q12_MULT_PRECISE(g_DeltaTime0, Q12(1.0f));
        }
    }

    for (i = 0; i < 3; i++)
    {
        if (TIMESTEP_ANGLE(1, 4) < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
            {
                stalker->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(45.0f));
            }
            else
            {
                stalker->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(45.0f));
            }
        }

        angleDeltaToPlayer = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                                  g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz) -
                                           stalker->rotation_24.vy);
    }

    if (stalkerProps.flags_E8 & StalkerFlag_5)
    {
        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_9, true))
        {
            if (distToPlayer < Q12(0.52f) || distToPlayer > Q12(0.54f))
            {
                moveSpeed = CLAMP_HIGH(Q12_MULT_PRECISE(g_DeltaTime0, Q12(1.0f)), distToPlayer - Q12(0.53f));
            }

            stalkerProps.relAnimTime_104 = stalker->model_0.anim_4.time_4 - Q12(83.0f);
        }
        else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_8, true))
        {
            if (distToPlayer < Q12(0.37f) || distToPlayer > Q12(0.39f))
            {
                moveSpeed = CLAMP_HIGH(Q12_MULT_PRECISE(g_DeltaTime0, Q12(1.0f)), distToPlayer - Q12(0.38f));
            }

            stalkerProps.relAnimTime_104 = stalker->model_0.anim_4.time_4 - Q12(70.0f);
        }
        else
        {
            stalkerProps.relAnimTime_104 = Q12(0.0f);
        }

        stalker->rotation_24.vy = Math_AngleBetweenPositionsGet(stalker->position_18, g_SysWork.playerWork_4C.player_0.position_18);

        if (g_SysWork.playerWork_4C.player_0.attackReceived_41 == NO_VALUE)
        {
            g_SysWork.field_2284[3]         &= ~(1 << 0);
            animStatus                       = stalker->model_0.anim_4.status_0;
            stalker->model_0.controlState_2  = StalkerControl_9;
            stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_10, false);
            stalkerProps.keyframeIdx_FC      = animStatus;
            stalker->field_E1_0              = 0;
            stalker->field_E1_0              = 3;

            stalkerProps.flags_E8 |= StalkerFlag_6;
            stalkerProps.flags_E8 &= ~StalkerFlag_5;
        }
        else
        {
            stalkerProps.timer_F8 += g_DeltaTime0;
            if (stalkerProps.timer_F8 > Q12(1.5f))
            {
                g_SysWork.playerWork_4C.player_0.damage_B4.amount_C += (FP_TO(D_800AD4C8[50].field_4, Q12_SHIFT) * Rng_GenerateUInt(85, 116)) / 100;
                stalkerProps.timer_F8              = Rng_Rand16() % Q12(0.5f);
            }
        }
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 472, 476))
    {
        vec0.vx = stalker->position_18.vx;
        vec0.vy = stalker->position_18.vy + stalker->field_C8.field_8;
        vec0.vz = stalker->position_18.vz;

        // TODO: What's weapon attack 49?
        if (func_8008A0E4(1, 49, stalker, &vec0, &g_SysWork.playerWork_4C, stalker->rotation_24.vy, Q12_ANGLE(90.0f)) != NO_VALUE)
        {
            stalkerProps.flags_E8 |= StalkerFlag_5;
            g_SysWork.field_2284[3] &= ~(1 << 1);

            sharedFunc_800D7E04_0_s00(stalker, Sfx_Unk1366);

            stalkerProps.timer_F8 = Q12(1.0f);
        }
    }
    else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_9, true) ||
             stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_8, true) ||
             distToPlayer > Q12(2.0f))
    {
        g_SysWork.field_2284[3] &= ~((1 << 0) | (1 << 1));
        stalker->model_0.controlState_2 = StalkerControl_9;

        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_34, true) ||
            stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_9,  false))
        {
            stalkerProps.keyframeIdx_FC = ANIM_STATUS(StalkerAnim_9, true);
        }
        else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_35, true) ||
                 stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_8,  false))
        {
            stalkerProps.keyframeIdx_FC = ANIM_STATUS(StalkerAnim_8, true);
        }
        else
        {
            stalkerProps.keyframeIdx_FC = stalker->model_0.anim_4.status_0;
        }

        stalkerProps.flags_E8 |= StalkerFlag_6;
        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_36, false);
        stalker->field_E1_0 = 3;
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        stalkerProps.offset_EC = Q12_MULT(moveSpeed, Math_Sin(stalker->rotation_24.vy));
        stalkerProps.offset_EE = Q12_MULT(moveSpeed, Math_Cos(stalker->rotation_24.vy));
    }
}

void Ai_Stalker_Control_7(s_SubCharacter* stalker)
{
    u16 flags;

    if (!(stalkerProps.flags_E8 & StalkerFlag_13))
    {
        Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_27, true) &&
        !Rng_GenerateInt(0, 3)) // 1 in 4 chance.
    {
        flags = stalkerProps.flags_E8;
        if (!(flags & StalkerFlag_13))
        {
            stalker->model_0.controlState_2  = (flags & StalkerFlag_1) ? StalkerControl_2 : StalkerControl_3;
            stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_30, false);
            stalkerProps.keyframeIdx_FC      = ANIM_STATUS(StalkerAnim_27, true);
            stalkerProps.relKeyframeIdx_FE   = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 427);
        }
    }
}

void Ai_Stalker_Control_8(s_SubCharacter* stalker)
{
#if defined(MAP1_S00) || defined(MAP1_S01)
    #define BASE_DIST_MAX Q12(6.0f)
#else
    #define BASE_DIST_MAX Q12(8.0f)
#endif

    u32    activeKeyframeIdx;
    s32    animDivTmp;
    s32    animDiv;
    s32    step;
    q19_12 animMult;
    s32    frameIdx;
    s32    flags;
    s32    cond;
    q19_12 duration;

    stalker->flags_3E &= ~CharaFlag_Unk2;
    if (!(stalkerProps.flags_E8 & StalkerFlag_13))
    {
        Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
    }

    Chara_MoveSpeedUpdate(stalker, Q12(1.5f));

    activeKeyframeIdx = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);
    animDivTmp = 0;
    animMult = Q12(0.0f);

    if (activeKeyframeIdx >= 110 && activeKeyframeIdx < 117)
    {
        animMult = Q12(0.3f);
        animDivTmp = 7;
    }
    else if (activeKeyframeIdx >= 117 && activeKeyframeIdx < 121)
    {
        animMult = Q12(0.3f);
        animDivTmp = 4;
    }
    else if (activeKeyframeIdx >= 121 && activeKeyframeIdx < 124)
    {
        animMult = Q12(0.1f);
        animDivTmp = 4;
    }

    if (animMult != Q12(0.0f))
    {
        animDiv  = FP_TO(animDivTmp, Q12_SHIFT);
        duration = STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant;
        step     = (Q12_MULT_PRECISE(duration, g_DeltaTime0) * animMult) / animDiv;

        stalkerProps.offset_EC = Q12_MULT(step, Math_Sin(stalker->rotation_24.vy));
        stalkerProps.offset_EE = Q12_MULT(step, Math_Cos(stalker->rotation_24.vy));
    }

    if (stalkerProps.flags_E8 & StalkerFlag_7)
    {
        frameIdx = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);
        if ((frameIdx >= 121 && frameIdx < 129) ||
            (frameIdx >= 149 && frameIdx < 158) ||
            (frameIdx >= 171 && frameIdx < 176))
        {
            stalkerProps.flags_E8 &= ~StalkerFlag_7;
        }
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_27, true) && !Rng_GenerateInt(0, 3)) // 1 in 4 chance.
    {
        if (stalkerProps.flags_E8 & StalkerFlag_1)
        {
            stalker->model_0.controlState_2 = StalkerControl_2;
        }
        else
        {
            stalker->model_0.controlState_2 = StalkerControl_3;
        }

        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_30, false);
        stalkerProps.keyframeIdx_FC      = ANIM_STATUS(StalkerAnim_27, true);
        stalkerProps.relKeyframeIdx_FE   = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 427);
    }

    // @hack `animDiv` has to be used for certain stuff for a match, weird.
    animDiv = g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0;
    flags = animDiv & 0x3;
    if (flags == 0)
    {
        cond = func_8006FD90(stalker, 0, Q12(7.5f), Q12(0.0f));
    }
    else if (flags == (1 << 1))
    {
        cond = func_8006FD90(stalker, 0, BASE_DIST_MAX, Q12(0.0f));
    }
    else
    {
        cond = func_8006FD90(stalker, 1, Q12(0.4f), Q12(0.0f));
    }

    if (cond || func_80070360(stalker, Q12(0.0f), Q12(1.0f)))
    {
        stalkerProps.targetPositionX_F0 = g_SysWork.playerWork_4C.player_0.position_18.vx;
        stalkerProps.targetPositionZ_F4 = g_SysWork.playerWork_4C.player_0.position_18.vz;
    }

    #undef BASE_DIST_MAX
}

void Ai_Stalker_Control_9(s_SubCharacter* stalker)
{
    #define FRICTION_PER_FRAME 1.5f // TODO: Or is it per tick?

    q19_12 dist;
    s32    distDiv;
    q19_12 angleOffset;

    if (stalker->health_B0 < sharedData_800E3A24_0_s00)
    {
        stalker->flags_3E |= CharaFlag_Unk2;
    }

    stalkerProps.flags_E8 |= StalkerFlag_6;
    if (!(stalkerProps.flags_E8 & StalkerFlag_13))
    {
        Chara_MoveSpeedUpdate(stalker, Q12(FRICTION_PER_FRAME));
    }

    distDiv = 0;
    angleOffset = Q12_ANGLE(0.0f);
    dist = Q12(0.0f);

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_24, false))
    {
        dist = Q12(0.15f);
        distDiv = 1;
        angleOffset = Q12_ANGLE(180.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 395, 402))
    {
        dist = Q12(1.0f);
        distDiv = 8 - stalkerProps.relKeyframeIdx_FE;
        angleOffset = Q12_ANGLE(180.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 407, 412))
    {
        dist = Q12(0.5f);
        distDiv = 5;
        angleOffset = Q12_ANGLE(0.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 0, 3))
    {
        dist = Q12(0.1f);
        distDiv = 4;
        angleOffset = Q12_ANGLE(180.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 9, 17))
    {
        dist = Q12(0.3f);
        distDiv = 9;
        angleOffset = Q12_ANGLE(180.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 4, 6))
    {
        dist = Q12(0.4f);
        distDiv = 3;
        angleOffset = Q12_ANGLE(180.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 20, 23))
    {
        dist = Q12(0.1f);
        distDiv = 5;
        angleOffset = Q12_ANGLE(0.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 27, 32))
    {
        dist = Q12(0.3f);
        distDiv = 6;
        angleOffset = Q12_ANGLE(0.0f);
    }
    else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_45, true) &&
             ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 159, 167))
    {
        dist = Q12(0.3f);
        distDiv = 8;
        angleOffset = Q12_ANGLE(180.0f);
    }
    else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_10, true) &&
             ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 96, 100))
    {
        dist = Q12(0.2f);
        distDiv = 5;
        angleOffset = Q12_ANGLE(180.0f);
    }

    if (dist != Q12(0.0f))
    {
        dist = (s32)(dist * (u32)Q12_MULT_PRECISE(STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0)) /
               FP_TO(distDiv, Q12_SHIFT);

        stalkerProps.offset_EC = Q12_MULT(dist, Math_Sin(stalker->rotation_24.vy + angleOffset));
        stalkerProps.offset_EE = Q12_MULT(dist, Math_Cos(stalker->rotation_24.vy + angleOffset));
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_26, true) ||
        stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_17, true) ||
        stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_18, true))
    {
        if (stalker->health_B0 == Q12(0.0f) && stalker->moveSpeed_38 == Q12(0.0f))
        {
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_26, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_21, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_17, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_19, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_18, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_20, false);
            }

            stalker->model_0.controlState_2 = StalkerControl_10;
            Savegame_EnemyStateUpdate(stalker);
        }

        if (stalker->health_B0 > sharedData_800E3A24_0_s00 &&
            !Rng_GenerateInt(0, 7) && // 1 in 8 chance.
            !(stalkerProps.flags_E8 & StalkerFlag_13))
        {
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_26, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_11, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_17, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_12, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_18, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_13, false);
            }

            stalker->model_0.controlState_2 = StalkerControl_8;
            stalkerProps.flags_E8 |= StalkerFlag_7;
            stalkerProps.flags_E8 &= ~StalkerFlag_6;
        }
    }
}

void Ai_Stalker_Control_10(s_SubCharacter* stalker)
{
    q19_12 curMoveSpeed;
    q19_12 newMoveSpeed;
    s32    newAnimStatus;

    if (!(stalkerProps.flags_E8 & (1 << 13)))
    {
        // TODO: Use macro.
        curMoveSpeed = stalker->moveSpeed_38;
        if (curMoveSpeed > Q12(0.0f))
        {
            newMoveSpeed = curMoveSpeed - Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 1.5f);
            if (newMoveSpeed < Q12(0.0f))
            {
                newMoveSpeed = Q12(0.0f);
            }
        }
        else
        {
            newMoveSpeed = curMoveSpeed + Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 1.5f);
            if (newMoveSpeed > Q12(0.0f))
            {
                newMoveSpeed = Q12(0.0f);
            }
        }
        stalker->moveSpeed_38 = newMoveSpeed;
    }

    if (stalker->health_B0 == Q12(0.0f))
    {
        stalker->flags_3E &= ~CharaFlag_Unk2;

        if (g_SysWork.targetNpcIdx_2353 != Chara_NpcIdxGet(stalker))
        {
            stalker->health_B0  = NO_VALUE;
            stalker->field_E1_0 = 0;
        }
    }

    // TODO: `stalkerProps.flags_E8` doesn't match?
    if (stalker->moveSpeed_38 == Q12(0.0f) && !(stalker->properties_E4.player.afkTimer_E8 & (StalkerFlag_8 |StalkerFlag_9)))
    {
        newAnimStatus = (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_31, true)) ? ANIM_STATUS(StalkerAnim_Still, true) :
                                                                                                  ANIM_STATUS(StalkerAnim_Still, false);

        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_32, true))
        {
            newAnimStatus = ANIM_STATUS(StalkerAnim_1, false);
        }

        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_33, true))
        {
            newAnimStatus = ANIM_STATUS(StalkerAnim_6, false);
        }

        if (newAnimStatus != ANIM_STATUS(StalkerAnim_Still, false))
        {
#if !defined(MAP5_S02) && !defined(MAP7_S02)
            func_800622B8(3, stalker, newAnimStatus, 3);
#endif
            stalkerProps.flags_E8 |= StalkerFlag_9;
        }
    }

#if defined(MAP5_S02) || defined(MAP7_S02)
    if (stalkerProps.flags_E8 & (1 << 9))
    {
        stalker->timer_C6 += Q12_MULT_FLOAT_PRECISE(g_DeltaTime0, 0.25f);
        if (stalker->timer_C6 > Q12(1.0f))
        {
            stalker->model_0.charaId_0 = Chara_None;
        }
    }
#endif
}

void Ai_Stalker_Control_11(s_SubCharacter* stalker)
{
}

void Ai_Stalker_Control_12(s_SubCharacter* stalker)
{
#if defined(MAP1_S00) || defined(MAP1_S01)
    #define BASE_DIST_MAX Q12(12.0f)
#else
    #define BASE_DIST_MAX Q12(16.0f)
#endif

    q19_12 distToPlayer;
    q3_12  angleDeltaToPlayer;
    s32    cond; // Not `bool`?

    distToPlayer       = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);
    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(stalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       stalker->rotation_24.vy);

    if (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1))))
    {
        cond = func_8006FD90(stalker, 0, Q12(7.5f), Q12(7.5f));
    }
    else if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
        cond = func_8006FD90(stalker, 0, BASE_DIST_MAX, Q12(0.0f));
    }
    else
    {
        cond = func_8006FD90(stalker, 1, Q12(0.4f), Q12(0.8f));
    }

    cond |= func_80070360(stalker, distToPlayer, Q12(1.0f));
    if (!cond)
    {
        return;
    }

    stalkerProps.targetPositionX_F0 = g_SysWork.playerWork_4C.player_0.position_18.vx;
    stalkerProps.targetPositionZ_F4 = g_SysWork.playerWork_4C.player_0.position_18.vz;

    if (distToPlayer < Q12(1.2f) && angleDeltaToPlayer < Q12_ANGLE(180.0f))
    {
        if (!(stalkerProps.flags_E8 & StalkerFlag_1))
        {
            stalker->model_0.controlState_2 = StalkerControl_3;
        }
        else
        {
            stalker->model_0.controlState_2 = StalkerControl_2;
        }

        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_30, false);

        stalkerProps.keyframeIdx_FC    = 55;
        stalkerProps.relKeyframeIdx_FE = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 427);
        stalkerProps.flags_E8         |= StalkerFlag_10;

        sharedFunc_800D7E04_0_s00(stalker, Sfx_Unk1363);
    }

    #undef BASE_DIST_MAX
}

void Ai_Stalker_Control_13(s_SubCharacter* stalker)
{
    if (stalker->model_0.stateStep_3 == 1)
    {
        stalker->model_0.stateStep_3++;
        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_15, false);
    }

    if (!(stalkerProps.flags_E8 & StalkerFlag_14) &&
        stalker->model_0.anim_4.time_4 > Q12(211.0f))
    {
        sharedFunc_800D7E04_0_s00(stalker, Sfx_Unk1365);

        stalker->health_B0     = NO_VALUE;
        stalkerProps.flags_E8 |= StalkerFlag_14;
    }

    if (stalker->model_0.stateStep_3 == 3)
    {
        stalker->model_0.stateStep_3++;
        Character_AnimSet(stalker, ANIM_STATUS(StalkerAnim_47, true), 294);

        if (stalker->health_B0 != NO_VALUE)
        {
            func_8005F6B0(&g_SysWork.npcs_1A0[1], &(VECTOR3){ Q12(140.39f), Q12(-0.55f), Q12(22.76f) }, 3, 3);

            stalker->health_B0     = NO_VALUE;
            stalkerProps.flags_E8 |= StalkerFlag_14;
        }
    }
}

void sharedFunc_800D67FC_0_s00(s_SubCharacter* stalker)
{
    s_800C4590* sp10[7];
    q3_12       newHeadingAngle;
    q19_12      prevMoveSpeed;
    u16         newFlags;

    stalker->fallSpeed_34   = stalker->fallSpeed_34 + g_DeltaTime2;
    newHeadingAngle         = func_8005BF38(stalker->rotation_24.vy);
    stalker->rotation_24.vy = newHeadingAngle;

    if (stalkerProps.flags_E8 & StalkerFlag_13)
    {
        Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
        if (stalker->moveSpeed_38 == Q12(0.0f))
        {
            stalkerProps.flags_E8 &= ~StalkerFlag_13;
        }
    }
    else
    {
        stalker->headingAngle_3C = newHeadingAngle;
    }

    prevMoveSpeed = stalker->moveSpeed_38;
    if (stalkerProps.flags_E8 & StalkerFlag_WarpRotation)
    {
        if (stalker->model_0.controlState_2 == StalkerControl_2)
        {
            stalker->moveSpeed_38 *= 8;
        }
        else
        {
            stalker->moveSpeed_38 *= 2;
        }
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        func_8005CB20(stalker, &sp10, stalkerProps.offset_EC, stalkerProps.offset_EE);
    }

    stalkerProps.offset_EE = Q12(0.0f);
    stalkerProps.offset_EC = Q12(0.0f);
    stalker->moveSpeed_38  = prevMoveSpeed;

    if (stalker->fallSpeed_34 != Q12(0.0f))
    {
        newFlags = stalkerProps.flags_E8 | StalkerFlag_8;
    }
    else
    {
        newFlags = stalkerProps.flags_E8 & ~StalkerFlag_8;
    }
    stalkerProps.flags_E8 = newFlags;
}

void sharedFunc_800D6970_0_s00(s_SubCharacter* stalker, s_AnmHeader* animHdr, GsCOORDINATE2* coord)
{
    typedef struct
    {
        MATRIX  field_0;
        VECTOR  field_20; // Q23.8, then Q10.12.
        SVECTOR field_30;
        VECTOR3 position_38;
        q3_12   angle_44;
        q3_12   angle_46;
    } s_sharedFunc_800D6970_0_s00;

    s32                          temp;
    s_AnimInfo*                  animInfo;
    s_sharedFunc_800D6970_0_s00* ptr;

    WorldGfx_HeldItemAttach(stalker->model_0.charaId_0, 2);

    switch (stalker->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(StalkerAnim_7, false):
            STALKER_ANIM_INFOS[ANIM_STATUS(StalkerAnim_7, false)].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE + 50;
            break;

        case ANIM_STATUS(StalkerAnim_7, true):
            STALKER_ANIM_INFOS[ANIM_STATUS(StalkerAnim_7, true)].startKeyframeIdx_C = (stalkerProps.relKeyframeIdx_FE + 50);

            if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 50, 58))
            {
                STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant = Q12(24.0f);
            }
            else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 59, 65))
            {
                STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant = Q12(32.0f);
            }
            else
            {
                STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant = Q12_MULT_PRECISE(MAX(stalker->moveSpeed_38, Q12(0.1f)), Q12(30.67f));
            }
            break;

        case ANIM_STATUS(StalkerAnim_37, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant = Q12_MULT_PRECISE(MAX(stalker->moveSpeed_38, Q12(1.5f)), Q12(30.67f));
            break;

        case ANIM_STATUS(StalkerAnim_30, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant = Q12_MULT_PRECISE(MAX(stalker->moveSpeed_38, Q12(0.1f)), Q12(30.67f));
            break;

        case ANIM_STATUS(StalkerAnim_1, false):
        case ANIM_STATUS(StalkerAnim_42, false):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE;
            break;

        case ANIM_STATUS(StalkerAnim_1, true):
        case ANIM_STATUS(StalkerAnim_42, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].startKeyframeIdx_C = stalkerProps.relKeyframeIdx_FE;
            break;

        case ANIM_STATUS(StalkerAnim_3, false):
        case ANIM_STATUS(StalkerAnim_43, false):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE + 9;
            break;

        case ANIM_STATUS(StalkerAnim_3, true):
        case ANIM_STATUS(StalkerAnim_43, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].startKeyframeIdx_C = stalkerProps.relKeyframeIdx_FE + 9;
            break;

        case ANIM_STATUS(StalkerAnim_4, false):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE + 20;
            break;

        case ANIM_STATUS(StalkerAnim_4, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].startKeyframeIdx_C = stalkerProps.relKeyframeIdx_FE + 20;
            break;

        case ANIM_STATUS(StalkerAnim_5, false):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE + 25;
            break;

        case ANIM_STATUS(StalkerAnim_5, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].startKeyframeIdx_C = stalkerProps.relKeyframeIdx_FE + 25;
            break;

        case ANIM_STATUS(StalkerAnim_24, false):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].endKeyframeIdx_E = stalkerProps.relKeyframeIdx_FE + 395;
            break;

        case ANIM_STATUS(StalkerAnim_24, true):
            STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].startKeyframeIdx_C = stalkerProps.relKeyframeIdx_FE + 395;
            break;
    }

    Math_MatrixTransform(&stalker->position_18, &stalker->rotation_24, coord);

    animInfo = &STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&stalker->model_0, animHdr, coord, animInfo);

    ptr = PSX_SCRATCH;

    if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 60, 65))
    {
        // TODO: Use macro?
        *(s32*)&ptr->field_30.vx = 0x21FFFB;
        ptr->field_30.vz         = 0x25;
        Vw_CoordHierarchyMatrixCompute(&coord[6], &ptr->field_0);

        gte_SetRotMatrix(&ptr->field_0);
        gte_SetTransMatrix(&ptr->field_0);
        gte_ldv0(&ptr->field_30);
        gte_rt();
        gte_stlvnl(&ptr->field_20);

        // TODO: Q conversion. From Q8 to Q12?
        ptr->field_20.vx = Q8_TO_Q12(ptr->field_20.vx);
        ptr->field_20.vy = Q8_TO_Q12(ptr->field_20.vy);
        ptr->field_20.vz = Q8_TO_Q12(ptr->field_20.vz);

        ptr->position_38.vx = stalker->position_18.vx;
        ptr->position_38.vy = stalker->position_18.vy + stalker->field_C8.field_8;
        ptr->position_38.vz = stalker->position_18.vz;

        // TODO: What's weapon attack 48?
        func_8008A0E4(1, 48, stalker, &ptr->position_38, &g_SysWork.playerWork_4C.player_0,
                      ratan2(ptr->field_20.vx - stalker->position_18.vx, ptr->field_20.vz - stalker->position_18.vz),
                      ratan2(Math_Vector2MagCalc(stalker->position_18.vx - ptr->field_20.vx,
                                                 stalker->position_18.vz - ptr->field_20.vz),
                             ptr->field_20.vy - (stalker->position_18.vy + stalker->field_C8.field_8)));
    }

    ptr->angle_44 = stalkerProps.angle_114;

    if (stalker->model_0.controlState_2 == StalkerControl_2 ||
        stalker->model_0.controlState_2 == StalkerControl_3)
    {
        ptr->angle_46 = func_8005BF38(Math_AngleBetweenPositionsGet(stalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                      stalker->rotation_24.vy);
        temp          = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                            g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);

        if (temp < Q12(3.0f) && ABS(ptr->angle_46) < Q12_ANGLE(45.0f))
        {
            if (sharedData_800E3A18_0_s00 == stalkerProps.targetPositionX_F0 &&
                sharedData_800E3A1C_0_s00 == stalkerProps.targetPositionZ_F4)
            {
                if (ptr->angle_46 > Q12_ANGLE(0.0f))
                {
                    ptr->angle_44 = CLAMP_HIGH(ptr->angle_46, ptr->angle_44 + Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(45.0f)));
                }
                else
                {
                    ptr->angle_44 = MAX(ptr->angle_46, ptr->angle_44 - Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(45.0f)));
                }
            }
        }
        else
        {
            if (ptr->angle_44 > Q12_ANGLE(0.0f))
            {
                ptr->angle_44 = CLAMP_LOW(ptr->angle_44 - Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(45.0f)), Q12_ANGLE(0.0f));
            }
            else
            {
                ptr->angle_44 = MIN(ptr->angle_44 + Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(45.0f)), Q12_ANGLE(0.0f));
            }
        }
    }
    else
    {
        if (ptr->angle_44 > Q12_ANGLE(0.0f))
        {
            ptr->angle_44 = CLAMP_LOW(ptr->angle_44 - Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(45.0f)), Q12_ANGLE(0.0f));
        }
        else
        {
            ptr->angle_44 = MIN(ptr->angle_44 + Q12_MULT_PRECISE(g_DeltaTime0, Q12_ANGLE(45.0f)), Q12_ANGLE(0.0f));
        }
    }

    ptr->field_30.vz         = 0;
    *(s32*)&ptr->field_30.vx = ptr->angle_44 << 16;

    Math_RotMatrixZxyNegGte(&ptr->field_30, &ptr->field_0);
    MulMatrix(&coord[3].coord, &ptr->field_0);

    stalkerProps.angle_114 = ptr->angle_44;
}


// TODO: Size of arrays may be incorrect. One big array doesn't match.
extern s_Keyframe sharedData_800DDBA8_0_s00;
extern s_Keyframe sharedData_800DDBBC_0_s00[9];
extern s_Keyframe sharedData_800DDC70_0_s00[7];
extern s_Keyframe sharedData_800DDCFC_0_s00[7];
extern s_Keyframe sharedData_800DDD88_0_s00[16];
extern s_Keyframe sharedData_800DDEC8_0_s00[5];
extern s_Keyframe sharedData_800DDF2C_0_s00[11];
extern s_Keyframe sharedData_800DE008_0_s00[11];
extern s_Keyframe sharedData_800DE0E4_0_s00[13];
extern s_Keyframe sharedData_800DE1E8_0_s00[11];
extern s_Keyframe sharedData_800DE2C4_0_s00;
extern s_Keyframe sharedData_800DE2D8_0_s00;
extern s_Keyframe sharedData_800DE2EC_0_s00;
extern s_Keyframe sharedData_800DE300_0_s00[16];
extern s_Keyframe sharedData_800DE440_0_s00[16];
extern s_Keyframe sharedData_800DE580_0_s00[42]; // Stalker anim data?
extern s_Keyframe sharedData_800DE8C8_0_s00[29];
extern s_Keyframe sharedData_800DEB0C_0_s00[18]; // Stalker anim data? Index is keyframe index.
extern s_Keyframe sharedData_800DEC74_0_s00[3];
extern s_Keyframe sharedData_800DECB0_0_s00[12];
extern s_Keyframe sharedData_800DEDA0_0_s00[5];
extern s_Keyframe sharedData_800DEE04_0_s00[3];
extern s_Keyframe sharedData_800DEE40_0_s00[2];
extern s_Keyframe sharedData_800DEE68_0_s00[9];
extern s_Keyframe sharedData_800DEF1C_0_s00[30];

#define CopyData(arg0, data)                  \
{                                             \
    s32 __temp;                               \
                                              \
    arg0->field_C8.field_0   = data.field_0;  \
                                              \
    __temp                   = data.field_2;  \
    arg0->field_C8.field_2   = __temp;        \
    arg0->field_C8.field_4   = data.field_4;  \
                                              \
    __temp                   = data.field_6;  \
    arg0->field_C8.field_6   = __temp;        \
    arg0->field_D8.offsetX_4 = data.field_10; \
                                              \
    __temp                   = data.field_12; \
    arg0->field_D8.offsetZ_6 = __temp;        \
    arg0->field_D4.radius_0   = data.field_8;  \
    arg0->field_D8.offsetX_0 = data.field_C;  \
                                              \
    __temp                   = data.field_E;  \
    arg0->field_D8.offsetZ_2 = __temp;        \
                                              \
    __temp                   = data.field_A;  \
    arg0->field_D4.field_2   = __temp;        \
}

void sharedFunc_800D70C4_0_s00(s_SubCharacter* stalker)
{
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 keyframeIdx2;

    switch (stalker->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(StalkerAnim_8, false):
        case ANIM_STATUS(StalkerAnim_9, false):
            func_80070400(stalker, &sharedData_800DE440_0_s00[15], &sharedData_800DDBA8_0_s00);
            break;

        case ANIM_STATUS(StalkerAnim_8, true):
        case ANIM_STATUS(StalkerAnim_9, true):
            CopyData(stalker, sharedData_800DDBA8_0_s00);
            break;

        case ANIM_STATUS(StalkerAnim_38, false):
            if (stalkerProps.keyframeIdx_FC == NO_VALUE)
            {
                func_80070400(stalker, &sharedData_800DE2C4_0_s00, &sharedData_800DDBBC_0_s00[0]);
            }
            else
            {
                func_80070400(stalker, &sharedData_800DE580_0_s00[20], &sharedData_800DDBBC_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_21, false):
            func_80070400(stalker, &sharedData_800DE2C4_0_s00, &sharedData_800DDBBC_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_21, true):
        case ANIM_STATUS(StalkerAnim_38, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 353);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 352);
            func_80070400(stalker, &sharedData_800DDBBC_0_s00[keyframeIdx0], &sharedData_800DDBBC_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_31, false):
        case ANIM_STATUS(StalkerAnim_31, true):
            CopyData(stalker, sharedData_800DDBBC_0_s00[8]);
            break;

        case ANIM_STATUS(StalkerAnim_19, false):
            func_80070400(stalker, &sharedData_800DE2D8_0_s00, &sharedData_800DDC70_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_39, false):
            if (stalkerProps.keyframeIdx_FC == NO_VALUE)
            {
                func_80070400(stalker, &sharedData_800DE2D8_0_s00, &sharedData_800DDC70_0_s00[0]);
            }
            else
            {
                func_80070400(stalker, &sharedData_800DE8C8_0_s00[stalkerProps.keyframeIdx_FC], &sharedData_800DDC70_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_19, true):
        case ANIM_STATUS(StalkerAnim_39, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 339);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 338);
            func_80070400(stalker, &sharedData_800DDC70_0_s00[keyframeIdx0], &sharedData_800DDC70_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_32, false):
        case ANIM_STATUS(StalkerAnim_32, true):
            CopyData(stalker, sharedData_800DDC70_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_20, false):
            func_80070400(stalker, &sharedData_800DE2EC_0_s00, &sharedData_800DDCFC_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_40, false):
            if (stalkerProps.keyframeIdx_FC == NO_VALUE)
            {
                func_80070400(stalker, &sharedData_800DE2EC_0_s00, &sharedData_800DDCFC_0_s00[0]);
            }
            else
            {
                func_80070400(stalker, &sharedData_800DEB0C_0_s00[stalkerProps.keyframeIdx_FC], &sharedData_800DDCFC_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_20, true):
        case ANIM_STATUS(StalkerAnim_40, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 346);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 345);
            func_80070400(stalker, &sharedData_800DDCFC_0_s00[keyframeIdx0], &sharedData_800DDCFC_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_33, false):
        case ANIM_STATUS(StalkerAnim_33, true):
            CopyData(stalker, sharedData_800DDCFC_0_s00[6]);
            break;

        case ANIM_STATUS(StalkerAnim_22, false):
            CopyData(stalker, sharedData_800DDD88_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_22, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 362);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 361);
            func_80070400(stalker, &sharedData_800DDD88_0_s00[keyframeIdx0], &sharedData_800DDD88_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_23, false):
        case ANIM_STATUS(StalkerAnim_41, false):
            CopyData(stalker, sharedData_800DDEC8_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_23, true):
        case ANIM_STATUS(StalkerAnim_41, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 378);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 377);
            func_80070400(stalker, &sharedData_800DDEC8_0_s00[keyframeIdx0], &sharedData_800DDEC8_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_36, false):
            func_80070400(stalker, &sharedData_800DDBA8_0_s00, &sharedData_800DE008_0_s00[6]);
            break;

        case ANIM_STATUS(StalkerAnim_10, false):
            func_80070400(stalker, &sharedData_800DDBA8_0_s00, &sharedData_800DE008_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_10, true):
        case ANIM_STATUS(StalkerAnim_36, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 96);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 95);
            func_80070400(stalker, &sharedData_800DE008_0_s00[keyframeIdx0], &sharedData_800DE008_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_24, false):
            if (stalkerProps.relKeyframeIdx_FE != 0)
            {
                func_80070400(stalker,
                              &sharedData_800DDD88_0_s00[stalkerProps.keyframeIdx_FC],
                              &sharedData_800DE0E4_0_s00[stalkerProps.relKeyframeIdx_FE]);
            }
            else
            {
                CopyData(stalker, sharedData_800DE0E4_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_24, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 394);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 393);
            func_80070400(stalker, &sharedData_800DE0E4_0_s00[keyframeIdx0], &sharedData_800DE0E4_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_25, false):
            if (stalkerProps.relKeyframeIdx_FE == 83)
            {
                func_80070400(stalker, &sharedData_800DDF2C_0_s00[0], &sharedData_800DE1E8_0_s00[1]);
            }
            else
            {
                keyframeIdx0 = stalkerProps.keyframeIdx_FC;
                if (stalkerProps.relKeyframeIdx_FE == 23)
                {
                    func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx0 + 20], &sharedData_800DE1E8_0_s00[1]);
                }
                else if (stalkerProps.relKeyframeIdx_FE == 25)
                {
                    func_80070400(stalker, &sharedData_800DE8C8_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[1]);
                }
                else if (stalkerProps.relKeyframeIdx_FE == 27)
                {
                    func_80070400(stalker, &sharedData_800DEB0C_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[1]);
                }
            }
            break;

        case ANIM_STATUS(StalkerAnim_25, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 407);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 406);
            func_80070400(stalker, &sharedData_800DE1E8_0_s00[keyframeIdx0], &sharedData_800DE1E8_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_26, false):
        case ANIM_STATUS(StalkerAnim_26, true):
            CopyData(stalker, sharedData_800DE2C4_0_s00);
            break;

        case ANIM_STATUS(StalkerAnim_17, false):
        case ANIM_STATUS(StalkerAnim_17, true):
            CopyData(stalker, sharedData_800DE2D8_0_s00);
            break;

        case ANIM_STATUS(StalkerAnim_18, false):
        case ANIM_STATUS(StalkerAnim_18, true):
            CopyData(stalker, sharedData_800DE2EC_0_s00);
            break;

        case ANIM_STATUS(StalkerAnim_27, false):
            CopyData(stalker, sharedData_800DE300_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_27, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 427);
            if (keyframeIdx0 != 15)
            {
                keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 426);
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(stalker, &sharedData_800DE300_0_s00[keyframeIdx0], &sharedData_800DE300_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_34, false):
        case ANIM_STATUS(StalkerAnim_35, false):
            keyframeIdx0 = stalkerProps.keyframeIdx_FC;
            keyframeIdx1 = 0;
            func_80070400(stalker, &sharedData_800DEF1C_0_s00[keyframeIdx0], &sharedData_800DE440_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_34, true):
        case ANIM_STATUS(StalkerAnim_35, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 461);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 460);
            func_80070400(stalker, &sharedData_800DE440_0_s00[keyframeIdx0], &sharedData_800DE440_0_s00[keyframeIdx1]);

            stalker->field_C8.field_8 = stalker->field_C8.field_6;
            break;

        case ANIM_STATUS(StalkerAnim_11, false):
            func_80070400(stalker, &sharedData_800DE2C4_0_s00, &sharedData_800DE580_0_s00[20]);
            break;

        case ANIM_STATUS(StalkerAnim_11, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 107);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 106);
            func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx0 + 20], &sharedData_800DE580_0_s00[keyframeIdx1 + 20]);
            break;

        case ANIM_STATUS(StalkerAnim_12, false):
            func_80070400(stalker, &sharedData_800DE2D8_0_s00, &sharedData_800DE8C8_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_12, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 129);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 128);
            func_80070400(stalker, &sharedData_800DE8C8_0_s00[keyframeIdx0], &sharedData_800DE8C8_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_13, false):
            func_80070400(stalker, &sharedData_800DE2EC_0_s00, &sharedData_800DEB0C_0_s00[0]);
            break;

        case ANIM_STATUS(StalkerAnim_13, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 158);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 157);
            func_80070400(stalker, &sharedData_800DEB0C_0_s00[keyframeIdx0], &sharedData_800DEB0C_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_7, false):
            keyframeIdx0 = stalkerProps.keyframeIdx_FC;
            keyframeIdx1 = stalkerProps.relKeyframeIdx_FE;
            func_80070400(stalker, &sharedData_800DEF1C_0_s00[keyframeIdx0], &sharedData_800DE580_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_7, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 50);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 49);
            func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx0], &sharedData_800DE580_0_s00[keyframeIdx1]);

            stalker->field_C8.field_8                                      = Q12(-0.7f);
            stalkerProps.keyframeIdx_FC = 15;
            break;

        case ANIM_STATUS(StalkerAnim_1, false):
        case ANIM_STATUS(StalkerAnim_42, false):
            func_80070400(stalker,
                          &sharedData_800DE580_0_s00[19 + stalkerProps.keyframeIdx_FC],
                          &sharedData_800DEC74_0_s00[stalkerProps.relKeyframeIdx_FE]);
            break;

        case ANIM_STATUS(StalkerAnim_1, true):
        case ANIM_STATUS(StalkerAnim_42, true):
            keyframeIdx0 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);
            keyframeIdx1 = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) + 1;
            func_80070400(stalker, &sharedData_800DEC74_0_s00[keyframeIdx0], &sharedData_800DEC74_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_3, false):
        case ANIM_STATUS(StalkerAnim_43, false):
            func_80070400(stalker,
                          &sharedData_800DE580_0_s00[19 + stalkerProps.keyframeIdx_FC],
                          &sharedData_800DECB0_0_s00[stalkerProps.relKeyframeIdx_FE]);
            break;

        case ANIM_STATUS(StalkerAnim_3, true):
        case ANIM_STATUS(StalkerAnim_43, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 10);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 9);
            func_80070400(stalker, &sharedData_800DECB0_0_s00[keyframeIdx0 + 1], &sharedData_800DECB0_0_s00[keyframeIdx1 + 1]);
            break;

        case ANIM_STATUS(StalkerAnim_2, false):
        case ANIM_STATUS(StalkerAnim_44, false):
            keyframeIdx2 = stalkerProps.keyframeIdx_FC;
            keyframeIdx2--;
            keyframeIdx1 = 0;
            func_80070400(stalker, &sharedData_800DE580_0_s00[keyframeIdx2 + 20], &sharedData_800DEDA0_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_2, true):
        case ANIM_STATUS(StalkerAnim_44, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 4);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 3);
            func_80070400(stalker, &sharedData_800DEDA0_0_s00[keyframeIdx0], &sharedData_800DEDA0_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_4, false):
            func_80070400(stalker,
                          &sharedData_800DE8C8_0_s00[stalkerProps.keyframeIdx_FC],
                          &sharedData_800DEE04_0_s00[stalkerProps.relKeyframeIdx_FE]);
            break;

        case ANIM_STATUS(StalkerAnim_4, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 20);
            keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 19);
            func_80070400(stalker, &sharedData_800DEE04_0_s00[keyframeIdx0], &sharedData_800DEE04_0_s00[keyframeIdx1]);
            break;

        case ANIM_STATUS(StalkerAnim_5, false):
            if (stalkerProps.relKeyframeIdx_FE >= 2)
            {
                func_80070400(stalker,
                              &sharedData_800DE8C8_0_s00[stalkerProps.keyframeIdx_FC],
                              &sharedData_800DEE40_0_s00[stalkerProps.relKeyframeIdx_FE]);
            }
            else
            {
                CopyData(stalker, sharedData_800DEE68_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_5, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 25);
            func_80070400(stalker, &sharedData_800DEE68_0_s00[keyframeIdx0], &sharedData_800DEE68_0_s00[keyframeIdx0 + 1]);
            break;

        case ANIM_STATUS(StalkerAnim_45, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 158);
            func_80070400(stalker, &sharedData_800DEB0C_0_s00[keyframeIdx0 + 1], &sharedData_800DEB0C_0_s00[keyframeIdx0]);
            break;

        case ANIM_STATUS(StalkerAnim_30, false):
            if (stalkerProps.keyframeIdx_FC == 15)
            {
                func_80070400(stalker, &sharedData_800DE580_0_s00[19], &sharedData_800DEF1C_0_s00[0]);
            }
            else if (stalkerProps.keyframeIdx_FC == 55)
            {
                func_80070400(stalker, &sharedData_800DE300_0_s00[stalkerProps.relKeyframeIdx_FE], &sharedData_800DEF1C_0_s00[0]);
            }
            break;

        case ANIM_STATUS(StalkerAnim_30, true):
        case ANIM_STATUS(StalkerAnim_37, true):
            keyframeIdx0 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 477);
            if (keyframeIdx0 != 29)
            {
                keyframeIdx1 = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 476);
            }
            else
            {
                keyframeIdx1 = 0;
            }

            func_80070400(stalker, &sharedData_800DEF1C_0_s00[keyframeIdx0], &sharedData_800DEF1C_0_s00[keyframeIdx1]);
            break;
    }

    func_8005C814(&stalker->field_D8, stalker);
}

void sharedFunc_800D7BE8_0_s00(s_SubCharacter* stalker)
{
    if (stalkerProps.field_10A == 0)
    {
        if (!(stalkerProps.flags_E8 & StalkerFlag_10))
        {
            if (!(stalkerProps.flags_E8 & StalkerFlag_6) && stalker->model_0.controlState_2 != 12)
            {
                stalkerProps.timer_108 += g_DeltaTime0;
                Rng_Rand16();
            }
        }
    }
    else
    {
        switch (stalkerProps.sfxId_102)
        {
            case Sfx_Unk1365:
                if (stalkerProps.timer_108 > Q12(0.2f) &&
                    stalkerProps.timer_108 < Q12(1.2f))
                {
                    func_8005DC1C(Sfx_Unk1365, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    stalkerProps.timer_108 += Q12(1.0f);
                }
                else if (stalkerProps.timer_108 < Q12(0.0f) ||
                         stalkerProps.timer_108 > Q12(1.8f))
                {
                    stalkerProps.field_10A = 0;
                }

                stalkerProps.timer_108 += g_DeltaTime0;
                break;

            case Sfx_Unk1364:
                stalkerProps.timer_108 += g_DeltaTime0;
                if (stalkerProps.timer_108 <= Q12(0.6f) ||
                    stalkerProps.timer_108 >= Q12(1.6f))
                {
                    if (stalkerProps.timer_108 < Q12(0.0f) ||
                        stalkerProps.timer_108 > Q12(2.8f))
                    {
                        stalkerProps.field_10A = 0;
                    }
                    break;
                }

                func_8005DC1C(stalkerProps.sfxId_102, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                stalkerProps.timer_108 += Q12(1.0f);
                break;

            case Sfx_Unk1363:
                stalkerProps.timer_108 += g_DeltaTime0;
                if (stalkerProps.timer_108 < Q12(0.0f) ||
                    stalkerProps.timer_108 > Q12(0.5f))
                {
                    if (Rng_GenerateInt(0, 7)) // 7 in 8 chance?
                    {
                        func_8005DC1C(Sfx_Unk1363, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    }

                    stalkerProps.field_10A = 0;
                }
                break;

            case Sfx_Unk1366:
                stalkerProps.timer_108 += g_DeltaTime0;
                if (stalkerProps.timer_108 > Q12(0.2f) &&
                    stalkerProps.timer_108 < Q12(1.2f))
                {
                    func_8005DC1C(stalkerProps.sfxId_102, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    stalkerProps.timer_108 += Q12(1.0f);
                }
                else if (stalkerProps.timer_108 < Q12(0.0f) ||
                         stalkerProps.timer_108 > Q12(3.0f))
                {
                    stalkerProps.field_10A = 0;
                }
                break;
        }
    }
}

void sharedFunc_800D7E04_0_s00(s_SubCharacter* stalker, s32 sfxId)
{
    s32 newSfxId;

    newSfxId = NO_VALUE;
    switch (sfxId)
    {
        case Sfx_Unk1365:
            if (stalkerProps.field_10A < 3)
            {
                newSfxId                                 = sfxId;
                stalkerProps.field_10A = 3;
                stalkerProps.timer_108 = Rng_GenerateInt(Q12(0.0f), Q12(0.2f) - 1);
            }
            break;

        case Sfx_Unk1364:
            if (stalkerProps.field_10A < 2)
            {
                newSfxId                                 = sfxId;
                stalkerProps.field_10A = 2;
                stalkerProps.timer_108 = Rng_GenerateInt(Q12(0.0f), Q12(0.3f) - 1);
            }
            break;

        case Sfx_Unk1363:
            if (stalkerProps.field_10A < 2)
            {
                newSfxId                                 = sfxId;
                stalkerProps.field_10A = 2;
                stalkerProps.timer_108 = Rng_GenerateInt(Q12(0.0f), Q12(0.3f) - 1);
            }
            break;

        case Sfx_Unk1366:
            if (stalkerProps.field_10A < 2)
            {
                newSfxId                                 = sfxId;
                stalkerProps.field_10A = 2;
                stalkerProps.timer_108 = Rng_GenerateInt(Q12(0.0f), Q12(0.3f) - 1);
            }
            break;
    }

    // TODO: `stalkerProps.sfxId_102` doesn't match?
    if (newSfxId != NO_VALUE)
    {
        Sd_SfxStop(*((u16*)&stalker->properties_E4.player.field_100 + 1));
        *((u16*)&stalker->properties_E4.player.field_100 + 1) = newSfxId;
    }
}

#undef stalkerProps
