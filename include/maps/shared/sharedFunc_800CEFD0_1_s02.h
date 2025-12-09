// @hack Needed for match, same as version in rng.h without parens around it
// Changing rng.h version still doesn't let it match though?
#define Rng_GenerateInt(rand, low, high) (s32)((rand) % (((high) - (low)) + 1)) + (low)

#ifdef MAP7_S03
extern s16 D_800F23D0; // TODO: Might be sharedData?
#endif

// Value used in case 0 comparison
#define UNK_VAL 5

#if defined(MAP1_S06)
#define UNK_VAL 6
#elif defined(MAP7_S03)
#define UNK_VAL 8
#endif

void sharedFunc_800CEFD0_1_s02(s32 pass, s_Particle* part, u16* rand, s32* deltaTime)
{
    s_Collision sp10;

    s32 xDeltaCase0, zDeltaCase0;
    s32 xDeltaCase1, zDeltaCase1;

    u16 localRand;

    s_Particle* localPart = part;

#if defined(MAP0_S00) || defined(MAP0_S01) || defined(MAP0_S02) || defined(MAP1_S00) || \
    defined(MAP1_S06) || defined(MAP2_S00) || defined(MAP2_S02) || defined(MAP3_S00) || \
    defined(MAP3_S01) || defined(MAP3_S06) || defined(MAP5_S01) || defined(MAP5_S03) || \
    defined(MAP6_S00) || defined(MAP7_S03)

    xDeltaCase0 = g_Particle_PrevPosition.vx - g_Particle_Position.vx;
    zDeltaCase0 = g_Particle_PrevPosition.vz - g_Particle_Position.vz;

#elif defined(MAP5_S00) || defined(MAP6_S03)
    xDeltaCase1 = g_Particle_PrevPosition.vx - g_Particle_Position.vx;
    zDeltaCase1 = g_Particle_PrevPosition.vz - g_Particle_Position.vz;
#endif

    switch (pass)
    {
        case 0:
#if !defined(MAP1_S02) && !defined(MAP1_S03) && !defined(MAP4_S02) && !defined(MAP4_S03) && \
    !defined(MAP4_S04) && !defined(MAP4_S05) && !defined(MAP5_S00) && !defined(MAP6_S03)
            if (localPart->type_1F == 0)
            {
                localPart->movement_18.vx += Rng_GenerateInt(*rand, -7, 7);
                *rand                      = Rng_Rand16();
                localRand                  = *rand;
                localPart->movement_18.vz += Rng_GenerateInt(localRand, -7, 7);
                localPart->movement_18.vy += Rng_GenerateInt(*rand, -1, 3);
            }
            else
            {
                s32 localRand2 = Rng_Rand16();
                s32 temp       = 12;

                localPart->movement_18.vy += ((temp - g_Particle_PrevPosition.vy) - (g_Particle_PrevPosition.vy << 1) - (sharedData_800DD588_0_s00[0] >> 4)) + Rng_GenerateInt(localRand2, -2, 2);

                limitRange(localPart->movement_18.vy, 5, 1000);
            }

            localPart->position0_0.vx += TIMESTEP_SCALE(*deltaTime, (localPart->movement_18.vx << 2) + g_Particle_SpeedX + xDeltaCase0);
            localPart->position0_0.vy += TIMESTEP_SCALE(*deltaTime, (localPart->movement_18.vy >> 1) << 2);
            localPart->position0_0.vz += TIMESTEP_SCALE(*deltaTime, (localPart->movement_18.vz << 2) + g_Particle_SpeedZ + zDeltaCase0);

#if defined(MAP7_S03)
            localPart->position0_0.vz += (zDeltaCase0 - D_800F23D0);
#endif

            if (ABS(localPart->position0_0.vx) + ABS(localPart->position0_0.vz) > Q12(UNK_VAL))
            {
                if (sharedData_800DF158_1_s02 != 0)
                {
                    sharedFunc_800D01BC_0_s00(rand, &part->position0_0, UNK_VAL);
                }
                else
                {
                    localPart->position0_0.vx = -localPart->position0_0.vx;
                    localPart->position0_0.vz = -localPart->position0_0.vz;
                    localPart->type_1F       += 0xF0; // Hex
                }
            }

            if (localPart->position0_0.vy >= 0)
            {
#if defined(MAP7_S03)
                localPart->position0_0.vy = 0;
                localPart->movement_18.vy = 0;
                localPart->stateStep_1E++;
#else
                PushMatrix();
                Collision_Get(&sp10, localPart->position0_0.vx + g_Particle_Position.vx, localPart->position0_0.vz + g_Particle_Position.vz);
                PopMatrix();

                if (localPart->position0_0.vy >= sp10.groundHeight_0)
                {
#if defined(MAP1_S06)
                    localPart->stateStep_1E = 0;
#else
                    localPart->position0_0.vy = sp10.groundHeight_0;
                    if (sp10.groundHeight_0 < 0 && sp10.groundHeight_0 > -Q12(0.2))
                    {
                        localPart->position0_0.vy = 0;
                    }
                    localPart->movement_18.vy = 0;
                    localPart->stateStep_1E++;
#endif
                }
#endif
            }
#endif
            break;

        case 1:
#if !defined(MAP0_S01) && !defined(MAP0_S02) && !defined(MAP1_S00) && !defined(MAP2_S00) && \
    !defined(MAP2_S02) && !defined(MAP3_S00) && !defined(MAP3_S01) && !defined(MAP3_S06) && \
    !defined(MAP5_S01) && !defined(MAP5_S03) && !defined(MAP1_S06) && !defined(MAP7_S03)

#if !defined(MAP5_S00) && !defined(MAP6_S03)
            xDeltaCase1 = g_ParticleVectors1.viewPosition_C.vx - g_ParticleVectors0.viewPosition_C.vx;
            zDeltaCase1 = g_ParticleVectors1.viewPosition_C.vz - g_ParticleVectors0.viewPosition_C.vz;

            localPart->position1_C.vx = localPart->position0_0.vx;
            localPart->position1_C.vz = localPart->position0_0.vz;
            localPart->position1_C.vy = localPart->position0_0.vy - localPart->movement_18.vy;
#endif
            localPart->position0_0.vx += TIMESTEP_SCALE(*deltaTime, g_Particle_SpeedX + xDeltaCase1);
            localPart->movement_18.vy += sharedData_800E32D4_0_s00;
            localPart->position0_0.vy += TIMESTEP_SCALE(*deltaTime, localPart->movement_18.vy << 2);

#if defined(MAP5_S00) || defined(MAP6_S03)
            localPart->position1_C.vy = localPart->position0_0.vy - Q12(0.125f);
#endif

            localPart->position0_0.vz += TIMESTEP_SCALE(*deltaTime, g_Particle_SpeedZ + zDeltaCase1);

#if defined(MAP5_S00) || defined(MAP6_S03)
            localPart->position1_C.vx = localPart->position0_0.vx;
            localPart->position1_C.vz = localPart->position0_0.vz;
#endif

            if (sharedData_800DF158_1_s02 != 0)
            {
                localPart->position1_C.vx = localPart->position0_0.vx;
                localPart->position1_C.vz = localPart->position0_0.vz;
            }

            if (ABS(localPart->position0_0.vx) + ABS(localPart->position0_0.vz) > Q12(6.0))
            {
                if (sharedData_800DF158_1_s02 != 0)
                {
                    sharedFunc_800D01BC_0_s00(rand, &part->position0_0, 6);

                    localPart->position1_C.vx = localPart->position0_0.vx;
                    localPart->position1_C.vz = localPart->position0_0.vz;
                }
                else
                {
                    localPart->position1_C.vx -= localPart->position0_0.vx;
                    localPart->position1_C.vz -= localPart->position0_0.vz;

                    localPart->position0_0.vx = -localPart->position0_0.vx;
                    localPart->position0_0.vz = -localPart->position0_0.vz;

                    localPart->position1_C.vx += localPart->position0_0.vx;
                    localPart->position1_C.vz += localPart->position0_0.vz;
                }
            }

            if (localPart->position0_0.vy >= 0)
            {
                PushMatrix();
                Collision_Get(&sp10, localPart->position0_0.vx + g_Particle_Position.vx, localPart->position0_0.vz + g_Particle_Position.vz);
                PopMatrix();

                localPart->position0_0.vy = sp10.groundHeight_0;
                localPart->movement_18.vx = sp10.field_8;

                if (sp10.field_8 == 11)
                {
                    localPart->type_1F        = 3;
                    localPart->position1_C.vx = localPart->position0_0.vx;
                    localPart->position1_C.vz = localPart->position0_0.vz;
                    localPart->position1_C.vy = localPart->position0_0.vy - 96;
                }
                localPart->movement_18.vz = 0;
                localPart->movement_18.vy = 0;
                localPart->stateStep_1E++;
            }
#endif
            break;
    }
}
