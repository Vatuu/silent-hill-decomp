void sharedFunc_800D91A0_2_s00(s_SubCharacter* chara) // 0x800D91A0
{
    bool cond;
    s32  animStatus;

    cond             = false;
    animStatus       = chara->model_0.anim_4.status_0;
    chara->flags_3E |= CharaFlag_Unk3;

    switch ((u32)chara->model_0.stateStep_3)
    {
        case 0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                chara->model_0.anim_4.status_0 = ANIM_STATUS(9, false);
                chara->model_0.stateStep_3     = 1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(9, false))
            {
                chara->model_0.stateStep_3           = 2;
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(9, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800D5E14_0_s01(chara);

    switch (Ai_AirScreamer_DamageTake(chara, Q12(0.6f)))
    {
        case 0:
        case 1:
        case 2:
            if (cond)
            {
                chara->model_0.controlState_2     = 31;
                chara->model_0.stateStep_3 = 0;
            }
            break;

        case 3:
        case 4:
            chara->model_0.controlState_2     = 32;
            chara->model_0.stateStep_3 = 0;

            if (chara->health_B0 <= Q12(0.0f))
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}
