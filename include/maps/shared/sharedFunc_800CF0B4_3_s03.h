void sharedFunc_800CF0B4_3_s03(s_SubCharacter* nurse)
{
    q19_12          limit;
    q3_12           angle;
    s_SubCharacter* localNurse;

    limit = Q12_MULT_PRECISE(nurse->properties_E4.npc.field_124->field_C, Q12(0.27f));
    localNurse = nurse;

    Chara_MoveSpeedUpdate2(nurse, Q12(1.4f), limit);
    limit = Q12(0.0f);

    // @note Did they forget to make it an if?
    Rng_Rand16();
    localNurse->properties_E4.puppetNurse.field_11C = Chara_HeadingAngleGet(nurse,
                                                                    Q12(1.0f),
                                                                    g_SysWork.playerWork_4C.player_0.position_18.vx,
                                                                    g_SysWork.playerWork_4C.player_0.position_18.vz,
                                                                    Q12_ANGLE(360.0f),
                                                                    true);

    angle = func_8005BF38(localNurse->properties_E4.puppetNurse.field_11C - nurse->rotation_24.vy);
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
