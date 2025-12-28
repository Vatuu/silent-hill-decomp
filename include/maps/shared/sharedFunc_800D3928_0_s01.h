bool sharedFunc_800D3928_0_s01(s_SubCharacter* airScreamer)
{
    q20_12 someTime;
    q19_12 deltaTime;
    void (*func)(s_SubCharacter*);

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    deltaTime = g_DeltaTime0;
    if (deltaTime < Q12(0.0f))
    {
        deltaTime = Q12(0.0f);
    }

    someTime = airScreamerProps.timer_120;
    if (someTime < deltaTime)
    {
        airScreamerProps.timer_120 = Q12(0.0f);
    }
    else
    {
        airScreamerProps.timer_120 = someTime - deltaTime;
    }

    sharedData_800E21D0_0_s01.field_14C.flags = sharedFunc_800D3758_0_s01(airScreamer,
                                                                          &sharedData_800E21D0_0_s01.distance_150,
                                                                          &sharedData_800E21D0_0_s01.angle_154,
                                                                          &sharedData_800E21D0_0_s01.field_158,
                                                                          &sharedData_800E21D0_0_s01.field_15C);

    if (airScreamerProps.field_E8_0 == 3)
    {
        airScreamerProps.field_E8_8 = 0;
    }

    func = sharedData_800DD7A0_0_s01[airScreamer->model_0.state_2];
    if (func)
    {
        func(airScreamer);
    }

    return true;

    #undef airScreamerProps
}
