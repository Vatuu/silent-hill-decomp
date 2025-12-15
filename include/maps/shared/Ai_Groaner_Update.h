void Ai_Groaner_Update(s_SubCharacter* groaner, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    u8 var;

    if (groaner->model_0.state_2 == 0)
    {
        Ai_Groaner_Init(groaner);
    }

    var = groaner->model_0.state_2;

    if (g_DeltaTime0 != Q12(0.0f))
    {
        sharedFunc_800E33DC_2_s00(groaner);
        sharedFunc_800E384C_2_s00(groaner);
        sharedFunc_800E5AA4_2_s00(groaner);
    }

    sharedFunc_800E5EC4_2_s00(groaner, anmHdr, coords);

    if (g_DeltaTime0 != Q12(0.0f))
    {
        sharedFunc_800E6338_2_s00(groaner); // Control func with state machine?
        sharedFunc_800E71E8_2_s00(groaner);

        if (groaner->model_0.state_2 != var)
        {
            *(u16*)&groaner->properties_E4.player.afkTimer_E8 &= ~(1 << 8);
        }

        if ((u16)groaner->properties_E4.player.afkTimer_E8 & (1 << 7))
        {
            groaner->flags_3E |= CharaFlag_Unk3;
        }
    }
}
