void Ai_Romper_Init(s_SubCharacter* chara)
{
#define BASE_HEALTH 450
#define RAND_MAX 112.5f

    s32 i;
    s32 temp_a0;
    s32 var_v0;

    chara->properties_E4.larvalStalker.properties_E8[0].val32 = 0;
    chara->model_0.anim_4.keyframeIdx1_A                      = 0;

    if (g_SaveGamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        chara->health_B0 = FP_TO(BASE_HEALTH, Q12_SHIFT) - ((s32)Rng_Rand16() % FP_FLOAT_TO(RAND_MAX, Q12_SHIFT));
    }
    else
    {
        if (g_SaveGamePtr->gameDifficulty_260 == GameDifficulty_Normal)
        {
            chara->health_B0 = FP_TO(BASE_HEALTH, Q12_SHIFT) + ((s32)Rng_Rand16() % FP_FLOAT_TO(RAND_MAX, Q12_SHIFT));
        }
        else
        {
            var_v0 = (s32)Rng_Rand16();

            temp_a0 = var_v0;
            if (temp_a0 < 0)
            {
                var_v0 = temp_a0 + (2048 - 1);
            }

            chara->health_B0 = FP_MULTIPLY((s64)((temp_a0 - ((var_v0 >> 11) << 11)) + FP_FLOAT_TO(1.5f, Q12_SHIFT)), // Shifts are equivalent to `var_v0_2 % 2048`
                                           FP_TO(BASE_HEALTH, Q12_SHIFT), Q12_SHIFT);
        }
    }

    chara->moveSpeed_38    = 0;
    chara->field_E0_8      = 3;
    chara->headingAngle_3C = chara->rotation_24.vy;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    chara->model_0.state_2               = 2;
    chara->model_0.anim_4.animIdx_0      = 31;
    chara->model_0.anim_4.time_4         = FP_TO(147, Q12_SHIFT);
    chara->model_0.anim_4.keyframeIdx0_8 = 147;

    chara->properties_E4.larvalStalker.properties_E8[2].val16[0] = 6;
    chara->properties_E4.larvalStalker.properties_E8[2].val16[1] = chara->rotation_24.vy;

    chara->moveSpeed_38 = 89;

    ModelAnim_UpdateField(&chara->model_0.anim_4, &sharedData_800EC954_2_s02);

    chara->field_C0 = 0;
    chara->field_BC = 0;
    chara->field_B8 = 0;
    chara->field_B4 = 0;

    chara->properties_E4.larvalStalker.properties_E8[5].val32 = chara->properties_E4.larvalStalker.properties_E8[10].val32 = chara->position_18.vx;
    chara->properties_E4.larvalStalker.properties_E8[6].val32 = chara->properties_E4.larvalStalker.properties_E8[8].val32 = chara->position_18.vz;
}
