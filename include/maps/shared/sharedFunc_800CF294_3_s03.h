bool sharedFunc_800CF294_3_s03(s_SubCharacter* arg0, q19_12 dist)
{
    s32           temp_a0;
    s32           temp_v1;
    s32           ret;
    s_D_800D5A8C* somePtr;

    somePtr = &sharedData_800D5A8C_3_s03[sharedFunc_800CEEAC_3_s03()];

    if (arg0->properties_E4.npc.field_11A > 0)
    {
        arg0->properties_E4.npc.field_11A -= g_DeltaTime;
    }

    if (func_80070360(arg0, dist, somePtr->field_8))
    {
        arg0->properties_E4.npc.field_11A = Q12_ANGLE(360.0f);
    }

    temp_v1 = somePtr->field_0;
    temp_a0 = arg0->properties_E4.npc.field_124->field_8;

    ret = false;
    if (func_8006FD90(arg0, 1, Q12_MULT_PRECISE(temp_v1, temp_a0), Q12_MULT_PRECISE(somePtr->field_4, temp_a0)) ||
        arg0->properties_E4.npc.field_11A > 0)
    {
        ret = true;
    }

    return ret;
}
