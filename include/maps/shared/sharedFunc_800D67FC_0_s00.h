void sharedFunc_800D67FC_0_s00(s_SubCharacter* chara)
{
    s32* sp10[7]; // Type assumed.
    s16  newRotY;
    s32  prevMoveSpeed;
    u16  newFlags;

    chara->field_34       = chara->field_34 + g_DeltaTime2;
    newRotY               = func_8005BF38(chara->rotation_24.vy);
    chara->rotation_24.vy = newRotY;

    if ((u16)chara->properties_E4.player.afkTimer_E8 & (1 << 13))
    {
        Chara_MoveSpeedUpdate(chara, Q12(1.5f));
        if (chara->moveSpeed_38 == Q12(0.0f))
        {
            *(u16*)&chara->properties_E4.player.afkTimer_E8 &= ~(1 << 13);
        }
    }
    else
    {
        chara->headingAngle_3C = newRotY;
    }

    prevMoveSpeed = chara->moveSpeed_38;
    if ((u16)chara->properties_E4.player.afkTimer_E8 & (1 << 12))
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

    if (g_DeltaTime0 != Q12(0.0f))
    {
        func_8005CB20(chara, &sp10, *(s16*)&chara->properties_E4.player.positionY_EC, *((s16*)&chara->properties_E4.player.positionY_EC + 1));
    }

    *((u16*)&chara->properties_E4.player.positionY_EC + 1) = 0;
    *(u16*)&chara->properties_E4.player.positionY_EC       = 0;
    chara->moveSpeed_38                                    = prevMoveSpeed;

    if (chara->field_34 != 0)
    {
        newFlags = chara->properties_E4.player.afkTimer_E8 | (1 << 8);
    }
    else
    {
        newFlags = chara->properties_E4.player.afkTimer_E8 & ~(1 << 8);
    }

    *(u16*)&chara->properties_E4.player.afkTimer_E8 = newFlags;
}
