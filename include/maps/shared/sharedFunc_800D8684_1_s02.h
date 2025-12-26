void sharedFunc_800D8684_1_s02(s_SubCharacter* creeper)
{
    q3_12         angle0;
    q3_12         angle1;
    q19_12        distToPlayer;
    q19_12        distToTarget;
    s_PlayerWork* playerWork;

    angle1 = func_8005BF38((ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - creeper->position_18.vx,
                                    g_SysWork.playerWork_4C.player_0.position_18.vz - creeper->position_18.vz) -
                             creeper->rotation_24.vy));

    if (((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1) && func_8006FD90(creeper, 0, Q12(12.0f), Q12(8.0f))) ||
        ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) &&
         (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)) && func_8006FD90(creeper, 2, Q12(0.8f), Q12(0.4f))) ||
        (!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))) && func_8006FD90(creeper, 1, Q12(4.0f), Q12(12.0f))) ||
        (func_80070360(creeper, 0, Q12(0.5f)) || creeper->properties_E4.creeper.flags_E8 & CreeperFlag_Alerted))
    {
        creeper->properties_E4.creeper.playerPositionX_F4 = g_SysWork.playerWork_4C.player_0.position_18.vx;
        creeper->properties_E4.creeper.playerPositionZ_F8 = g_SysWork.playerWork_4C.player_0.position_18.vz;
        creeper->properties_E4.creeper.flags_E8          &= ~CreeperFlag_5;
    }

    distToPlayer = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - creeper->position_18.vx,
                                       g_SysWork.playerWork_4C.player_0.position_18.vz - creeper->position_18.vz);
    distToTarget = Math_Vector2MagCalc(creeper->properties_E4.creeper.playerPositionX_F4 - creeper->position_18.vx,
                                       creeper->properties_E4.creeper.playerPositionZ_F8 - creeper->position_18.vz);

    if (distToTarget < Q12(1.2f) && !(creeper->properties_E4.creeper.flags_E8 & CreeperFlag_0) &&
        !func_800700F8(creeper, &g_SysWork.playerWork_4C.player_0))
    {
        playerWork = &g_SysWork.playerWork_4C;

        if (distToPlayer > Q12(1.2f))
        {
            //if ((creeper->properties_E4.creeper.flags_E8 & (CreeperFlag_4 | CreeperFlag_5)) == CreeperFlag_4) // TODO: Doesn't match?
            if ((creeper->properties_E4.player.afkTimer_E8 & 0x30) == 0x10)
            {
                creeper->properties_E4.creeper.flags_E8          |= CreeperFlag_5;
                creeper->properties_E4.creeper.playerPositionX_F4 = creeper->properties_E4.creeper.playerPositionX_FC;
                creeper->properties_E4.creeper.playerPositionZ_F8 = creeper->properties_E4.creeper.playerPositionZ_100;
            }
            else
            {
                creeper->model_0.state_2                = 1;
                creeper->model_0.anim_4.status_0        = ANIM_STATUS(CreeperAnim_11, false);
                creeper->properties_E4.creeper.timer_F0 = Q12(0.0f);
            }
        }
        else if (!(g_SysWork.field_2284[3] & (1 << 1)) && !(playerWork->player_0.flags_3E & CharaFlag_Unk4) &&
                 distToPlayer < Q12(0.5f) && ABS(angle1) < FP_ANGLE(10.0f) && g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
        {
            creeper->model_0.state_2                = 3;
            creeper->model_0.anim_4.status_0        = ANIM_STATUS(CreeperAnim_12, false);
            creeper->properties_E4.creeper.timer_F0 = Q12(0.0f);
            g_SysWork.field_2284[3]                |= 1 << 1;
        }
        else
        {
            if (ABS(angle1) >= FP_ANGLE(90.0f))
            {
                Chara_MoveSpeedUpdate(creeper, Q12(4.0f));
            }
            else
            {
                Chara_MoveSpeedUpdate3(creeper, Q12(1.5f), (creeper->properties_E4.creeper.moveSpeed_10C * (FP_ANGLE(90.0f) - ABS(angle1))) >> 10);
            }

            if (((g_DeltaTime0 >> 2) + 1) < ABS(angle1) && Rng_GenerateInt(0, 7)) // 1 in 8 chance.
            {
                if (angle1 > FP_ANGLE(0.0f))
                {
                    creeper->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }
                else
                {
                    creeper->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
                }
            }
        }
    }
    else
    {
        Chara_MoveSpeedUpdate4(creeper, Q12(1.5f), creeper->properties_E4.creeper.moveSpeed_10C);

        creeper->properties_E4.creeper.timer_F0 += g_DeltaTime0;

        if ((ABS(angle1) > FP_ANGLE(10.0f) && func_80070184(creeper, Q12(1.0f), creeper->properties_E4.creeper.rotationY_108)) ||
            (!Rng_GenerateInt(0, 7) && // 1 in 8 chance.
             ((!(creeper->properties_E4.creeper.flags_E8 & CreeperFlag_0) && creeper->properties_E4.creeper.timer_F0 > Q12(0.5f)) ||
              ( (creeper->properties_E4.creeper.flags_E8 & CreeperFlag_0) && creeper->properties_E4.creeper.timer_F0 > Q12(2.0f)))))
        {
            if (creeper->properties_E4.creeper.timer_F0 > Q12(2.0f))
            {
                creeper->properties_E4.creeper.flags_E8 &= ~CreeperFlag_0;
            }

            creeper->properties_E4.creeper.rotationY_108 = func_8006FAFC(creeper,
                                                                         Q12(1.2f),
                                                                         creeper->properties_E4.creeper.playerPositionX_F4,
                                                                         creeper->properties_E4.creeper.playerPositionZ_F8,
                                                                         Q12(1.0f),
                                                                         true);
            if (creeper->properties_E4.creeper.rotationY_108 == FP_ANGLE(360.0f))
            {
                creeper->properties_E4.creeper.rotationY_108 = creeper->rotation_24.vy;
            }
            else
            {
                creeper->properties_E4.creeper.timer_F0 = Q12(0.0f);
            }
        }

        angle0 = func_8005BF38(creeper->properties_E4.creeper.rotationY_108 - creeper->rotation_24.vy);
        if (((g_DeltaTime0 >> 2) + 1) < ABS(angle0))
        {
            if (angle0 > FP_ANGLE(0.0f))
            {
                creeper->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
            }
            else
            {
                creeper->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(180.0f), Q12_SHIFT);
            }
        }
    }
}
