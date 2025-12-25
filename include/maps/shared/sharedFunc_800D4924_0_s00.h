void sharedFunc_800D4924_0_s00(s_SubCharacter* chara)
{
    q3_12  angle;
    s16    xdel_7;
    q3_12  angle0;
    q19_12 mag;
    s32    var_fp;
    s32    i;
    s32    var_s7;
    bool   cond1;
    s32    temp;
    s32    temp2;

    mag = Math_Vector2MagCalc(sharedData_800E3A18_0_s00 - chara->position_18.vx,
                              sharedData_800E3A1C_0_s00 - chara->position_18.vz);

    angle0 = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - chara->position_18.vx,
                                  sharedData_800E3A1C_0_s00 - chara->position_18.vz) -
                           chara->rotation_24.vy);

    if (!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))))
    {
        var_fp = Q12(15.0f);
        var_s7 = Q12(5.5f);
        cond1  = func_8006FD90(chara, 0, Q12(7.5f), Q12(7.5f));
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
#if defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP5_S02) || defined(MAP6_S03) || defined(MAP6_S04) || defined(MAP7_S02)
        var_fp = Q12(16.0f);
        var_s7 = Q12(6.0f);
        cond1  = func_8006FD90(chara, 0, Q12(8.0f), Q12(8.0f));
#else
        var_fp = Q12(12.0f);
        var_s7 = Q12(4.5f);
        cond1  = func_8006FD90(chara, 0, Q12(6.0f), Q12(6.0f));
#endif
    }
    else
    {
        var_fp = Q12(0.8f);
#if defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP5_S02) || defined(MAP6_S03) || defined(MAP6_S04) || defined(MAP7_S02)
        var_s7 = Q12(1.2f);
#else
        var_s7 = Q12(1.0f);
#endif
        cond1 = func_8006FD90(chara, 1, Q12(0.4f), Q12(0.4f));
    }

    if (cond1 || func_80070360(chara, mag, Q12(1.0f)))
    {
        chara->properties_E4.player.field_F0 = sharedData_800E3A18_0_s00;
        chara->properties_E4.player.field_F4 = sharedData_800E3A1C_0_s00;

        if (!(chara->properties_E4.splitHead.flags_E8 & (1 << 10)))
        {
            chara->properties_E4.splitHead.flags_E8 |= 1 << 10;
            sharedFunc_800D7E04_0_s00(chara, 1363);
        }

        chara->properties_E4.dummy.properties_E8[11].val16[1] = 0;
    }
    else if (chara->properties_E4.splitHead.flags_E8 & (1 << 10))
    {
        chara->properties_E4.dummy.properties_E8[11].val16[1] += g_DeltaTime0;

        if (!Rng_TestProbabilityBits(9) || (u16)chara->properties_E4.dummy.properties_E8[11].val16[1] > Q12(1.2f))
        {
            chara->properties_E4.dummy.properties_E8[11].val16[1] = 0;
            chara->properties_E4.splitHead.flags_E8              &= ~(1 << 10);
        }
    }

    if (mag > Q12(8.0f))
    {
        if (chara->properties_E4.splitHead.flags_E8 & (1 << 0) && chara->properties_E4.splitHead.flags_E8 & (1 << 10) &&
            !(g_SysWork.flags_22A4 & (1 << 7)))
        {
            if (!Vw_AabbVisibleInScreenCheck(chara->position_18.vx - Q12(1.0f),
                                             chara->position_18.vx + Q12(1.0f),
                                             chara->position_18.vy - Q12(1.8f),
                                             chara->position_18.vy,
                                             chara->position_18.vz - Q12(1.0f),
                                             chara->position_18.vz - Q12(1.0f)))
            {
                chara->properties_E4.splitHead.flags_E8 |= 1 << 12;
            }
        }
    }

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(30, true) && !(chara->properties_E4.splitHead.flags_E8 & 0x100) &&
        !func_800700F8(chara, &g_SysWork.playerWork_4C.player_0))
    {
        chara->properties_E4.player.runTimer_F8 = 0;

        if (!(chara->properties_E4.splitHead.flags_E8 & 0x2000))
        {
            Chara_MoveSpeedUpdate3(chara, FP_ANGLE(180.0f), (0x800 - ABS(angle0)) * 2);
        }

        if (chara->properties_E4.splitHead.flags_E8 & 0x1000)
        {
            chara->rotation_24.vy = ratan2(chara->properties_E4.player.field_F0 - chara->position_18.vx,
                                           chara->properties_E4.player.field_F4 - chara->position_18.vz);
        }
        else
        {
            for (i = 3 + ((ABS(angle0) > FP_ANGLE(90.0f)) ? 1 : 0); i > 0; i--)
            {
                if (((g_DeltaTime0 >> 3) + 1) < ABS(angle0))
                {
                    if (angle0 > FP_ANGLE(0.0f))
                    {
                        chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
                    }
                    else
                    {
                        chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
                    }

                    angle0 = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - chara->position_18.vx,
                                                  sharedData_800E3A1C_0_s00 - chara->position_18.vz) -
                                           chara->rotation_24.vy);
                }

                if (ABS(angle0) < ((g_DeltaTime0 >> 3) + 1) || mag > (var_s7 >> 2))
                {
                    break;
                }
            }
        }

        if ((g_SysWork.field_2284[3] & (1 << 0)) || func_80070320() ||
            ABS(chara->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy) > 0x4CC ||
            ( (chara->properties_E4.splitHead.flags_E8 & (1 << 2)) &&  Rng_GenerateInt(0, 3)) || // 3 in 4 chance?
            (!(chara->properties_E4.splitHead.flags_E8 & (1 << 2)) && !Rng_GenerateInt(0, 3)))   // 1 in 4 chance.
        {
            if (!(g_SysWork.playerWork_4C.player_0.flags_3E & 8) && mag < 0xE66 && (mag >= 0xB34 || !Rng_GenerateInt(0, 3)) &&
                ABS(angle0) < 0x400 && g_SysWork.playerWork_4C.player_0.health_B0 > 0)
            {
                chara->model_0.state_2   = 5;
                g_SysWork.field_2284[3] |= 2;

                sharedFunc_800D7E04_0_s00(chara, 1364);

                if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 492 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 505)
                {
                    chara->model_0.anim_4.status_0                       = 0x4B;
                    chara->properties_E4.dummy.properties_E8[5].val16[0] = 0x1D;
                    chara->properties_E4.dummy.properties_E8[5].val16[1] = 0;
                }
                else
                {
                    chara->model_0.anim_4.status_0                       = ANIM_STATUS(7, false);
                    chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x1DD;

                    if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 477 &&
                        FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 482)
                    {
                        chara->properties_E4.dummy.properties_E8[5].val16[1] = 1;
                    }
                    else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 481 &&
                             FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 488)
                    {
                        chara->properties_E4.dummy.properties_E8[5].val16[1] = 2;
                    }
                    else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 487 &&
                             FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 491)
                    {
                        chara->properties_E4.dummy.properties_E8[5].val16[1] = 3;
                    }
                    else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 490 &&
                             FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 493)
                    {
                        chara->properties_E4.dummy.properties_E8[5].val16[1] = 4;
                    }
                    else
                    {
                        chara->properties_E4.dummy.properties_E8[5].val16[1] = 0;
                    }
                }
            }
            else if (mag < Q12(0.7f))
            {
                chara->model_0.state_2 = 4;
            }
        }
        else if (!(g_SysWork.playerWork_4C.player_0.flags_3E & CharaFlag_Unk4) &&
                 mag < Q12(1.0f) && mag > Q12(0.5f) &&
                 ABS(angle0) < FP_ANGLE(59.95f) && g_SysWork.playerWork_4C.player_0.health_B0 > Q12(0.0f))
        {
            chara->model_0.state_2 = 6;

            angle = func_8005BF38(g_SysWork.playerWork_4C.player_0.rotation_24.vy - chara->rotation_24.vy);
            if (ABS(angle) > FP_ANGLE(90.0f))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(34, false);
            }
            else
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(35, false);
            }

            chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 477;
            g_SysWork.field_2284[3]                             |= (1 << 0) | (1 << 1);
            chara->field_44.field_0                              = 1;
        }
        else if (mag < Q12(0.7f))
        {
            chara->model_0.state_2 = 4;
        }
    }
    else
    {
        if (!(chara->properties_E4.splitHead.flags_E8 & (1 << 13)))
        {
            Chara_MoveSpeedUpdate3(chara, Q12(0.5f), Q12(0.7f));
        }

        if (chara->properties_E4.player.runTimer_F8 == Q12(0.0f))
        {
            chara->properties_E4.dummy.properties_E8[6].val16[0] = func_8006FAFC(chara,
                                                                                 Q12(2.5f),
                                                                                 chara->properties_E4.player.field_F0,
                                                                                 chara->properties_E4.player.field_F4,
                                                                                 Q12(1.0f),
                                                                                 true);
            if (chara->properties_E4.dummy.properties_E8[6].val16[0] == Q12(1.0f))
            {
                chara->properties_E4.dummy.properties_E8[6].val16[0] = chara->rotation_24.vy - FP_ANGLE(180.0f);
            }
        }

        chara->properties_E4.player.runTimer_F8 += g_DeltaTime0;
        if (chara->properties_E4.player.runTimer_F8 > Q12(3.0f) &&
            !Rng_GenerateInt(0, 15)) // 1 in 16 chance.
        {
            chara->properties_E4.player.runTimer_F8 = Q12(0.0f);
        }

        if (chara->properties_E4.splitHead.flags_E8 & (1 << 12))
        {
            chara->rotation_24.vy = chara->properties_E4.dummy.properties_E8[6].val16[0];
        }
        else
        {
            xdel_7 = func_8005BF38((chara->properties_E4.dummy.properties_E8[6].val16[0] - chara->rotation_24.vy));

            if (((g_DeltaTime0 >> 3) + 1) < ABS(xdel_7))
            {
                if (xdel_7 > 0)
                {
                    chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
                }
                else
                {
                    chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
                }
            }
        }
    }

    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(30, true) && (var_fp * 2) < mag)
    {
        temp = SquareRoot0(SQUARE(Q12_TO_Q6(chara->position_18.vx - chara->properties_E4.player.field_F0)) +
                           SQUARE(Q12_TO_Q6(chara->position_18.vz - chara->properties_E4.player.field_F4)));
        temp2 = (var_s7 >> 1);
        if (Q6_TO_Q12(temp) < temp2)
        {
            chara->model_0.state_2 = 4;
        }
    }
}
