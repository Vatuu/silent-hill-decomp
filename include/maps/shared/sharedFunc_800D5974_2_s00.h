void sharedFunc_800D5974_2_s00(s_SubCharacter* airScreamer)
{
    s32 bit3;
    s32 f150;
    s32 idx;
    s32 switch2Idx;
    u32 stateStep;
    s32 animStatus;
    s16 one;

    animStatus = airScreamer->model_0.anim_4.status_0;
    idx        = sharedFunc_800D4A80_0_s01(airScreamer);
    switch2Idx = 0;

    bit3      = sharedData_800E21D0_0_s01.field_14C.bits.field_14C_2;
    stateStep = airScreamer->model_0.stateStep_3;
    f150      = sharedData_800E21D0_0_s01.distance_150;
    one       = 1;

    switch (stateStep)
    {
        case 0:
            if (!sharedFunc_800DC30C_2_s00(airScreamer) || Rng_RandQ12() >= FP_ANGLE(252.0f))
            {
                airScreamer->properties_E4.dummy.properties_E8[0xE].val32 = Q12(2.0f);
                airScreamer->model_0.stateStep_3                                  = one;
            }
            else
            {
                airScreamer->model_0.stateStep_3 = 2;
            }
            break;

        case 1:
            if (sharedFunc_800DC598_2_s00(airScreamer))
            {
                airScreamer->model_0.stateStep_3 = 2;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(25, true) || animStatus == ANIM_STATUS(23, true))
            {
                switch2Idx                     = 1;
                airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                airScreamer->model_0.stateStep_3     = 3;
            }
            break;

        case 3:
            switch2Idx = 1;
            break;
    }

    sharedFunc_800DE1F8_2_s00(airScreamer);
    sharedFunc_800DF710_2_s00(airScreamer);

    switch (Ai_AirScreamer_DamageTake(airScreamer, Q12(1.0f)))
    {
        case 0:
            switch (switch2Idx)
            {
                case 0:
                    if (airScreamer->properties_E4.dummy.properties_E8[0xE].val32 == 0 || f150 > 0x2000)
                    {
                        if (bit3 == 0)
                        {
                            airScreamer->model_0.controlState_2 = 13;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = 10;
                        }

                        airScreamer->model_0.stateStep_3 = 0;
                    }
                    break;

                case 1:
                    if (idx == 2)
                    {
                        if (bit3 != 0)
                        {
                            airScreamer->model_0.controlState_2 = 24;
                        }
                        else
                        {
                            airScreamer->model_0.controlState_2 = 26;
                        }

                        airScreamer->model_0.stateStep_3 = 0;
                    }
                    break;

                default:
                    return;
            }
            break;

        case 1:
        case 2:
            airScreamer->model_0.controlState_2                 = 16;
            airScreamer->model_0.stateStep_3             = 0;
            airScreamer->properties_E4.player.flags_11C |= CharaUnk0Flag_Unk3;
            return;

        case 3:
        case 4:
            airScreamer->model_0.controlState_2     = 17;
            airScreamer->model_0.stateStep_3 = 0;

            if (airScreamer->health_B0 <= Q12(0.0f))
            {
                airScreamer->properties_E4.player.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                airScreamer->properties_E4.player.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}
