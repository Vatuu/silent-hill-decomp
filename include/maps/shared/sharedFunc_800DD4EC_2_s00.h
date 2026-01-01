void sharedFunc_800DD4EC_2_s00(s_SubCharacter* airScreamer)
{
    #define airScreamerProps airScreamer->properties_E4.airScreamer

    sharedFunc_800DD2C4_2_s00(airScreamer, Q12(-2.2f), 0);
    sharedFunc_800D529C_0_s01(airScreamer, Q12(30.0f), airScreamer->rotation_24.vy);
    airScreamerProps.timer_120 = Q12(12.0f);

    #undef airScreamerProps
}
