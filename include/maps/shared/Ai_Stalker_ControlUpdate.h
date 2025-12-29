void Ai_Stalker_ControlUpdate(s_SubCharacter* stalker)
{
    q3_12 angle;
    s32   temp_s1;
    s32   temp_v0;
    s32   temp_v0_2;
    s32   i;
    s32   angle1;
    s32   unkAnimStatus;
    s32   animStatus;

    #define stalkerProps stalker->properties_E4.stalker

    if (stalkerProps.flags_E8 & StalkerFlag_10)
    {
        stalker->flags_3E |= CharaFlag_Unk3;
    }

    if (stalker->model_0.anim_4.status_0 != ANIM_STATUS(StalkerAnim_34, true))
    {
        animStatus = stalker->model_0.anim_4.status_0;

        if (animStatus > ANIM_STATUS(StalkerAnim_34, true))
        {
            unkAnimStatus = ANIM_STATUS(StalkerAnim_35, true);
            unkAnimStatus++; // } TODO: Hack.
            unkAnimStatus--; // }
        }
        else
        {
            unkAnimStatus = ANIM_STATUS(StalkerAnim_7, true);
        }

        if (animStatus != unkAnimStatus)
        {
            stalker->field_44.field_0 = 0;
        }
    }

    if (!(g_SysWork.sysFlags_22A0 & SysFlag_4))
    {
        g_SysWork.sysFlags_22A0 |= SysFlag_4;

        for (i = 4; i > 0; i--)
        {
            sharedData_800E39EC_0_s00[i] = sharedData_800E39EC_0_s00[i - 1];
            sharedData_800E3A0C_0_s00[i] = sharedData_800E3A0C_0_s00[i - 1];
        }

        // TODO: Use `Math_Vector2MagCalc`.
        temp_v0                      = ((g_SysWork.playerWork_4C.player_0.position_18.vx - sharedData_800E39E4_0_s00) >> 6);
        temp_v0_2                    = (g_SysWork.playerWork_4C.player_0.position_18.vz - sharedData_800E39E8_0_s00) >> 6;
        sharedData_800E39EC_0_s00[0] = (FP_TO(SquareRoot0(SQUARE(temp_v0) + SQUARE(temp_v0_2)), Q12_SHIFT) << 6) / g_DeltaTime0;
        sharedData_800E3A0C_0_s00[0] = ratan2(g_SysWork.playerWork_4C.player_0.position_18.vx - sharedData_800E39E4_0_s00, g_SysWork.playerWork_4C.player_0.position_18.vz - sharedData_800E39E8_0_s00);
        sharedData_800E39E4_0_s00    = g_SysWork.playerWork_4C.player_0.position_18.vx;
        sharedData_800E39E8_0_s00    = g_SysWork.playerWork_4C.player_0.position_18.vz;

        if (sharedData_800DD5A6_0_s00 != 5)
        {
            sharedData_800DD5A6_0_s00++;
            sharedData_800E3A18_0_s00 = g_SysWork.playerWork_4C.player_0.position_18.vx;
            sharedData_800E3A1C_0_s00 = g_SysWork.playerWork_4C.player_0.position_18.vz;
        }
        else
        {
            angle1 = FP_ANGLE(0.0f);
            for (i = 0; i < 4; i++)
            {
                angle1 += func_8005BF38(sharedData_800E3A0C_0_s00[i] - sharedData_800E3A0C_0_s00[i + 1]);
            }

            angle = sharedData_800E3A0C_0_s00[0] + (angle1 >> 2);

            angle1 = 0;
            for (i = 0; i < 4; i++)
            {
                angle1 += sharedData_800E39EC_0_s00[i] - sharedData_800E39EC_0_s00[i + 1];
            }

            temp_s1                   = sharedData_800E39EC_0_s00[0] + (angle1 >> 2);
            sharedData_800E3A18_0_s00 = ((temp_s1 * Math_Sin(angle)) >> 14) + g_SysWork.playerWork_4C.player_0.position_18.vx;
            sharedData_800E3A1C_0_s00 = ((temp_s1 * Math_Cos(angle)) >> 14) + g_SysWork.playerWork_4C.player_0.position_18.vz;
        }
    }

    // Handle control state.
    switch (stalker->model_0.controlState_2)
    {
        case StalkerControl_None:
            break;

        case StalkerControl_2:
            Ai_Stalker_Control_2(stalker);
            break;

        case StalkerControl_3:
            Ai_Stalker_Control_3(stalker);
            break;

        case StalkerControl_8:
            Ai_Stalker_Control_8(stalker);
            break;

        case StalkerControl_4:
            Ai_Stalker_Control_4(stalker);
            break;

        case StalkerControl_5:
            Ai_Stalker_Control_5(stalker);
            break;

        case StalkerControl_6:
            Ai_Stalker_Control_6(stalker);
            break;

        case StalkerControl_7:
            Ai_Stalker_Control_7(stalker);
            break;

        case StalkerControl_9:
            Ai_Stalker_Control_9(stalker);
            break;

        case StalkerControl_10:
            Ai_Stalker_Control_10(stalker);
            break;

        case StalkerControl_11:
            Ai_Stalker_Control_11(stalker);
            break;

        case StalkerControl_12:
            Ai_Stalker_Control_12(stalker);
            break;

        case StalkerControl_13:
            Ai_Stalker_Control_13(stalker);
            break;
    }

    #undef stalkerProps
}
