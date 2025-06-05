void Ai_PuppetNurse_UpdateMain(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords)
{
    if (g_DeltaTime0 != 0)
    {
        sharedFunc_800CDF24_3_s03(chara);
        Ai_PuppetNurse_Control(chara);
        sharedFunc_800CDA88_3_s03(chara);
        sharedFunc_800D03E4_3_s03(chara);
        sharedFunc_800D06AC_3_s03(chara, arg1, coords);
        sharedFunc_800D0968_3_s03(chara, coords);
        sharedFunc_800D02E4_3_s03(chara, coords);
        return;
    }

    sharedFunc_800D06AC_3_s03(chara, arg1, coords);
}
