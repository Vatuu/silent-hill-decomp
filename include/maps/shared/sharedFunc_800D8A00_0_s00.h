// Seems like this function is intended to be called repeatedly, swapping between states
// Might be called many times in a single logic update, or over multiple updates
bool sharedFunc_800D8A00_0_s00(s_SubCharacter* chara, s32 arg1, VECTOR3* arg2In, s32 angleIn, s32 arg4)
{
    s16 shortestAngle;
    s32 angleIncr;

    VECTOR3* arg2;
    
    s32 tmpIdx;
    s32 tmpRot;
    s16 tmpAngle;
    s32 tmpDistance;

    // Angle threshold check: 360 / 64 = 5.625 degrees
    #define ANGLE_THRESHOLD (FP_ANGLE(360.0) >> 6)

    // Yet another way to wrap & clamp angles to +ve
    #define ABS_ANGLE(x) (((x) + FP_ANGLE(360.0f)) & 0xfff)
    
    #define FP_VECTOR3_XZ_DIST(vec1, vec2) \
        (SquareRoot0((((vec2).vx - (vec1).vx) >> 4) * (((vec2).vx - (vec1).vx) >> 4) + ((((vec2).vz - (vec1).vz) >> 4) * (((vec2).vz - (vec1).vz) >> 4))))
    
    #define FP_VECTOR3_XZ_DIST_SQRD(vec1, vec2) \
        ((((vec2).vx - (vec1).vx) >> 4) * (((vec2).vx - (vec1).vx) >> 4) + ((((vec2).vz - (vec1).vz) >> 4) * (((vec2).vz - (vec1).vz) >> 4)))

    // Clean up the incoming angle
    angleIn = ABS_ANGLE(angleIn);

    arg2 = arg2In;

    // All this data is hard to keep track of, and may not point to the right properties_E4 struct
    // so here are some short-hand defines to make it easier to follow
    #define CHARA_STATE_3 chara->model_0.stateStep_3
    #define CHARA_STATE_E8 chara->properties_E4.larvalStalker.properties_E8[0].val32
    #define CHARA_STATE_EC chara->properties_E4.larvalStalker.properties_E8[1].val32
    #define CHARA_STATE_F4 chara->properties_E4.larvalStalker.properties_E8[3].val32
    #define CHARA_STATE_FC chara->properties_E4.larvalStalker.properties_E8[5].val32
    
    switch (CHARA_STATE_EC)
    {
        case 0:
            sharedData_800DF1F8_0_s00 = 0;
            CHARA_STATE_EC = 1U;
            break;
        
        case 1:
            if (arg2[0].vx == chara->position_18.vx && arg2[0].vz == chara->position_18.vz)
            {
                CHARA_STATE_EC = 6U;
            }
            else
            {
                tmpAngle = ABS_ANGLE(ratan2(arg2[0].vx - chara->position_18.vx, arg2[0].vz - chara->position_18.vz));
                tmpRot = chara->rotation_24.vy;
                sharedData_800DF1FA_0_s00 = tmpAngle;
                Math_ShortestAngleGet(tmpRot, tmpAngle, &shortestAngle);
                
                if (ABS(shortestAngle) < ANGLE_THRESHOLD)
                {
                    chara->rotation_24.vy = sharedData_800DF1FA_0_s00;
                    CHARA_STATE_EC = 3U;
                }
                else
                {
                    if (shortestAngle < 0)
                    {
                        CHARA_STATE_FC = 4;
                        CHARA_STATE_E8 = 4;
                        CHARA_STATE_3 = 0;
                    }
                    else
                    {
                        CHARA_STATE_FC = 3;
                        CHARA_STATE_E8 = 3;
                        CHARA_STATE_3 = 0;
                    }
                    CHARA_STATE_EC = 2U;
                }
            }
            break;
        
        case 2:
            Math_ShortestAngleGet(chara->rotation_24.vy, sharedData_800DF1FA_0_s00, &shortestAngle);
            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                chara->rotation_24.vy = sharedData_800DF1FA_0_s00;
                CHARA_STATE_EC = 3U;
            }
            break;
        
        case 3:
            tmpDistance = FP_VECTOR3_XZ_DIST_SQRD(arg2[0], chara->position_18);
            tmpDistance = SquareRoot0(tmpDistance);
            // There's no reason for an ABS, it'll always be +ve
            if (FP_METER(0.00925) >= ABS(tmpDistance))
            {
                CHARA_STATE_E8 = 0;
                CHARA_STATE_3 = 0;
                CHARA_STATE_EC = 8U;
            }
            else
            {
                CHARA_STATE_E8 = arg1;
                CHARA_STATE_3 = 0;
                CHARA_STATE_FC = arg1;
                CHARA_STATE_EC = 4U;
            }
            break;
        
        case 4:
            // Some awkward interleaving
            tmpAngle = ratan2(arg2[sharedData_800DF1F8_0_s00].vx - chara->position_18.vx, arg2[sharedData_800DF1F8_0_s00].vz - chara->position_18.vz);
            tmpDistance = FP_VECTOR3_XZ_DIST_SQRD(arg2[sharedData_800DF1F8_0_s00], chara->position_18);
            sharedData_800DF1FA_0_s00 = ABS_ANGLE(tmpAngle);
            sharedData_800DF1F4_0_s00 = SquareRoot0(tmpDistance);

            CHARA_STATE_EC = 5U;
            break;
            
        case 5:
            // Test against the next vector3 in the list, unless we've hit the last one
            if (sharedData_800DF1F8_0_s00 + 1 < arg4)
            {
                sharedData_800DF1FA_0_s00 = ratan2(arg2[sharedData_800DF1F8_0_s00 + 1].vx - chara->position_18.vx, arg2[sharedData_800DF1F8_0_s00 + 1].vz - chara->position_18.vz);
            }
            else
            {
                sharedData_800DF1FA_0_s00 = ratan2(arg2[sharedData_800DF1F8_0_s00].vx - chara->position_18.vx, arg2[sharedData_800DF1F8_0_s00].vz - chara->position_18.vz);
            }

            tmpRot = chara->rotation_24.vy;
            sharedData_800DF1FA_0_s00 = ABS_ANGLE(sharedData_800DF1FA_0_s00);

            Math_ShortestAngleGet(tmpRot, sharedData_800DF1FA_0_s00, &shortestAngle);

            angleIncr = (g_DeltaTime0 << (shortestAngle < FP_ANGLE(45.0) ? 5 : 8)) / 136; // Turn towards it
            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                chara->rotation_24.vy = sharedData_800DF1FA_0_s00;
            }
            else
            {
                if (shortestAngle < 0)
                {
                    chara->rotation_24.vy -= angleIncr;
                }
                else
                {
                    chara->rotation_24.vy += angleIncr;
                }
            }

            chara->rotation_24.vy = ABS_ANGLE(chara->rotation_24.vy);
            tmpIdx = sharedData_800DF1F8_0_s00;

            tmpDistance = FP_VECTOR3_XZ_DIST(arg2[tmpIdx], chara->position_18);

            // This should be (arg1 * FP_METER(0.15)) but the compiler splits out one of the distances for some reason
            if (tmpDistance < (((arg1 - 1) * FP_METER(0.15)) + FP_METER(0.15)) >> 4 ||
                (sharedData_800DF1F4_0_s00 < tmpDistance && sharedData_800DF1F8_0_s00 != arg4 - 1))
            {
                sharedData_800DF1F8_0_s00++;
                tmpDistance = FP_VECTOR3_XZ_DIST(arg2[sharedData_800DF1F8_0_s00], chara->position_18);

                if (sharedData_800DF1F8_0_s00 == arg4)
                {
                    CHARA_STATE_EC = 6;
                }
                else
                {
                    CHARA_STATE_EC = 4;
                }
            }
            
            sharedData_800DF1F4_0_s00 = tmpDistance;
            break;
        
        case 6:
            Math_ShortestAngleGet(chara->rotation_24.vy, angleIn, &shortestAngle);
            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                chara->rotation_24.vy = angleIn;
                CHARA_STATE_EC = 8U;
            }
            else
            {
                if (shortestAngle < 0)
                {
                    CHARA_STATE_FC = 4;
                    CHARA_STATE_E8 = 4;
                    CHARA_STATE_3 = 0;
                }
                else
                {
                    CHARA_STATE_FC = 3;
                    CHARA_STATE_E8 = 3;
                    CHARA_STATE_3 = 0;
                }
                CHARA_STATE_EC = 7U;
            }
            break;
        
        case 7:
            Math_ShortestAngleGet(chara->rotation_24.vy, angleIn, &shortestAngle);
            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                CHARA_STATE_FC = arg1 - 1;
                chara->rotation_24.vy = angleIn;
                CHARA_STATE_E8 = 0;
                CHARA_STATE_3 = 0;
                CHARA_STATE_EC = 8U;
            }
            break;
        
        case 8:
            CHARA_STATE_F4 = 1;
            sharedData_800DF1FA_0_s00 = 0;
            CHARA_STATE_EC = 0;
            chara->properties_E4.npc.field_124 = NULL;
            return true;
    }
    return false;
}
