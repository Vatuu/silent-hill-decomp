bool sharedFunc_800D3430_0_s01(s_SubCharacter* chara, s32* dist, s32* angle)
{
    bool cond;

    sharedData_800DE180_0_s01.vx = g_SysWork.player_4C.chara_0.position_18.vx;
    sharedData_800DE180_0_s01.vy = g_SysWork.player_4C.chara_0.position_18.vy + g_SysWork.player_4C.chara_0.field_C8; // Head offset.
    sharedData_800DE180_0_s01.vz = g_SysWork.player_4C.chara_0.position_18.vz;
    cond                         = sharedFunc_800D2E04_0_s01(chara, &sharedData_800DE180_0_s01, dist, angle);

    if (cond)
    {
        *((VECTOR3*)&chara->properties_E4.npc.field_104) = sharedData_800DE180_0_s01;
    }

    if (dist != NULL)
    {
        *dist = Math_Distance2dGet(&chara->position_18, (VECTOR3*)&chara->properties_E4.npc.field_104);
    }

    if (angle != NULL)
    {
        *angle = func_80080478(&chara->position_18, (VECTOR3*)&chara->properties_E4.npc.field_104);
    }

    return cond;
}
