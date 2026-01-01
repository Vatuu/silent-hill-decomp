bool sharedFunc_800DC50C_2_s00(s_SubCharacter* airScreamer)
{
    return (airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(19, true) || airScreamer->model_0.anim_4.status_0 == ANIM_STATUS(27, true)) &&
           sharedFunc_800DC3BC_2_s00(airScreamer) &&
           ((airScreamer->field_34 >= 0 && sharedFunc_800DC0A8_2_s00(airScreamer)) || sharedFunc_800DBF88_2_s00(airScreamer, Q12(1.0f)));
}
