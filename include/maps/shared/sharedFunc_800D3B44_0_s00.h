void sharedFunc_800D3B44_0_s00(s_SubCharacter* stalker)
{
    s16 temp_a2;
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 i;
    s32 var_s2;
    s32 unkAnimStatus;
    s32 animStatus;

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

        // TODO: Not sure what this shifting is doing.
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
            var_s2 = 0;
            for (i = 0; i < 4; i++)
            {
                var_s2 += func_8005BF38(sharedData_800E3A0C_0_s00[i] - sharedData_800E3A0C_0_s00[i + 1]);
            }
            temp_a2 = sharedData_800E3A0C_0_s00[0] + (var_s2 >> 2);

            var_s2 = 0;
            for (i = 0; i < 4; i++)
            {
                var_s2 += sharedData_800E39EC_0_s00[i] - sharedData_800E39EC_0_s00[i + 1];
            }

            temp_s1                   = sharedData_800E39EC_0_s00[0] + (var_s2 >> 2);
            sharedData_800E3A18_0_s00 = ((temp_s1 * Math_Sin(temp_a2)) >> 14) + g_SysWork.playerWork_4C.player_0.position_18.vx;
            sharedData_800E3A1C_0_s00 = ((temp_s1 * Math_Cos(temp_a2)) >> 14) + g_SysWork.playerWork_4C.player_0.position_18.vz;
        }
    }

    switch (stalker->model_0.controlState_2)
    {
        case 0:
            break;

        case 2:
            sharedFunc_800D3EF4_0_s00(stalker);
            break;

        case 3:
            sharedFunc_800D4924_0_s00(stalker);
            break;

        case 8:
            sharedFunc_800D5C64_0_s00(stalker);
            break;

        case 4:
            sharedFunc_800D492C_0_s00(stalker);
            break;

        case 5:
            sharedFunc_800D5098_0_s00(stalker);
            break;

        case 6:
            sharedFunc_800D54A8_0_s00(stalker);
            break;

        case 7:
            sharedFunc_800D5B48_0_s00(stalker);
            break;

        case 9:
            sharedFunc_800D5FCC_0_s00(stalker);
            break;

        case 10:
            sharedFunc_800D63D0_0_s00(stalker);
            break;

        case 11:
            sharedFunc_800D654C_0_s00(stalker);
            break;

        case 12:
            sharedFunc_800D6554_0_s00(stalker);
            break;

        case 13:
            sharedFunc_800D670C_0_s00(stalker);
            break;
    }

    #undef stalkerProps
}
