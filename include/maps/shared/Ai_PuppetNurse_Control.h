void Ai_PuppetNurse_Control(s_SubCharacter* nurse)
{
    switch (nurse->model_0.state_2)
    {
        case 1:
            Ai_PuppetNurse_Control1(nurse);
            break;

        case 2:
            Ai_PuppetNurse_Control2(nurse);
            break;

        case 3:
            Ai_PuppetNurse_Control3_4(nurse, 1);
            break;

        case 4:
            Ai_PuppetNurse_Control3_4(nurse, 0);
            break;

        case 5:
            Ai_PuppetNurse_Control5(nurse);
            break;

        case 6:
            Ai_PuppetNurse_Control6_7(nurse, 0);
            break;

        case 7:
            Ai_PuppetNurse_Control6_7(nurse, 1);
            break;

        case 8:
            sharedFunc_800CEC88_3_s03(nurse);
            break;

        case 9:
            Ai_PuppetNurse_Control9(nurse);
            break;

        case 10:
            Ai_PuppetNurse_Control10(nurse);
            break;

        case 11:
            sharedFunc_800CFDD4_3_s03(nurse);
            break;

        case 12:
            sharedFunc_800CF9F8_3_s03(nurse);
            break;

        case 13:
            sharedFunc_800D0110_3_s03(nurse);
            break;
    }
}
