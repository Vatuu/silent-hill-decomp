void sharedFunc_800D3EF4_0_s00(s_SubCharacter* chara)
{
    s16 temp_v0_4;
    s16 var_s1;
    s32 temp_s4;
    s32 i;

    temp_s4   = SquareRoot0(SQUARE((sharedData_800E3A18_0_s00 - chara->position_18.vx) >> 6) + SQUARE((sharedData_800E3A1C_0_s00 - chara->position_18.vz) >> 6));
    temp_s4 <<= 6;
    var_s1    = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - chara->position_18.vx, sharedData_800E3A1C_0_s00 - chara->position_18.vz) - chara->rotation_24.vy);

    if (temp_s4 > 0x8000 && (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 1) && !(g_SysWork.flags_22A4 & 0x80))
    {
        if (!Vw_AabbVisibleInScreenCheck(chara->position_18.vx - 0x1000, chara->position_18.vx + 0x1000, chara->position_18.vy - 0x1CCC, chara->position_18.vy, chara->position_18.vz - 0x1000, chara->position_18.vz - 0x1000))
        {
            chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 0x1000;
        }
    }

    if (chara->model_0.anim_4.status_0 == 0x3D && !func_800700F8(chara, &g_SysWork.player_4C.chara_0))
    {
        chara->properties_E4.player.runTimer_F8 = 0;

        if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x1000)
        {
            chara->rotation_24.vy = ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);
        }
        else
        {
            if (ABS(var_s1) > 0x400)
            {
                Chara_MoveSpeedUpdate(chara, 0x1800);
            }
            else
            {
                Chara_MoveSpeedUpdate3(chara, 0x800, (0x400 - ABS(var_s1)) * 4);
            }
        }

        for (i = 3 + (ABS(var_s1) > 0x400 ? 1 : 0); i > 0; i--)
        {
            if ((g_DeltaTime0 >> 2) + 1 < ABS(var_s1))
            {
                if (var_s1 > 0)
                {
                    chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x800, Q12_SHIFT);
                }
                else
                {
                    chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x800, Q12_SHIFT);
                }

                var_s1 = func_8005BF38(ratan2(sharedData_800E3A18_0_s00 - chara->position_18.vx, sharedData_800E3A1C_0_s00 - chara->position_18.vz) - chara->rotation_24.vy);
            }

            if (ABS(var_s1) < (g_DeltaTime0 >> 2) + 1 || temp_s4 > 0x2000)
            {
                break;
            }
        }

        if ((g_SysWork.field_2284[3] & 1) ||
            ((chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 4) && Rng_TestProbabilityBits(2)) ||
            (!(chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 4) && Rng_TestProbabilityBits(1)))
        {
            if (temp_s4 < 0xE66)
            {
                if (temp_s4 > 0xB33 || !Rng_TestProbabilityBits(2))
                {
                    if (ABS(var_s1) < 0x400)
                    {
                        if (g_SysWork.player_4C.chara_0.health_B0 > 0)
                        {
                            chara->model_0.state_2   = 5;
                            g_SysWork.field_2284[3] |= 2;

                            sharedFunc_800D7E04_0_s00(chara, 0x554);

                            if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x1EC && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x1F9)
                            {
                                chara->model_0.anim_4.status_0                               = 0x4B;
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = 0x1D;
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 0;
                                return;
                            }

                            chara->model_0.anim_4.status_0 = 0xE;

                            chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x1DD;

                            if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x1DD && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x1E2)
                            {
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 1;
                            }
                            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x1E1 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x1E8)
                            {
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 2;
                            }
                            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x1E7 && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x1EB)
                            {
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 3;
                            }
                            else if (FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) > 0x1EA && FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) < 0x1ED)
                            {
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 4;
                            }
                            else
                            {
                                chara->properties_E4.larvalStalker.properties_E8[5].val16[1] = 0;
                            }
                            return;
                        }
                    }
                }
            }
        }
        else if (temp_s4 > 0x800 && temp_s4 < 0x1000)
        {
            if (ABS(var_s1) < 0x2AA)
            {
                if (g_SysWork.player_4C.chara_0.health_B0 > 0)
                {
                    chara->model_0.state_2 = 6;
                    temp_v0_4              = func_8005BF38(g_SysWork.player_4C.chara_0.rotation_24.vy - chara->rotation_24.vy);

                    if (ABS(temp_v0_4) > 0x400)
                    {
                        chara->model_0.anim_4.status_0 = 0x44;
                    }
                    else
                    {
                        chara->model_0.anim_4.status_0 = 0x46;
                    }

                    chara->properties_E4.larvalStalker.properties_E8[5].val16[0] = FP_FROM(chara->model_0.anim_4.time_4, Q12_SHIFT) - 0x1DD;
                    g_SysWork.field_2284[3]                                     |= 3;
                    return;
                }
            }
        }

        if (temp_s4 < 0xB33)
        {
            chara->model_0.state_2 = 4;
        }
    }
    else
    {
        Chara_MoveSpeedUpdate3(chara, 0x800, 0x1000);

        if (chara->properties_E4.player.runTimer_F8 == 0)
        {
            chara->properties_E4.larvalStalker.properties_E8[6].val16[0] = func_8006FAFC(chara, 0x2000, g_SysWork.player_4C.chara_0.position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz, 0x1000, 1);

            if (chara->properties_E4.larvalStalker.properties_E8[6].val16[0] == 0x1000)
            {
                chara->properties_E4.larvalStalker.properties_E8[6].val16[0] = chara->rotation_24.vy - 0x800;
            }
        }

        chara->properties_E4.player.runTimer_F8 += g_DeltaTime0;

        if ((chara->properties_E4.player.runTimer_F8 > 0x2800) && !Rng_TestProbabilityBits(4))
        {
            chara->properties_E4.player.runTimer_F8 = 0;
        }

        if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & 0x1000)
        {
            chara->rotation_24.vy = chara->properties_E4.larvalStalker.properties_E8[6].val16[0];
        }
        else
        {
            temp_v0_4 = func_8005BF38(chara->properties_E4.larvalStalker.properties_E8[6].val16[0] - chara->rotation_24.vy);

            if ((g_DeltaTime0 >> 2) + 1 < ABS(temp_v0_4))
            {
                if (temp_v0_4 > 0)
                {
                    chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x800, Q12_SHIFT);
                }
                else
                {
                    chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, 0x800, Q12_SHIFT);
                }
            }
        }
    }
}
