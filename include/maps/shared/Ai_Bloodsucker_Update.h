void Ai_Bloodsucker_Update(s_SubCharacter* chara, s32 arg1, GsCOORDINATE2* coords)
{
    u32 animIdxDiv2;
    s32 stateStepMul2;

    if (chara->model_0.state_2 == 0)
    {
        Ai_Bloodsucker_Init(chara);
    }

    switch (chara->model_0.state_2)
    {
        case 1:
            sharedFunc_800D0E20_3_s03(chara);
            break;

        case 2:
            sharedSymbol_800D0E38_3_s03(chara);
            break;

        case 3:
            sharedFunc_800D0E80_3_s03(chara);
            break;

        case 4:
            sharedSymbol_800D0ECC_3_s03(chara);
            break;
    }

    sharedFunc_800D0F28_3_s03(chara, arg1, coords);

    if (g_SysWork.field_22A0 & (1 << 6))
    {
        chara->properties_E4.larvalStalker.properties_E8[13].val32 &= ~(1 << 0);
        chara->properties_E4.larvalStalker.properties_E8[13].val32 &= ~(1 << 1);
    }

    if (chara->model_0.stateStep_3 != 0)
    {
        return;
    }

    if (!(chara->properties_E4.larvalStalker.properties_E8[13].val32 & (1 << 0)))
    {
        Sd_EngineCmd(0x5F5);
        chara->properties_E4.larvalStalker.properties_E8[13].val32 |= 1 << 0;
    }

    func_8005DE0C(0x5F5, &chara->position_18, chara->properties_E4.larvalStalker.properties_E8[1].val32 >> 5, 0x10000, 0);

    if (chara->properties_E4.larvalStalker.properties_E8[1].val32 < chara->properties_E4.larvalStalker.properties_E8[2].val32)
    {
        chara->properties_E4.larvalStalker.properties_E8[1].val32 += FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 0.5f, Q12_SHIFT);

        if (chara->properties_E4.larvalStalker.properties_E8[1].val32 > chara->properties_E4.larvalStalker.properties_E8[2].val32)
        {
            chara->properties_E4.larvalStalker.properties_E8[1].val32 = chara->properties_E4.larvalStalker.properties_E8[2].val32;
        }
    }
    else if (chara->properties_E4.larvalStalker.properties_E8[1].val32 > chara->properties_E4.larvalStalker.properties_E8[2].val32)
    {
        chara->properties_E4.larvalStalker.properties_E8[1].val32 -= FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 0.5f, Q12_SHIFT);

        if (chara->properties_E4.larvalStalker.properties_E8[1].val32 < chara->properties_E4.larvalStalker.properties_E8[2].val32)
        {
            chara->properties_E4.larvalStalker.properties_E8[1].val32 = chara->properties_E4.larvalStalker.properties_E8[2].val32;
        }
    }

    animIdxDiv2   = chara->model_0.anim_4.animIdx_0 / 2;
    stateStepMul2 = chara->model_0.stateStep_3 * 2;

    if (animIdxDiv2 == (stateStepMul2 + 23) / 2 || animIdxDiv2 == (stateStepMul2 + 17) / 2)
    {
        if (!(chara->properties_E4.larvalStalker.properties_E8[13].val32 & (1 << 1)))
        {
            chara->properties_E4.larvalStalker.properties_E8[13].val32 |= 1 << 1;
            Sd_EngineCmd(0x5F7);
        }

        chara->properties_E4.larvalStalker.properties_E8[3].val32 += FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 2.0f, Q12_SHIFT);

        if (chara->properties_E4.larvalStalker.properties_E8[3].val32 > FP_FLOAT_TO(1.0f, Q12_SHIFT))
        {
            chara->properties_E4.larvalStalker.properties_E8[3].val32 = FP_FLOAT_TO(1.0f, Q12_SHIFT);
        }

        func_8005DE0C(0x5F7, &chara->position_18, chara->properties_E4.larvalStalker.properties_E8[3].val32 >> 5, 0x10000, 0);
    }
    else if (chara->properties_E4.larvalStalker.properties_E8[13].val32 & (1 << 1))
    {
        chara->properties_E4.larvalStalker.properties_E8[3].val32 -= FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 2.0f, Q12_SHIFT);

        if (chara->properties_E4.larvalStalker.properties_E8[3].val32 < 0)
        {
            chara->properties_E4.larvalStalker.properties_E8[3].val32 = 0;
            chara->properties_E4.larvalStalker.properties_E8[13].val32 &= ~(1 << 1);
            func_8004690C(0x5F7);
        }
    }
}
