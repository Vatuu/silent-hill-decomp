void sharedFunc_800D67FC_0_s00(s_SubCharacter* chara)
{
    s32* sp10[7]; // Type assumed.
    s16  newRotY;
    s32  moveSpeed;
    s32  origMoveSpeed;
    s32  newMoveSpeed;
    s32  newMoveSpeed_2;
    u16  newFlags;

    chara->field_34       = chara->field_34 + g_DeltaTime2;
    newRotY               = func_8005BF38(chara->rotation_24.vy);
    chara->rotation_24.vy = newRotY;

    if ((u16)chara->properties_E4.player.properties_E4[1] & (1 << 13))
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

        if (newMoveSpeed == 0)
        {
            *(u16*)&chara->properties_E4.player.properties_E4[1] &= ~(1 << 13);
        }
    }
    else
    {
        chara->headingAngle_3C = newRotY;
    }

    origMoveSpeed = chara->moveSpeed_38;
    if ((u16)chara->properties_E4.player.properties_E4[1] & (1 << 12))
    {
        if (chara->model_0.state_2 == 2)
        {
            chara->moveSpeed_38 *= 8;
        }
        else
        {
            chara->moveSpeed_38 *= 2;
        }
    }

    if (g_DeltaTime0 != 0)
    {
        func_8005CB20(chara, &sp10, *(s16*)&chara->properties_E4.player.properties_E4[2], *((s16*)&chara->properties_E4.player.properties_E4[2] + 1));
    }

    *((u16*)&chara->properties_E4.player.properties_E4[2] + 1) = 0;
    *(u16*)&chara->properties_E4.player.properties_E4[2]       = 0;
    chara->moveSpeed_38                   = origMoveSpeed;

    if (chara->field_34 != 0)
    {
        newFlags = chara->properties_E4.player.properties_E4[1] | (1 << 8);
    }
    else
    {
        newFlags = chara->properties_E4.player.properties_E4[1] & ~(1 << 8);
    }

    *(u16*)&chara->properties_E4.player.properties_E4[1] = newFlags;
}
