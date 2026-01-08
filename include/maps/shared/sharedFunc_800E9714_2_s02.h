void sharedFunc_800E9714_2_s02(s_SubCharacter* romper)
{
    s32 sp10;
    s32 sp14;
    s16 sp18;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_s0;

    temp_s3   = romper->moveSpeed_38;
    var_s0    = 0x8000;
    temp_v0   = FP_TO(temp_s3, Q12_SHIFT) / var_s0;
    temp_v0_4 = temp_s3 - Q12_MULT_PRECISE(temp_v0, 0x4000);
    sp18      = romper->rotation_24.vy;
    temp_v0_5 = Q12_MULT_PRECISE(temp_v0_4, temp_v0);

    if (temp_v0_5 >= Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                         g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz))
    {
        sp10 = romper->position_18.vx + Q12_MULT(temp_v0_5, Math_Sin(sp18));
        sp14 = romper->position_18.vz + Q12_MULT(temp_v0_5, Math_Cos(sp18));
    }
    else
    {
        sp10 = g_SysWork.playerWork_4C.player_0.position_18.vx;
        sp14 = g_SysWork.playerWork_4C.player_0.position_18.vz;
    }

    sharedFunc_800D2E9C_0_s00(&sp10, &sp14, &sp18);

    temp_v0 = (FP_TO(Math_Vector2MagCalc(sp10 - romper->position_18.vx, sp14 - romper->position_18.vz), Q12_SHIFT) << 1) / temp_s3;
    var_s0  = FP_TO(temp_s3, Q12_SHIFT) / temp_v0;

    if (var_s0 < 0)
    {
        var_s0 = 0x4000;
    }

    if (var_s0 > 0x20000)
    {
        var_s0 = 0x20000;
    }

    romper->properties_E4.romper.rotationY_F2  = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - romper->position_18.vx,
                                                        g_SysWork.playerWork_4C.player_0.position_18.vz - romper->position_18.vz);
    romper->properties_E4.romper.field_124     = var_s0;
    romper->properties_E4.romper.positionX_FC  = sp10;
    romper->properties_E4.romper.positionZ_100 = sp14;
}