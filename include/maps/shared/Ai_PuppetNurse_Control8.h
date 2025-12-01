void Ai_PuppetNurse_Control8(s_SubCharacter* nurse)
{
    u16 modelStates[8];
    s32 modelState;
    s32 speed;
    register s32 angle asm("v1"); // @hack forced register for a match. Doesn't affect code logic.

    switch (nurse->model_0.stateStep_3)
    {
        case 0:
            angle = func_8005BF38((g_SysWork.player_4C.chara_0.rotation_24.vy - nurse->rotation_24.vy) - FP_ANGLE(90.0f));
            if (angle < 0)
            {
                nurse->properties_E4.puppetNurse.field_104 = -angle;
            }
            else
            {
                nurse->properties_E4.puppetNurse.field_104 = angle;
            }
            nurse->model_0.stateStep_3++;
            break;
        case 1:
            if (nurse->properties_E4.puppetNurse.field_104 < 0)
            {
                nurse->moveSpeed_38 = Q12(-1.0f);
                nurse->model_0.anim_4.status_0 = ANIM_STATUS(10, false);
                nurse->model_0.stateStep_3 = 2;
            }
            nurse->properties_E4.puppetNurse.field_104 -= g_DeltaTime0;
            break;
        case 2:
            memcpy(modelStates, g_PuppetNurse_ModelStates0, sizeof(g_PuppetNurse_ModelStates0));
            if (nurse->model_0.anim_4.status_0 == ANIM_STATUS(18, false))
            {
                if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                {
                    modelState = 9;
                    
                }
                else
                {
                    modelState = modelStates[(Rng_Rand16() >> 4) & 7];
                }
                nurse->model_0.state_2 = modelState;
                nurse->model_0.stateStep_3 = 0;
            }
            else
            {
                speed = Rng_Rand16() & 0x1FF;
                Chara_MoveSpeedUpdate(nurse, (speed + Q12(0.8f)));
            }
            break;
    }
}
