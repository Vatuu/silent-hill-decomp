void sharedFunc_800CF0B4_3_s03(s_SubCharacter* nurse) 
{
    s32 limit;
    s16 angle;
    s_SubCharacter* nurseCpy;

    limit = FP_MULTIPLY_PRECISE(nurse->properties_E4.npc.field_124->field_C, Q12(0.27f), Q12_SHIFT);
    nurseCpy = nurse;
    Chara_MoveSpeedUpdate2(nurse, Q12(1.4f), limit);
    limit =0;

    // @note Did they forgot to make it an if ?
    Rng_Rand16();
    nurseCpy->properties_E4.puppetNurse.field_11C = 
        func_8006FAFC(nurse, Q12(1.0f), g_SysWork.player_4C.chara_0.position_18.vx,
                      g_SysWork.player_4C.chara_0.position_18.vz, FP_ANGLE(360.0f), 1);

    angle = func_8005BF38(nurseCpy->properties_E4.puppetNurse.field_11C - nurse->rotation_24.vy);
    if (ABS(angle) > FP_ANGLE(5.0f))
    {
        if (angle > FP_ANGLE(0.0f))
        {
            nurse->rotation_24.vy += FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
        }
        else
        {
            nurse->rotation_24.vy -= FP_MULTIPLY_PRECISE(g_DeltaTime0, FP_ANGLE(90.0f), Q12_SHIFT);
        }
    }
}
