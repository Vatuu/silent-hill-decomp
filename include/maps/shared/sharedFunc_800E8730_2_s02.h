void sharedFunc_800E8730_2_s02(s_SubCharacter* romper)
{
    s_800C4590 sp10;
    VECTOR3    sp30;
    s16        temp_s4;
    s32        temp_s0;
    s32        temp_s2;
    s32        temp_s3;
    s32        temp_v0;

    romper->field_34 += g_DeltaTime2;

    if ((romper->model_0.anim_4.status_0 >> 1) == 3 || (romper->model_0.anim_4.status_0 >> 1) == 5)
    {
        romper->headingAngle_3C = romper->properties_E4.romper.rotationY_F2;
    }
    else
    {
        romper->headingAngle_3C = romper->rotation_24.vy;
    }

    if (g_DeltaTime0 != 0)
    {
        temp_s4 = romper->headingAngle_3C;
        temp_s0 = Q12_MULT_PRECISE(g_DeltaTime0, romper->moveSpeed_38);
        temp_s2 = (temp_s0 < -0x7FFF || temp_s0 > 0x7FFF) * 4;
        temp_v0 = Math_Sin(temp_s4);
        temp_s3 = temp_s2 >> 1;
        temp_s0 = temp_s0 >> temp_s3;

        sp30.vx = Q12_MULT_PRECISE(temp_s0, temp_v0 >> temp_s3) << temp_s2;
        sp30.vz = Q12_MULT_PRECISE(temp_s0, Math_Cos(temp_s4) >> temp_s3) << temp_s2;
        sp30.vy = Q12_MULT_PRECISE(g_DeltaTime0, romper->field_34);

        sp30.vx += romper->properties_E4.romper.field_F8;
        sp30.vz += romper->properties_E4.romper.field_FA;

        func_80069B24(&sp10, &sp30, romper);

        romper->position_18.vx += sp10.offset_0.vx;
        romper->position_18.vz += sp10.offset_0.vz;

        if (romper->properties_E4.romper.flags_E8 & 0x400)
        {
            if (romper->model_0.controlState_2 != 0xA && romper->position_18.vy <= sp10.field_C)
            {
                romper->properties_E4.romper.flags_E8 &= ~0x400;
            }

            if (romper->properties_E4.romper.flags_E8 & 0x400)
            {
                if (romper->model_0.controlState_2 == 0xA)
                {
                    romper->position_18.vy += sp10.offset_0.vy;

                    if (g_SysWork.playerWork_4C.player_0.position_18.vy < romper->position_18.vy)
                    {
                        romper->position_18.vy = g_SysWork.playerWork_4C.player_0.position_18.vy;
                        romper->field_34       = 0;
                    }
                }
                else
                {
                    romper->position_18.vy -= Q12_MULT_PRECISE(g_DeltaTime0, 0x266);
                    romper->field_34        = 0;

                    if (sp10.field_C >= romper->position_18.vy)
                    {
                        romper->position_18.vy = sp10.field_C;
                    }
                }
            }
            else
            {
                romper->position_18.vy += sp10.offset_0.vy;

                if (sp10.field_C < romper->position_18.vy)
                {
                    romper->position_18.vy = sp10.field_C;
                    romper->field_34       = 0;
                }
            }
        }
        else
        {
            romper->position_18.vy += sp10.offset_0.vy;

            if (sp10.field_C < romper->position_18.vy)
            {
                romper->position_18.vy = sp10.field_C;
                romper->field_34       = 0;
            }
        }

        romper->properties_E4.romper.field_FA = 0;
        romper->properties_E4.romper.field_F8 = 0;
    }

    romper->rotation_24.vy = func_8005BF38(romper->rotation_24.vy);

    if (romper->field_34 != 0)
    {
        romper->properties_E4.romper.flags_E8 |= 1;
    }
    else
    {
        romper->properties_E4.romper.flags_E8 &= ~1;
    }
}