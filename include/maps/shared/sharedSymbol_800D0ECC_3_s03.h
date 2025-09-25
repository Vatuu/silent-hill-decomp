void sharedSymbol_800D0ECC_3_s03(s_SubCharacter* chara)
{
#ifdef MAP3_S03
    if (chara->model_0.anim_4.status_0 != ((chara->model_0.stateStep_3 * 2) + 2) &&
        chara->model_0.anim_4.status_0 != ((chara->model_0.stateStep_3 * 2) + 3) &&
        chara->model_0.anim_4.status_0 != ((chara->model_0.stateStep_3 * 2) + 16) &&
        chara->model_0.anim_4.status_0 != ((chara->model_0.stateStep_3 * 2) + 17))
    {
        chara->model_0.anim_4.status_0 = ((chara->model_0.stateStep_3 * 2) + 2);
    }

    if (IS_ANIM_STATUS_ACTIVE(chara->model_0.anim_4.status_0))
    {
        chara->properties_E4.larvalStalker.properties_E8[2].val32 = Q12(0.3f);
    }
    else
    {
        chara->properties_E4.larvalStalker.properties_E8[2].val32 = Q12(0.75f);
    }
#endif
}
