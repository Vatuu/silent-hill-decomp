void Ai_PuppetNurse_Control3_4(s_SubCharacter* nurse, s32 idx)
{
    s32             animStatus;
    s_SubCharacter* localNurse;

    localNurse = nurse;

    if (!nurse->model_0.stateStep_3)
    {
        if (nurse->model_0.anim_4.status_0 == ANIM_STATUS(PuppetNurseAnim_2, true)) 
        {
            return;
        }

        Ai_PuppetNurse_SfxPlay(nurse, 2);

        nurse->model_0.anim_4.status_0 = g_PuppetNurse_AnimStatus0[idx];
        nurse->field_E1_0 = 4;
        nurse->flags_3E |= CharaFlag_Unk2;
        nurse->model_0.stateStep_3++;
    }

    animStatus = nurse->model_0.anim_4.status_0;
    if (animStatus == ANIM_STATUS(PuppetNurseAnim_14, true) || animStatus == ANIM_STATUS(PuppetNurseAnim_5, true) ||
        animStatus == ANIM_STATUS(PuppetNurseAnim_5, false) || animStatus == ANIM_STATUS(PuppetNurseAnim_15, true))
    {
        if ((func_8005C7D0(nurse) != g_SysWork.targetNpcIdx_2353) && (nurse->health_B0 == 0))
        {
            nurse->health_B0 = NO_VALUE;
            nurse->field_E1_0 = 0;
            func_800622B8(3, nurse, g_PuppetNurse_AnimStatus1[idx], 11);

            localNurse->properties_E4.puppetNurse.flags_122 |= PuppetNurseFlag_1;
        } 
        else if (nurse->model_0.anim_4.status_0 == ANIM_STATUS(PuppetNurseAnim_15, true) && nurse->health_B0 > Q12(0.0f))
        {
            nurse->model_0.anim_4.status_0 = ANIM_STATUS(PuppetNurseAnim_5, false);
        }
    }

    Chara_MoveSpeedUpdate(nurse, Q12(4.0f));
}
