#include "bodyprog/bodyprog.h"
#include "bodyprog/math/math.h"
#include "bodyprog/player_logic.h"
#include "main/rng.h"
#include "maps/shared.h"
#include "maps/characters/split_head.h"

#define splitHeadProps splitHead->properties_E4.splitHead

void Ai_SplitHead_Update(s_SubCharacter* splitHead, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    sharedData_800D8610_1_s05 = coords;

    // Initialize.
    if (splitHead->model_0.controlState_2 == SplitHeadControl_None)
    {
        Ai_SplitHead_Init(splitHead);
    }

    if (g_DeltaTime != Q12(0.0f))
    {
        Ai_SplitHead_DamageTake(splitHead);
        Ai_SplitHead_ControlUpdate(splitHead);
        sharedFunc_800D267C_1_s05(splitHead);
        sharedFunc_800D3AFC_1_s05(splitHead);
    }

    sharedFunc_800D274C_1_s05(splitHead, anmHdr);

    if (g_DeltaTime != Q12(0.0f))
    {
        sharedFunc_800D2D74_1_s05(splitHead);
        sharedFunc_800D3B30_1_s05(splitHead);
    }

    sharedFunc_800D4070_1_s05(splitHead);
    sharedFunc_800CF990_1_s05(splitHead);
}

void Ai_SplitHead_Init(s_SubCharacter* splitHead)
{
    s32 i;

    splitHead->health_B0              = 25500; // TODO: Split Head health isn't stored as Q12?
    splitHeadProps.flags_E8           = SplitHeadFlag_None;
    splitHead->model_0.anim_4.alpha_A = Q12(0.0f);
    splitHead->moveSpeed_38           = Q12(0.0f);
    splitHead->headingAngle_3C        = splitHead->rotation_24.vy;
    splitHead->field_E1_0             = 4;
    Chara_PropertiesClear(splitHead);

    splitHead->model_0.controlState_2 = SplitHeadControl_8;
    Character_AnimSet(splitHead, ANIM_STATUS(SplitHeadAnim_10, true), 162);
    ModelAnim_AnimInfoSet(&splitHead->model_0.anim_4, SPLIT_HEAD_ANIM_INFOS);

    sharedData_800D8614_1_s05 = Q12(0.0f);
    sharedData_800D8616_1_s05 = Q12(0.0f);

    Chara_DamageClear(splitHead);

    splitHeadProps.field_EA = 196;
    splitHead->flags_3E    |= CharaFlag_Unk9 | CharaFlag_Unk3;
}

void sharedFunc_800CF990_1_s05(s_SubCharacter* splitHead)
{
    s32     keyframeIdx;
    s32     sfxVol;
    s32     sfxPitch;
    VECTOR3 sfxPos;

    keyframeIdx = FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT);
    sfxVol      = ((FP_TO(sharedData_800D5884_1_s05, Q12_SHIFT) / Q12(24.0f)) >> 7) + 96;                          // @hack `(/ Q12(24.0f)) >> 7` should be same as `/ 0xC00000`?
    sfxPitch    = ((FP_TO(sharedData_800D5884_1_s05, Q12_SHIFT) / Q12(24.0f)) >> 6) - 64 + Rng_GenerateUInt(0, 7); // @hack `(/ Q12(24.0f)) >> 6` should be same as `/ 0x600000`?

    if ((keyframeIdx >= 147 && keyframeIdx < 162) ||
        (keyframeIdx >= 187 && keyframeIdx < 201))
    {
        if (splitHeadProps.field_108[0] == 0)
        {
            sfxPos.vx = splitHead->position_18.vx + FP_FROM(Math_Sin(splitHead->rotation_24.vy + Q12_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splitHead->position_18.vy;
            sfxPos.vz = splitHead->position_18.vz + FP_FROM(Math_Cos(splitHead->rotation_24.vy + Q12_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);

            func_8005DD44(Sfx_Unk1472, &sfxPos, sfxVol, sfxPitch);
            splitHeadProps.field_108[0]++;
        }
    }
    else
    {
        splitHeadProps.field_108[0] = 0;
    }

    if ((keyframeIdx >= 132 && keyframeIdx < 148) ||
        keyframeIdx == 161 ||
        (keyframeIdx >= 172 && keyframeIdx < 185) ||
        (keyframeIdx >= 200 && keyframeIdx < 202))
    {
        if (splitHeadProps.field_108[1] == 0)
        {
            sfxPos.vx = splitHead->position_18.vx + FP_FROM(Math_Sin(splitHead->rotation_24.vy + Q12_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splitHead->position_18.vy;
            sfxPos.vz = splitHead->position_18.vz + FP_FROM(Math_Cos(splitHead->rotation_24.vy + Q12_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            splitHeadProps.field_108[1]++;
        }
    }
    else
    {
        splitHeadProps.field_108[1] = 0;
    }

    if ((keyframeIdx >= 132 && keyframeIdx < 147) ||
        (keyframeIdx >= 160 && keyframeIdx < 162) ||
        (keyframeIdx >= 172 && keyframeIdx < 187) ||
        (keyframeIdx >= 199 && keyframeIdx < 202))
    {
        if (splitHeadProps.field_108[2] == 0)
        {
            sfxPos.vx = splitHead->position_18.vx + FP_FROM(Math_Sin(splitHead->rotation_24.vy - Q12_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splitHead->position_18.vy;
            sfxPos.vz = splitHead->position_18.vz + FP_FROM(Math_Cos(splitHead->rotation_24.vy - Q12_ANGLE(45.0f)) * Q12(1.2f), Q12_SHIFT);

            func_8005DD44(Sfx_Unk1472, &sfxPos, sfxVol, sfxPitch);
            splitHeadProps.field_108[2]++;
        }
    }
    else
    {
        splitHeadProps.field_108[2] = 0;
    }

    if ((keyframeIdx >= 146 && keyframeIdx < 161) ||
        (keyframeIdx >= 186 && keyframeIdx < 200))
    {
        if ((u8)splitHeadProps.field_108[3] == 0)
        {
            sfxPos.vx = splitHead->position_18.vx + FP_FROM(Math_Sin(splitHead->rotation_24.vy - Q12_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            sfxPos.vy = splitHead->position_18.vy;
            sfxPos.vz = splitHead->position_18.vz + FP_FROM(Math_Cos(splitHead->rotation_24.vy - Q12_ANGLE(135.0f)) * Q12(1.2f), Q12_SHIFT);
            splitHeadProps.field_108[3]++;
        }
    }
    else
    {
        splitHeadProps.field_108[3] = 0;
    }

    if (splitHeadProps.field_10C == Q12(0.0f))
    {
        if (splitHeadProps.flags_E8 & SplitHeadFlag_8)
        {
            func_8005DC1C(Sfx_Unk1422, &splitHead->position_18, Q8_CLAMPED(0.5f), 0);
            splitHeadProps.field_10C = Rng_GenerateInt(Q12(3.0f), Q12(5.0f) - 1);
        }
        else if (splitHeadProps.flags_E8 & SplitHeadFlag_7)
        {
            func_8005DC1C(Sfx_Unk1474, &splitHead->position_18, Q8_CLAMPED(0.5f), 0);
            splitHeadProps.field_10C = Rng_GenerateInt(Q12(1.5f), Q12(2.5f) - 1);
        }
    }
    else
    {
        splitHeadProps.field_10C -= g_DeltaTime;
        if (splitHeadProps.field_10C < Q12(0.0f))
        {
            splitHeadProps.field_10C = Q12(0.0f);
        }
    }

    splitHeadProps.flags_E8 &= ~(SplitHeadFlag_8 | SplitHeadFlag_7);
}

void Ai_SplitHead_DamageTake(s_SubCharacter* splitHead)
{
    u8  isPlayerDead;
    s32 damageAmt;
    s32 newHealth;

    // `Player_DisableDamage` sets first arg to `g_Player_IsDead` value, which gets set to 1 by `Player_ReceiveDamage` when player health is 0 or below.
    // Second arg is used to set `g_Player_DisableDamage`.
    // `isPlayerDead` gets checked below. If it's set, Split Head health isn't allowed to go below 0.
    // Presumably this is used to prevent both player + Split Head from dying at the same moment?
    Player_DisableDamage(&isPlayerDead, splitHead->health_B0 == 0);

    // Return early if no damage or health is already 0.
    if (splitHead->damage_B4.amount_C == Q12(0.0f) || splitHead->health_B0 == 0) // TODO: Split Head health isn't Q12 going off checks below?
    {
        return;
    }

    damageAmt = FP_FROM(splitHead->damage_B4.amount_C, Q12_SHIFT);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        damageAmt >>= 1;
    }

    if (damageAmt == 0)
    {
        damageAmt = 1;
    }

    if (splitHeadProps.flags_E8 & SplitHeadFlag_0)
    {
        // TODO: Odd `WEAPON_ATTACK` value. Input type 3 doesn't exist.
        if (g_SavegamePtr->gameDifficulty_260 != GameDifficulty_Hard &&
            g_SysWork.playerCombat_38.weaponAttack_F == WEAPON_ATTACK(EquippedWeaponId_Hammer, 3))
        {
            damageAmt <<= 5;
        }
        else
        {
            damageAmt <<= 4;
        }
    }

    newHealth = splitHead->health_B0 - damageAmt;
    if (isPlayerDead)
    {
        if (newHealth <= 0)
        {
            newHealth = 1;
        }
    }
    else if (newHealth < 0)
    {
        newHealth = 0;
    }
    splitHead->health_B0 = newHealth;

    if (splitHead->health_B0 < 24000 && !(splitHeadProps.flags_E8 & SplitHeadFlag_4))
    {
        splitHead->model_0.controlState_2 = SplitHeadControl_4;
        splitHeadProps.flags_E8   |= SplitHeadFlag_4;
    }
    else if (splitHead->health_B0 == Q12(0.0f))
    {
        if (ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) == SplitHeadAnim_2)
        {
            splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_8, false);
        }
        else if (splitHead->moveSpeed_38 > Q12(0.0f))
        {
            splitHeadProps.flags_E8 |= SplitHeadFlag_5;
        }
        else if (splitHead->moveSpeed_38 < Q12(0.0f))
        {
            splitHeadProps.flags_E8 &= ~SplitHeadFlag_5;
        }

        splitHead->model_0.controlState_2 = SplitHeadControl_6;
    }
    else if (splitHeadProps.flags_E8 & SplitHeadFlag_0)
    {
        splitHeadProps.flags_E8 |= SplitHeadFlag_6 | SplitHeadFlag_7;
    }

    Chara_DamageClear(splitHead);

    Player_DisableDamage(&isPlayerDead, splitHead->health_B0 == 0);
}

void Ai_SplitHead_ControlUpdate(s_SubCharacter* splitHead)
{
    extern void (*g_Ai_SplitHead_ControlFuncs[])(s_SubCharacter* splitHead); // TODO: Add func table to this func.

    // Handle control state.
    splitHeadProps.flags_E8 &= ~SplitHeadFlag_3;
    g_Ai_SplitHead_ControlFuncs[splitHead->model_0.controlState_2](splitHead);

    if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_11, true))
    {
        splitHeadProps.animTime_F8 = splitHead->model_0.anim_4.time_4;
    }
    else if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_11, false))
    {
        splitHeadProps.animTime_F8 = Q12(201.0f);
    }
}

void Ai_SplitHead_Control_1(s_SubCharacter* splitHead)
{
    VECTOR unkPos;
    q3_12  angleDeltaToPlayer;
    q19_12 distToPlayer;

    distToPlayer       = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - splitHead->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - splitHead->position_18.vz);
    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       splitHead->rotation_24.vy);

    if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_11, true))
    {
        if (distToPlayer > Q12(3.5f))
        {
            Chara_MoveSpeedUpdate3(splitHead, Q12(2.4f), Q12(2.4f));
        }
        else
        {
            if (ABS(angleDeltaToPlayer) > Q12_ANGLE(90.0f) || distToPlayer > Q12(5.0f))
            {
                splitHead->model_0.controlState_2 = SplitHeadControl_5;
            }
            else
            {
                splitHeadProps.flags_E8 |= SplitHeadFlag_3;
                Chara_MoveSpeedUpdate(splitHead, Q12(4.8f));

                if (sharedFunc_800D4530_1_s05(splitHead) != false)
                {
                    splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_2, false);
                    func_8005DC1C(Sfx_Unk1475, &splitHead->position_18, Q8(0.5f), 0);
                }
            }
        }

        if (TIMESTEP_ANGLE(1, 4) < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
            {
                splitHead->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(45.0f));
            }
            else
            {
                splitHead->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(45.0f));
            }
        }
        else
        {
            splitHead->rotation_24.vy = Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
    }
    else if (ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) == SplitHeadAnim_4)
    {
        Chara_MoveSpeedUpdate(splitHead, Q12(4.8f));
    }
    else if (ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) == SplitHeadAnim_10)
    {
        Chara_MoveSpeedUpdate(splitHead, Q12(4.8f));

        if (splitHeadProps.flags_E8 & SplitHeadFlag_6)
        {
            splitHeadProps.flags_E8 &= ~SplitHeadFlag_6;

            if (!(Rng_Rand16() & 0x3))
            {
                splitHead->model_0.controlState_2  = SplitHeadControl_7;
                splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_9, false);
            }
            else
            {
                splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_4, false);
            }
        }
        else if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_10, true) && !Rng_GenerateUInt(0, 31))
        {
            splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_11, false);
            splitHead->model_0.controlState_2  = SplitHeadControl_5;
        }
    }
    else if (splitHeadProps.flags_E8 & SplitHeadFlag_1)
    {
        if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_2, true))
        {
            splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_14, false);
        }

        Chara_MoveSpeedUpdate3(splitHead, Q12(1.2f), Q12(0.0f));

        if (TIMESTEP_ANGLE(3, 4) < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
            {
                splitHead->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(15.0f));
            }
            else
            {
                splitHead->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(15.0f));
            }
        }
        else
        {
            splitHead->rotation_24.vy = Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }

        if (FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) == 35)
        {
            unkPos.vx = Rng_AddGeneratedUInt(g_SysWork.playerWork_4C.player_0.position_18.vx, Q12(-0.25f), Q12(0.0f) - 1);
            unkPos.vy = (g_SysWork.playerWork_4C.player_0.position_18.vy - Rng_GenerateUInt(0, Q12(0.5f) - 1)) - Q12(1.0f); // TODO: Doesn't match with `Rng_AddGeneratedUInt`?
            unkPos.vz = Rng_AddGeneratedUInt(g_SysWork.playerWork_4C.player_0.position_18.vz, Q12(-0.25f), Q12(0.0f) - 1);
            func_8005F6B0(&g_SysWork.playerWork_4C.player_0, &unkPos, 2, 7);
        }
    }
    else
    {
        if (distToPlayer < Q12(2.8f))
        {
            Chara_MoveSpeedUpdate(splitHead, Q12(1.2f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(splitHead, Q12(1.2f), Q12(0.6f));
        }

        if (TIMESTEP_ANGLE(3, 4) < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
            {
                splitHead->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(15.0f));
            }
            else
            {
                splitHead->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(15.0f));
            }
        }
        else
        {
            splitHead->rotation_24.vy = Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
    }
}

void Ai_SplitHead_Control_2(s_SubCharacter* splitHead)
{
    s_RayData ray;
    VECTOR3   sp30;
    q3_12     angleToPlayer2;
    q3_12     angleDeltaToPlayer;
    q3_12     angle1;
    q3_12     angle;
    q3_12     angleToPlayer;
    q19_12    distToPlayer;
    q19_12    distMax;
    q19_12    activeDistMax;
    s32       i;
    s32       angleMult;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - splitHead->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - splitHead->position_18.vz);

    if (splitHeadProps.timer_F2 > Q12(0.6f))
    {
        angle = Q12_ANGLE(0.0f);
        angleToPlayer = Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18);

        if (splitHeadProps.flags_E8 & SplitHeadFlag_2)
        {
            angleMult                                               = 1;
            splitHeadProps.flags_E8 &= ~SplitHeadFlag_2;
        }
        else
        {
            angleMult                                               = NO_VALUE;
            splitHeadProps.flags_E8 |= SplitHeadFlag_2;
        }

        for (i = 0; i < 16; i++)
        {
            if (i != 0 && i != 15)
            {
                angleToPlayer2 = Rng_GenerateUInt(Q12_ANGLE(-5.7f), Q12_ANGLE(5.7f) - 1);
                if (i & 0x1)
                {
                    angle1 = angleToPlayer2 * angleMult;
                }
                else
                {
                    angle1 = angleToPlayer2 * -angleMult;
                }
            }
            else
            {
                angle1 = Q12_ANGLE(0.0f);
            }

            if (angle < Q12_ANGLE(90.0f))
            {
                distMax = Q12(1.8f);
            }
            else
            {
                distMax = FP_FROM((distToPlayer * Math_Cos(angle)) + (Math_Sin(angle) * Q12(1.8f)), Q12_SHIFT);
            }

            if (distToPlayer < distMax)
            {
                activeDistMax = distMax;
            }
            else
            {
                activeDistMax = distToPlayer;
            }
            distMax = activeDistMax;

            sp30.vx = Q12_MULT(distMax, Math_Sin((angleToPlayer + angle) + angle1));
            sp30.vy = Q12(0.0f);
            sp30.vz = Q12_MULT(distMax, Math_Cos((angleToPlayer + angle) + angle1));

            func_8006DB3C(&ray, &splitHead->position_18, &sp30, splitHead);

            if (!ray.hasHit_0 || ray.chara_10 != NULL)
            {
                splitHeadProps.angle_F0 = angle1 + (angleToPlayer + angle);
                break;
            }

            if (!(i & 1))
            {
                angle += Q12_ANGLE(22.5f);
            }
        }

        if (i != 16)
        {
            splitHeadProps.timer_F2 = Q12(0.0f);
        }
    }

    splitHeadProps.timer_F2 += g_DeltaTime;

    angleToPlayer = func_8005BF38((splitHeadProps.angle_F0 - splitHead->rotation_24.vy));
    if (TIMESTEP_ANGLE(3, 3) < ABS(angleToPlayer))
    {
        if (angleToPlayer > Q12_ANGLE(0.0f))
        {
            splitHead->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
        }
        else
        {
            splitHead->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
        }
    }
    else
    {
        splitHead->rotation_24.vy = splitHeadProps.angle_F0;
    }

    angleToPlayer      = ABS(func_8005BF38(splitHeadProps.angle_F0 - splitHead->rotation_24.vy));
    angleDeltaToPlayer = ABS(func_8005BF38(Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                           splitHead->rotation_24.vy));

    if (ABS(angleToPlayer - angleDeltaToPlayer) < Q12_ANGLE(15.0f))
    {
        if (distToPlayer <= Q12(5.75f) && angleToPlayer < Q12_ANGLE(60.0f))
        {
            Chara_MoveSpeedUpdate3(splitHead, Q12(0.8f), Q12(-1.2f));
        }
        else if ((distToPlayer <= Q12(5.75f) && angleToPlayer > Q12_ANGLE(60.0f)) ||
                 (distToPlayer >  Q12(5.75f) && angleToPlayer > Q12_ANGLE(90.0f)))
        {
            Chara_MoveSpeedUpdate(splitHead, Q12(0.8f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(splitHead, Q12(0.8f), Q12(1.2f));
        }
    }
    else
    {
        if (angleToPlayer < Q12_ANGLE(30.0f))
        {
            Chara_MoveSpeedUpdate3(splitHead, Q12(0.8f), Q12(1.2f));
        }
        else
        {
            Chara_MoveSpeedUpdate(splitHead, Q12(0.8f));
        }
    }

    angleToPlayer2 = Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18);
    sp30.vx = Q12_MULT(distToPlayer, Math_Sin(angleToPlayer2));
    sp30.vy = Q12(0.0f);
    sp30.vz = Q12_MULT(distToPlayer, Math_Cos(angleToPlayer2));

    func_8006DB3C(&ray, &splitHead->position_18, &sp30, splitHead);

    if (distToPlayer < Q12(6.4f) &&
        (angleDeltaToPlayer < Q12_ANGLE(7.5f) || distToPlayer > Q12(3.2f) && angleDeltaToPlayer < Q12_ANGLE(15.0f)) &&
        (!ray.hasHit_0 || ray.chara_10 != NULL))
    {
        splitHead->model_0.controlState_2 = SplitHeadControl_3;
    }

    if (!Rng_GenerateUInt(0, 127))
    {
        splitHeadProps.flags_E8 |= SplitHeadFlag_8;
    }

    if (!Rng_GenerateUInt(0, 63))
    {
        splitHeadProps.flags_E8 |= SplitHeadFlag_7;
    }
}

void Ai_SplitHead_Control_3(s_SubCharacter* splitHead)
{
    q3_12  angleDeltaToPlayer;
    q19_12 distToPlayer;

    distToPlayer       = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - splitHead->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - splitHead->position_18.vz);
    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       splitHead->rotation_24.vy);

    if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_11, true))
    {
        if (distToPlayer > Q12(4.0f))
        {
            Chara_MoveSpeedUpdate3(splitHead, Q12(4.0f), Q12(2.4f));
        }
        else
        {
            if (ABS(angleDeltaToPlayer) > Q12_ANGLE(90.0f) ||
                distToPlayer > Q12(8.0f) ||
                (distToPlayer < Q12(3.2f) && ABS(angleDeltaToPlayer) > Q12_ANGLE(22.5f)))
            {
                splitHead->model_0.controlState_2 = SplitHeadControl_2;
            }
            else
            {
                splitHeadProps.flags_E8 |= SplitHeadFlag_3;
                Chara_MoveSpeedUpdate(splitHead, Q12(16.0f));

                if (sharedFunc_800D4530_1_s05(splitHead))
                {
                    splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_3, false);
                    func_8005DC1C(Sfx_Unk1471, &splitHead->position_18, Q8(0.5f), 0);
                }
            }
        }

        if (TIMESTEP_ANGLE(3, 3) < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
            {
                splitHead->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
            }
            else
            {
                splitHead->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
            }
        }
        else
        {
            splitHead->rotation_24.vy = Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
    }
    else if (ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) == SplitHeadAnim_10)
    {
        Chara_MoveSpeedUpdate(splitHead, 0x1998); // TODO

        sharedData_800D5A8C_1_s05 += g_DeltaTime;

        if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_10, true) &&
            (!Rng_GenerateUInt(0, 63) || sharedData_800D5A8C_1_s05 > Q12(4.0f)))
        {
            sharedData_800D5A8C_1_s05      = 0;
            splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_11, false);
            splitHead->model_0.controlState_2  = SplitHeadControl_2;
        }
    }
    else
    {
        if (distToPlayer < Q12(6.4f))
        {
            Chara_MoveSpeedUpdate(splitHead, Q12(4.0f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(splitHead, Q12(4.0f), Q12(2.4f));
        }

        if (TIMESTEP_ANGLE(3, 4) < ABS(angleDeltaToPlayer))
        {
            if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
            {
                splitHead->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(15.0f));
            }
            else
            {
                splitHead->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(15.0f));
            }
        }
        else
        {
            splitHead->rotation_24.vy = Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
    }
}

void Ai_SplitHead_Control_4(s_SubCharacter* splitHead)
{
    s32 vol;
    s32 timer0;
    s16 timer1;
    s16 timer1_div6;

    Chara_MoveSpeedUpdate(splitHead, Q12(1.5997f));
    switch (splitHead->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(SplitHeadAnim_11, false):
        case ANIM_STATUS(SplitHeadAnim_11, true):
            splitHeadProps.flags_E8 |= SplitHeadFlag_3;

            if (!sharedFunc_800D4530_1_s05(splitHead))
            {
                break;
            }

        case ANIM_STATUS(SplitHeadAnim_10, true):
            splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_1, false);
            SD_Call(Sfx_Unk1477);
            break;

        case ANIM_STATUS(SplitHeadAnim_1, false):
        case ANIM_STATUS(SplitHeadAnim_1, true):
            timer0      = splitHeadProps.timer_F4;
            timer1      = sharedData_800D5880_1_s05;
            timer1_div6 = timer1 / 6;

            if (timer0 < timer1_div6)
            {
                vol = (timer0 << 7) / timer1_div6;
            }
            else if (((timer1 * 5) / 6) < timer0)
            {
                vol = ((sharedData_800D5880_1_s05 - timer0) << 7) / timer1_div6;
            }
            else
            {
                vol = 0x80;
            }

            func_8005DE0C(Sfx_Unk1477, &splitHead->position_18, vol, Q12(16.0f), 0);

            if (splitHeadProps.timer_F4 > sharedData_800D5880_1_s05)
            {
                sharedData_800D5880_1_s05                   = Q12(3.8f);
                splitHead->model_0.controlState_2           = SplitHeadControl_5;
                splitHeadProps.timer_F4 = Q12(0.0f);
                splitHead->model_0.anim_4.status_0          = ANIM_STATUS(SplitHeadAnim_11, false);

                Sd_SfxStop(Sfx_Unk1477);
                break;
            }

            splitHeadProps.timer_F4 += g_DeltaTime;
            break;
    }
}

void Ai_SplitHead_Control_5(s_SubCharacter* splitHead)
{
    s_RayData ray;
    VECTOR3   sp30;
    q3_12     angle1;
    q3_12     angle2;
    q3_12     angle3;
    q3_12     angle;
    q3_12     angleToPlayer;
    q19_12    distToPlayer;
    q19_12    distMax;
    s32       i;
    s32       angleMult;
    q19_12    activeDistMax;

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - splitHead->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - splitHead->position_18.vz);

    if (splitHeadProps.timer_F2 > Q12(0.4f))
    {
        angle = Q12_ANGLE(0.0f);
        angleToPlayer = Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18);

        if (splitHeadProps.flags_E8 & SplitHeadFlag_2)
        {
            angleMult                                               = 1;
            splitHeadProps.flags_E8 &= ~SplitHeadFlag_2;
        }
        else
        {
            angleMult                                               = NO_VALUE;
            splitHeadProps.flags_E8 |= SplitHeadFlag_2;
        }

        for (i = 0; i < 16; i++)
        {
            if (i != 0 && i != 15)
            {
                angle1 = Rng_GenerateUInt(Q12_ANGLE(-5.7f), Q12_ANGLE(5.7f) - 1);
                if (i & 0x1)
                {
                    angle3 = angle1 * angleMult;
                }
                else
                {
                    angle3 = angle1 * -angleMult;
                }
            }
            else
            {
                angle3 = Q12_ANGLE(0.0f);
            }

            if (angle < Q12_ANGLE(90.0f))
            {
                distMax = Q12(2.0f);
            }
            else
            {
                distMax = FP_FROM((distToPlayer * Math_Cos(angle)) + (Math_Sin(angle) << 13), Q12_SHIFT);
            }

            if (distToPlayer < distMax)
            {
                activeDistMax = distMax;
            }
            else
            {
                activeDistMax = distToPlayer;
            }
            distMax = activeDistMax;

            sp30.vx = Q12_MULT(distMax, Math_Sin((angleToPlayer + angle) + angle3));
            sp30.vy = Q12(0.0f);
            sp30.vz = Q12_MULT(distMax, Math_Cos((angleToPlayer + angle) + angle3));

            func_8006DB3C(&ray, &splitHead->position_18, &sp30, splitHead);

            if (!ray.hasHit_0 || ray.chara_10 != NULL)
            {
                splitHeadProps.angle_F0 = angle3 + (angleToPlayer + angle);
                break;
            }

            if (!(i & 0x1))
            {
                angle += Q12_ANGLE(22.5f);
            }
        }

        if (i != 16)
        {
            splitHeadProps.timer_F2 = 0;
        }
    }

    splitHeadProps.timer_F2 += g_DeltaTime;

    angleToPlayer = func_8005BF38((splitHeadProps.angle_F0 - splitHead->rotation_24.vy));

    if (TIMESTEP_ANGLE(1, 4) < ABS(angleToPlayer))
    {
        if (angleToPlayer > Q12_ANGLE(0.0f))
        {
            splitHead->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(45.0f));
        }
        else
        {
            splitHead->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(45.0f));
        }
    }
    else
    {
        splitHead->rotation_24.vy = splitHeadProps.angle_F0;
    }

    angleToPlayer   = ABS(func_8005BF38(splitHeadProps.angle_F0 - splitHead->rotation_24.vy));
    angle2 = ABS(func_8005BF38(Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18) - splitHead->rotation_24.vy));

    if (ABS(angleToPlayer - angle2) < Q12_ANGLE(15.0f))
    {
        if (distToPlayer <= Q12(4.8f) && angle2 > Q12_ANGLE(3.75f) && angleToPlayer < Q12_ANGLE(60.0f))
        {
            Chara_MoveSpeedUpdate3(splitHead, Q12(2.4f), Q12(-2.4f));
        }
        else if ((distToPlayer <= Q12(4.8f) && angleToPlayer > Q12_ANGLE(60.0f)) ||
                 (distToPlayer >  Q12(4.8f) && angleToPlayer > Q12_ANGLE(90.0f)))
        {
            Chara_MoveSpeedUpdate(splitHead, Q12(2.4f));
        }
        else
        {
            Chara_MoveSpeedUpdate3(splitHead, Q12(2.4f), Q12(2.4f));
        }
    }
    else
    {
        if (angleToPlayer < Q12_ANGLE(30.0f))
        {
            Chara_MoveSpeedUpdate3(splitHead, Q12(2.4f), Q12(2.4f));
        }
        else
        {
            Chara_MoveSpeedUpdate(splitHead, Q12(2.4f));
        }
    }

    angle1 = Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18);

    sp30.vx = Q12_MULT(distToPlayer, Math_Sin(angle1));
    sp30.vy = Q12(0.0f);
    sp30.vz = Q12_MULT(distToPlayer, Math_Cos(angle1));

    func_8006DB3C(&ray, &splitHead->position_18, &sp30, splitHead);

    if (distToPlayer > Q12(2.85f) && distToPlayer < Q12(4.0f) &&
        angle2 < Q12_ANGLE(15.0f) &&
        (!ray.hasHit_0 || ray.chara_10 != NULL))
    {
        splitHead->model_0.controlState_2 = SplitHeadControl_1;
        if (!Rng_GenerateUInt(0, 7))
        {
            splitHeadProps.flags_E8 |= SplitHeadFlag_8;
        }
    }

    if (!Rng_GenerateUInt(0, 127))
    {
        splitHeadProps.flags_E8 |= SplitHeadFlag_8;
    }

    if (!Rng_GenerateUInt(0, 63))
    {
        splitHeadProps.flags_E8 |= SplitHeadFlag_7;
    }
}

void Ai_SplitHead_Control_6(s_SubCharacter* splitHead)
{
    switch (splitHead->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(SplitHeadAnim_11, true):
            Chara_MoveSpeedUpdate(splitHead, Q12(0.5f));

            if (!sharedFunc_800D4530_1_s05(splitHead))
            {
                break;
            }

        case ANIM_STATUS(SplitHeadAnim_1, false):
        case ANIM_STATUS(SplitHeadAnim_1, true):
        case ANIM_STATUS(SplitHeadAnim_10, false):
        case ANIM_STATUS(SplitHeadAnim_10, true):
        case ANIM_STATUS(SplitHeadAnim_11, false):
            splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_7, false);
            Chara_MoveSpeedUpdate(splitHead, Q12(1.0f));
            break;

        default:
            break;

        case ANIM_STATUS(SplitHeadAnim_7, false):
        case ANIM_STATUS(SplitHeadAnim_7, true):
        case ANIM_STATUS(SplitHeadAnim_8, false):
        case ANIM_STATUS(SplitHeadAnim_8, true):
        case ANIM_STATUS(SplitHeadAnim_12, false):
        case ANIM_STATUS(SplitHeadAnim_12, true):
        case ANIM_STATUS(SplitHeadAnim_13, false):
        case ANIM_STATUS(SplitHeadAnim_13, true):
            Chara_MoveSpeedUpdate(splitHead, Q12(1.0f));

            if (!Savegame_EventFlagGet(EventFlag_131))
            {
                func_8005DC1C(Sfx_Unk1479, &splitHead->position_18, Q8_CLAMPED(0.5f), 0);
            }

            Savegame_EventFlagSet(EventFlag_131);
            break;
    }
}

void Ai_SplitHead_Control_7(s_SubCharacter* splitHead)
{
    q3_12 angleDeltaToPlayer;

    if (ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) == SplitHeadAnim_9)
    {
        Chara_MoveSpeedUpdate3(splitHead, Q12(0.8f), Q12(-1.2f));

        angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                           splitHead->rotation_24.vy);
        if (TIMESTEP_ANGLE(3, 3) < ABS(angleDeltaToPlayer)) // @hack `(g_DeltaTime / 3) >> 3` should be same as `g_DeltaTime / 24`, but that doesn't match?
        {
            if (angleDeltaToPlayer > Q12_ANGLE(0.0f))
            {
                splitHead->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
            }
            else
            {
                splitHead->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(30.0f));
            }
        }
        else
        {
            splitHead->rotation_24.vy = Math_AngleBetweenPositionsGet(splitHead->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        }
    }
    else
    {
        splitHead->model_0.controlState_2 = SplitHeadControl_4;
    }
}

void Ai_SplitHead_Control_8(s_SubCharacter* splitHead)
{
    if (!Savegame_EventFlagGet(EventFlag_130))
    {
        return;
    }

    splitHead->model_0.controlState_2  = SplitHeadControl_2;
    splitHead->model_0.anim_4.status_0 = ANIM_STATUS(SplitHeadAnim_11, false);
    splitHeadProps.flags_E8           |= SplitHeadFlag_8;
}

void sharedFunc_800D267C_1_s05(s_SubCharacter* splitHead)
{
    s_800C4590 sp18;
    VECTOR3    pos;

    splitHead->headingAngle_3C = splitHead->rotation_24.vy;

    sharedFunc_800D4408_1_s05(&pos, 2, Q8(0.0f), -57, 3);

    splitHead->field_D8.offsetX_4 = pos.vx - splitHead->position_18.vx;
    splitHead->field_C8.field_0   = pos.vy;
    splitHead->field_D8.offsetZ_6 = pos.vz - splitHead->position_18.vz;

    if (ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) == SplitHeadAnim_2 ||
        ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) == SplitHeadAnim_14)
    {
        splitHead->field_D4.radius_0 = Q12(1.3f);
    }
    else
    {
        splitHead->field_D4.radius_0 = Q12(1.7f);
    }

    splitHead->field_E1_0 = 4;

    func_8005CB20(splitHead, &sp18, sharedData_800D8614_1_s05, sharedData_800D8616_1_s05);

    sharedData_800D8614_1_s05 = Q12(0.0f);
    sharedData_800D8616_1_s05 = Q12(0.0f);
}

void sharedFunc_800D274C_1_s05(s_SubCharacter* splitHead, s_AnmHeader* anmHdr)
{
    SVECTOR     sp10;
    MATRIX      sp18;
    s32         i;
    s_AnimInfo* animInfo;

    splitHead->rotation_24.vy = func_8005BF38(splitHead->rotation_24.vy);

    switch (splitHead->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(SplitHeadAnim_1, false):
        case ANIM_STATUS(SplitHeadAnim_1, true):
        case ANIM_STATUS(SplitHeadAnim_2, false):
        case ANIM_STATUS(SplitHeadAnim_2, true):
        case ANIM_STATUS(SplitHeadAnim_4, false):
        case ANIM_STATUS(SplitHeadAnim_7, false):
        case ANIM_STATUS(SplitHeadAnim_8, false):
        case ANIM_STATUS(SplitHeadAnim_8, true):
        case ANIM_STATUS(SplitHeadAnim_13, false):
        case ANIM_STATUS(SplitHeadAnim_13, true):
        case ANIM_STATUS(SplitHeadAnim_14, false):
        case ANIM_STATUS(SplitHeadAnim_14, true):
            WorldGfx_HeldItemAttach(splitHead->model_0.charaId_0, 2);
            break;

        default:
            WorldGfx_HeldItemAttach(splitHead->model_0.charaId_0, 1);
            break;
    }

    switch (splitHead->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(SplitHeadAnim_9, true):
        case ANIM_STATUS(SplitHeadAnim_11, true):
            switch (splitHead->model_0.controlState_2)
            {
                case SplitHeadControl_2:
                case SplitHeadControl_7:
                    sharedData_800D5884_1_s05 = Q12_MULT_PRECISE(splitHead->moveSpeed_38, Q12(9.3f));

                    if (splitHead->rotation_24.vy != splitHeadProps.angle_EC)
                    {
                        if (splitHead->moveSpeed_38 >= Q12(0.0f))
                        {
                            sharedData_800D5884_1_s05 = MAX(sharedData_800D5884_1_s05, Q12(8.0f));
                        }
                        else
                        {
                            sharedData_800D5884_1_s05 = CLAMP_HIGH(sharedData_800D5884_1_s05, Q12(-8.0f));
                        }
                    }
                    break;

                case SplitHeadControl_1:
                case SplitHeadControl_3:
                    if (!(splitHeadProps.flags_E8 & SplitHeadFlag_3))
                    {
                        sharedData_800D5884_1_s05 = CLAMP_LOW(Q12_MULT_PRECISE(splitHead->moveSpeed_38, Q12(9.3f)), Q12(12.0f));

                        if (splitHead->moveSpeed_38 > Q12(0.0f))
                        {
                            splitHeadProps.flags_E8 |= SplitHeadFlag_5;
                        }
                        else if (splitHead->moveSpeed_38 < Q12(0.0f))
                        {
                            splitHeadProps.flags_E8 &= ~SplitHeadFlag_5;
                        }
                    }
                    else
                    {
                        if (splitHeadProps.flags_E8 & SplitHeadFlag_5)
                        {
                            sharedData_800D5884_1_s05 = Q12(24.0f);
                        }
                        else
                        {
                            sharedData_800D5884_1_s05 = Q12(-24.0f);
                        }
                    }
                    break;

                case SplitHeadControl_4:
                    if (!(splitHeadProps.flags_E8 & SplitHeadFlag_3))
                    {
                        sharedData_800D5884_1_s05 = CLAMP_LOW(Q12_MULT_PRECISE(splitHead->moveSpeed_38, Q12(9.3f)), Q12(12.0f));
                    }
                    else
                    {
                        if (FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) > 187 &&
                            FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) < 203)
                        {
                            sharedData_800D5884_1_s05 = Q12(24.0f);
                        }
                        else
                        {
                            sharedData_800D5884_1_s05 = Q12(-24.0f);
                        }
                    }
                    break;

                case SplitHeadControl_5:
                    sharedData_800D5884_1_s05 = Q12_MULT_PRECISE(splitHead->moveSpeed_38, Q12(9.3f));

                    if (splitHead->rotation_24.vy != splitHeadProps.angle_EC)
                    {
                        if (splitHead->moveSpeed_38 >= Q12(0.0f))
                        {
                            sharedData_800D5884_1_s05 = MAX(sharedData_800D5884_1_s05, Q12(10.0f));
                        }
                        else
                        {
                            sharedData_800D5884_1_s05 = CLAMP_HIGH(sharedData_800D5884_1_s05, Q12(-10.0f));
                        }
                    }
                    break;

                case SplitHeadControl_6:
                    sharedData_800D5884_1_s05 = Q12_MULT_PRECISE(splitHead->moveSpeed_38, Q12(9.3f));

                    if (splitHeadProps.flags_E8 & SplitHeadFlag_5)
                    {
                        sharedData_800D5884_1_s05 = MAX(sharedData_800D5884_1_s05, Q12(12.0f));
                    }
                    else
                    {
                        sharedData_800D5884_1_s05 = CLAMP_HIGH(sharedData_800D5884_1_s05, Q12(-12.0f));
                    }
                    break;
            }

            SPLIT_HEAD_ANIM_INFOS[splitHead->model_0.anim_4.status_0].duration_8.constant = sharedData_800D5884_1_s05;

        case ANIM_STATUS(SplitHeadAnim_3, true):
            break;

        case ANIM_STATUS(SplitHeadAnim_2, true):
            if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
            {
                SPLIT_HEAD_ANIM_INFOS[5].duration_8.constant = Q12(12.0f);
            }
            else if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
            {
                SPLIT_HEAD_ANIM_INFOS[5].duration_8.constant = Q12(8.0f);
            }
            else
            {
                SPLIT_HEAD_ANIM_INFOS[5].duration_8.constant = Q12(16.0f);
            }
            break;
    }

    Math_MatrixTransform(&splitHead->position_18, (SVECTOR*)&splitHead->rotation_24, sharedData_800D8610_1_s05);

    animInfo = &SPLIT_HEAD_ANIM_INFOS[splitHead->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&splitHead->model_0, anmHdr, sharedData_800D8610_1_s05, animInfo);

    // TODO: Are the unconverted numbers angles or time values?
    if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_11, true) && (splitHead->rotation_24.vy != splitHeadProps.angle_EC))
    {
        if ((splitHeadProps.angle_EC   < splitHead->rotation_24.vy && splitHead->moveSpeed_38 >= Q12(0.0f)) ||
            (splitHead->rotation_24.vy < splitHeadProps.angle_EC   && splitHead->moveSpeed_38 <  Q12(0.0f)))
        {
            splitHeadProps.field_EE = CLAMP_LOW(splitHeadProps.field_EE - Q12_MULT_PRECISE(g_DeltaTime, 160), -192);
        }
        else
        {
            splitHeadProps.field_EE = MIN(splitHeadProps.field_EE + Q12_MULT_PRECISE(g_DeltaTime, 160), 192);
        }
    }
    else
    {
        if (splitHeadProps.field_EE > Q12(0.0f))
        {
            splitHeadProps.field_EE = CLAMP_LOW(splitHeadProps.field_EE - Q12_MULT_PRECISE(g_DeltaTime, 160), Q12(0.0f));
        }
        else
        {
            splitHeadProps.field_EE = MIN(splitHeadProps.field_EE + Q12_MULT_PRECISE(g_DeltaTime, 160), Q12(0.0f));
        }
    }

    if (splitHeadProps.field_EE != Q12(0.0f))
    {
        *(s32*)&sp10 = splitHeadProps.field_EE << 16;
        sp10.vz= 0;

        Math_RotMatrixZxyNegGte(&sp10, &sp18);
        MulMatrix(&sharedData_800D8610_1_s05[1].coord, &sp18);

        *(s32*)&sp10 = (splitHeadProps.field_EE >> 3) << 16;
        sp10.vz = 0;

        Math_RotMatrixZxyNegGte(&sp10, &sp18);

        for (i = 18; i < 25; i++)
        {
            MulMatrix(&sharedData_800D8610_1_s05[i].coord, &sp18);
        }
    }

    splitHeadProps.angle_EC = splitHead->rotation_24.vy;
}

void sharedFunc_800D2D74_1_s05(s_SubCharacter* splitHead)
{
    VECTOR3 sp20[4];
    VECTOR3 sp50[4];
    s32     sp80[4];
    s16     sp90[4];
    s16     sp98[3];
    q19_12  deltaX;
    q19_12  deltaZ;
    q19_12  dist;
    s32     i;
    s32     unkIdx;
    q19_12  offsetX;
    q19_12  offsetZ;

    sharedFunc_800D4408_1_s05(&sp20[0], 2, Q8(0.0f), -0x45, 0xFB);
    sharedFunc_800D4408_1_s05(&sp50[0], 2, Q8(0.0f), 0xED, 0xA6);
    sharedFunc_800D4408_1_s05(&sp20[1], 0x13, -0x24, 5, 0x71);
    sharedFunc_800D4408_1_s05(&sp20[2], 0x17, 0x24, 5, 0x71);

    deltaX = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - splitHead->position_18.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - splitHead->position_18.vz);
    dist   = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    sp98[0] = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - sp20[0].vx, g_SysWork.playerWork_4C.player_0.position_18.vz - sp20[0].vz);
    sp98[1] = func_8005BF38((ratan2(sp20[1].vx - sp20[0].vx, sp20[1].vz - sp20[0].vz) - sp98[0]));
    sp98[2] = func_8005BF38((ratan2(sp20[2].vx - sp20[0].vx, sp20[2].vz - sp20[0].vz) - sp98[0]));

    if (sp98[1] < 0x400 && sp98[2] > -0x400)
    {
        if ((sp98[1] >= 0 && sp98[2] <= 0) || (dist > Q12(2.75f) && sp98[1] >= -0x40 && sp98[2] <= 0x40))
        {
            if (ABS(sp98[1] - sp98[2]) >= 0x72)
            {
                splitHeadProps.flags_E8 |= SplitHeadFlag_0;
                splitHead->field_C8.field_0                  = sp20[0].vy;
                splitHead->field_C8.field_4                  = sp50[0].vy;
                splitHead->field_D4.field_2                  = Q12(0.6f);

                offsetX = (sp20[0].vx - splitHead->position_18.vx) * 3;

                if (offsetX < 0)
                {
                    offsetX += 3;
                }
                splitHead->field_D8.offsetX_0 = (offsetX >> 2);

                offsetZ = (sp20[0].vz - splitHead->position_18.vz) * 3;

                if (offsetZ < 0)
                {
                    offsetZ += 3;
                }

                splitHead->field_D8.offsetZ_2 = offsetZ >> 2;
                return;
            }
        }
    }

    if (dist > Q12(2.75f))
    {
        splitHeadProps.flags_E8 &= ~SplitHeadFlag_0;
    }

    sharedFunc_800D4408_1_s05(&sp20[3], 1, 0, -0x46, -0xB7);

    unkIdx = 1;

    sp80[0] = func_8005C478(&sp90[0], g_SysWork.playerWork_4C.player_0.position_18.vx,
                            g_SysWork.playerWork_4C.player_0.position_18.vz, sp20[0].vx, sp20[0].vz,
                            (sp20[1].vx + sp20[2].vx) >> 1, (sp20[1].vz + sp20[2].vz) >> 1);

    for (i = 1; i < 4; i++)
    {
        sp80[i] = func_8005C478(&sp90[i], g_SysWork.playerWork_4C.player_0.position_18.vx,
                                g_SysWork.playerWork_4C.player_0.position_18.vz, sp20[0].vx, sp20[0].vz, sp20[i].vx, sp20[i].vz);

        if (sp80[i] < sp80[unkIdx])
        {
            unkIdx = i;
        }
    }

    if (unkIdx < 3)
    {
        if (sp90[0] > Q12(0.85f))
        {
            sp90[unkIdx] = Q12(0.85f);
        }
        else
        {
            sp90[unkIdx] = sp90[0];
        }

        if (unkIdx == 1)
        {
            sharedFunc_800D4408_1_s05(&sp50[1], 0x13, -0x24, 0x88, 0x16);
        }
        else
        {
            sharedFunc_800D4408_1_s05(&sp50[2], 0x17, 0x24, 0x88, 0x16);
        }
    }
    else
    {
        if (sp90[3] > Q12(0.9f))
        {
            sp90[3] = Q12(0.9f);
        }
        sharedFunc_800D4408_1_s05(&sp50[3], 1, 0, 0x95, -0x13F);
    }

    splitHead->field_C8.field_0 = FP_FROM((sp20[0].vy * (Q12(1.0f) - sp90[unkIdx])) + (sp20[unkIdx].vy * sp90[unkIdx]), Q12_SHIFT);
    splitHead->field_C8.field_4 = FP_FROM((sp50[0].vy * (Q12(1.0f) - sp90[unkIdx])) + (sp20[unkIdx + 4].vy * sp90[unkIdx]), Q12_SHIFT);
    splitHead->field_C8.field_6 = (splitHead->field_C8.field_0 + splitHead->field_C8.field_4) >> 1;

    if (unkIdx == 3)
    {
        splitHead->field_D4.field_2 = Q12(0.6f);
    }
    else
    {
        splitHead->field_D4.field_2 = FP_FROM(((Q12(1.0f) - sp90[unkIdx]) * Q12(0.6f)) + (sp90[unkIdx] * Q12(0.35f)), Q12_SHIFT);
    }

    splitHead->field_D8.offsetX_0 = FP_FROM((sp20[0].vx * (Q12(1.0f) - sp90[unkIdx])) + (sp20[unkIdx].vx * sp90[unkIdx]), Q12_SHIFT) - splitHead->position_18.vx;
    splitHead->field_D8.offsetZ_2 = FP_FROM((sp20[0].vz * (Q12(1.0f) - sp90[unkIdx])) + (sp20[unkIdx].vz * sp90[unkIdx]), Q12_SHIFT) - splitHead->position_18.vz;
}

void sharedFunc_800D3388_1_s05(s_SubCharacter* splitHead, q19_12* offsetX, q19_12* offsetZ)
{
    u8                           sp18[9];
    u8                           sp28[9];
    s_sharedFunc_800D4594_1_s05  sp38[9];
    s16                          spC8[9];
    q19_12                       newPosX;
    q19_12                       newPosZ;
    s32                          temp_s7;
    s32                          j;
    s32                          k;
    s32                          var_a0;
    s32                          var_a1;
    s32                          i;
    s32                          new_var;
    s_sharedFunc_800D4594_1_s05* ptr0;
    s_sharedFunc_800D4594_1_s05* ptr1;

    k = 0;

    if (splitHeadProps.flags_E8 & SplitHeadFlag_1)
    {
        *offsetZ = 0;
        *offsetX = 0;
        return;
    }

    newPosX = g_SysWork.playerWork_4C.player_0.position_18.vx + *offsetX;
    newPosZ = g_SysWork.playerWork_4C.player_0.position_18.vz + *offsetZ;

    for (i = sharedData_800D5AAE_1_s05; i < 9; i++)
    {
        sharedFunc_800D4594_1_s05(&sp38[k], newPosX, newPosZ, &sharedData_800D8618_1_s05[i], &sharedData_800D8618_1_s05[(i == 8) ? sharedData_800D5AAE_1_s05 : (i + 1)]);

        sp18[i]              = sp38[k].field_C;
        sp28[i]              = sp38[k].field_D;
        sp38[k].field_E = i;

        if (g_SysWork.playerWork_4C.player_0.field_D4.radius_0 >= sp38[k].field_0)
        {
            k++;
        }
    }

    temp_s7 = k;

    while (k != 0)
    {
        for (k = 0, j = 0; j < 5 && k == 0; j++)
        {
            for (i = 0; i < temp_s7; i++)
            {
                if (j < 3)
                {
                    if ((j == 0 && sp38[i].field_D != 0 && sp38[i].field_C == 2) ||
                        (j == 1 && sp38[i].field_C == j && sp38[(i + 1) % temp_s7].field_C == 0 &&
                         (sp38[i].field_E == 8 ? sharedData_800D5AAE_1_s05 : sp38[i].field_E + 1) == sp38[(i + 1) % temp_s7].field_E) ||
                        (j == 2 && sp38[i].field_D != 0))
                    {
                        ptr0 = &sp18[i * 16] + 32;
                        ptr1 = &sp18[k * 16] + 32;

                        ptr1->field_0 = ptr0->field_0;
                        ptr1->field_4 = ptr0->field_4;
                        ptr1->field_8 = ptr0->field_8;
                        ptr1->field_C = ptr0->field_C;
                        ptr1->field_D = ptr0->field_D;
                        ptr1->field_E = ptr0->field_E;

                        sp38[k].field_0 = g_SysWork.playerWork_4C.player_0.field_D4.radius_0 - sp38[k].field_0;
                        spC8[k]         = ratan2(newPosX - sp38[i].field_4, newPosZ - sp38[i].field_8);

                        k++;

                        if (j == 1)
                        {
                            i += 1;
                        }
                    }
                }
                else
                {
                    if (j == 3)
                    {
                        if (sp38[i].field_E != sharedData_800D5AAE_1_s05)
                        {
                            var_a0 = sp38[i].field_E - 1;
                        }
                        else
                        {
                            var_a0 = 8;
                        }

                        if (sp38[i].field_E == 8)
                        {
                            var_a1 = sharedData_800D5AAE_1_s05;
                        }
                        else
                        {
                            var_a1 = sp38[i].field_E + 1;
                        }
                    }
                    else
                    {
                        if (sharedData_800D5CF8_1_s05[sp38[i].field_E] != 0)
                        {
                            if (sp38[i].field_E == 8)
                            {
                                var_a0 = sharedData_800D5AAE_1_s05;
                            }
                            else
                            {
                                var_a0 = sp38[i].field_E + 1;
                            }
                            var_a1 = 0;
                        }
                        else
                        {
                            if (sp38[i].field_E != sharedData_800D5AAE_1_s05)
                            {
                                var_a0 = sp38[i].field_E - 1;
                            }
                            else
                            {
                                var_a0 = 8;
                            }
                            var_a1 = 0;
                        }
                    }

                    new_var = var_a0;

                    if ((j == 3 && sharedData_800D5CF8_1_s05[sp38[i].field_E] == 2 &&
                         (sharedData_800D5D08_1_s05[sp38[i].field_E] != 0 ||
                          (sharedData_800D5CF8_1_s05[new_var] == 1 && sharedData_800D5D08_1_s05[new_var] != 0) ||
                          (sharedData_800D5CF8_1_s05[var_a1] == 0 && sharedData_800D5D08_1_s05[var_a1] != 0))) ||
                        (j == 4 && sharedData_800D5CF8_1_s05[sp38[i].field_E] != 2 &&
                         (sharedData_800D5D08_1_s05[sp38[i].field_E] != 0 || sharedData_800D5D08_1_s05[new_var] != 0)))
                    {
                        ptr0 = &sp18[i * 16] + 32;
                        ptr1 = &sp18[k * 16] + 32;

                        ptr1->field_0 = ptr0->field_0;
                        ptr1->field_4 = ptr0->field_4;
                        ptr1->field_8 = ptr0->field_8;
                        ptr1->field_C = ptr0->field_C;
                        ptr1->field_D = ptr0->field_D;
                        ptr1->field_E = ptr0->field_E;

                        sp38[k].field_0 = g_SysWork.playerWork_4C.player_0.field_D4.radius_0 + sp38[k].field_0;
                        spC8[k]         = ratan2(sp38[i].field_4 - newPosX, sp38[i].field_8 - newPosZ);

                        k++;

                        sp28[sp38[i].field_E] = sharedData_800D5D08_1_s05[sp38[i].field_E];
                        sp18[sp38[i].field_E] = sharedData_800D5CF8_1_s05[sp38[i].field_E];
                    }
                }
            }
        }

        if (k == 0)
        {
            for (i = 0; i < temp_s7; i++)
            {
                sp38[i].field_0 = g_SysWork.playerWork_4C.player_0.field_D4.radius_0 + sp38[i].field_0;
                spC8[i]         = ratan2(sp38[i].field_4 - newPosX, sp38[i].field_8 - newPosZ);
            }

            k = temp_s7;
        }
        break;
    }

    *offsetZ = 0;
    *offsetX = 0;

    for (i = 0; i < k; i++)
    {
        *offsetX += Q12_MULT(sp38[i].field_0, Math_Sin(spC8[i]));
        *offsetZ += Q12_MULT(sp38[i].field_0, Math_Cos(spC8[i]));

        if (FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) > 13 && FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) < 34 &&
            (sp38[i].field_E < 2 || sp38[i].field_E > 6))
        {
            sharedData_800D5AAF_1_s05 = 1;
        }
    }

    for (i = 0; i < 9; i++)
    {
        sharedData_800D5CF8_1_s05[i] = sp18[i];
        sharedData_800D5D08_1_s05[i] = sp28[i];
    }
}

void sharedFunc_800D3AFC_1_s05(s_SubCharacter* splitHead)
{
    sharedData_800D8684_1_s05 = 0;
    sharedData_800D8688_1_s05 = 0;
    sharedFunc_800D3388_1_s05(splitHead, &sharedData_800D8684_1_s05, &sharedData_800D8688_1_s05);
}

void sharedFunc_800D3B30_1_s05(s_SubCharacter* splitHead)
{
    s_sharedFunc_800D4594_1_s05 sp18;
    s_sharedFunc_800D4594_1_s05 sp28;
    VECTOR3                     sp38;
    s32                         sp48;
    s32                         sp4C;
    s32                         temp_v0;
    q19_12                      deltaX;
    q19_12                      deltaZ;
    s32                         var_v1;
    q3_12                       var_v1_3;

    splitHead->field_C8.field_2   = 0;
    splitHead->field_D4.radius_0   = 0;
    splitHead->field_D8.offsetX_4 = Q12(0.0f);
    splitHead->field_D8.offsetZ_6 = Q12(0.0f);
    splitHead->field_E1_0         = 0;
    splitHead->field_E1_0         = 4;

    sharedFunc_800D4408_1_s05(&sharedData_800D8618_1_s05[0], 17, sharedData_800D5A90_1_s05[0].vx, sharedData_800D5A90_1_s05[0].vy, sharedData_800D5A90_1_s05[0].vz);
    sharedFunc_800D4408_1_s05(&sharedData_800D8618_1_s05[1], 21, (s16)((u16)sharedData_800D5A90_1_s05[0].vx * -1), sharedData_800D5A90_1_s05[0].vy, sharedData_800D5A90_1_s05[0].vz);

    sharedData_800D8618_1_s05[0].vx = (sharedData_800D8618_1_s05[0].vx + sharedData_800D8618_1_s05[1].vx) >> 1;
    sharedData_800D8618_1_s05[0].vy = (sharedData_800D8618_1_s05[0].vy + sharedData_800D8618_1_s05[1].vy) >> 1;
    sharedData_800D8618_1_s05[0].vz = (sharedData_800D8618_1_s05[0].vz + sharedData_800D8618_1_s05[1].vz) >> 1;

    sharedFunc_800D4408_1_s05(&sharedData_800D8618_1_s05[1], 19, sharedData_800D5A90_1_s05[2].vx, sharedData_800D5A90_1_s05[2].vy, sharedData_800D5A90_1_s05[2].vz);
    sharedFunc_800D4408_1_s05(&sharedData_800D8618_1_s05[2], 19, sharedData_800D5A90_1_s05[3].vx, sharedData_800D5A90_1_s05[3].vy, sharedData_800D5A90_1_s05[3].vz);
    sharedFunc_800D4408_1_s05(&sharedData_800D8618_1_s05[3], 2, (s16)((u16)sharedData_800D5A90_1_s05[1].vx * -1), sharedData_800D5A90_1_s05[1].vy, sharedData_800D5A90_1_s05[1].vz);
    sharedFunc_800D4408_1_s05(&sharedData_800D8618_1_s05[4], 3, sharedData_800D5A90_1_s05[4].vx, sharedData_800D5A90_1_s05[4].vy, sharedData_800D5A90_1_s05[4].vz);
    sharedFunc_800D4408_1_s05(&sharedData_800D8618_1_s05[5], 7, (s16)((u16)sharedData_800D5A90_1_s05[4].vx * -1), sharedData_800D5A90_1_s05[4].vy, sharedData_800D5A90_1_s05[4].vz);
    sharedFunc_800D4408_1_s05(&sharedData_800D8618_1_s05[6], 2, sharedData_800D5A90_1_s05[1].vx, sharedData_800D5A90_1_s05[1].vy, sharedData_800D5A90_1_s05[1].vz);
    sharedFunc_800D4408_1_s05(&sharedData_800D8618_1_s05[7], 23, (s16)((u16)sharedData_800D5A90_1_s05[3].vx * -1), sharedData_800D5A90_1_s05[3].vy, sharedData_800D5A90_1_s05[3].vz);
    sharedFunc_800D4408_1_s05(&sharedData_800D8618_1_s05[8], 23, (s16)((u16)sharedData_800D5A90_1_s05[2].vx * -1), sharedData_800D5A90_1_s05[2].vy, sharedData_800D5A90_1_s05[2].vz);

    if (!(splitHeadProps.flags_E8 & SplitHeadFlag_0))
    {
        sharedData_800D5AAE_1_s05       = 2;
        sharedData_800D8618_1_s05[8].vx = ((sharedData_800D8618_1_s05[8].vx + sharedData_800D8618_1_s05[1].vx) >> 1);
        sharedData_800D8618_1_s05[8].vy = ((sharedData_800D8618_1_s05[8].vy + sharedData_800D8618_1_s05[1].vy) >> 1);
        sharedData_800D8618_1_s05[8].vz = ((sharedData_800D8618_1_s05[8].vz + sharedData_800D8618_1_s05[1].vz) >> 1);
    }
    else
    {
        sharedData_800D5AAE_1_s05 = 0;
    }

    sharedData_800D5AAF_1_s05 = 0;
    sp48       = sharedData_800D8684_1_s05;
    sp4C       = sharedData_800D8688_1_s05;
    sharedFunc_800D3388_1_s05(splitHead, &sp48, &sp4C);

    if (sharedData_800D5AAF_1_s05 != 0)
    {
        sp38.vx = 0;
        sp38.vy = 0;
        sp38.vz = 0;
    }
    else
    {
        temp_v0 = ABS(sp48) - 32;
        var_v1  = (temp_v0 < 0) ? 0 : (temp_v0 >> 4);
        sp38.vx = (sp48 <= 0) ? (var_v1 * -var_v1) : SQUARE(var_v1);

        sp38.vy = 0;

        temp_v0 = ABS(sp4C) - 32;
        var_v1  = (temp_v0 < 0) ? 0 : (temp_v0 >> 4);
        sp38.vz = (sp4C <= 0) ? (var_v1 * -var_v1) : SQUARE(var_v1);
    }

    sharedFunc_800D2E8C_0_s00(sp48 + sharedData_800D8684_1_s05, sp4C + sharedData_800D8688_1_s05, &sp38);

    if (splitHeadProps.flags_E8 & SplitHeadFlag_0)
    {
        deltaX = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - splitHead->position_18.vx);
        deltaZ = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - splitHead->position_18.vz);

        if (Q6_TO_Q12((SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)))) < Q12(3.3f))
        {
            sharedFunc_800D4594_1_s05(&sp18, g_SysWork.playerWork_4C.player_0.position_18.vx,
                                      g_SysWork.playerWork_4C.player_0.position_18.vz, &sharedData_800D8618_1_s05[0], &sharedData_800D8618_1_s05[1]);
            sharedFunc_800D4594_1_s05(&sp28, g_SysWork.playerWork_4C.player_0.position_18.vx,
                                      g_SysWork.playerWork_4C.player_0.position_18.vz, &sharedData_800D8618_1_s05[0], &sharedData_800D8618_1_s05[8]);

            if (splitHead->model_0.anim_4.time_4 < Q12(31.0f))
            {
                var_v1_3 = Q12(0.0f);
            }
            else if (splitHead->model_0.anim_4.time_4 < Q12(33.0f))
            {
                var_v1_3 = FP_MULTIPLY_PRECISE(g_SysWork.playerWork_4C.player_0.field_D4.radius_0,
                                               splitHead->model_0.anim_4.time_4 + Q12(-31.0f), Q12_SHIFT) >> 1;
            }
            else
            {
                var_v1_3 = Q12(0.0f);
                if (splitHead->model_0.anim_4.time_4 < Q12(37.0f))
                {
                    var_v1_3 = g_SysWork.playerWork_4C.player_0.field_D4.radius_0;
                }
            }

            if (sp18.field_0 < var_v1_3 &&
                sp28.field_0 < var_v1_3 &&
                !(splitHeadProps.flags_E8 & SplitHeadFlag_9))
            {
                Chara_AttackReceivedSet(&g_SysWork.playerWork_4C.player_0, WEAPON_ATTACK(EquippedWeaponId_Unk37, AttackInputType_Hold));

                splitHeadProps.flags_E8 |= SplitHeadFlag_1 | SplitHeadFlag_9;

                func_8005DC1C(Sfx_Unk1473, &g_SysWork.playerWork_4C.player_0.position_18, Q8(0.999f), 2);
            }
        }
    }
}

void sharedFunc_800D4070_1_s05(s_SubCharacter* splitHead)
{
    VECTOR3 unkPos;  // Q19.12
    VECTOR  sp30[2]; // Q23.8
    s32     i;
    s32     j;
    q20_12  moveSpeed;
    q3_12   moveSpeedDiv2;
    q3_12   headingAngle;
    s32     animIdx;
    int     new_var;

    if (g_DeltaTime != Q12(0.0f))
    {
        new_var = Q12(2.0f);

        animIdx = ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0);

        if ((ANIM_STATUS_IDX_GET(splitHead->model_0.anim_4.status_0) != SplitHeadAnim_12) && animIdx != SplitHeadAnim_13)
        {
            if ((FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) < 20 || FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) > 35) &&
                (FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) > 14 && FP_FROM(splitHead->model_0.anim_4.time_4, Q12_SHIFT) < 20 ||
                 ((animIdx == SplitHeadAnim_1 || animIdx == SplitHeadAnim_9) && !Rng_GenerateUInt(0, 3)) || !Rng_GenerateUInt(0, 31)))
            {
                if (splitHead->model_0.anim_4.status_0 == ANIM_STATUS(SplitHeadAnim_3, true))
                {
                    i = Rng_GenerateInt(0, 37);
                }
                else
                {
                    i = Rng_GenerateInt(0, 21);
                }

                sharedFunc_800D4408_1_s05(&unkPos, sharedData_800D5AB0_1_s05[i].idx, sharedData_800D5AB0_1_s05[i].vec.vx, sharedData_800D5AB0_1_s05[i].vec.vy, sharedData_800D5AB0_1_s05[i].vec.vz);

                sp30[0].vx = Q12_TO_Q8(unkPos.vx);
                sp30[0].vy = Q12_TO_Q8(unkPos.vy);
                sp30[0].vz = Q12_TO_Q8(unkPos.vz);

                if (ANIM_TIME_RANGE_CHECK(splitHead->model_0.anim_4.time_4, 15, 19))
                {
                    moveSpeedDiv2 = new_var;
                    if (sharedData_800D5AB0_1_s05[i].idx < 20)
                    {
                        headingAngle = splitHead->rotation_24.vy + Q12_ANGLE(90.0f);
                    }
                    else
                    {
                        headingAngle = splitHead->rotation_24.vy - Q12_ANGLE(90.0f);
                    }
                }
                else
                {
                    moveSpeed = splitHead->moveSpeed_38;

                    if (splitHead->moveSpeed_38 > Q12(0.0f))
                    {
                        headingAngle = splitHead->rotation_24.vy;
                        moveSpeedDiv2 = moveSpeed >> 1;
                    }
                    else
                    {
                        moveSpeed = -moveSpeed;
                        moveSpeedDiv2  = moveSpeed >> 1;
                        headingAngle  = splitHead->rotation_24.vy + Q12_ANGLE(180.0f);
                    }
                }

                sharedFunc_800CBE7C_1_s05(sp30[0].vx, sp30[0].vy, sp30[0].vz, moveSpeedDiv2, Q12_FRACT(headingAngle));
            }
        }
    }

    switch (splitHead->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(SplitHeadAnim_8, false):
        case ANIM_STATUS(SplitHeadAnim_8, true):
        case ANIM_STATUS(SplitHeadAnim_13, false):
        case ANIM_STATUS(SplitHeadAnim_13, true):
            splitHeadProps.field_EA = MAX(0, splitHeadProps.field_EA - g_DeltaTime / 68);

        case ANIM_STATUS(SplitHeadAnim_1, true):
        case ANIM_STATUS(SplitHeadAnim_2, true):
        case ANIM_STATUS(SplitHeadAnim_14, false):
        case ANIM_STATUS(SplitHeadAnim_14, true):
            for (i = 0; i < 6; i++)
            {
                for (j = 0; j < 2; j++)
                {
                    sharedFunc_800D4408_1_s05(&unkPos, sharedData_800D5AB0_1_s05[sharedData_800D5BE0_1_s05[i][j]].idx, sharedData_800D5AB0_1_s05[sharedData_800D5BE0_1_s05[i][j]].vec.vx,
                                              sharedData_800D5AB0_1_s05[sharedData_800D5BE0_1_s05[i][j]].vec.vy, sharedData_800D5AB0_1_s05[sharedData_800D5BE0_1_s05[i][j]].vec.vz);

                    sp30[j].vx = Q12_TO_Q8(unkPos.vx);
                    sp30[j].vy = Q12_TO_Q8(unkPos.vy);
                    sp30[j].vz = Q12_TO_Q8(unkPos.vz);
                }

                sharedFunc_800CCE2C_1_s05(sharedData_800D5BE0_1_s05[i][2], splitHeadProps.field_EA,
                                          sp30[0].vx, sp30[0].vy, sp30[0].vz, sp30[1].vx, sp30[1].vy, sp30[1].vz);
            }
            break;
    }
}

void sharedFunc_800D4408_1_s05(VECTOR3* pos, s32 idx, q23_8 posX, q23_8 posY, q23_8 posZ)
{
    typedef struct
    {
        MATRIX  mat_0;
        SVECTOR field_20;
        VECTOR3 field_28;
    } s_ScratchData;

    s_ScratchData* scratch;

    scratch = PSX_SCRATCH;

    Math_SetSVectorFastSum(&scratch->field_20, posX, posY, posZ);
    scratch->field_20.vz = posZ; // @hack Needed for match.

    Vw_CoordHierarchyMatrixCompute(&sharedData_800D8610_1_s05[idx], &scratch->mat_0);

    gte_SetRotMatrix(&scratch->mat_0);
    gte_SetTransMatrix(&scratch->mat_0);

    gte_ldv0(&scratch->field_20);
    gte_rt();
    gte_stlvnl(&scratch->field_28);

    pos->vx = Q8_TO_Q12(scratch->field_28.vx);
    pos->vy = Q8_TO_Q12(scratch->field_28.vy);
    pos->vz = Q8_TO_Q12(scratch->field_28.vz);
}

void sharedFunc_800D450C_1_s05(q19_12 offsetX, q19_12 offsetZ)
{
    sharedData_800D8614_1_s05 += offsetX;
    sharedData_800D8616_1_s05 += offsetZ;
}

bool sharedFunc_800D4530_1_s05(s_SubCharacter* splitHead)
{
    q19_12 animTime;

    animTime = splitHeadProps.animTime_F8;
    return ((animTime <  Q12(0.0f) || animTime > Q12(198.0f)) && splitHead->model_0.anim_4.time_4 < Q12(175.0f)) ||
           ((animTime >= Q12(0.0f) && animTime < Q12(175.0f)) && splitHead->model_0.anim_4.time_4 > Q12(198.0f));
}

void sharedFunc_800D4594_1_s05(s_sharedFunc_800D4594_1_s05* arg0, q19_12 posX, q19_12 posZ, VECTOR3* vec0, VECTOR3* vec1)
{
    q3_12 angle;
    q3_12 angle1;
    s32   temp_a1;
    s32   temp_s0_2;
    s32   temp_s2;
    s32   temp_v0;

    angle       = ratan2(vec1->vx - vec0->vx, vec1->vz - vec0->vz) + Q12_ANGLE(90.0f);
    temp_s0_2     = posX + Math_Sin(angle);
    temp_v0       = Math_Cos(angle);
    angle1     = (((posX - vec0->vx) >> 2) * ((vec1->vz - vec0->vz) >> 2)) - (((posZ - vec0->vz) >> 2) * ((vec1->vx - vec0->vx) >> 2)) < 1;
    arg0->field_D = angle1;

    if ((((vec0->vx - posX) >> 2) * (temp_v0 >> 2)) - (((vec0->vz - posZ) >> 2) * ((temp_s0_2 - posX) >> 2)) < 0)
    {
        arg0->field_0 = SquareRoot0(SQUARE((posX - vec0->vx) >> 3) + SQUARE((posZ - vec0->vz) >> 3)) << 3;
        arg0->field_4 = vec0->vx;
        arg0->field_8 = vec0->vz;
        arg0->field_C = 0;
    }
    else if ((((vec1->vx - posX) >> 2) * (temp_v0 >> 2)) - (((vec1->vz - posZ) >> 2) * ((temp_s0_2 - posX) >> 2)) > 0)
    {
        arg0->field_0 = SquareRoot0(SQUARE((posX - vec1->vx) >> 3) + SQUARE((posZ - vec1->vz) >> 3)) << 3;
        arg0->field_4 = vec1->vx;
        arg0->field_8 = vec1->vz;
        arg0->field_C = 1;
    }
    else
    {
        angle       = ratan2(vec1->vx - vec0->vx, vec1->vz - vec0->vz);
        temp_s2       = SquareRoot0(SQUARE((posX - vec0->vx) >> 3) + SQUARE((posZ - vec0->vz) >> 3)) << 3;
        angle1     = ratan2(posX - vec0->vx, posZ - vec0->vz) - angle;
        arg0->field_0 = ABS(FP_FROM(temp_s2 * Math_Sin(angle1), Q12_SHIFT));
        temp_s2       = FP_FROM(temp_s2 * Math_Cos(angle1), Q12_SHIFT);
        arg0->field_4 = FP_FROM(temp_s2 * Math_Sin(angle), Q12_SHIFT) + vec0->vx;
        arg0->field_8 = FP_FROM(temp_s2 * Math_Cos(angle), Q12_SHIFT) + vec0->vz;
        arg0->field_C = 2;
    }
}

#undef splitHeadProps
