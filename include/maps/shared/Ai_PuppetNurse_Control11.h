void Ai_PuppetNurse_Control11(s_SubCharacter* nurse)
{
    u8              controlState;
    q19_12          deltaX;
    q19_12          deltaZ;
    q19_12          dist;
    q3_12           angle;
    q19_12          tmp;
    s32             temp_s0;
    s_SubCharacter* localNurse;

    #define nurseProps nurse->properties_E4.puppetNurse

    if (!nurse->model_0.stateStep_3)
    {
        nurseProps.field_104 = 0;
        nurse->model_0.anim_4.status_0 = ANIM_STATUS(PuppetNurseAnim_17, false);
        nurseProps.field_11C = func_8006F99C(nurse, Q12(1.0f), nurse->rotation_24.vy);
        nurse->model_0.stateStep_3++;
    }

    if (sharedFunc_800CE398_3_s03(nurse->model_0.anim_4.status_0))
    {
        if (Rng_GenerateUInt(0, 15) == 0) // 1 in 16 chance.
        {
            if (Rng_Rand16() & 0x80)
            {
                controlState = PuppetNurseControl_6;
            }
            else
            {
                controlState = PuppetNurseControl_7;
            }

            nurse->model_0.controlState_2 = controlState;
            nurse->model_0.stateStep_3 = 0;
        }
        else
        {
            nurse->model_0.anim_4.status_0 = g_PuppetNurse_AnimStatus4[(Rng_Rand16() >> 2) & 3];
        }
    }

    deltaX = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - nurse->position_18.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - nurse->position_18.vz);
    dist   = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    if (sharedFunc_800CF294_3_s03(nurse, dist))
    {
        nurse->model_0.controlState_2 = PuppetNurseControl_9;
        nurse->model_0.stateStep_3 = 0;
        return;
    }

    localNurse = nurse;
    #define localNurseProps localNurse->properties_E4.puppetNurse

    Chara_MoveSpeedUpdate3(nurse, Q12(1.4f), Q12(0.27f));

    if (Rng_GenerateUInt(0, 63) == 0) // 1 in 64 chance.
    {
        tmp = Q12(1.5f);
        temp_s0 = localNurseProps.field_108 + ((Rng_Rand16() % Q12(3.0f)) - tmp);
        localNurseProps.field_11C = Chara_HeadingAngleGet(nurse,
                                                           Q12(1.0f),
                                                           temp_s0,
                                                           localNurseProps.field_10C + ((Rng_Rand16() % Q12(3.0f)) - tmp),
                                                           Q12_ANGLE(360.0f),
                                                           true);
    }

    angle = func_8005BF38(localNurseProps.field_11C - nurse->rotation_24.vy);
    if (ABS(angle) > Q12_ANGLE(5.0f))
    {
        if (angle > Q12_ANGLE(0.0f))
        {
            nurse->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
        else
        {
            nurse->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
    }

    #undef nurseProps
    #undef localNurseProps
}
