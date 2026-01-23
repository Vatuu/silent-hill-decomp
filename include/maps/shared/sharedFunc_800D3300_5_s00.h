void sharedFunc_800D3300_5_s00(s_SubCharacter* scratcher)
{
#define animKeyframeIdx FP_FROM(scratcher->model_0.anim_4.time_4, Q12_SHIFT)

    if (scratcher->properties_E4.hangedScratcher.timer_100 != Q12(0.0f))
    {
        if (scratcher->properties_E4.hangedScratcher.timer_100 > Q12(0.0f))
        {
            scratcher->properties_E4.hangedScratcher.timer_100 -= g_DeltaTime0;
            if (scratcher->properties_E4.hangedScratcher.timer_100 <= Q12(0.0f))
            {
                scratcher->properties_E4.hangedScratcher.timer_100 = Q12(0.0f);
            }
        }
        else
        {
            scratcher->properties_E4.hangedScratcher.timer_100 += g_DeltaTime0;
            if (scratcher->properties_E4.hangedScratcher.timer_100 >= 0)
            {
                scratcher->properties_E4.hangedScratcher.timer_100 = Q12(0.75f);
                func_8005DC1C(Sfx_Unk1580, &scratcher->position_18, Q8(0.5f), 0);
            }
        }
    }
    else
    {
        if (scratcher->properties_E4.hangedScratcher.flags_E8 & (1 << 5))
        {
            if (scratcher->properties_E4.hangedScratcher.flags_E8 & (1 << 0))
            {
                func_8005DC1C(Sfx_Unk1584, &scratcher->position_18, Q8(0.5f), 0);
            }
            else
            {
                func_8005DC1C(Sfx_Unk1579, &scratcher->position_18, Q8(0.5f), 0);
            }

            scratcher->properties_E4.hangedScratcher.timer_100 = Q12(0.5f);
        }
        else
        {
            if (scratcher->properties_E4.hangedScratcher.flags_E8 & (1 << 4))
            {
                scratcher->properties_E4.hangedScratcher.timer_100 = Q12(-0.3f);
            }
        }

        switch (scratcher->model_0.controlState_2)
        {
            case 1:
            case 16:
                if (scratcher->properties_E4.hangedScratcher.timer_108 == Q12(0.0f))
                {
                    if (!Rng_GenerateInt(0, 511))
                    {
                        if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                                g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) > Q12(6.5f))
                        {
                            scratcher->properties_E4.hangedScratcher.timer_108 = Rng_GenerateInt(Q12(3.5f), Q12(8.0f) - 1);
                            func_8005DC1C(Sfx_Unk1583, &scratcher->position_18, Q8(0.5f), 0);
                        }
                    }
                }
                else
                {
                    scratcher->properties_E4.hangedScratcher.timer_108 -= g_DeltaTime0;
                    if (scratcher->properties_E4.hangedScratcher.timer_108 < Q12(0.0f))
                    {
                        scratcher->properties_E4.hangedScratcher.timer_108 = Q12(0.0f);
                    }
                }
                break;

            case 2:
            case 3:
            case 5:
            case 6:
            case 7:
                if (scratcher->properties_E4.hangedScratcher.timer_108 == Q12(0.0f))
                {
                    if (!Rng_GenerateUInt(0, 255))
                    {
                        if (Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - scratcher->position_18.vx,
                                                g_SysWork.playerWork_4C.player_0.position_18.vz - scratcher->position_18.vz) > Q12(4.5f))
                        {
                            scratcher->properties_E4.hangedScratcher.timer_108 = Rng_GenerateInt(Q12(3.5f), Q12(7.5f) - 1);
                            func_8005DC1C(Sfx_Unk1583, &scratcher->position_18, Q8(0.5f), 0);
                        }
                    }
                }
                else
                {
                    scratcher->properties_E4.hangedScratcher.timer_108 -= g_DeltaTime0;
                    if (scratcher->properties_E4.hangedScratcher.timer_108 < Q12(0.0f))
                    {
                        scratcher->properties_E4.hangedScratcher.timer_108 = Q12(0.0f);
                    }
                }
                break;
        }
    }

    scratcher->properties_E4.hangedScratcher.flags_E8 &= ~((1 << 4) | (1 << 5));

    // TODO: Can the `+ 88` etc below be added into the Rng macro calls? (Couldn't match with that yet)
    if (scratcher->model_0.anim_4.status_0 == 35)
    {
        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 272, 273))
        {
            if (scratcher->properties_E4.hangedScratcher.field_103 == 0)
            {
                func_8005DD44(Sfx_Unk1578, &scratcher->position_18, Q8(0.125f),
                              Rng_GenerateUInt(0, 15) + ((FP_TO(scratcher->moveSpeed_38, Q12_SHIFT) / Q12(3.0f)) >> 5) + 88);
                scratcher->properties_E4.hangedScratcher.field_103 = 1;
            }
        }
        else
        {
            scratcher->properties_E4.hangedScratcher.field_103 = 0;
        }

        if (animKeyframeIdx == 276 || animKeyframeIdx == 267)
        {
            if (scratcher->properties_E4.hangedScratcher.field_102 == 0)
            {
                func_8005DD44(Sfx_Unk1578, &scratcher->position_18, Q8(0.125f),
                              Rng_GenerateUInt(0, 15) + ((FP_TO(scratcher->moveSpeed_38, Q12_SHIFT) / Q12(3.0f)) >> 5) + 88);
                scratcher->properties_E4.hangedScratcher.field_102 = 1;
            }
        }
        else
        {
            scratcher->properties_E4.hangedScratcher.field_102 = 0;
        }
    }
    else if (scratcher->model_0.anim_4.status_0 == 37)
    {
        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 285, 286))
        {
            if (scratcher->properties_E4.hangedScratcher.field_103 == 0)
            {
                func_8005DD44(Sfx_Unk1578, &scratcher->position_18, Q8(0.5f),
                              Rng_GenerateUInt(0, 15) + ((FP_TO(scratcher->moveSpeed_38, Q12_SHIFT) / Q12(2.8f)) >> 5) + 120);
                scratcher->properties_E4.hangedScratcher.field_103 = 1;
            }
        }
        else
        {
            scratcher->properties_E4.hangedScratcher.field_103 = 0;
        }

        if (ANIM_TIME_RANGE_CHECK(scratcher->model_0.anim_4.time_4, 277, 278))
        {
            if (scratcher->properties_E4.hangedScratcher.field_102 == 0)
            {
                func_8005DD44(Sfx_Unk1578, &scratcher->position_18, Q8(0.5f),
                              Rng_GenerateUInt(0, 15) + ((FP_TO(scratcher->moveSpeed_38, Q12_SHIFT) / Q12(2.8f)) >> 5) + 120);
                scratcher->properties_E4.hangedScratcher.field_102 = 1;
            }
        }
        else
        {
            scratcher->properties_E4.hangedScratcher.field_102 = 0;
        }
    }
    else if (scratcher->model_0.anim_4.status_0 == 3)
    {
        if (scratcher->properties_E4.hangedScratcher.field_103 < 3)
        {
            s32 temp_v1 = (scratcher->properties_E4.hangedScratcher.field_103 + 1) * 11;
            if (animKeyframeIdx >= temp_v1 && (animKeyframeIdx < temp_v1 + 2))
            {
                func_8005DD44(Sfx_Unk1578, &scratcher->position_18, Q8(0.5f), -16);
                scratcher->properties_E4.hangedScratcher.field_103++;
            }
        }
    }
    else
    {
        scratcher->properties_E4.hangedScratcher.field_102 = 0;
        scratcher->properties_E4.hangedScratcher.field_103 = 0;
    }

#undef animKeyframeIdx
}
