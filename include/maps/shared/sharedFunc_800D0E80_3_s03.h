void sharedFunc_800D0E80_3_s03(s_SubCharacter* chara)
{
    if (chara->model_0.anim_4.animIdx_0 == ((chara->model_0.stateStep_3 * 2) + 23))
    {
        chara->model_0.anim_4.animIdx_0 = (chara->model_0.stateStep_3 * 2) + 8;
    }

    if (g_SysWork.player_4C.chara_0.position_18.vx > -FP_FLOAT_TO(140.5f, Q12_SHIFT))
    {
        chara->model_0.state_2 = 2;
    }

    chara->properties_E4.larvalStalker.properties_E8[2].val32 = FP_FLOAT_TO(1.0f, Q12_SHIFT);
}
