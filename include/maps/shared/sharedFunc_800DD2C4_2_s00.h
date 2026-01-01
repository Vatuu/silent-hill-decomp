void sharedFunc_800DD2C4_2_s00(s_SubCharacter* arg0, s32 arg1, s32 arg2)
{
    s32 temp_fp;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s7;
    s32 var_s4;
    s32 i;
    s32 var_s6;
    s32 var_v0;

    temp_s2 = arg0->position_18.vx;
    temp_s1 = arg0->position_18.vz;
    temp_s7 = g_SysWork.playerWork_4C.player_0.position_18.vx;
    temp_fp = g_SysWork.playerWork_4C.player_0.position_18.vz;

    var_v0 = FP_ANGLE_NORM_S(arg0->rotation_24.vy - ratan2(temp_s2 - temp_s7, temp_s1 - temp_fp));
    var_s4 = arg0->rotation_24.vy + 0x800;
    var_s6 = var_v0 > 0;
    var_s6 = arg2 != var_s6 ? 0x200 : -0x200;

    arg0->properties_E4.unk0.field_F8.vx = temp_s7;
    arg0->properties_E4.unk0.field_F8.vz = temp_fp;

    for (i = 8; i > 0; i--, var_s4 += var_s6)
    {
        temp_s0 = FP_MULTIPLY_PRECISE(Rng_RandQ12(), 0x6000, Q12_SHIFT) + 0x13000;
        temp_s2 = temp_s7 + FP_MULTIPLY_PRECISE(temp_s0, Math_Sin(var_s4), Q12_SHIFT);
        temp_s1 = temp_fp + FP_MULTIPLY_PRECISE(temp_s0, Math_Cos(var_s4), Q12_SHIFT);

        var_v0 = Collision_GroundHeightGet(temp_s2, temp_s1);
        var_v0 = MIN(var_v0, 0);

        arg0->position_18.vy                 = var_v0 + arg1;
        arg0->position_18.vx                 = temp_s2;
        arg0->position_18.vz                 = temp_s1;
        arg0->properties_E4.unk0.field_F8.vy = arg0->position_18.vy;

        if (func_8008F914(temp_s2, temp_s1) && func_800808AC(temp_s2, temp_s1) &&
            sharedFunc_800D4AEC_0_s01(arg0, NULL, &arg0->properties_E4.unk0.field_F8, NULL))
        {
            break;
        }
    }

    if (i == 0)
    {
        arg0->position_18.vx = temp_s7 + 0x32000;
        arg0->position_18.vy = sharedFunc_800D5274_0_s01() * 2;
        arg0->position_18.vz = temp_fp + 0x32000;
    }
}