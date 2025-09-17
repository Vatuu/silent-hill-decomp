void sharedFunc_800D9774_1_s02(s_SubCharacter* chara)
{
    chara->flags_3E &= ~(1 << 1);

    if (chara->health_B0 == Q12(0.0f) && func_8005C7D0(chara) != g_SysWork.enemyTargetIdx_2353)
    {
        chara->health_B0   = NO_VALUE;
        chara->u_E1.s_1.field_E1_0 &= (1 << 5) | (1 << 6) | (1 << 7);
    }

    if (chara->moveSpeed_38 == 0 && !(chara->properties_E4.player.afkTimer_E8 & 0xC))
    {
        chara->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 3;

        func_80037DC4(chara);

        if (chara->model_0.anim_4.status_0 == ANIM_STATUS(14, true))
        {
            func_800622B8(3, chara, 10, 5);
        }
        else
        {
            func_800622B8(3, chara, 11, 5);
        }
    }
}
