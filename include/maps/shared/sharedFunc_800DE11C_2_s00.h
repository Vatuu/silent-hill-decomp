void sharedFunc_800DE11C_2_s00(s_SubCharacter* chara)
{
    s32    pcX;
    s32    pcZ;
    q19_12 pcX_2;
    q19_12 pcY_2;
    q19_12 pcZ_2;
    q19_12 angle0;
    s32    field_D4;

    pcX      = g_SysWork.playerWork_4C.player_0.position_18.vx;
    pcZ      = g_SysWork.playerWork_4C.player_0.position_18.vz;
    field_D4 = g_SysWork.playerWork_4C.player_0.field_D4.field_0;

    angle0 = ratan2(chara->position_18.vx - g_SysWork.playerWork_4C.player_0.position_18.vx,
                    chara->position_18.vz - g_SysWork.playerWork_4C.player_0.position_18.vz);
    pcX_2  = pcX + FP_MULTIPLY_PRECISE(field_D4, Math_Sin(angle0), Q12_SHIFT);
    pcZ_2  = pcZ + FP_MULTIPLY_PRECISE(field_D4, Math_Cos(angle0), Q12_SHIFT);

    pcY_2                                 = func_80080884(pcX_2, pcZ_2);
    chara->properties_E4.unk0.field_F8.vx = pcX_2;
    chara->properties_E4.unk0.field_F8.vy = pcY_2;
    chara->properties_E4.unk0.field_F8.vz = pcZ_2;

    sharedFunc_800D4E84_0_s01(chara);
}
