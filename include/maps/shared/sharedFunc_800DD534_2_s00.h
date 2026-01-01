void sharedFunc_800DD534_2_s00(s_SubCharacter* airScreamer)
{
    #define airScreamerProps airScreamer->properties_E4.airScreamer

    sharedFunc_800DD2C4_2_s00(airScreamer, Q12(-2.2f), 1);
    sharedFunc_800DEC84_2_s00(airScreamer, Q12(30.0f), airScreamer->rotation_24.vy);

    airScreamer->moveSpeed_38                            = sharedData_800CAA98_0_s01.unk_380[9][0];
    airScreamerProps.timer_120 = Q12(10.0f);

    #undef airScreamerProps
}
