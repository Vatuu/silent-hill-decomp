void sharedFunc_800D9960_1_s02(s_SubCharacter* creeper, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    Math_MatrixTransform(&creeper->position_18, &creeper->rotation_24, coords);

    animInfo = &CREEPER_ANIM_INFOS[creeper->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&creeper->model_0, anmHdr, coords, animInfo);
}
