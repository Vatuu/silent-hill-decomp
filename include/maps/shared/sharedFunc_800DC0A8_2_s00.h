bool sharedFunc_800DC0A8_2_s00(s_SubCharacter* airScreamer)
{
    return (Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz) - Q12(0.2f)) < airScreamer->position_18.vy;
}
