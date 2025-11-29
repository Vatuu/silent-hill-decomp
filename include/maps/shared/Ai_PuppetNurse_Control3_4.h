void Ai_PuppetNurse_Control3_4(s_SubCharacter* nurse, s32 arg1)
{
    s32 animStat;
    s32 moveSpeed;
    s32 idx;
    s_SubCharacter* nurseCpy;

    nurseCpy = nurse;
    if (!nurse->model_0.stateStep_3)
    {
        if (nurse->model_0.anim_4.status_0 == ANIM_STATUS(2, true)) 
        {
            return;
        }
        Ai_PuppetNurse_SfxPlay(nurse, 2);
        nurse->model_0.anim_4.status_0 = g_PuppetNurse_AnimStatus0[arg1];
        nurse->field_E1_0 = 4;
        nurse->flags_3E |= (1<<1);
        nurse->model_0.stateStep_3++;
    }

    animStat = nurse->model_0.anim_4.status_0;
    if (animStat == ANIM_STATUS(14, true) || animStat == ANIM_STATUS(5, true) ||
        animStat == ANIM_STATUS(5, false) || animStat == ANIM_STATUS(15, true))
    {
        if ((func_8005C7D0(nurse) != g_SysWork.targetNpcIdx_2353) && (nurse->health_B0 == 0))
        {
            nurse->health_B0 = NO_VALUE;
            nurse->field_E1_0 = 0;
            func_800622B8(3, nurse, g_PuppetNurse_AnimStatus1[arg1], 11);
            nurseCpy->properties_E4.puppetNurse.flags_122 |= (1<<1);
        } 
        else if ((nurse->model_0.anim_4.status_0 == ANIM_STATUS(15, true)) && (nurse->health_B0 > 0))
        {
            nurse->model_0.anim_4.status_0 = ANIM_STATUS(5, false);
        }
    }
    Chara_MoveSpeedUpdate(nurse, Q12(4.0f));
}
