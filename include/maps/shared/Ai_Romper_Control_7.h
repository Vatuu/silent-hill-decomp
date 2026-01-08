void Ai_Romper_Control_7(s_SubCharacter* romper)
{
    s16 temp_s0;

    if (romper->properties_E4.romper.flags_E8 & 1)
    {
        Chara_MoveSpeedUpdate(romper, Q12_MULT_PRECISE(romper->moveSpeed_38, 0x3000) + 0x3000);
    }
    else
    {
        romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, 0xF000), 0);
    }

    if (romper->model_0.anim_4.status_0 == 22 || (FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) > 92 &&
                                                    FP_FROM(romper->model_0.anim_4.time_4, Q12_SHIFT) < 97))
    {
        temp_s0 = Q12_MULT_PRECISE(sharedData_800ECACC_2_s02, g_DeltaTime0) * 0x1666 / 0x7000;

        romper->properties_E4.romper.field_F8 = Q12_MULT(temp_s0, Math_Sin(romper->rotation_24.vy));
        romper->properties_E4.romper.field_FA = Q12_MULT(temp_s0, Math_Cos(romper->rotation_24.vy));
    }

    if ((romper->model_0.anim_4.status_0 >> 1) == 10)
    {
        romper->flags_3E |= 2;
    }

    if (romper->health_B0 == Q12(0.0f) && romper->model_0.anim_4.status_0 == 21)
    {
        romper->model_0.controlState_2  = 8;
        romper->model_0.anim_4.status_0 = 12;
        romper->flags_3E               &= 0xFFFD;

        func_80037DC4(romper);
    }
}
