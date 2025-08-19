void sharedFunc_800D63D0_0_s00(s_SubCharacter* chara, s32 arg1)
#ifdef SHARED_FUNC_IMPL
{
    u16* flags;
    s32  moveSpeed;
    s32  newMoveSpeed;
    s32  animVar;

    flags = &chara->properties_E4.player.properties_E4[1];

    moveSpeed = arg1;
    if (!(*flags & (1 << 13)))
    {
        moveSpeed = chara->moveSpeed_38;
        if (moveSpeed > 0)
        {
            newMoveSpeed = moveSpeed - FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 1.5f, Q12_SHIFT);
            if (newMoveSpeed < 0)
            {
                newMoveSpeed = 0;
            }
        }
        else
        {
            newMoveSpeed = moveSpeed + FP_MULTIPLY_FLOAT((s64)g_DeltaTime0, 1.5f, Q12_SHIFT);
            if (newMoveSpeed > 0)
            {
                newMoveSpeed = 0;
            }
        }
        chara->moveSpeed_38 = newMoveSpeed;
    }

    if (chara->health_B0 == 0)
    {
        chara->flags_3E &= ~CharaFlag_Unk2;

        if (g_SysWork.field_2353 != func_8005C7D0(chara, moveSpeed))
        {
            chara->health_B0 = NO_VALUE;
            chara->field_E0_8 = 0;
        }
    }

    if (chara->moveSpeed_38 == 0 && !(chara->properties_E4.player.properties_E4[1] & ((1 << 8) | (1 << 9))))
    {
        animVar = chara->model_0.anim_4.animIdx_0 == 63;
        if (chara->model_0.anim_4.animIdx_0 == 65)
        {
            animVar = 2;
        }
        if (chara->model_0.anim_4.animIdx_0 == 67)
        {
            animVar = 12;
        }
        if (animVar != 0)
        {
            func_800622B8(3, chara, animVar, 3);

            flags = &chara->properties_E4.player.properties_E4[1];
            *flags |= 1 << 9;
        }
    }
}
#else
;
#endif
