void Ai_PuppetNurse_UpdateMain(s_SubCharacter* nurse, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (g_DeltaTime != Q12(0.0f))
    {
        Ai_PuppetNurse_DamageHandle(nurse);
        Ai_PuppetNurse_Control(nurse);
        sharedFunc_800CDA88_3_s03(nurse);
        sharedFunc_800D03E4_3_s03(nurse);
        Ai_PuppetNurse_AnimUpdate(nurse, anmHdr, coords);
        sharedFunc_800D0968_3_s03(nurse, coords);
        sharedFunc_800D02E4_3_s03(nurse, coords);
        return;
    }
    else
    {
        Ai_PuppetNurse_AnimUpdate(nurse, anmHdr, coords);
    }
}
