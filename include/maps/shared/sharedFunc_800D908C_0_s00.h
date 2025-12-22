bool sharedFunc_800D908C_0_s00(s32 animStatus, s_SubCharacter* chara, s32 keyframeIdx0, s32 keyframeIdx1, s32 sfxId, s32 pitch)
{
    if (chara->model_0.anim_4.status_0 != animStatus)
    {
        return false;
    }

    if (chara->model_0.anim_4.keyframeIdx_8 >= keyframeIdx1)
    {
        if (!(chara->properties_E4.dummy.properties_E8[13].val32 & (1 << 4)))
        {
            func_8005DD44(sfxId, &chara->position_18, Q8_CLAMPED(0.5f), pitch);
            chara->properties_E4.dummy.properties_E8[13].val32 |= 1 << 4;
            return true;
        }
    }
    else
    {
        chara->properties_E4.dummy.properties_E8[13].val32 &= ~(1 << 4);
    }

    if (chara->model_0.anim_4.keyframeIdx_8 >= keyframeIdx0)
    {
        if (!(chara->properties_E4.dummy.properties_E8[13].val32 & (1 << 5)))
        {
            func_8005DD44(sfxId, &chara->position_18, Q8_CLAMPED(0.5f), pitch);
            chara->properties_E4.dummy.properties_E8[13].val32 |= 1 << 5;
            return true;
        }
    }
    else
    {
        chara->properties_E4.dummy.properties_E8[13].val32 &= ~(1 << 5);
    }

    return false;
}
