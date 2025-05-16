
void sharedFunc_800D670C_0_s00(s_SubCharacter* arg0)
{
    if (arg0->model_0.stateStep_3 == 1)
    {
        arg0->model_0.stateStep_3++;
        arg0->model_0.anim_4.animIdx_0 = 30;
    }

    if (!((u16)arg0->properties_E4.player.properties_E4[1] & (1 << 14)) &&
        arg0->model_0.anim_4.time_4 > FP_TO(211, Q12_SHIFT))
    {
        sharedFunc_800D7E04_0_s00(arg0, 0x555);
        arg0->health_B0                = NO_VALUE;
        *(u16*)&arg0->properties_E4.player.properties_E4[1] = (u16)arg0->properties_E4.player.properties_E4[1] | (1 << 14);
    }

    if (arg0->model_0.stateStep_3 == 3)
    {
        arg0->model_0.stateStep_3++;
        arg0->model_0.anim_4.animIdx_0      = 95;
        arg0->model_0.anim_4.keyframeIdx0_8 = 294;
        arg0->model_0.anim_4.time_4         = FP_TO(294, Q12_SHIFT);

        if (arg0->health_B0 != NO_VALUE)
        {
            func_8005F6B0(&g_SysWork.npcs_1A0[1], &sharedData_800CAB70_0_s00, 3, 3);

            arg0->health_B0                = NO_VALUE;
            *(u16*)&arg0->properties_E4.player.properties_E4[1] = (u16)arg0->properties_E4.player.properties_E4[1] | (1 << 14);
        }
    }
}
