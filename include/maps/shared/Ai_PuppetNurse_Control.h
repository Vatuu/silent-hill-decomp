void Ai_PuppetNurse_Control(s_SubCharacter* nurse)
{
    // Handle control state.
    switch (nurse->model_0.state_2)
    {
        case PuppetNurseControl_1:
            Ai_PuppetNurse_Control1(nurse);
            break;

        case PuppetNurseControl_2:
            Ai_PuppetNurse_Control2(nurse);
            break;

        case PuppetNurseControl_3:
            Ai_PuppetNurse_Control3_4(nurse, true);
            break;

        case PuppetNurseControl_4:
            Ai_PuppetNurse_Control3_4(nurse, false);
            break;

        case PuppetNurseControl_5:
            Ai_PuppetNurse_Control5(nurse);
            break;

        case PuppetNurseControl_6:
            Ai_PuppetNurse_Control6_7(nurse, false);
            break;

        case PuppetNurseControl_7:
            Ai_PuppetNurse_Control6_7(nurse, true);
            break;

        case PuppetNurseControl_8:
            Ai_PuppetNurse_Control8(nurse);
            break;

        case PuppetNurseControl_9:
            Ai_PuppetNurse_Control9(nurse);
            break;

        case PuppetNurseControl_10:
            Ai_PuppetNurse_Control10(nurse);
            break;

        case PuppetNurseControl_11:
            Ai_PuppetNurse_Control11(nurse);
            break;

        case PuppetNurseControl_12:
            Ai_PuppetNurse_Control12(nurse);
            break;

        case PuppetNurseControl_13:
            Ai_PuppetNurse_Control13(nurse);
            break;
    }
}
