void sharedFunc_800D67FC_0_s00(s_SubCharacter* stalker)
{
    s_800C4590* sp10[7];
    q3_12       newHeadingAngle;
    q19_12      prevMoveSpeed;
    u16         newFlags;

    #define stalkerProps stalker->properties_E4.stalker

    stalker->field_34       = stalker->field_34 + g_DeltaTime2;
    newHeadingAngle         = func_8005BF38(stalker->rotation_24.vy);
    stalker->rotation_24.vy = newHeadingAngle;

    if (stalkerProps.flags_E8 & StalkerFlag_13)
    {
        Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
        if (stalker->moveSpeed_38 == Q12(0.0f))
        {
            stalkerProps.flags_E8 &= ~StalkerFlag_13;
        }
    }
    else
    {
        stalker->headingAngle_3C = newHeadingAngle;
    }

    prevMoveSpeed = stalker->moveSpeed_38;
    if (stalkerProps.flags_E8 & StalkerFlag_WarpRotation)
    {
        if (stalker->model_0.controlState_2 == 2)
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
        func_8005CB20(stalker, &sp10, stalkerProps.offset_EC, stalkerProps.offset_EE);
    }

    stalkerProps.offset_EE = Q12(0.0f);
    stalkerProps.offset_EC = Q12(0.0f);
    stalker->moveSpeed_38  = prevMoveSpeed;

    if (stalker->field_34 != Q12(0.0f))
    {
        newFlags = stalkerProps.flags_E8 | StalkerFlag_8;
    }
    else
    {
        newFlags = stalkerProps.flags_E8 & ~StalkerFlag_8;
    }
    stalkerProps.flags_E8 = newFlags;

    #undef stalkerProps
}
