void Ai_PuppetNurse_Control(s_SubCharacter* nurse)
{
    // Handle control state.
    switch (nurse->model_0.state_2)
    {
        case PuppetNurseState_1:
            Ai_PuppetNurse_Control1(nurse);
            break;

        case PuppetNurseState_2:
            Ai_PuppetNurse_Control2(nurse);
            break;

        case PuppetNurseState_3:
            Ai_PuppetNurse_Control3_4(nurse, true);
            break;

        case PuppetNurseState_4:
            Ai_PuppetNurse_Control3_4(nurse, false);
            break;

        case PuppetNurseState_5:
            Ai_PuppetNurse_Control5(nurse);
            break;

        case PuppetNurseState_6:
            Ai_PuppetNurse_Control6_7(nurse, false);
            break;

        case PuppetNurseState_7:
            Ai_PuppetNurse_Control6_7(nurse, true);
            break;

        case PuppetNurseState_8:
            Ai_PuppetNurse_Control8(nurse);
            break;

        case PuppetNurseState_9:
            Ai_PuppetNurse_Control9(nurse);
            break;

        case PuppetNurseState_10:
            Ai_PuppetNurse_Control10(nurse);
            break;

        case PuppetNurseState_11:
            Ai_PuppetNurse_Control11(nurse);
            break;

        case PuppetNurseState_12:
            Ai_PuppetNurse_Control12(nurse);
            break;

        case PuppetNurseState_13:
            Ai_PuppetNurse_Control13(nurse);
            break;
    }
}
