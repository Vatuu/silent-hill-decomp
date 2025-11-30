void sharedSymbol_800D0E38_3_s03(s_SubCharacter* bloodsucker)
{
#ifdef MAP3_S03
    if (bloodsucker->model_0.anim_4.status_0 == ((bloodsucker->model_0.stateStep_3 * 2) + 9))
    {
        bloodsucker->model_0.anim_4.status_0 = (bloodsucker->model_0.stateStep_3 * 2) + 22;
    }

    if (g_SysWork.player_4C.chara_0.position_18.vx < -Q12(140.75f))
    {
        bloodsucker->model_0.state_2 = 3;
    }

    bloodsucker->properties_E4.larvalStalker.properties_E8[2].val32 = Q12(0.3f);
#endif
}
