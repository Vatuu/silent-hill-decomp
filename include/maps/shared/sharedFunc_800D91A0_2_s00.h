void sharedFunc_800D91A0_2_s00(s_SubCharacter* airScreamer) // 0x800D91A0
{
    bool cond;
    s32  animStatus;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    cond             = false;
    animStatus       = airScreamer->model_0.anim_4.status_0;
    airScreamer->flags_3E |= CharaFlag_Unk3;

    switch ((u32)airScreamer->model_0.stateStep_3)
    {
        case 0:
            if (ANIM_STATUS_IS_ACTIVE(animStatus))
            {
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(9, false);
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_1;
            }
            break;

        case 1:
            if (animStatus != ANIM_STATUS(9, false))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_2;
                airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;

        case 2:
            if (animStatus != ANIM_STATUS(9, true))
            {
                cond = true;
            }
            break;
    }

    sharedFunc_800D5E14_0_s01(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(0.6f)))
    {
        case 0:
        case 1:
        case 2:
            if (cond)
            {
                airScreamer->model_0.controlState_2 = AirScreamerControl_31;
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;
            }
            break;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2 = AirScreamerControl_32;
            airScreamer->model_0.stateStep_3 = AirScreamerStateStep_0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamerProps.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                airScreamerProps.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }

    #undef airScreamerProps
}
