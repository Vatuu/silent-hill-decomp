void Ai_LarvalStalker_Init(s_SubCharacter* arg0)
{
    s32 i;

    arg0->model_0.state_2               = 3;
    arg0->model_0.anim_4.time_4         = 0;
    arg0->model_0.anim_4.status_0      = ANIM_STATUS(10, false);
    arg0->model_0.anim_4.time_4         = Q12(162.0f);
    arg0->model_0.anim_4.keyframeIdx_8 = 162;

    arg0->properties_E4.dummy.properties_E8[0].val16[0] = 0;

    arg0->model_0.anim_4.alpha_A = Q12(0.0f);
    arg0->model_0.stateStep_3    = 0;

    ModelAnim_AnimInfoSet(&arg0->model_0.anim_4, LARVAL_STALKER_ANIM_INFOS);

    arg0->health_B0         = Q12(300.0f);
    arg0->field_34          = 0;
    arg0->moveSpeed_38      = 0;
    Chara_DamageClear(arg0);
    arg0->field_E1_0        = 0;
    arg0->headingAngle_3C   = arg0->rotation_24.vy;

    for (i = 0; i < 16; i++)
    {
        arg0->properties_E4.dummy.properties_E8[i].val32 = 0;
    }

    arg0->properties_E4.dummy.properties_E8[4].val32 = g_SysWork.playerWork_4C.player_0.position_18.vx;
    arg0->properties_E4.dummy.properties_E8[5].val32 = g_SysWork.playerWork_4C.player_0.position_18.vz;
}
