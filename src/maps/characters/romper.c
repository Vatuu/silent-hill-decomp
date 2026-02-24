#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/romper.h"

#define romperProps romper->properties_E4.romper

void Ai_Romper_Update(s_SubCharacter* romper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (romper->model_0.controlState_2 == ModelState_Uninitialized)
    {
        Ai_Romper_Init(romper);
    }
    else if (g_DeltaTime != Q12(0.0f))
    {
        sharedFunc_800E6420_2_s02(romper);
        Ai_Romper_ControlUpdate(romper);
        sharedFunc_800E8730_2_s02(romper);
        sharedFunc_800E8DFC_2_s02(romper);
    }

    sharedFunc_800E8A40_2_s02(romper, anmHdr, coords);
    sharedFunc_800E60FC_2_s02(romper);
}

void Ai_Romper_Init(s_SubCharacter* romper)
{
    #define HEALTH_BASE      Q12(450.0f)
    #define HEALTH_BONUS_MAX Q12(112.5f)

    s32 i;
    s32 temp_a0;
    s32 var_v0;

    romperProps.flags_E8           = RomperFlag_None;
    romper->model_0.anim_4.alpha_A = Q12(0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        romper->health_B0 = HEALTH_BASE - ((s32)Rng_Rand16() % HEALTH_BONUS_MAX);
    }
    else
    {
        if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
        {
            romper->health_B0 = HEALTH_BASE + ((s32)Rng_Rand16() % HEALTH_BONUS_MAX);
        }
        else
        {
            var_v0 = (s32)Rng_Rand16();
            temp_a0 = var_v0;
            if (temp_a0 < Q12(0.0f))
            {
                var_v0 = temp_a0 + (Q12(0.5f) - 1);
            }

            // TODO: Shifts are equivalent to `var_v0_2 % Q12(0.5f)`.
            romper->health_B0 = Q12_MULT_PRECISE(((temp_a0 - ((var_v0 >> 11) << 11)) + Q12(1.5f)), HEALTH_BASE);
        }
    }

    romper->moveSpeed_38    = Q12(0.0f);
    romper->field_E1_0      = 3;
    romper->headingAngle_3C = romper->rotation_24.vy;
    Chara_PropertiesClear(romper);

    romper->model_0.controlState_2 = RomperControl_2;
    Character_AnimSet(romper, ANIM_STATUS(RomperAnim_15, true), 147);

    romperProps.field_F0     = 6;
    romperProps.rotationY_F2 = romper->rotation_24.vy;
    romper->moveSpeed_38 = Q12(0.02175f);

    ModelAnim_AnimInfoSet(&romper->model_0.anim_4, ROPMER_ANIM_INFOS);
    Chara_DamageClear(romper);

    romperProps.targetPositionX_FC = romperProps.positionZ_110 = romper->position_18.vx;
    romperProps.targetPositionZ_100 = romperProps.positionX_108 = romper->position_18.vz;

    #undef HEALTH_BASE
    #undef HEALTH_BONUS_MAX
}

void sharedFunc_800E5FC8_2_s02(s_SubCharacter* chara, s16 arg1, s16 arg2, u8* arg3)
{
    q19_12 animTime;
    q19_12 arg1Plus2;
    q23_8  pitch;
    q23_8  vol;

    animTime  = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
    arg1Plus2 = arg1 + arg2;
    pitch     = Q8(0.0f);
    vol       = Q8(0.0f);

    if (animTime >= arg1Plus2 && animTime < (arg1Plus2 + 2))
    {
        if (*arg3 == 0)
        {
            switch (arg1)
            {
                case 2:
                    pitch = Q8(0.125f);
                    vol   = Q8(0.765625f);
                    break;

                case 8:
                case 15:
                case 93:
                    pitch = Q8(-0.125f);
                    vol   = Q8(0.5f);
                    break;

                case 109:
                    pitch = Q8(0.0f);
                    vol   = Q8(0.5f);
                    break;

                case 110:
                default:
                    pitch = -Q8(0.25f);
                    vol   = Q8(0.125f);
                    break;
            }

            func_8005DD44(Sfx_Unk1405, &chara->position_18, vol, pitch + Rng_GenerateUInt(-7, 8));
            *arg3 = 1;
        }
    }
    else
    {
        *arg3 = 0;
    }
}

void sharedFunc_800E60FC_2_s02(s_SubCharacter* romper)
{
    q19_12 var_s1;

    switch (romper->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(RomperAnim_2, true):
            sharedFunc_800E5FC8_2_s02(romper, 2, 2, &romperProps.field_114);
            break;

        case ANIM_STATUS(RomperAnim_3, true):
            sharedFunc_800E5FC8_2_s02(romper, 8, 5, &romperProps.field_114);
            break;

        case ANIM_STATUS(RomperAnim_4, true):
            sharedFunc_800E5FC8_2_s02(romper, 15, 2, &romperProps.field_114);
            break;

        case ANIM_STATUS(RomperAnim_11, true):
            sharedFunc_800E5FC8_2_s02(romper, 93, 2, &romperProps.field_115);
            sharedFunc_800E5FC8_2_s02(romper, 93, 3, &romperProps.field_114);
            break;

        case ANIM_STATUS(RomperAnim_13, true):
            sharedFunc_800E5FC8_2_s02(romper, 109, 7, &romperProps.field_115);
            sharedFunc_800E5FC8_2_s02(romper, 109, 20, &romperProps.field_114);
            break;

        case ANIM_STATUS(RomperAnim_14, true):
            sharedFunc_800E5FC8_2_s02(romper, 131, 8, &romperProps.field_115);
            sharedFunc_800E5FC8_2_s02(romper, 131, 15, &romperProps.field_114);
            break;

        default:
            romperProps.field_115 = 0;
            romperProps.field_114 = 0;
            break;
    }

    if (romperProps.field_116 != Q12(0.0f))
    {
        romperProps.field_116 -= g_DeltaTime;
        if (romperProps.field_116 < Q12(0.0f))
        {
            romperProps.field_116 = Q12(0.0f);
        }
    }
    else if (romperProps.flags_E8 & RomperFlag_7)
    {
        romperProps.field_116 = Q12(0.8f);
        func_8005DC1C(Sfx_Unk1400, &romper->position_18, Q8(0.5f), 0);
    }

    romperProps.flags_E8 &= ~RomperFlag_7;

    if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_5, true))
    {
        if (romperProps.timer_118 == Q12(0.0f))
        {
            func_8005DC1C(Sfx_Unk1401, &romper->position_18, Q8(0.5f), 0);
            romperProps.timer_118 = Q12(3.2f);
        }
        else
        {
            romperProps.timer_118 -= g_DeltaTime;
            if (romperProps.timer_118 < Q12(0.0f))
            {
                romperProps.timer_118 = Q12(0.0f);
            }
        }
    }
    else if (romperProps.timer_118 > Q12(0.0f))
    {
        romperProps.timer_118 = Q12(0.0f);
        Sd_SfxStop(Sfx_Unk1401);
    }

    if (romperProps.field_11A != 0)
    {
        func_8005DC1C(Sfx_Unk1402, &romper->position_18, Rng_GenerateUInt(120, 135), 0);
        romperProps.field_11A = 0;
    }

    if (romper->model_0.anim_4.status_0 != ANIM_STATUS(RomperAnim_5, true) &&
        romperProps.field_116 == 0 &&
        romper->health_B0 > Q12(0.0f))
    {
        if (romperProps.timer_11C != Q12(0.0f))
        {
            romperProps.timer_11C -= g_DeltaTime;
            if (romperProps.timer_11C < Q12(0.0f))
            {
                romperProps.timer_11C = Q12(0.0f);
            }
        }
        else
        {
            // TODO: Is this Q6?
            if (romper->health_B0 <= Q12(225.0f))
            {
                var_s1 = Q12_TO_Q6(Q12_DIV(romper->health_B0, Q12(450.0f))) + Q6(0.875f);
            }
            else
            {
                var_s1 = Q6(1.875f);
            }

            func_8005DC1C(Sfx_Unk1404, &romper->position_18, Rng_AddGeneratedUInt(var_s1, 0, 15) >> 1, 0);
            romperProps.timer_11C = Rng_GenerateInt(Q12(4.5f), Q12(6.5f) - 1);
        }
    }
}

void sharedFunc_800E6420_2_s02(s_SubCharacter* romper)
{
    s_Collision coll;
    s32         keyframeIdx;
    q19_12      unkHealth;
    s32         prevControlState;

    if (romper->health_B0 > Q12(0.0f))
    {
        Collision_Get(&coll, romper->position_18.vx, romper->position_18.vz);

        if (coll.field_8 == 12)
        {
            if (Rng_GenerateInt(Q12(4.0f), Q12(8.0f) - 1) < romper->position_18.vy)
            {
                romper->damage_B4.amount_C = Q12(3000.0f);
            }
        }
    }

    if (romper->damage_B4.amount_C == Q12(0.0f) || romper->health_B0 <= Q12(0.0f))
    {
        Chara_DamageClear(romper);
        return;
    }

    prevControlState = romper->model_0.controlState_2;

    romper->health_B0 = MAX(romper->health_B0 - romper->damage_B4.amount_C, Q12(0.0f));
    romperProps.flags_E8 |= RomperFlag_7;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        unkHealth = Q12(400.0f);
    }
    else
    {
        unkHealth = Q12(200.0f);
    }

    if (unkHealth < romper->health_B0)
    {
        romperProps.targetPositionX_FC  = g_SysWork.playerWork_4C.player_0.position_18.vx;
        romperProps.targetPositionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz;
        romperProps.field_10E     = 0;

        romperProps.rotationY_F2 = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                          g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz);

        switch (romper->model_0.anim_4.status_0)
        {
            case ANIM_STATUS(RomperAnim_13, false):
                romper->model_0.anim_4.time_4 = Q12(109.0f);

            case ANIM_STATUS(RomperAnim_13, true):
                keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 109;
                if (keyframeIdx > 0)
                {
                    if (keyframeIdx < 7)
                    {
                        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_18, true);
                    }
                    else if (keyframeIdx < 11)
                    {
                        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_8, false);
                    }
                    else if (keyframeIdx > 17)
                    {
                        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_7, false);
                    }
                    else
                    {
                        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_17, true);
                    }
                }
                else
                {
                    romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_7, false);
                }

                if (!ANIM_STATUS_IS_ACTIVE(romper->model_0.anim_4.status_0))
                {
                    romper->model_0.controlState_2 = RomperControl_6;
                }
                break;

            case ANIM_STATUS(RomperAnim_15, false):
                romper->model_0.anim_4.time_4 = Q12(147.0f);

            case ANIM_STATUS(RomperAnim_15, true):
                keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 147;
                if (keyframeIdx < 2)
                {
                    romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_7, false);
                }
                else if (keyframeIdx >= 10)
                {
                    romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_7, false);
                }
                else
                {
                    romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_8, false);
                }

                romper->model_0.controlState_2 = RomperControl_6;
                break;

            case ANIM_STATUS(RomperAnim_12, false):
            case ANIM_STATUS(RomperAnim_12, true):
            case ANIM_STATUS(RomperAnim_14, false):
            case ANIM_STATUS(RomperAnim_14, true):
                romper->model_0.controlState_2  = RomperControl_6;
                romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_7, false);
                break;
        }
    }
    else if (!(romperProps.flags_E8 & RomperFlag_2))
    {
        romper->model_0.controlState_2         = RomperControl_7;
        romper->model_0.anim_4.status_0        = ANIM_STATUS(RomperAnim_11, false);
        romperProps.flags_E8 |= RomperFlag_2;
    }

    romperProps.field_10E    = 0;
    romperProps.rotationY_F2 = Q12_ANGLE(360.0f);

    Chara_DamageClear(romper);

    if (prevControlState != romper->model_0.controlState_2)
    {
        if (romperProps.flags_E8 & RomperFlag_11)
        {
            romperProps.flags_E8 &= ~RomperFlag_11;
            g_SysWork.field_2284[3] &= 0xFFFC;
        }
    }
}

void Ai_Romper_ControlUpdate(s_SubCharacter* romper)
{
    u8 controlState;

    if (romper->model_0.controlState_2 != RomperControl_5)
    {
        romper->field_44.field_0 = 0;
    }

    // Handle control state.
    controlState = romper->model_0.controlState_2;
    g_Romper_ControlFuncs[controlState](romper);
    if (romper->model_0.controlState_2 != controlState)
    {
        romperProps.distance_120 = 0;
    }
}

void Ai_Romper_Control_1(s_SubCharacter* romper)
{
    s32    flags;
    q19_12 newMoveSpeed;
    s32    var;

    flags = g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1));
    if (flags == 0)
    {
        var = func_8006FD90(romper, 1, Q12(1.8f), Q12(4.0f));
    }
    else if (flags == (1 << 1))
    {
        var = func_8006FD90(romper, 1, Q12(3.0f), Q12(7.0f));
    }
    else
    {
        var = func_8006FD90(romper, 1, Q12(1.0f), Q12(1.0f));
    }

    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        var += func_80070360(romper, Q12(0.0f), Q12(0.4f));
    }

    newMoveSpeed         = romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime, Q12(15.0f));
    romper->moveSpeed_38 = MAX(newMoveSpeed, Q12(0.0f));

    if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_12, true) &&
        (Rng_GenerateUInt(0, 4095) == 0 || var)) // 1 in 4096 chance.
    {
        romper->model_0.controlState_2         = RomperControl_2;
        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_15, false);
    }
}

void Ai_Romper_Control_2(s_SubCharacter* romper)
{
    q3_12  moveDist;
    q3_12  angleDeltaToTarget;
    q19_12 headingAngle;
    s32    flags;
    bool   cond;

    angleDeltaToTarget = func_8005BF38(romperProps.rotationY_F2 - romper->rotation_24.vy);
    if (TIMESTEP_ANGLE(3, 3) < ABS(angleDeltaToTarget))
    {
        if (angleDeltaToTarget > Q12_ANGLE(0.0f))
        {
            romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
        }
        else
        {
            romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
        }
    }
    else
    {
        romper->rotation_24.vy = romperProps.rotationY_F2;
    }

    if (romper->rotation_24.vy == romperProps.rotationY_F2 || func_8007029C(romper, Q12(1.0f), romper->rotation_24.vy))
    {
        angleDeltaToTarget = func_8005BF38(romper->rotation_24.vy - ratan2(romperProps.targetPositionX_FC  - romper->position_18.vx,
                                                                           romperProps.targetPositionZ_100 - romper->position_18.vz));
        if (ABS(angleDeltaToTarget) > Q12_ANGLE(15.0f))
        {
            if (!Rng_GenerateInt(0, 15)) // 1 in 16 chance.
            {
                romperProps.rotationY_F2 = Chara_HeadingAngleGet(romper, Q12(1.0f), romperProps.targetPositionX_FC,
                                                                                  romperProps.targetPositionZ_100, Q12_ANGLE(360.0f), true);
            }
        }
    }

    if (Math_Vector2MagCalc(romper->position_18.vx - romperProps.targetPositionX_FC,
                            romper->position_18.vz - romperProps.targetPositionZ_100) < Q12(1.0f))
    {
        moveDist                        = Rng_GenerateInt(Q12(0.0f), Q12(5.0f) - 1);
        headingAngle                    = Rng_GenerateUInt(0, Q12_ANGLE(360.0f) - 1);
        romperProps.targetPositionX_FC  = romperProps.positionZ_110 + Q12_MULT(moveDist, Math_Sin(headingAngle));
        romperProps.targetPositionZ_100 = romperProps.positionX_108 + Q12_MULT(moveDist, Math_Cos(headingAngle));
    }

    romperProps.field_F0 += sharedFunc_800E939C_2_s02(romper);
    romper->moveSpeed_38 += romperProps.field_F0;

    flags = g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1));
    if (flags == 0)
    {
        cond = func_8006FD90(romper, 1, Q12(1.8f), Q12(4.0f));
    }
    else if (flags == (1 << 1))
    {
        cond = func_8006FD90(romper, 1, Q12(3.0f), Q12(7.0f));
    }
    else
    {
        cond = func_8006FD90(romper, 1, Q12(1.0f), Q12(1.0f));
    }

    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        cond += func_80070360(romper, Q12(0.0f), 0x266); // TODO: Last arg is angle? Unclear.
    }

    if (cond != 0 && romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_15, true))
    {
        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_19, false);

        if (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 148 &&
            FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 157)
        {
            romperProps.field_10C = 7;
        }
        else
        {
            romperProps.field_10C = 18;
        }

        romper->flags_3E |= RomperFlag_2;
    }
}

void Ai_Romper_Control_3(s_SubCharacter* romper)
{
    q3_12           angleDeltaToTarget;
    s32             temp_s0;
    bool            cond;
    q19_12          distToTarget;
    s32             temp_v1_2;
    s32             unkDist1;
    s32             var_s0;
    s32             i;
    q3_12           angleToTarget;
    q19_12          unkDist;
    s_SubCharacter* player;

    romperProps.field_F0 += sharedFunc_800E94B4_2_s02(romper);
    romper->moveSpeed_38                  += romperProps.field_F0;

    temp_v1_2 = g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 3;
    if (temp_v1_2 == 0)
    {
        var_s0 = func_8006FD90(romper, 0, Q12(2.5f), Q12(6.0f));
    }
    else if (temp_v1_2 == 2)
    {
        var_s0 = func_8006FD90(romper, 0, Q12(3.0f), Q12(8.0f));
    }
    else
    {
        var_s0 = func_8006FD90(romper, 0, Q12(0.8f), Q12(2.0f));
    }

    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        var_s0 |= func_80070360(romper, 0, Q12(0.2f));
    }

    if (var_s0)
    {
        romperProps.targetPositionX_FC = g_SysWork.playerWork_4C.player_0.position_18.vx +
                                                    (Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Sin(g_SysWork.playerWork_4C.player_0.headingAngle_3C)) >> 1);

        romperProps.targetPositionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz +
                                                     (Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Cos(g_SysWork.playerWork_4C.player_0.headingAngle_3C)) >> 1);
        romperProps.field_10E = 0;
    }
    else
    {
        romperProps.field_10E += g_DeltaTime;
    }

    if (ANIM_TIME_RANGE_CHECK(romper->model_0.anim_4.time_4, 112, 114) ||
        ANIM_TIME_RANGE_CHECK(romper->model_0.anim_4.time_4, 121, 126))
    {
        romperProps.flags_E8 &= ~RomperFlag_3;
        romperProps.flags_E8 &= ~RomperFlag_8;
        return;
    }

    if (!(romperProps.flags_E8 & RomperFlag_8))
    {
        romperProps.flags_E8 |= RomperFlag_8;
        return;
    }

    distToTarget = Math_Vector2MagCalc(romper->position_18.vx - romperProps.targetPositionX_FC,
                                       romper->position_18.vz - romperProps.targetPositionZ_100);

    cond = func_800700F8(romper, &g_SysWork.playerWork_4C.player_0);

    if (!(romperProps.flags_E8 & RomperFlag_3))
    {
        romperProps.flags_E8 |= RomperFlag_3;

        angleToTarget = ratan2(romperProps.targetPositionX_FC - romper->position_18.vx,
                               romperProps.targetPositionZ_100 - romper->position_18.vz);
        angleDeltaToTarget = ABS(func_8005BF38(angleToTarget - romper->rotation_24.vy));
        unkDist   = Q12_MULT_PRECISE(angleDeltaToTarget * 2, Q12(4.0f));

        if (!(romperProps.flags_E8 & RomperFlag_4) && unkDist < distToTarget)
        {
            if (angleDeltaToTarget < Q12_ANGLE(60.0f) && distToTarget < Q12(6.0f) && !cond)
            {
                romperProps.rotationY_F2 = angleToTarget;
            }
            else
            {
                unkDist1 = Q12_MULT_PRECISE(Rng_GenerateUInt(0xF00, 0x1100 - 1), CLAMP_MIN_THEN_LOW(distToTarget - Q12(0.2f), Q12(0.2f), Q12(2.5f)));

                romperProps.rotationY_F2 = Chara_HeadingAngleGet(romper, unkDist1, romperProps.targetPositionX_FC, romperProps.targetPositionZ_100, Q12_ANGLE(360.0f), true);
            }
        }
        else
        {
            unkDist1 = Q12_MULT_PRECISE(Rng_GenerateUInt(0xF00, 0x1100 - 1), Q12(2.5f));
            romperProps.rotationY_F2 = Chara_HeadingAngleGet(romper, unkDist1, romperProps.targetPositionX_FC, romperProps.targetPositionZ_100, Q12_ANGLE(360.0f), false);
        }

        if (romperProps.rotationY_F2 == angleToTarget)
        {
            temp_s0 = func_8007029C(romper, CLAMP_HIGH(distToTarget, 0x1AAA), romper->rotation_24.vy);
        }
        else
        {
            temp_s0 = func_8007029C(romper, 0x1AAA, romper->rotation_24.vy);
        }

        if (romperProps.field_10E > Q12(1.0f) && !Rng_GenerateUInt(0, 15))
        {
            romper->model_0.controlState_2            = RomperControl_1;
            romper->model_0.anim_4.status_0           = ANIM_STATUS(RomperAnim_12, false);
            romperProps.rotationY_F2 = romper->rotation_24.vy;
        }
        else if (temp_s0 != 0 || romperProps.rotationY_F2 == Q12_ANGLE(360.0f) ||
                 distToTarget < Q12_MULT_PRECISE(Q12(1.0f) - Math_Cos(angleDeltaToTarget >> 1), Q12(2.5f)))
        {
            if (romperProps.rotationY_F2 == Q12_ANGLE(360.0f))
            {
                romperProps.rotationY_F2 = romper->rotation_24.vy + Q12_ANGLE(180.0f);
            }

            // TODO: `ANIM_TIME_RANGE_CHECK` doesn't match?
            if (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 115 ||
                FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 120)
            {
                romper->model_0.controlState_2         = RomperControl_4;
                romper->model_0.anim_4.status_0        = ANIM_STATUS(RomperAnim_14, false);
                romperProps.field_10C = 0;
                romper->moveSpeed_38                   = Q12(0.0f);
                romperProps.distance_120 = 0;
            }
        }
    }

    for (i = 0; i < 3; i++)
    {
        angleToTarget = func_8005BF38(romperProps.rotationY_F2 - romper->rotation_24.vy);

        if (TIMESTEP_ANGLE(1, 3) < ABS(angleToTarget))
        {
            if (angleToTarget > Q12_ANGLE(0.0f))
            {
                romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
            else
            {
                romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
            }
        }
        else
        {
            romper->rotation_24.vy = romperProps.rotationY_F2;
            break;
        }
    }

    if (romperProps.flags_E8 & RomperFlag_4)
    {
        romperProps.distance_120 += g_DeltaTime;
        if (distToTarget > Q12(1.8f) || romperProps.distance_120 > Q12(1.8f))
        {
            romperProps.distance_120 = 0;
            romperProps.flags_E8 &= ~RomperFlag_4;
        }
    }

    // @hack Required for match.
    for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
    {
        if (&g_SysWork.npcs_1A0[i] == romper)
        {
            break;
        }
    }

    if (g_SysWork.playerWork_4C.player_0.health_B0 <= Q12(0.0f))
    {
        return;
    }

    player = &g_SysWork.playerWork_4C.player_0;

    if (player->flags_3E & RomperFlag_3)
    {
        return;
    }

    if (g_SysWork.sysState_8 != SysState_Gameplay || g_SysWork.field_2284[3] & 0x3)
    {
        return;
    }

    if (romper->fallSpeed_34 != Q12(0.0f) || distToTarget <= Q12(0.3f) || distToTarget >= Q12(3.2f) ||
        (romper->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy) >= Q12(1.0f) ||
        (romper->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy) <= Q12(-1.2f))
    {
        return;
    }

    if (romperProps.flags_E8 & RomperFlag_4)
    {
        return;
    }

    if (ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                 g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz) -
                          romper->rotation_24.vy)) < 0x155)
    {
        romper->model_0.controlState_2         = RomperControl_5;
        romper->model_0.anim_4.status_0        = ANIM_STATUS(RomperAnim_2, false);
        romper->field_44.field_0               = 1;
        g_SysWork.field_2284[3]               |= 3;
        romperProps.flags_E8 |= RomperFlag_4 | RomperFlag_11;
    }
}

void Ai_Romper_Control_4(s_SubCharacter* romper)
{
    q19_12 angle0;
    s32    temp_s0;
    s32    flags;
    s32    var_s0;
    s32    i;
    s32    angle1;

    flags = g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & 0x3;
    if (flags == 0)
    {
        var_s0 = func_8006FD90(romper, 0, Q12(2.5f), Q12(6.0f));
    }
    else if (flags == 2)
    {
        var_s0 = func_8006FD90(romper, 0, Q12(3.0f), Q12(8.0f));
    }
    else
    {
        var_s0 = func_8006FD90(romper, 0, Q12(0.8f), Q12(2.0f));
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        var_s0 |= func_80070360(romper, 0, Q12(0.2f));
    }

    if (var_s0 != false)
    {
        romperProps.targetPositionX_FC  = g_SysWork.playerWork_4C.player_0.position_18.vx;
        romperProps.targetPositionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz;
        romperProps.field_10E     = 0;
    }
    else
    {
        romperProps.field_10E += g_DeltaTime;
    }

    temp_s0 = func_8007029C(romper, Q12(2.5f), romper->rotation_24.vy);
    if (romperProps.distance_120 == Q12(0.0f) ||
        (temp_s0 != 0 && romperProps.distance_120 >= Q12(0.0f)))
    {
        romperProps.rotationY_F2 = Q12_ANGLE(0.0f);

        if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz) >= Q12_ANGLE(180.0f))
        {
            romperProps.rotationY_F2 = Chara_HeadingAngleGet(romper, Q12(2.5f), romperProps.targetPositionX_FC,
                                                                              romperProps.targetPositionZ_100, Q12(1.0f), true);
        }
        else
        {
            romperProps.rotationY_F2 = Chara_HeadingAngleGet(romper, Q12(2.5f), romperProps.targetPositionX_FC,
                                                                              romperProps.targetPositionZ_100, Q12(1.0f), false);
        }

        if (romperProps.rotationY_F2 == Q12_ANGLE(360.0f))
        {
            romperProps.rotationY_F2 = func_8006F99C(romper, Q12(2.5f), romper->rotation_24.vy);
        }

        if (temp_s0 != 0)
        {
            romperProps.distance_120 = -((Rng_Rand16() % Q12(1.0f)) + Q12(1.0f));
        }
        else
        {
            romperProps.distance_120 = (Rng_Rand16() % Q12(2.0f)) + Q12(1.0f);
        }
    }

    if (romperProps.distance_120 > Q12(0.0f))
    {
        romperProps.distance_120 -= g_DeltaTime;
        if (romperProps.distance_120 < Q12(0.0f))
        {
            romperProps.distance_120 = Q12(0.0f);
        }
    }
    else
    {
        romperProps.distance_120 += g_DeltaTime;
        if (romperProps.distance_120 > Q12(0.0f))
        {
            romperProps.distance_120 = Q12(0.0f);
        }
    }

    for (i = 0; i < 3; i++)
    {
        angle0 = func_8005BF38(romperProps.rotationY_F2 - romper->rotation_24.vy);
        if (TIMESTEP_ANGLE(1, 4) < ABS(angle0))
        {
            if (angle0 > 0)
            {
                romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(45.0f));
            }
            else
            {
                romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(45.0f));
            }
        }
        else
        {
            romper->rotation_24.vy = romperProps.rotationY_F2;
        }
    }

    if (!func_8007029C(romper, Q12(2.5f), romper->rotation_24.vy) && ANIM_TIME_RANGE_CHECK(romper->model_0.anim_4.time_4, 131, 132))
    {
        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_20, false);
        romper->moveSpeed_38            = Q12(0.0f);
        return;
    }

    angle0 = func_8005BF38(romperProps.rotationY_F2 - romper->rotation_24.vy);
    if (angle0 >= Q12_ANGLE(0.0f))
    {
        angle1 = Q12_ANGLE(180.0f) - angle0;
    }
    else
    {
        angle1 = angle0 + Q12_ANGLE(180.0f);
    }

    Chara_MoveSpeedUpdate4(romper, Q12(1.2f), Q12_MULT_PRECISE(angle1 * 2, Q12(2.4f)));
}

void Ai_Romper_Control_5(s_SubCharacter* romper)
{
    s_Collision coll;
    VECTOR3     pos; // Q19.12
    s16         temp_v0_4;
    q3_12       unkAngle1;
    s16         var_s3;
    s32         temp_a1;
    q19_12      unkAngle;
    s32         temp_v0;
    s32         temp_v0_3;
    s32         temp_v1_5;
    s16         var_a0_2;
    s32         i;
    s16         temp;

    if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_2, true))
    {
        if (romper->model_0.anim_4.time_4 > Q12(5.0f))
        {
            var_s3 = Q12(0.0f);
        }
        else
        {
            var_s3 = Q12(0.5f) - (Q12_DIV(romper->model_0.anim_4.time_4 - Q12(2.0f), Q12(3.0f)) >> 1);
        }
    }
    else
    {
        var_s3 = Q12(0.5f);
    }

    temp_v0                                   = Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Sin(g_SysWork.playerWork_4C.player_0.headingAngle_3C));
    romperProps.targetPositionX_FC = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12_MULT_PRECISE(temp_v0, var_s3);

    temp_a1                                    = Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Cos(g_SysWork.playerWork_4C.player_0.headingAngle_3C));
    romperProps.targetPositionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12_MULT_PRECISE(temp_a1, var_s3);

    temp_v0_3 = ratan2(romperProps.targetPositionX_FC - romper->position_18.vx, romperProps.targetPositionZ_100 - romper->position_18.vz);
    unkAngle   = temp_v0_3;

    if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_2, false))
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime, Q12(15.0f)), Q12(0.0f));

        for (i = 0; i < 4; i++)
        {
            temp_v0_4 = func_8005BF38(unkAngle - romper->rotation_24.vy);

            if ((((g_DeltaTime >> 3) + 1) >> 1) < ABS(temp_v0_4))
            {
                if (temp_v0_4 > 0)
                {
                    romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f)) >> 1;
                }
                else
                {
                    romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f)) >> 1;
                }
            }
            else
            {
                romper->rotation_24.vy = unkAngle;
            }
        }
    }
    else if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_2, true))
    {
        unkAngle1 = func_8005BF38(temp_v0_3 - romper->rotation_24.vy);
        if (TIMESTEP_ANGLE(1, 4) < ABS(unkAngle1))
        {
            if (unkAngle1 > Q12_ANGLE(0.0f))
            {
                romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(45.0f));
            }
            else
            {
                romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(45.0f));
            }
        }

        if (romper->model_0.anim_4.time_4 == Q12(2.0f))
        {
            temp_v1_5 = Math_Vector2MagCalc(romperProps.targetPositionX_FC - romper->position_18.vx,
                                            romperProps.targetPositionZ_100 - romper->position_18.vz);

            var_a0_2             = CLAMP_LOW(temp_v1_5, Q12(0.3f));
            romper->moveSpeed_38 = var_a0_2 << 1;
            Collision_Get(&coll, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz);
            temp                                   = coll.groundHeight_0 - Q12(0.8f);
            romper->fallSpeed_34                   = (temp << 1) - Q12(2.45f);
            romperProps.flags_E8 &= ~RomperFlag_9;
        }
        else if (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) == 5 ||
                 FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) == 6)
        {
            if (!(romperProps.flags_E8 & RomperFlag_9))
            {
                func_8005DC1C(Sfx_Unk1403, &romper->position_18, Q8(0.5f), 0);
                romperProps.flags_E8 |= RomperFlag_9;
            }

            pos.vx = romper->position_18.vx;
            pos.vy = romper->position_18.vy;
            pos.vz = romper->position_18.vz;

            if (func_8008A0E4(1, WEAPON_ATTACK(EquippedWeaponId_Shotgun, AttackInputType_Multitap), romper, &pos, &g_SysWork.playerWork_4C.player_0, romper->rotation_24.vy, Q12_ANGLE(90.0f)) != NO_VALUE)
            {
                romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_3, false);
                romper->model_0.controlState_2  = RomperControl_10;

                sharedFunc_800E9714_2_s02(romper);
                romperProps.flags_E8 |= RomperFlag_10;
            }
        }
    }
    else
    {
        if (romperProps.flags_E8 & RomperFlag_0)
        {
            Chara_MoveSpeedUpdate(romper, Q12_MULT_PRECISE(romper->moveSpeed_38, Q12(3.0f)) + Q12(3.0f));
        }
        else
        {
            romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime, Q12(15.0f)), Q12(0.0f));
        }
    }
}

void Ai_Romper_Control_6(s_SubCharacter* romper)
{
    q3_12 moveDist;

    romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime, Q12(15.0f)), Q12(0.0f));

    if (ANIM_STATUS_IDX_GET(romper->model_0.anim_4.status_0) == RomperAnim_7 ||
        ANIM_STATUS_IDX_GET(romper->model_0.anim_4.status_0) == RomperAnim_8)
    {
        moveDist               = (Q12_MULT_PRECISE(sharedData_800ECA4C_2_s02, g_DeltaTime) * Q12(0.6f)) / Q12(10.0f);
        romperProps.offsetX_F8 = Q12_MULT(moveDist, Math_Sin(romper->rotation_24.vy));
        romperProps.offsetZ_FA = Q12_MULT(moveDist, Math_Cos(romper->rotation_24.vy));
    }
}

void Ai_Romper_Control_7(s_SubCharacter* romper)
{
    q3_12 moveDist;

    if (romperProps.flags_E8 & RomperFlag_0)
    {
        Chara_MoveSpeedUpdate(romper, Q12_MULT_PRECISE(romper->moveSpeed_38, Q12(3.0f)) + Q12(3.0f));
    }
    else
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime, Q12(15.0f)), Q12(0.0f));
    }

    if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_11, false) ||
        ANIM_TIME_RANGE_CHECK(romper->model_0.anim_4.time_4, 93, 96))
    {
        moveDist               = (Q12_MULT_PRECISE(sharedData_800ECACC_2_s02, g_DeltaTime) * Q12(1.4f)) / Q12(7.0f);
        romperProps.offsetX_F8 = Q12_MULT(moveDist, Math_Sin(romper->rotation_24.vy));
        romperProps.offsetZ_FA = Q12_MULT(moveDist, Math_Cos(romper->rotation_24.vy));
    }

    if (ANIM_STATUS_IDX_GET(romper->model_0.anim_4.status_0) == RomperAnim_10)
    {
        romper->flags_3E |= 2;
    }

    if (romper->health_B0 == Q12(0.0f) && romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_10, true))
    {
        romper->model_0.controlState_2  = RomperControl_8;
        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_6, false);
        romper->flags_3E               &= ~CharaFlag_Unk2;

        Savegame_EnemyStateUpdate(romper);
    }
}

void Ai_Romper_Control_8(s_SubCharacter* romper)
{
    if (romper->health_B0 == Q12(0.0f))
    {
        if (g_SysWork.targetNpcIdx_2353 != Chara_NpcIdxGet(romper))
        {
            romper->health_B0  = NO_VALUE;
            romper->field_E1_0 = 0;
        }
    }

    if (romper->moveSpeed_38 == Q12(0.0f) &&
        !(romperProps.flags_E8 & (RomperFlag_0 | RomperFlag_1)))
    {
        func_800622B8(3, romper, ANIM_STATUS(RomperAnim_6, true), 9);
        romperProps.flags_E8 |= RomperFlag_1;
    }
}

void Ai_Romper_Control_9(s_SubCharacter* romper) {}

void Ai_Romper_Control_10(s_SubCharacter* romper)
{
    VECTOR          sp10;
    s_SubCharacter* player;

    if (romper->position_18.vx != romperProps.targetPositionX_FC ||
        romper->position_18.vz != romperProps.targetPositionZ_100)
    {
        romperProps.rotationY_F2 = ratan2(romperProps.targetPositionX_FC - romper->position_18.vx,
                                          romperProps.targetPositionZ_100 - romper->position_18.vz);
    }

    if (romper->model_0.anim_4.status_0 == 11)
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime, romperProps.field_124 * 4), Q12(0.0f));
    }
    else
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime, romperProps.field_124), Q12(0.0f));
    }

    romper->field_E1_0 = 0;
    if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_5, true))
    {
        romperProps.field_104 = romper->model_0.anim_4.time_4 - Q12(20.0f);
    }
    else
    {
        romperProps.field_104 = 0;
    }

    player = &g_SysWork.playerWork_4C.player_0;

    if (player->attackReceived_41 == NO_VALUE)
    {
        romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_9, false);
        romper->model_0.controlState_2  = RomperControl_11;
        romper->field_E1_0              = 0;
        romper->field_E1_0              = 3;
    }
    else if (romper->model_0.anim_4.time_4 < Q12(24.0f))
    {
        romperProps.flags_E8 |= RomperFlag_6;
    }
    else if (romperProps.flags_E8 & RomperFlag_6)
    {
        romperProps.flags_E8 &= ~RomperFlag_6;

        g_SysWork.playerWork_4C.player_0.damage_B4.amount_C += (FP_TO(D_800AD4C8[55].field_4, Q12_SHIFT) *
                                                               Rng_GenerateUInt(85, 116)) / 100;

        sp10.vx = romper->position_18.vx + FP_FROM(FP_TO(Math_Sin(romper->rotation_24.vy) >> 1, Q12_SHIFT), Q12_SHIFT);
        sp10.vy = romper->position_18.vy - Q12(0.1f);
        sp10.vz = romper->position_18.vz + FP_FROM(FP_TO(Math_Cos(romper->rotation_24.vy) >> 1, Q12_SHIFT), Q12_SHIFT);

        func_8005F6B0(&g_SysWork.playerWork_4C.player_0, &sp10, 4, 9);

        romperProps.field_11A = 1;
    }
}

void Ai_Romper_Control_11(s_SubCharacter* romper)
{
    if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_12, true) &&
        !Rng_GenerateInt(0, 7)) // 1 in 8 chance.
    {
        g_SysWork.field_2284[3]                  &= ~((1 << 0) | (1 << 1));
        romper->model_0.controlState_2                   = RomperControl_1;
        romperProps.flags_E8 &= ~RomperFlag_11;
    }
}

void sharedFunc_800E8730_2_s02(s_SubCharacter* romper)
{
    s_800C4590 sp10;
    VECTOR3    pos; // Q19.12
    s16        temp_s4;
    s32        temp_s0;
    s32        temp_s2;
    s32        temp_s3;
    s32        temp_v0;

    romper->fallSpeed_34 += g_GravitySpeed;

    if (ANIM_STATUS_IDX_GET(romper->model_0.anim_4.status_0) == RomperAnim_3 ||
        ANIM_STATUS_IDX_GET(romper->model_0.anim_4.status_0) == RomperAnim_5)
    {
        romper->headingAngle_3C = romperProps.rotationY_F2;
    }
    else
    {
        romper->headingAngle_3C = romper->rotation_24.vy;
    }

    if (g_DeltaTime != Q12(0.0f))
    {
        temp_s4 = romper->headingAngle_3C;
        temp_s0 = Q12_MULT_PRECISE(g_DeltaTime, romper->moveSpeed_38);
        temp_s2 = (temp_s0 < -0x7FFF || temp_s0 > 0x7FFF) * 4;
        temp_v0 = Math_Sin(temp_s4);
        temp_s3 = temp_s2 >> 1;
        temp_s0 = temp_s0 >> temp_s3;

        pos.vx = Q12_MULT_PRECISE(temp_s0, temp_v0 >> temp_s3) << temp_s2;
        pos.vz = Q12_MULT_PRECISE(temp_s0, Math_Cos(temp_s4) >> temp_s3) << temp_s2;
        pos.vy = Q12_MULT_PRECISE(g_DeltaTime, romper->fallSpeed_34);

        pos.vx += romperProps.offsetX_F8;
        pos.vz += romperProps.offsetZ_FA;

        func_80069B24(&sp10, &pos, romper);

        romper->position_18.vx += sp10.offset_0.vx;
        romper->position_18.vz += sp10.offset_0.vz;

        if (romperProps.flags_E8 & RomperFlag_10)
        {
            if (romper->model_0.controlState_2 != RomperControl_10 && romper->position_18.vy <= sp10.field_C)
            {
                romperProps.flags_E8 &= ~RomperFlag_10;
            }

            if (romperProps.flags_E8 & RomperFlag_10)
            {
                if (romper->model_0.controlState_2 == RomperControl_10)
                {
                    romper->position_18.vy += sp10.offset_0.vy;
                    if (g_SysWork.playerWork_4C.player_0.position_18.vy < romper->position_18.vy)
                    {
                        romper->position_18.vy = g_SysWork.playerWork_4C.player_0.position_18.vy;
                        romper->fallSpeed_34   = Q12(0.0f);
                    }
                }
                else
                {
                    romper->position_18.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.15f));
                    romper->fallSpeed_34    = Q12(0.0f);
                    if (sp10.field_C >= romper->position_18.vy)
                    {
                        romper->position_18.vy = sp10.field_C;
                    }
                }
            }
            else
            {
                romper->position_18.vy += sp10.offset_0.vy;
                if (sp10.field_C < romper->position_18.vy)
                {
                    romper->position_18.vy = sp10.field_C;
                    romper->fallSpeed_34   = Q12(0.0f);
                }
            }
        }
        else
        {
            romper->position_18.vy += sp10.offset_0.vy;
            if (sp10.field_C < romper->position_18.vy)
            {
                romper->position_18.vy = sp10.field_C;
                romper->fallSpeed_34   = Q12(0.0f);
            }
        }

        romperProps.offsetZ_FA = Q12(0.0f);
        romperProps.offsetX_F8 = Q12(0.0f);
    }

    romper->rotation_24.vy = func_8005BF38(romper->rotation_24.vy);

    if (romper->fallSpeed_34 != Q12(0.0f))
    {
        romperProps.flags_E8 |= RomperFlag_0;
    }
    else
    {
        romperProps.flags_E8 &= ~RomperFlag_0;
    }
}

void sharedFunc_800E8A40_2_s02(s_SubCharacter* romper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    typedef struct
    {
        MATRIX  field_0;
        SVECTOR field_20;
    } s_sharedFunc_800E8A40_2_s02;

    q19_12                       angleDeltaToTarget;
    q19_12                       unkAngle;
    s32                          temp_v0_4;
    s_AnimInfo*                  animInfo;
    s_sharedFunc_800E8A40_2_s02* ptr;

    ptr = PSX_SCRATCH;

    switch (romper->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(RomperAnim_13, true):
        case ANIM_STATUS(RomperAnim_17, true):
        case ANIM_STATUS(RomperAnim_18, true):
            ROPMER_ANIM_INFOS[romper->model_0.anim_4.status_0].duration_8.constant = sharedData_800EC950_2_s02;
            break;

        case ANIM_STATUS(RomperAnim_14, false):
            sharedData_800ECB22_2_s02 = romperProps.field_10C + 131;
            break;

        case ANIM_STATUS(RomperAnim_14, true):
            ROPMER_ANIM_INFOS[29].startKeyframeIdx_C                               = romperProps.field_10C + 131;
            romperProps.field_10C                                 = 0;
            ROPMER_ANIM_INFOS[romper->model_0.anim_4.status_0].duration_8.constant = Q12_MULT_PRECISE(MAX(romper->moveSpeed_38, Q12(1.5f)), Q12(8.32f));
            break;

        case ANIM_STATUS(RomperAnim_19, false):
            sharedData_800ECBC2_2_s02 = romperProps.field_10C + 109;
            break;

        case ANIM_STATUS(RomperAnim_19, true):
            sharedData_800ECBD0_2_s02 = romperProps.field_10C + 109;
            break;
    }

    Math_MatrixTransform(&romper->position_18, (SVECTOR*)&romper->rotation_24, coords);

    animInfo = &ROPMER_ANIM_INFOS[romper->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&romper->model_0, anmHdr, coords, animInfo);

    switch (romper->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(RomperAnim_7, false):
            romper->model_0.controlState_2 = RomperControl_6;
            if (romper->model_0.anim_4.time_4 == Q12(127.0f))
            {
                romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_7, true);
                romper->model_0.anim_4.time_4   = Q12(39.0f);
            }
            break;

        case ANIM_STATUS(RomperAnim_8, false):
            romper->model_0.controlState_2 = RomperControl_6;
            if (romper->model_0.anim_4.time_4 == Q12(116.0f))
            {
                romper->model_0.anim_4.status_0 = ANIM_STATUS(RomperAnim_8, true);
                romper->model_0.anim_4.time_4   = Q12(50.0f);
            }
            break;

        case ANIM_STATUS(RomperAnim_13, false):
            if (romper->model_0.controlState_2 == RomperControl_5)
            {
                romperProps.flags_E8 &= ~RomperFlag_11;
                g_SysWork.field_2284[3]               &= 0xFFFC;
            }

            romper->model_0.controlState_2        = RomperControl_3;
            romperProps.field_F4 = Q12(22.0f) - 1;

            if (romper->model_0.anim_4.time_4 == Q12(49.0f))
            {
                romper->model_0.anim_4.status_0       = ANIM_STATUS(RomperAnim_13, true);
                romperProps.field_F4 = Q12(1.0f) - 1;
                romper->model_0.anim_4.time_4         = Q12(110.0f);
                romperProps.field_F0 = 1143;
                romper->moveSpeed_38                  = 0;
            }
            else if (romper->model_0.anim_4.time_4 == Q12(60.0f))
            {
                romper->model_0.anim_4.status_0       = ANIM_STATUS(RomperAnim_13, true);
                romperProps.field_F4 = Q12(11.0f) - 1;
                romperProps.field_F0 = 121;
                romper->model_0.anim_4.time_4         = Q12(120.0f);
                romper->moveSpeed_38                  = Q12(1.2f);
            }
            break;

        case ANIM_STATUS(RomperAnim_19, true):
        case ANIM_STATUS(RomperAnim_20, true):
            romper->model_0.controlState_2        = RomperControl_3;
            romper->model_0.anim_4.status_0       = ANIM_STATUS(RomperAnim_13, true);
            romperProps.field_F4 = romper->model_0.anim_4.time_4 - (Q12(109.0f) + 1);
            break;
    }

    angleDeltaToTarget = func_8005BF38(romperProps.angle_EC - romper->rotation_24.vy);
    if (angleDeltaToTarget == Q12_ANGLE(0.0f))
    {
        unkAngle = Q12_ANGLE(0.0f);
    }
    else
    {
        unkAngle = Q12_ANGLE(17.25f);
    }

    if (angleDeltaToTarget < Q12_ANGLE(0.0f))
    {
        unkAngle = -unkAngle;
    }

    temp_v0_4 = Q12_MULT_FLOAT_PRECISE(g_DeltaTime, 0.0625f);
    if (unkAngle < romperProps.field_EE)
    {
        romperProps.field_EE = MAX(unkAngle, romperProps.field_EE - temp_v0_4);
    }
    else
    {
        romperProps.field_EE = CLAMP_HIGH(unkAngle, romperProps.field_EE + temp_v0_4);
    }

    *(s32*)&ptr->field_20 = romperProps.field_EE << 16;
    ptr->field_20.vz      = 0;

    Math_RotMatrixZxyNegGte(&ptr->field_20, &ptr->field_0);
    MulMatrix2(&ptr->field_0, &coords[2].coord);

    romperProps.angle_EC = romper->rotation_24.vy;
}

extern s_Keyframe sharedData_800ECC44_2_s02;
extern s_Keyframe sharedData_800ECC58_2_s02[];
extern s_Keyframe sharedData_800ECCBC_2_s02;
extern s_Keyframe sharedData_800ECCD0_2_s02[];
extern s_Keyframe sharedData_800ECD34_2_s02;
extern s_Keyframe sharedData_800ECD48_2_s02[];
extern s_Keyframe sharedData_800ECE24_2_s02[];
extern s_Keyframe sharedData_800ECF00_2_s02[];
extern s_Keyframe sharedData_800ECF64_2_s02[];
extern s_Keyframe sharedData_800ED018_2_s02[];
extern s_Keyframe sharedData_800ED1D0_2_s02[];
extern s_Keyframe sharedData_800ED2C0_2_s02;

#define CopyData(arg0, data)                  \
{                                             \
    s32 __temp;                               \
    s32 __temp2;                              \
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
    __temp2                = data.field_A;    \
    arg0->field_D4.field_2 = __temp2;         \
}

void sharedFunc_800E8DFC_2_s02(s_SubCharacter* romper)
{
    s32 keyframeIdxs[2];
    s32 keyframeIdx;
    s32 i;

    switch (romper->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(RomperAnim_2, true):
            for (i = 0, keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 2; i < 2; i++, keyframeIdx++)
            {
                keyframeIdxs[i] = keyframeIdx - !(keyframeIdx < 5);
            }

            func_80070400(romper, &sharedData_800ECC58_2_s02[keyframeIdxs[0]], &sharedData_800ECC58_2_s02[keyframeIdxs[1]]);
            break;

        case ANIM_STATUS(RomperAnim_3, false):
        case ANIM_STATUS(RomperAnim_3, true):
        case ANIM_STATUS(RomperAnim_5, false):
        case ANIM_STATUS(RomperAnim_5, true):
            CopyData(romper, sharedData_800ECCBC_2_s02);
            break;

        case ANIM_STATUS(RomperAnim_4, true):
            for (i = 0, keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 15;
                 i < 2;
                 i++, keyframeIdx++)
            {
                keyframeIdxs[i] = keyframeIdx;
            }

            func_80070400(romper, &sharedData_800ECCD0_2_s02[keyframeIdxs[0]], &sharedData_800ECCD0_2_s02[keyframeIdxs[1]]);
            break;

        case ANIM_STATUS(RomperAnim_7, true):
            for (i = 0, keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 39;
                 i < 2;
                 i++, keyframeIdx++)
            {
                keyframeIdxs[i] = keyframeIdx;
            }

            func_80070400(romper, &sharedData_800ECD48_2_s02[keyframeIdxs[0]], &sharedData_800ECD48_2_s02[keyframeIdxs[1]]);
            break;

        case ANIM_STATUS(RomperAnim_8, true):
            for (i = 0, keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 50;
                 i < 2;
                 i++, keyframeIdx++)
            {
                keyframeIdxs[i] = keyframeIdx;
            }

            func_80070400(romper, &sharedData_800ECE24_2_s02[keyframeIdxs[0]], &sharedData_800ECE24_2_s02[keyframeIdxs[1]]);
            break;

        case ANIM_STATUS(RomperAnim_6, false):
        case ANIM_STATUS(RomperAnim_6, true):
        case ANIM_STATUS(RomperAnim_10, false):
        case ANIM_STATUS(RomperAnim_10, true):
        case ANIM_STATUS(RomperAnim_16, false):
        case ANIM_STATUS(RomperAnim_16, true):
            CopyData(romper, sharedData_800ECF00_2_s02[4]);
            break;

        case ANIM_STATUS(RomperAnim_11, false):
            CopyData(romper, sharedData_800ECF00_2_s02[0]);
            break;

        case ANIM_STATUS(RomperAnim_11, true):
            for (i = 0, keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 93;
                i < 2;
                i++, keyframeIdx++)
            {
                keyframeIdxs[i] = keyframeIdx >= 4 ? 4 : keyframeIdx;
            }

            func_80070400(romper, &sharedData_800ECF00_2_s02[keyframeIdxs[0]], &sharedData_800ECF00_2_s02[keyframeIdxs[1]]);
            break;

        case ANIM_STATUS(RomperAnim_12, true):
            for (i = 0, keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 100;
                 i < 2;
                 i++, keyframeIdx   = (keyframeIdx + 1) % 9)
            {
                keyframeIdxs[i] = keyframeIdx;
            }

            func_80070400(romper, &sharedData_800ECF64_2_s02[keyframeIdxs[0]], &sharedData_800ECF64_2_s02[keyframeIdxs[1]]);
            break;

        case ANIM_STATUS(RomperAnim_13, true):
            for (i = 0, keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 109;
                 i < 2;
                 i++, keyframeIdx = (keyframeIdx + 1) % 22)
            {
                keyframeIdxs[i] = keyframeIdx;
            }

            func_80070400(romper, &sharedData_800ED018_2_s02[keyframeIdxs[0]], &sharedData_800ED018_2_s02[keyframeIdxs[1]]);
            break;

        case ANIM_STATUS(RomperAnim_14, true):
            CopyData(romper, sharedData_800ED2C0_2_s02);
            break;

        case ANIM_STATUS(RomperAnim_15, true):
            for (i = 0, keyframeIdx = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 147;
                 i < 2;
                 i++, keyframeIdx = (keyframeIdx + 1) % 16)
            {
                keyframeIdxs[i] = keyframeIdx - (keyframeIdx > 0) - !(keyframeIdx < 4) - !(keyframeIdx < 8) - !(keyframeIdx < 12);
            }

            func_80070400(romper, &sharedData_800ED1D0_2_s02[keyframeIdxs[0]], &sharedData_800ED1D0_2_s02[keyframeIdxs[1]]);
            break;

        case ANIM_STATUS(RomperAnim_9, true):
            CopyData(romper, sharedData_800ECD34_2_s02);
            romper->field_D4.radius_0 = (romper->model_0.anim_4.time_4 - Q12(61.0f)) / 100;
            break;

        default:
            CopyData(romper, sharedData_800ECC44_2_s02);
            break;
    }

    func_8005C814(&romper->field_D8, romper);

    if (ANIM_STATUS_IDX_GET(romper->model_0.anim_4.status_0) != RomperAnim_2)
    {
        romper->field_44.field_0 = 0;
    }
}

s32 sharedFunc_800E939C_2_s02(s_SubCharacter* romper)
{
    s32    i;
    q19_12 relAnimTime;
    u32    var_a3;

    if (romper->model_0.anim_4.time_4 <  Q12(147.0f) ||
        romper->model_0.anim_4.time_4 >= Q12(163.0f))
    {
        return 0;
    }

    relAnimTime = romper->model_0.anim_4.time_4 - Q12(147.0f);
    if (relAnimTime < romperProps.field_F4)
    {
        romperProps.field_F0 = 6;
        romperProps.field_F4 = Q12(0.0f);
        romper->moveSpeed_38 = 89; // TODO: Clean float. Maybe it was a fraction?
    }

    var_a3 = 0;
    for (i = 0; i < 7; i++)
    {
        if (sharedData_800ED2D4_2_s02[i].field_0 > romperProps.field_F4 ||
            romperProps.field_F4 >= sharedData_800ED2D4_2_s02[i + 1].field_0)
        {
            continue;
        }

        if (relAnimTime < sharedData_800ED2D4_2_s02[i + 1].field_0)
        {
            var_a3 += Q12_MULT_PRECISE(relAnimTime - romperProps.field_F4, sharedData_800ED2D4_2_s02[i].field_4);
            break;
        }

        var_a3 += Q12_MULT_PRECISE(sharedData_800ED2D4_2_s02[i + 1].field_0 - romperProps.field_F4, sharedData_800ED2D4_2_s02[i].field_4);
        romperProps.field_F4 = sharedData_800ED2D4_2_s02[i + 1].field_0;
    }

    romperProps.field_F4 = relAnimTime;
    return (var_a3 >> 31) + var_a3;
}

s32 sharedFunc_800E94B4_2_s02(s_SubCharacter* romper)
{
    s32 i;
    s32 relAnimTime;
    u32 var_t4;

    // TODO: Demagic hex values in this func. Some of the resulting floats are awkward.

    if (romper->model_0.anim_4.time_4 <  Q12(109.0f) ||
        romper->model_0.anim_4.time_4 >= Q12(131.0f))
    {
        return 0;
    }

    relAnimTime = romper->model_0.anim_4.time_4 - Q12(109.0f);
    if (relAnimTime < romperProps.field_F4)
    {
        romperProps.field_F0 = -404;
        romperProps.field_F4 = Q12(0.0f);
        romper->moveSpeed_38                  = Q12(-0.256f);
    }

    var_t4 = 0;
    for (i = 0; i < 22; i++)
    {
        if (romperProps.field_F4 < FP_TO(i, Q12_SHIFT) ||
            romperProps.field_F4 >= FP_TO(i + 1, Q12_SHIFT))
        {
            continue;
        }

        if (relAnimTime >= FP_TO(i + 1, Q12_SHIFT))
        {
            switch (i + 1)
            {
                case 1:
                    if (romper->fallSpeed_34 == 0)
                    {
                        romper->fallSpeed_34 = -0x2A77;
                    }
                    break;

                case 11:
                    if (romper->fallSpeed_34 == 0)
                    {
                        romper->fallSpeed_34 = -0x30FF;
                    }
                    break;

                case 7:
                    var_t4                                = 0;
                    romperProps.field_F0 = 0x112;
                    romper->moveSpeed_38                  = Q12(1.268f);
                    break;

                case 18:
                    var_t4                                = 0;
                    romperProps.field_F0 = 0x3F;
                    romper->moveSpeed_38                  = 0xBF0;
                    break;

                default:
                    var_t4               += Q12_MULT_PRECISE(FP_TO(i + 1, Q12_SHIFT) - romperProps.field_F4, sharedData_800ED314_2_s02[i].field_0);
                    romper->moveSpeed_38 += Q12_MULT_PRECISE(FP_TO(i + 1, Q12_SHIFT) - romperProps.field_F4, sharedData_800ED314_2_s02[i].field_4);
                    break;
            }
            romperProps.field_F4 = FP_TO(i + 1, Q12_SHIFT);
        }
        else
        {
            var_t4               += Q12_MULT_PRECISE(relAnimTime - romperProps.field_F4, sharedData_800ED314_2_s02[i].field_0);
            romper->moveSpeed_38 += Q12_MULT_PRECISE(relAnimTime - romperProps.field_F4, sharedData_800ED314_2_s02[i].field_4);
            break;
        }
    }

    romperProps.field_F4 = relAnimTime;

    if ((relAnimTime >= Q12(1.0f) && relAnimTime < Q12(7.0f)) ||
        (relAnimTime >= Q12(11.0f) && relAnimTime < Q12(18.0f)))
    {
        sharedData_800EC950_2_s02 = Q12(12.0f);
    }
    else
    {
        sharedData_800EC950_2_s02 = Q12(24.0f);
    }

    return (var_t4 >> 31) + var_t4;
}

void sharedFunc_800E9714_2_s02(s_SubCharacter* romper)
{
    q19_12 newPosX;
    q19_12 newPosZ;
    q3_12  headingAngle;
    q19_12 moveSpeed;
    q19_12 temp_v0;
    q19_12 temp_v0_4;
    q19_12 moveDist;
    q19_12 moveSpeedStep;

    // TODO: Document this.
    moveSpeed     = romper->moveSpeed_38;
    moveSpeedStep = Q12(8.0f);
    temp_v0       = Q12_DIV(moveSpeed, moveSpeedStep);
    temp_v0_4     = moveSpeed - Q12_MULT_PRECISE(temp_v0, Q12(4.0f));
    headingAngle  = romper->rotation_24.vy;
    moveDist      = Q12_MULT_PRECISE(temp_v0_4, temp_v0);

    if (moveDist >= Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                        g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz))
    {
        newPosX = romper->position_18.vx + Q12_MULT(moveDist, Math_Sin(headingAngle));
        newPosZ = romper->position_18.vz + Q12_MULT(moveDist, Math_Cos(headingAngle));
    }
    else
    {
        newPosX = g_SysWork.playerWork_4C.player_0.position_18.vx;
        newPosZ = g_SysWork.playerWork_4C.player_0.position_18.vz;
    }

    sharedFunc_800D2E9C_0_s00(&newPosX, &newPosZ, &headingAngle);

    temp_v0 = (FP_TO(Math_Vector2MagCalc(newPosX - romper->position_18.vx, newPosZ - romper->position_18.vz), Q12_SHIFT) << 1) / moveSpeed;
    moveSpeedStep  = FP_TO(moveSpeed, Q12_SHIFT) / temp_v0;

    if (moveSpeedStep < Q12(0.0f))
    {
        moveSpeedStep = Q12(4.0f);
    }

    if (moveSpeedStep > Q12(32.0f))
    {
        moveSpeedStep = Q12(32.0f);
    }

    romperProps.rotationY_F2  = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz);
    romperProps.field_124     = moveSpeedStep;
    romperProps.targetPositionX_FC  = newPosX;
    romperProps.targetPositionZ_100 = newPosZ;
}

#undef romperProps
