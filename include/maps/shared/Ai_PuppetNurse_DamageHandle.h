void Ai_PuppetNurse_DamageHandle(s_SubCharacter* nurse)
{
    q19_12          newHealth;
    s32             sfxIdx;
    s_SubCharacter* nurseCpy;

    nurseCpy = nurse;

    if (nurse->damage_B4.amount_C > Q12(0.0f))
    {
        sfxIdx = PuppetNurse_HurtSfxIdGet(nurse);
        if (sfxIdx != NO_VALUE)
        {
            Ai_PuppetNurse_SfxPlay(nurse, sfxIdx);
        }

        switch (nurse->properties_E4.puppetNurse.field_118)
        {
            case 0:
                nurse->properties_E4.puppetNurse.damage_F4 = nurse->damage_B4;
                nurse->properties_E4.puppetNurse.field_114 += nurse->damage_B4.amount_C;

                newHealth = nurse->health_B0 - nurse->damage_B4.amount_C;
                if (newHealth < Q12(0.0f))
                {
                    newHealth = Q12(0.0f);
                }

                nurse->health_B0 = newHealth;
                if (newHealth <= Q12(120.0f))
                {
                    nurse->properties_E4.puppetNurse.field_118++;

                    if (!Ai_PuppetNurse_SomeAngleCheck(nurse))
                    {
                        nurse->model_0.controlState_2 = PuppetNurseControl_4;
                        nurse->model_0.stateStep_3 = 0;
                    }
                    else
                    {
                        nurse->model_0.controlState_2 = PuppetNurseControl_3;
                        nurse->model_0.stateStep_3 = 0;
                    }

                    if (!nurse->health_B0)
                    {
                        Savegame_EnemyStateUpdate(nurse);
                    }
                }
                else
                {
                    if (nurse->model_0.controlState_2 != PuppetNurseControl_2 &&
                        ((nurse->properties_E4.puppetNurse.field_124->field_4 < nurse->properties_E4.puppetNurse.field_114) ||
                         (nurse->damage_B4.amount_C > Q12(320.0f))))
                    {
                        nurse->properties_E4.puppetNurse.field_114 = 0;
                        nurse->model_0.controlState_2 = PuppetNurseControl_2;
                        nurse->model_0.stateStep_3 = 0;
                    }
                }
                break;

            case 1:
                if (nurse->health_B0)
                {
                    Ai_PuppetNurse_SfxPlay(nurse, 1);
                    nurse->health_B0 = Q12(0.0f);
                    Savegame_EnemyStateUpdate(nurse);

                    if (nurse->model_0.anim_4.status_0 == ANIM_STATUS(14, true))
                    {
                        nurse->model_0.anim_4.status_0 = ANIM_STATUS(22, false);
                    }
                }

                nurseCpy->properties_E4.npc.field_118++;

            case 2:
                break;
        }
    }

    Chara_DamageClear(nurse);
}
