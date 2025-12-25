void sharedSymbol_800D0ECC_3_s03(s_SubCharacter* bloodsucker)
{
#ifdef MAP3_S03
    if (bloodsucker->model_0.anim_4.status_0 != ((bloodsucker->model_0.stateStep_3 * 2) + 2) &&
        bloodsucker->model_0.anim_4.status_0 != ((bloodsucker->model_0.stateStep_3 * 2) + 3) &&
        bloodsucker->model_0.anim_4.status_0 != ((bloodsucker->model_0.stateStep_3 * 2) + 16) &&
        bloodsucker->model_0.anim_4.status_0 != ((bloodsucker->model_0.stateStep_3 * 2) + 17))
    {
        bloodsucker->model_0.anim_4.status_0 = (bloodsucker->model_0.stateStep_3 * 2) + 2;
    }

    if (ANIM_STATUS_IS_ACTIVE(bloodsucker->model_0.anim_4.status_0))
    {
        bloodsucker->properties_E4.bloodsucker.timer_F0 = Q12(0.3f);
    }
    else
    {
        bloodsucker->properties_E4.bloodsucker.timer_F0 = Q12(0.75f);
    }
#endif
}
