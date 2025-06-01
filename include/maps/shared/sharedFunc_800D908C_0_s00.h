s32 sharedFunc_800D908C_0_s00(s32 arg0, s_SubCharacter* chara, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    if (chara->model_0.anim_4.animIdx_0 != arg0)
    {
        return 0;
    }

    if (chara->model_0.anim_4.keyframeIdx0_8 >= arg3)
    {
        if ((chara->properties_E4.larvalStalker.properties_E8[13].val32 & (1 << 4)) == 0)
        {
            func_8005DD44(arg4, &chara->position_18, 0x80, arg5);
            chara->properties_E4.larvalStalker.properties_E8[13].val32 |= 1 << 4;
            return 1;
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
            func_8005DD44(arg4, &chara->position_18, 0x80, arg5);
            chara->properties_E4.larvalStalker.properties_E8[13].val32 |= 1 << 5;
            return 1;
        }
    }
    else
    {
        chara->properties_E4.larvalStalker.properties_E8[13].val32 &= ~(1 << 5);
    }

    return 0;
}
