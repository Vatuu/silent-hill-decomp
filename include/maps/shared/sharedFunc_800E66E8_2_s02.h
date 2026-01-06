void sharedFunc_800E66E8_2_s02(s_SubCharacter* romper)
{
    u8 curModelState;

    if (romper->model_0.controlState_2 != 5)
    {
        romper->field_44.field_0 = 0;
    }

    curModelState = romper->model_0.controlState_2;

    sharedData_800ECC14_2_s02[curModelState](romper);

    if (romper->model_0.controlState_2 != curModelState)
    {
        romper->properties_E4.romper.field_120 = 0;
    }
}