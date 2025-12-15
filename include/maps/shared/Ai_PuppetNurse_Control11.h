void Ai_PuppetNurse_Control11(s_SubCharacter* nurse)
{
    u8              animStatus;
    q19_12          deltaX;
    q19_12          deltaZ;
    q19_12          dist;
    q3_12           angle;
    q19_12          tmp;
    s32             temp_s0;
    s_SubCharacter* localNurse;

    if (!nurse->model_0.stateStep_3)
    {
        nurse->properties_E4.player.field_104 = 0;
        nurse->model_0.anim_4.status_0 = ANIM_STATUS(17, false);
        nurse->properties_E4.puppetNurse.field_11C = func_8006F99C(nurse, Q12(1.0f), nurse->rotation_24.vy);
        nurse->model_0.stateStep_3++;
    }

    if (sharedFunc_800CE398_3_s03(nurse->model_0.anim_4.status_0))
    {
        if (!(Rng_Rand16() & 0xF))
        {
            if (Rng_Rand16() & 0x80)
            {
                animStatus = ANIM_STATUS(3, false);
            }
            else
            {
                animStatus = ANIM_STATUS(3, true);
            }

            nurse->model_0.state_2 = animStatus;
            nurse->model_0.stateStep_3 = 0;
        } 
        else
        {
            nurse->model_0.anim_4.status_0 = g_PuppetNurse_AnimStatus4[(Rng_Rand16() >> 2) & 3];
        }
    }

    deltaX = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vx - nurse->position_18.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vz - nurse->position_18.vz);
    dist   = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    if (sharedFunc_800CF294_3_s03(nurse, dist))
    {
        nurse->model_0.state_2 = 9;
        nurse->model_0.stateStep_3 = 0;
        return;
    }

    localNurse = nurse;
    Chara_MoveSpeedUpdate3(nurse, Q12(1.4f), Q12(0.27f));

    if (!(Rng_Rand16() & 0x3F))
    {
        tmp = Q12(1.5f);
        temp_s0 = localNurse->properties_E4.puppetNurse.field_108 + ((Rng_Rand16() % Q12(3.0f)) - tmp);
        localNurse->properties_E4.puppetNurse.field_11C = func_8006FAFC(nurse,
                                                                        Q12(1.0f),
                                                                        temp_s0,
                                                                        localNurse->properties_E4.puppetNurse.field_10C + ((Rng_Rand16() % Q12(3.0f)) - tmp),
                                                                        FP_ANGLE(360.0f),
                                                                        true);
    }

    angle = func_8005BF38(localNurse->properties_E4.puppetNurse.field_11C - nurse->rotation_24.vy);
    if (ABS(angle) > FP_ANGLE(5.0f))
    {
        if (angle > FP_ANGLE(0.0f))
        {
            nurse->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
        }
        else
        {
            nurse->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
        }
    }
}
