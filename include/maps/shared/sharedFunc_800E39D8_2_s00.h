void sharedFunc_800E39D8_2_s00(s_SubCharacter* groaner)
{
    q3_12  unkAngleDelta;
    q19_12 targetPosX;
    q19_12 targetPosZ;
    q19_12 unkRand;
    q19_12 randTargetPosX;
    q19_12 posX;
    q19_12 posZ;

    #define groanerProps groaner->properties_E4.groaner

    Chara_MoveSpeedUpdate4(groaner, Q12(6.0f), Q12_MULT_PRECISE(groanerProps.field_114, Q12(0.5f)));

    if (groanerProps.flags_E8.val16[0] & GroanerFlag_0)
    {
        unkAngleDelta = func_8005BF38(groanerProps.angle_FC - groaner->rotation_24.vy);
        if (TIMESTEP_ANGLE_5 < ABS(unkAngleDelta))
        {
            if (unkAngleDelta > FP_ANGLE(0.0f))
            {
                groaner->rotation_24.vy += Q12_MULT_PRECISE(g_DeltaTime0, FP_ANGLE(60.0f));
            }
            else
            {
                groaner->rotation_24.vy -= Q12_MULT_PRECISE(g_DeltaTime0, FP_ANGLE(60.0f));
            }
        }
        else
        {
            groaner->rotation_24.vy = groanerProps.angle_FC;
            groanerProps.flags_E8.val16[0] &= ~GroanerFlag_0;
        }
    }
    else
    {
        if (func_8007029C(groaner, FP_ANGLE(306.0f), groaner->rotation_24.vy))
        {
            groanerProps.angle_FC = func_8006F99C(groaner, FP_ANGLE(306.0f), groaner->rotation_24.vy);
            if (groanerProps.angle_FC == FP_ANGLE(360.0f))
            {
                groanerProps.angle_FC = -groaner->rotation_24.vy;
            }

            groanerProps.flags_E8.val16[0] |= GroanerFlag_0;
        }
        else
        {
            unkRand = Rng_GenerateInt(Q12(2.0f), Q12(6.0f) - 1);

            posX       = groaner->position_18.vx;
            targetPosX = groanerProps.targetPositionX_F4;
            posZ       = groaner->position_18.vz;
            targetPosZ = groanerProps.targetPositionZ_F8;

            // TODO: Demangle condition.
            if (unkRand < (((posX - targetPosX) > (posZ - targetPosZ)) ? ABS(posX - targetPosX) + ABS((posZ - targetPosZ) >> 1) :
                                                                         ABS((posX - targetPosX) >> 1) + ABS(posZ - targetPosZ)))
            {
                // TODO: Cleaner random angle generation.
                if (ABS(func_8005BF38(groaner->rotation_24.vy - ratan2(groaner->position_18.vx - groanerProps.targetPositionX_F4,
                                                                       groaner->position_18.vz - groanerProps.targetPositionZ_F8))) < (Rng_TestProbabilityBits(6) + FP_ANGLE(45.0f)))
                {
                    randTargetPosX        = groanerProps.targetPositionX_F4 + Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1);
                    groanerProps.angle_FC = Chara_HeadingAngleGet(groaner, FP_ANGLE(306.0f),
                                                                  randTargetPosX, groanerProps.targetPositionZ_F8 + Rng_GenerateInt(Q12(-0.5f), Q12(0.5f) - 1),
                                                                  FP_ANGLE(360.0f), true);
                    if (groanerProps.angle_FC == FP_ANGLE(360.0f))
                    {
                        groanerProps.angle_FC = -groaner->rotation_24.vy;
                    }

                    groanerProps.flags_E8.val16[0] |= GroanerFlag_0;
                }
            }
        }
    }

    if (groaner->model_0.anim_4.status_0 == ANIM_STATUS(GroanerAnim_17, true) &&
        (groanerProps.flags_E8.val32 & (GroanerFlag_5 | GroanerFlag_7)) == (GroanerFlag_5 | GroanerFlag_7))
    {
        groaner->model_0.controlState_2 = GroanerControl_2;
        groaner->model_0.anim_4.status_0 = ANIM_STATUS(GroanerAnim_16, false);
        groanerProps.flags_E8.val16[0] &= ~GroanerFlag_0;
        groanerProps.flags_E8.val16[0] |= GroanerFlag_10;
    }

    #undef groanerProps
}
