void sharedFunc_800D7BE8_0_s00(s_SubCharacter* stalker)
{
    if (stalker->properties_E4.stalker.field_10A == 0)
    {
        if (!(stalker->properties_E4.stalker.flags_E8 & StalkerFlag_10))
        {
            if (!(stalker->properties_E4.stalker.flags_E8 & StalkerFlag_6) && stalker->model_0.state_2 != 12)
            {
                stalker->properties_E4.stalker.timer_108 += g_DeltaTime0;
                Rng_Rand16();
            }
        }
    }
    else
    {
        switch (stalker->properties_E4.stalker.sfxId_102)
        {
            case Sfx_Unk1365:
                if (stalker->properties_E4.stalker.timer_108 > Q12(0.2f) &&
                    stalker->properties_E4.stalker.timer_108 < Q12(1.2f))
                {
                    func_8005DC1C(Sfx_Unk1365, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    stalker->properties_E4.stalker.timer_108 += Q12(1.0f);
                }
                else if (stalker->properties_E4.stalker.timer_108 < Q12(0.0f) ||
                         stalker->properties_E4.stalker.timer_108 > Q12(1.8f))
                {
                    stalker->properties_E4.stalker.field_10A = 0;
                }

                stalker->properties_E4.stalker.timer_108 += g_DeltaTime0;
                break;

            case Sfx_Unk1364:
                stalker->properties_E4.stalker.timer_108 += g_DeltaTime0;
                if (stalker->properties_E4.stalker.timer_108 <= Q12(0.6f) ||
                    stalker->properties_E4.stalker.timer_108 >= Q12(1.6f))
                {
                    if (stalker->properties_E4.stalker.timer_108 < Q12(0.0f) ||
                        stalker->properties_E4.stalker.timer_108 > Q12(2.8f))
                    {
                        stalker->properties_E4.stalker.field_10A = 0;
                    }
                    break;
                }

                func_8005DC1C(stalker->properties_E4.stalker.sfxId_102, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                stalker->properties_E4.stalker.timer_108 += Q12(1.0f);
                break;

            case Sfx_Unk1363:
                stalker->properties_E4.stalker.timer_108 += g_DeltaTime0;
                if (stalker->properties_E4.stalker.timer_108 < Q12(0.0f) ||
                    stalker->properties_E4.stalker.timer_108 > Q12(0.5f))
                {
                    if (Rng_GenerateInt(0, 7)) // 7 in 8 chance?
                    {
                        func_8005DC1C(Sfx_Unk1363, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    }

                    stalker->properties_E4.stalker.field_10A = 0;
                }
                break;

            case Sfx_Unk1366:
                stalker->properties_E4.stalker.timer_108 += g_DeltaTime0;
                if (stalker->properties_E4.stalker.timer_108 > Q12(0.2f) &&
                    stalker->properties_E4.stalker.timer_108 < Q12(1.2f))
                {
                    func_8005DC1C(stalker->properties_E4.stalker.sfxId_102, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    stalker->properties_E4.stalker.timer_108 += Q12(1.0f);
                }
                else if (stalker->properties_E4.stalker.timer_108 < Q12(0.0f) ||
                         stalker->properties_E4.stalker.timer_108 > Q12(3.0f))
                {
                    stalker->properties_E4.stalker.field_10A = 0;
                }
                break;
        }
    }
}
