// NOTE: Function body is only included in M2S00/M2S02/M4S02/M5S01/M6S00, all other maps include the function without any body.

/** @brief Returns `true` if angle `a` is generally in front of angle `b`.
 * Checks the angle difference and reports if it falls within the forward arc.
 */
static inline bool Math_AngleFrontCheck(u16 a, u16 b)
{
    s32 diff = FP_ANGLE_ABS(a - b);
    return diff < FP_ANGLE(90.0f) || diff >= FP_ANGLE(270.0f);
}

void sharedFunc_800D2E9C_0_s00(s32* arg0, s32* arg1, s16* arg2)
{
#if defined(MAP2_S00) || defined(MAP2_S02) || defined(MAP4_S02) || defined(MAP5_S01) || defined(MAP6_S00)
    VECTOR3 vec;
    s16     charaHeading;
    s16     temp_s1;
    s32     angleFrontOfChara;

    g_SysWork.player_4C.chara_0.properties_E4.player.playerMoveDistance_126 = 0;
    g_SysWork.player_4C.chara_0.headingAngle_3C                             = 0;
    angleFrontOfChara                                                       = Math_AngleFrontCheck(*arg2, g_SysWork.player_4C.chara_0.rotation_24.vy);

    arg2--; // @hack Permuter find, needed for match
    arg2++;

    if (!angleFrontOfChara)
    {
        D_800C4610.vx = *arg0 + FP_FROM((Math_Cos(*arg2) * -0x16C) + (Math_Sin(*arg2) * -0x6B0), Q12_SHIFT);
        D_800C4610.vz = *arg1 + FP_FROM((-Math_Sin(*arg2) * -0x16C) + (Math_Cos(*arg2) * -0x6B0), Q12_SHIFT);
    }
    else
    {
        D_800C4610.vx = *arg0 + FP_FROM((Math_Cos(*arg2) * -0xCB) + (Math_Sin(*arg2) * 0x3C6), Q12_SHIFT);
        D_800C4610.vz = *arg1 + FP_FROM((-Math_Sin(*arg2) * -0xCB) + (Math_Cos(*arg2) * 0x3C6), Q12_SHIFT);
    }

    charaHeading = g_SysWork.player_4C.chara_0.headingAngle_3C;
    vec.vx       = Math_Sin(charaHeading); // @unused
    vec.vx       = 0;
    vec.vz       = Math_Cos(charaHeading); // @unused
    vec.vz       = 0;

    vec.vx = D_800C4610.vx - g_SysWork.player_4C.chara_0.position_18.vx;
    vec.vz = D_800C4610.vz - g_SysWork.player_4C.chara_0.position_18.vz;
    vec.vy = FP_MULTIPLY_PRECISE(g_SysWork.player_4C.chara_0.field_34, g_DeltaTime0, Q12_SHIFT);

    func_80069B24(&D_800C4590, &vec, &g_SysWork.player_4C.chara_0);

    D_800C4610.vx = g_SysWork.player_4C.chara_0.position_18.vx + D_800C4590.offset_0.vx;
    D_800C4610.vz = g_SysWork.player_4C.chara_0.position_18.vz + D_800C4590.offset_0.vz;

    if (!angleFrontOfChara)
    {
        temp_s1 = *arg2 + FP_ANGLE(180.0f);
        *arg0   = D_800C4610.vx + FP_FROM((Math_Cos(temp_s1) * 0x16C) + (Math_Sin(temp_s1) * 0x6B0), Q12_SHIFT);
        *arg1   = D_800C4610.vz + FP_FROM((-Math_Sin(temp_s1) * 0x16C) + (Math_Cos(temp_s1) * 0x6B0), Q12_SHIFT);
    }
    else
    {
        temp_s1 = *arg2;
        *arg0   = D_800C4610.vx + FP_FROM((Math_Cos(temp_s1) * 0xCB) + (Math_Sin(temp_s1) * -0x3C6), Q12_SHIFT);
        *arg1   = D_800C4610.vz + FP_FROM((-Math_Sin(temp_s1) * 0xCB) + (Math_Cos(temp_s1) * -0x3C6), Q12_SHIFT);
    }
#endif
}
