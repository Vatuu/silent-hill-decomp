void Ai_PuppetNurse_Control(s_SubCharacter* arg0)
{
    switch (arg0->model_0.state_2)
    {
        case 1:
            Ai_PuppetNurse_Control1(arg0);
            break;

        case 2:
            Ai_PuppetNurse_Control2(arg0);
            break;

        case 3:
            Ai_PuppetNurse_Control3_4(arg0, 1);
            break;

        case 4:
            Ai_PuppetNurse_Control3_4(arg0, 0);
            break;

        case 5:
            Ai_PuppetNurse_Control5(arg0);
            break;

        case 6:
            Ai_PuppetNurse_Control6_7(arg0, 0);
            break;

        case 7:
            Ai_PuppetNurse_Control6_7(arg0, 1);
            break;

        case 8:
            sharedFunc_800CEC88_3_s03(arg0);
            break;

        case 9:
            sharedFunc_800CF3AC_3_s03(arg0);
            break;

        case 10:
            sharedFunc_800CFD18_3_s03(arg0);
            break;

        case 11:
            sharedFunc_800CFDD4_3_s03(arg0);
            break;

        case 12:
            sharedFunc_800CF9F8_3_s03(arg0);
            break;

        case 13:
            sharedFunc_800D0110_3_s03(arg0);
            break;
    }
}
