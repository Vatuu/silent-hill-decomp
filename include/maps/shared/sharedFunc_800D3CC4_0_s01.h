void sharedFunc_800D3CC4_0_s01(s_SubCharacter* chara)
{
    u32  keyframeIdx;
    bool cond;

    sharedData_800E21D0_0_s01.flags_0 |= 1 << 31;
    cond                               = false;

    switch (chara->model_0.stateStep_3)
    {
        case 0:
            cond                           = true;
            chara->model_0.anim_4.status_0 = ANIM_STATUS(23, true);
            chara->model_0.stateStep_3     = 1;

        case 1:
            chara->properties_E4.player.flags_11C |= 1 << 16;
            break;

        case 2:
            cond                           = true;
            chara->model_0.anim_4.status_0 = ANIM_STATUS(24, true);
            chara->model_0.stateStep_3     = 3;

        case 3:
            chara->properties_E4.player.flags_11C |= 1 << 16;
            break;

        case 4:
            cond                           = true;
            chara->model_0.anim_4.status_0 = ANIM_STATUS(15, true);
            chara->model_0.stateStep_3     = 5;

        case 5:
            chara->properties_E4.player.flags_11C &= ~(1 << 16);
            break;

        case 6:
            if (chara->model_0.anim_4.status_0 == ANIM_STATUS(19, true))
            {
                chara->model_0.stateStep_3 = 7;
            }
            break;

        case 7:
            chara->model_0.state_2     = 0;
            chara->model_0.stateStep_3 = 13;
            sharedSymbol_800D3B0C_0_s01(chara);
            break;
    }

    Chara_TakeDamage(chara, Q12(0.0f));

    if (cond)
    {
        keyframeIdx                         = func_80044918(&chara->model_0.anim_4)->startKeyframeIdx_C;
        chara->model_0.anim_4.keyframeIdx_8 = keyframeIdx;
        chara->model_0.anim_4.time_4        = Q12(keyframeIdx);
    }
}
