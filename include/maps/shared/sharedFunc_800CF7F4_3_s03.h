void sharedFunc_800CF7F4_3_s03(s_SubCharacter* chara)
{
    int angle; // TODO: Type

    if ((Rng_Rand16() & Q8_CLAMPED(1.0f)) >= Q8(0.5f))
    {
        chara->properties_E4.larvalStalker.properties_E8[13].val16[0] = func_8006FAFC(chara,
                                                                                      Q12(1.0f),
                                                                                      g_SysWork.player_4C.chara_0.position_18.vx,
                                                                                      g_SysWork.player_4C.chara_0.position_18.vz,
                                                                                      FP_ANGLE(360.0f),
                                                                                      1);
    }

    angle = func_8005BF38(chara->properties_E4.larvalStalker.properties_E8[13].val16[0] - chara->rotation_24.vy);
    if (ABS(angle) > FP_ANGLE(5.0f))
    {
        if (angle > FP_ANGLE(0.0f))
        {
            chara->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
        }
        else
        {
            chara->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
        }
    }
}
