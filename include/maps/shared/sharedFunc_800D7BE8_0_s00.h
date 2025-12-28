void sharedFunc_800D7BE8_0_s00(s_SubCharacter* stalker)
{
    #define stalkerProps stalker->properties_E4.stalker

    if (stalkerProps.field_10A == 0)
    {
        if (!(stalkerProps.flags_E8 & StalkerFlag_10))
        {
            if (!(stalkerProps.flags_E8 & StalkerFlag_6) && stalker->model_0.state_2 != 12)
            {
                stalkerProps.timer_108 += g_DeltaTime0;
                Rng_Rand16();
            }
        }
    }
    else
    {
        switch (stalkerProps.sfxId_102)
        {
            case Sfx_Unk1365:
                if (stalkerProps.timer_108 > Q12(0.2f) &&
                    stalkerProps.timer_108 < Q12(1.2f))
                {
                    func_8005DC1C(Sfx_Unk1365, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    stalkerProps.timer_108 += Q12(1.0f);
                }
                else if (stalkerProps.timer_108 < Q12(0.0f) ||
                         stalkerProps.timer_108 > Q12(1.8f))
                {
                    stalkerProps.field_10A = 0;
                }

                stalkerProps.timer_108 += g_DeltaTime0;
                break;

            case Sfx_Unk1364:
                stalkerProps.timer_108 += g_DeltaTime0;
                if (stalkerProps.timer_108 <= Q12(0.6f) ||
                    stalkerProps.timer_108 >= Q12(1.6f))
                {
                    if (stalkerProps.timer_108 < Q12(0.0f) ||
                        stalkerProps.timer_108 > Q12(2.8f))
                    {
                        stalkerProps.field_10A = 0;
                    }
                    break;
                }

                func_8005DC1C(stalkerProps.sfxId_102, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                stalkerProps.timer_108 += Q12(1.0f);
                break;

            case Sfx_Unk1363:
                stalkerProps.timer_108 += g_DeltaTime0;
                if (stalkerProps.timer_108 < Q12(0.0f) ||
                    stalkerProps.timer_108 > Q12(0.5f))
                {
                    if (Rng_GenerateInt(0, 7)) // 7 in 8 chance?
                    {
                        func_8005DC1C(Sfx_Unk1363, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    }

                    stalkerProps.field_10A = 0;
                }
                break;

            case Sfx_Unk1366:
                stalkerProps.timer_108 += g_DeltaTime0;
                if (stalkerProps.timer_108 > Q12(0.2f) &&
                    stalkerProps.timer_108 < Q12(1.2f))
                {
                    func_8005DC1C(stalkerProps.sfxId_102, &stalker->position_18, Q8_CLAMPED(0.5f), 0);
                    stalkerProps.timer_108 += Q12(1.0f);
                }
                else if (stalkerProps.timer_108 < Q12(0.0f) ||
                         stalkerProps.timer_108 > Q12(3.0f))
                {
                    stalkerProps.field_10A = 0;
                }
                break;
        }
    }

    #undef stalkerProps
}
