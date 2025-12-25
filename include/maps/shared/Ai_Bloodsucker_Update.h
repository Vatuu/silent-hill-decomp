void Ai_Bloodsucker_Update(s_SubCharacter* bloodsucker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    u32 animStatusDiv2;
    s32 stateStepMul2;

    if (bloodsucker->model_0.state_2 == ModelState_Uninitialized)
    {
        Ai_Bloodsucker_Init(bloodsucker);
    }

    switch (bloodsucker->model_0.state_2)
    {
        case 1:
            sharedFunc_800D0E20_3_s03(bloodsucker);
            break;

        case 2:
            sharedSymbol_800D0E38_3_s03(bloodsucker);
            break;

        case 3:
            sharedFunc_800D0E80_3_s03(bloodsucker);
            break;

        case 4:
            sharedSymbol_800D0ECC_3_s03(bloodsucker);
            break;
    }

    sharedFunc_800D0F28_3_s03(bloodsucker, anmHdr, coords);

    if (g_SysWork.sysFlags_22A0 & SysFlag_6)
    {
        bloodsucker->properties_E4.bloodsucker.flags_118 &= ~BloodsuckerFlag_0;
        bloodsucker->properties_E4.bloodsucker.flags_118 &= ~BloodsuckerFlag_1;
    }

    if (bloodsucker->model_0.stateStep_3 != 0)
    {
        return;
    }

    if (!(bloodsucker->properties_E4.bloodsucker.flags_118 & BloodsuckerFlag_0))
    {
        SD_Call(Sfx_Unk1525);
        bloodsucker->properties_E4.bloodsucker.flags_118 |= BloodsuckerFlag_0;
    }

    func_8005DE0C(Sfx_Unk1525, &bloodsucker->position_18, bloodsucker->properties_E4.bloodsucker.timer_EC >> 5, Q12(16.0f), 0);

    if (bloodsucker->properties_E4.bloodsucker.timer_EC < bloodsucker->properties_E4.bloodsucker.timer_F0)
    {
        bloodsucker->properties_E4.bloodsucker.timer_EC += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, Q12_SHIFT);
        if (bloodsucker->properties_E4.bloodsucker.timer_EC > bloodsucker->properties_E4.bloodsucker.timer_F0)
        {
            bloodsucker->properties_E4.bloodsucker.timer_EC = bloodsucker->properties_E4.bloodsucker.timer_F0;
        }
    }
    else if (bloodsucker->properties_E4.bloodsucker.timer_EC > bloodsucker->properties_E4.bloodsucker.timer_F0)
    {
        bloodsucker->properties_E4.bloodsucker.timer_EC -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, Q12_SHIFT);
        if (bloodsucker->properties_E4.bloodsucker.timer_EC < bloodsucker->properties_E4.bloodsucker.timer_F0)
        {
            bloodsucker->properties_E4.bloodsucker.timer_EC = bloodsucker->properties_E4.bloodsucker.timer_F0;
        }
    }

    animStatusDiv2 = bloodsucker->model_0.anim_4.status_0 / 2;
    stateStepMul2  = bloodsucker->model_0.stateStep_3 * 2;

    if (animStatusDiv2 == ((stateStepMul2 + 23) / 2) || animStatusDiv2 == ((stateStepMul2 + 17) / 2))
    {
        if (!(bloodsucker->properties_E4.bloodsucker.flags_118 & BloodsuckerFlag_1))
        {
            bloodsucker->properties_E4.bloodsucker.flags_118 |= BloodsuckerFlag_1;
            SD_Call(Sfx_Unk1527);
        }

        bloodsucker->properties_E4.bloodsucker.timer_F4 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 2.0f, Q12_SHIFT);
        if (bloodsucker->properties_E4.bloodsucker.timer_F4 > Q12(1.0f))
        {
            bloodsucker->properties_E4.bloodsucker.timer_F4 = Q12(1.0f);
        }

        func_8005DE0C(Sfx_Unk1527, &bloodsucker->position_18, bloodsucker->properties_E4.bloodsucker.timer_F4 >> 5, Q12(16.0f), 0);
    }
    else if (bloodsucker->properties_E4.bloodsucker.flags_118 & BloodsuckerFlag_1)
    {
        bloodsucker->properties_E4.bloodsucker.timer_F4 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 2.0f, Q12_SHIFT);
        if (bloodsucker->properties_E4.bloodsucker.timer_F4 < Q12(0.0f))
        {
            bloodsucker->properties_E4.bloodsucker.timer_F4 = Q12(0.0f);
            bloodsucker->properties_E4.bloodsucker.flags_118 &= ~BloodsuckerFlag_1;
            Sd_SfxStop(Sfx_Unk1527);
        }
    }
}
