void sharedFunc_800DBDEC_2_s00(s_SubCharacter* airScreamer)
{
    bool cond;
    s32  animStatus;

    #define airScreamerFlags airScreamer->properties_E4.airScreamer

    cond       = false;
    animStatus = airScreamer->model_0.anim_4.status_0;

    airScreamer->flags_3E |= CharaFlag_Unk3;

    // Handle state step. TODO: Cast necessary?
    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_11, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case AirScreamerStateStep_1:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_11, false))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                airScreamerFlags.flags_11C |= AirScreamerFlag_3;
            }
            break;

        case AirScreamerStateStep_2:
            if (animStatus != ANIM_STATUS(AirScreamerAnim_11, true))
            {
                cond = true;
            }
            break;
    }

    if (sharedFunc_800D4A80_0_s01(airScreamer) == 3)
    {
        sharedFunc_800E04B0_2_s00(airScreamer);
    }
    else
    {
        sharedFunc_800D5638_0_s01(airScreamer);
    }

    Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f));

    if (cond)
    {
        airScreamer->model_0.controlState_2 = AirScreamerControl_2;
        airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
        airScreamerFlags.field_E8_8 = 1;
    }
}
