void sharedFunc_800E83D4_2_s02(s_SubCharacter* chara)
{
    if (chara->health_B0 == Q12(0.0f))
    {
        if (g_SysWork.targetNpcIdx_2353 != func_8005C7D0(chara))
        {
            chara->health_B0  = NO_VALUE;
            chara->field_E1_0 = 0;
        }
    }

    if (chara->moveSpeed_38 == Q12(0.0f) && !(chara->properties_E4.player.afkTimer_E8 & 0x3))
    {
        func_800622B8(3, chara, ANIM_STATUS(6, true), 9);
        chara->properties_E4.player.afkTimer_E8 |= 0x2;
    }
}
