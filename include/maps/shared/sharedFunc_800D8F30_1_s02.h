void sharedFunc_800D8F30_1_s02(s_SubCharacter* creaper)
{
    VECTOR3 creaperPos;
    s32     i;
    s32     field_10C;
    q19_12  dist;
    q19_12  moveSpeed;
    q19_12  moveSpeedTmp0;

    #define playerPos (g_SysWork.playerWork_4C.player_0.position_18)

    if (func_800700F8(creaper, &g_SysWork.playerWork_4C.player_0))
    {
        g_SysWork.field_2284[3]         &= ~(1 << 1);
        creaper->model_0.state_2         = 2;
        creaper->model_0.anim_4.status_0 = ANIM_STATUS(CreaperAnim_13, false);
        return;
    }

    if (ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == CreaperAnim_12 ||
        creaper->model_0.anim_4.status_0 == ANIM_STATUS(CreaperAnim_2, false) ||
        ANIM_TIME_RANGE_CHECK(creaper->model_0.anim_4.time_4, 4, 7))
    {
        dist = Math_Vector2MagCalc(playerPos.vx - creaper->position_18.vx, playerPos.vz - creaper->position_18.vz);
        if (dist < Q12(0.4f))
        {
            Chara_MoveSpeedUpdate3(creaper, Q12(16.0f), Q12(0.0f));
        }
        else
        {
            field_10C = (u16)creaper->properties_E4.dummy.properties_E8[9].val16[0] >> 1;

            // TODO: Why don't either of these fit?
            // creaper->moveSpeed_38 = APPROACH(creaper->moveSpeed_38, field_10C, FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(6.0f), Q12_SHIFT));
            // Chara_MoveSpeedUpdate3(creaper, Q12(6.0f), field_10C);

            if (field_10C < creaper->moveSpeed_38)
            {
                moveSpeed   = field_10C;
                moveSpeedTmp0 = creaper->moveSpeed_38 - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(6.0f), Q12_SHIFT);
                if (moveSpeed < moveSpeedTmp0)
                {
                    moveSpeed = moveSpeedTmp0;
                }
            }
            else
            {
                moveSpeed   = field_10C;
                moveSpeedTmp0 = creaper->moveSpeed_38 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(6.0f), Q12_SHIFT);
                if (moveSpeed >= moveSpeedTmp0)
                {
                    moveSpeed = moveSpeedTmp0;
                }
            }
            creaper->moveSpeed_38 = moveSpeed;
        }

        if (((g_DeltaTime0 >> 2) + 1) < ABS(func_8005BF38((ratan2(playerPos.vx - creaper->position_18.vx, playerPos.vz - creaper->position_18.vz) - creaper->rotation_24.vy))))
        {
            if ((func_8005BF38((ratan2(playerPos.vx - creaper->position_18.vx, playerPos.vz - creaper->position_18.vz) - creaper->rotation_24.vy)) << 0x10) > 0)
            {
                creaper->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.5f), Q12_SHIFT);
            }
            else
            {
                creaper->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.5f), Q12_SHIFT);
            }
        }
        else
        {
            creaper->rotation_24.vy = ratan2(playerPos.vx - creaper->position_18.vx, playerPos.vz - creaper->position_18.vz);
        }

        creaper->field_44.field_0 = 1;
        return;
    }

    Chara_MoveSpeedUpdate3(creaper, Q12(2.0f), Q12(0.0f));

    if (ANIM_TIME_RANGE_CHECK(creaper->model_0.anim_4.time_4, 9, 10))
    {
        creaperPos     = creaper->position_18;
        creaperPos.vy += creaper->field_C8.field_8;

        func_8008A0E4(1, WEAPON_ATTACK(EquippedWeaponId_HuntingRifle, AttackInputType_Multitap),
                      creaper, &creaperPos, &g_SysWork.playerWork_4C.player_0, creaper->rotation_24.vy,
                      ratan2(Q12(0.4f), (playerPos.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_2) - (creaper->position_18.vy + creaper->field_C8.field_2)));

        if (!(creaper->properties_E4.creaper.flags_E8 & (1 << 0)))
        {
            func_8005DC1C(Sfx_Unk1424, &creaper->position_18, Q8(0.5f), 0);
        }

        creaper->properties_E4.creaper.flags_E8 |= 1 << 0;

        // Run through NPCs.
        for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
        {
            if (creaper->model_0.charaId_0 == Chara_Creaper && !Math_Distance2dCheck(&creaper->position_18, &g_SysWork.npcs_1A0[i].position_18, Q12(16.0f)))
            {
                g_SysWork.npcs_1A0[i].properties_E4.creaper.flags_E8 |= 1 << 8;
            }
        }
    }
    else if (ANIM_STATUS_IDX_GET(creaper->model_0.anim_4.status_0) == CreaperAnim_13)
    {
        g_SysWork.field_2284[3]               &= ~(1 << 1);
        creaper->model_0.state_2               = 2;
        creaper->properties_E4.player.field_F0 = Q12(0.0f);
        creaper->properties_E4.dummy.properties_E8[8].val16[0] = func_8006FAFC(creaper, Q12(4.8f), playerPos.vx, playerPos.vz, FP_ANGLE(360.0f), false);
        creaper->field_44.field_0 = 0;
    }
}
