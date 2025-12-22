void sharedFunc_800D82F0_1_s02(s_SubCharacter* creaper)
{
    bool cond;

    Chara_MoveSpeedUpdate3(creaper, Q12(4.0f), Q12(0.0f));

    creaper->properties_E4.player.field_104 += g_DeltaTime0;

    if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & 3) == 2)
    {
        cond = func_8006FD90(creaper, 2, Q12(12.0f), Q12(8.0f));
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 2) &&
             (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 1))
    {
        cond = func_8006FD90(creaper, 2, Q12(0.8f), Q12(0.4f));
    }
    else
    {
        cond = func_8006FD90(creaper, 2, Q12(4.0f), Q12(12.0f));
    }

    cond |= func_80070360(creaper, Q12(0.0f), Q12(0.5f));

    if (cond)
    {
        creaper->flags_3E |= CharaFlag_Unk3;

        if (Rng_GenerateUInt(0, 7) == 0 && creaper->model_0.anim_4.status_0 == ANIM_STATUS(11, true))
        {
            creaper->model_0.state_2                = 2;
            creaper->model_0.anim_4.status_0        = ANIM_STATUS(13, false);
            creaper->properties_E4.player.field_F0  = Q12(0.5f);
            creaper->properties_E4.player.field_104 = 0;
            return;
        }
    }

    if (creaper->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 8))
    {
        creaper->model_0.state_2                = 2;
        creaper->model_0.anim_4.status_0        = ANIM_STATUS(13, false);
        creaper->properties_E4.player.field_F0  = Q12(0.5f);
        creaper->properties_E4.player.field_104 = 0;
    }
    else if (creaper->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 6))
    {
        if (creaper->properties_E4.dummy.properties_E8[0].val16[0] & (1 << 7))
        {
            if (Rng_GenerateUInt(0, 7) == 0)
            {
                if (creaper->properties_E4.player.field_104 > Q12(0.5f))
                {
                    if (creaper->properties_E4.player.field_104 < Q12(2.5f))
                    {
                        func_8005DC1C(Sfx_Unk1427, &creaper->position_18, Q8_CLAMPED(0.5f), 0);
                        creaper->properties_E4.player.field_104 = 0;
                        sharedData_800E57CC_1_s02--;
                        creaper->properties_E4.dummy.properties_E8[0].val16[0] &= ~(1 << 7);
                    }
                }
            }
        }
        else if (sharedData_800E57CC_1_s02 == 0)
        {
            if (Rng_GenerateUInt(0, 511) == 0 && creaper->properties_E4.player.field_104 > Q12(4.0f))
            {
                s32 i;

                func_8005DC1C(Sfx_Unk1427, &creaper->position_18, Q8_CLAMPED(0.5f), 0);
                creaper->properties_E4.player.field_104 = 0;

                for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
                {
                    if ((g_SysWork.npcs_1A0[i].model_0.charaId_0 == Chara_Creaper) &&
                        g_SysWork.npcs_1A0[i].field_40 != creaper->field_40 &&
                        g_SysWork.npcs_1A0[i].properties_E4.dummy.properties_E8[0].val16[0] & (1 << 6) &&
                        g_SysWork.npcs_1A0[i].model_0.state_2 == 1 &&
                        !Math_Distance2dCheck(&creaper->position_18, &g_SysWork.npcs_1A0[i].position_18, Q12(16.0f)))
                    {
                        g_SysWork.npcs_1A0[i].properties_E4.player.field_104 = 0;
                        sharedData_800E57CC_1_s02++;
                        g_SysWork.npcs_1A0[i].properties_E4.dummy.properties_E8[0].val16[0] |= (1 << 7);
                    }
                }
            }
            else if (Rng_GenerateUInt(0, 63) == 0 && creaper->properties_E4.player.field_104 > Q12(2.0f))
            {
                func_8005DC1C(Sfx_Unk1426, &creaper->position_18, Q8_CLAMPED(0.5f), 0);

                creaper->properties_E4.player.field_104 = Rng_GenerateInt(Q12(0.8f), Q12(1.8f) - 1);
            }
        }
    }
}
