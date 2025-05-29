void sharedSymbol_800D0ECC_3_s03(s_SubCharacter* chara)
{
#ifdef MAP3_S03
    if (chara->model_0.anim_4.animIdx_0 != ((chara->model_0.stateStep_3 * 2) + 2) &&
        chara->model_0.anim_4.animIdx_0 != ((chara->model_0.stateStep_3 * 2) + 3) &&
        chara->model_0.anim_4.animIdx_0 != ((chara->model_0.stateStep_3 * 2) + 16) &&
        chara->model_0.anim_4.animIdx_0 != ((chara->model_0.stateStep_3 * 2) + 17))
    {
        chara->model_0.anim_4.animIdx_0 = ((chara->model_0.stateStep_3 * 2) + 2);
    }

    if (chara->model_0.anim_4.animIdx_0 & (1 << 0))
    {
        chara->properties_E4.larvalStalker.properties_E8[2].val32 = FP_FLOAT_TO(0.30f, Q12_SHIFT);
    }
    else
    {
        chara->properties_E4.larvalStalker.properties_E8[2].val32 = FP_FLOAT_TO(0.75f, Q12_SHIFT);
    }
#endif
}
