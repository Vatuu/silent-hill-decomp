#if defined(MAP7_S03)
// TODO: Move to map .c / .h
extern s32 D_800F23D4;
#endif

void sharedFunc_800CB6B0_0_s00(s32 arg1, s32 arg2, s32 arg3)
{
    s32 temp_a2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_v0;
    s32 i;
    s32 var_v0;
    s32 var_v0_3;
    u32 temp_t0;
    u32 temp_v1_2;
    u16 temp_v1_3;

#if defined(MAP5_S01)
    if (g_MapEventIdx == 7 && g_SysWork.sysStateStep_C[0] == 8)
    {
        return;
    }
#endif

#if defined(MAP0_S00) || defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP4_S02) || \
    defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || defined(MAP5_S00) || \
    defined(MAP6_S00) || defined(MAP6_S03)
    sharedFunc_800D0CB8_0_s00();
#endif

    func_80055434(&g_ParticleVectors0.vector_0);
    g_ParticleVectors0.field_28 = func_8005545C(&g_ParticleVectors0.svec_18);

    vwGetViewPosition(&g_ParticleVectors0.viewPosition_C);
    vwGetViewAngle(&g_ParticleVectors0.viewRotation_20);

#if defined(MAP5_S01)
    sharedData_800DFB64_0_s00 = 0;
#endif

    switch (arg3)
    {
        case 0:
        case -1:

            // TODO: `sharedData_800E326C_0_s00` should be changed to same type as `sharedData_800E5768_1_s02`?
            // (may also need to rename them to same symbol name, not completely sure yet though)
#if defined(MAP0_S00)
            sharedData_800DD591_0_s00 = 1;
            
            sharedData_800E326C_0_s00.vector_0.vx = Q12(-5.0f);
            sharedData_800E326C_0_s00.vector_0.vy = Q12(-4.5f);
            sharedData_800E326C_0_s00.vector_0.vz = Q12(211.0f);
            
            sharedData_800E326C_0_s00.vector_C.vx = Q12(15.0f);
            sharedData_800E326C_0_s00.vector_C.vy = Q12(-4.5f);
            sharedData_800E326C_0_s00.vector_C.vz = Q12(211.0f);
#elif defined(MAP0_S01)
            sharedData_800DD591_0_s00 = 1;
            
            sharedData_800E326C_0_s00.vector_0.vx = Q12(-0.30f);
            sharedData_800E326C_0_s00.vector_0.vz = Q12(275.0f);
            sharedData_800E326C_0_s00.vector_C.vx = Q12(-0.30f);
            sharedData_800E326C_0_s00.vector_C.vz = Q12(265.0f);
#elif defined(MAP1_S06)
            switch (g_SavegamePtr->mapRoomIdx_A5)
            {
                case 12:
                    sharedData_800DD591_0_s00             = 1;
                    sharedData_800E326C_0_s00.vector_0.vx = Q12(105.5f);
                    sharedData_800E326C_0_s00.vector_0.vz = Q12(67.0f);
                    sharedData_800E326C_0_s00.vector_C.vx = Q12(105.5f);
                    sharedData_800E326C_0_s00.vector_C.vz = Q12(50.0f);
                    break;
                case 13:
                    sharedData_800DD591_0_s00             = 1;
                    sharedData_800E326C_0_s00.vector_0.vx = Q12(145.0f);
                    sharedData_800E326C_0_s00.vector_0.vz = Q12(24.0f);
                    sharedData_800E326C_0_s00.vector_C.vx = Q12(132.0f);
                    sharedData_800E326C_0_s00.vector_C.vz = Q12(24.0f);
                    break;
                case 9:
                    sharedData_800DD591_0_s00             = 1;
                    sharedData_800E326C_0_s00.vector_0.vx = Q12(55.0f);
                    sharedData_800E326C_0_s00.vector_0.vz = Q12(137.0f);
                    sharedData_800E326C_0_s00.vector_C.vx = Q12(62.0f);
                    sharedData_800E326C_0_s00.vector_C.vz = Q12(137.0f);
                    break;
                case 14:
                    sharedData_800DD591_0_s00             = 2;
                    sharedData_800E326C_0_s00.vector_0.vx = Q12(96.5f);
                    sharedData_800E326C_0_s00.vector_0.vz = Q12(15.0f);
                    sharedData_800E326C_0_s00.vector_C.vx = Q12(103.5f);
                    sharedData_800E326C_0_s00.vector_C.vz = Q12(15.0f);
                    break;
            }
#elif defined(MAP2_S00)
            switch (g_SavegamePtr->mapRoomIdx_A5)
            {
                case 38:
                    sharedData_800DD591_0_s00                 = 10;
                    sharedData_800E5768_1_s02.corners_0[0].vx = Q12(120.0f);
                    sharedData_800E5768_1_s02.corners_0[0].vz = Q12(303.5f);
                    sharedData_800E5768_1_s02.corners_0[1].vx = Q12(110.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vz = Q12(303.5f);
                    sharedData_800E5768_1_s02.corners_0[2].vx = Q12(128.3f);
                    sharedData_800E5768_1_s02.corners_0[2].vz = Q12(295.0f);
                    sharedData_800E5768_1_s02.corners_0[3].vx = Q12(128.3f);
                    sharedData_800E5768_1_s02.corners_0[3].vz = Q12(305.0f);
                    sharedData_800E5768_1_s02.corners_0[4].vx = Q12(111.3f);
                    sharedData_800E5768_1_s02.corners_0[4].vz = Q12(298.0f);
                    sharedData_800E5768_1_s02.corners_0[5].vx = Q12(111.3f);
                    sharedData_800E5768_1_s02.corners_0[5].vz = Q12(295.0f);
                    break;

                case 23:
                    sharedData_800DD591_0_s00                 = 1;
                    sharedData_800E5768_1_s02.corners_0[0].vx = Q12(-186.0f);
                    sharedData_800E5768_1_s02.corners_0[0].vz = Q12(301.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vx = Q12(-188.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vz = Q12(301.0f);
                    break;

                case 37:
                    sharedData_800DD591_0_s00                 = 9;
                    sharedData_800E5768_1_s02.corners_0[0].vx = Q12(121.0f);
                    sharedData_800E5768_1_s02.corners_0[0].vz = Q12(223.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vx = Q12(114.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vz = Q12(223.0f);
                    sharedData_800E5768_1_s02.corners_0[2].vx = Q12(128.3f);
                    sharedData_800E5768_1_s02.corners_0[2].vz = Q12(215.0f);
                    sharedData_800E5768_1_s02.corners_0[3].vx = Q12(128.3f);
                    sharedData_800E5768_1_s02.corners_0[3].vz = Q12(220.0f);
                    break;

                case 40:
                    sharedData_800DD591_0_s00                 = 11;
                    sharedData_800E5768_1_s02.corners_0[0].vx = Q12(-48.0f);
                    sharedData_800E5768_1_s02.corners_0[0].vz = Q12(349.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vx = Q12(-48.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vz = Q12(343.0f);
                    sharedData_800E5768_1_s02.corners_0[2].vx = Q12(-39.0f);
                    sharedData_800E5768_1_s02.corners_0[2].vz = Q12(343.0f);
                    sharedData_800E5768_1_s02.corners_0[3].vx = Q12(-39.0f);
                    sharedData_800E5768_1_s02.corners_0[3].vz = Q12(349.0f);
                    sharedData_800E5768_1_s02.corners_0[4].vx = Q12(-39.0f);
                    sharedData_800E5768_1_s02.corners_0[4].vz = Q12(349.0f);
                    sharedData_800E5768_1_s02.corners_0[5].vx = Q12(-48.0f);
                    sharedData_800E5768_1_s02.corners_0[5].vz = Q12(349.0f);
                    sharedData_800E5768_1_s02.corners_0[6].vx = Q12(-48.0f);
                    sharedData_800E5768_1_s02.corners_0[6].vz = Q12(343.0f);
                    sharedData_800E5768_1_s02.corners_0[7].vx = Q12(-39.0f);
                    sharedData_800E5768_1_s02.corners_0[7].vz = Q12(343.0f);
                    break;

                default:
                    sharedData_800DD591_0_s00 = 0;
                    break;
            }
#elif defined(MAP2_S02)
            sharedData_800DD591_0_s00                 = 0;
            sharedData_800E5768_1_s02.corners_0[0].vx = Q12(-31.0f);
            sharedData_800E5768_1_s02.corners_0[0].vz = Q12(-8.0f);
            sharedData_800E5768_1_s02.corners_0[1].vx = Q12(-31.0f);
            sharedData_800E5768_1_s02.corners_0[1].vz = Q12(-11.0f);
            sharedData_800E5768_1_s02.corners_0[2].vx = Q12(-25.5f);
            sharedData_800E5768_1_s02.corners_0[2].vz = Q12(-8.0f);
            sharedData_800E5768_1_s02.corners_0[3].vx = Q12(-31.0f);
            sharedData_800E5768_1_s02.corners_0[3].vz = Q12(-8.0f);
            sharedData_800E5768_1_s02.corners_0[4].vx = Q12(-25.5f);
            sharedData_800E5768_1_s02.corners_0[4].vz = Q12(-11.0f);
            sharedData_800E5768_1_s02.corners_0[5].vx = Q12(-25.5f);
            sharedData_800E5768_1_s02.corners_0[5].vz = Q12(-8.0f);
#elif defined(MAP3_S00) || defined(MAP3_S01) || defined(MAP3_S06)
            switch (g_SavegamePtr->mapRoomIdx_A5)
            {
                case 3:
                    sharedData_800DD591_0_s00                 = 2;
                    sharedData_800E5768_1_s02.corners_0[0].vx = Q12(101.5f);
                    sharedData_800E5768_1_s02.corners_0[0].vz = Q12(100.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vx = Q12(101.5f);
                    sharedData_800E5768_1_s02.corners_0[1].vz = Q12(105.0f);
                    break;
                case 5:
                    sharedData_800DD591_0_s00                 = 1;
                    sharedData_800E5768_1_s02.corners_0[0].vx = Q12(17.7f);
                    sharedData_800E5768_1_s02.corners_0[0].vz = Q12(30.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vx = Q12(17.7f);
                    sharedData_800E5768_1_s02.corners_0[1].vz = Q12(17.0f);
                    sharedData_800E5768_1_s02.corners_0[2].vx = Q12(17.5f);
                    sharedData_800E5768_1_s02.corners_0[2].vz = Q12(15.0f);
                    sharedData_800E5768_1_s02.corners_0[3].vx = Q12(15.0f);
                    sharedData_800E5768_1_s02.corners_0[3].vz = Q12(15.0f);
                    break;
                case 8:
                    sharedData_800DD591_0_s00                 = 2;
                    sharedData_800E5768_1_s02.corners_0[0].vx = Q12(63.5f);
                    sharedData_800E5768_1_s02.corners_0[0].vz = Q12(57.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vx = Q12(63.5f);
                    sharedData_800E5768_1_s02.corners_0[1].vz = Q12(63.0f);
                    break;
                case 9:
                    sharedData_800DD591_0_s00                 = 2;
                    sharedData_800E5768_1_s02.corners_0[0].vx = Q12(104.0f);
                    sharedData_800E5768_1_s02.corners_0[0].vz = Q12(56.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vx = Q12(104.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vz = Q12(61.5f);
                    break;
                case 11:
                    sharedData_800DD591_0_s00                 = 2;
                    sharedData_800E5768_1_s02.corners_0[0].vx = Q12(143.8f);
                    sharedData_800E5768_1_s02.corners_0[0].vz = Q12(18.0f);
                    sharedData_800E5768_1_s02.corners_0[1].vx = Q12(143.8f);
                    sharedData_800E5768_1_s02.corners_0[1].vz = Q12(22.0f);
                    break;
                default:
                    sharedData_800DD591_0_s00 = 0;
                    break;
            }
#elif defined(MAP4_S03)
            if (g_SavegamePtr->mapRoomIdx_A5 == 20)
            {
                sharedData_800DD591_0_s00                 = 1;
                sharedData_800E5768_1_s02.corners_0[0].vx = Q12(133.0f);
                sharedData_800E5768_1_s02.corners_0[0].vz = Q12(130.0f);
                sharedData_800E5768_1_s02.corners_0[1].vx = Q12(133.0f);
                sharedData_800E5768_1_s02.corners_0[1].vz = Q12(150.0f);
            }
#elif defined(MAP5_S03)
            sharedData_800DD591_0_s00 = 2;
#endif

#if defined(MAP0_S00) || defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP4_S02) || \
    defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || defined(MAP6_S00)
            sharedData_800E32D4_0_s00 = 30;
    #if defined(MAP0_S00) || defined(MAP6_S00)
                sharedData_800DD592_0_s00 = 1;
    #endif
#elif defined(MAP5_S00) || defined(MAP6_S03)
            sharedData_800E32D4_0_s00 = 3; // @hack Mis-share? Is this meant to be `sharedData_800DD591_0_s00`?
#else
            sharedData_800DD592_0_s00 = 1;
#endif

            if (arg3 == NO_VALUE)
            {
                g_SysWork.field_2349 = g_MapOverlayHeader.field_17;
                g_SysWork.field_2348 = g_MapOverlayHeader.field_17;
            }

            sharedData_800DD598_0_s00 = 0;
#if defined(MAP7_S03)
            D_800F23D4 = 0;
#endif
            sharedData_800E324C_0_s00.vz = 0;
            sharedData_800E324C_0_s00.vx = 0;

            g_SysWork.field_234A = 1;
            sharedData_800DFB4C_0_s00 = arg2;

            sharedData_800E0CB8_0_s00 = FP_FROM(sharedData_800E0CB0_0_s00, Q12_SHIFT);
            sharedData_800E0CB6_0_s00 = sharedData_800E0CB0_0_s00;
            sharedData_800E0CB4_0_s00 = sharedData_800E0CB0_0_s00;

            temp_s0 = SetSp(0x1F8003D8);

            sharedFunc_800CBC94_0_s00(&sharedData_800E0CBC_0_s00);
#if defined(MAP0_S00)
            func_800CBFB0(&sharedData_800E34FC_0_s00, &sharedData_800E330C_0_s00, sharedData_800DFB4C_0_s00);
#endif
            SetSp(temp_s0);
            break;

        default:
#if defined(MAP7_S03)
            sharedData_800DD584_0_s00 = 0;
            D_800F23D4               += g_DeltaTime0;
#else
            sharedData_800DD584_0_s00 = g_DeltaTime0 == Q12(0.0f);
#endif

            func_8003EDB8(&sharedData_800E3258_0_s00, &sharedData_800E325C_0_s00);

            if (sharedData_800E0CB6_0_s00 != sharedData_800E0CB4_0_s00)
            {
                if (sharedData_800DD584_0_s00 == 0)
                {
                    sharedData_800DD598_0_s00++;
                }

                temp_s0_2 = FP_MULTIPLY(Math_Sin(FP_ANGLE(270.0f) + (sharedData_800DD598_0_s00 * 2)), (PARTICLE_COUNT_MAX / 2), Q12_SHIFT) + (PARTICLE_COUNT_MAX / 2);
                temp_a2   = FP_MULTIPLY(Math_Sin(FP_ANGLE(180.0f) + (sharedData_800DD598_0_s00 * 2)), (PARTICLE_COUNT_MAX / 2), Q12_SHIFT) + (PARTICLE_COUNT_MAX / 2);
                temp_t0 = sharedData_800E0CB6_0_s00 >> 14;
               
                for (i = 0; i < 2; i++)
                {
                    temp_v1_2 = (sharedData_800E0CB4_0_s00 >> ((1 - i) * 6)) & 0x3F;
                    temp_v1_3 = (sharedData_800E0CB4_0_s00 >> 6) & 0x3F;
                    temp_v0 = temp_v1_3;

                    switch (temp_v1_2)
                    {
                        case 4:
                        case 6:
                            sharedData_800DD588_0_s00[i] = temp_s0_2;
                            break;

                        case 5:
                        case 7:
                            var_v0 = temp_s0_2 * 2;
                            sharedData_800DD588_0_s00[i] = var_v0;
                            break;

                        case 32:
                        case 48:
                            sharedData_800DD588_0_s00[i] = temp_a2;
                            break;

                        case 37:
                        case 39:
                        case 53:
                        case 55:
                            var_v0                       = temp_s0_2 + (PARTICLE_COUNT_MAX / 2);
                            sharedData_800DD588_0_s00[i] = var_v0;
                            break;

                        case 40:
                        case 56:
                            var_v0 = temp_a2 * 2;
                            sharedData_800DD588_0_s00[i] = var_v0;
                            break;

                        case 44:
                        case 46:
                        case 60:
                        case 62:
                            var_v0                       = temp_a2 + (PARTICLE_COUNT_MAX / 2);
                            sharedData_800DD588_0_s00[i] = var_v0;
                            break;

                        case 0:
                            sharedData_800DD588_0_s00[i] = 0;
                            break;

                        case 36:
                        case 38:
                        case 52:
                        case 54:
                            var_v0                       = (PARTICLE_COUNT_MAX / 2);
                            sharedData_800DD588_0_s00[i] = var_v0;
                            break;

                        case 45:
                        case 47:
                        case 61:
                        case 63:
                            var_v0                       = PARTICLE_COUNT_MAX;
                            sharedData_800DD588_0_s00[i] = var_v0;
                            break;
                    }

#if !defined(MAP1_S02) && !defined(MAP1_S03) && !defined(MAP4_S02) && !defined(MAP4_S03) && \
    !defined(MAP4_S04) && !defined(MAP4_S05) && !defined(MAP5_S00) && !defined(MAP6_S03)
                    if (i == 0)
                    {
                        if (temp_t0 < 2)
                        {
                            if (temp_t0 != 1 || (sharedData_800E0CB4_0_s00 >> 14) < 2)
                            {
                                sharedData_800DD592_0_s00 = 1;
                                continue;
                            }
                        }

                        switch (temp_v0)
                        {
                            case 4:
                            case 6:
                            case 32:
                            case 48:
                                var_v0_3                  = sharedData_800DD588_0_s00[i] < ((PARTICLE_COUNT_MAX / 4) + 1);
                                sharedData_800DD592_0_s00 = var_v0_3 ^ 1;
                                break;

                            case 5:
                            case 7:
                            case 40:
                            case 56:
                                var_v0_3                  = sharedData_800DD588_0_s00[i] < ((PARTICLE_COUNT_MAX / 2) + 1);
                                sharedData_800DD592_0_s00 = var_v0_3 ^ 1;
                                break;

                            case 8:
                            case 9:
                            case 10:
                            case 11:
                            case 12:
                            case 13:
                            case 14:
                            case 15:
                            case 16:
                            case 17:
                            case 18:
                            case 19:
                            case 20:
                            case 21:
                            case 22:
                            case 23:
                            case 24:
                            case 25:
                            case 26:
                            case 27:
                            case 28:
                            case 29:
                            case 30:
                            case 31:
                            case 33:
                            case 34:
                            case 35:
                            case 36:
                            case 37:
                            case 38:
                            case 39:
                            case 41:
                            case 42:
                            case 43:
                            case 44:
                            case 45:
                            case 46:
                            case 47:
                            case 49:
                            case 50:
                            case 51:
                            case 52:
                            case 53:
                            case 54:
                            case 55:
                            default:
                                sharedData_800DD592_0_s00 = 1;
                                break;
                        }
                    }
#endif
                }

                if (sharedData_800DD598_0_s00 >= 0x200)
                {
                    sharedData_800DD598_0_s00 = 0;
                    g_SysWork.field_234A = 1;
                    sharedData_800E0CB6_0_s00 = sharedData_800E0CB4_0_s00;

                    switch ((sharedData_800E0CB8_0_s00 & 0xF) >> 2)
                    {
                        case 0:
                            sharedData_800DFB6C_0_s00 = 0;
                            sharedData_800DFB70_0_s00 = 0;
                            break;

                        case 1:
                            sharedData_800DFB6C_0_s00 = 1;
                            sharedData_800DFB70_0_s00 = 0;
                            break;

                        case 2:
                            sharedData_800DFB6C_0_s00 = 0;
                            sharedData_800DFB70_0_s00 = 1;
                            break;
                    }
                }
            }

            sharedData_800DFB50_0_s00 = arg2;
            temp_s0_3 = SetSp(0x1F8003D8);

            Particle_Update(sharedData_800E0CBC_0_s00);
#if defined(MAP0_S00)
            func_800CC6E8(&sharedData_800E34FC_0_s00, &sharedData_800E330C_0_s00, sharedData_800DFB50_0_s00);
#endif
            SetSp(temp_s0_3);

            for (i = sharedData_800DD588_0_s00[0] + sharedData_800DD588_0_s00[1]; i < PARTICLE_COUNT_MAX; i++)
            {
                sharedData_800E0CBC_0_s00[i].stateStep_1E = 0;
            }
    }

    g_ParticleVectors1 = g_ParticleVectors0;
}
