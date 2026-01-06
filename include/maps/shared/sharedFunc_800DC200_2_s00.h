bool sharedFunc_800DC200_2_s00(s_SubCharacter* airScreamer)
{
    if ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 0x1) &&
        (g_SavegamePtr->gameDifficulty_260 <= GameDifficulty_Normal || airScreamer->model_0.charaId_0 == Chara_AirScreamer))
    {
        return false;
    }

    sharedData_800F216C_2_s00.vx = airScreamer->position_18.vx + Q12_MULT_PRECISE(Math_Sin(airScreamer->rotation_24.vy), Q12(2.0f));
    sharedData_800F216C_2_s00.vy = airScreamer->position_18.vy + Q12(0.5f);
    sharedData_800F216C_2_s00.vz = airScreamer->position_18.vz + Q12_MULT_PRECISE(Math_Cos(airScreamer->rotation_24.vy), Q12(2.0f));

    return sharedFunc_800D4AEC_0_s01(airScreamer, NULL, &sharedData_800F216C_2_s00, NULL) != 0;
}
