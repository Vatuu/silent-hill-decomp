void sharedFunc_800DA900_2_s00(s_SubCharacter* arg0)
{
    s32           sp10;
    s32           temp_s0;
    s32           temp_s0_2;
    s32           temp_s0_4;
    s32           temp_s3;
    s32           temp_s5;
    s32           temp_v0;
    s32           temp_v1_2;
    s32           var_s4;
    s32           temp_s7;
    s32           var_v0_2;
    bool          new_var;
    s32           temp_s6;
    s_PlayerWork* player;

    temp_s7 = arg0->model_0.anim_4.status_0;
    var_s4  = 0;

    temp_v0 = sharedFunc_800D4A80_0_s01(arg0);

    new_var = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_s0 = sharedData_800E21D0_0_s01.distance_150;
    sp10    = new_var;

    temp_s3 = sharedFunc_800DC438_2_s00(arg0);
    temp_s6 = sharedFunc_800DEE24_2_s00(arg0);

    switch (arg0->model_0.stateStep_3)
    {
        case 0:
            temp_s0_2 = temp_s0 + (Rng_RandQ12() * 4);

            if (!sharedFunc_800DC30C_2_s00(arg0) || temp_s0_2 >= 0x3000 || Rng_RandQ12() >= 0x333)
            {
                arg0->model_0.stateStep_3 = 1;
            }
            else
            {
                arg0->model_0.stateStep_3 = 4;
            }
            arg0->properties_E4.dummy.properties_E8[0xE].val32 = 0x4000;
            break;

        case 1:
            temp_s5   = arg0->properties_E4.dummy.properties_E8[5].val32 - arg0->position_18.vy;
            temp_s0_4 = Math_Distance2dGet(&arg0->position_18, (VECTOR3*)&arg0->properties_E4.dummy.properties_E8[4]);
            temp_v1_2 = FP_ANGLE_NORM_S(func_80080478(&arg0->position_18, (VECTOR3*)&arg0->properties_E4.dummy.properties_E8[4]) - arg0->rotation_24.vy);

            if (temp_s3 == 2)
            {
                arg0->model_0.stateStep_3 = temp_s3;
            }
            else if (temp_s3 == 1)
            {
                arg0->model_0.stateStep_3 = 4;
            }
            else if ((temp_s5 >= -0x333 && temp_s5 <= 0x333) && (temp_s6 > 0x599 && temp_s6 < 0x8CD) &&
                     (temp_v1_2 >= -0x80 && temp_v1_2 <= 0x80))
            {
                var_s4 = 1;
            }
            else
            {
                // @hack This check should be `if ((temp_v1_2 >= -0x400 && temp_v1_2 < 0x400) && temp_s0_4 < 0x4000)`,
                if (Math_CheckSignedRange(temp_v1_2, 0x400) && (temp_s0_4 < 0x4000))
                {
                    var_s4 = 2;
                }
                else if (arg0->properties_E4.dummy.properties_E8[0xE].val32 == 0)
                {
                    arg0->model_0.stateStep_3 = 0;
                }
            }
            break;

        case 2:
            if (temp_s7 == 0x23)
            {
                var_s4                        = 3;
                arg0->model_0.anim_4.status_0 = 0x20;
                arg0->model_0.stateStep_3     = 3;
            }
            break;

        case 3:
            var_s4 = 3;
            break;

        case 4:
            if (temp_s7 == 0x23)
            {
                var_s4                        = 4;
                arg0->model_0.anim_4.status_0 = 0x1E;
                arg0->model_0.stateStep_3     = 5;
            }
            break;

        case 5:
            var_s4 = 4;
            break;
    }

    sharedFunc_800E021C_2_s00(arg0, 2, 0);

    switch (Ai_AirScreamer_DamageTake(arg0, 0x1000))
    {
        case 0:
            switch (var_s4)
            {
                case 0:
                case 2:
                    if (!sharedFunc_800DC67C_2_s00(arg0))
                    {
                        var_v0_2 = 0x29;
                        if (sp10 != 0)
                        {
                            if (var_s4 == 2)
                            {
                                arg0->model_0.controlState_2 = 0x27;
                                arg0->model_0.stateStep_3    = 0;
                            }
                            break;
                        }
                    }
                    else
                    {
                        var_v0_2 = 0x2A;
                    }

                    arg0->model_0.controlState_2 = var_v0_2;
                    arg0->model_0.stateStep_3    = 0;
                    break;

                case 1:
                    player = &g_SysWork.playerWork_4C;

                    if (!((u16)player->player_0.flags_3E & 8) &&
                        (g_SysWork.npcIdxs_2354[0] == -1 && g_SysWork.npcIdxs_2354[1] == -1) && (temp_s7 == 0x23))
                    {
                        arg0->model_0.controlState_2 = 0x28;
                        arg0->model_0.stateStep_3    = 0;
                    }
                    break;

                case 3:
                    if (temp_v0 == 1)
                    {
                        sharedFunc_800DE11C_2_s00(arg0);
                        arg0->model_0.controlState_2 = 0xA;
                        arg0->model_0.stateStep_3    = 0;
                    }
                    break;

                case 4:
                    if (temp_v0 == 2)
                    {
                        arg0->model_0.controlState_2 = 0x17;
                        arg0->model_0.stateStep_3    = 0;
                    }
                    break;
            }
            break;

        case 1:
        case 2:
            arg0->model_0.controlState_2                        = 0x2C;
            arg0->model_0.stateStep_3                           = 0;
            arg0->properties_E4.dummy.properties_E8[0xD].val32 |= 8;
            break;

        case 3:
        case 4:
            arg0->model_0.controlState_2 = 0x2D;
            arg0->model_0.stateStep_3    = 0;
            if (arg0->health_B0 <= 0)
            {
                arg0->properties_E4.dummy.properties_E8[0xD].val32 |= 0x40;
            }
            else
            {
                arg0->properties_E4.dummy.properties_E8[0xD].val32 |= 8;
            }
            break;
    }
}