void sharedFunc_800D63D0_0_s00(s_SubCharacter* stalker)
{
    q19_12 curMoveSpeed;
    q19_12 newMoveSpeed;
    s32    newAnimStatus;

    #define stalkerProps stalker->properties_E4.stalker

    if (!(stalkerProps.flags_E8 & (1 << 13)))
    {
        // TODO: Use macro.
        curMoveSpeed = stalker->moveSpeed_38;
        if (curMoveSpeed > Q12(0.0f))
        {
            newMoveSpeed = curMoveSpeed - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.5f, Q12_SHIFT);
            if (newMoveSpeed < Q12(0.0f))
            {
                newMoveSpeed = Q12(0.0f);
            }
        }
        else
        {
            newMoveSpeed = curMoveSpeed + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 1.5f, Q12_SHIFT);
            if (newMoveSpeed > Q12(0.0f))
            {
                newMoveSpeed = Q12(0.0f);
            }
        }
        stalker->moveSpeed_38 = newMoveSpeed;
    }

    if (stalker->health_B0 == Q12(0.0f))
    {
        stalker->flags_3E &= ~CharaFlag_Unk2;

        if (g_SysWork.targetNpcIdx_2353 != func_8005C7D0(stalker))
        {
            stalker->health_B0  = NO_VALUE;
            stalker->field_E1_0 = 0;
        }
    }

    // TODO: `stalkerProps.flags_E8` doesn't match?
    if (stalker->moveSpeed_38 == Q12(0.0f) && !(stalker->properties_E4.player.afkTimer_E8 & (StalkerFlag_8 |StalkerFlag_9)))
    {
        newAnimStatus = (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_31, true)) ? ANIM_STATUS(StalkerAnim_Still, true) :
                                                                                                  ANIM_STATUS(StalkerAnim_Still, false);

        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_32, true))
        {
            newAnimStatus = ANIM_STATUS(StalkerAnim_1, false);
        }

        if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_33, true))
        {
            newAnimStatus = ANIM_STATUS(StalkerAnim_6, false);
        }

        if (newAnimStatus != ANIM_STATUS(StalkerAnim_Still, false))
        {
#if !defined(MAP5_S02) && !defined(MAP7_S02)
            func_800622B8(3, stalker, newAnimStatus, 3);
#endif
            stalkerProps.flags_E8 |= StalkerFlag_9;
        }
    }

#if defined(MAP5_S02) || defined(MAP7_S02)
    if (stalkerProps.flags_E8 & (1 << 9))
    {
        stalker->timer_C6 += FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 0.25f, Q12_SHIFT);
        if (stalker->timer_C6 > Q12(1.0f))
        {
            stalker->model_0.charaId_0 = Chara_None;
        }
    }
#endif

    #undef stalkerProps
}
