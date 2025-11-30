void sharedFunc_800D9774_1_s02(s_SubCharacter* creaper)
{
    creaper->flags_3E &= ~CharaFlag_Unk2;

    if (creaper->health_B0 == Q12(0.0f) && func_8005C7D0(creaper) != g_SysWork.targetNpcIdx_2353)
    {
        creaper->health_B0   = NO_VALUE;
        creaper->field_E1_0  = 0;
    }

    if (creaper->moveSpeed_38 == Q12(0.0f) && !(creaper->properties_E4.player.afkTimer_E8 & 0xC))
    {
        creaper->properties_E4.larvalStalker.properties_E8[0].val16[0] |= 1 << 3;

        func_80037DC4(creaper);

        if (creaper->model_0.anim_4.status_0 == ANIM_STATUS(14, true))
        {
            func_800622B8(3, creaper, 10, 5);
        }
        else
        {
            func_800622B8(3, creaper, 11, 5);
        }
    }
}
