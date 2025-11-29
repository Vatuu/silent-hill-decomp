void sharedFunc_800D3C24_2_s00(s_SubCharacter* chara)
{
    bool cond0;
    bool cond1;
    s32  newStep;
    s32  animStatus;
    s32  animState;
    s32  animStatusCheck;
    u32  tmp0;
    u32  step;

    animStatus = chara->model_0.anim_4.status_0;
    sharedFunc_800D5638_0_s01(chara);
    step      = chara->model_0.stateStep_3;
    animState = ANIM_STATUS(12, true);

    animStatusCheck = animStatus | 1; // TODO: Use macro.

    switch (step)
    {
        case 0:
            newStep = sharedFunc_800E0698_2_s00(chara);
            cond1   = false;
            cond0   = chara->position_18.vy >= Q12(8.0f);

            if (func_800808AC(chara->position_18.vx, chara->position_18.vz) == 7)
            {
                cond1 = chara->position_18.vy >= func_80080884(chara->position_18.vx, chara->position_18.vz);
            }

            if (cond0)
            {
                Chara_DamageTake(chara, 0);

                chara->position_18.vx = g_SysWork.player_4C.chara_0.position_18.vx + Q12(100.0f);
                chara->position_18.vz = g_SysWork.player_4C.chara_0.position_18.vz + Q12(100.0f);

                sharedFunc_800D3DFC_0_s01(chara);
                break;
            }

            if (cond1)
            {
                Chara_DamageTake(chara, 0);
                sharedFunc_800D2364_0_s01(chara);

                chara->position_18.vx = g_SysWork.player_4C.chara_0.position_18.vx + Q12(100.0f);
                chara->position_18.vz = g_SysWork.player_4C.chara_0.position_18.vz + Q12(100.0f);

                sharedFunc_800D3DFC_0_s01(chara);
                break;
            }

            if (chara->health_B0 <= Q12(0.0f))
            {
                Chara_DamageTake(chara, 0);

                if (animStatus == ANIM_STATUS(26, true) && newStep == 1)
                {
                    chara->health_B0 = NO_VALUE;
                    func_800622B8(3, chara, ANIM_STATUS(4, true), 2);
                    chara->model_0.stateStep_3 = newStep;
                    sharedFunc_800D3DFC_0_s01(chara);
                }
            }
            else
            {
                chara->flags_3E |= CharaFlag_Unk2;

                if (Chara_DamageTake(chara, Q12(1.0f)) == 4)
                {
                    if (chara->health_B0 <= Q12(0.0f))
                    {
                        chara->model_0.anim_4.status_0         = ANIM_STATUS(5, false);
                        chara->properties_E4.player.flags_11C |= PlayerFlag_Unk6;
                        break;
                    }

                    chara->model_0.anim_4.status_0         = ANIM_STATUS(12, false);
                    chara->model_0.stateStep_3             = 2;
                    chara->properties_E4.player.flags_11C |= PlayerFlag_WallStopRight;
                }
            }
            break;

        case 1:
            Chara_DamageTake(chara, 0);
            break;

        case 2:
            Chara_DamageTake(chara, Q12(0.5f));

            if (animStatusCheck != animState)
            {
                chara->model_0.stateStep_3 = 0;
            }
            break;
    }
}
