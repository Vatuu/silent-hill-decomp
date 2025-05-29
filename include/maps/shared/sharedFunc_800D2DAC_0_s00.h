s32 sharedFunc_800D2DAC_0_s00()
{
    s_Model*    playerModel = &g_SysWork.player_4C.chara_0.model_0;
    s_AnimInfo* animInfo    = &g_MapOverlayHeader.animInfo_34[playerModel->anim_4.animIdx_0 - 76];

    if (animInfo->funcPtr_0 == Anim_Update0)
    {
        if (func_800449AC(playerModel, animInfo) > 0)
        {
            return playerModel->anim_4.keyframeIdx0_8 == animInfo->keyframeIdx1_E;
        }
        else
        {
            return playerModel->anim_4.keyframeIdx0_8 == animInfo->keyframeIdx0_C;
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
