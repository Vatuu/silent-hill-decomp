void Ai_PuppetNurse_Control9(s_SubCharacter* nurse)
{
    bool cond;
    s32 dist;
    s32 deltaX;
    s32 deltaZ;
    u16 rng;
    s16 angle;
    s16 angleAbs;
    s_800D5710* somePtr;
    s_SubCharacter* nurseCpy;

    nurseCpy = nurse;
    deltaX = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vx - nurse->position_18.vx);
    deltaZ = Q12_TO_Q6(g_SysWork.player_4C.chara_0.position_18.vz - nurse->position_18.vz);
    dist   = Q6_TO_Q12(SquareRoot0(SQUARE(deltaX) + SQUARE(deltaZ)));
    angle = func_8005BF38(ratan2(
        g_SysWork.player_4C.chara_0.position_18.vx - nurse->position_18.vx,
        g_SysWork.player_4C.chara_0.position_18.vz - nurse->position_18.vz) - nurse->rotation_24.vy);
    angleAbs = ABS(angle);

    if (!nurse->model_0.stateStep_3)
    {
        nurse->properties_E4.player.field_104 = 0;
        nurse->properties_E4.puppetNurse.field_11C = func_8006F99C(nurse, FP_ANGLE(360.0f), nurse->rotation_24.vy);
        nurse->model_0.stateStep_3++;
    }
    cond = sharedFunc_800CF294_3_s03(nurse, dist);
    nurse->field_44.field_0 = 0;
    switch (nurse->model_0.stateStep_3)
    {
        case 1:
            if (!cond)
            {
                sharedFunc_800CEEE0_3_s03(nurse);
                break;
            } 
            else
            {
                nurse->model_0.stateStep_3 = 2;
            }
            /* fallthrough */
        case 2:
            if (!cond) 
            {
                nurse->model_0.stateStep_3 = 1;
            }
            else
            {
                sharedFunc_800CF0B4_3_s03(nurse);
                somePtr = nurseCpy->properties_E4.npc.field_124;
                if (dist < FP_MULTIPLY_PRECISE(somePtr->field_8, Q12(3.0f), Q12_SHIFT) &&
                    angleAbs < FP_ANGLE(60.0f) && g_SysWork.player_4C.chara_0.health_B0 > 0)
                {
                    nurse->model_0.state_2 = 12;
                    nurse->model_0.stateStep_3 = 0;
                }
            }
            break;
    }
    if (nurse->model_0.stateStep_3 && sharedFunc_800CE398_3_s03(nurse->model_0.anim_4.status_0))
    {
        if (!(Rng_Rand16() & 0x1F))
        {
            rng = Rng_Rand16();
            nurse->model_0.anim_4.status_0 = g_PuppetNurse_AnimStatus2[(rng >> 7) & 1];
            nurse->model_0.state_2 = 6;
            nurse->model_0.stateStep_3 = 0;
            return;
        }
        else
        {
            nurse->model_0.anim_4.status_0 = g_PuppetNurse_AnimStatus3[(Rng_Rand16() >> 2) & 3];
        }
    }
}
