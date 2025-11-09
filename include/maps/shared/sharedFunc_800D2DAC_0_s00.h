s32 sharedFunc_800D2DAC_0_s00(void)
{
    s_Model*    model;
    s_AnimInfo* animInfo;   

    // NOTE: There are 37 base anims for Harry. 38 and beyond are map-specific.
    model    = &g_SysWork.player_4C.chara_0.model_0;
    animInfo = &g_MapOverlayHeader.animInfos_34[model->anim_4.status_0 - ANIM_STATUS(38, false)];

    if (animInfo->updateFunc_0 == Anim_Update0)
    {
        // Check if anim has started or finished.
        if (Anim_DurationGet(model, animInfo) > Q12(0.0f))
        {
            return model->anim_4.keyframeIdx_8 == animInfo->endKeyframeIdx_E;
        }
        else
        {
            return model->anim_4.keyframeIdx_8 == animInfo->startKeyframeIdx_C;
        }
    }

    if (animInfo->updateFunc_0 == Anim_Update2)
    {
        return -2;
    }
    else
    {
        return -1;
    }
}
