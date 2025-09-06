void Ai_LarvalStalker_Init(s_SubCharacter* chara)
{
    s32 i;

    chara->model_0.state_2       = 3;
    chara->model_0.anim_4.time_4 = 0;
    Character_AnimSet(chara, ANIM_STATUS(10, true), 162);

    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;

    chara->model_0.anim_4.alpha_A = FP_ALPHA(0.0f);
    chara->model_0.stateStep_3    = 0;

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, LARVAL_STALKER_ANIM_INFOS);

    chara->health_B0         = FP_HEALTH(300.0f);
    chara->field_34          = 0;
    chara->moveSpeed_38      = 0;
    chara->damageReceived_C0 = FP_HEALTH(0.0f);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;
    chara->field_E0_8        = 0;
    chara->headingAngle_3C   = chara->rotation_24.vy;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    chara->properties_E4.larvalStalker.properties_E8[4].val32 = g_SysWork.player_4C.chara_0.position_18.vx;
    chara->properties_E4.larvalStalker.properties_E8[5].val32 = g_SysWork.player_4C.chara_0.position_18.vz;
}