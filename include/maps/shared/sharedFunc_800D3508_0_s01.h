bool sharedFunc_800D3508_0_s01(s_SubCharacter* airScreamer, q19_12* dist)
{
    q19_12 angleToPlayer;
    q19_12 angleToPlayerCpy;
    q19_12 offsetDist;
    q19_12 offsetX;
    u32    offsetZ;
    bool   cond;
    // TODO: Fix messy local var reuse.

    #define airScreamerProps airScreamer->properties_E4.airScreamer
    #define playerProps      g_SysWork.playerWork_4C.player_0.properties_E4.player

    offsetDist = playerProps.field_10C << 8;
    if (dist != NULL)
    {
        *dist = offsetDist;
    }

    cond = sharedFunc_800D2FB4_0_s01(airScreamer, &g_SysWork.playerWork_4C.player_0.position_18, offsetDist);
    if (cond)
    {
        angleToPlayer    = Math_AngleBetweenPositionsGet(airScreamer->position_18, g_SysWork.playerWork_4C.player_0.position_18);
        angleToPlayerCpy = angleToPlayer;

        offsetZ = g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0;
        if (!(offsetZ & 0x2))
        {
            // @hack Permuter find.
            offsetZ = 0;
            while (offsetZ) {};

            do
            {
                sharedFunc_800D4A80_0_s01(airScreamer);
            }
            while (false);
        }

        angleToPlayer = FP_MULTIPLY_PRECISE(offsetDist, Math_Sin(angleToPlayerCpy), Q12_SHIFT);
        offsetX = angleToPlayer;
        offsetZ = FP_MULTIPLY_PRECISE(offsetDist, Math_Cos(angleToPlayerCpy), Q12_SHIFT);

        airScreamerProps.position_104.vx = airScreamer->position_18.vx + offsetX;
        airScreamerProps.position_104.vy = g_SysWork.playerWork_4C.player_0.position_18.vy + g_SysWork.playerWork_4C.player_0.field_C8.field_6;
        airScreamerProps.position_104.vz = airScreamer->position_18.vz + offsetZ;
    }

    return cond;

    #undef airScreamerProps
    #undef playerProps
}

