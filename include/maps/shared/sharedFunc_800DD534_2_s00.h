void sharedFunc_800DD534_2_s00(s_SubCharacter* chara)
{
    sharedFunc_800DD2C4_2_s00(chara, Q12(-2.2f), 1);
    sharedFunc_800DEC84_2_s00(chara, Q12(30.0f), chara->rotation_24.vy);
    chara->moveSpeed_38                            = sharedData_800CAA98_0_s01.unk_380[9][0];
    chara->properties_E4.unk0.properties_120.val32 = Q12(10.0f);
}
