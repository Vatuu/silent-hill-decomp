void Ai_Bloodsucker_Update(s_SubCharacter* bloodsucker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    u32 animStatusDiv2;
    s32 stateStepMul2;

    if (bloodsucker->model_0.state_2 == 0)
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
        bloodsucker->properties_E4.larvalStalker.properties_E8[13].val32 &= ~(1 << 0);
        bloodsucker->properties_E4.larvalStalker.properties_E8[13].val32 &= ~(1 << 1);
    }

    if (bloodsucker->model_0.stateStep_3 != 0)
    {
        return;
    }

    if (!(bloodsucker->properties_E4.larvalStalker.properties_E8[13].val32 & (1 << 0)))
    {
        Sd_EngineCmd(Sfx_Unk1525);
        bloodsucker->properties_E4.larvalStalker.properties_E8[13].val32 |= 1 << 0;
    }

    func_8005DE0C(Sfx_Unk1525, &bloodsucker->position_18, bloodsucker->properties_E4.larvalStalker.properties_E8[1].val32 >> 5, 0x10000, 0);

    if (bloodsucker->properties_E4.larvalStalker.properties_E8[1].val32 < bloodsucker->properties_E4.larvalStalker.properties_E8[2].val32)
    {
        bloodsucker->properties_E4.larvalStalker.properties_E8[1].val32 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, Q12_SHIFT);

        if (bloodsucker->properties_E4.larvalStalker.properties_E8[1].val32 > bloodsucker->properties_E4.larvalStalker.properties_E8[2].val32)
        {
            bloodsucker->properties_E4.larvalStalker.properties_E8[1].val32 = bloodsucker->properties_E4.larvalStalker.properties_E8[2].val32;
        }
    }
    else if (bloodsucker->properties_E4.larvalStalker.properties_E8[1].val32 > bloodsucker->properties_E4.larvalStalker.properties_E8[2].val32)
    {
        bloodsucker->properties_E4.larvalStalker.properties_E8[1].val32 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.5f, Q12_SHIFT);

        if (bloodsucker->properties_E4.larvalStalker.properties_E8[1].val32 < bloodsucker->properties_E4.larvalStalker.properties_E8[2].val32)
        {
            bloodsucker->properties_E4.larvalStalker.properties_E8[1].val32 = bloodsucker->properties_E4.larvalStalker.properties_E8[2].val32;
        }
    }

    animStatusDiv2 = bloodsucker->model_0.anim_4.status_0 / 2;
    stateStepMul2  = bloodsucker->model_0.stateStep_3 * 2;

    if (animStatusDiv2 == (stateStepMul2 + 23) / 2 || animStatusDiv2 == (stateStepMul2 + 17) / 2)
    {
        if (!(bloodsucker->properties_E4.larvalStalker.properties_E8[13].val32 & (1 << 1)))
        {
            bloodsucker->properties_E4.larvalStalker.properties_E8[13].val32 |= 1 << 1;
            Sd_EngineCmd(Sfx_Unk1527);
        }

        bloodsucker->properties_E4.larvalStalker.properties_E8[3].val32 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 2.0f, Q12_SHIFT);

        if (bloodsucker->properties_E4.larvalStalker.properties_E8[3].val32 > Q12(1.0f))
        {
            bloodsucker->properties_E4.larvalStalker.properties_E8[3].val32 = Q12(1.0f);
        }

        func_8005DE0C(Sfx_Unk1527, &bloodsucker->position_18, bloodsucker->properties_E4.larvalStalker.properties_E8[3].val32 >> 5, 0x10000, 0);
    }
    else if (bloodsucker->properties_E4.larvalStalker.properties_E8[13].val32 & (1 << 1))
    {
        bloodsucker->properties_E4.larvalStalker.properties_E8[3].val32 -= FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 2.0f, Q12_SHIFT);

        if (bloodsucker->properties_E4.larvalStalker.properties_E8[3].val32 < 0)
        {
            bloodsucker->properties_E4.larvalStalker.properties_E8[3].val32 = 0;
            bloodsucker->properties_E4.larvalStalker.properties_E8[13].val32 &= ~(1 << 1);
            func_8004690C(Sfx_Unk1527);
        }
    }
}
