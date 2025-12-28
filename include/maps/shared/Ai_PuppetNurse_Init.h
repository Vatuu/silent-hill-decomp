void Ai_PuppetNurse_Init(s_SubCharacter* nurse, bool isPuppetDoctor)
{
    extern s_800D5710 sharedData_800D5710_3_s03[4]; // Likely static.

    s32             charaState;
    s32             charStatIdx;
    s32             charPalette;
    s32             modelVariation;
    s32             stateStepDiv3;
    s_SubCharacter* chara2;

    #define nurseProps nurse->properties_E4.puppetNurse

    chara2 = nurse; // TODO: Not sure why this is needed, possibly an inline here somewhere?

    nurse->moveSpeed_38                = Q12(0.0f);
    nurse->field_E1_0                  = 3;
    nurse->headingAngle_3C             = nurse->rotation_24.vy;
    nurseProps.position_E8 = nurse->position_18;
    nurse->field_D4.field_0                                  = Q12(0.3f);
    nurseProps.damage_F4.position_0.vx = Q12(0.0f);
    nurseProps.damage_F4.position_0.vy = Q12(0.0f);
    nurseProps.damage_F4.position_0.vz = Q12(0.0f);
    nurseProps.field_114 = 0;
    nurseProps.field_118 = 0;

    Chara_DamageClear(nurse);

    nurseProps.flags_122 = PuppetNurseFlag_None;
    nurseProps.field_108 = nurse->position_18.vx;
    nurseProps.field_10C = nurse->position_18.vz;

    charPalette    = (nurse->model_0.stateStep_3 - 1) % 3;
    stateStepDiv3  = (nurse->model_0.stateStep_3 - 1) / 3;
    modelVariation = stateStepDiv3 % 3;
    charaState     = stateStepDiv3 / 3;

    nurseProps.field_11A = 0;
    nurse->flags_3E |= CharaFlag_Unk3;

    if (!isPuppetDoctor)
    {
        charStatIdx                                 = charPalette + 1; // Skip doctor stat at beginning.
        nurseProps.modelVariation_119 = modelVariation + 1;
    }
    else
    {
        nurseProps.modelVariation_119 = 1;
        charPalette                                 = 0;
        charStatIdx                                 = 0;
    }

    chara2->properties_E4.puppetNurse.field_124 = &sharedData_800D5710_3_s03[charStatIdx];

    nurse->health_B0 = chara2->properties_E4.puppetNurse.field_124->health_0;
    nurse->model_0.paletteIdx_1 = charPalette;

    switch (charaState)
    {
        case 0:
            nurse->model_0.controlState_2              = PuppetNurseControl_11;
            nurse->model_0.stateStep_3          = 0;
            nurse->model_0.anim_4.time_4        = Q12(459.0f);
            nurse->model_0.anim_4.keyframeIdx_8 = 459;
            break;

        case 1:
            nurse->model_0.controlState_2              = PuppetNurseControl_10;
            nurse->model_0.stateStep_3          = 0;
            nurse->model_0.anim_4.time_4        = Q12(459.0f);
            nurse->model_0.anim_4.keyframeIdx_8 = 459;
            break;

        case 2:
            nurse->model_0.controlState_2              = PuppetNurseControl_9;
            nurse->model_0.stateStep_3          = 0;
            nurse->model_0.anim_4.time_4        = Q12(459.0f);
            nurse->model_0.anim_4.keyframeIdx_8 = 459;
            break;
    }

    ModelAnim_AnimInfoSet(&nurse->model_0.anim_4, chara2->properties_E4.puppetNurse.field_124->animInfo_24);

    nurse->model_0.anim_4.status_0 = ANIM_STATUS(PuppetNurseAnim_17, false);
    nurse->model_0.anim_4.alpha_A  = Q12(0.0f);
    chara2->properties_E4.puppetNurse.field_120 = Q12(1.0f);

    #undef nurseProps
}
