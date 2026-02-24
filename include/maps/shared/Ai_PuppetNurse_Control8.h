void Ai_PuppetNurse_Control8(s_SubCharacter* nurse)
{
    u16          modelStates[8];
    s32          controlState;
    q19_12       speed;
#if !defined(M2CTX)
    register q19_12 angle asm("v1"); // @hack forced register for a match. Doesn't affect code logic.
#else
    q19_12 angle;
#endif

    switch (nurse->model_0.stateStep_3)
    {
        case 0:
            angle = func_8005BF38((g_SysWork.playerWork_4C.player_0.rotation_24.vy - nurse->rotation_24.vy) - Q12_ANGLE(90.0f));
            if (angle < Q12_ANGLE(0.0f))
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

            nurse->properties_E4.puppetNurse.field_104 -= g_DeltaTime;
            break;

        case 2:
            memcpy(modelStates, g_PuppetNurse_ModelStates0, sizeof(g_PuppetNurse_ModelStates0));

            if (nurse->model_0.anim_4.status_0 == ANIM_STATUS(18, false))
            {
                if (g_SavegamePtr->gameDifficulty_260 == GameDifficulty_Hard)
                {
                    controlState = PuppetNurseControl_9;
                }
                else
                {
                    controlState = modelStates[(Rng_Rand16() >> 4) & 7];
                }

                nurse->model_0.controlState_2 = controlState;
                nurse->model_0.stateStep_3 = 0;
            }
            else
            {
                speed = Rng_GenerateUInt(0, 0x1FF); // TODO: Combine with the +0.8f below?
                Chara_MoveSpeedUpdate(nurse, (speed + Q12(0.8f)));
            }
            break;
    }
}
