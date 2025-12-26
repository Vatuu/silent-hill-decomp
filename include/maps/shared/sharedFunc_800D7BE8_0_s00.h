void sharedFunc_800D7BE8_0_s00(s_SubCharacter* stalker)
{
    if ((u8)stalker->properties_E4.dummy.properties_E8[8].val8[2] == 0)
    {
        if (!(stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 10)))
        {
            if (!(stalker->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 6)) && stalker->model_0.state_2 != 12)
            {
                stalker->properties_E4.dummy.properties_E8[8].val16[0] += g_DeltaTime0;
                Rng_Rand16();
            }
        }
    }
    else
    {
        switch (stalker->properties_E4.dummy.properties_E8[6].val16[1])
        {
            case Sfx_Unk1365:
                if (stalker->properties_E4.dummy.properties_E8[8].val16[0] > Q12(0.2f) &&
                    stalker->properties_E4.dummy.properties_E8[8].val16[0] < Q12(1.2f))
                {
                    func_8005DC1C(Sfx_Unk1365, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    stalker->properties_E4.dummy.properties_E8[8].val16[0] += Q12(1.0f);
                }
                else if (stalker->properties_E4.dummy.properties_E8[8].val16[0] < Q12(0.0f) ||
                         stalker->properties_E4.dummy.properties_E8[8].val16[0] > Q12(1.8f))
                {
                    stalker->properties_E4.dummy.properties_E8[8].val8[2] = 0;
                }

                stalker->properties_E4.dummy.properties_E8[8].val16[0] += g_DeltaTime0;
                break;

            case Sfx_Unk1364:
                stalker->properties_E4.dummy.properties_E8[8].val16[0] += g_DeltaTime0;
                if (stalker->properties_E4.dummy.properties_E8[8].val16[0] <= Q12(0.6f) ||
                    stalker->properties_E4.dummy.properties_E8[8].val16[0] >= Q12(1.6f))
                {
                    if (stalker->properties_E4.dummy.properties_E8[8].val16[0] < Q12(0.0f) ||
                        stalker->properties_E4.dummy.properties_E8[8].val16[0] > Q12(2.8f))
                    {
                        stalker->properties_E4.dummy.properties_E8[8].val8[2] = 0;
                    }
                    break;
                }

                func_8005DC1C(stalker->properties_E4.dummy.properties_E8[6].val16[1], &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                stalker->properties_E4.dummy.properties_E8[8].val16[0] += Q12(1.0f);
                break;

            case Sfx_Unk1363:
                stalker->properties_E4.dummy.properties_E8[8].val16[0] += g_DeltaTime0;
                if (stalker->properties_E4.dummy.properties_E8[8].val16[0] < Q12(0.0f) ||
                    stalker->properties_E4.dummy.properties_E8[8].val16[0] > Q12(0.5f))
                {
                    if (Rng_GenerateInt(0, 7) != 0) // 1 in 8 chance.
                    {
                        func_8005DC1C(Sfx_Unk1363, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    }

                    stalker->properties_E4.dummy.properties_E8[8].val8[2] = 0;
                }
                break;

            case Sfx_Unk1366:
                stalker->properties_E4.dummy.properties_E8[8].val16[0] += g_DeltaTime0;
                if (stalker->properties_E4.dummy.properties_E8[8].val16[0] > Q12(0.2f) &&
                    stalker->properties_E4.dummy.properties_E8[8].val16[0] < Q12(1.2f))
                {
                    func_8005DC1C(stalker->properties_E4.dummy.properties_E8[6].val16[1], &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    stalker->properties_E4.dummy.properties_E8[8].val16[0] += Q12(1.0f);
                }
                else if (stalker->properties_E4.dummy.properties_E8[8].val16[0] < Q12(0.0f) ||
                         stalker->properties_E4.dummy.properties_E8[8].val16[0] > Q12(3.0f))
                {
                    stalker->properties_E4.dummy.properties_E8[8].val8[2] = 0;
                }
                break;
        }
    }
}
