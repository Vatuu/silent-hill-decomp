bool sharedFunc_800D3430_0_s01(s_SubCharacter* airScreamer, q19_12* dist, q19_12* angle)
{
    bool cond;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    sharedData_800DE180_0_s01.vx = g_SysWork.playerWork_4C.player_0.position_18.vx;
    sharedData_800DE180_0_s01.vy = g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_0; // Head offset.
    sharedData_800DE180_0_s01.vz = g_SysWork.playerWork_4C.player_0.position_18.vz;

    cond = sharedFunc_800D2E04_0_s01(airScreamer, &sharedData_800DE180_0_s01, dist, angle);
    if (cond)
    {
        airScreamerProps.position_104 = sharedData_800DE180_0_s01;
    }

    if (dist != NULL)
    {
        *dist = Math_Distance2dGet(&airScreamer->position_18, &airScreamerProps.position_104);
    }

    if (angle != NULL)
    {
        *angle = func_80080478(&airScreamer->position_18, &airScreamerProps.position_104);
    }

    return cond;

    #undef airScreamerProps
}
