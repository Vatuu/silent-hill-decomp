void Ai_Groaner_Update(s_SubCharacter* chara, s_AnmHeader* anmHeader, GsCOORDINATE2* coords)
{
    u8 var;

    if (chara->model_0.state_2 == 0)
    {
        Ai_Groaner_Init(chara);
    }

    var = chara->model_0.state_2;

    if (g_DeltaTime0 != FP_TIME(0.0))
    {
        sharedFunc_800E33DC_2_s00(chara);
        sharedFunc_800E384C_2_s00(chara);
        sharedFunc_800E5AA4_2_s00(chara);
    }

    sharedFunc_800E5EC4_2_s00(chara, anmHeader, coords);

    if (g_DeltaTime0 != FP_TIME(0.0))
    {
        sharedFunc_800E6338_2_s00(chara); // Control func with state machine?
        sharedFunc_800E71E8_2_s00(chara);

        if (chara->model_0.state_2 != var)
        {
            *(u16*)&chara->properties_E4.player.afkTimer_E8 &= ~(1 << 8);
        }

        if ((u16)chara->properties_E4.player.afkTimer_E8 & (1 << 7))
        {
            chara->flags_3E |= CharaFlag_Unk3;
        }
    }
}
