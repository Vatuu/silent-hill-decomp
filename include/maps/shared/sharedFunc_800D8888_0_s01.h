void sharedFunc_800D8888_0_s01(s_SubCharacter* arg0, s_AnmHeader* arg1, GsCOORDINATE2* arg2)
{
    s_AnimInfo* temp_a3;

    if (arg0->properties_E4.player.field_F0 == 0)
    {
    #if defined(MAP6_S01) || defined(MAP7_S03)
        temp_a3 = &CYBIL_ANIM_INFOS[arg0->model_0.anim_4.status_0];
    #else
        temp_a3 = &KAUFMANN_ANIM_INFOS[arg0->model_0.anim_4.status_0];
    #endif
        temp_a3->updateFunc_0(&arg0->model_0, arg1, arg2, temp_a3);
    }
}
