s32 sharedFunc_800D3430_0_s01(s_SubCharacter* chara, s32* arg1, s32* arg2)
{
    s32 ret;

    sharedData_800DE180_0_s01.vx = g_SysWork.player_4C.chara_0.position_18.vx;
    sharedData_800DE180_0_s01.vy = g_SysWork.player_4C.chara_0.position_18.vy + g_SysWork.player_4C.chara_0.field_C8; // Head offset.
    sharedData_800DE180_0_s01.vz = g_SysWork.player_4C.chara_0.position_18.vz;
    ret                          = sharedFunc_800D2E04_0_s01(chara, &sharedData_800DE180_0_s01, arg1, arg2);

    if (ret != 0)
    {
        *((VECTOR3*)&chara->properties_E4.npc.field_104) = sharedData_800DE180_0_s01;
    }

    if (arg1 != NULL)
    {
        *arg1 = Math_Distance2d(&chara->position_18, (VECTOR3*)&chara->properties_E4.npc.field_104);
    }

    if (arg2 != NULL)
    {
        *arg2 = func_80080478(&chara->position_18, (VECTOR3*)&chara->properties_E4.npc.field_104);
    }

    return ret;
}
