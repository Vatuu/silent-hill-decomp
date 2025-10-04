s32 sharedFunc_800D3630_0_s01(s_SubCharacter* chara, s32* arg1)
{
    s32    ret;
    q19_12 angle;
    q19_12 offsetX;
    q19_12 offsetZ;
    q19_12 offset;

    offset = sharedFunc_800D3814_0_s01(chara);
    if (arg1 != NULL)
    {
        *arg1 = offset;
    }

    ret = sharedFunc_800D31D0_0_s01(chara, &g_SysWork.player_4C.chara_0.position_18, offset);
    if (ret != 0)
    {
        offset = MAX(offset, Q12(1.5));
        angle  = ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);

        offsetX = FP_MULTIPLY_PRECISE(offset, Math_Sin(angle), Q12_SHIFT);
        offsetZ = FP_MULTIPLY_PRECISE(offset, Math_Cos(angle), Q12_SHIFT);

        chara->properties_E4.npc.field_104 = chara->position_18.vx + offsetX;
        chara->properties_E4.npc.field_108 = g_SysWork.player_4C.chara_0.position_18.vy + g_SysWork.player_4C.chara_0.field_CE;
        chara->properties_E4.npc.field_10C = chara->position_18.vz + offsetZ;
    }

    return ret;
}
