void sharedFunc_800D9774_1_s02(s_SubCharacter* chara)
{
    chara->flags_3E &= ~CharaFlag_Unk2;

    if (chara->health_B0 == Q12(0.0f) && func_8005C7D0(chara) != g_SysWork.enemyTargetIdx_2353)
    {
        chara->health_B0   = NO_VALUE;
        chara->field_E1_0  = 0;
    }

    if (chara->moveSpeed_38 == Q12(0.0f) && !(chara->properties_E4.player.afkTimer_E8 & 0xC))
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
