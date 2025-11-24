void sharedFunc_800DBDEC_2_s00(s_SubCharacter* chara)
{
    bool cond;
    s32  animStatus;

    cond       = false;
    animStatus = chara->model_0.anim_4.status_0;

    chara->flags_3E |= CharaFlag_Unk3;

    switch ((u32)chara->model_0.stateStep_3)
    {
        case 0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(11, false);
                chara->model_0.stateStep_3     = 1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(11, false))
            {
                chara->model_0.stateStep_3           = 2;
                chara->properties_E4.unk0.flags_11C |= 1 << 3;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(11, true))
            {
                cond = true;
            }
            break;
    }

    if (sharedFunc_800D4A80_0_s01(chara) == 3)
    {
        sharedFunc_800E04B0_2_s00(chara);
    }
    else
    {
        sharedFunc_800D5638_0_s01(chara);
    }

    Chara_DamageTake(chara, Q12(0.6f));

    if (cond)
    {
        chara->model_0.state_2     = 2;
        chara->model_0.stateStep_3 = 0;

        chara->properties_E4.unk0.field_E8_8 = 1;
    }
}
