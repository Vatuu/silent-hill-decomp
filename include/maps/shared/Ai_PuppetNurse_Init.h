void Ai_PuppetNurse_Init(s_SubCharacter* chara, s32 isPuppetDoctor)
{
    extern s_800D5710 sharedData_800D5710_3_s03[4]; // Likely static.

    s32             charaState;
    s32             charStatIdx;
    s32             charPalette;
    s32             modelVariation;
    s32             stateStepDiv3;
    s_SubCharacter* chara2;

    chara2 = chara; // TODO: Not sure why this is needed, possibly an inline here somewhere?

    chara->moveSpeed_38                = 0;
    chara->field_E0_8                  = 3;
    chara->headingAngle_3C             = chara->rotation_24.vy;
    chara->properties_E4.npc.field_E8  = chara->position_18;
    chara->field_D4                    = FP_FLOAT_TO(0.3f, Q12_SHIFT);
    chara->properties_E4.npc.field_F4  = 0;
    chara->properties_E4.npc.field_F8  = 0;
    chara->properties_E4.npc.field_FC  = 0;
    chara->properties_E4.npc.field_114 = 0;
    chara->properties_E4.npc.field_118 = 0;
    chara->damageReceived_C0           = FP_HEALTH(0.0f);
    chara->field_BC                    = 0;
    chara->field_B8                    = 0;
    chara->field_B4                    = 0;
    chara->properties_E4.npc.field_122 = 0;
    chara->properties_E4.npc.field_108 = chara->position_18.vx;
    chara->properties_E4.npc.field_10C = chara->position_18.vz;

    charPalette    = (chara->model_0.stateStep_3 - 1) % 3;
    stateStepDiv3  = (chara->model_0.stateStep_3 - 1) / 3;
    modelVariation = stateStepDiv3 % 3;
    charaState     = stateStepDiv3 / 3;

    chara->properties_E4.npc.field_11A = 0;

    chara->flags_3E |= CharaFlag_Unk3;

    if (!isPuppetDoctor)
    {
        charStatIdx                                 = charPalette + 1; // skip doctor stat at beginning
        chara->properties_E4.npc.modelVariation_119 = modelVariation + 1;
    }
    else
    {
        chara->properties_E4.npc.modelVariation_119 = 1;
        charPalette                                 = 0;
        charStatIdx                                 = 0;
    }

    chara2->properties_E4.npc.field_124 = &sharedData_800D5710_3_s03[charStatIdx];

    chara->health_B0 = chara2->properties_E4.npc.field_124->health_0;

    chara->model_0.paletteIdx_1 = charPalette;

    switch (charaState)
    {
        case 0:
            chara->model_0.state_2              = 11;
            chara->model_0.stateStep_3          = 0;
            chara->model_0.anim_4.time_4        = FP_TIME(459.0f);
            chara->model_0.anim_4.keyframeIdx_8 = 459;
            break;
        case 1:
            chara->model_0.state_2              = 10;
            chara->model_0.stateStep_3          = 0;
            chara->model_0.anim_4.time_4        = FP_TIME(459.0f);
            chara->model_0.anim_4.keyframeIdx_8 = 459;
            break;
        case 2:
            chara->model_0.state_2              = 9;
            chara->model_0.stateStep_3          = 0;
            chara->model_0.anim_4.time_4        = FP_TIME(459.0f);
            chara->model_0.anim_4.keyframeIdx_8 = 459;
            break;
    }

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, chara2->properties_E4.npc.field_124->animInfo_24);

    chara->model_0.anim_4.status_0 = ANIM_STATUS(17, false);
    chara->model_0.anim_4.alpha_A  = FP_ALPHA(0.0f);

    chara2->properties_E4.npc.field_120 = 4096;
}
