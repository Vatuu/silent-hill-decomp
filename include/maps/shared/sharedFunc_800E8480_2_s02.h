void sharedFunc_800E8480_2_s02(s_SubCharacter* romper)
{
    VECTOR          sp10;
    s_SubCharacter* player;

    if (romper->position_18.vx != romper->properties_E4.romper.positionX_FC ||
        romper->position_18.vz != romper->properties_E4.romper.positionZ_100)
    {
        romper->properties_E4.romper.rotationY_F2 = ratan2(romper->properties_E4.romper.positionX_FC - romper->position_18.vx,
                                                           romper->properties_E4.romper.positionZ_100 - romper->position_18.vz);
    }

    if (romper->model_0.anim_4.status_0 == 0xB)
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, romper->properties_E4.romper.field_124 * 4), 0);
    }
    else
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, romper->properties_E4.romper.field_124), 0);
    }

    romper->field_E1_0 = 0;

    if (romper->model_0.anim_4.status_0 == 0xB)
    {
        romper->properties_E4.romper.field_104 = romper->model_0.anim_4.time_4 - 0x14000;
    }
    else
    {
        romper->properties_E4.romper.field_104 = 0;
    }

    player = &g_SysWork.playerWork_4C.player_0;

    if (player->attackReceived_41 == -1)
    {
        romper->model_0.anim_4.status_0 = 0x12;
        romper->model_0.controlState_2  = 0xB;
        romper->field_E1_0              = 0;
        romper->field_E1_0              = 3;
    }
    else if (romper->model_0.anim_4.time_4 <= 0x17FFF)
    {
        romper->properties_E4.romper.flags_E8 |= 0x40;
    }
    else if (romper->properties_E4.romper.flags_E8 & 0x40)
    {
        romper->properties_E4.romper.flags_E8 &= ~0x40;

        g_SysWork.playerWork_4C.player_0.damage_B4.amount_C += FP_TO(D_800AD4C8[55].field_4, Q12_SHIFT) *
                                                               (Rng_TestProbabilityBits(5) + 0x55) / 100;

        sp10.vx = romper->position_18.vx + FP_FROM(FP_TO(Math_Sin(romper->rotation_24.vy) >> 1, Q12_SHIFT), Q12_SHIFT);
        sp10.vy = romper->position_18.vy - 0x199;
        sp10.vz = romper->position_18.vz + FP_FROM(FP_TO(Math_Cos(romper->rotation_24.vy) >> 1, Q12_SHIFT), Q12_SHIFT);

        func_8005F6B0(&g_SysWork.playerWork_4C.player_0, &sp10, 4, 9);

        romper->properties_E4.romper.field_11A = 1;
    }
}