void Ai_Romper_Control_6(s_SubCharacter* romper)
{
    s16 temp_s0;

    romper->moveSpeed_38 = MAX(romper->moveSpeed_38 - Q12_MULT_PRECISE(g_DeltaTime0, 0xF000), 0);

    if ((romper->model_0.anim_4.status_0 >> 1) == 7 || (romper->model_0.anim_4.status_0 >> 1) == 8)
    {
        temp_s0                               = Q12_MULT_PRECISE(sharedData_800ECA4C_2_s02, g_DeltaTime0) * 0x999 / 0xA000;
        romper->properties_E4.romper.field_F8 = Q12_MULT(temp_s0, Math_Sin(romper->rotation_24.vy));
        romper->properties_E4.romper.field_FA = Q12_MULT(temp_s0, Math_Cos(romper->rotation_24.vy));
    }
}
