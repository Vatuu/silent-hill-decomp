void sharedFunc_800D63D0_0_s00(s_SubCharacter* chara, s32 moveSpeed)
{
    u16* flags;
    s32  curMoveSpeed;
    s32  newMoveSpeed;
    s32  newAnimStatus;

    flags = &chara->properties_E4.player.afkTimer_E8;

    curMoveSpeed = moveSpeed;
    if (!(*flags & (1 << 13)))
    {
        curMoveSpeed = chara->moveSpeed_38;
        if (curMoveSpeed > 0)
        {
            newMoveSpeed = curMoveSpeed - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.5f, Q12_SHIFT);
            if (newMoveSpeed < 0)
            {
                newMoveSpeed = 0;
            }
        }
        else
        {
            newMoveSpeed = curMoveSpeed + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.5f, Q12_SHIFT);
            if (newMoveSpeed > 0)
            {
                newMoveSpeed = 0;
            }
        }
        chara->moveSpeed_38 = newMoveSpeed;
    }

    if (chara->health_B0 == FP_HEALTH(0.0f))
    {
        chara->flags_3E &= ~CharaFlag_Unk2;

        if (g_SysWork.enemyTargetIdx_2353 != func_8005C7D0(chara))
        {
            chara->health_B0  = NO_VALUE;
            chara->field_E0_8 = 0;
        }
    }

    if (chara->moveSpeed_38 == 0 && !(chara->properties_E4.player.afkTimer_E8 & ((1 << 8) | (1 << 9))))
    {
        newAnimStatus = (chara->model_0.anim_4.status_0 == ANIM_STATUS(31, true)) ? ANIM_STATUS(0, true) : ANIM_STATUS(0, false);

        if (chara->model_0.anim_4.status_0 == ANIM_STATUS(32, true))
        {
            newAnimStatus = ANIM_STATUS(1, false);
        }

        if (chara->model_0.anim_4.status_0 == ANIM_STATUS(33, true))
        {
            newAnimStatus = ANIM_STATUS(6, false);
        }

        if (newAnimStatus != ANIM_STATUS(0, false))
        {
            func_800622B8(3, chara, newAnimStatus, 3);

            flags   = &chara->properties_E4.player.afkTimer_E8;
            *flags |= 1 << 9;
        }
    }
}
