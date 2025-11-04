// Ai_LarvalStalker

void sharedFunc_800D17BC_1_s00(s_SubCharacter* chara)
{
    s32 angle;
    s32 keyframe;
    s32 keyframe2;
    s16 keyframeOffset;

    if (chara->damageReceived_C0 <= Q12(0.0f) || chara->health_B0 <= Q12(0.0f))
    {
        return;
    }

    func_8005DC1C(0, &chara->position_18, Q8_CLAMPED(0.5f), 0);

    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 7;

    chara->health_B0       = MAX(chara->health_B0 - chara->damageReceived_C0, Q12(0.0f));
    chara->field_B4       += FP_FROM(chara->moveSpeed_38 * Math_Sin(chara->headingAngle_3C), Q12_SHIFT);
    chara->field_BC       += FP_FROM(chara->moveSpeed_38 * Math_Cos(chara->headingAngle_3C), Q12_SHIFT);
    chara->moveSpeed_38    = FP_TO(Math_Vector2MagCalc(chara->field_B4, chara->field_BC), Q12_SHIFT) / Q12(2.4f);
    chara->field_34        = FP_TO(chara->field_B8, Q12_SHIFT) / Q12(2.4f);
    chara->headingAngle_3C = ratan2(chara->field_B4, chara->field_BC);

    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 1;
    chara->properties_E4.larvalStalker.properties_E8[4].val32     = g_SysWork.player_4C.chara_0.position_18.vx;
    chara->properties_E4.larvalStalker.properties_E8[5].val32     = g_SysWork.player_4C.chara_0.position_18.vz;

    if (chara->model_0.state_2 == 11)
    {
        if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 9)
        {
            chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = NO_VALUE;
            chara->model_0.anim_4.status_0                               = ANIM_STATUS(17, false);
        }
    }
    else if (chara->model_0.state_2 == 12)
    {
        if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 2)
        {
            chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = NO_VALUE;
            chara->model_0.anim_4.status_0                               = ANIM_STATUS(18, false);
        }
    }
    else
    {
        if (func_8005BF38(ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) - chara->rotation_24.vy) < 0)
        {
            angle = -func_8005BF38(ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) - chara->rotation_24.vy);
        }
        else
        {
            angle = func_8005BF38(ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz) - chara->rotation_24.vy);
        }

        if (chara->health_B0 > Q12(100.0f))
        {
            chara->model_0.state_2 = 10;
            if (angle < FP_ANGLE(90.0f))
            {
                keyframe2      = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe2 - 41;
                if (keyframe2 >= 41 && keyframe2 < 66)
                {
                    // No-op
                }
                else if (keyframe2 >= 66 && keyframe2 < 73)
                {
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                    if (keyframeOffset == 30)
                    {
                        chara->model_0.anim_4.time_4 -= Q12(1.0f);
                    }

                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(5, false);
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = 76 - FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else if (keyframe2 >= 73 && keyframe2 < 75)
                {
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(5, false);
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = 5;
                }
                else if (keyframe2 >= 75 && keyframe2 < 79)
                {
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                    if (keyframeOffset == 36)
                    {
                        chara->model_0.anim_4.time_4 -= Q12(1.0f);
                    }
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(5, false);
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = 79 - FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else
                {
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = 0;
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(5, false);
                }
            }
            else
            {
                keyframe2      = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe2 - 86;
                if (keyframe2 >= 86 && keyframe2 < 105)
                {
                    // No-op
                }
                else if (keyframe2 >= 105 && keyframe2 < 119)
                {
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(6, false);
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = 7 - ((FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 104) >> 1);
                }
                else
                {
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = 0;
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(6, false);
                }
            }
        }
        else
        {
            if (!Rng_TestProbabilityBits(3))
            {
                func_80037DC4(chara);
            }

            if (angle < FP_ANGLE(90.0f))
            {
                keyframe       = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe - 41;
                if (keyframe >= 41 && keyframe < 52)
                {
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(7, false);
                    keyframeOffset                                               = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 41;
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = keyframeOffset;
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                }
                else if (keyframe >= 52 && keyframe < 66)
                {
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(2, false);
                }
                else if (keyframe >= 66 && keyframe < 73)
                {
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                    if (keyframeOffset == 30)
                    {
                        chara->model_0.anim_4.time_4 -= Q12(1.0f);
                    }
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(7, false);
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = 76 - FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else if (keyframe >= 73 && keyframe < 75)
                {
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(7, false);
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                    chara->model_0.anim_4.time_4                                 = 5;
                }
                else if (keyframe >= 75 && keyframe < 79)
                {
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                    if (keyframeOffset == 36)
                    {
                        chara->model_0.anim_4.time_4 -= Q12(1.0f);
                    }
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(7, false);
                    chara->model_0.anim_4.time_4   = 79 - FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
                }
                else
                {
                    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != 7)
                    {
                        chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = 0;
                        chara->model_0.anim_4.status_0                               = ANIM_STATUS(7, false);
                    }
                }

                chara->model_0.state_2 = 12;
            }
            else
            {
                keyframe2      = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT);
                keyframeOffset = keyframe2 - 86;
                if (keyframe2 >= 86 && keyframe2 < 97)
                {
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(8, false);
                    keyframeOffset                                               = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 86;
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = keyframeOffset;
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                }
                else if (keyframe2 >= 97 && keyframe2 < 105)
                {
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(9, false);
                }
                else if (keyframe2 >= 105 && keyframe2 < 119)
                {
                    chara->model_0.anim_4.status_0                               = ANIM_STATUS(8, false);
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[1] = keyframeOffset;
                    chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = 7 - ((FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 104) >> 1);
                }
                else
                {
                    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) != 8)
                    {
                        chara->properties_E4.larvalStalker.properties_E8[3].val16[0] = 0;
                    }
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(8, false);
                }

                chara->model_0.state_2 = 11;
            }
        }
    }

    chara->properties_E4.larvalStalker.properties_E8[8].val16[0] = 0;
    chara->properties_E4.larvalStalker.properties_E8[1].val32    = 0;
}
