void sharedFunc_800D5C64_0_s00(s_SubCharacter* stalker)
{
#if defined(MAP1_S00) || defined(MAP1_S01)
    #define BASE_DIST_MAX Q12(6.0f)
#else
    #define BASE_DIST_MAX Q12(8.0f)
#endif

    u32    activeKeyframeIdx;
    s32    animDivTmp;
    s32    animDiv;
    s32    step;
    q19_12 animMult;
    s32    frameIdx;
    s32    flags;
    s32    cond;
    q19_12 duration;

    #define stalkerProps stalker->properties_E4.stalker

    stalker->flags_3E &= ~CharaFlag_Unk2;
    if (!(stalkerProps.flags_E8 & StalkerFlag_13))
    {
        Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
    }

    Chara_MoveSpeedUpdate(stalker, Q12(1.5f));

    activeKeyframeIdx = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);
    animDivTmp = 0;
    animMult = Q12(0.0f);

    if (activeKeyframeIdx >= 110 && activeKeyframeIdx < 117)
    {
        animMult = Q12(0.3f);
        animDivTmp = 7;
    } 
    else if (activeKeyframeIdx >= 117 && activeKeyframeIdx < 121)
    {
        animMult = Q12(0.3f);
        animDivTmp = 4;
    }
    else if (activeKeyframeIdx >= 121 && activeKeyframeIdx < 124)
    {
        animMult = Q12(0.1f);
        animDivTmp = 4;
    }

    if (animMult != Q12(0.0f))
    {
        animDiv  = FP_TO(animDivTmp, Q12_SHIFT);
        duration = STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant;
        step     = (FP_MULTIPLY_PRECISE(duration, g_DeltaTime0, Q12_SHIFT) * animMult) / animDiv;

        stalkerProps.offset_EC = FP_MULTIPLY(step, Math_Sin(stalker->rotation_24.vy), Q12_SHIFT);
        stalkerProps.offset_EE = FP_MULTIPLY(step, Math_Cos(stalker->rotation_24.vy), Q12_SHIFT);
    }

    if (stalkerProps.flags_E8 & StalkerFlag_7)
    {
        frameIdx = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);
        if ((frameIdx >= 121 && frameIdx < 129) ||
            (frameIdx >= 149 && frameIdx < 158) ||
            (frameIdx >= 171 && frameIdx < 176))
        {
            stalkerProps.flags_E8 &= ~StalkerFlag_7;
        }
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(StalkerAnim_27, true) && !Rng_GenerateInt(0, 3)) // 1 in 4 chance.
    {
        if (stalkerProps.flags_E8 & StalkerFlag_1)
        {
            stalker->model_0.controlState_2 = 2;
        }
        else
        {
            stalker->model_0.controlState_2 = 3;
        }

        stalker->model_0.anim_4.status_0 = ANIM_STATUS(StalkerAnim_30, false);
        stalkerProps.keyframeIdx_FC      = ANIM_STATUS(StalkerAnim_27, true);
        stalkerProps.relKeyframeIdx_FE   = ANIM_TIME_REL_KEYFRAME_IDX_GET(stalker->model_0.anim_4.time_4, 427);
    }

    // @hack `animDiv` has to be used for certain stuff for a match, weird.
    animDiv = g_SysWork.field_2388.field_154.field_0.field_0.field_0;
    flags = animDiv & 0x3;
    if (flags == 0)
    {
        cond = func_8006FD90(stalker, 0, Q12(7.5f), Q12(0.0f));
    }
    else if (flags == (1 << 1))
    {
        cond = func_8006FD90(stalker, 0, BASE_DIST_MAX, Q12(0.0f));
    }
    else
    {
        cond = func_8006FD90(stalker, 1, Q12(0.4f), Q12(0.0f));
    }

    if (cond || func_80070360(stalker, Q12(0.0f), Q12(1.0f)))
    {
        stalkerProps.targetPositionX_F0 = g_SysWork.playerWork_4C.player_0.position_18.vx;
        stalkerProps.targetPositionZ_F4 = g_SysWork.playerWork_4C.player_0.position_18.vz;
    }

    #undef stalkerProps
}
