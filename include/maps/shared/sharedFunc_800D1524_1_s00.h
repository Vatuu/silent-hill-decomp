void sharedFunc_800D1524_1_s00(s_SubCharacter* larvalStalker, s_AnmHeader* anmHdr, GsCOORDINATE2* coords)
{
    s_AnimInfo* animInfo;

    #define larvalStalkerProps larvalStalker->properties_E4.larvalStalker
    #define activeAnimInfo     LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0]

    switch (larvalStalker->model_0.anim_4.status_0)
    {
        case ANIM_STATUS(LarvalStalkerAnim_5, false):
            activeAnimInfo.endKeyframeIdx_E = larvalStalkerProps.keyframeIdx_F4 + 41;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_5, true):
            activeAnimInfo.startKeyframeIdx_C = larvalStalkerProps.keyframeIdx_F4 + 41;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_7, false):
            activeAnimInfo.endKeyframeIdx_E = larvalStalkerProps.keyframeIdx_F4 + 121;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_7, true):
            activeAnimInfo.startKeyframeIdx_C = larvalStalkerProps.keyframeIdx_F4 + 121;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_6, false):
            activeAnimInfo.endKeyframeIdx_E = larvalStalkerProps.keyframeIdx_F4 + 86;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_6, true):
            activeAnimInfo.startKeyframeIdx_C = larvalStalkerProps.keyframeIdx_F4 + 86;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_8, false):
            activeAnimInfo.endKeyframeIdx_E = larvalStalkerProps.keyframeIdx_F4 + 143;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_8, true):
            activeAnimInfo.startKeyframeIdx_C = larvalStalkerProps.keyframeIdx_F4 + 143;
            break;

        case ANIM_STATUS(LarvalStalkerAnim_12, true):
            activeAnimInfo.duration_8.constant = FP_MULTIPLY_FLOAT_PRECISE(larvalStalker->moveSpeed_38, 32.0f, Q12_SHIFT);
            break;
    }

    animInfo = &LARVAL_STALKER_ANIM_INFOS[larvalStalker->model_0.anim_4.status_0];
    animInfo->updateFunc_0(&larvalStalker->model_0, anmHdr, coords, animInfo);

    #undef larvalStalkerProps
    #undef activeAnimInfo
}
