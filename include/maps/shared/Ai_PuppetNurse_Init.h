static inline void ModelAnim_UpdateFieldC(s_ModelAnim* anim, s32 fieldCValue)
{
    anim->field_10 = 0;
    anim->field_C = fieldCValue;
}

void Ai_PuppetNurse_Init(s_SubCharacter* chara, s32 isPuppetDoctor)
{
    extern s_800D5710 sharedData_800D5710_3_s03[4];

    s32 charaStage;
    s32 charStatIdx;
    s32 charPalette;
    s32 modelVariation;
    s32 stageStepDiv3;
    s_SubCharacter *chara2;

    chara2 = chara; // TODO: not sure why this is needed, possibly an inline here somewhere?
    
    chara->moveSpeed_38 = 0;
    chara->field_E0_8 = 3;
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->properties_E4.npc.field_E8 = chara->position_18;
    chara->field_D4 = FP_FLOAT_TO(0.3f, Q12_SHIFT);
    chara->properties_E4.npc.field_F4 = 0;
    chara->properties_E4.npc.field_F8 = 0;
    chara->properties_E4.npc.field_FC = 0;
    chara->properties_E4.npc.field_114 = 0;
    chara->properties_E4.npc.field_118 = 0;
    chara->field_C0 = 0;
    chara->field_BC = 0;
    chara->field_B8 = 0;
    chara->field_B4 = 0;
    chara->properties_E4.npc.field_122 = 0;
    chara->properties_E4.npc.field_108 = chara->position_18.vx;
    chara->properties_E4.npc.field_10C = chara->position_18.vz;

    stageStepDiv3  = (chara->model_0.stageStep_3 - 1) / 3;
    charPalette    = (chara->model_0.stageStep_3 - 1) % 3;
    modelVariation = stageStepDiv3 % 3;
    charaStage     = stageStepDiv3 / 3;
    
    chara->properties_E4.npc.field_11A = 0;
    chara->field_3E |= 4; // rename to flags_3E
    
    if (!isPuppetDoctor)
    {
        charStatIdx = charPalette + 1; // skip doctor stat at beginning
        chara->properties_E4.npc.modelVariation_119 = modelVariation + 1;
    }
    else
    {
        chara->properties_E4.npc.modelVariation_119 = 1;
        charPalette = 0;
        charStatIdx = 0;
    }
    
    chara2->properties_E4.npc.field_124 = &sharedData_800D5710_3_s03[charStatIdx];

    chara->health_B0 = chara2->properties_E4.npc.field_124->health_0;

    chara->model_0.paletteIdx_1 = charPalette;
    
    switch(charaStage)
    {
    case 0:
        chara->model_0.stage_2       = 11;
        chara->model_0.stageStep_3   = 0;
        chara->model_0.anim_4.time_4 = FP_TO(459, Q12_SHIFT);
        chara->model_0.anim_4.keyframeIdx0_8 = 459;
        break;
    case 1:
        chara->model_0.stage_2       = 10;
        chara->model_0.stageStep_3   = 0;
        chara->model_0.anim_4.time_4 = FP_TO(459, Q12_SHIFT);
        chara->model_0.anim_4.keyframeIdx0_8 = 459;
        break;
    case 2:
        chara->model_0.stage_2       = 9;
        chara->model_0.stageStep_3   = 0;
        chara->model_0.anim_4.time_4 = FP_TO(459, Q12_SHIFT);
        chara->model_0.anim_4.keyframeIdx0_8 = 459;
        break;
    }

    ModelAnim_UpdateFieldC(&chara->model_0.anim_4, chara2->properties_E4.npc.field_124->field_24);
    
    chara->model_0.anim_4.animIdx_0 = 34;
    chara->model_0.anim_4.keyframeIdx1_A = 0;
    
    chara2->properties_E4.npc.field_120 = 4096;
}
