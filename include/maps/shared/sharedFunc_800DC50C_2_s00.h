bool sharedFunc_800DC50C_2_s00(s_SubCharacter* chara)
{
    return (chara->model_0.anim_4.status_0 == ANIM_STATUS(19, true) || chara->model_0.anim_4.status_0 == ANIM_STATUS(27, true)) &&
           sharedFunc_800DC3BC_2_s00(chara) &&
           ((chara->field_34 >= 0 && sharedFunc_800DC0A8_2_s00(chara)) || sharedFunc_800DBF88_2_s00(chara, Q12(1.0f)));
}
