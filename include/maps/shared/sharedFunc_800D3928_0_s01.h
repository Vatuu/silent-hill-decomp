bool sharedFunc_800D3928_0_s01(s_SubCharacter* chara)
{
    q20_12 someTime;
    q19_12 deltaTime;
    void (*func)(s_SubCharacter*);

    deltaTime = g_DeltaTime0;
    if (deltaTime < Q12(0.0f))
    {
        deltaTime = Q12(0.0f);
    }

    someTime = chara->properties_E4.unk0.properties_120.val32;
    if (someTime < deltaTime)
    {
        chara->properties_E4.unk0.properties_120.val32 = 0;
    }
    else
    {
        chara->properties_E4.unk0.properties_120.val32 = someTime - deltaTime;
    }

    sharedData_800E21D0_0_s01.field_14C.flags = sharedFunc_800D3758_0_s01(chara,
                                                                   &sharedData_800E21D0_0_s01.dist_150,
                                                                   &sharedData_800E21D0_0_s01.angle_154,
                                                                   &sharedData_800E21D0_0_s01.field_158,
                                                                   &sharedData_800E21D0_0_s01.field_15C);

    if (chara->properties_E4.unk0.field_E8_0 == 3)
    {
        chara->properties_E4.unk0.field_E8_8 = 0;
    }

    func = sharedData_800DD7A0_0_s01[chara->model_0.state_2];
    if (func)
    {
        func(chara);
    }

    return true;
}
