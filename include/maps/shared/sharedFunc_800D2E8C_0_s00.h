void sharedFunc_800D2E8C_0_s00(q19_12 posX, q19_12 posZ, VECTOR3* vec)
{
#if defined(MAP1_S05)
    q19_12                angle;
    s32                   vecSqr;
    s32                   playerExtraState;
    s_SubCharacter*       playerChara;
    s_MainCharacterExtra* playerExtra;

    playerChara = &g_SysWork.player_4C.chara_0;
    playerExtra = &g_SysWork.player_4C.extra_128;

    if (vec->vx == 0 && vec->vz == 0)
    {
        if (D_800D587C != 0)
        {
            D_800D587C = 0;
        }
    }
    else
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.field_118 = FP_ANGLE_ABS(ratan2(vec->vx, vec->vz));
    }

    if (posX == 0 && posZ == 0)
    {
        return;
    }

    D_800C45B0.vx = posX;
    D_800C45B0.vz = posZ;

    if (g_SysWork.npcs_1A0[0].health_B0 <= Q12(0.0f) || g_Player_IsInWalkToRunTransition || playerChara->health_B0 <= Q12(0.0f))
    {
        return;
    }

    vecSqr      = SQUARE(vec->vx) + SQUARE(vec->vz);
    D_800D587C += SquareRoot0(vecSqr);

    if (vecSqr > Q12(0.75f))
    {
        if (g_SysWork.player_4C.extra_128.state_1C < PlayerState_DamagePushBack || g_SysWork.player_4C.extra_128.state_1C >= PlayerState_Unk31)
        {
            angle = FP_ANGLE_ABS(FP_ANGLE_ABS(ratan2(vec->vx, vec->vz)) - (u16)playerChara->rotation_24.vy);

            if (D_800D587C > Q12(1.75f))
            {
                if (g_SysWork.player_4C.extra_128.state_1C >= 23 && g_SysWork.player_4C.extra_128.state_1C < 27)
                {
                    playerChara->model_0.stateStep_3 = 0;
                    playerChara->model_0.state_2     = 0;
                    playerExtra->model_0.stateStep_3 = 0;
                    playerExtra->model_0.state_2     = 0;
                }

                if (angle >= FP_ANGLE(90.0f) && angle < FP_ANGLE(270.0f))
                {
                    playerExtraState = PlayerState_DamagePushFront;
                }
                else
                {
                    playerExtraState = PlayerState_DamagePushBack;
                }

                Player_ExtraStateSet(playerChara, playerExtra, playerExtraState);
                func_8005DC1C(Sfx_Unk1326, &playerChara->position_18, Q8_CLAMPED(0.125f), 0);
            }
            else if ((g_SysWork.player_4C.extra_128.state_1C < PlayerState_DamageTorsoBack || g_SysWork.player_4C.extra_128.state_1C >= PlayerState_DamageFeetFront) &&
                     g_SysWork.player_4C.extra_128.state_1C != PlayerState_DamagePushBack &&
                     g_SysWork.player_4C.extra_128.state_1C != PlayerState_DamagePushFront)
            {
                if (angle >= FP_ANGLE(45.0f) && angle < FP_ANGLE(135.0f))
                {
                    playerExtraState = PlayerState_DamageTorsoLeft;
                }
                else if (angle >= FP_ANGLE(135.0f) && angle < FP_ANGLE(225.0f))
                {
                    playerExtraState = PlayerState_DamageTorsoFront;
                }
                else if (angle >= FP_ANGLE(225.0f) && angle < FP_ANGLE(315.0f))
                {
                    playerExtraState = PlayerState_DamageTorsoRight;
                }
                else
                {
                    playerExtraState = PlayerState_DamageTorsoBack;
                }

                Player_ExtraStateSet(playerChara, playerExtra, playerExtraState);
            }

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk12;

            playerChara->properties_E4.player.afkTimer_E8 = Q12(0.0f);
            playerChara->properties_E4.player.field_F4    = 0;
            g_SysWork.playerCombatInfo_38.isAiming_13     = false;
            playerChara->field_44                         = NO_VALUE;

            g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk9;

            playerChara->field_44 = NO_VALUE; // Redundant set needed for match.
        }
    }

    if (vecSqr > Q12(1.75f))
    {
        playerChara->damageReceived_C0 = SquareRoot0(vecSqr) * 4;
    }
    else
    {
        playerChara->damageReceived_C0 = SquareRoot0(vecSqr) * 64;
    }

    if (!(g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C & PlayerFlag_DamageReceived) &&
        vecSqr > Q12(0.75f) && vecSqr <= Q12(1.75f))
    {
        func_8005DC1C(Sfx_Unk1327, &playerChara->position_18, Q8_CLAMPED(0.125f), 0);

        playerChara->properties_E4.player.field_10C = 64;
        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C |= PlayerFlag_DamageReceived;
    }

    if (playerChara->damageReceived_C0 != Q12(0.0f))
    {
        g_SysWork.player_4C.chara_0.properties_E4.player.flags_11C &= ~PlayerFlag_Unk2;

        playerChara->health_B0 -= playerChara->damageReceived_C0;
        func_800893D0(playerChara->damageReceived_C0);
        playerChara->damageReceived_C0 = Q12(0.0f);
    }
#endif
}
