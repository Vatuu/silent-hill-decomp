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

    chara->model_0.state_2 = 8;
    Character_AnimSet(chara, ANIM_STATUS(SplitheadAnim_Unk10, true), 162);
    ModelAnim_AnimInfoSet(&chara->model_0.anim_4, SPLITHEAD_ANIM_INFOS);

    sharedData_800D8614_1_s05 = 0;
    sharedData_800D8616_1_s05 = 0;

    chara->dmg_B4.damageReceived_C = Q12(0.0f);
    chara->dmg_B4.field_8          = 0;
    chara->dmg_B4.field_4          = 0;
    chara->dmg_B4.field_0          = 0;

    *(u8*)&chara->properties_E4.larvalStalker.properties_E8[0].val8[2] = 196;

    chara->flags_3E |= CharaFlag_Unk9 | CharaFlag_Unk3;
}
