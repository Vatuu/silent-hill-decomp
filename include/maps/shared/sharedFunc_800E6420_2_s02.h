void sharedFunc_800E6420_2_s02(s_SubCharacter* romper)
{
    s_Collision coll;
    s32         temp_v1_3;
    s32         var_a1;
    s32         prevControlState;

    if (romper->health_B0 > Q12(0.0f))
    {
        Collision_Get(&coll, romper->position_18.vx, romper->position_18.vz);

        if (coll.field_8 == 12)
        {
            if (Rng_GenerateInt(0x4000, 0x7FFF) < romper->position_18.vy)
            {
                romper->damage_B4.amount_C = 0xBB8000;
            }
        }
    }

    if (romper->damage_B4.amount_C == Q12(0.0f) || romper->health_B0 <= Q12(0.0f))
    {
        romper->damage_B4.amount_C      = Q12(0.0f);
        romper->damage_B4.position_0.vz = Q12(0.0f);
        romper->damage_B4.position_0.vy = Q12(0.0f);
        romper->damage_B4.position_0.vx = Q12(0.0f);
        return;
    }

    prevControlState = romper->model_0.controlState_2;

    romper->health_B0 = MAX(romper->health_B0 - romper->damage_B4.amount_C, Q12(0.0f));
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
                temp_v1_3 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 109;

                if (temp_v1_3 > 0)
                {
                    if (temp_v1_3 < 7)
                    {
                        romper->model_0.anim_4.status_0 = 37;
                    }
                    else if (temp_v1_3 < 11)
                    {
                        romper->model_0.anim_4.status_0 = 16;
                    }
                    else if (temp_v1_3 > 17)
                    {
                        romper->model_0.anim_4.status_0 = 14;
                    }
                    else
                    {
                        romper->model_0.anim_4.status_0 = 35;
                    }
                }
                else
                {
                    romper->model_0.anim_4.status_0 = 14;
                }

                if (!(romper->model_0.anim_4.status_0 & 0x1))
                {
                    romper->model_0.controlState_2 = 6;
                }
                break;

            case 30:
                romper->model_0.anim_4.time_4 = 0x93000;

            case 31:
                temp_v1_3 = FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) - 147;

                if (temp_v1_3 < 2)
                {
                    romper->model_0.anim_4.status_0 = 14;
                }
                else if (temp_v1_3 >= 10)
                {
                    romper->model_0.anim_4.status_0 = 14;
                }
                else
                {
                    romper->model_0.anim_4.status_0 = 16;
                }

                romper->model_0.controlState_2 = 6;
                break;

            case 24:
            case 25:
            case 28:
            case 29:
                romper->model_0.controlState_2  = 6;
                romper->model_0.anim_4.status_0 = 14;
                break;
        }
    }
    else if (!(romper->properties_E4.romper.field_E8 & 4))
    {
        romper->model_0.controlState_2         = 7;
        romper->model_0.anim_4.status_0        = 22;
        romper->properties_E4.romper.field_E8 |= 4;
    }

    romper->properties_E4.romper.field_10E    = 0;
    romper->properties_E4.romper.rotationY_F2 = 0x1000;
    romper->damage_B4.amount_C                = Q12(0.0f);
    romper->damage_B4.position_0.vz           = Q12(0.0f);
    romper->damage_B4.position_0.vy           = Q12(0.0f);
    romper->damage_B4.position_0.vx           = Q12(0.0f);

    if (prevControlState != romper->model_0.controlState_2)
    {
        if (romper->properties_E4.romper.field_E8 & 0x800)
        {
            romper->properties_E4.romper.field_E8 &= ~0x800;
            g_SysWork.field_2284[3]               &= 0xFFFC;
        }
    }
}
