void sharedFunc_800D7BE8_0_s00(s_SubCharacter* chara)
{
    if ((u8)chara->properties_E4.larvalStalker.properties_E8[8].val8[2] == 0)
    {
        if (!(chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 10)))
        {
            if (!(chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 6)) && chara->model_0.state_2 != 12)
            {
                chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += g_DeltaTime0;
                Rng_Rand16();
            }
        }
    }
    else
    {
        switch (chara->properties_E4.larvalStalker.properties_E8[6].val16[1])
        {
            case 0x555:
                if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(0.2f) && chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < Q12(1.2f))
                {
                    func_8005DC1C(0x555, &chara->position_18, 128, 0);
                    chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += Q12(1.0f);
                }
                else if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < 0 || chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(1.8f))
                {
                    chara->properties_E4.larvalStalker.properties_E8[8].val8[2] = 0;
                }

                chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += g_DeltaTime0;
                return;
            case 0x554:
                chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += g_DeltaTime0;
                if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] <= Q12(0.6f) || chara->properties_E4.larvalStalker.properties_E8[8].val16[0] >= Q12(1.6f))
                {
                    if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < 0 || chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(2.8f))
                    {
                        chara->properties_E4.larvalStalker.properties_E8[8].val8[2] = 0;
                    }
                    return;
                }

                func_8005DC1C(chara->properties_E4.larvalStalker.properties_E8[6].val16[1], &chara->position_18, 0x80, 0);
                chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += Q12(1.0f);
                return;
            case 0x553:
                chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += g_DeltaTime0;
                if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < 0 || chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(0.5f))
                {
                    if (Rng_Rand16() % 8)
                    {
                        func_8005DC1C(0x553, &chara->position_18, 128, 0);
                    }
                    chara->properties_E4.larvalStalker.properties_E8[8].val8[2] = 0;
                    return;
                }
                break;
            case 0x556:
                chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += g_DeltaTime0;
                if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(0.2f) && chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < Q12(1.2f))
                {
                    func_8005DC1C(chara->properties_E4.larvalStalker.properties_E8[6].val16[1], &chara->position_18, 128, 0);
                    chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += Q12(1.0f);
                }
                else if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < 0 || chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(3.0f))
                {
                    chara->properties_E4.larvalStalker.properties_E8[8].val8[2] = 0;
                }
                break;
        }
    }
}
