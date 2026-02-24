#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/creeper.h"

#define creeperProps creeper->properties_E4.creeper

void Ai_Creeper_Update(s_SubCharacter* creeper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    // Initialize.
    if (creeper->model_0.controlState_2 == CreeperControl_None)
    {
        Ai_Creeper_Init(creeper);
    }

    if (g_DeltaTime != Q12(0.0f))
    {
        sharedFunc_800D7EE8_1_s02(creeper);
        Ai_Creeper_ControlUpdate(creeper);
        sharedFunc_800D983C_1_s02(creeper);
    }

    sharedFunc_800D9960_1_s02(creeper, anmHdr, coords);
    sharedFunc_800D99D0_1_s02(creeper);
}

// This inline allows getting rid of some ugly gotos, couldn't find a different way to handle it.
static inline void Ai_Creeper_PropertiesUpdateFromStep(s_SubCharacter* creeper)
{
    s32 stateStep;

    stateStep = creeper->model_0.stateStep_3;
    if (creeper->model_0.stateStep_3 != 3)
    {
        if (stateStep < 3)
        {
            return;
        }

        if (stateStep >= 14)
        {
            return;
        }

        if (stateStep < 12)
        {
            return;
        }

        creeperProps.flags_E8               |= CreeperFlag_4;
        creeperProps.prevTargetPositionX_FC  = creeper->position_18.vx;
        creeperProps.prevTargetPositionZ_100 = creeper->position_18.vz;
    }

    if (creeper->model_0.stateStep_3 == 13 || creeper->model_0.stateStep_3 == 3)
    {
        creeperProps.flags_E8 |= CreeperFlag_6;
    }

    creeper->model_0.controlState_2 = 1;
    Character_AnimSet(creeper, ANIM_STATUS(CreeperAnim_11, true), 94);
}

void Ai_Creeper_Init(s_SubCharacter* creeper)
{
    // TODO: Values used in the `Rng_Rand16` calls at the end. TODO: Not sure of the actual purpose yet.
    #define BASE_EASY_VAL   0.7f
    #define BASE_NORMAL_VAL 0.9f
    #define BASE_HARD_VAL   1.2f
    #define RAND_EASY_MAX   0.2f
    #define RAND_NORMAL_MAX 0.2f
    #define RAND_HARD_MAX   0.4f

    s32 i;

    // Check if any other Creeper NPCs are present, making sure to skip this `s_SubCharacter` instance in the NPC array.
    i = 0;
    do
    {
        if (creeper == &g_SysWork.npcs_1A0[i] || g_SysWork.npcs_1A0[i].model_0.charaId_0 != Chara_Creeper)
        {
            i++;
            continue;
        }

        break;
    }
    while (i < ARRAY_SIZE(g_SysWork.npcs_1A0));

    if (i == ARRAY_SIZE(g_SysWork.npcs_1A0))
    {
        // No other Creepers present.
        sharedData_800E57CC_1_s02 = 0;
    }

    creeper->health_B0              = Q12(200.0f);
    creeperProps.flags_E8           = CreeperFlag_None;
    creeper->model_0.anim_4.alpha_A = Q12(0.0f);
    creeper->moveSpeed_38           = Q12(0.0f);
    creeper->headingAngle_3C        = creeper->rotation_24.vy;
    creeper->field_E1_0             = 2;

    Chara_PropertiesClear(creeper);
    Ai_Creeper_PropertiesUpdateFromStep(creeper);
    ModelAnim_AnimInfoSet(&creeper->model_0.anim_4, CREEPER_ANIM_INFOS);
    Chara_DamageClear(creeper);

    creeperProps.targetPositionX_F4 = creeper->position_18.vx;
    creeperProps.targetPositionZ_F8 = creeper->position_18.vz;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        creeperProps.moveSpeed_10C = Q12_MULT_FLOAT_PRECISE((Q12(BASE_EASY_VAL) + (Rng_Rand16() % Q12(RAND_EASY_MAX))), 2.0f);
    }
    else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
    {
        creeperProps.moveSpeed_10C = Q12_MULT_FLOAT_PRECISE((Q12(BASE_NORMAL_VAL) + (Rng_Rand16() % Q12(RAND_NORMAL_MAX))), 2.0f);
    }
    else
    {
        creeperProps.moveSpeed_10C = Q12_MULT_FLOAT_PRECISE((Q12(BASE_HARD_VAL) + (Rng_Rand16() % Q12(RAND_HARD_MAX))), 2.0f);
    }

#ifdef MAP5_S00
    creeper->flags_3E |= CharaFlag_Unk9;
#endif

    #undef BASE_EASY_VAL
    #undef BASE_NORMAL_VAL
    #undef BASE_HARD_VAL
    #undef RAND_EASY_MAX
    #undef RAND_NORMAL_MAX
    #undef RAND_HARD_MAX
}

void sharedFunc_800D7EE8_1_s02(s_SubCharacter* creeper)
{
    #define playerChara g_SysWork.playerWork_4C.player_0

    if (creeper->damage_B4.amount_C > Q12(0.0f) && creeper->health_B0 > Q12(0.0f))
    {
        func_8005DC1C(Sfx_Unk1425, &creeper->position_18, Q8_CLAMPED(0.5f), 0);
        creeperProps.timer_104 = Q12(0.0f);

        // TODO: Weird position scaling?
        creeper->damage_B4.position_0.vx += (creeper->moveSpeed_38 * Math_Sin(creeper->headingAngle_3C)) >> 15;
        creeper->damage_B4.position_0.vz += (creeper->moveSpeed_38 * Math_Cos(creeper->headingAngle_3C)) >> 15;

        creeper->moveSpeed_38 = (SquareRoot0(SQUARE(Q12_TO_Q6(creeper->damage_B4.position_0.vx)) +
                                             SQUARE(Q12_TO_Q6(creeper->damage_B4.position_0.vz))) << 18) /
                                Q12(0.8f);

        creeper->fallSpeed_34    = FP_TO(creeper->damage_B4.position_0.vy, Q12_SHIFT) / Q12(0.8f);
        creeper->headingAngle_3C = Rng_AddGeneratedUInt(ratan2(creeper->damage_B4.position_0.vx, creeper->damage_B4.position_0.vz), -128, 127);

        creeperProps.flags_E8 |= CreeperFlag_1;

        if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_7)
        {
            creeper->health_B0 = Q12(0.0f);

            creeperProps.animStatus_10A = ANIM_STATUS(CreeperAnim_16, true);
            if (creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_7, true))
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_16, true);
            }
            else
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_16, false);
            }
        }
        else if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_8)
        {
            creeper->health_B0 = Q12(0.0f);

            creeperProps.animStatus_10A = ANIM_STATUS(CreeperAnim_17, true);
            if (creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_8, true))
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_17, true);
            }
            else
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_17, false);
            }
        }
        else if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_9)
        {
            creeper->health_B0               = Q12(0.0f);
            creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_3, false);
            creeper->model_0.controlState_2         = CreeperControl_5;
        }
        else if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == 10)
        {
            creeper->health_B0               = Q12(0.0f);
            creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_4, false);
            creeper->model_0.controlState_2         = CreeperControl_5;
        }
        else
        {
            if (creeper->model_0.controlState_2 == CreeperControl_3)
            {
                g_SysWork.field_2284[3] &= ~(1 << 1);
            }

            creeper->model_0.controlState_2 = CreeperControl_4;
            creeper->health_B0       = Q12(20.0f);
            creeper->flags_3E       |= CharaFlag_Unk2;

            if (ABS(func_8005BF38(Math_AngleBetweenPositionsGet(creeper->position_18, playerChara.position_18) -
                                  creeper->rotation_24.vy)) < Q12_ANGLE(60.0f))
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_7, false);
            }
            else
            {
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_8, false);
            }
        }
    }

    if (creeper->damage_B4.amount_C < Q12(200.0f) || creeper->health_B0 <= Q12(0.0f))
    {
        Chara_DamageClear(creeper);
    }

    #undef playerChara
}

void Ai_Creeper_ControlUpdate(s_SubCharacter* creeper)
{
    // Handle control state.
    switch (creeper->model_0.controlState_2)
    {
        case CreeperControl_1:
            Ai_Creeper_Control_1(creeper);
            break;

        case CreeperControl_2:
            Ai_Creeper_Control_2(creeper);
            break;

        case CreeperControl_3:
            Ai_Creeper_Control_3(creeper);
            break;

        case CreeperControl_4:
            Ai_Creeper_Control_4(creeper);
            break;

        case CreeperControl_5:
            Ai_Creeper_Control_5(creeper);
            break;
    }

    // Reset alerted flag.
    creeperProps.flags_E8 &= ~CreeperFlag_Alerted;
}

void Ai_Creeper_Control_1(s_SubCharacter* creeper)
{
    bool cond;

    Chara_MoveSpeedUpdate3(creeper, Q12(4.0f), Q12(0.0f));
    creeperProps.timer_104 += g_DeltaTime;

    if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
        cond = func_8006FD90(creeper, 2, Q12(12.0f), Q12(8.0f));
    }
    else if ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) &&
             (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)))
    {
        cond = func_8006FD90(creeper, 2, Q12(0.8f), Q12(0.4f));
    }
    else
    {
        cond = func_8006FD90(creeper, 2, Q12(4.0f), Q12(12.0f));
    }

    cond |= func_80070360(creeper, Q12(0.0f), Q12(0.5f));
    if (cond)
    {
        creeper->flags_3E |= CharaFlag_Unk3;

        if (Rng_GenerateUInt(0, 7) == 0 && // 1 in 8 chance.
            creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_11, true))
        {
            creeper->model_0.controlState_2  = CreeperControl_2;
            creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_13, false);
            creeperProps.timer_F0            = Q12(0.5f);
            creeperProps.timer_104           = Q12(0.0f);
            return;
        }
    }

    // Check if Creeper was alerted.
    if (creeperProps.flags_E8 & CreeperFlag_Alerted)
    {
        creeper->model_0.controlState_2                 = CreeperControl_2;
        creeper->model_0.anim_4.status_0         = ANIM_STATUS(CreeperAnim_13, false);
        creeperProps.timer_F0  = Q12(0.5f);
        creeperProps.timer_104 = Q12(0.0f);
    }
    else if (creeperProps.flags_E8 & CreeperFlag_6)
    {
        if (creeperProps.flags_E8 & CreeperFlag_7)
        {
            if (!Rng_GenerateUInt(0, 7)) // 1 in 8 chance.
            {
                if (creeperProps.timer_104 > Q12(0.5f))
                {
                    if (creeperProps.timer_104 < Q12(2.5f))
                    {
                        func_8005DC1C(Sfx_Unk1427, &creeper->position_18, Q8_CLAMPED(0.5f), 0);

                        creeperProps.timer_104 = Q12(0.0f);
                        sharedData_800E57CC_1_s02--;
                        creeperProps.flags_E8 &= ~CreeperFlag_7;
                    }
                }
            }
        }
        else if (sharedData_800E57CC_1_s02 == 0)
        {
            if (!Rng_GenerateUInt(0, 511) && creeperProps.timer_104 > Q12(4.0f)) // 1 in 512 chance.
            {
                s32 i;

                func_8005DC1C(Sfx_Unk1427, &creeper->position_18, Q8_CLAMPED(0.5f), 0);
                creeperProps.timer_104 = Q12(0.0f);

                // Update other Creepers.
                for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
                {
                    #define curNpc g_SysWork.npcs_1A0[i]

                    // Check if NPC is Creeper.
                    if (curNpc.model_0.charaId_0 != Chara_Creeper)
                    {
                        continue;
                    }

                    if (curNpc.field_40 != creeper->field_40 &&
                        (curNpc.properties_E4.creeper.flags_E8 & CreeperFlag_6) &&
                        curNpc.model_0.controlState_2 == CreeperControl_1 &&
                        !Math_Distance2dCheck(&creeper->position_18, &curNpc.position_18, Q12(16.0f)))
                    {
                        curNpc.properties_E4.creeper.timer_104 = Q12(0.0f);
                        sharedData_800E57CC_1_s02++;
                        curNpc.properties_E4.creeper.flags_E8 |= CreeperFlag_7;
                    }

                    #undef curNpc
                }
            }
            else if (!Rng_GenerateUInt(0, 63) && creeperProps.timer_104 > Q12(2.0f)) // 1 in 64 chance.
            {
                func_8005DC1C(Sfx_Unk1426, &creeper->position_18, Q8_CLAMPED(0.5f), 0);
                creeperProps.timer_104 = Rng_GenerateInt(Q12(0.8f), Q12(1.8f) - 1);
            }
        }
    }
}

void Ai_Creeper_Control_2(s_SubCharacter* creeper)
{
    q3_12         unkAngleDelta;
    q3_12         angleDeltaToPlayer;
    q19_12        distToPlayer;
    q19_12        distToTarget;

    #define playerChara g_SysWork.playerWork_4C.player_0

    angleDeltaToPlayer = func_8005BF38((Math_AngleBetweenPositionsGet(creeper->position_18, playerChara.position_18) -
                                        creeper->rotation_24.vy));

    if (((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1) && func_8006FD90(creeper, 0, Q12(12.0f), Q12(8.0f))) ||
        ((g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 1)) &&
         (g_SysWork.field_2388.field_154.effectsInfo_0.field_0.s_field_0.field_0 & (1 << 0)) && func_8006FD90(creeper, 2, Q12(0.8f), Q12(0.4f))) ||
        (!(g_SysWork.field_2388.field_154.effectsInfo_0.field_0.field_0 & ((1 << 0) | (1 << 1))) && func_8006FD90(creeper, 1, Q12(4.0f), Q12(12.0f))) ||
        (func_80070360(creeper, 0, Q12(0.5f)) || creeperProps.flags_E8 & CreeperFlag_Alerted))
    {
        creeperProps.targetPositionX_F4 = playerChara.position_18.vx;
        creeperProps.targetPositionZ_F8 = playerChara.position_18.vz;
        creeperProps.flags_E8          &= ~CreeperFlag_5;
    }

    distToPlayer = Math_Vector2MagCalc(playerChara.position_18.vx - creeper->position_18.vx,
                                       playerChara.position_18.vz - creeper->position_18.vz);
    distToTarget = Math_Vector2MagCalc(creeperProps.targetPositionX_F4 - creeper->position_18.vx,
                                       creeperProps.targetPositionZ_F8 - creeper->position_18.vz);

    if (distToTarget < Q12(1.2f) && !(creeperProps.flags_E8 & CreeperFlag_0) &&
        !func_800700F8(creeper, &playerChara))
    {
        if (distToPlayer > Q12(1.2f))
        {
            //if ((creeperProps.flags_E8 & (CreeperFlag_4 | CreeperFlag_5)) == CreeperFlag_4) // TODO: Doesn't match?
            if ((creeper->properties_E4.player.afkTimer_E8 & 0x30) == 0x10)
            {
                creeperProps.flags_E8          |= CreeperFlag_5;
                creeperProps.targetPositionX_F4 = creeperProps.prevTargetPositionX_FC;
                creeperProps.targetPositionZ_F8 = creeperProps.prevTargetPositionZ_100;
            }
            else
            {
                creeper->model_0.controlState_2  = CreeperControl_1;
                creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_11, false);
                creeperProps.timer_F0            = Q12(0.0f);
            }
        }
        else if (!(g_SysWork.field_2284[3] & (1 << 1)) && !Chara_HasFlag(&playerChara, CharaFlag_Unk4) &&
                 distToPlayer < Q12(0.5f) && ABS(angleDeltaToPlayer) < Q12_ANGLE(10.0f) &&
                 playerChara.health_B0 > Q12(0.0f))
        {
            creeper->model_0.controlState_2  = CreeperControl_3;
            creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_12, false);
            creeperProps.timer_F0            = Q12(0.0f);
            g_SysWork.field_2284[3]         |= 1 << 1;
        }
        else
        {
            if (ABS(angleDeltaToPlayer) >= Q12_ANGLE(90.0f))
            {
                Chara_MoveSpeedUpdate(creeper, Q12(4.0f));
            }
            else
            {
                Chara_MoveSpeedUpdate3(creeper, Q12(1.5f), (creeperProps.moveSpeed_10C * (Q12_ANGLE(90.0f) - ABS(angleDeltaToPlayer))) >> 10);
            }

            if (TIMESTEP_ANGLE(1, 2) < ABS(angleDeltaToPlayer) && Rng_GenerateInt(0, 7)) // 1 in 8 chance.
            {
                if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
                {
                    creeper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(180.0f));
                }
                else
                {
                    creeper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(180.0f));
                }
            }
        }
    }
    else
    {
        Chara_MoveSpeedUpdate4(creeper, Q12(1.5f), creeperProps.moveSpeed_10C);

        creeperProps.timer_F0 += g_DeltaTime;

        if ((ABS(angleDeltaToPlayer) > Q12_ANGLE(10.0f) && func_80070184(creeper, Q12(1.0f), creeperProps.rotationY_108)) ||
            (!Rng_GenerateInt(0, 7) && // 1 in 8 chance.
             ((!(creeperProps.flags_E8 & CreeperFlag_0) && creeperProps.timer_F0 > Q12(0.5f)) ||
              ( (creeperProps.flags_E8 & CreeperFlag_0) && creeperProps.timer_F0 > Q12(2.0f)))))
        {
            if (creeperProps.timer_F0 > Q12(2.0f))
            {
                creeperProps.flags_E8 &= ~CreeperFlag_0;
            }

            creeperProps.rotationY_108 = Chara_HeadingAngleGet(creeper,
                                                               Q12(1.2f),
                                                               creeperProps.targetPositionX_F4,
                                                               creeperProps.targetPositionZ_F8,
                                                               Q12(1.0f),
                                                               true);
            if (creeperProps.rotationY_108 == Q12_ANGLE(360.0f))
            {
                creeperProps.rotationY_108 = creeper->rotation_24.vy;
            }
            else
            {
                creeperProps.timer_F0 = Q12(0.0f);
            }
        }

        unkAngleDelta = func_8005BF38(creeperProps.rotationY_108 - creeper->rotation_24.vy);
        if (TIMESTEP_ANGLE(1, 2) < ABS(unkAngleDelta))
        {
            if (unkAngleDelta > Q12_ANGLE(0.0f))
            {
                creeper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(180.0f));
            }
            else
            {
                creeper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(180.0f));
            }
        }
    }

    #undef playerChara
}

void Ai_Creeper_Control_3(s_SubCharacter* creeper)
{
    VECTOR3 creeperPos;
    s32     i;
    q19_12  moveSpeed0;
    q19_12  distToPlayer;
    q19_12  moveSpeed;
    q19_12  moveSpeedTmp0;

    #define playerChara g_SysWork.playerWork_4C.player_0

    if (func_800700F8(creeper, &playerChara))
    {
        g_SysWork.field_2284[3]         &= ~(1 << 1);
        creeper->model_0.controlState_2         = CreeperControl_2;
        creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_13, false);
        return;
    }

    if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_12 ||
        creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_2, false) ||
        ANIM_TIME_RANGE_CHECK(creeper->model_0.anim_4.time_4, 4, 7))
    {
        distToPlayer = Math_Vector2MagCalc(playerChara.position_18.vx - creeper->position_18.vx,
                                           playerChara.position_18.vz - creeper->position_18.vz);
        if (distToPlayer < Q12(0.4f))
        {
            Chara_MoveSpeedUpdate3(creeper, Q12(16.0f), Q12(0.0f));
        }
        else
        {
            moveSpeed0 = creeperProps.moveSpeed_10C / 2;

            // TODO: Why don't either of these fit?
            // creeper->moveSpeed_38 = APPROACH(creeper->moveSpeed_38, moveSpeed0, Q12_MULT_PRECISE(g_DeltaTime, Q12(6.0f)));
            // Chara_MoveSpeedUpdate3(creeper, Q12(6.0f), moveSpeed0);

            if (moveSpeed0 < creeper->moveSpeed_38)
            {
                moveSpeed   = moveSpeed0;
                moveSpeedTmp0 = creeper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime, Q12(6.0f));
                if (moveSpeed < moveSpeedTmp0)
                {
                    moveSpeed = moveSpeedTmp0;
                }
            }
            else
            {
                moveSpeed   = moveSpeed0;
                moveSpeedTmp0 = creeper->moveSpeed_38 + Q12_MULT_PRECISE(g_DeltaTime, Q12(6.0f));
                if (moveSpeed >= moveSpeedTmp0)
                {
                    moveSpeed = moveSpeedTmp0;
                }
            }
            creeper->moveSpeed_38 = moveSpeed;
        }

        if (TIMESTEP_ANGLE(1, 2) < ABS(func_8005BF38((Math_AngleBetweenPositionsGet(creeper->position_18, playerChara.position_18) - creeper->rotation_24.vy))))
        {
            if ((func_8005BF38((Math_AngleBetweenPositionsGet(creeper->position_18, playerChara.position_18) - creeper->rotation_24.vy)) << 16) > 0)
            {
                creeper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12(0.5f));
            }
            else
            {
                creeper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12(0.5f));
            }
        }
        else
        {
            creeper->rotation_24.vy = Math_AngleBetweenPositionsGet(creeper->position_18, playerChara.position_18);
        }

        creeper->field_44.field_0 = 1;
        return;
    }

    Chara_MoveSpeedUpdate3(creeper, Q12(2.0f), Q12(0.0f));

    if (ANIM_TIME_RANGE_CHECK(creeper->model_0.anim_4.time_4, 9, 10))
    {
        creeperPos     = creeper->position_18;
        creeperPos.vy += creeper->field_C8.field_8;

        func_8008A0E4(1, WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Multitap),
                      creeper, &creeperPos, &playerChara, creeper->rotation_24.vy,
                      ratan2(Q12(0.4f), (playerChara.position_18.vy + playerChara.field_C8.field_2) - (creeper->position_18.vy + creeper->field_C8.field_2)));

        if (!(creeperProps.flags_E8 & CreeperFlag_0))
        {
            func_8005DC1C(Sfx_Unk1424, &creeper->position_18, Q8(0.5f), 0);
        }

        creeperProps.flags_E8 |= CreeperFlag_0;

        // Alert other Creepers.
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
        {
            if (creeper->model_0.charaId_0 == Chara_Creeper &&
                !Math_Distance2dCheck(&creeper->position_18, &g_SysWork.npcs_1A0[i].position_18, Q12(16.0f)))
            {
                g_SysWork.npcs_1A0[i].properties_E4.creeper.flags_E8 |= CreeperFlag_Alerted;
            }
        }
    }
    else if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_13)
    {
        g_SysWork.field_2284[3]   &= ~(1 << 1);
        creeper->model_0.controlState_2   = CreeperControl_2;
        creeperProps.timer_F0      = Q12(0.0f);
        creeperProps.rotationY_108 = Chara_HeadingAngleGet(creeper, Q12(4.8f),
                                                           playerChara.position_18.vx, playerChara.position_18.vz,
                                                           Q12_ANGLE(360.0f), false);
        creeper->field_44.field_0   = 0;
    }

    #undef playerChara
}

void Ai_Creeper_Control_4(s_SubCharacter* creeper)
{
    q19_12 dist;

    if (creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_7, true))
    {
        if (creeper->rotation_24.vy != func_8005BF38(creeper->headingAngle_3C + Q12_ANGLE(180.0f)))
        {
            if (func_8005BF38((creeper->headingAngle_3C + Q12_ANGLE(180.0f)) - creeper->rotation_24.vy) > Q12_ANGLE(0.0f))
            {
                creeper->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
            }
            else
            {
                creeper->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
            }
        }

        if (ANIM_TIME_RANGE_CHECK(creeper->model_0.anim_4.time_4, 50, 59))
        {
            dist = Q12_MULT_PRECISE(CREEPER_ANIM_INFOS[creeper->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime) / 9;
        }
        else
        {
            q19_12 baseDist = Q12_MULT_PRECISE(CREEPER_ANIM_INFOS[creeper->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime) * Q12(0.1f);
            dist            = baseDist / Q12(4.0f);
        }

        creeperProps.offsetX_EC = Q12_MULT(dist, Math_Sin(creeper->rotation_24.vy + Q12_ANGLE(180.0f)));
        creeperProps.offsetZ_EE = Q12_MULT(dist, Math_Cos(creeper->rotation_24.vy + Q12_ANGLE(180.0f)));
    }

    if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_3  ||
        ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_4  ||
        ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_14 ||
        ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_15)
    {
        creeper->model_0.controlState_2 = CreeperControl_5;
    }
}

void Ai_Creeper_Control_5(s_SubCharacter* creeper)
{
    creeper->flags_3E &= ~CharaFlag_Unk2;

    if (creeper->health_B0 == Q12(0.0f) && Chara_NpcIdxGet(creeper) != g_SysWork.targetNpcIdx_2353)
    {
        creeper->health_B0  = NO_VALUE;
        creeper->field_E1_0 = 0;
    }

    //if (creeper->moveSpeed_38 == Q12(0.0f) && !(creeper->properties_E4.creeper.flags_E8 & (CreeperFlag_3 | CreeperFlag_4))) // TODO: Doesn't match?
    if (creeper->moveSpeed_38 == Q12(0.0f) && !(creeper->properties_E4.player.afkTimer_E8 & 0xC))
    {
        creeper->properties_E4.creeper.flags_E8 |= CreeperFlag_3;
        Savegame_EnemyStateUpdate(creeper);

        if (creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_14, true))
        {
            func_800622B8(3, creeper, ANIM_STATUS(CreeperAnim_5, false), 5);
        }
        else
        {
            func_800622B8(3, creeper, ANIM_STATUS(CreeperAnim_5, true), 5);
        }
    }
}

void sharedFunc_800D983C_1_s02(s_SubCharacter* creeper)
{
    s_800C4590 unused;

    creeper->fallSpeed_34 += g_GravitySpeed >> 2;

    if (creeperProps.flags_E8 & CreeperFlag_1)
    {
        Chara_MoveSpeedUpdate(creeper, Q12(4.0f));
    }
    else
    {
        creeper->headingAngle_3C = creeper->rotation_24.vy;
    }

    func_8005CB20(creeper, &unused, creeperProps.offsetX_EC, creeperProps.offsetZ_EE);
    creeperProps.offsetZ_EE = Q12(0.0f);
    creeperProps.offsetX_EC = Q12(0.0f);

    if (creeper->fallSpeed_34 != Q12(0.0f))
    {
        creeperProps.flags_E8 |= CreeperFlag_2;
    }
    else
    {
        creeperProps.flags_E8 &= ~CreeperFlag_2;
    }

    creeper->rotation_24.vy = func_8005BF38(creeper->rotation_24.vy);
}

void sharedFunc_800D9960_1_s02(s_SubCharacter* creeper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    Math_MatrixTransform(&creeper->position_18, &creeper->rotation_24, coords);

    animInfo = &CREEPER_ANIM_INFOS[creeper->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&creeper->model_0, anmHdr, coords, animInfo);
}

extern s_Keyframe sharedData_800E0F78_1_s02[];
extern s_Keyframe sharedData_800E0FC8_1_s02;
extern s_Keyframe sharedData_800E0FDC_1_s02;
extern s_Keyframe sharedData_800E0FF0_1_s02;
extern s_Keyframe sharedData_800E1004_1_s02[]; // Creeper keyframe data?
extern s_Keyframe sharedData_800E10CC_1_s02;
extern s_Keyframe sharedData_800E10E0_1_s02[];
extern s_Keyframe sharedData_800E1158_1_s02;
extern s_Keyframe sharedData_800E116C_1_s02;
extern s_Keyframe sharedData_800E1180_1_s02;
extern s_Keyframe sharedData_800E1194_1_s02;
extern s_Keyframe sharedData_800E11A8_1_s02;
extern s_Keyframe sharedData_800E11BC_1_s02;

#define CopyData(arg0, data)                  \
{                                             \
    s32 __temp;                               \
    s32 __temp2;                              \
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
    __temp2                  = data.field_A;  \
    arg0->field_D4.field_2   = __temp2;       \
}

void sharedFunc_800D99D0_1_s02(s_SubCharacter* creaper)
{
    s32 keyframeIdx0;
    s32 keyframeIdx1;
    s32 keyframeIdx2;
    s32 keyframeIdx3;

    switch (creaper->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(CreeperAnim_1, false):
            func_80070400(creaper, &sharedData_800E0FC8_1_s02, &sharedData_800E0F78_1_s02[0]);
            break;

        case ANIM_STATUS(CreeperAnim_1, true):
            creaper->properties_E4.creeper.animStatus_10A = ANIM_STATUS(CreeperAnim_1, true);
            keyframeIdx0 = FP_FROM(creaper->model_0.anim_4.time_4, Q12_SHIFT);
            keyframeIdx1 = keyframeIdx0 + 1;
            func_80070400(creaper, &sharedData_800E0F78_1_s02[keyframeIdx0], &sharedData_800E0F78_1_s02[keyframeIdx1]);
            break;

        case ANIM_STATUS(CreeperAnim_2, false):
            func_80070400(creaper, &sharedData_800E11A8_1_s02, &sharedData_800E0FC8_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_2, true):
            CopyData(creaper, sharedData_800E0FC8_1_s02);
            creaper->field_C8.field_8 = -655;
            break;

        case ANIM_STATUS(CreeperAnim_3, false):
            if (creaper->properties_E4.creeper.animStatus_10A == ANIM_STATUS(CreeperAnim_16, true))
            {
                func_80070400(creaper, &sharedData_800E10CC_1_s02, &sharedData_800E0FDC_1_s02);
            }
            else
            {
                func_80070400(creaper, &sharedData_800E116C_1_s02, &sharedData_800E0FDC_1_s02);
            }
            break;

        case ANIM_STATUS(CreeperAnim_3, true):
        case ANIM_STATUS(CreeperAnim_14, false):
        case ANIM_STATUS(CreeperAnim_14, true):
            CopyData(creaper, sharedData_800E0FDC_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_4, false):
            if (creaper->properties_E4.creeper.animStatus_10A == ANIM_STATUS(CreeperAnim_17, true))
            {
                func_80070400(creaper, &sharedData_800E1158_1_s02, &sharedData_800E0FF0_1_s02);
            }
            else
            {
                func_80070400(creaper, &sharedData_800E1180_1_s02, &sharedData_800E0FF0_1_s02);
            }
            break;

        case ANIM_STATUS(CreeperAnim_4, true):
        case ANIM_STATUS(CreeperAnim_15, false):
        case ANIM_STATUS(CreeperAnim_15, true):
            CopyData(creaper, sharedData_800E0FF0_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_7, false):
        case ANIM_STATUS(CreeperAnim_16, false):
            CopyData(creaper, sharedData_800E1004_1_s02[0]);
            break;

        case ANIM_STATUS(CreeperAnim_7, true):
        case ANIM_STATUS(CreeperAnim_16, true):
            keyframeIdx2 = FP_FROM(creaper->model_0.anim_4.time_4, Q12_SHIFT) - 50;
            keyframeIdx3 = keyframeIdx2 - !(keyframeIdx2 < 10) - !(keyframeIdx2 < 11);

            keyframeIdx0 = keyframeIdx3 - !(keyframeIdx2 < 12);
            keyframeIdx1 = (keyframeIdx2 + 1) - !(keyframeIdx2 < 9) - !(keyframeIdx2 < 10) - !(keyframeIdx2 < 11);
            func_80070400(creaper, &sharedData_800E1004_1_s02[keyframeIdx0], &sharedData_800E1004_1_s02[keyframeIdx1]);
            break;

        case ANIM_STATUS(CreeperAnim_8, false):
        case ANIM_STATUS(CreeperAnim_17, false):
            CopyData(creaper, sharedData_800E10E0_1_s02[0]);
            break;

        case ANIM_STATUS(CreeperAnim_8, true):
        case ANIM_STATUS(CreeperAnim_17, true):
            keyframeIdx0 = FP_FROM(creaper->model_0.anim_4.time_4, Q12_SHIFT) - 64;
            keyframeIdx1 = keyframeIdx0 + 1;
            func_80070400(creaper, &sharedData_800E10E0_1_s02[keyframeIdx0], &sharedData_800E10E0_1_s02[keyframeIdx1]);
            break;

        case ANIM_STATUS(CreeperAnim_9, false):
            func_80070400(creaper, &sharedData_800E10CC_1_s02, &sharedData_800E116C_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_9, true):
            CopyData(creaper, sharedData_800E116C_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_10, false):
            func_80070400(creaper, &sharedData_800E1158_1_s02, &sharedData_800E1180_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_10, true):
            CopyData(creaper, sharedData_800E1180_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_11, false):
            func_80070400(creaper, &sharedData_800E11BC_1_s02, &sharedData_800E1194_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_11, true):
            creaper->properties_E4.creeper.animStatus_10A = ANIM_STATUS(CreeperAnim_11, true);
            CopyData(creaper, sharedData_800E1194_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_12, false):
            func_80070400(creaper, &sharedData_800E11BC_1_s02, &sharedData_800E11A8_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_12, true):
            CopyData(creaper, sharedData_800E11A8_1_s02);
            break;

        case ANIM_STATUS(CreeperAnim_13, false):
            if (creaper->properties_E4.creeper.animStatus_10A == ANIM_STATUS(CreeperAnim_11, true))
            {
                func_80070400(creaper, &sharedData_800E1194_1_s02, &sharedData_800E11BC_1_s02);
            }
            else if (creaper->properties_E4.creeper.animStatus_10A == ANIM_STATUS(CreeperAnim_1, true))
            {
                func_80070400(creaper, &sharedData_800E0F78_1_s02[0], &sharedData_800E11BC_1_s02);
            }
            else
            {
                CopyData(creaper, sharedData_800E11BC_1_s02);
            }
            break;

        case ANIM_STATUS(CreeperAnim_13, true):
            CopyData(creaper, sharedData_800E11BC_1_s02);
            break;
    }

    func_8005C814(&creaper->field_D8, creaper);
}

#undef creeperProps
