// Ai_LarvalStalker

void sharedFunc_800D1524_1_s00(s_SubCharacter* chara, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

#define CHARA_KEYFRAME_PROPERTY (chara->properties_E4.larvalStalker.properties_E8[3].val16[0])

    switch (chara->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(5, false):
            LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = CHARA_KEYFRAME_PROPERTY + 41;
            break;
        case ANIM_STATUS(5, true):
            LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = CHARA_KEYFRAME_PROPERTY + 41;
            break;
        case ANIM_STATUS(7, false):
            LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = CHARA_KEYFRAME_PROPERTY + 121;
            break;
        case ANIM_STATUS(7, true):
            LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = CHARA_KEYFRAME_PROPERTY + 121;
            break;
        case ANIM_STATUS(6, false):
            LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = CHARA_KEYFRAME_PROPERTY + 86;
            break;
        case ANIM_STATUS(6, true):
            LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = CHARA_KEYFRAME_PROPERTY + 86;
            break;
        case ANIM_STATUS(8, false):
            LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].endKeyframeIdx_E = CHARA_KEYFRAME_PROPERTY + 143;
            break;
        case ANIM_STATUS(8, true):
            LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].startKeyframeIdx_C = CHARA_KEYFRAME_PROPERTY + 143;
            break;
        case ANIM_STATUS(12, true):
            LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0].duration_8.constant = FP_MULTIPLY_FLOAT_PRECISE(chara->moveSpeed_38, 32.0f, 12);
            break;
    }

    animInfo = &LARVAL_STALKER_ANIM_INFOS[chara->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&chara->model_0, anmHdr, coords, animInfo);
}
