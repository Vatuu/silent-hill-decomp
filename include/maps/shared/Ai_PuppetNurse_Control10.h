void Ai_PuppetNurse_Control10(s_SubCharacter* nurse)
{
    u8     animStatus;
    q19_12 deltaX;
    q19_12 deltaZ;
    q19_12 dist;

    if (!nurse->model_0.stateStep_3)
    {
        nurse->properties_E4.player.field_104 = 0;
        nurse->model_0.anim_4.status_0 = ANIM_STATUS(19, false);
        nurse->model_0.stateStep_3++;
    }

    deltaX = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vx - nurse->position_18.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.playerWork_4C.player_0.position_18.vz - nurse->position_18.vz);
    dist   = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));

    if (sharedFunc_800CF294_3_s03(nurse, dist))
    {
        nurse->model_0.controlState_2 = PuppetNurseControl_9;
        nurse->model_0.stateStep_3 = 0;

        if (Rng_Rand16() & 0x80)
        {
            animStatus = ANIM_STATUS(7, false);
        }
        else
        {
           animStatus = ANIM_STATUS(8, false);
        }

        nurse->model_0.anim_4.status_0 = animStatus;
    }
}
