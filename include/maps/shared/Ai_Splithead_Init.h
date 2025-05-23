void Ai_Splithead_Init(s_SubCharacter* chara)
{
    s32 i;

    chara->health_B0 = FP_FLOAT_TO(6.2256f, Q12_SHIFT);
    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;
    chara->model_0.anim_4.keyframeIdx1_A = 0;
    chara->moveSpeed_38 = 0;
    chara->headingAngle_3C = chara->rotation_24.vy;
    chara->field_E0_8 = 4;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }
    
    chara->model_0.state_2 = 8;
    chara->model_0.anim_4.animIdx_0 = 21;
    chara->model_0.anim_4.time_4 = FP_TO(162, Q12_SHIFT);
    chara->model_0.anim_4.keyframeIdx0_8 = 162;
    
    ModelAnim_UpdateField(&chara->model_0.anim_4, &sharedData_800D5888_1_s05);
    
    sharedData_800D8614_1_s05 = 0;
    sharedData_800D8616_1_s05 = 0;
    
    chara->field_C0 = 0;
    chara->field_BC = 0;
    chara->field_B8 = 0;
    chara->field_B4 = 0;
    
    *(u8*)&chara->properties_E4.larvalStalker.properties_E8[0].val8[2] = 196;
    
    chara->flags_3E |= (1 << 8) | (1 << 2);
}
