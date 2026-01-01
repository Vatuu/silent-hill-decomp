s32 sharedFunc_800DEE24_2_s00(s_SubCharacter* airScreamer)
{
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 temp_fp;
    s32 sp1C;
    s32 sp20;
    s32 temp_s6;
    s32 var_s4;
    s32 var_s0;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_v0_2;
    s32 var_s1;
    s32 var_s2;
    s32 var_s3;
    s32 var_v1;

    var_s4 = g_SysWork.playerWork_4C.player_0.headingAngle_3C;
    var_s3 = g_SysWork.playerWork_4C.player_0.moveSpeed_38;

    sp10 = g_SysWork.playerWork_4C.player_0.position_18.vx;
    sp14 = g_SysWork.playerWork_4C.player_0.position_18.vy;
    sp18 = g_SysWork.playerWork_4C.player_0.position_18.vz;

    temp_fp = airScreamer->position_18.vx;
    sp1C    = airScreamer->position_18.vz;

    temp_s6 = airScreamer->rotation_24.vy;
    sp20    = airScreamer->moveSpeed_38;

    var_s1 = FP_MULTIPLY_PRECISE(var_s3, Math_Sin(var_s4), Q12_SHIFT);
    var_s0 = FP_MULTIPLY_PRECISE(var_s3, Math_Cos(var_s4), Q12_SHIFT);

    sharedData_800F21FC_2_s00.vy = 0;
    sharedData_800F21FC_2_s00.vx = FP_MULTIPLY_PRECISE(g_DeltaTime0, var_s1, Q12_SHIFT);
    sharedData_800F21FC_2_s00.vz = FP_MULTIPLY_PRECISE(g_DeltaTime0, var_s0, Q12_SHIFT);

    if (g_DeltaTime0 != 0 && func_80069B24(&sharedData_800E2350_0_s01, &sharedData_800F21FC_2_s00, &g_SysWork.playerWork_4C.player_0))
    {
        var_s1 = sharedData_800E2350_0_s01.offset_0.vx;
        var_s0 = sharedData_800E2350_0_s01.offset_0.vz;

        var_s3 = SquareRoot12(FP_SQUARE_PRECISE(var_s1, Q12_SHIFT) + FP_SQUARE_PRECISE(var_s0, Q12_SHIFT));
        var_s3 = FP_TO(var_s3, Q12_SHIFT) / g_DeltaTime0;
        var_s4 = ratan2(var_s1, var_s0);
    }

    temp_v0_2 = Math_Cos(FP_ANGLE_NORM_S(temp_s6 - var_s4));

    var_s1 = sp10 - temp_fp;
    var_s0 = sp18 - sp1C;

    var_s2    = sp20 - FP_MULTIPLY_PRECISE(var_s3, temp_v0_2, Q12_SHIFT);
    temp_v0_2 = FP_ANGLE_NORM_S(ratan2(var_s1, var_s0) - temp_s6);

    if (temp_v0_2 > -0x2AB && temp_v0_2 < 0x2AA)
    {
        var_s0 = SquareRoot12(FP_SQUARE_PRECISE(var_s1, Q12_SHIFT) + FP_SQUARE_PRECISE(var_s0, Q12_SHIFT));

        if (var_s2 < 0x1000)
        {
            var_s2 = 0x1000;
        }

        var_s2 = FP_TO(var_s0, Q12_SHIFT) / var_s2;
        var_s0 = FP_MULTIPLY_PRECISE(var_s3, var_s2, Q12_SHIFT);
        var_s1 = FP_MULTIPLY_PRECISE(var_s0, Math_Sin(var_s4), Q12_SHIFT);
        var_s0 = FP_MULTIPLY_PRECISE(var_s0, Math_Cos(var_s4), Q12_SHIFT);
    }
    else
    {
        var_s2 = 0xA000;
        var_s1 = 0;
        var_s0 = 0;
    }

    temp_s4 = sp10 + var_s1;
    temp_s3 = sp18 + var_s0;
    var_s1  = sp14 + g_SysWork.playerWork_4C.player_0.field_C8.field_0;

    var_s0 = Collision_GroundHeightGet(temp_s4, temp_s3);
    var_v1 = airScreamer->properties_E4.airScreamer.groundHeight_124;

    if (var_v1 < var_s0)
    {
        var_s0 = var_v1;
    }

    if (var_s0 < sharedFunc_800D5274_0_s01())
    {
        var_s0 = sharedFunc_800D5274_0_s01();
    }

    var_v1 = var_s0 - 0x2000;

    if (var_s1 < var_v1)
    {
        var_s1 = var_v1;
    }

    airScreamer->properties_E4.airScreamer.targetPosition_F8.vx = temp_s4;
    airScreamer->properties_E4.airScreamer.targetPosition_F8.vy = var_s1;
    airScreamer->properties_E4.airScreamer.targetPosition_F8.vz = temp_s3;

    sharedFunc_800D4E84_0_s01(airScreamer);

    return var_s2;
}