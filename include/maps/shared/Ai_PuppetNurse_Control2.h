void Ai_PuppetNurse_Control2(s_SubCharacter* nurse)
{
    s32 moveSpeed;

    if (!nurse->model_0.stateStep_3)
    {
        Ai_PuppetNurse_SfxPlay(nurse, 2);
        nurse->model_0.anim_4.status_0 = ANIM_STATUS(2, false);
        nurse->model_0.stateStep_3++;
    }
    if (nurse->model_0.anim_4.status_0 == ANIM_STATUS(18, false))
    {
        nurse->model_0.state_2 = ANIM_STATUS(4, true);
        nurse->model_0.stateStep_3 = 0;
    }

    if (nurse->moveSpeed_38 > Q12(0.0f))
    {
        moveSpeed = nurse->moveSpeed_38 - FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 4.0f, Q12_SHIFT);
        if (moveSpeed < Q12(0.0f))
        {
            moveSpeed = Q12(0.0f);
        }
    }
    else
    {
        moveSpeed = nurse->moveSpeed_38 + FP_MULTIPLY_FLOAT_PRECISE(g_DeltaTime0, 4.0f, Q12_SHIFT);
        if (moveSpeed > Q12(0.0f))
        {
            moveSpeed = Q12(0.0f);
        }
    }
    nurse->moveSpeed_38 = moveSpeed;
}

