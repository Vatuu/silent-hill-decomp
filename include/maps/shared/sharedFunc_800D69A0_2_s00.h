void sharedFunc_800D69A0_2_s00(s_SubCharacter* chara)
{
    bool cond;
    s32  animStatus;
    u32  modelStep;

    cond = false;

    modelStep        = chara->model_0.stateStep_3;
    animStatus       = chara->model_0.anim_4.status_0;
    chara->flags_3E |= CharaFlag_Unk3;

    switch (modelStep)
    {
        case 0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(4, false);
                chara->model_0.stateStep_3     = 1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(4, false))
            {
                chara->model_0.stateStep_3             = 2;
                chara->properties_E4.player.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;

        case 2:
            if (animStatus != 9)
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800DF8A0_2_s00(chara);
    Ai_AirScreamer_DamageTake(chara, Q12(0.6f));

    if (cond)
    {
        chara->model_0.controlState_2               = 2;
        chara->model_0.stateStep_3           = 0;
        chara->properties_E4.unk0.field_E8_8 = 1;
    }
}
