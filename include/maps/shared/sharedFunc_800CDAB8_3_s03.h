void sharedFunc_800CDAB8_3_s03(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    if (g_DeltaTime0 != 0)
    {
        sharedFunc_800CDF24_3_s03(chara);
        sharedFunc_800D01D0_3_s03(chara);
        sharedFunc_800CDA88_3_s03(chara);
        sharedFunc_800D03E4_3_s03(chara);
        sharedFunc_800D06AC_3_s03(chara, arg1, arg2);
        sharedFunc_800D0968_3_s03(chara, arg2);
        sharedFunc_800D02E4_3_s03(chara, arg2);
        return;
    }

    sharedFunc_800D06AC_3_s03(chara, arg1, arg2);
}
