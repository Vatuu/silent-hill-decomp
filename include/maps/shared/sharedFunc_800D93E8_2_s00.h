void sharedFunc_800D93E8_2_s00(s_SubCharacter* chara)
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
                if (animStatus == ANIM_STATUS(21, true) || animStatus == ANIM_STATUS(9, true))
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(20, false);
                }
                else
                {
                    chara->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                }
                chara->model_0.stateStep_3 = 1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(10, false) && animStatus != ANIM_STATUS(20, false))
            {
                chara->model_0.stateStep_3             = 2;
                chara->properties_E4.player.flags_11C |= 1 << 3;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(10, true) && animStatus != ANIM_STATUS(20, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800D5E14_0_s01(chara);
    Chara_DamageTake(chara, Q12(0.6f));

    if (cond)
    {
        chara->model_0.state_2     = 2;
        chara->model_0.stateStep_3 = 0;

        chara->properties_E4.unk0.field_E8_8 = 1;
    }
}
