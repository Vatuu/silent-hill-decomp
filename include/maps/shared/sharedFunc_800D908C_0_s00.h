bool sharedFunc_800D908C_0_s00(s32 arg0, s_SubCharacter* chara, s32 arg2, s32 arg3, s32 sfx, s32 pitch)
{
    if (chara->model_0.anim_4.animIdx_0 != arg0)
    {
        return false;
    }

    if (chara->model_0.anim_4.keyframeIdx0_8 >= arg3)
    {
        if ((chara->properties_E4.larvalStalker.properties_E8[13].val32 & (1 << 4)) == 0)
        {
            func_8005DD44(sfx, &chara->position_18, FP_VOLUME(0.5f), pitch);
            chara->properties_E4.larvalStalker.properties_E8[13].val32 |= 1 << 4;
            return true;
        }
    }
    else
    {
        chara->properties_E4.larvalStalker.properties_E8[13].val32 &= ~(1 << 4);
    }

    if (chara->model_0.anim_4.keyframeIdx0_8 >= arg2)
    {
        if ((chara->properties_E4.larvalStalker.properties_E8[13].val32 & (1 << 5)) == 0)
        {
            func_8005DD44(sfx, &chara->position_18, FP_VOLUME(0.5f), pitch);
            chara->properties_E4.larvalStalker.properties_E8[13].val32 |= 1 << 5;
            return true;
        }
    }
    else
    {
        chara->properties_E4.larvalStalker.properties_E8[13].val32 &= ~(1 << 5);
    }

    return false;
}
