bool sharedFunc_800DC200_2_s00(s_SubCharacter* chara)
{
    if ((g_SysWork.field_2388.field_154.field_0.field_0.s_field_0.field_0 & 0x1) &&
        (g_SavegamePtr->gameDifficulty_260 <= GameDifficulty_Normal || chara->model_0.charaId_0 == Chara_AirScreamer))
    {
        return false;
    }

    sharedData_800F216C_2_s00.vx = chara->position_18.vx + FP_MULTIPLY_PRECISE(Math_Sin(chara->rotation_24.vy), Q12(2.0f), Q12_SHIFT);
    sharedData_800F216C_2_s00.vy = chara->position_18.vy + Q12(0.5f);
    sharedData_800F216C_2_s00.vz = chara->position_18.vz + FP_MULTIPLY_PRECISE(Math_Cos(chara->rotation_24.vy), Q12(2.0f), Q12_SHIFT);

    return sharedFunc_800DC98C_2_s00(chara, NULL, &sharedData_800F216C_2_s00, NULL) != 0;
}
