void Ai_PuppetNurse_UpdateMain(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (g_DeltaTime0 != Q12(0.0))
    {
        Ai_PuppetNurse_DamageHandle(chara);
        Ai_PuppetNurse_Control(chara);
        sharedFunc_800CDA88_3_s03(chara);
        sharedFunc_800D03E4_3_s03(chara);
        Ai_PuppetNurse_AnimUpdate(chara, anmHdr, coords);
        sharedFunc_800D0968_3_s03(chara, coords);
        sharedFunc_800D02E4_3_s03(chara, coords);
        return;
    }

    Ai_PuppetNurse_AnimUpdate(chara, anmHdr, coords);
}
