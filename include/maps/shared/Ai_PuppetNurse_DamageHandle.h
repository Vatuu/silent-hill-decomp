void Ai_PuppetNurse_DamageHandle(s_SubCharacter* nurse)
{
    s32 hpLeft;
    s32 sfxIdx;
    s_SubCharacter* nurseCpy;

    nurseCpy = nurse;
    if (nurse->dmg_B4.damageReceived_C > 0)
    {
        sfxIdx = PuppetNurse_HurtSfxIdGet(nurse);
        if (sfxIdx != NO_VALUE)
        {
            Ai_PuppetNurse_SfxPlay(nurse, sfxIdx);
        }
        switch (nurse->properties_E4.unk1.field_118) 
        {
            case 0:
                nurse->properties_E4.unk1.dmg_F4 = nurse->dmg_B4;
                nurse->properties_E4.unk1.field_114 += nurse->dmg_B4.damageReceived_C;
                hpLeft = nurse->health_B0 - nurse->dmg_B4.damageReceived_C;
                
                if (hpLeft < 0)
                {
                    hpLeft = 0;
                }
                nurse->health_B0 = hpLeft;
                if (hpLeft <= Q12(120.0f))
                {
                    nurse->properties_E4.unk1.field_118++;
                    
                    if (!Ai_PuppetNurse_SomeAngleCheck(nurse))
                    {
                        nurse->model_0.state_2 = 4;
                        nurse->model_0.stateStep_3 = 0;
                    }
                    else
                    {
                        nurse->model_0.state_2 = 3;
                        nurse->model_0.stateStep_3 = 0;
                    }

                    if (!nurse->health_B0)
                    {
                        func_80037DC4(nurse);
                    }
                }
                else
                {
                    if (nurse->model_0.state_2 != 2 && 
                        ((nurse->properties_E4.unk1.field_124->field_4 < nurse->properties_E4.unk1.field_114) || (nurse->dmg_B4.damageReceived_C > Q12(320.0f))))
                    {
                        nurse->properties_E4.unk1.field_114 = 0;
                        nurse->model_0.state_2 = 2;
                        nurse->model_0.stateStep_3 = 0;
                    }
                }
                break;
            case 1:
                if (nurse->health_B0)
                {
                    Ai_PuppetNurse_SfxPlay(nurse, 1);
                    nurse->health_B0 = 0;
                    func_80037DC4(nurse);
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

