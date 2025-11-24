bool sharedFunc_800DC30C_2_s00(s_SubCharacter* chara)
{
    func_8006F250(sharedData_800E2370_0_s01, chara->position_18.vx, chara->position_18.vz, 0, 0);

    switch (func_800808AC(chara->position_18.vx, chara->position_18.vz))
    {
        case 0:
        case 7:
        case 12:
            return true;
    }

    return (func_80080884(chara->position_18.vx, chara->position_18.vz) + (chara->field_C8 * 2)) >= sharedData_800E2370_0_s01[1];
}
