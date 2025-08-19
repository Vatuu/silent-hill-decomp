s32 sharedFunc_800D3758_0_s01(s_SubCharacter* chara, s32* outDist, s32* outAngle, s32 arg3, s32 arg4)
#ifdef SHARED_FUNC_IMPL
{
    s32 temp_a0;
    s32 temp_s2;
    s32 temp_v0;
    s32 var_v1;

    temp_v0 = sharedFunc_800D3430_0_s01(chara, outDist, outAngle);
    if (temp_v0 != 0)
    {
        sharedData_800DE190_0_s01 = *((VECTOR3*)&chara->properties_E4.npc.field_104);
    }

    temp_s2 = sharedFunc_800D3630_0_s01(chara, arg3);
    temp_a0 = sharedFunc_800D3508_0_s01(chara, arg4);

    if (temp_v0 != 0)
    {
        *((VECTOR3*)&chara->properties_E4.npc.field_104) = sharedData_800DE190_0_s01;
    }

    var_v1 = (temp_v0 != 0) * 4;
    if (temp_s2 != 0)
    {
        var_v1 |= 1 << 1;
    }

    return var_v1 | (temp_a0 != 0);
}

#else
;
#endif
