bool sharedFunc_800DC30C_2_s00(s_SubCharacter* airScreamer)
{
    func_8006F250(sharedData_800E2370_0_s01, airScreamer->position_18.vx, airScreamer->position_18.vz, Q12(0.0f), Q12(0.0f));

    switch (func_800808AC(airScreamer->position_18.vx, airScreamer->position_18.vz))
    {
        case 0:
        case 7:
        case 12:
            return true;
    }

    return (Collision_GroundHeightGet(airScreamer->position_18.vx, airScreamer->position_18.vz) + (airScreamer->field_C8.field_0 * 2)) >= sharedData_800E2370_0_s01[1];
}
