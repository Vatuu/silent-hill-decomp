// Seems like this function is intended to be called repeatedly, swapping between states
// Might be called many times in a single logic update, or over multiple updates
bool sharedFunc_800D8A00_0_s00(s_SubCharacter* chara, s32 arg1, VECTOR3* arg2In, s32 angleIn, s32 arg4)
{
    #define ANGLE_THRESHOLD (FP_ANGLE(360.0) >> 6) // 360 / 64 = 5.625 degrees.

    q7_8     shortestAngle;
    s32      angleStep;
    s32      tmpIdx;
    s32      rotY;
    s16      tmpAngle;
    s32      dist;
    VECTOR3* arg2; // Q19.12

    // TODO: This data is hard to keep track of and may not point to the right `properties_E4` struct.
    // Short-hand defines to make it easier to follow.
    #define charaState3  chara->model_0.stateStep_3
    #define charaStateE8 chara->properties_E4.larvalStalker.properties_E8[0].val32
    #define charaStateEC chara->properties_E4.larvalStalker.properties_E8[1].val32
    #define charaStateF4 chara->properties_E4.larvalStalker.properties_E8[3].val32
    #define charaStateFC chara->properties_E4.larvalStalker.properties_E8[5].val32

    angleIn = FP_ANGLE_ABS(angleIn);
    arg2 = arg2In;

    switch (charaStateEC)
    {
        case 0:
            sharedData_800DF1F8_0_s00 = 0;
            charaStateEC = 1;
            break;
        
        case 1:
            if (arg2[0].vx == chara->position_18.vx && arg2[0].vz == chara->position_18.vz)
            {
                charaStateEC = 6;
            }
            else
            {
                tmpAngle = FP_ANGLE_ABS(ratan2(arg2[0].vx - chara->position_18.vx, arg2[0].vz - chara->position_18.vz));
                rotY = chara->rotation_24.vy;
                sharedData_800DF1FA_0_s00 = tmpAngle;
                Math_ShortestAngleGet(rotY, tmpAngle, &shortestAngle);
                
                if (ABS(shortestAngle) < ANGLE_THRESHOLD)
                {
                    chara->rotation_24.vy = sharedData_800DF1FA_0_s00;
                    charaStateEC = 3;
                }
                else
                {
                    if (shortestAngle < FP_ANGLE(0.0f))
                    {
                        charaStateFC = 4;
                        charaStateE8 = 4;
                        charaState3 = 0;
                    }
                    else
                    {
                        charaStateFC = 3;
                        charaStateE8 = 3;
                        charaState3 = 0;
                    }

                    charaStateEC = 2;
                }
            }
            break;
        
        case 2:
            Math_ShortestAngleGet(chara->rotation_24.vy, sharedData_800DF1FA_0_s00, &shortestAngle);
            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                chara->rotation_24.vy = sharedData_800DF1FA_0_s00;
                charaStateEC = 3;
            }
            break;
        
        case 3:
            dist = FP_2D_DISTANCE_SQR(arg2[0], chara->position_18);
            dist = SquareRoot0(dist);

            if (Q12(0.00925f) >= ABS(dist))
            {
                charaStateE8 = 0;
                charaState3 = 0;
                charaStateEC = 8;
            }
            else
            {
                charaStateE8 = arg1;
                charaState3 = 0;
                charaStateFC = arg1;
                charaStateEC = 4;
            }
            break;
        
        case 4:
            // Awkward interleaving.
            tmpAngle = ratan2(arg2[sharedData_800DF1F8_0_s00].vx - chara->position_18.vx, arg2[sharedData_800DF1F8_0_s00].vz - chara->position_18.vz);
            dist = FP_2D_DISTANCE_SQR(arg2[sharedData_800DF1F8_0_s00], chara->position_18);
            sharedData_800DF1FA_0_s00 = FP_ANGLE_ABS(tmpAngle);
            sharedData_800DF1F4_0_s00 = SquareRoot0(dist);

            charaStateEC = 5;
            break;
            
        case 5:
            // Test against next `VECTOR3` unless last one has been reached.
            if ((sharedData_800DF1F8_0_s00 + 1) < arg4)
            {
                sharedData_800DF1FA_0_s00 = ratan2(arg2[sharedData_800DF1F8_0_s00 + 1].vx - chara->position_18.vx,
                                                   arg2[sharedData_800DF1F8_0_s00 + 1].vz - chara->position_18.vz);
            }
            else
            {
                sharedData_800DF1FA_0_s00 = ratan2(arg2[sharedData_800DF1F8_0_s00].vx - chara->position_18.vx,
                                                   arg2[sharedData_800DF1F8_0_s00].vz - chara->position_18.vz);
            }

            rotY = chara->rotation_24.vy;
            sharedData_800DF1FA_0_s00 = FP_ANGLE_ABS(sharedData_800DF1FA_0_s00);

            Math_ShortestAngleGet(rotY, sharedData_800DF1FA_0_s00, &shortestAngle);

            // Turn toward.
            angleStep = TIMESTEP_SCALE(g_DeltaTime0, (shortestAngle < FP_ANGLE(45.0f)) ? FP_ANGLE(2.9f) : FP_ANGLE(22.5f));

            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                chara->rotation_24.vy = sharedData_800DF1FA_0_s00;
            }
            else
            {
                if (shortestAngle < FP_ANGLE(0.0f))
                {
                    chara->rotation_24.vy -= angleStep;
                }
                else
                {
                    chara->rotation_24.vy += angleStep;
                }
            }

            chara->rotation_24.vy = FP_ANGLE_ABS(chara->rotation_24.vy);
            tmpIdx = sharedData_800DF1F8_0_s00;

            dist = SquareRoot0(FP_2D_DISTANCE_SQR(arg2[tmpIdx], chara->position_18));

            // TODO: Should be `arg1 * Q12(0.15f)`, but compiler splits out one distance for some reason.
            if (dist < (((arg1 - 1) * Q12(0.15f)) + Q12(0.15f)) >> 4 ||
                (sharedData_800DF1F4_0_s00 < dist && sharedData_800DF1F8_0_s00 != arg4 - 1))
            {
                sharedData_800DF1F8_0_s00++;
                dist = SquareRoot0(FP_2D_DISTANCE_SQR(arg2[sharedData_800DF1F8_0_s00], chara->position_18));

                if (sharedData_800DF1F8_0_s00 == arg4)
                {
                    charaStateEC = 6;
                }
                else
                {
                    charaStateEC = 4;
                }
            }
            
            sharedData_800DF1F4_0_s00 = dist;
            break;
        
        case 6:
            Math_ShortestAngleGet(chara->rotation_24.vy, angleIn, &shortestAngle);
            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                chara->rotation_24.vy = angleIn;
                charaStateEC = 8;
            }
            else
            {
                if (shortestAngle < FP_ANGLE(0.0f))
                {
                    charaStateFC = 4;
                    charaStateE8 = 4;
                    charaState3 = 0;
                }
                else
                {
                    charaStateFC = 3;
                    charaStateE8 = 3;
                    charaState3 = 0;
                }

                charaStateEC = 7;
            }
            break;
        
        case 7:
            Math_ShortestAngleGet(chara->rotation_24.vy, angleIn, &shortestAngle);
            if (ABS(shortestAngle) < ANGLE_THRESHOLD)
            {
                charaStateFC = arg1 - 1;
                chara->rotation_24.vy = angleIn;
                charaStateE8 = 0;
                charaState3 = 0;
                charaStateEC = 8;
            }
            break;
        
        case 8:
            charaStateF4 = 1;
            sharedData_800DF1FA_0_s00 = 0;
            charaStateEC = 0;
            chara->properties_E4.npc.field_124 = NULL;
            return true;
    }

    return false;
}
