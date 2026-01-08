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
    else if (g_DeltaTime0 != Q12(0.0f))
    {
        sharedFunc_800E6420_2_s02(romper);
        Ai_Romper_Control(romper);
        sharedFunc_800E8730_2_s02(romper);
        sharedFunc_800E8DFC_2_s02(romper);
    }

    sharedFunc_800E8A40_2_s02(romper, anmHdr, coords);
    sharedFunc_800E60FC_2_s02(romper);
}

void Ai_Romper_Init(s_SubCharacter* romper)
{
    #define ROMPER_HEALTH_BASE      Q12(450.0f)
    #define ROMPER_HEALTH_BONUS_MAX Q12(112.5f)

    s32 i;
    s32 temp_a0;
    s32 var_v0;

    romperProps.flags_E8           = RomperFlag_None;
    romper->model_0.anim_4.alpha_A = Q12(0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        romper->health_B0 = ROMPER_HEALTH_BASE - ((s32)Rng_Rand16() % ROMPER_HEALTH_BONUS_MAX);
    }
    else
    {
        if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
        {
            romper->health_B0 = ROMPER_HEALTH_BASE + ((s32)Rng_Rand16() % ROMPER_HEALTH_BONUS_MAX);
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
            romper->health_B0 = Q12_MULT_PRECISE(((temp_a0 - ((var_v0 >> 11) << 11)) + Q12(1.5f)), ROMPER_HEALTH_BASE);
        }
    }

    romper->moveSpeed_38    = Q12(0.0f);
    romper->field_E1_0      = 3;
    romper->headingAngle_3C = romper->rotation_24.vy;
    Chara_PropertiesClear(romper);

    romper->model_0.controlState_2 = 2;
    Character_AnimSet(romper, ANIM_STATUS(RomperAnim_15, true), 147);

    romperProps.field_F0     = 6;
    romperProps.rotationY_F2 = romper->rotation_24.vy;
    romper->moveSpeed_38 = Q12(0.02175f);

    ModelAnim_AnimInfoSet(&romper->model_0.anim_4, ROPMER_ANIM_INFOS);
    Chara_DamageClear(romper);

    romperProps.positionX_FC =
        romperProps.positionZ_110 = romper->position_18.vx;
    romperProps.positionZ_100 =
        romperProps.positionX_108 = romper->position_18.vz;

#undef ROMPER_HEALTH_BASE
    #undef ROMPER_HEALTH_BONUS_MAX
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
    s32 var_s1;

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
        romperProps.field_116 -= g_DeltaTime0;
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
            romperProps.timer_118 -= g_DeltaTime0;
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
        // TODO: Wrong RNG macro.
        func_8005DC1C(Sfx_Unk1402, &romper->position_18, Rng_TestProbabilityBits(4) + 120, 0);
        romperProps.field_11A = 0;
    }

    if (romper->model_0.anim_4.status_0 != ANIM_STATUS(RomperAnim_5, true) &&
        romperProps.field_116 == 0 &&
        romper->health_B0 > Q12(0.0f))
    {
        if (romperProps.timer_11C != Q12(0.0f))
        {
            romperProps.timer_11C -= g_DeltaTime0;
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

            // TODO: Wrong RNG macro.
            func_8005DC1C(Sfx_Unk1404, &romper->position_18, (var_s1 + Rng_TestProbabilityBits(4)) >> 1, 0);
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
        romper->damage_B4.amount_C      = Q12(0.0f);
        romper->damage_B4.position_0.vz = Q12(0.0f);
        romper->damage_B4.position_0.vy = Q12(0.0f);
        romper->damage_B4.position_0.vx = Q12(0.0f);
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
        romperProps.positionX_FC = g_SysWork.playerWork_4C.player_0.position_18.vx;

        romperProps.positionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz;
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
                    romper->model_0.controlState_2 = 6;
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
    romperProps.rotationY_F2 = FP_ANGLE(360.0f);
    romper->damage_B4.amount_C                = Q12(0.0f);
    romper->damage_B4.position_0.vz           = Q12(0.0f);
    romper->damage_B4.position_0.vy           = Q12(0.0f);
    romper->damage_B4.position_0.vx           = Q12(0.0f);

    if (prevControlState != romper->model_0.controlState_2)
    {
        if (romperProps.flags_E8 & RomperFlag_11)
        {
            romperProps.flags_E8 &= ~RomperFlag_11;
            g_SysWork.field_2284[3] &= 0xFFFC;
        }
    }
}

void Ai_Romper_Control(s_SubCharacter* romper)
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
        romperProps.field_120 = 0;
    }
}

void Ai_Romper_Control_1(s_SubCharacter* romper)
{
    s32    flags;
    q19_12 newMoveSpeed;
    s32    var;

    flags = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1));
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

    newMoveSpeed         = romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, Q12(15.0f));
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
    if (TIMESTEP_ANGLE_2 < ABS(angleDeltaToTarget))
    {
        if (angleDeltaToTarget > FP_ANGLE(0.0f))
        {
            romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f));
        }
        else
        {
            romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, FP_ANGLE(30.0f));
        }
    }
    else
    {
        romper->rotation_24.vy = romperProps.rotationY_F2;
    }

    if (romper->rotation_24.vy == romperProps.rotationY_F2 || func_8007029C(romper, Q12(1.0f), romper->rotation_24.vy))
    {
        angleDeltaToTarget = func_8005BF38(romper->rotation_24.vy - ratan2(romperProps.positionX_FC  - romper->position_18.vx,
                                                                           romperProps.positionZ_100 - romper->position_18.vz));
        if (ABS(angleDeltaToTarget) > FP_ANGLE(15.0f))
        {
            if (!Rng_TestProbabilityBits(4))
            {
                romperProps.rotationY_F2 = Chara_HeadingAngleGet(romper, Q12(1.0f), romperProps.positionX_FC,
                                                                                  romperProps.positionZ_100, FP_ANGLE(360.0f), true);
            }
        }
    }

    if (Math_Vector2MagCalc(romper->position_18.vx - romperProps.positionX_FC,
                            romper->position_18.vz - romperProps.positionZ_100) < Q12(1.0f))
    {
        moveDist                                   = Rng_GenerateInt(Q12(0.0f), Q12(5.0f) - 1);
        headingAngle                               = Rng_TestProbabilityBits(12); // TODO: Wrong macro.
        romperProps.positionX_FC  = romperProps.positionZ_110 + Q12_MULT(moveDist, Math_Sin(headingAngle));
        romperProps.positionZ_100 = romperProps.positionX_108 + Q12_MULT(moveDist, Math_Cos(headingAngle));
    }

    romperProps.field_F0 += sharedFunc_800E939C_2_s02(romper);
    romper->moveSpeed_38 += romperProps.field_F0;

    flags = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1));
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

        romper->flags_3E |= 4;
    }
}

void Ai_Romper_Control_3(s_SubCharacter* romper)
{
    s16             var_s3;
    s32             temp_s0;
    s32             temp_s4;
    s32             temp_s5;
    s32             temp_v1_2;
    s32             var_a1;
    s32             var_s0;
    s32             i;
    s16             var_s2;
    s32             temp;
    s_SubCharacter* player;

    romperProps.field_F0 += sharedFunc_800E94B4_2_s02(romper);
    romper->moveSpeed_38                  += romperProps.field_F0;

    temp_v1_2 = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3;
    if (temp_v1_2 == 0)
    {
        var_s0 = func_8006FD90(romper, 0, 0x2800, 0x6000);
    }
    else if (temp_v1_2 == 2)
    {
        var_s0 = func_8006FD90(romper, 0, 0x3000, 0x8000);
    }
    else
    {
        var_s0 = func_8006FD90(romper, 0, 0xCCC, 0x2000);
    }

    if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        var_s0 |= func_80070360(romper, 0, 0x333);
    }

    if (var_s0)
    {
        romperProps.positionX_FC = g_SysWork.playerWork_4C.player_0.position_18.vx +
                                                    (Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Sin(g_SysWork.playerWork_4C.player_0.headingAngle_3C)) >> 1);

        romperProps.positionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz +
                                                     (Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Cos(g_SysWork.playerWork_4C.player_0.headingAngle_3C)) >> 1);
        romperProps.field_10E = 0;
    }
    else
    {
        romperProps.field_10E += g_DeltaTime0;
    }

    if ((FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 0x6F && FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 0x73) ||
        (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 0x78 && FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 0x7F))
    {
        romperProps.flags_E8 &= ~8;
        romperProps.flags_E8 &= ~0x100;
        return;
    }

    if (!(romperProps.flags_E8 & 0x100))
    {
        romperProps.flags_E8 |= 0x100;
        return;
    }

    temp_s5 = Math_Vector2MagCalc(romper->position_18.vx - romperProps.positionX_FC,
                                  romper->position_18.vz - romperProps.positionZ_100);

    temp_s4 = func_800700F8(romper, &g_SysWork.playerWork_4C.player_0);

    if (!(romperProps.flags_E8 & 8))
    {
        romperProps.flags_E8 |= 8;

        var_s2 = ratan2(romperProps.positionX_FC - romper->position_18.vx,
                        romperProps.positionZ_100 - romper->position_18.vz);

        var_s3 = ABS(func_8005BF38(var_s2 - romper->rotation_24.vy));
        temp   = Q12_MULT_PRECISE(var_s3 * 2, 0x4000);

        if (!(romperProps.flags_E8 & 0x10) && temp < temp_s5)
        {
            if (var_s3 < 0x2AA && temp_s5 < 0x6000 && !temp_s4)
            {
                romperProps.rotationY_F2 = var_s2;
            }
            else
            {
                var_a1 = Q12_MULT_PRECISE(Rng_TestProbabilityBits(9) + 0xF00, CLAMP_MIN_THEN_LOW(temp_s5 - 0x333, 0x333, 0x2800));

                romperProps.rotationY_F2 = Chara_HeadingAngleGet(romper, var_a1,
                                                                                  romperProps.positionX_FC, romperProps.positionZ_100, 0x1000, true);
            }
        }
        else
        {
            var_a1 = Q12_MULT_PRECISE(Rng_TestProbabilityBits(9) + 0xF00, 0x2800);

            romperProps.rotationY_F2 = Chara_HeadingAngleGet(romper, var_a1,
                                                                              romperProps.positionX_FC, romperProps.positionZ_100, 0x1000, false);
        }

        if (romperProps.rotationY_F2 == var_s2)
        {
            temp_s0 = func_8007029C(romper, CLAMP_HIGH(temp_s5, 0x1AAA), romper->rotation_24.vy);
        }
        else
        {
            temp_s0 = func_8007029C(romper, 0x1AAA, romper->rotation_24.vy);
        }

        if (romperProps.field_10E > 0x1000 && !Rng_TestProbabilityBits(4))
        {
            romper->model_0.controlState_2            = 1;
            romper->model_0.anim_4.status_0           = 24;
            romperProps.rotationY_F2 = romper->rotation_24.vy;
        }
        else if (temp_s0 != 0 || romperProps.rotationY_F2 == 0x1000 ||
                 temp_s5 < Q12_MULT_PRECISE(0x1000 - Math_Cos(var_s3 >> 1), 0x2800))
        {
            if (romperProps.rotationY_F2 == 0x1000)
            {
                romperProps.rotationY_F2 = romper->rotation_24.vy + 0x800;
            }

            if (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 0x73 || FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 0x78)
            {
                romper->model_0.controlState_2         = 4;
                romper->model_0.anim_4.status_0        = 28;
                romperProps.field_10C = 0;
                romper->moveSpeed_38                   = 0;
                romperProps.field_120 = 0;
            }
        }
    }

    for (i = 0; i < 3; i++)
    {
        var_s2 = func_8005BF38(romperProps.rotationY_F2 - romper->rotation_24.vy);

        if (TIMESTEP_ANGLE_4 < ABS(var_s2))
        {
            if (var_s2 > 0)
            {
                romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, 0x400);
            }
            else
            {
                romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, 0x400);
            }
        }
        else
        {
            romper->rotation_24.vy = romperProps.rotationY_F2;
            break;
        }
    }

    if (romperProps.flags_E8 & 0x10)
    {
        romperProps.field_120 += g_DeltaTime0;
        if (temp_s5 > 0x1CCC || romperProps.field_120 > 0x1CCC)
        {
            romperProps.field_120 = 0;
            romperProps.flags_E8 &= ~0x10;
        }
    }

    for (i = 0; i < 6; i++)
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

    if (player->flags_3E & 8)
    {
        return;
    }

    if (g_SysWork.sysState_8 != 0 || g_SysWork.field_2284[3] & 3)
    {
        return;
    }

    if (romper->field_34 != 0 || temp_s5 <= 0x4CC || temp_s5 >= 0x3333 ||
        romper->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy >= 0x1000 ||
        romper->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy <= -0x1333)
    {
        return;
    }

    if (romperProps.flags_E8 & 0x10)
    {
        return;
    }

    if (ABS(func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                 g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz) -
                          romper->rotation_24.vy)) < 0x155)
    {
        romper->model_0.controlState_2         = 5;
        romper->model_0.anim_4.status_0        = 4;
        romper->field_44.field_0               = 1;
        g_SysWork.field_2284[3]               |= 3;
        romperProps.flags_E8 |= 0x810;
    }
}

void Ai_Romper_Control_4(s_SubCharacter* romper)
{
    s32 temp_v0_5;
    s32 temp_s0;
    s32 temp_v1;
    s32 var_s0;
    s32 i;
    s32 var_v0_5;

    temp_v1 = g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3;
    if (temp_v1 == 0)
    {
        var_s0 = func_8006FD90(romper, 0, 0x2800, 0x6000);
    }
    else if (temp_v1 == 2)
    {
        var_s0 = func_8006FD90(romper, 0, 0x3000, 0x8000);
    }
    else
    {
        var_s0 = func_8006FD90(romper, 0, 0xCCC, 0x2000);
    }

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        var_s0 |= func_80070360(romper, 0, 0x333);
    }

    if (var_s0 != false)
    {
        romperProps.positionX_FC  = g_SysWork.playerWork_4C.player_0.position_18.vx;
        romperProps.positionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz;
        romperProps.field_10E     = 0;
    }
    else
    {
        romperProps.field_10E += g_DeltaTime0;
    }

    temp_s0 = func_8007029C(romper, 0x2800, romper->rotation_24.vy);

    if (romperProps.field_120 == 0 ||
        (temp_s0 != 0 && romperProps.field_120 >= 0))
    {
        romperProps.rotationY_F2 = 0;

        if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz) >= 0x800)
        {
            romperProps.rotationY_F2 = Chara_HeadingAngleGet(romper, 0x2800, romperProps.positionX_FC,
                                                                              romperProps.positionZ_100, 0x1000, true);
        }
        else
        {
            romperProps.rotationY_F2 = Chara_HeadingAngleGet(romper, 0x2800, romperProps.positionX_FC,
                                                                              romperProps.positionZ_100, 0x1000, false);
        }

        if (romperProps.rotationY_F2 == 0x1000)
        {
            romperProps.rotationY_F2 = func_8006F99C(romper, 0x2800, romper->rotation_24.vy);
        }

        if (temp_s0 != 0)
        {
            romperProps.field_120 = -(Rng_Rand16() % 0x1000 + 0x1000);
        }
        else
        {
            romperProps.field_120 = Rng_Rand16() % 0x2000 + 0x1000;
        }
    }

    if (romperProps.field_120 > 0)
    {
        romperProps.field_120 -= g_DeltaTime0;
        if (romperProps.field_120 < 0)
        {
            romperProps.field_120 = 0;
        }
    }
    else
    {
        romperProps.field_120 += g_DeltaTime0;
        if (romperProps.field_120 > 0)
        {
            romperProps.field_120 = 0;
        }
    }

    for (i = 0; i < 3; i++)
    {
        temp_v0_5 = func_8005BF38(romperProps.rotationY_F2 - romper->rotation_24.vy);

        if (TIMESTEP_ANGLE_0 < ABS(temp_v0_5))
        {
            if (temp_v0_5 > 0)
            {
                romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, 0x200);
            }
            else
            {
                romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, 0x200);
            }
        }
        else
        {
            romper->rotation_24.vy = romperProps.rotationY_F2;
        }
    }

    if (!func_8007029C(romper, 0x2800, romper->rotation_24.vy) && (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 0x82 &&
                                                                   FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 0x85))
    {
        romper->model_0.anim_4.status_0 = 40;
        romper->moveSpeed_38            = 0;
        return;
    }

    temp_v0_5 = func_8005BF38(romperProps.rotationY_F2 - romper->rotation_24.vy);
    if (temp_v0_5 >= 0)
    {
        var_v0_5 = 0x800 - temp_v0_5;
    }
    else
    {
        var_v0_5 = temp_v0_5 + 0x800;
    }

    Chara_MoveSpeedUpdate4(romper, 0x1333, Q12_MULT_PRECISE(var_v0_5 * 2, 0x2666));
}

void Ai_Romper_Control_5(s_SubCharacter* romper)
{
    s_Collision sp20;
    VECTOR3     sp30;
    s16         temp_v0_4;
    s16         temp_v0_5;
    s16         var_s3;
    s32         temp_a1;
    s32         temp_s2;
    s32         temp_v0;
    s32         temp_v0_3;
    s32         temp_v1_5;
    s16         var_a0_2;
    s32         i;
    s16         temp;

    if (romper->model_0.anim_4.status_0 == 5)
    {
        if (romper->model_0.anim_4.time_4 > 0x5000)
        {
            var_s3 = 0;
        }
        else
        {
            var_s3 = 0x800 - (FP_TO(romper->model_0.anim_4.time_4 - 0x2000, Q12_SHIFT) / 0x3000 >> 1);
        }
    }
    else
    {
        var_s3 = 0x800;
    }

    temp_v0                                   = Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Sin(g_SysWork.playerWork_4C.player_0.headingAngle_3C));
    romperProps.positionX_FC = g_SysWork.playerWork_4C.player_0.position_18.vx + Q12_MULT_PRECISE(temp_v0, var_s3);

    temp_a1                                    = Q12_MULT(g_SysWork.playerWork_4C.player_0.moveSpeed_38, Math_Cos(g_SysWork.playerWork_4C.player_0.headingAngle_3C));
    romperProps.positionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz + Q12_MULT_PRECISE(temp_a1, var_s3);

    temp_v0_3 = ratan2(romperProps.positionX_FC - romper->position_18.vx, romperProps.positionZ_100 - romper->position_18.vz);
    temp_s2   = temp_v0_3;

    if (romper->model_0.anim_4.status_0 == 4)
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, 0xF000), 0);

        for (i = 0; i < 4; i++)
        {
            temp_v0_4 = func_8005BF38(temp_s2 - romper->rotation_24.vy);

            if (((g_DeltaTime0 >> 3) + 1) >> 1 < ABS(temp_v0_4))
            {
                if (temp_v0_4 > 0)
                {
                    romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, 0x400) >> 1;
                }
                else
                {
                    romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, 0x400) >> 1;
                }
            }
            else
            {
                romper->rotation_24.vy = temp_s2;
            }
        }
    }
    else if (romper->model_0.anim_4.status_0 == 5)
    {
        temp_v0_5 = func_8005BF38(temp_v0_3 - romper->rotation_24.vy);

        if (TIMESTEP_ANGLE_0 < ABS(temp_v0_5))
        {
            if (temp_v0_5 > 0)
            {
                romper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, 0x200);
            }
            else
            {
                romper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, 0x200);
            }
        }

        if (romper->model_0.anim_4.time_4 == 0x2000)
        {
            temp_v1_5 = Math_Vector2MagCalc(romperProps.positionX_FC - romper->position_18.vx,
                                            romperProps.positionZ_100 - romper->position_18.vz);

            var_a0_2             = CLAMP_LOW(temp_v1_5, 0x4CC);
            romper->moveSpeed_38 = var_a0_2 << 1;
            Collision_Get(&sp20, g_SysWork.playerWork_4C.player_0.position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz);
            temp                                   = sp20.groundHeight_0 - 0xCCC;
            romper->field_34                       = (temp << 1) - 0x2733;
            romperProps.flags_E8 &= ~0x200;
        }
        else if (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) == 5 || FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) == 6)
        {
            if (!(romperProps.flags_E8 & 0x200))
            {
                func_8005DC1C(1403, &romper->position_18, 0x80, 0);
                romperProps.flags_E8 |= 0x200;
            }

            sp30.vx = romper->position_18.vx;
            sp30.vy = romper->position_18.vy;
            sp30.vz = romper->position_18.vz;

            if (func_8008A0E4(1, 54, romper, &sp30, &g_SysWork.playerWork_4C.player_0, romper->rotation_24.vy, 0x400) != -1)
            {
                romper->model_0.anim_4.status_0 = 6;
                romper->model_0.controlState_2  = 10;
                sharedFunc_800E9714_2_s02(romper);
                romperProps.flags_E8 |= 0x400;
            }
        }
    }
    else
    {
        if (romperProps.flags_E8 & 1)
        {
            Chara_MoveSpeedUpdate(romper, Q12_MULT_PRECISE(romper->moveSpeed_38, 0x3000) + 0x3000);
        }
        else
        {
            romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, 0xF000), 0);
        }
    }
}

void Ai_Romper_Control_6(s_SubCharacter* romper)
{
    s16 temp_s0;

    romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, 0xF000), 0);

    if ((romper->model_0.anim_4.status_0 >> 1) == 7 || (romper->model_0.anim_4.status_0 >> 1) == 8)
    {
        temp_s0                               = Q12_MULT_PRECISE(sharedData_800ECA4C_2_s02, g_DeltaTime0) * 0x999 / 0xA000;
        romperProps.field_F8 = Q12_MULT(temp_s0, Math_Sin(romper->rotation_24.vy));
        romperProps.field_FA = Q12_MULT(temp_s0, Math_Cos(romper->rotation_24.vy));
    }
}

void Ai_Romper_Control_7(s_SubCharacter* romper)
{
    s16 temp_s0;

    if (romperProps.flags_E8 & 1)
    {
        Chara_MoveSpeedUpdate(romper, Q12_MULT_PRECISE(romper->moveSpeed_38, 0x3000) + 0x3000);
    }
    else
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, 0xF000), 0);
    }

    if (romper->model_0.anim_4.status_0 == 22 || (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 92 &&
                                                    FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 97))
    {
        temp_s0 = Q12_MULT_PRECISE(sharedData_800ECACC_2_s02, g_DeltaTime0) * 0x1666 / 0x7000;

        romperProps.field_F8 = Q12_MULT(temp_s0, Math_Sin(romper->rotation_24.vy));
        romperProps.field_FA = Q12_MULT(temp_s0, Math_Cos(romper->rotation_24.vy));
    }

    if ((romper->model_0.anim_4.status_0 >> 1) == 10)
    {
        romper->flags_3E |= 2;
    }

    if (romper->health_B0 == Q12(0.0f) && romper->model_0.anim_4.status_0 == 21)
    {
        romper->model_0.controlState_2  = 8;
        romper->model_0.anim_4.status_0 = 12;
        romper->flags_3E               &= 0xFFFD;

        func_80037DC4(romper);
    }
}

void Ai_Romper_Control_8(s_SubCharacter* romper)
{
    if (romper->health_B0 == Q12(0.0f))
    {
        if (g_SysWork.targetNpcIdx_2353 != func_8005C7D0(romper))
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

    if (romper->position_18.vx != romperProps.positionX_FC ||
        romper->position_18.vz != romperProps.positionZ_100)
    {
        romperProps.rotationY_F2 = ratan2(romperProps.positionX_FC - romper->position_18.vx,
                                                           romperProps.positionZ_100 - romper->position_18.vz);
    }

    if (romper->model_0.anim_4.status_0 == 11)
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, romperProps.field_124 * 4), 0);
    }
    else
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, romperProps.field_124), 0);
    }

    romper->field_E1_0 = 0;

    if (romper->model_0.anim_4.status_0 == 11)
    {
        romperProps.field_104 = romper->model_0.anim_4.time_4 - 0x14000;
    }
    else
    {
        romperProps.field_104 = 0;
    }

    player = &g_SysWork.playerWork_4C.player_0;

    if (player->attackReceived_41 == NO_VALUE)
    {
        romper->model_0.anim_4.status_0 = 18;
        romper->model_0.controlState_2  = 11;
        romper->field_E1_0              = 0;
        romper->field_E1_0              = 3;
    }
    else if (romper->model_0.anim_4.time_4 <= 0x17FFF)
    {
        romperProps.flags_E8 |= 0x40;
    }
    else if (romperProps.flags_E8 & 0x40)
    {
        romperProps.flags_E8 &= ~0x40;

        g_SysWork.playerWork_4C.player_0.damage_B4.amount_C += FP_TO(D_800AD4C8[55].field_4, Q12_SHIFT) *
                                                               (Rng_TestProbabilityBits(5) + 0x55) / 100;

        sp10.vx = romper->position_18.vx + FP_FROM(FP_TO(Math_Sin(romper->rotation_24.vy) >> 1, Q12_SHIFT), Q12_SHIFT);
        sp10.vy = romper->position_18.vy - 0x199;
        sp10.vz = romper->position_18.vz + FP_FROM(FP_TO(Math_Cos(romper->rotation_24.vy) >> 1, Q12_SHIFT), Q12_SHIFT);

        func_8005F6B0(&g_SysWork.playerWork_4C.player_0, &sp10, 4, 9);

        romperProps.field_11A = 1;
    }
}

void Ai_Romper_Control_11(s_SubCharacter* romper)
{
    if (romper->model_0.anim_4.status_0 == ANIM_STATUS(RomperAnim_12, true) &&
        (Rng_Rand16() % 8) == 0)
    {
        g_SysWork.field_2284[3]                  &= ~((1 << 0) | (1 << 1));
        romper->model_0.controlState_2                   = RomperControl_1;
        romperProps.flags_E8 &= ~RomperFlag_11;
    }
}

void sharedFunc_800E8730_2_s02(s_SubCharacter* romper)
{
    s_800C4590 sp10;
    VECTOR3    sp30;
    s16        temp_s4;
    s32        temp_s0;
    s32        temp_s2;
    s32        temp_s3;
    s32        temp_v0;

    romper->field_34 += g_DeltaTime2;

    if ((romper->model_0.anim_4.status_0 >> 1) == 3 || (romper->model_0.anim_4.status_0 >> 1) == 5)
    {
        romper->headingAngle_3C = romperProps.rotationY_F2;
    }
    else
    {
        romper->headingAngle_3C = romper->rotation_24.vy;
    }

    if (g_DeltaTime0 != 0)
    {
        temp_s4 = romper->headingAngle_3C;
        temp_s0 = Q12_MULT_PRECISE(g_DeltaTime0, romper->moveSpeed_38);
        temp_s2 = (temp_s0 < -0x7FFF || temp_s0 > 0x7FFF) * 4;
        temp_v0 = Math_Sin(temp_s4);
        temp_s3 = temp_s2 >> 1;
        temp_s0 = temp_s0 >> temp_s3;

        sp30.vx = Q12_MULT_PRECISE(temp_s0, temp_v0 >> temp_s3) << temp_s2;
        sp30.vz = Q12_MULT_PRECISE(temp_s0, Math_Cos(temp_s4) >> temp_s3) << temp_s2;
        sp30.vy = Q12_MULT_PRECISE(g_DeltaTime0, romper->field_34);

        sp30.vx += romperProps.field_F8;
        sp30.vz += romperProps.field_FA;

        func_80069B24(&sp10, &sp30, romper);

        romper->position_18.vx += sp10.offset_0.vx;
        romper->position_18.vz += sp10.offset_0.vz;

        if (romperProps.flags_E8 & 0x400)
        {
            if (romper->model_0.controlState_2 != 0xA && romper->position_18.vy <= sp10.field_C)
            {
                romperProps.flags_E8 &= ~0x400;
            }

            if (romperProps.flags_E8 & 0x400)
            {
                if (romper->model_0.controlState_2 == 0xA)
                {
                    romper->position_18.vy += sp10.offset_0.vy;

                    if (g_SysWork.playerWork_4C.player_0.position_18.vy < romper->position_18.vy)
                    {
                        romper->position_18.vy = g_SysWork.playerWork_4C.player_0.position_18.vy;
                        romper->field_34       = 0;
                    }
                }
                else
                {
                    romper->position_18.vy -= Q12_MULT_PRECISE(g_DeltaTime0, 0x266);
                    romper->field_34        = 0;

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
                    romper->field_34       = 0;
                }
            }
        }
        else
        {
            romper->position_18.vy += sp10.offset_0.vy;

            if (sp10.field_C < romper->position_18.vy)
            {
                romper->position_18.vy = sp10.field_C;
                romper->field_34       = 0;
            }
        }

        romperProps.field_FA = 0;
        romperProps.field_F8 = 0;
    }

    romper->rotation_24.vy = func_8005BF38(romper->rotation_24.vy);

    if (romper->field_34 != 0)
    {
        romperProps.flags_E8 |= 1;
    }
    else
    {
        romperProps.flags_E8 &= ~1;
    }
}

void sharedFunc_800E8A40_2_s02(s_SubCharacter* romper, s_AnmHeader* arg1, GsCOORDINATE2* arg2)
{
    typedef struct
    {
        MATRIX  field_0;
        SVECTOR field_20;
    } s_sharedFunc_800E8A40_2_s02;

    s32                          temp_v0_3;
    s32                          var_a1;
    s32                          temp_v0_4;
    s_AnimInfo*                  anim;
    s_sharedFunc_800E8A40_2_s02* ptr;

    ptr = PSX_SCRATCH;

    switch (romper->model_0.anim_4.status_0)
    {
        case 27:
        case 35:
        case 37:
            ROPMER_ANIM_INFOS[romper->model_0.anim_4.status_0].duration_8.constant = sharedData_800EC950_2_s02;
            break;

        case 28:
            sharedData_800ECB22_2_s02 = romperProps.field_10C + 0x83;
            break;

        case 29:
            ROPMER_ANIM_INFOS[29].startKeyframeIdx_C                               = romperProps.field_10C + 0x83;
            romperProps.field_10C                                 = 0;
            ROPMER_ANIM_INFOS[romper->model_0.anim_4.status_0].duration_8.constant = Q12_MULT_PRECISE(MAX(romper->moveSpeed_38, 0x1800), 0x851E);
            break;

        case 38:
            sharedData_800ECBC2_2_s02 = romperProps.field_10C + 0x6D;
            break;

        case 39:
            sharedData_800ECBD0_2_s02 = romperProps.field_10C + 0x6D;
            break;
    }

    Math_MatrixTransform(&romper->position_18, (SVECTOR*)&romper->rotation_24, arg2);

    anim = &ROPMER_ANIM_INFOS[romper->model_0.anim_4.status_0];
    anim->updateFunc_0(&romper->model_0, arg1, arg2, anim);

    switch (romper->model_0.anim_4.status_0)
    {
        case 14:
            romper->model_0.controlState_2 = 6;
            if (romper->model_0.anim_4.time_4 == 0x7F000)
            {
                romper->model_0.anim_4.status_0 = 0xF;
                romper->model_0.anim_4.time_4   = 0x27000;
            }
            break;

        case 16:
            romper->model_0.controlState_2 = 6;
            if (romper->model_0.anim_4.time_4 == 0x74000)
            {
                romper->model_0.anim_4.status_0 = 0x11;
                romper->model_0.anim_4.time_4   = 0x32000;
            }
            break;

        case 26:
            if (romper->model_0.controlState_2 == 5)
            {
                romperProps.flags_E8 &= ~0x800;
                g_SysWork.field_2284[3]               &= 0xFFFC;
            }

            romper->model_0.controlState_2        = 3;
            romperProps.field_F4 = 0x15FFF;

            if (romper->model_0.anim_4.time_4 == 0x31000)
            {
                romper->model_0.anim_4.status_0       = 0x1B;
                romperProps.field_F4 = 0xFFF;
                romper->model_0.anim_4.time_4         = 0x6E000;
                romperProps.field_F0 = 0x477;
                romper->moveSpeed_38                  = 0;
            }
            else if (romper->model_0.anim_4.time_4 == 0x3C000)
            {
                romper->model_0.anim_4.status_0       = 0x1B;
                romperProps.field_F4 = 0xAFFF;
                romperProps.field_F0 = 0x79;
                romper->model_0.anim_4.time_4         = 0x78000;
                romper->moveSpeed_38                  = 0x1333;
            }
            break;

        case 39:
        case 41:
            romper->model_0.controlState_2        = 3;
            romper->model_0.anim_4.status_0       = 0x1B;
            romperProps.field_F4 = romper->model_0.anim_4.time_4 - 0x6D001;
            break;
    }

    temp_v0_3 = func_8005BF38(romperProps.field_EC - romper->rotation_24.vy);

    if (temp_v0_3 == 0)
    {
        var_a1 = 0;
    }
    else
    {
        var_a1 = 0xC4;
    }

    if (temp_v0_3 < 0)
    {
        var_a1 = -var_a1;
    }

    temp_v0_4 = Q12_MULT_PRECISE(g_DeltaTime0, 0x100);

    if (var_a1 < romperProps.field_EE)
    {
        romperProps.field_EE = MAX(var_a1, romperProps.field_EE - temp_v0_4);
    }
    else
    {
        romperProps.field_EE = CLAMP_HIGH(var_a1, romperProps.field_EE + temp_v0_4);
    }

    *(s32*)&ptr->field_20 = romperProps.field_EE << 16;
    ptr->field_20.vz      = 0;

    Math_RotMatrixZxyNegGte(&ptr->field_20, &ptr->field_0);
    MulMatrix2(&ptr->field_0, &arg2[2].coord);

    romperProps.field_EC = romper->rotation_24.vy;
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

#define CopyData(arg0, data)                      \
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
    s32 sp10[2];
    s32 var_a1;
    s32 i;

    switch (romper->model_0.anim_4.status_0)
    {
        case 5:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 2; i < 2; i++, var_a1++)
            {
                sp10[i] = var_a1 - !(var_a1 < 5);
            }
            func_80070400(romper, &sharedData_800ECC58_2_s02[sp10[0]], &sharedData_800ECC58_2_s02[sp10[1]]);
            break;

        case 6:
        case 7:
        case 10:
        case 11:
            CopyData(romper, sharedData_800ECCBC_2_s02);
            break;

        case 9:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0xF; i < 2; i++, var_a1++)
            {
                sp10[i] = var_a1;
            }
            func_80070400(romper, &sharedData_800ECCD0_2_s02[sp10[0]], &sharedData_800ECCD0_2_s02[sp10[1]]);
            break;

        case 15:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x27; i < 2; i++, var_a1++)
            {
                sp10[i] = var_a1;
            }
            func_80070400(romper, &sharedData_800ECD48_2_s02[sp10[0]], &sharedData_800ECD48_2_s02[sp10[1]]);
            break;

        case 17:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x32; i < 2; i++, var_a1++)
            {
                sp10[i] = var_a1;
            }
            func_80070400(romper, &sharedData_800ECE24_2_s02[sp10[0]], &sharedData_800ECE24_2_s02[sp10[1]]);
            break;

        case 12:
        case 13:
        case 20:
        case 21:
        case 32:
        case 33:
            CopyData(romper, sharedData_800ECF00_2_s02[4]);
            break;

        case 22:
            CopyData(romper, sharedData_800ECF00_2_s02[0]);
            break;

        case 23:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x5D; i < 2; i++, var_a1++)
            {
                sp10[i] = var_a1 >= 4 ? 4 : var_a1;
            }
            func_80070400(romper, &sharedData_800ECF00_2_s02[sp10[0]], &sharedData_800ECF00_2_s02[sp10[1]]);
            break;

        case 25:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x64; i < 2;
                 i++, var_a1   = (var_a1 + 1) % 9)
            {
                sp10[i] = var_a1;
            }
            func_80070400(romper, &sharedData_800ECF64_2_s02[sp10[0]], &sharedData_800ECF64_2_s02[sp10[1]]);
            break;

        case 27:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x6D; i < 2;
                 i++, var_a1   = (var_a1 + 1) % 22)
            {
                sp10[i] = var_a1;
            }
            func_80070400(romper, &sharedData_800ED018_2_s02[sp10[0]], &sharedData_800ED018_2_s02[sp10[1]]);
            break;

        case 29:
            CopyData(romper, sharedData_800ED2C0_2_s02);
            break;

        case 31:
            for (i = 0, var_a1 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x93; i < 2;
                 i++, var_a1   = (var_a1 + 1) % 16)
            {
                sp10[i] = var_a1 - (var_a1 > 0) - !(var_a1 < 4) - !(var_a1 < 8) - !(var_a1 < 0xC);
            }
            func_80070400(romper, &sharedData_800ED1D0_2_s02[sp10[0]], &sharedData_800ED1D0_2_s02[sp10[1]]);
            break;

        case 19:
            CopyData(romper, sharedData_800ECD34_2_s02);
            romper->field_D4.radius_0 = (romper->model_0.anim_4.time_4 - 0x3D000) / 100;
            break;

        default:
            CopyData(romper, sharedData_800ECC44_2_s02);
            break;
    }

    func_8005C814(&romper->field_D8, romper);

    if ((romper->model_0.anim_4.status_0 >> 1) != 2)
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

    if (romper->model_0.anim_4.time_4 <  Q12(109.0f) ||
        romper->model_0.anim_4.time_4 >= Q12(131.0f))
    {
        return 0;
    }

    relAnimTime = romper->model_0.anim_4.time_4 - Q12(109.0f);
    if (relAnimTime < romperProps.field_F4)
    {
        romperProps.field_F0 = -0x194;
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
                    if (romper->field_34 == 0)
                    {
                        romper->field_34 = -0x2A77;
                    }
                    break;

                case 11:
                    if (romper->field_34 == 0)
                    {
                        romper->field_34 = -0x30FF;
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
    s32 sp10;
    s32 sp14;
    s16 sp18;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_s0;

    temp_s3   = romper->moveSpeed_38;
    var_s0    = 0x8000;
    temp_v0   = FP_TO(temp_s3, Q12_SHIFT) / var_s0;
    temp_v0_4 = temp_s3 - Q12_MULT_PRECISE(temp_v0, 0x4000);
    sp18      = romper->rotation_24.vy;
    temp_v0_5 = Q12_MULT_PRECISE(temp_v0_4, temp_v0);

    if (temp_v0_5 >= Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                         g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz))
    {
        sp10 = romper->position_18.vx + Q12_MULT(temp_v0_5, Math_Sin(sp18));
        sp14 = romper->position_18.vz + Q12_MULT(temp_v0_5, Math_Cos(sp18));
    }
    else
    {
        sp10 = g_SysWork.playerWork_4C.player_0.position_18.vx;
        sp14 = g_SysWork.playerWork_4C.player_0.position_18.vz;
    }

    sharedFunc_800D2E9C_0_s00(&sp10, &sp14, &sp18);

    temp_v0 = (FP_TO(Math_Vector2MagCalc(sp10 - romper->position_18.vx, sp14 - romper->position_18.vz), Q12_SHIFT) << 1) / temp_s3;
    var_s0  = FP_TO(temp_s3, Q12_SHIFT) / temp_v0;

    if (var_s0 < 0)
    {
        var_s0 = 0x4000;
    }

    if (var_s0 > 0x20000)
    {
        var_s0 = 0x20000;
    }

    romperProps.rotationY_F2  = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                                        g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz);
    romperProps.field_124     = var_s0;
    romperProps.positionX_FC  = sp10;
    romperProps.positionZ_100 = sp14;
}

#undef romperProps
