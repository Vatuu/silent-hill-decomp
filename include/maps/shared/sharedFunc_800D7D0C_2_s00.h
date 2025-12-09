void sharedFunc_800D7D0C_2_s00(s_SubCharacter* chara) // 0x800D7D0C
{
    s32     temp_fp;
    s32     temp_fp_tmp;
    bool    field14C_2;
    bool    field14C_2_tmp;
    bool    temp_s6;
    q19_12 dist0;
    q19_12 dist1;
    q19_12 posDiffAngle;
    q19_12 distTest;
    s32    switchCond;
    s32    animStatus;

    animStatus = chara->model_0.anim_4.status_0;
    switchCond = 0;

    temp_fp_tmp    = sharedFunc_800D4A80_0_s01(chara);
    dist0      = sharedData_800E21D0_0_s01.distance_150;
    field14C_2_tmp = sharedData_800E21D0_0_s01.field_14C.bits32.field_14C_2;
    temp_fp        = temp_fp_tmp;
    field14C_2     = field14C_2_tmp;
    temp_s6        = sharedFunc_800DC50C_2_s00(chara);

    sharedFunc_800DE940_2_s00(chara);
    switch (chara->model_0.stateStep_3)
    {
        case 0:
            #define ANGLE_DIFF FP_ANGLE_NORM_S(g_SysWork.player_4C.chara_0.rotation_24.vy - chara->rotation_24.vy)
            
            distTest = dist0 + (func_80080514() * 4);
            if (sharedFunc_800DC200_2_s00(chara) && distTest > Q12(8.0f))
            {
                chara->model_0.stateStep_3 = 4;
            }
            else if (!sharedFunc_800DC3BC_2_s00(chara) || distTest >= Q12(4.0f) ||
                     (ANGLE_DIFF < FP_ANGLE(-30.0f) || ANGLE_DIFF >= FP_ANGLE(30.0f)) ||
                     func_80080514() >= Q12(0.2f))
            {
                chara->model_0.stateStep_3 = 1;
            }
            else
            {
                chara->model_0.stateStep_3 = 2;
            }

            chara->properties_E4.unk0.properties_120.val32 = Q12(4.0f);
            break;

        case 1:
            distTest = NO_VALUE;
            if (chara->properties_E4.unk0.field_F8.vy - chara->position_18.vy > Q12(-0.2f) &&
                chara->properties_E4.unk0.field_F8.vy - chara->position_18.vy < Q12(0.8f))
            {
                distTest = chara->field_D4 + Q12(0.15f);
            }

            dist1    = Math_Distance2dGet(&chara->position_18, &chara->properties_E4.unk0.field_F8);
            posDiffAngle = FP_ANGLE_NORM_S(func_80080478(&chara->position_18, &chara->properties_E4.unk0.field_F8) - chara->rotation_24.vy);

            if (temp_s6)
            {
                chara->model_0.stateStep_3 = 2;
            }
            else if (dist1 < distTest && (posDiffAngle >= FP_ANGLE(-22.5f) && posDiffAngle < FP_ANGLE(22.5f)))
            {
                switchCond = 1;
            }
            else if (chara->properties_E4.unk0.properties_120.val32 == 0)
            {
                chara->model_0.stateStep_3 = 0;
            }
            break;

        case 2:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 2;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(27, false);
                chara->model_0.stateStep_3     = 3;
            }
            break;

        case 3:
            switchCond = 2;
            break;

        case 4:
            if (animStatus == ANIM_STATUS(19, true))
            {
                switchCond                     = 3;
                chara->model_0.anim_4.status_0 = ANIM_STATUS(18, false);
                chara->model_0.stateStep_3     = 5;
            }
            break;

        case 5:
            switchCond = 3;
            break;
    }

    sharedFunc_800D57C8_0_s01(chara);

    switch (Chara_DamageTake(chara, Q12(1.0f)))
    {
        case 0:
            switch (switchCond)
            {
                case 0:
                    if (!sharedFunc_800DC67C_2_s00(chara))
                    {
                        if (field14C_2 == 0)
                        {
                            chara->model_0.state_2     = 26;
                            chara->model_0.stateStep_3 = 0;
                        }
                    }
                    else
                    {
                        chara->model_0.state_2     = 27;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 1:
                    // TODO: Likely some kind of `CharaHasFlag` inline?
                    if (!((&g_SysWork.player_4C.chara_0)->flags_3E & CharaFlag_Unk4) &&
                        g_SysWork.npcIdxs_2354[0] == NO_VALUE &&
                        g_SysWork.npcIdxs_2354[1] == NO_VALUE)
                    {
                        if (animStatus == ANIM_STATUS(19, true))
                        {
                            chara->model_0.state_2     = 25;
                            chara->model_0.stateStep_3 = 0;
                        }
                    }
                    else
                    {
                        chara->model_0.state_2     = 24;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;

                case 2:
                    if (animStatus == ANIM_STATUS(23, true) || animStatus == ANIM_STATUS(25, true))
                    {
                        sharedFunc_800DE11C_2_s00(chara);
                        chara->model_0.state_2     = 10;
                        chara->model_0.stateStep_3 = 0;
                    }
                    else if (sharedFunc_800DC0A8_2_s00(chara))
                    {
                        chara->model_0.anim_4.status_0 = ANIM_STATUS(23, false);
                    }
                    break;

                case 3:
                    if (temp_fp == switchCond)
                    {
                        chara->model_0.state_2     = 38;
                        chara->model_0.stateStep_3 = 0;
                    }
                    break;
            }
            break;

        case 1:
            chara->model_0.state_2               = 29;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 2:
            chara->model_0.state_2               = 30;
            chara->model_0.stateStep_3           = 0;
            chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            break;

        case 3:
        case 4:
            chara->model_0.state_2     = 32;
            chara->model_0.stateStep_3 = 0;

            if (chara->health_B0 <= Q12(0.0f))
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk6;
            }
            else
            {
                chara->properties_E4.unk0.flags_11C |= CharaUnk0Flag_Unk3;
            }
            break;
    }
}
