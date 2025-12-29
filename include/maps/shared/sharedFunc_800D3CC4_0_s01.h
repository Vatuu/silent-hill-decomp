void sharedFunc_800D3CC4_0_s01(s_SubCharacter* airScreamer)
{
    u32  keyframeIdx;
    bool setAnim;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    sharedData_800E21D0_0_s01.flags_0 |= 1 << 31;
    setAnim                            = false;

    // Handle state step.
    switch (airScreamer->model_0.stateStep_3)
    {
        case AirScreamerStateStep_0:
            setAnim                              = true;
            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_23, true);
            airScreamer->model_0.stateStep_3     = AirScreamerStateStep_1;

        case AirScreamerStateStep_1:
            airScreamerProps.flags_11C |= AirScreamerFlag_16;
            break;

        case AirScreamerStateStep_2:
            setAnim                              = true;
            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_24, true);
            airScreamer->model_0.stateStep_3     = AirScreamerStateStep_3;

        case AirScreamerStateStep_3:
            airScreamerProps.flags_11C |= AirScreamerFlag_16;
            break;

        case AirScreamerStateStep_4:
            setAnim                              = true;
            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, true);
            airScreamer->model_0.stateStep_3     = AirScreamerStateStep_5;

        case AirScreamerStateStep_5:
            airScreamerProps.flags_11C &= ~AirScreamerFlag_16;
            break;

        case AirScreamerStateStep_6:
            if (airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(AirScreamerAnim_19, true))
            {
                airScreamer->model_0.stateStep_3 = AirScreamerStateStep_7;
            }
            break;

        case AirScreamerStateStep_7:
            airScreamer->model_0.controlState_2 = AirScreamerControl_None;
            airScreamer->model_0.stateStep_3    = AirScreamerStateStep_13;
            sharedSymbol_800D3B0C_0_s01(airScreamer);
            break;
    }

    Chara_DamageTake(airScreamer, Q12(0.0f));

    if (setAnim)
    {
        keyframeIdx                               = func_80044918(&airScreamer->model_0.anim_4)->startKeyframeIdx_C;
        airScreamer->model_0.anim_4.keyframeIdx_8 = keyframeIdx;
        airScreamer->model_0.anim_4.time_4        = Q12(keyframeIdx);
    }

    #undef airScreamerProps
}
