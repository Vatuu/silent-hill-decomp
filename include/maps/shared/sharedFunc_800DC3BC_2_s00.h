bool sharedFunc_800DC3BC_2_s00(s_SubCharacter* chara)
{
    switch (func_800808AC(chara->position_18.vx, chara->position_18.vz))
    {
        case 0:
        case 7:
        case 12:
            return false;
    }

    return func_80080884(chara->position_18.vx, chara->position_18.vz) <= Q12(3.0f);
}
