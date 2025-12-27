
void sharedFunc_800D670C_0_s00(s_SubCharacter* stalker)
{
    if (stalker->model_0.stateStep_3 == 1)
    {
        stalker->model_0.stateStep_3++;
        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_15, false);
    }

    if (!(stalker->properties_E4.stalker.flags_E8 & StalkerFlag_14) &&
        stalker->model_0.anim_4.time_4 > Q12(211.0f))
    {
        sharedFunc_800D7E04_0_s00(stalker, 1365);

        stalker->health_B0 = NO_VALUE;
        stalker->properties_E4.stalker.flags_E8 |= StalkerFlag_14;
    }

    if (stalker->model_0.stateStep_3 == 3)
    {
        stalker->model_0.stateStep_3++;
        Character_AnimSet(stalker, ANIM_STATUS(StalkerAnim_47, true), 294);

        if (stalker->health_B0 != NO_VALUE)
        {
            func_8005F6B0(&g_SysWork.npcs_1A0[1], &(VECTOR3){ Q12(140.39f), Q12(-0.55f), Q12(22.76f) }, 3, 3);

            stalker->health_B0 = NO_VALUE;
            stalker->properties_E4.stalker.flags_E8 |=StalkerFlag_14;
        }
    }
}
