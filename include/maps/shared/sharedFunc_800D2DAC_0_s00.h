s32 sharedFunc_800D2DAC_0_s00()
{
    s_Model*    model;
    s_AnimInfo* animInfo;   

    model    = &g_SysWork.player_4C.chara_0.model_0;
    animInfo = &g_MapOverlayHeader.animInfo_34[model->anim_4.animIdx_0 - ANIM_STATUS_GET(38, false)];

    if (animInfo->funcPtr_0 == Anim_Update0)
    {
        if (func_800449AC(model, animInfo) > 0)
        {
            return model->anim_4.keyframeIdx0_8 == animInfo->keyframeIdx1_E;
        }
        else
        {
            return model->anim_4.keyframeIdx0_8 == animInfo->keyframeIdx0_C;
        }
    }

    if (animInfo->funcPtr_0 == Anim_Update2)
    {
        return -2;
    }
    else
    {
        return -1;
    }
}
