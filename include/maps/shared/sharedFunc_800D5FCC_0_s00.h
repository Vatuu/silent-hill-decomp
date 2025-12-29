void sharedFunc_800D5FCC_0_s00(s_SubCharacter* stalker)
{
    #define FRICTION_PER_FRAME 1.5f // TODO: Or is it per tick?

    q19_12 dist;
    s32    distDiv;
    q19_12 angleOffset;

    #define stalkerProps stalker->properties_E4.stalker

    if (stalker->health_B0 < sharedData_800E3A24_0_s00)
    {
        stalker->flags_3E |= CharaFlag_Unk2;
    }

    stalkerProps.flags_E8 |= StalkerFlag_6;
    if (!(stalkerProps.flags_E8 & StalkerFlag_13))
    {
        Chara_MoveSpeedUpdate(stalker, Q12(FRICTION_PER_FRAME));
    }

    distDiv = 0;
    angleOffset = FP_ANGLE(0.0f);
    dist = Q12(0.0f);

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_24, false))
    {
        dist = Q12(0.15f);
        distDiv = 1;
        angleOffset = FP_ANGLE(180.0f);
    }
    else if (ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 395, 402))
    {
        dist = Q12(1.0f);
        distDiv = 8 - stalkerProps.relKeyframeIdx_FE;
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
    else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_45, true) &&
             ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 159, 167))
    {
        dist = Q12(0.3f);
        distDiv = 8;
        angleOffset = FP_ANGLE(180.0f);
    }
    else if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_10, true) &&
             ANIM_TIME_RANGE_CHECK(stalker->model_0.anim_4.time_4, 96, 100))
    {
        dist = Q12(0.2f);
        distDiv = 5;
        angleOffset = FP_ANGLE(180.0f);
    }

    if (dist != Q12(0.0f))
    {
        dist = (s32)(dist * (u32)FP_MULTIPLY_PRECISE(STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant, g_DeltaTime0, Q12_SHIFT)) /
               FP_TO(distDiv, Q12_SHIFT);

        stalkerProps.offset_EC = FP_MULTIPLY(dist, Math_Sin(stalker->rotation_24.vy + angleOffset), Q12_SHIFT);
        stalkerProps.offset_EE = FP_MULTIPLY(dist, Math_Cos(stalker->rotation_24.vy + angleOffset), Q12_SHIFT);
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_26, true) ||
        stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_17, true) ||
        stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_18, true))
    {
        if (stalker->health_B0 == Q12(0.0f) && stalker->moveSpeed_38 == Q12(0.0f))
        {
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_26, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_21, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_17, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_19, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_18, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_20, false);
            }

            stalker->model_0.controlState_2 = StalkerControl_10;
            func_80037DC4(stalker);
        }

        if (stalker->health_B0 > sharedData_800E3A24_0_s00 &&
            !Rng_GenerateInt(0, 7) && // 1 in 8 chance.
            !(stalkerProps.flags_E8 & StalkerFlag_13))
        {
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_26, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_11, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_17, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_12, false);
            }
            if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_18, true))
            {
                stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_13, false);
            }
            
            stalker->model_0.controlState_2 = StalkerControl_8;
            stalkerProps.flags_E8 |= StalkerFlag_7;
            stalkerProps.flags_E8 &= ~StalkerFlag_6;
        }
    }

    #undef stalkerProps
}
