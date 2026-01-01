bool sharedFunc_800DC3BC_2_s00(s_SubCharacter* airScreamer)
{
    switch (func_800808AC(airScreamer->position_18.vx, airScreamer->position_18.vz))
    {
        case 0:
        case 7:
        case 12:
            return false;
    }

    return Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz) <= Q12(3.0f);
}
