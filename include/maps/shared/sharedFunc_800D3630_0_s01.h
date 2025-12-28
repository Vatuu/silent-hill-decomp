bool sharedFunc_800D3630_0_s01(s_SubCharacter* airScreamer, q19_12* dist)
{
    bool   cond;
    q19_12 angleToPlayer;
    q19_12 offsetDist;
    q19_12 offsetX;
    q19_12 offsetZ;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    offsetDist = sharedFunc_800D3814_0_s01(airScreamer);
    if (dist != NULL)
    {
        *dist = offsetDist;
    }

    // Set target position for pecking?
    cond = sharedFunc_800D31D0_0_s01(airScreamer, &g_SysWork.playerWork_4C.player_0.position_18, offsetDist);
    if (cond)
    {
        // Compute extra offset distance.
        offsetDist = MAX(offsetDist, Q12(1.5f));

        // Compute extra offset.
        angleToPlayer = Math_AngleBetweenPositionsGet(airScreamer->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        offsetX = FP_MULTIPLY_PRECISE(offsetDist, Math_Sin(angleToPlayer), Q12_SHIFT);
        offsetZ = FP_MULTIPLY_PRECISE(offsetDist, Math_Cos(angleToPlayer), Q12_SHIFT);

        // Set target position slightly ahead of Air Screamer.
        airScreamerProps.position_104.vx = airScreamer->position_18.vx + offsetX;
        airScreamerProps.position_104.vy = g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_6;
        airScreamerProps.position_104.vz = airScreamer->position_18.vz + offsetZ;
    }

    return cond;

    #undef airScreamerProps
}
