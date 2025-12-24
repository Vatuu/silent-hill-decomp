void sharedFunc_800D1C0C_5_s00(s_SubCharacter* chara)
{
    Chara_MoveSpeedUpdate(chara, Q12(4.0f));

    if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 15 && chara->moveSpeed_38 == 0 && Rng_GenerateInt(0, 7) == 0)
    {
        chara->model_0.state_2         = 7;
        chara->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
    }
}