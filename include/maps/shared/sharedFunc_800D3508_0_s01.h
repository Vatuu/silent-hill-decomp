bool sharedFunc_800D3508_0_s01(s_SubCharacter* chara, s32* arg1)
{
    s32    temp_hi;
    q19_12 angle;
    s32    temp_s2;
    u32    temp_lo;
    bool   cond;
    q19_12 tmpAngle;

    temp_s2 = g_SysWork.player_4C.chara_0.properties_E4.player.field_10C << 8;
    if (arg1 != NULL)
    {
        *arg1 = temp_s2;
    }

    cond = sharedFunc_800D2FB4_0_s01(chara, &g_SysWork.player_4C.chara_0.position_18, temp_s2);
    if (cond)
    {
        tmpAngle = ratan2(g_SysWork.player_4C.chara_0.position_18.vx - chara->position_18.vx, g_SysWork.player_4C.chara_0.position_18.vz - chara->position_18.vz);
        angle = tmpAngle;

        temp_lo = g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0;
        if (!(temp_lo & 0x2))
        {
            // @hack Permuter find.
            temp_lo = 0;
            while (temp_lo) {};

            do
            {
                sharedFunc_800D4A80_0_s01(chara);
            }
            while (false);
        }

        tmpAngle = FP_MULTIPLY_PRECISE(temp_s2, Math_Sin(angle), Q12_SHIFT);
        temp_hi = tmpAngle;
        temp_lo = FP_MULTIPLY_PRECISE(temp_s2, Math_Cos(angle), Q12_SHIFT);

        chara->properties_E4.unk0.pos_104.vx = chara->position_18.vx + temp_hi;
        temp_hi                              = g_SysWork.player_4C.chara_0.field_C8.field_6;
        chara->properties_E4.unk0.pos_104.vy = g_SysWork.player_4C.chara_0.position_18.vy + temp_hi;
        chara->properties_E4.unk0.pos_104.vz = chara->position_18.vz + temp_lo;
    }

    return cond;
}

