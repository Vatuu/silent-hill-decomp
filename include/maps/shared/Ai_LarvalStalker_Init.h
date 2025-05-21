void Ai_LarvalStalker_Init(s_SubCharacter* arg0)
{
    s32 i;

    arg0->model_0.state_2               = 3;
    arg0->model_0.anim_4.time_4         = 0;
    arg0->model_0.anim_4.animIdx_0      = 20;
    arg0->model_0.anim_4.time_4         = FP_TO(162, Q12_SHIFT);
    arg0->model_0.anim_4.keyframeIdx0_8 = 162;

    arg0->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;

    arg0->model_0.anim_4.keyframeIdx1_A = 0;
    arg0->model_0.stateStep_3           = 0;

    ModelAnim_UpdateField(&arg0->model_0.anim_4, &sharedData_800DA6C8_0_s00);

    arg0->health_B0       = FP_TO(300, Q12_SHIFT);
    arg0->field_34        = 0;
    arg0->moveSpeed_38    = 0;
    arg0->field_C0        = 0;
    arg0->field_BC        = 0;
    arg0->field_B8        = 0;
    arg0->field_B4        = 0;
    arg0->field_E0_8      = 0;
    arg0->headingAngle_3C = arg0->rotation_24.vy;

    for (i = 0; i < 16; i++)
    {
        arg0->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    arg0->properties_E4.larvalStalker.properties_E8[4].val32 = g_SysWork.player_4C.chara_0.position_18.vx;
    arg0->properties_E4.larvalStalker.properties_E8[5].val32 = g_SysWork.player_4C.chara_0.position_18.vz;
}