void sharedFunc_800D69A0_2_s00(s_SubCharacter* airScreamer)
{
    bool cond;
    s32  animStatus;
    u32  modelStep;

    cond = false;

    modelStep        = airScreamer->model_0.stateStep_3;
    animStatus       = airScreamer->model_0.anim_4.status_0;
    airScreamer->flags_3E |= CharaFlag_Unk3;

    switch (modelStep)
    {
        case 0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(4, false);
                airScreamer->model_0.stateStep_3     = 1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(4, false))
            {
                airScreamer->model_0.stateStep_3             = 2;
                airScreamer->properties_E4.player.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;

        case 2:
            if (animStatus != 9)
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800DF8A0_2_s00(airScreamer);
    Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f));

    if (cond)
    {
        airScreamer->model_0.controlState_2               = 2;
        airScreamer->model_0.stateStep_3           = 0;
        airScreamer->properties_E4.unk0.field_E8_8 = 1;
    }
}
