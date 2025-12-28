void sharedSymbol_800D3B0C_0_s01(s_SubCharacter* airScreamer)
{
    s32 keyframeIdx;
    s32 var0;
    s32 var1;
    s32 var2;
    u32 controlState;
    u32 stateStep;
    s32 field40;
    u32 modelState;
    u32 animStatus;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    field40 = airScreamer->field_40;
    switch (field40 % 0x3)
    {
        case 0:
        default:
            var2 = 0;
            break;

        case 1:
            var2 = 1;
            break;

        case 2:
            var2 = 2;
            break;
    }

    switch(field40 - (field40 / 2) * 2)
    {
        case 0:
        default:
            var1 = 1;
            break;

        case 1:
            var1 = 0;
            break;
    }

    stateStep = 0;
    switch (airScreamer->model_0.stateStep_3)
    {
#if defined(MAP0_S01)
        case 12:
        default:
            var0 = 4;
            var1 = 1;
            var2 = 3;
            animStatus = NO_VALUE;
            controlState = AirScreamerState_1;
            break;

        case 13:
            animStatus = ANIM_STATUS(AirScreamerAnim_19, true);

            if (g_SavegamePtr->mapOverlayId_A4 == 1)
            {
                var0 = 2;
                var1 = 1;
                var2 = 2;
                animStatus = ANIM_STATUS(AirScreamerAnim_2, true);
                controlState = AirScreamerState_46;
            }
            else
            {
                var0 = 2;

                if (airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(AirScreamerAnim_19, true))
                {
                    animStatus = NO_VALUE;
                }

                controlState = AirScreamerState_18;
            }
            break;
#else
        default:
            var0 = 1;
            animStatus = ANIM_STATUS(AirScreamerAnim_23, true);
            controlState = AirScreamerState_3;
            break;

        case 0:
        case 2:
            var0 = 1;
            animStatus = ANIM_STATUS(AirScreamerAnim_25, true);
            controlState = AirScreamerState_5;
            break;

        case 3:
            var0 = 1;
            animStatus = ANIM_STATUS(AirScreamerAnim_19, true);
            controlState = AirScreamerState_19;
            break;

        case 4:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_25, true);
            controlState = AirScreamerState_4;
            stateStep = 64;
            break;

        case 5:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_19, true);
            controlState = AirScreamerState_18;
            stateStep = 64;
            break;

        case 6:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_17, true);
            var2 = 2;
            controlState = AirScreamerState_33;
            stateStep = 64;
            break;

        case 8:
            var0 = 1;
            animStatus = ANIM_STATUS(AirScreamerAnim_14, true);
            var2 = 4;
            controlState = AirScreamerState_9;
            break;

        case 9:
            var0 = 3;
            animStatus = ANIM_STATUS(AirScreamerAnim_19, true);;
            controlState = AirScreamerState_19;
            var2 = 2;
            airScreamer->health_B0 *= 4;;
            break;

        case 11:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_17, true);
            controlState = AirScreamerState_33;
            stateStep = 65;
            var2 = 2;
            break;

        case 7:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_17, true);
            controlState = AirScreamerState_33;
            stateStep = 66;
            var2 = 2;
            break;

        case 10:
            var0 = 0;
            animStatus = ANIM_STATUS(AirScreamerAnim_17, true);
            controlState = AirScreamerState_33;
            stateStep = 67;
            var2 = 2;
            airScreamer->health_B0 -= airScreamer->health_B0 >> 2;
            break;
#endif
    }

    airScreamer->model_0.state_2 = controlState;
    airScreamer->model_0.stateStep_3 = stateStep;
    airScreamerProps.flags_11C = AirScreamerFlag_None;
    airScreamerProps.field_E8_0 = var0;
    airScreamerProps.field_E8_4 = var1;
    airScreamerProps.field_E8_8 = var2;

    if (controlState == AirScreamerState_1)
    {
        airScreamerProps.flags_11C = CharaUnk0Flag_Unk16;
    }

    if (animStatus != NO_VALUE && animStatus != airScreamer->model_0.anim_4.status_0)
    {
        airScreamer->model_0.anim_4.status_0      = animStatus;
        keyframeIdx                               = func_80044918(&airScreamer->model_0.anim_4)->startKeyframeIdx_C;
        airScreamer->model_0.anim_4.alpha_A       = Q12(0.0f);
        airScreamer->model_0.anim_4.keyframeIdx_8 = keyframeIdx;
        airScreamer->model_0.anim_4.time_4        = FP_TO(keyframeIdx, Q12_SHIFT);
    }

    #undef airScreamerProps
}
