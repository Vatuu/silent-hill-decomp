s32 sharedFunc_800D3758_0_s01(s_SubCharacter* airScreamer, q19_12* outDist, q19_12* outAngle, q19_12 dist, s32* arg4)
{
    s32  cond1;
    s32  cond0;
    bool cond;
    s32  flags;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    cond = sharedFunc_800D3430_0_s01(airScreamer, outDist, outAngle);
    if (cond)
    {
        sharedData_800DE190_0_s01 = airScreamerProps.position_104;
    }

    cond0 = sharedFunc_800D3630_0_s01(airScreamer, dist);
    cond1 = sharedFunc_800D3508_0_s01(airScreamer, arg4);

    if (cond)
    {
        airScreamerProps.position_104 = sharedData_800DE190_0_s01;
    }

    flags = (cond != false) * 4;
    if (cond0)
    {
        flags |= 1 << 1;
    }

    return flags | (cond1 != false);

    #undef airScreamerProps
}

