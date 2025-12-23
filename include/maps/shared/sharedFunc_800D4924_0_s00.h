void sharedFunc_800D4924_0_s00(s_SubCharacter* chara)
{
    s16  xdel_4;
    s16  xdel_7;
    s16  angle0;
    s32  mag;
    s32  var_fp;
    s32  i;
    s32  var_s7;
    bool cond1;
    s32  temp;
    s32  temp2;

    mag = SquareRoot0(SQUARE((sharedData_800E3A18_0_s00 - chara->position_18.vx) >> 6) +
                      SQUARE((sharedData_800E3A1C_0_s00 - chara->position_18.vz) >> 6))
          << 6;

    angle0 = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - chara->position_18.vx,
                                  sharedData_800E3A1C_0_s00 - chara->position_18.vz) -
                           chara->rotation_24.vy);

    if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3) == 0)
    {
        var_fp = 0xF000;
        var_s7 = 0x5800;
        cond1  = func_8006FD90(chara, 0, 0x7800, 0x7800);
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3) == 2)
    {
#if defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP5_S02) || defined(MAP6_S03) || defined(MAP6_S04) || defined(MAP7_S02)
        var_fp = 0x10000;
        var_s7 = 0x6000;
        cond1  = func_8006FD90(chara, 0, 0x8000, 0x8000);
#else
        var_fp = 0xC000;
        var_s7 = 0x4800;
        cond1  = func_8006FD90(chara, 0, 0x6000, 0x6000);
#endif
    }
    else
    {
        var_fp = 0xCCC;
#if defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP5_S02) || defined(MAP6_S03) || defined(MAP6_S04) || defined(MAP7_S02)
        var_s7 = 0x1333;
#else
        var_s7 = 0x1000;
#endif
        cond1 = func_8006FD90(chara, 1, 0x666, 0x666);
    }

    if (cond1 || func_80070360(chara, mag, 0x1000))
    {
        chara->properties_E4.player.field_F0 = sharedData_800E3A18_0_s00;
        chara->properties_E4.player.field_F4 = sharedData_800E3A1C_0_s00;

        if (!(chara->properties_E4.splitHead.flags_E8 & 0x400))
        {
            chara->properties_E4.splitHead.flags_E8 |= 0x400;
            sharedFunc_800D7E04_0_s00(chara, 0x553);
        }

        chara->properties_E4.dummy.properties_E8[11].val16[1] = 0;
    }
    else if (chara->properties_E4.splitHead.flags_E8 & 0x400)
    {
        chara->properties_E4.dummy.properties_E8[11].val16[1] += g_DeltaTime0;

        if (!Rng_TestProbabilityBits(9) || (u16)chara->properties_E4.dummy.properties_E8[11].val16[1] > 0x1333)
        {
            chara->properties_E4.dummy.properties_E8[11].val16[1] = 0;
            chara->properties_E4.splitHead.flags_E8              &= 0xFBFF;
        }
    }

    if (mag > 0x8000)
    {
        if (chara->properties_E4.splitHead.flags_E8 & 1 && chara->properties_E4.splitHead.flags_E8 & 0x400 && !(g_SysWork.flags_22A4 & 0x80))
        {
            if (!Vw_AabbVisibleInScreenCheck(chara->position_18.vx - 0x1000,
                                             chara->position_18.vx + 0x1000,
                                             chara->position_18.vy - 0x1CCC,
                                             chara->position_18.vy,
                                             chara->position_18.vz - 0x1000,
                                             chara->position_18.vz - 0x1000))
            {
                chara->properties_E4.splitHead.flags_E8 |= 0x1000;
            }
        }
    }

    if (chara->model_0.anim_4.status_0 == 0x3D && !(chara->properties_E4.splitHead.flags_E8 & 0x100) &&
        !func_800700F8(chara, &g_SysWork.playerWork_4C.player_0))
    {
        chara->properties_E4.player.runTimer_F8 = 0;

        if (!(chara->properties_E4.splitHead.flags_E8 & 0x2000))
        {
            Chara_MoveSpeedUpdate3(chara, FP_ANGLE(180.0f), (0x800 - ABS(angle0)) * 2);
        }

        if (chara->properties_E4.splitHead.flags_E8 & 0x1000)
        {
            chara->rotation_24.vy = ratan2(
                chara->properties_E4.player.field_F0 - chara->position_18.vx,
                chara->properties_E4.player.field_F4 - chara->position_18.vz);
        }
        else
        {
            for (i = 3 + ((ABS(angle0) > 0x400) ? 1 : 0); i > 0; i--)
            {
                if (((g_DeltaTime0 >> 3) + 1) < ABS(angle0))
                {
                    if (angle0 > 0)
                    {
                        chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x400, Q12_SHIFT);
                    }
                    else
                    {
                        chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x400, Q12_SHIFT);
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

        if ((g_SysWork.field_2284[3] & 1) || func_80070320() || ABS(chara->position_18.vy - g_SysWork.playerWork_4C.player_0.position_18.vy) > 0x4CC ||
            ((chara->properties_E4.splitHead.flags_E8 & 4) && Rng_GenerateInt(0, 3)) || (!(chara->properties_E4.splitHead.flags_E8 & 4) && !Rng_GenerateInt(0, 3)))
        {
            if (!(g_SysWork.playerWork_4C.player_0.flags_3E & 8) && mag < 0xE66 && (mag >= 0xB34 || !Rng_GenerateInt(0, 3)) &&
                ABS(angle0) < 0x400 && g_SysWork.playerWork_4C.player_0.health_B0 > 0)
            {
                chara->model_0.state_2   = 5;
                g_SysWork.field_2284[3] |= 2;

                sharedFunc_800D7E04_0_s00(chara, 0x554);

                if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 492 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 505)
                {
                    chara->model_0.anim_4.status_0                       = 0x4B;
                    chara->properties_E4.dummy.properties_E8[5].val16[0] = 0x1D;
                    chara->properties_E4.dummy.properties_E8[5].val16[1] = 0;
                }
                else
                {
                    chara->model_0.anim_4.status_0                       = 0xE;
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
            else if (mag < 0xB33)
            {
                chara->model_0.state_2 = 4;
            }
        }
        else if (!(g_SysWork.playerWork_4C.player_0.flags_3E & 8) && mag < 0x1000 && mag > 0x800 &&
                 ABS(angle0) < 0x2AA && g_SysWork.playerWork_4C.player_0.health_B0 > 0)
        {
            chara->model_0.state_2 = 6;
            xdel_4                 = func_8005BF38(g_SysWork.playerWork_4C.player_0.rotation_24.vy - chara->rotation_24.vy);

            if (ABS(xdel_4) > 0x400)
            {
                chara->model_0.anim_4.status_0 = 0x44;
            }
            else
            {
                chara->model_0.anim_4.status_0 = 0x46;
            }

            chara->properties_E4.dummy.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x1DD;
            g_SysWork.field_2284[3]                             |= 3;
            chara->field_44.field_0                              = 1;
        }
        else if (mag < 0xB33)
        {
            chara->model_0.state_2 = 4;
        }
    }
    else
    {
        if (!(chara->properties_E4.splitHead.flags_E8 & 0x2000))
        {
            Chara_MoveSpeedUpdate3(chara, Q12(0.5f), Q12(0.7f));
        }

        if (chara->properties_E4.player.runTimer_F8 == 0)
        {
            chara->properties_E4.dummy.properties_E8[6].val16[0] = func_8006FAFC(chara, 0x2800, chara->properties_E4.player.field_F0, chara->properties_E4.player.field_F4, 0x1000, 1);

            if (chara->properties_E4.dummy.properties_E8[6].val16[0] == 0x1000)
            {
                chara->properties_E4.dummy.properties_E8[6].val16[0] = chara->rotation_24.vy - 0x800;
            }
        }

        chara->properties_E4.player.runTimer_F8 += g_DeltaTime0;

        if (chara->properties_E4.player.runTimer_F8 > 0x3000 && !Rng_GenerateInt(0, 15))
        {
            chara->properties_E4.player.runTimer_F8 = 0;
        }

        if (chara->properties_E4.splitHead.flags_E8 & 0x1000)
        {
            chara->rotation_24.vy = chara->properties_E4.dummy.properties_E8[6].val16[0];
        }
        else
        {
            xdel_7 = func_8005BF38((chara->properties_E4.dummy.properties_E8[6].val16[0] - chara->rotation_24.vy));

            if ((g_DeltaTime0 >> 3) + 1 < ABS(xdel_7))
            {
                if (xdel_7 > 0)
                {
                    chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x400, Q12_SHIFT);
                }
                else
                {
                    chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x400, Q12_SHIFT);
                }
            }
        }
    }

    if (chara->model_0.anim_4.status_0 == 0x3D && var_fp * 2 < mag)
    {
        temp = SquareRoot0(SQUARE((chara->position_18.vx - chara->properties_E4.player.field_F0) >> 6) +
                           SQUARE((chara->position_18.vz - chara->properties_E4.player.field_F4) >> 6));

        temp2 = (var_s7 >> 1);

        if (temp << 6 < temp2)
        {
            chara->model_0.state_2 = 4;
        }
    }
}