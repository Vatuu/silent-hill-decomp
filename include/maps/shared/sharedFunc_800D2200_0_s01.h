void sharedFunc_800D2200_0_s01(s_SubCharacter* airScreamer)
{
    s32 count;

    count = func_800808AC(airScreamer->position_18.vx, airScreamer->position_18.vz);
    if (count == 7)
    {
        return;
    }

    if (count < 8)
    {
        if (count != 0)
        {
            airScreamer->properties_E4.airScreamer.groundHeight_124 = Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz);
        }
    }
    else if (count != 12)
    {
        airScreamer->properties_E4.airScreamer.groundHeight_124 = Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz);
    }
}
