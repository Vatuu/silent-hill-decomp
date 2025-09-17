void Ai_Romper_Init(s_SubCharacter* chara)
{
    #define ROMPER_HEALTH_BASE      Q12(450.0f)
    #define ROMPER_HEALTH_BONUS_MAX Q12(112.5f)

    s32 i;
    s32 temp_a0;
    s32 var_v0;

    chara->properties_E4.larvalStalker.properties_E8[0].val32 = 0;
    chara->model_0.anim_4.alpha_A                             = Q12(0.0f);

    if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Easy)
    {
        chara->health_B0 = ROMPER_HEALTH_BASE - ((s32)Rng_Rand16() % ROMPER_HEALTH_BONUS_MAX);
    }
    else
    {
        if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Normal)
        {
            chara->health_B0 = ROMPER_HEALTH_BASE + ((s32)Rng_Rand16() % ROMPER_HEALTH_BONUS_MAX);
        }
        else
        {
            var_v0 = (s32)Rng_Rand16();

            temp_a0 = var_v0;
            if (temp_a0 < 0)
            {
                var_v0 = temp_a0 + (2048 - 1);
            }

            // Shifts are equivalent to `var_v0_2 % 2048`.
            chara->health_B0 = FP_MULTIPLY_PRECISE(((temp_a0 - ((var_v0 >> 11) << 11)) + FP_FLOAT_TO(1.5f, Q12_SHIFT)),
                                                   ROMPER_HEALTH_BASE,
                                                   Q12_SHIFT);
        }
    }

    chara->moveSpeed_38    = 0;
    chara->field_E1_0      = 3;
    chara->headingAngle_3C = chara->rotation_24.vy;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    chara->model_0.state_2               = 2;
    chara->model_0.anim_4.status_0      = ANIM_STATUS(15, true);
    chara->model_0.anim_4.time_4         = FP_TIME(147.0f);
    chara->model_0.anim_4.keyframeIdx_8 = 147;

    chara->properties_E4.larvalStalker.properties_E8[2].val16[0] = 6;
    chara->properties_E4.larvalStalker.properties_E8[2].val16[1] = chara->rotation_24.vy;

    chara->moveSpeed_38 = 89;

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, ROPMER_ANIM_INFOS);

    chara->damageReceived_C0 = Q12(0.0f);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

    chara->properties_E4.larvalStalker.properties_E8[5].val32 = chara->properties_E4.larvalStalker.properties_E8[10].val32 = chara->position_18.vx;
    chara->properties_E4.larvalStalker.properties_E8[6].val32 = chara->properties_E4.larvalStalker.properties_E8[8].val32 = chara->position_18.vz;
}
