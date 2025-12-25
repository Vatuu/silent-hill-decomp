void sharedFunc_800D633C_0_s01(s_SubCharacter* airScreamer)
{
    q19_12 posY;

    func_8006F250(&sharedData_800E2370_0_s01, airScreamer->position_18.vx, airScreamer->position_18.vz, Q12(0.0f), Q12(0.0f));

    posY = sharedData_800E2370_0_s01[1] - airScreamer->field_C8.field_0;
    if (airScreamer->position_18.vy < posY)
    {
        airScreamer->position_18.vy = posY;
    }
}
