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
            case Sfx_Unk1365:
                if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(0.2f) &&
                    chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < Q12(1.2f))
                {
                    func_8005DC1C(Sfx_Unk1365, &chara->position_18, Q8_CLAMPED(0.5f), 0);
                    chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += Q12(1.0f);
                }
                else if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < Q12(0.0f) ||
                         chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(1.8f))
                {
                    chara->properties_E4.larvalStalker.properties_E8[8].val8[2] = 0;
                }

                chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += g_DeltaTime0;
                break;

            case Sfx_Unk1364:
                chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += g_DeltaTime0;
                if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] <= Q12(0.6f) ||
                    chara->properties_E4.larvalStalker.properties_E8[8].val16[0] >= Q12(1.6f))
                {
                    if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < Q12(0.0f) ||
                        chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(2.8f))
                    {
                        chara->properties_E4.larvalStalker.properties_E8[8].val8[2] = 0;
                    }
                    break;
                }

                func_8005DC1C(chara->properties_E4.larvalStalker.properties_E8[6].val16[1], &chara->position_18, Q8_CLAMPED(0.5f), 0);
                chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += Q12(1.0f);
                break;

            case Sfx_Unk1363:
                chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += g_DeltaTime0;
                if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < Q12(0.0f) ||
                    chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(0.5f))
                {
                    if (Rng_GenerateInt(0, 7) != 0) // 1 in 8 chance.
                    {
                        func_8005DC1C(Sfx_Unk1363, &chara->position_18, Q8_CLAMPED(0.5f), 0);
                    }

                    chara->properties_E4.larvalStalker.properties_E8[8].val8[2] = 0;
                }
                break;

            case Sfx_Unk1366:
                chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += g_DeltaTime0;
                if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(0.2f) &&
                    chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < Q12(1.2f))
                {
                    func_8005DC1C(chara->properties_E4.larvalStalker.properties_E8[6].val16[1], &chara->position_18, Q8_CLAMPED(0.5f), 0);
                    chara->properties_E4.larvalStalker.properties_E8[8].val16[0] += Q12(1.0f);
                }
                else if (chara->properties_E4.larvalStalker.properties_E8[8].val16[0] < Q12(0.0f) ||
                         chara->properties_E4.larvalStalker.properties_E8[8].val16[0] > Q12(3.0f))
                {
                    chara->properties_E4.larvalStalker.properties_E8[8].val8[2] = 0;
                }
                break;
        }
    }
}
