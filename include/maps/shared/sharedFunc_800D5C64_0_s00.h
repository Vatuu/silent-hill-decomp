void sharedFunc_800D5C64_0_s00(s_SubCharacter* stalker)
{
    q20_12 animFrameIdx;
    s32    animDivTmp;
    s32    animDiv;
    s32    step;
    q19_12 animMult;
    s32    frameIdx;
    s32    flags;
    s32    var;
    q19_12 duration;

    #define dummyProps stalker->properties_E4.dummy

    stalker->flags_3E &= ~CharaFlag_Unk2;
    if (!(dummyProps.properties_E8[0].val16[0] & (1 << 13)))
    {
        Chara_MoveSpeedUpdate(stalker, Q12(1.5f));
    }

    Chara_MoveSpeedUpdate(stalker, Q12(1.5f));

    animFrameIdx = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);
    animDivTmp = 0;
    animMult = Q12(0.0f);

    if (animFrameIdx >= 110 && animFrameIdx < 117)
    {
        animMult = Q12(0.3f);
        animDivTmp = 7;
    } 
    else if (animFrameIdx >= 117 && animFrameIdx < 121)
    {
        animMult = Q12(0.3f);
        animDivTmp = 4;
    }
    else if (animFrameIdx >= 121 && animFrameIdx < 124)
    {
        animMult = Q12(0.1f);
        animDivTmp = 4;
    }

    if (animMult != Q12(0.0f))
    {
        animDiv  = FP_TO(animDivTmp, Q12_SHIFT);
        duration = STALKER_ANIM_INFOS[stalker->model_0.anim_4.status_0].duration_8.constant;
        step     = (FP_MULTIPLY_PRECISE(duration, g_DeltaTime0, Q12_SHIFT) * animMult) / animDiv;

        dummyProps.properties_E8[1].val16[0] = FP_MULTIPLY(step, Math_Sin(stalker->rotation_24.vy), Q12_SHIFT);
        dummyProps.properties_E8[1].val16[1] = FP_MULTIPLY(step, Math_Cos(stalker->rotation_24.vy), Q12_SHIFT);
    }

    if (dummyProps.properties_E8[0].val16[0] & (1 << 7))
    {
        frameIdx = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT);
        if ((frameIdx >= 121 && frameIdx < 129) ||
            (frameIdx >= 149 && frameIdx < 158) ||
            (frameIdx >= 171 && frameIdx < 176))
        {
            dummyProps.properties_E8[0].val16[0] &= ~(1 << 7);
        }
    }

    if (stalker->model_0.anim_4.status_0 == ANIM_STATUS(27, true) && Rng_GenerateInt(0, 3) == 0) // 1 in 4 chance.
    {
        if (dummyProps.properties_E8[0].val16[0] & (1 << 1))
        {
            stalker->model_0.state_2 = 2;
        }
        else
        {
            stalker->model_0.state_2 = 3;
        }

        stalker->model_0.anim_4.status_0 = ANIM_STATUS(30, false);
        dummyProps.properties_E8[5].val16[0] = 55;
        dummyProps.properties_E8[5].val16[1] = FP_FROM(stalker->model_0.anim_4.time_4, Q12_SHIFT) - 427;
    }

    // @hack `animDiv` has to be used for certain stuff for a match, weird.
    animDiv = g_SysWork.field_2388.field_154.field_0.field_0.field_0;
    flags = animDiv & 0x3;
    if (flags == 0)
    {
        var = func_8006FD90(stalker, 0, Q12(7.5f), Q12(0.0f));
    }
    else if (flags == 2)
    {
        #if defined(MAP1_S00) || defined(MAP1_S01)
            var = func_8006FD90(stalker, 0, Q12(6.0f), Q12(0.0f));
        #else
            var = func_8006FD90(stalker, 0, Q12(8.0f), Q12(0.0f));
        #endif
    }
    else
    {
        var = func_8006FD90(stalker, 1, Q12(0.4f), Q12(0.0f));

    }

    if (var || func_80070360(stalker, Q12(0.0f), Q12(1.0f)))
    {
        stalker->properties_E4.player.field_F0 = g_SysWork.playerWork_4C.player_0.position_18.vx;
        stalker->properties_E4.player.field_F4 = g_SysWork.playerWork_4C.player_0.position_18.vz;
    }
}
