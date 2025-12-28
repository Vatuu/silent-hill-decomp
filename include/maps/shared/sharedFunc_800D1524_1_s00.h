// Ai_LarvalStalker

void sharedFunc_800D1524_1_s00(s_SubCharacter* larvalStalker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    #define props = larvalStalker->properties_E4.larvalStalker
    #define charaKeyframeProp (larvalStalker->properties_E4.dummy.properties_E8[3].val16[0])

    switch (larvalStalker->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(LarvalStalkerAnim_5, false):
            LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].endKeyframeIdx_E = charaKeyframeProp + 41;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_5, true):
            LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].startKeyframeIdx_C = charaKeyframeProp + 41;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_7, false):
            LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].endKeyframeIdx_E = charaKeyframeProp + 121;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_7, true):
            LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].startKeyframeIdx_C = charaKeyframeProp + 121;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_6, false):
            LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].endKeyframeIdx_E = charaKeyframeProp + 86;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_6, true):
            LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].startKeyframeIdx_C = charaKeyframeProp + 86;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_8, false):
            LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].endKeyframeIdx_E = charaKeyframeProp + 143;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_8, true):
            LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].startKeyframeIdx_C = charaKeyframeProp + 143;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_12, true):
            LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0].duration_8.constant = FP_MULTIPLY_FLOAT_PRECISE(larvalStalker->moveSpeed_38, 32.0f, 12);
            break;
    }

    animInfo = &LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&larvalStalker->model_0, anmHdr, coords, animInfo);

    #undef props
}
