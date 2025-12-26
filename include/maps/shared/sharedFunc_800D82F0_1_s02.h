void sharedFunc_800D82F0_1_s02(s_SubCharacter* creeper)
{
    bool cond;

    Chara_MoveSpeedUpdate3(creeper, Q12(4.0f), Q12(0.0f));

    creeper->properties_E4.creeper.timer_104 += g_DeltaTime0;

    if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
        cond = func_8006FD90(creeper, 2, Q12(12.0f), Q12(8.0f));
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 1)) &&
             (g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & (1 << 0)))
    {
        cond = func_8006FD90(creeper, 2, Q12(0.8f), Q12(0.4f));
    }
    else
    {
        cond = func_8006FD90(creeper, 2, Q12(4.0f), Q12(12.0f));
    }

    cond |= func_80070360(creeper, Q12(0.0f), Q12(0.5f));
    if (cond)
    {
        creeper->flags_3E |= CharaFlag_Unk3;

        if (Rng_GenerateUInt(0, 7) == 0 && // 1 in 8 chance.
            creeper->model_0.anim_4.status_0 == ANIM_STATUS(CreeperAnim_11, true))
        {
            creeper->model_0.state_2                 = 2;
            creeper->model_0.anim_4.status_0         = ANIM_STATUS(CreeperAnim_13, false);
            creeper->properties_E4.creeper.timer_F0  = Q12(0.5f);
            creeper->properties_E4.creeper.timer_104 = Q12(0.0f);
            return;
        }
    }

    // Check if Creeper was alerted.
    if (creeper->properties_E4.creeper.flags_E8 & CreeperFlag_Alerted)
    {
        creeper->model_0.state_2                 = 2;
        creeper->model_0.anim_4.status_0         = ANIM_STATUS(CreeperAnim_13, false);
        creeper->properties_E4.creeper.timer_F0  = Q12(0.5f);
        creeper->properties_E4.creeper.timer_104 = Q12(0.0f);
    }
    else if (creeper->properties_E4.creeper.flags_E8 & CreeperFlag_6)
    {
        if (creeper->properties_E4.creeper.flags_E8 & CreeperFlag_7)
        {
            if (Rng_GenerateUInt(0, 7) == 0) // 1 in 8 chance.
            {
                if (creeper->properties_E4.creeper.timer_104 > Q12(0.5f))
                {
                    if (creeper->properties_E4.creeper.timer_104 < Q12(2.5f))
                    {
                        func_8005DC1C(Sfx_Unk1427, &creeper->position_18, Q8_CLAMPED(0.5f), 0);

                        creeper->properties_E4.creeper.timer_104 = Q12(0.0f);
                        sharedData_800E57CC_1_s02--;
                        creeper->properties_E4.creeper.flags_E8 &= ~CreeperFlag_7;
                    }
                }
            }
        }
        else if (sharedData_800E57CC_1_s02 == 0)
        {
            if (Rng_GenerateUInt(0, 511) == 0 && // 1 in 512 chance.
                creeper->properties_E4.creeper.timer_104 > Q12(4.0f))
            {
                s32 i;

                func_8005DC1C(Sfx_Unk1427, &creeper->position_18, Q8_CLAMPED(0.5f), 0);
                creeper->properties_E4.creeper.timer_104 = Q12(0.0f);

                for (i = 0; i < ARRAY_SIZE(g_SysWork.npcs_1A0); i++)
                {
                    if (g_SysWork.npcs_1A0[i].model_0.charaId_0 == Chara_Creeper &&
                        g_SysWork.npcs_1A0[i].field_40 != creeper->field_40 &&
                        (g_SysWork.npcs_1A0[i].properties_E4.creeper.flags_E8 & CreeperFlag_6) &&
                        g_SysWork.npcs_1A0[i].model_0.state_2 == 1 &&
                        !Math_Distance2dCheck(&creeper->position_18, &g_SysWork.npcs_1A0[i].position_18, Q12(16.0f)))
                    {
                        g_SysWork.npcs_1A0[i].properties_E4.creeper.timer_104 = Q12(0.0f);
                        sharedData_800E57CC_1_s02++;
                        g_SysWork.npcs_1A0[i].properties_E4.creeper.flags_E8 |= CreeperFlag_7;
                    }
                }
            }
            else if (Rng_GenerateUInt(0, 63) == 0 && // 1 in 64 chance.
                     creeper->properties_E4.creeper.timer_104 > Q12(2.0f))
            {
                func_8005DC1C(Sfx_Unk1426, &creeper->position_18, Q8_CLAMPED(0.5f), 0);
                creeper->properties_E4.creeper.timer_104 = Rng_GenerateInt(Q12(0.8f), Q12(1.8f) - 1);
            }
        }
    }
}
