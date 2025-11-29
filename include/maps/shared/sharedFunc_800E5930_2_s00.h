void sharedFunc_800E5930_2_s00(s_SubCharacter* chara)
{
    q19_12 newMoveSpeed;
    s32    newAnimStatus;
    u32    animStatus;

    // NOTE: This code reads `chara->field_E8` both as word and a half... (half here).
    if (!(chara->properties_E4.splitHead.flags_E8 & CharaUnk0Flag_Unk1))
    {
        Chara_MoveSpeedUpdate(chara, Q12(1.8f));
    }

    if (chara->health_B0 == Q12(0.0f))
    {
        if (g_SysWork.targetNpcIdx_2353 != func_8005C7D0(chara))
        {
            chara->health_B0  = NO_VALUE;
            chara->field_E1_0 = 0;
        }
    }

    // NOTE: Reads `chara->field_E8` both as word and a half.
    if (!(chara->properties_E4.player.afkTimer_E8 & 0x44) && chara->moveSpeed_38 == Q12(0.0f))
    {
        animStatus    = ANIM_STATUS_IDX_GET(chara->model_0.anim_4.status_0);
        newAnimStatus = ANIM_STATUS(0, false);
        if (animStatus == ANIM_STATUS(9, false))
        {
            newAnimStatus = ANIM_STATUS(2, true);
        }
        if (animStatus == ANIM_STATUS(9, true))
        {
            newAnimStatus = ANIM_STATUS(3, false);
        }
        if (animStatus == ANIM_STATUS(10, false))
        {
            newAnimStatus = ANIM_STATUS(3, true);
        }

        if (newAnimStatus != ANIM_STATUS(0, false))
        {
            func_800622B8(3, chara, newAnimStatus, 6);
            chara->properties_E4.splitHead.flags_E8 |= CharaUnk0Flag_Unk6;
        }
    }
}
