
void sharedFunc_800D670C_0_s00(s_SubCharacter* chara)
{
    if (chara->model_0.stateStep_3 == 1)
    {
        chara->model_0.stateStep_3++;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(15, false);
    }

    if (!((u16)chara->properties_E4.player.afkTimer_E8 & (1 << 14)) &&
        chara->model_0.anim_4.time_4 > FP_TIME(211.0f))
    {
        sharedFunc_800D7E04_0_s00(chara, 1365);

        chara->health_B0 = NO_VALUE;
        *(u16*)&chara->properties_E4.player.afkTimer_E8 |= 1 << 14;
    }

    if (chara->model_0.stateStep_3 == 3)
    {
        chara->model_0.stateStep_3++;
        Character_AnimSet(chara, ANIM_STATUS(47, true), 294);

        if (chara->health_B0 != NO_VALUE)
        {
            func_8005F6B0(&g_SysWork.npcs_1A0[1], &sharedData_800CAB70_0_s00, 3, 3);

            chara->health_B0 = NO_VALUE;
            *(u16*)&chara->properties_E4.player.afkTimer_E8 |= 1 << 14;
        }
    }
}
