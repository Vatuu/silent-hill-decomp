s32 sharedFunc_800D3758_0_s01(s_SubCharacter* chara, q19_12* outDist, q19_12* outAngle, q19_12 dist, s32* arg4)
{
    s32  cond1;
    s32  cond0;
    bool cond;
    s32  var_v1;

    cond = sharedFunc_800D3430_0_s01(chara, outDist, outAngle);
    if (cond)
    {
        sharedData_800DE190_0_s01 = *((VECTOR3*)&chara->properties_E4.npc.field_104);
    }

    cond0 = sharedFunc_800D3630_0_s01(chara, dist);
    cond1 = sharedFunc_800D3508_0_s01(chara, arg4);

    if (cond)
    {
        *((VECTOR3*)&chara->properties_E4.npc.field_104) = sharedData_800DE190_0_s01;
    }

    var_v1 = (cond != false) * 4;
    if (cond0)
    {
        var_v1 |= 1 << 1;
    }

    return var_v1 | (cond1 != false);
}

