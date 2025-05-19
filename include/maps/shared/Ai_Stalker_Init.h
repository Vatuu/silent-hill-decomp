static inline void ModelAnim_UpdateFieldC_Stalker(s_ModelAnim* anim, s32 fieldCValue)
{
    anim->field_C  = fieldCValue;
    anim->field_10 = 0;
}

void Ai_Stalker_Init(s_SubCharacter* arg0)
{
    s32 i;

    arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;

    for (i = 0; i < 0x10; i++)
    {
        arg0->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    arg0->health_B0 = sharedData_800E3A20_0_s00;

#ifdef MAP6_S03
    // MAP6_S03: change stalker health to 1.5x when not on easy difficulty
    if (g_SaveGamePtr->gameDifficulty_260 != GameDifficulty_Easy)
    {
        arg0->health_B0 = FP_MULTIPLY_FLOAT((s64)sharedData_800E3A20_0_s00, 1.5f, Q12_SHIFT);
    }
#endif

    arg0->moveSpeed_38   = 0;
    arg0->field_34       = 0;
    arg0->rotation_24.vz = 0;
    arg0->rotation_24.vx = 0;

    arg0->model_0.anim_4.animIdx_0      = 61;
    arg0->model_0.anim_4.time_4         = FP_TO(477, Q12_SHIFT);
    arg0->model_0.anim_4.keyframeIdx0_8 = 477;

    arg0->headingAngle_3C = arg0->rotation_24.vy;

    switch (arg0->model_0.stateStep_3)
    {
        case 11:
            arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] |= (1 << 2);
        case 3:
            arg0->properties_E4.larvalStalker.properties_E8[4].val32     = FP_FLOAT_TO(2.5f, Q12_SHIFT);
            arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] |= (1 << 0);
        case 8:
            arg0->model_0.state_2 = 4;
            arg0->field_E0_8      = 3;
            break;
        case 7:
            arg0->model_0.state_2                                        = 4;
            arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] |= (1 << 11);
            arg0->field_E0_8                                             = 3;
            break;
        case 6:
            arg0->model_0.state_2                                        = 2;
            arg0->flags_3E                                              |= (1 << 2);
            arg0->properties_E4.larvalStalker.properties_E8[4].val32     = FP_FLOAT_TO(1.0f, Q12_SHIFT);
            arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] |= ((1 << 0) | (1 << 1));
            arg0->field_E0_8                                             = 3;
            arg0->flags_3E                                              &= ~(1 << 4);
            break;
        case 5:
            arg0->model_0.state_2 = 1;
            arg0->field_E0_8      = 0;
            arg0->flags_3E       |= (1 << 4);
            break;
        case 9:
            arg0->model_0.state_2               = 12;
            arg0->model_0.anim_4.animIdx_0      = 55;
            arg0->model_0.anim_4.time_4         = FP_TO(427, Q12_SHIFT);
            arg0->model_0.anim_4.keyframeIdx0_8 = 427;
            arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] |= (1 << 0);
            arg0->field_E0_8 = 3;
            break;
        case 10:
            arg0->model_0.state_2               = 11;
            arg0->model_0.anim_4.animIdx_0      = 57;
            arg0->model_0.anim_4.time_4         = FP_TO(443, Q12_SHIFT);
            arg0->model_0.anim_4.keyframeIdx0_8 = 443;
            arg0->field_E0_8                    = 3;
            break;
        case 17:
            arg0->model_0.state_2               = 13;
            arg0->model_0.anim_4.animIdx_0      = 29;
            arg0->model_0.anim_4.time_4         = FP_TO(176, Q12_SHIFT);
            arg0->model_0.anim_4.keyframeIdx0_8 = 176;
            arg0->field_E0_8                    = 0;
            break;
    }

    arg0->model_0.stateStep_3 = 0;

    arg0->properties_E4.larvalStalker.properties_E8[6].val16[1] = NO_VALUE;
    arg0->properties_E4.larvalStalker.properties_E8[2].val32    = arg0->position_18.vx;
    arg0->properties_E4.larvalStalker.properties_E8[3].val32    = arg0->position_18.vz;
    arg0->properties_E4.larvalStalker.properties_E8[0xA].val32  = arg0->health_B0;

    ModelAnim_UpdateFieldC_Stalker(&arg0->model_0.anim_4, &sharedData_800DD5A8_0_s00);

    arg0->field_C0 = 0;
    arg0->field_BC = 0;
    arg0->field_B8 = 0;
    arg0->field_B4 = 0;

#ifdef MAP6_S03
    arg0->flags_3E |= (1 << 8);
#endif
}
