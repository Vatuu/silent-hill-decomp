void sharedFunc_800D5FCC_0_s00(s_SubCharacter* stalker)
{
    #define FRICTION_PER_FRAME 1.5f // TODO: Or is it per tick?

    q19_12 dist;
    s32    distDiv;
    q19_12 angleOffset;

    if (stalker->health_B0 < sharedData_800E3A24_0_s00)
    {
        stalker->flags_3E |= CharaFlag_Unk2;
    }

    stalker->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 6;

    if (!(stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 13)))
    {
        Chara_MoveSpeedUpdate(stalker, Q12(FRICTION_PER_FRAME));
    }

    distDiv = 0;
    angleOffset = FP_ANGLE(0.0f);
    dist = Q12(0.0f);

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(24, false))
    {
        dist = Q12(0.15f);
        distDiv = 1;
        angleOffset = FP_ANGLE(180.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 395, 402))
    {
        dist = Q12(1.0f);
        distDiv = 8 - stalker->properties_E4.dummy.properties_E8[5].val16[1];
        angleOffset = FP_ANGLE(180.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 407, 412))
    {
        dist = Q12(0.5f);
        distDiv = 5;
        angleOffset = FP_ANGLE(0.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 0, 3))
    {
        dist = Q12(0.1f);
        distDiv = 4;
        angleOffset = FP_ANGLE(180.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 9, 17))
    {
        dist = Q12(0.3f);
        distDiv = 9;
        angleOffset = FP_ANGLE(180.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 4, 6))
    {
        dist = Q12(0.4f);
        distDiv = 3;
        angleOffset = FP_ANGLE(180.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 20, 23))
    {
        dist = Q12(0.1f);
        distDiv = 5;
        angleOffset = FP_ANGLE(0.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 27, 32))
    {
        dist = Q12(0.3f);
        distDiv = 6;
        angleOffset = FP_ANGLE(0.0f);
    }
    else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(45, true) && ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 159, 167))
    {
        dist = Q12(0.3f);
        distDiv = 8;
        angleOffset = FP_ANGLE(180.0f);
    }
    else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(10, true) && ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 96, 100))
    {
        dist = Q12(0.2f);
        distDiv = 5;
        angleOffset = FP_ANGLE(180.0f);
    }

    if (dist != Q12(0.0f))
    {
        dist = (s32)(dist * (u32)FP_MULTIPLY_PRECISE(STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, Q12_SHIFT)) /
               FP_TO(distDiv, Q12_SHIFT);

        stalker->properties_E4.dummy.properties_E8[1].val16[0] = FP_MULTIPLY(dist, Math_Sin(stalker->rotation_24.vy + angleOffset), Q12_SHIFT);
        stalker->properties_E4.dummy.properties_E8[1].val16[1] = FP_MULTIPLY(dist, Math_Cos(stalker->rotation_24.vy + angleOffset), Q12_SHIFT);
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(26, true) ||
        stalker->model_0.anim_4.status_0 == ANIM_STATUS(17, true) ||
        stalker->model_0.anim_4.status_0 == ANIM_STATUS(18, true))
    {
        if (stalker->health_B0 == Q12(0.0f) && stalker->moveSpeed_38 == Q12(0.0f))
        {
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(26, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(21, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(17, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(19, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(18, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(20, false);
            }

            stalker->model_0.state_2 = 10;
            func_80037DC4(stalker);
        }

        if (stalker->health_B0 > sharedData_800E3A24_0_s00 &&
            (Rng_Rand16() % 8) == 0 &&
            (stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 13)) == 0)
        {
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(26, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(17, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(12, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(18, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(13, false);
            }
            
            stalker->model_0.state_2 = 8;
            stalker->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 7;
            stalker->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 6);
        }
    }
}
