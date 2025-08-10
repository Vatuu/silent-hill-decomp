static inline void Ai_Bloodsucker_AnimUpdateFromStep(s_SubCharacter* chara)
{
    u32         temp_v0;
    s_Savegame* save;

    switch (chara->model_0.stateStep_3)
    {
        case 17:
            chara->model_0.state_2               = 1;
            chara->model_0.anim_4.animIdx_0      = 15;
            chara->model_0.stateStep_3           = 0;
            chara->model_0.anim_4.time_4         = FP_TO(81, Q12_SHIFT);
            chara->model_0.anim_4.keyframeIdx0_8 = 81;
            return;

#ifdef MAP7_S02 // MAP7_S02 skips rest of function.
    }
#else
        case 18:
            chara->health_B0       = 1;
            chara->model_0.state_2 = 2;
            break;

        case 19:
        case 20:
            chara->model_0.state_2 = 2;
            break;

        default:
            return;
    }

    save = g_SavegamePtr; // TODO: Odd pointer copy, might be some inline flagcheck func?

    temp_v0 = chara->model_0.stateStep_3 - 18;

    chara->model_0.stateStep_3 = temp_v0;

    if (!(save->eventFlags_180[1] & (1 << 26)))
    {
        chara->model_0.anim_4.animIdx_0 = (temp_v0 * 2) + 23;
    }
    else
    {
        chara->model_0.anim_4.animIdx_0 = (temp_v0 * 2) + 17;
    }

    chara->model_0.anim_4.time_4         = FP_TO(sharedData_800D5ABC_3_s03[chara->model_0.anim_4.animIdx_0].keyframeIdx0_C, Q12_SHIFT);
    chara->model_0.anim_4.keyframeIdx0_8 = sharedData_800D5ABC_3_s03[chara->model_0.anim_4.animIdx_0].keyframeIdx0_C;
#endif
}

void Ai_Bloodsucker_Init(s_SubCharacter* chara)
{
    s32 i;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    chara->field_E0_8      = 4;
    chara->headingAngle_3C = chara->rotation_24.vy;

    Ai_Bloodsucker_AnimUpdateFromStep(chara);

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, sharedData_800D5ABC_3_s03);

    chara->damageReceived_C0 = 0;
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;
}
