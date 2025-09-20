void Ai_HangedScratcher_Update(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_HangedScratcher_Init(chara);
    }

    sharedFunc_800CFF74_5_s00(chara);
    sharedFunc_800D029C_5_s00(chara);
    sharedFunc_800D26D8_5_s00(chara);
    sharedFunc_800D2844_5_s00(chara, anmHdr, coords);
    sharedFunc_800D2C18_5_s00(chara);
    sharedFunc_800D3300_5_s00(chara);
}
