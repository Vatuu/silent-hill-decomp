s32 sharedFunc_800D569C_0_s01(s_SubCharacter* airScreamer, q19_12 vecY, q19_12 dist)
{
    q19_12 posY;
    s32    someY;
    q19_12 groundHeight;
    q19_12 vecYCpy;
    q19_12 distCpy;
    q19_12 vec_x;
    q19_12 vec_z;

    #define airScreamerProps airScreamer->properties_E4.airScreamer

    vecYCpy      = vecY;
    posY         = airScreamer->position_18.vy;
    distCpy      = dist;
    groundHeight = Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz);

    // @hack: Unions shouldn't be mixed (NPC vs. Larval Stalker).
    someY = airScreamer->properties_E4.npc.field_124;

    vec_x = airScreamerProps.position_110.vx;
    vec_z = airScreamerProps.position_110.vz;

    if (someY < groundHeight)
    {
        groundHeight = someY;
    }

    groundHeight -= Q12(1.7f);
    someY  = func_800808AC(vec_x, vec_z); // Collision type? This returns `caseVar` from `Collision_Fill`.

    if (someY == 12 || someY == 0 || someY == 7)
    {
        distCpy = 0;
    }

    if (posY < groundHeight)
    {
        groundHeight = posY;
    }

    if (distCpy > Q12(12.0f))
    {
        vecYCpy = groundHeight;
    }
    else if (distCpy > Q12(4.0f))
    {
        someY    = FP_TO(distCpy - Q12(4.0f), Q12_SHIFT) / Q12(8.0f);
        vecYCpy += Q12_MULT_PRECISE((groundHeight - vecYCpy), someY);
    }

    if (vecYCpy < sharedFunc_800D5274_0_s01())
    {
        vecYCpy = sharedFunc_800D5274_0_s01();
    }

    return vecYCpy;

    #undef airScreamerProps
}
