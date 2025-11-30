void sharedFunc_800D9960_1_s02(s_SubCharacter* creaper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    Math_MatrixTransform(&creaper->position_18, &creaper->rotation_24, coords);

    animInfo = &CREAPER_ANIM_INFOS[creaper->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&creaper->model_0, anmHdr, coords, animInfo);
}
