void sharedFunc_800D5FCC_0_s00(s_SubCharacter* chara)
{
    s32    var_a1;
    q19_12 var_s0;
    s32    var_s2;
    s32    moveSpeed;

    const float FRICTION_PER_FRAME = 1.5;

    if (chara->health_B0 < sharedData_800E3A24_0_s00)
    {
        chara->flags_3E |= (1 << 1);
    }

    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= (1 << 6);

    if (!(chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 13)))
    {
        if (chara->moveSpeed_38 > 0)
        {
            moveSpeed = chara->moveSpeed_38 - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, FRICTION_PER_FRAME, Q12_SHIFT);
            if (moveSpeed < 0)
            {
                moveSpeed = 0;
            }
        }
        else
        {
            moveSpeed = chara->moveSpeed_38 + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, FRICTION_PER_FRAME, Q12_SHIFT);
            if (moveSpeed > 0)
            {
                moveSpeed = 0;
            }
        }
        chara->moveSpeed_38 = moveSpeed;
    }

    var_a1 = 0;
    var_s2 = 0;
    var_s0 = 0;

    #define ANIM_TIME_INT FP_FROM(chara->model_0.anim_4.time_4, 0xC)

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(24, false))
    {
        var_s0 = Q12(0.15f);
        var_a1 = 1;
        var_s2 = FP_ANGLE(180.0f);
    }
    else if (ANIM_TIME_INT >= 395 && ANIM_TIME_INT <= 402)
    {
        var_s0 = Q12(1.0f);
        var_a1 = 8 - chara->properties_E4.larvalStalker.properties_E8[5].val16[1];
        var_s2 = FP_ANGLE(180.0f);
    }
    else if (ANIM_TIME_INT >= 407 && ANIM_TIME_INT <= 412)
    {
        var_s0 = Q12(0.5f);
        var_a1 = 5;
        var_s2 = FP_ANGLE(0.0f);
    }
    else if (ANIM_TIME_INT >= 0 && ANIM_TIME_INT <= 3)
    {
        var_s0 = Q12(0.1f);
        var_a1 = 4;
        var_s2 = FP_ANGLE(180.0f);
    }
    else if (ANIM_TIME_INT >= 9 && ANIM_TIME_INT <= 17)
    {
        var_s0 = Q12(0.3f);
        var_a1 = 9;
        var_s2 = FP_ANGLE(180.0f);
    }
    else if (ANIM_TIME_INT >= 4 && ANIM_TIME_INT <= 6)
    {
        var_s0 = Q12(0.4f);
        var_a1 = 3;
        var_s2 = FP_ANGLE(180.0f);
    }
    else if (ANIM_TIME_INT >= 20 && ANIM_TIME_INT <= 23)
    {
        var_s0 = Q12(0.1f);
        var_a1 = 5;
        var_s2 = FP_ANGLE(0.0f);
    }
    else if (ANIM_TIME_INT >= 27 && ANIM_TIME_INT <= 32)
    {
        var_s0 = Q12(0.3f);
        var_a1 = 6;
        var_s2 = FP_ANGLE(0.0f);
    }
    else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(45, true) && (ANIM_TIME_INT >= 159 && ANIM_TIME_INT <= 167))
    {
        var_s0 = Q12(0.3f);
        var_a1 = 8;
        var_s2 = FP_ANGLE(180.0f);
    }
    else if (chara->model_0.anim_4.status_0 == ANIM_STATUS(10, true) && (ANIM_TIME_INT >= 96 && ANIM_TIME_INT <= 100))
    {
        var_s0 = Q12(0.2f);
        var_a1 = 5;
        var_s2 = FP_ANGLE(180.0f);
    }

    if (var_s0 != 0)
    {
        var_s0 = (s32)(var_s0 * (u32)FP_MULTIPLY_PRECISE(STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, 12)) / FP_TO(var_a1, 12);

        chara->properties_E4.larvalStalker.properties_E8[1].val16[0] = FP_FROM(var_s0 * Math_Sin(chara->rotation_24.vy + var_s2), 12);
        chara->properties_E4.larvalStalker.properties_E8[1].val16[1] = FP_FROM(var_s0 * Math_Cos(chara->rotation_24.vy + var_s2), 12);
    }

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(26, true) ||
        chara->model_0.anim_4.status_0 == ANIM_STATUS(17, true) ||
        chara->model_0.anim_4.status_0 == ANIM_STATUS(18, true))
    {
        if (chara->health_B0 == 0 && chara->moveSpeed_38 == 0)
        {
            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(26, true))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(21, false);
            }
            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(17, true))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(19, false);
            }
            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(18, true))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(20, false);
            }
            chara->model_0.state_2 = 10;
            func_80037DC4(chara);
        }

        if (chara->health_B0 > sharedData_800E3A24_0_s00 &&
            (Rng_Rand16() % 8) == 0 &&
            (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 13)) == 0)
        {
            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(26, true))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
            }
            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(17, true))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
            }
            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(18, true))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(13, false);
            }
            
            chara->model_0.state_2 = 8;

            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= (1 << 7);
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] &= ~(1 << 6);
        }
    }
}
