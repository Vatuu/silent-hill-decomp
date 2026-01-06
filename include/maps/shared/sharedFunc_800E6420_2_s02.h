void sharedFunc_800E6420_2_s02(s_SubCharacter* romper)
{
    s_Collision sp10;
    s32         temp_v1_3;
    s32         var_a1;
    s32         temp_s1;

    if (romper->health_B0 > 0)
    {
        Collision_Get(&sp10, romper->position_18.vx, romper->position_18.vz);

        if (sp10.field_8 == 0xC)
        {
            if (Rng_GenerateInt(0x4000, 0x7FFF) < romper->position_18.vy)
            {
                romper->damage_B4.amount_C = 0xBB8000;
            }
        }
    }

    if (romper->damage_B4.amount_C == 0 || romper->health_B0 <= 0)
    {
        romper->damage_B4.amount_C      = 0;
        romper->damage_B4.position_0.vz = 0;
        romper->damage_B4.position_0.vy = 0;
        romper->damage_B4.position_0.vx = 0;
        return;
    }

    temp_s1 = romper->model_0.controlState_2;

    romper->health_B0 = MAX(romper->health_B0 - romper->damage_B4.amount_C, 0);

    romper->properties_E4.romper.field_E8 |= 0x80;

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
    {
        var_a1 = 0x190000;
    }
    else
    {
        var_a1 = 0xC8000;
    }

    if (var_a1 < romper->health_B0)
    {
        romper->properties_E4.romper.positionX_FC = g_SysWork.playerWork_4C.player_0.position_18.vx;

        romper->properties_E4.romper.positionZ_100 = g_SysWork.playerWork_4C.player_0.position_18.vz;
        romper->properties_E4.romper.field_10E     = 0;

        romper->properties_E4.romper.rotationY_F2 = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                                           g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz);

        switch (romper->model_0.anim_4.status_0)
        {
            case 26:
                romper->model_0.anim_4.time_4 = 0x6D000;

            case 27:
                temp_v1_3 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x6D;

                if (temp_v1_3 > 0)
                {
                    if (temp_v1_3 < 7)
                    {
                        romper->model_0.anim_4.status_0 = 0x25;
                    }
                    else if (temp_v1_3 < 0xB)
                    {
                        romper->model_0.anim_4.status_0 = 0x10;
                    }
                    else if (temp_v1_3 > 0x11)
                    {
                        romper->model_0.anim_4.status_0 = 0xE;
                    }
                    else
                    {
                        romper->model_0.anim_4.status_0 = 0x23;
                    }
                }
                else
                {
                    romper->model_0.anim_4.status_0 = 0xE;
                }

                if (!(romper->model_0.anim_4.status_0 & 1))
                {
                    romper->model_0.controlState_2 = 6;
                }
                break;

            case 30:
                romper->model_0.anim_4.time_4 = 0x93000;

            case 31:
                temp_v1_3 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 0x93;

                if (temp_v1_3 < 2)
                {
                    romper->model_0.anim_4.status_0 = 0xE;
                }
                else if (temp_v1_3 >= 0xA)
                {
                    romper->model_0.anim_4.status_0 = 0xE;
                }
                else
                {
                    romper->model_0.anim_4.status_0 = 0x10;
                }

                romper->model_0.controlState_2 = 6;
                break;

            case 24:
            case 25:
            case 28:
            case 29:
                romper->model_0.controlState_2  = 6;
                romper->model_0.anim_4.status_0 = 0xE;
                break;
        }
    }
    else if (!(romper->properties_E4.romper.field_E8 & 4))
    {
        romper->model_0.controlState_2         = 7;
        romper->model_0.anim_4.status_0        = 0x16;
        romper->properties_E4.romper.field_E8 |= 4;
    }

    romper->properties_E4.romper.field_10E    = 0;
    romper->properties_E4.romper.rotationY_F2 = 0x1000;
    romper->damage_B4.amount_C                = 0;
    romper->damage_B4.position_0.vz           = 0;
    romper->damage_B4.position_0.vy           = 0;
    romper->damage_B4.position_0.vx           = 0;

    if (temp_s1 != romper->model_0.controlState_2)
    {
        if (romper->properties_E4.romper.field_E8 & 0x800)
        {
            romper->properties_E4.romper.field_E8 &= ~0x800;
            g_SysWork.field_2284[3]               &= 0xFFFC;
        }
    }
}