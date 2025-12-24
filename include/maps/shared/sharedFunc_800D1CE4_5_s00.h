extern q19_12 D_800DE28C;

void sharedFunc_800D1CE4_5_s00(s_SubCharacter* chara)
{
    if (chara->properties_E4.splitHead.flags_E8 & 1)
    {
        chara->field_34 += g_DeltaTime2 >> 1;
        if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 176, 184))
        {
            D_800DE28C = Q12(10.0f);
        }
        else
        {
            D_800DE28C = Q12(0.0f);
        }
    }
    else
    {
        Chara_MoveSpeedUpdate(chara, Q12(4.0f));
        if (ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0) == 10)
        {
            if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 176, 185))
            {
                chara->model_0.anim_4.time_4        = Q12(186.0f);
                chara->model_0.anim_4.keyframeIdx_8 = 186;
            }
            D_800DE28C = Q12(8.0f);
        }
    }
    if (ANIM_TIME_RANGE_CHECK(chara->model_0.anim_4.time_4, 191, 193))
    {
        Character_AnimSet(chara, ANIM_STATUS(12, true), 202);
        chara->rotation_24.vz = 0;
        return;
    }
    if (chara->model_0.anim_4.status_0 == ANIM_STATUS(12, true))
    {
        chara->flags_3E |= CharaFlag_Unk2;
        if (chara->health_B0 <= 0)
        {
            chara->model_0.state_2         = 13;
            chara->model_0.anim_4.status_0 = ANIM_STATUS(6, false);
        }
    }
}
