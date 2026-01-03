void sharedFunc_800E33DC_2_s00(s_SubCharacter* arg0)
{
    s_Collision sp10;
    s16         temp_s2;
    s32         temp_s3;
    s32         temp_v0;
    s16         var_s1;
    s32         temp_s4;

    if (arg0->health_B0 > 0)
    {
        Collision_Get(&sp10, arg0->position_18.vx, arg0->position_18.vz);

        if (sp10.field_8 == 0xC && Rng_GenerateInt(0x4000, 0x6FFF) < arg0->position_18.vy)
        {
            arg0->damage_B4.amount_C = 0x3E8000;
        }
    }

    if (arg0->damage_B4.amount_C == 0)
    {
        return;
    }

    if (arg0->health_B0 < 0)
    {
        return;
    }

    temp_s4 = arg0->model_0.controlState_2;

    if (arg0->health_B0 > 0)
    {
        arg0->properties_E4.dummy.properties_E8[9].val8[3] = 4;
    }

    arg0->properties_E4.dummy.properties_E8[3].val32     = g_SysWork.playerWork_4C.player_0.position_18.vx;
    arg0->properties_E4.dummy.properties_E8[4].val32     = g_SysWork.playerWork_4C.player_0.position_18.vz;
    arg0->properties_E4.dummy.properties_E8[0].val16[0] |= 0x80;

    arg0->health_B0 = MAX(arg0->health_B0 - arg0->damage_B4.amount_C, 0);
    temp_s3         = Math_Vector2MagCalc(arg0->damage_B4.position_0.vx, arg0->damage_B4.position_0.vz);

    if (arg0->damage_B4.position_0.vx != 0 || arg0->damage_B4.position_0.vz != 0)
    {
        var_s1 = ratan2(arg0->damage_B4.position_0.vx, arg0->damage_B4.position_0.vz);
    }
    else
    {
        var_s1 = g_SysWork.playerWork_4C.player_0.rotation_24.vy;
    }

    temp_s2 = func_8005BF38(var_s1 - arg0->rotation_24.vy + 0x800);

    arg0->properties_E4.dummy.properties_E8[5].val16[1] = CLAMP_LOW(temp_s3 >> 2, 0x400);

    temp_v0 = FP_TO(arg0->damage_B4.position_0.vy, Q12_SHIFT);

    arg0->headingAngle_3C = var_s1;

    arg0->damage_B4.amount_C                             = 0;
    arg0->damage_B4.position_0.vz                        = 0;
    arg0->damage_B4.position_0.vy                        = 0;
    arg0->damage_B4.position_0.vx                        = 0;
    arg0->properties_E4.dummy.properties_E8[0].val16[0] |= 2;
    arg0->moveSpeed_38                                   = FP_TO(temp_s3, Q12_SHIFT) / 4915;
    arg0->field_34                                      += temp_v0 / 4915;

    if (arg0->properties_E4.dummy.properties_E8[0].val16[0] & 8)
    {
        arg0->properties_E4.dummy.properties_E8[5].val16[1] = 0;

        if (arg0->health_B0 != 0)
        {
            if (arg0->model_0.anim_4.status_0 >> 1 == 4)
            {
                if (arg0->model_0.anim_4.status_0 != 9)
                {
                    arg0->properties_E4.dummy.properties_E8[6].val16[0] = 0;
                }
                else
                {
                    arg0->properties_E4.dummy.properties_E8[6].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x4E;
                }
                arg0->model_0.anim_4.status_0 = 0x2A;
            }
            else if (arg0->model_0.anim_4.status_0 >> 1 == 8)
            {
                if (arg0->model_0.anim_4.status_0 != 0x11)
                {
                    arg0->properties_E4.dummy.properties_E8[6].val16[0] = 0;
                }
                else
                {
                    arg0->properties_E4.dummy.properties_E8[6].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0xA5;
                }
                arg0->model_0.anim_4.status_0 = 0x2C;
            }
            else if (arg0->model_0.anim_4.status_0 >> 1 == 14)
            {
                if (arg0->model_0.anim_4.status_0 != 0x1D)
                {
                    arg0->properties_E4.dummy.properties_E8[6].val16[0] = 0;
                }
                else
                {
                    arg0->properties_E4.dummy.properties_E8[6].val16[0] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x13F;
                }
                arg0->model_0.anim_4.status_0 = 0x2E;
            }
        }
    }
    else if (arg0->health_B0 > 0x64000)
    {
        if (!(arg0->properties_E4.dummy.properties_E8[0].val16[0] & 0x400))
        {
            if (ABS(temp_s2) < 0x200)
            {
                if ((arg0->model_0.anim_4.status_0 >> 1) != 2)
                {
                    arg0->model_0.anim_4.status_0 = 4;
                }
            }
            else
            {
                if (temp_s2 > 0)
                {
                    if ((arg0->model_0.anim_4.status_0 >> 1) != 6)
                    {
                        arg0->model_0.anim_4.status_0 = 0xC;
                    }
                }
                else if ((arg0->model_0.anim_4.status_0 >> 1) != 0xC)
                {
                    arg0->model_0.anim_4.status_0 = 0x18;
                }
            }
            arg0->model_0.controlState_2 = 5;
        }
    }
    else
    {
        func_80037DC4(arg0);

        arg0->flags_3E                                      |= 2;
        arg0->properties_E4.dummy.properties_E8[0].val16[0] |= 0x1008;

        if (ABS(temp_s2) < 0x200)
        {
            arg0->model_0.anim_4.status_0 = 6;
            arg0->model_0.controlState_2  = 6;
        }
        else if (temp_s2 > 0)
        {
            arg0->model_0.anim_4.status_0 = 0xE;
            arg0->model_0.controlState_2  = 7;
        }
        else
        {
            arg0->model_0.anim_4.status_0 = 0x1A;
            arg0->model_0.controlState_2  = 8;
        }
    }

    if (temp_s4 != arg0->model_0.controlState_2 && temp_s4 == 3)
    {
        g_SysWork.field_2284[3] &= 0xFFFD;
    }
}