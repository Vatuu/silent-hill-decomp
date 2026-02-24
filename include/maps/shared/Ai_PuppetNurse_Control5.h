void Ai_PuppetNurse_Control5(s_SubCharacter* nurse)
{
    s32 controlState;

    if (!nurse->model_0.stateStep_3)
    {
        nurse->model_0.anim_4.status_0 = ANIM_STATUS(PuppetNurseAnim_6, false);
        nurse->properties_E4.player.field_104 = 0;
        nurse->model_0.stateStep_3++;
    }

    sharedFunc_800CE7C8_3_s03(nurse);

    controlState = nurse->model_0.stateStep_3;
    if (controlState == PuppetNurseControl_1)
    {
        if (nurse->properties_E4.puppetNurse.flags_122 & PuppetNurseFlag_0)
        {
            nurse->model_0.stateStep_3 = 2;
        }
        else
        {
            if (nurse->properties_E4.player.field_104 <= Q12(1.5f))
            {
                if (func_80070320())
                {
                    nurse->model_0.controlState_2 = controlState;
                    nurse->model_0.stateStep_3 = 0;
                    nurse->model_0.anim_4.status_0 = ANIM_STATUS(PuppetNurseAnim_18, false);
                    return;
                }
            }
            else
            {
                nurse->model_0.controlState_2 = PuppetNurseControl_13;
                nurse->model_0.stateStep_3 = 0;
                return;
            }
        }
    }
    else if (controlState == 2)
    {
        if (Chara_AttackReceivedGet(&g_SysWork.playerWork_4C.player_0) == NO_VALUE)
        {
            nurse->model_0.controlState_2 = PuppetNurseControl_8;
            nurse->model_0.stateStep_3 = 0;
            return;
        }

        if (nurse->properties_E4.puppetNurse.field_104 >= Q12(1.5f))
        {
            // TODO: `D_800AD4C8` indexes different weapon attacks, but `WEAPON_ATTACK` macro can't match 56 with current `EquippedWeaponId`/`AttackInputType` enums?
            g_SysWork.playerWork_4C.player_0.damage_B4.amount_C += Q12(D_800AD4C8[56].field_4);
            nurse->properties_E4.puppetNurse.field_104 = 0;
        }
    }

    nurse->properties_E4.puppetNurse.field_104 += g_DeltaTime;
}
