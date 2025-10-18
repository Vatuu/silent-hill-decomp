void sharedFunc_800D63D0_0_s00(s_SubCharacter* chara)
{
    u16* flags;
    s32  curMoveSpeed;
    s32  newMoveSpeed;
    s32  newAnimStatus;

    flags = &chara->properties_E4.player.afkTimer_E8;
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

    if (chara->health_B0 == Q12(0.0f))
    {
        chara->flags_3E &= ~CharaFlag_Unk2;

        if (g_SysWork.targetNpcIdx_2353 != func_8005C7D0(chara))
        {
            chara->health_B0  = NO_VALUE;
            chara->field_E1_0 = 0;
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
#if !defined(MAP5_S02) && !defined(MAP7_S02)
            func_800622B8(3, chara, newAnimStatus, 3);
#endif
            flags   = &chara->properties_E4.player.afkTimer_E8;
            *flags |= 1 << 9;
        }
    }

#if defined(MAP5_S02) || defined(MAP7_S02)
    if (chara->properties_E4.larvalStalker.properties_E8[0].val16[0] & (1 << 9))
    {
        chara->timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
        if (chara->timer_C6 > Q12(1.0f))
        {
            chara->model_0.charaId_0 = Chara_None;
        }
    }
#endif
}
