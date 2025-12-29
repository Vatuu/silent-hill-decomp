void Ai_Stalker_Control_12(s_SubCharacter* stalker)
{
#if defined(MAP1_S00) || defined(MAP1_S01)
    #define BASE_DIST_MAX Q12(12.0f)
#else
    #define BASE_DIST_MAX Q12(16.0f)
#endif

    q19_12 distToPlayer;
    q3_12  angleDeltaToPlayer;
    s32    cond; // Not `bool`?

    #define stalkerProps stalker->properties_E4.stalker

    distToPlayer       = Math_Vector2MagCalc(g_SysWork.playerWork_4C.player_0.position_18.vx - stalker->position_18.vx,
                                             g_SysWork.playerWork_4C.player_0.position_18.vz - stalker->position_18.vz);
    angleDeltaToPlayer = func_8005BF38(Math_AngleBetweenPositionsGet(stalker->position_18, g_SysWork.playerWork_4C.player_0.position_18) -
                                       stalker->rotation_24.vy);

    if (!(g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))))
    {
        cond = func_8006FD90(stalker, 0, Q12(7.5f), Q12(7.5f));
    }
    else if ((g_SysWork.field_2388.field_154.field_0.field_0.field_0 & ((1 << 0) | (1 << 1))) == (1 << 1))
    {
        cond = func_8006FD90(stalker, 0, BASE_DIST_MAX, Q12(0.0f));
    }
    else
    {
        cond = func_8006FD90(stalker, 1, Q12(0.4f), Q12(0.8f));
    }

    cond |= func_80070360(stalker, distToPlayer, Q12(1.0f));
    if (!cond)
    {
        return;
    }

    stalkerProps.targetPositionX_F0 = g_SysWork.playerWork_4C.player_0.position_18.vx;
    stalkerProps.targetPositionZ_F4 = g_SysWork.playerWork_4C.player_0.position_18.vz;

    if (distToPlayer < Q12(1.2f) && angleDeltaToPlayer < FP_ANGLE(180.0f))
    {
        if (!(stalkerProps.flags_E8 & StalkerFlag_1))
        {
            stalker->model_0.controlState_2 = StalkerControl_3;
        }
        else
        {
            stalker->model_0.controlState_2 = StalkerControl_2;
        }

        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_30, false);

        stalkerProps.keyframeIdx_FC    = 55;
        stalkerProps.relKeyframeIdx_FE = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 427);
        stalkerProps.flags_E8         |= StalkerFlag_10;

        sharedFunc_800D7E04_0_s00(stalker, Sfx_Unk1363);
    }

    #undef BASE_DIST_MAX
    #undef stalkerProps
}
