void sharedFunc_800E71E8_2_s00(s_SubCharacter* groaner)
{
    s32    keyframeIdx;
    q19_12 sfxVol;
    s32    sfxPitch;
    s32    temp_a0;

    #define groanerProps groaner->properties_E4.groaner

    if (groanerProps.timer_10C > Q12(0.0f))
    {
        groanerProps.timer_10C -= g_DeltaTime0;
        if (groanerProps.timer_10C <= Q12(0.0f))
        {
            groanerProps.timer_10C = Q12(0.0f);
            groanerProps.field_10E = 0;
        }
    }
    else if (groanerProps.timer_10C < Q12(0.0f))
    {
        groanerProps.timer_10C += g_DeltaTime0;
        if (groanerProps.timer_10C >= Q12(0.0f))
        {
            func_8005DC1C(Sfx_Unk1411, &groaner->position_18, Q8(0.5f), 0);
            groanerProps.timer_10C = Q12(2.0f);
        }
    }

    switch (groanerProps.field_10E)
    {
        default:
            temp_a0 = groanerProps.field_10F;
            if (temp_a0 == 4)
            {
                groanerProps.timer_10C = Q12(1.0f);
                groanerProps.field_10E = temp_a0;

                if (groaner->health_B0 > Q12(0.0f) &&
                    (groanerProps.flags_E8.val32 & (GroanerFlag_3 | GroanerFlag_12)) == GroanerFlag_3)
                {
                    func_8005DC1C(Sfx_Unk1409, &groaner->position_18, Q8(0.5f), 0);
                }
                else
                {
                    func_8005DC1C(Sfx_Unk1414, &groaner->position_18, Q8(0.5f), 0);
                }

                groanerProps.flags_E8.val16[0] &= ~GroanerFlag_12;
                break;
            }
            else if (groanerProps.field_10E != 2 && temp_a0 == 2)
            {
                groanerProps.timer_10C = Q12(-0.3f);
                groanerProps.field_10E = temp_a0;
                break;
            }

        case 4:
            // TODO: These 10E/10F checks load word from 0x10C and ANDs the upper 16 bits, not even a bitfield, weird.
            if (groanerProps.field_10E == 0 && groanerProps.field_10F == 0 &&
                (groaner->health_B0 > Q12(0.0f)))
            {
                if (groaner->model_0.anim_4.status_0 == 33)
                {
                    func_8005DC1C(Sfx_Unk1410, &groaner->position_18, Q8(0.25f), 0);
                    groanerProps.timer_10C = Rng_GenerateInt(Q12(0.5f), Q12(0.6f) - 1);
                    groanerProps.field_10E = 3;
                }
                else if (ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_10 &&
                         ANIM_STATUS_IDX_GET(groaner->model_0.anim_4.status_0) != GroanerAnim_15 &&
                         !Rng_TestProbabilityBits(4))
                {
                    func_8005DC1C(Sfx_Unk1406, &groaner->position_18, (Q12_DIV(groaner->health_B0, Q12(280.0f)) >> 7) + 32, 0);
                    groanerProps.timer_10C = Rng_GenerateInt(Q12(4.8f), Q12(8.0f) - 2);
                    groanerProps.field_10E = 1;
                }
            }
            break;
    }

    groanerProps.field_10F = 0;

    keyframeIdx = FP_FROM(groaner->model_0.anim_4.time_4, Q12_SHIFT);
    sfxVol      = (Q12_DIV(groaner->moveSpeed_38, Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f))) >> 6) + 64;
    sfxPitch    = (Q12_DIV(groaner->moveSpeed_38, Q12_MULT_PRECISE(groanerProps.field_114, Q12(3.6f))) >> 7) + Rng_TestProbabilityBits(3);

    if ((keyframeIdx > 365 && keyframeIdx < 370) ||
        (keyframeIdx > 374 && keyframeIdx < 382))
    {
        if (groanerProps.field_110 == 0)
        {
            func_8005DD44(Sfx_Unk1413, &groaner->position_18, sfxVol, sfxPitch);
            groanerProps.field_110++;
        }
    }
    else
    {
        groanerProps.field_110 = 0;
    }

    if ((keyframeIdx > 367 && keyframeIdx < 373) ||
        (keyframeIdx > 390 && keyframeIdx < 397))
    {
        if (groanerProps.field_111 == 0)
        {
            func_8005DD44(Sfx_Unk1413, &groaner->position_18, sfxVol, sfxPitch);
            groanerProps.field_111++;
        }
    }
    else
    {
        groanerProps.field_111 = 0;
    }

    #undef groanerProps
}
