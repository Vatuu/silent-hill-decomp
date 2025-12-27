void sharedFunc_800D8F30_1_s02(s_SubCharacter* creeper)
{
    VECTOR3 creeperPos;
    s32     i;
    q19_12  moveSpeed0;
    q19_12  distToPlayer;
    q19_12  moveSpeed;
    q19_12  moveSpeedTmp0;

    // TODO: Using name `playerPos` causes decomp.me context errors. Change name when all functions are matched.
    #define PLAYER_POS (g_SysWork.playerWork_4C.player_0.position_18)

    if (func_800700F8(creeper, &g_SysWork.playerWork_4C.player_0))
    {
        g_SysWork.field_2284[3]         &= ~(1 << 1);
        creeper->model_0.state_2         = 2;
        creeper->model_0.anim_4.status_0 = ANIM_STATUS(CreeperAnim_13, false);
        return;
    }

    if (ANIM_STATUS_IDX_GET(creeper->model_0.anim_4.status_0) == CreeperAnim_12 ||
        creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_2, false) ||
        ANIM_TIME_RANGE_CHECK(creeper->model_0.anim_4.time_4, 4, 7))
    {
        distToPlayer = Math_Vector2MagCalc(PLAYER_POS.vx - creeper->position_18.vx,
                                           PLAYER_POS.vz - creeper->position_18.vz);
        if (distToPlayer < Q12(0.4f))
        {
            Chara_MoveSpeedUpdate3(creeper, Q12(16.0f), Q12(0.0f));
        }
        else
        {
            moveSpeed0 = creeper->properties_E4.creeper.moveSpeed_10C / 2;

            // TODO: Why don't either of these fit?
            // creeper->moveSpeed_38 = APPROACH(creeper->moveSpeed_38, moveSpeed0, FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(6.0f), Q12_SHIFT));
            // Chara_MoveSpeedUpdate3(creeper, Q12(6.0f), moveSpeed0);

            if (moveSpeed0 < creeper->moveSpeed_38)
            {
                moveSpeed   = moveSpeed0;
                moveSpeedTmp0 = creeper->moveSpeed_38 - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(6.0f), Q12_SHIFT);
                if (moveSpeed < moveSpeedTmp0)
                {
                    moveSpeed = moveSpeedTmp0;
                }
            }
            else
            {
                moveSpeed   = moveSpeed0;
                moveSpeedTmp0 = creeper->moveSpeed_38 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(6.0f), Q12_SHIFT);
                if (moveSpeed >= moveSpeedTmp0)
                {
                    moveSpeed = moveSpeedTmp0;
                }
            }
            creeper->moveSpeed_38 = moveSpeed;
        }

        if (((g_DeltaTime0 >> 2) + 1) < ABS(func_8005BF38((ratan2(PLAYER_POS.vx - creeper->position_18.vx, PLAYER_POS.vz - creeper->position_18.vz) - creeper->rotation_24.vy))))
        {
            if ((func_8005BF38((ratan2(PLAYER_POS.vx - creeper->position_18.vx, PLAYER_POS.vz - creeper->position_18.vz) - creeper->rotation_24.vy)) << 0x10) > 0)
            {
                creeper->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.5f), Q12_SHIFT);
            }
            else
            {
                creeper->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(0.5f), Q12_SHIFT);
            }
        }
        else
        {
            creeper->rotation_24.vy = ratan2(PLAYER_POS.vx - creeper->position_18.vx, PLAYER_POS.vz - creeper->position_18.vz);
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
                      creeper, &creeperPos, &g_SysWork.playerWork_4C.player_0, creeper->rotation_24.vy,
                      ratan2(Q12(0.4f), (PLAYER_POS.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_2) - (creeper->position_18.vy + creeper->field_C8.field_2)));

        if (!(creeper->properties_E4.creeper.flags_E8 & CreeperFlag_0))
        {
            func_8005DC1C(Sfx_Unk1424, &creeper->position_18, Q8(0.5f), 0);
        }

        creeper->properties_E4.creeper.flags_E8 |= CreeperFlag_0;

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
        g_SysWork.field_2284[3]                     &= ~(1 << 1);
        creeper->model_0.state_2                     = 2;
        creeper->properties_E4.creeper.timer_F0      = Q12(0.0f);
        creeper->properties_E4.creeper.rotationY_108 = Chara_HeadingAngleGet(creeper, Q12(4.8f), PLAYER_POS.vx, PLAYER_POS.vz, FP_ANGLE(360.0f), false);
        creeper->field_44.field_0                    = 0;
    }
}
