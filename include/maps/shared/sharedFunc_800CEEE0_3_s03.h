void sharedFunc_800CEEE0_3_s03(s_SubCharacter* nurse)
{
    s32 limit;
    s16 angle;
    s_SubCharacter* nurseCpy;

    limit = Q12_MULT_PRECISE(nurse->properties_E4.npc.field_124->field_C, Q12(0.27f));
    nurseCpy = nurse;
    Chara_MoveSpeedUpdate2(nurse, Q12(1.4f), limit);
    limit =0;

    if (Rng_GenerateUInt(0, 63) == 0) // 1 in 64 chance.
    {
        nurseCpy->properties_E4.puppetNurse.field_11C = func_8006F99C(nurse, Q12_ANGLE(360.0f), nurse->rotation_24.vy);
    }
    angle = func_8005BF38(nurseCpy->properties_E4.puppetNurse.field_11C - nurse->rotation_24.vy);
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
