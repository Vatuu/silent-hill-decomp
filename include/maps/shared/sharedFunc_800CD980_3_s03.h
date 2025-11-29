s32 sharedFunc_800CD980_3_s03(s_SubCharacter* chara)
{
    s32 attack;
    s32 idx;

    attack = chara->attackReceived_41;
    if (attack != 5 && attack != 15 && attack != 25 && attack != 2 && attack != 12 && attack != 22)
    {
        idx = D_800AD4C8[attack].field_10;
        return sharedData_800D57E0_3_s03[idx];
    }
    return NO_VALUE;
}
