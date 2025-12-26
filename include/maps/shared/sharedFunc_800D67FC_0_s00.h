void sharedFunc_800D67FC_0_s00(s_SubCharacter* stalker)
{
    s32* sp10[7]; // Type assumed.
    s16  newRotY;
    s32  prevMoveSpeed;
    u16  newFlags;

    stalker->field_34       = stalker->field_34 + g_DeltaTime2;
    newRotY               = func_8005BF38(stalker->rotation_24.vy);
    stalker->rotation_24.vy = newRotY;

    if ((u16)stalker->properties_E4.player.afkTimer_E8 & (1 << 13))
    {
        Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
        if (stalker->moveSpeed_38 == Q12(0.0f))
        {
            *(u16*)&stalker->properties_E4.player.afkTimer_E8 &= ~(1 << 13);
        }
    }
    else
    {
        stalker->headingAngle_3C = newRotY;
    }

    prevMoveSpeed = stalker->moveSpeed_38;
    if ((u16)stalker->properties_E4.player.afkTimer_E8 & (1 << 12))
    {
        if (stalker->model_0.state_2 == 2)
        {
            stalker->moveSpeed_38 *= 8;
        }
        else
        {
            stalker->moveSpeed_38 *= 2;
        }
    }

    if (g_DeltaTime0 != Q12(0.0f))
    {
        func_8005CB20(stalker, &sp10, *(s16*)&stalker->properties_E4.player.positionY_EC, *((s16*)&stalker->properties_E4.player.positionY_EC + 1));
    }

    *((u16*)&stalker->properties_E4.player.positionY_EC + 1) = 0;
    *(u16*)&stalker->properties_E4.player.positionY_EC       = 0;
    stalker->moveSpeed_38                                    = prevMoveSpeed;

    if (stalker->field_34 != 0)
    {
        newFlags = stalker->properties_E4.player.afkTimer_E8 | (1 << 8);
    }
    else
    {
        newFlags = stalker->properties_E4.player.afkTimer_E8 & ~(1 << 8);
    }

    *(u16*)&stalker->properties_E4.player.afkTimer_E8 = newFlags;
}
