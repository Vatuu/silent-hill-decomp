void sharedSymbol_800D0E38_3_s03(s_SubCharacter* chara)
{
#ifdef MAP3_S03
    if (chara->model_0.anim_4.status_0 == ((chara->model_0.stateStep_3 * 2) + 9))
    {
        chara->model_0.anim_4.status_0 = (chara->model_0.stateStep_3 * 2) + 22;
    }

    if (g_SysWork.player_4C.chara_0.position_18.vx < -Q12(140.75f))
    {
        chara->model_0.state_2 = 3;
    }

    chara->properties_E4.larvalStalker.properties_E8[2].val32 = Q12(0.3f);
#endif
}
