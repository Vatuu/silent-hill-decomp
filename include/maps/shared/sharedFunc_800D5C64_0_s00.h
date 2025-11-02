void sharedFunc_800D5C64_0_s00(s_SubCharacter* arg0)
{
    u32 animTime;
    s32 animDivTmp;
    s32 animDiv;
    s32 step;
    s32 animMult;
    s32 frame;
    s32 flags;
    s32 var;
    s32 movSpeed0;
    s32 movSpeed1;
    s32 duration;
    
#define CHARA_PROPS arg0->properties_E4.larvalStalker

    arg0->flags_3E &= ~(1<<1);
    if (!(CHARA_PROPS.properties_E8[0].val16[0] & (1<<13)))
    {
        movSpeed0 = arg0->moveSpeed_38;
        if (movSpeed0 > 0)
        {
            arg0->moveSpeed_38 = MAX(0, movSpeed0 - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.5f), 12));
        }
        else
        {
            arg0->moveSpeed_38 = MIN(0, movSpeed0 + FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.5f), 12));
        }
    }
    
    movSpeed0 = arg0->moveSpeed_38;
    if (movSpeed0 > 0)
    {
        movSpeed1 = MAX(0, movSpeed0 - FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.5f), 12));
    }
    else
    {
        movSpeed1 = MIN(0, movSpeed0 +  FP_MULTIPLY_PRECISE(g_DeltaTime0, Q12(1.5f), 12));
    }
    arg0->moveSpeed_38 = movSpeed1;

    animTime = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT);
    animDivTmp = 0;
    animMult = 0;
    if (animTime >= 0x6E && animTime < 0x6E + 7)
    {
        animMult = Q12(0.3f);
        animDivTmp = 7;
    } 
    else if (animTime >= 0x75 && animTime < 0x75 + 4)
    {
        animMult = Q12(0.3f);
        animDivTmp = 4;
    }
    else if (animTime >= 0x79 && animTime < 0x79 + 3)
    {
        animMult = Q12(0.1f);
        animDivTmp = 4;
    }

    if (animMult)
    {
        animDiv = FP_TO(animDivTmp, Q12_SHIFT);
        duration = STALKER_ANIM_INFOS[arg0->model_0.anim_4.status_0].duration_8.constant;
        step = (FP_MULTIPLY_PRECISE(duration, g_DeltaTime0, Q12_SHIFT) * animMult) / animDiv;

        CHARA_PROPS.properties_E8[1].val16[0] = FP_MULTIPLY(step, Math_Sin(arg0->rotation_24.vy), 12);
        CHARA_PROPS.properties_E8[1].val16[1] = FP_MULTIPLY(step, Math_Cos(arg0->rotation_24.vy), 12);
    }

    if (CHARA_PROPS.properties_E8[0].val16[0] & (1<<7))
    {
        frame = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT);
        if ((frame >= 0x79 && frame < 0x79 + 8) ||
            (frame >= 0x95 && frame < 0x95 + 9) ||
            (frame >= 0xAB && frame < 0xAB + 5))
        {
            CHARA_PROPS.properties_E8[0].val16[0] &= ~(1<<7);
        }
    }
    
    if ((arg0->model_0.anim_4.status_0 == ANIM_STATUS(27, true)) && !(Rng_Rand16() & 3))
    {
        if(CHARA_PROPS.properties_E8[0].val16[0] & (1<<1))
        {
            arg0->model_0.state_2 = 2;
        }
        else
        {
            arg0->model_0.state_2 = 3;
        }
        arg0->model_0.anim_4.status_0 = ANIM_STATUS(30, false);
        CHARA_PROPS.properties_E8[5].val16[0] = 55;
        CHARA_PROPS.properties_E8[5].val16[1] = FP_FROM(arg0->model_0.anim_4.time_4, Q12_SHIFT) - 0x1AB;
    }
    // @hack animDiv has to be used for certain stuff for a match, weird.
    animDiv = g_SysWork.field_2388.field_154.field_0.field_0.field_0;
    flags = animDiv & 3;
    if (flags == 0)
    {
        var = func_8006FD90(arg0, 0, Q12(7.5f), Q12(0.0f));
    }
    else if (flags == 2)
    {
        #if defined(MAP1_S00) || defined(MAP1_S01)
            var = func_8006FD90(arg0, 0, Q12(6.0f), Q12(0.0f));
        #else
            var = func_8006FD90(arg0, 0, Q12(8.0f), Q12(0.0f));
        #endif
    }
    else
    {
        var = func_8006FD90(arg0, 1, Q12(0.4f), Q12(0.0f));

    }

    if (var || func_80070360(arg0, Q12(0.0f), Q12(1.0f)))
    {
        arg0->properties_E4.player.field_F0 = g_SysWork.player_4C.chara_0.position_18.vx;
        arg0->properties_E4.player.field_F4 = g_SysWork.player_4C.chara_0.position_18.vz;
    }
}
