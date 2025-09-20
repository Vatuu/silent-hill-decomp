void Ai_BloodyLisa_Update(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords)
{
    if (chara->model_0.state_2 == 0)
    {
        Ai_BloodyLisa_Init(chara);
    }

    sharedFunc_800D5B3C_7_s01(chara, coords);
    sharedFunc_800D59A4_7_s01(chara, coords);
    sharedFunc_800D595C_7_s01(chara, anmHeader, coords);
}
