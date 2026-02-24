void sharedFunc_800CF7F4_3_s03(s_SubCharacter* nurse)
{
    int angle; // TODO: Type

    if ((Rng_Rand16() & Q8_CLAMPED(1.0f)) >= Q8(0.5f))
    {
        nurse->properties_E4.dummy.properties_E8[13].val16[0] = Chara_HeadingAngleGet(nurse,
                                                                                      Q12(1.0f),
                                                                                      g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                                                      g_SysWork.playerWork_4C.player_0.position_18.vz,
                                                                                      Q12_ANGLE(360.0f),
                                                                                      true);
    }

    angle = func_8005BF38(nurse->properties_E4.dummy.properties_E8[13].val16[0] - nurse->rotation_24.vy);
    if (ABS(angle) > Q12_ANGLE(5.0f))
    {
        if (angle > Q12_ANGLE(0.0f))
        {
            nurse->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
        else
        {
            nurse->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime, Q12_ANGLE(90.0f));
        }
    }
}
