void sharedFunc_800D17BC_1_s00(s_SubCharacter* larvalStalker)
{
    q19_12 angle;
    s32    keyframe;
    s32    keyframe2;
    s16    keyframeOffset;

    if (larvalStalker->damage_B4.amount_C <= Q12(0.0f) || larvalStalker->health_B0 <= Q12(0.0f))
    {
        return;
    }

    func_8005DC1C(0, &larvalStalker->position_18, Q8_CLAMPED(0.5f), 0);

    larvalStalker->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 7;

    larvalStalker->health_B0           = MAX(larvalStalker->health_B0 - larvalStalker->damage_B4.amount_C, Q12(0.0f));
    larvalStalker->damage_B4.position_0.vx += FP_FROM(larvalStalker->moveSpeed_38 * Math_Sin(larvalStalker->headingAngle_3C), Q12_SHIFT);
    larvalStalker->damage_B4.position_0.vz += FP_FROM(larvalStalker->moveSpeed_38 * Math_Cos(larvalStalker->headingAngle_3C), Q12_SHIFT);
    larvalStalker->moveSpeed_38        = FP_TO(Math_Vector2MagCalc(larvalStalker->damage_B4.position_0.vx, larvalStalker->damage_B4.position_0.vz), Q12_SHIFT) / Q12(2.4f);
    larvalStalker->field_34            = FP_TO(larvalStalker->damage_B4.position_0.vy, Q12_SHIFT) / Q12(2.4f);
    larvalStalker->headingAngle_3C     = ratan2(larvalStalker->damage_B4.position_0.vx, larvalStalker->damage_B4.position_0.vz);

    larvalStalker->properties_E4.dummy.properties_E8[0].val16[0] |= 1 << 1;
    larvalStalker->properties_E4.dummy.properties_E8[4].val32     = g_SysWork.playerWork_4C.player_0.position_18.vx;
    larvalStalker->properties_E4.dummy.properties_E8[5].val32     = g_SysWork.playerWork_4C.player_0.position_18.vz;

    if (larvalStalker->model_0.state_2 == 11)
    {
        if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == 9)
        {
            larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = NO_VALUE;
            larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(17, false);
        }
    }
    else if (larvalStalker->model_0.state_2 == 12)
    {
        if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) == 2)
        {
            larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = NO_VALUE;
            larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(18, false);
        }
    }
    else
    {
        if (func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - larvalStalker->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - larvalStalker->position_18.vz) - larvalStalker->rotation_24.vy) < 0)
        {
            angle = -func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - larvalStalker->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - larvalStalker->position_18.vz) - larvalStalker->rotation_24.vy);
        }
        else
        {
            angle = func_8005BF38(ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - larvalStalker->position_18.vx, g_SysWork.playerWork_4C.player_0.position_18.vz - larvalStalker->position_18.vz) - larvalStalker->rotation_24.vy);
        }

        if (larvalStalker->health_B0 > Q12(100.0f))
        {
            larvalStalker->model_0.state_2 = 10;
            if (angle < FP_ANGLE(90.0f))
            {
                keyframe2      = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe2 - 41;
                if (keyframe2 >= 41 && keyframe2 < 66)
                {
                    // No-op.
                }
                else if (keyframe2 >= 66 && keyframe2 < 73)
                {
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                    if (keyframeOffset == 30)
                    {
                        larvalStalker->model_0.anim_4.time_4 -= Q12(1.0f);
                    }

                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(5, false);
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = 76 - FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else if (keyframe2 >= 73 && keyframe2 < 75)
                {
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(5, false);
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = 5;
                }
                else if (keyframe2 >= 75 && keyframe2 < 79)
                {
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                    if (keyframeOffset == 36)
                    {
                        larvalStalker->model_0.anim_4.time_4 -= Q12(1.0f);
                    }
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(5, false);
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = 79 - FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else
                {
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = 0;
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(5, false);
                }
            }
            else
            {
                keyframe2      = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe2 - 86;
                if (keyframe2 >= 86 && keyframe2 < 105)
                {
                    // No-op
                }
                else if (keyframe2 >= 105 && keyframe2 < 119)
                {
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(6, false);
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = 7 - ((FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) - 104) >> 1);
                }
                else
                {
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = 0;
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(6, false);
                }
            }
        }
        else
        {
            if (Rng_GenerateInt(0, 7) == 0) // 1 in 8 chance.
            {
                func_80037DC4(larvalStalker);
            }

            if (angle < FP_ANGLE(90.0f))
            {
                keyframe       = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe - 41;
                if (keyframe >= 41 && keyframe < 52)
                {
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(7, false);
                    keyframeOffset                                               = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) - 41;
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = keyframeOffset;
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                }
                else if (keyframe >= 52 && keyframe < 66)
                {
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(2, false);
                }
                else if (keyframe >= 66 && keyframe < 73)
                {
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                    if (keyframeOffset == 30)
                    {
                        larvalStalker->model_0.anim_4.time_4 -= Q12(1.0f);
                    }
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(7, false);
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = 76 - FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else if (keyframe >= 73 && keyframe < 75)
                {
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(7, false);
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                    larvalStalker->model_0.anim_4.time_4                                 = 5;
                }
                else if (keyframe >= 75 && keyframe < 79)
                {
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                    if (keyframeOffset == 36)
                    {
                        larvalStalker->model_0.anim_4.time_4 -= Q12(1.0f);
                    }
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(7, false);
                    larvalStalker->model_0.anim_4.time_4   = 79 - FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else
                {
                    if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != 7)
                    {
                        larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = 0;
                        larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(7, false);
                    }
                }

                larvalStalker->model_0.state_2 = 12;
            }
            else
            {
                keyframe2      = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe2 - 86;
                if (keyframe2 >= 86 && keyframe2 < 97)
                {
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(8, false);
                    keyframeOffset                                               = FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) - 86;
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = keyframeOffset;
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                }
                else if (keyframe2 >= 97 && keyframe2 < 105)
                {
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(9, false);
                }
                else if (keyframe2 >= 105 && keyframe2 < 119)
                {
                    larvalStalker->model_0.anim_4.status_0                               = ANIM_STATUS(8, false);
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[1] = keyframeOffset;
                    larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = 7 - ((FP_FROM(larvalStalker->model_0.anim_4.time_4, Q12_SHIFT) - 104) >> 1);
                }
                else
                {
                    if (ANIM_STATUS_IDX_GET(larvalStalker->model_0.anim_4.status_0) != 8)
                    {
                        larvalStalker->properties_E4.dummy.properties_E8[3].val16[0] = 0;
                    }
                    larvalStalker->model_0.anim_4.status_0 = ANIM_STATUS(8, false);
                }

                larvalStalker->model_0.state_2 = 11;
            }
        }
    }

    larvalStalker->properties_E4.dummy.properties_E8[8].val16[0] = 0;
    larvalStalker->properties_E4.dummy.properties_E8[1].val32    = 0;
}
