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

    sharedData_800E231C_0_s01.result_0 = sharedFunc_800D3758_0_s01(chara,
                                                                   &sharedData_800E231C_0_s01.dist_4,
                                                                   &sharedData_800E231C_0_s01.angle_8,
                                                                   &sharedData_800E231C_0_s01.field_C,
                                                                   &sharedData_800E231C_0_s01.field_10);

    if (chara->properties_E4.unk0.field_E0_0 == 3)
    {
        chara->properties_E4.unk0.field_E0_8 = 0;
    }

    func = sharedData_800DD7A0_0_s01[chara->model_0.state_2];
    if (func)
    {
        func(chara);
    }

    return true;
}
