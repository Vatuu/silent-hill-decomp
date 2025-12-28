void sharedFunc_800D3CC4_0_s01(s_SubCharacter* airScreamer)
{
    u32  keyframeIdx;
    bool setAnim;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    sharedData_800E21D0_0_s01.flags_0 |= 1 << 31;
    setAnim                            = false;

    switch (airScreamer->model_0.stateStep_3)
    {
        case 0:
            setAnim                              = true;
            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_23, true);
            airScreamer->model_0.stateStep_3     = 1;

        case 1:
            airScreamerProps.flags_11C |= AirScreamerFlag_16;
            break;

        case 2:
            setAnim                              = true;
            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_24, true);
            airScreamer->model_0.stateStep_3     = 3;

        case 3:
            airScreamerProps.flags_11C |= AirScreamerFlag_16;
            break;

        case 4:
            setAnim                              = true;
            airScreamer->model_0.anim_4.status_0 = ANIM_STATUS(AirScreamerAnim_15, true);
            airScreamer->model_0.stateStep_3     = 5;

        case 5:
            airScreamerProps.flags_11C &= ~AirScreamerFlag_16;
            break;

        case 6:
            if (airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(AirScreamerAnim_19, true))
            {
                airScreamer->model_0.stateStep_3 = 7;
            }
            break;

        case 7:
            airScreamer->model_0.state_2     = AirScreamerControl_None;
            airScreamer->model_0.stateStep_3 = 13;
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
