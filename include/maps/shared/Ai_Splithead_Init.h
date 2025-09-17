void Ai_Splithead_Init(s_SubCharacter* chara)
{
    s32 i;

    chara->health_B0                                             = Q12(6.2256f);
    chara->properties_E4.larvalStalker.properties_E8[0].val16[0] = 0;
    chara->model_0.anim_4.alpha_A                                = Q12(0.0f);
    chara->moveSpeed_38                                          = 0;
    chara->headingAngle_3C                                       = chara->rotation_24.vy;
    chara->field_E1_0                                            = 4;

    for (i = 0; i < 16; i++)
    {
        chara->properties_E4.larvalStalker.properties_E8[i].val32 = 0;
    }

    chara->model_0.state_2               = 8;
    chara->model_0.anim_4.status_0      = ANIM_STATUS(10, true);
    chara->model_0.anim_4.time_4         = FP_TIME(162.0f);
    chara->model_0.anim_4.keyframeIdx_8 = 162;

    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, SPLITHEAD_ANIM_INFOS);

    sharedData_800D8614_1_s05 = 0;
    sharedData_800D8616_1_s05 = 0;

    chara->damageReceived_C0 = Q12(0.0f);
    chara->field_BC          = 0;
    chara->field_B8          = 0;
    chara->field_B4          = 0;

    *(u8*)&chara->properties_E4.larvalStalker.properties_E8[0].val8[2] = 196;

    chara->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;
}
