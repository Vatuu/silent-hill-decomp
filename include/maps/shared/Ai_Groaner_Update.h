void Ai_Groaner_Update(s_SubCharacter* chara, s32 arg1, s32 arg2)
{
    u8 var;

    // `stage_2` suggests it's initialized?
    if (chara->model_0.stage_2 == 0)
    {
        sharedFunc_800E3074_2_s00(chara); // Init func?
    }

    var = chara->model_0.stage_2;

    if (g_DeltaTime0 != 0)
    {
        sharedFunc_800E33DC_2_s00(chara);
        sharedFunc_800E384C_2_s00(chara);
        sharedFunc_800E5AA4_2_s00(chara);
    }

    sharedFunc_800E5EC4_2_s00(chara, arg1, arg2);

    if (g_DeltaTime0 != 0)
    {
        sharedFunc_800E6338_2_s00(chara); // Control func with state machine?
        sharedFunc_800E71E8_2_s00(chara);

        if (chara->model_0.stage_2 != (var & 0xFF))
        {
            *(u16*)&chara->properties_E4.player.properties_E4[1] &= ~(1 << 8);
        }

        if ((u16)chara->properties_E4.player.properties_E4[1] & (1 << 7))
        {
            chara->field_3E |= 1 << 2;
        }
    }
}
