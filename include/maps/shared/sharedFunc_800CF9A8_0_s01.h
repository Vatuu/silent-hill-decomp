/** @brief Reset function for a snow particle */
void sharedFunc_800CF9A8_0_s01(s32 arg0, s_Particle* part, u16* rand)
{
    #define SNOW_Y_START_SPEED  Q12(0.0245f)
    #define RAIN_XZ_SPAWN_RANGE 6
#if defined(MAP1_S06)
    #define SNOW_XZ_SPAWN_RANGE 6
#elif defined(MAP7_S03)
    #define SNOW_XZ_SPAWN_RANGE 8
#else
    #define SNOW_XZ_SPAWN_RANGE 5
#endif

    s_Particle* partCpy;

    partCpy = part;

    switch (arg0)
    {
        case 0:
// TODO: Probably better to change this to the maps that include it instead.
#if !defined(MAP1_S02) && !defined(MAP1_S03) && !defined(MAP4_S02) && !defined(MAP4_S03) && \
    !defined(MAP4_S04) && !defined(MAP4_S05) && !defined(MAP5_S00) && !defined(MAP6_S03)
            if (sharedData_800DD592_0_s00 != 0)
            {
                part->type_1F = ParticleType_Snow;
            }
            else
            {
                part->type_1F = ParticleType_Unk1;
            }

            // Set start position.
            partCpy->position0_0.vy = sharedData_800E323C_0_s00.vy;

            // Set downward movement.
            partCpy->movement_18.vz = Q12(0.0f);
            partCpy->movement_18.vx = Q12(0.0f);
            partCpy->movement_18.vy = SNOW_Y_START_SPEED;

            // Set random start XZ position.
            sharedFunc_800D01BC_0_s00(rand, part, SNOW_XZ_SPAWN_RANGE);

            // Second position unused for snow.
            partCpy->position1_C.vz = Q12(0.0f);
            partCpy->position1_C.vy = Q12(0.0f);
            partCpy->position1_C.vx = Q12(0.0f);
#endif
            break;

        case 1:
#if defined(MAP0_S00) || defined(MAP1_S02) || defined(MAP1_S03) || defined(MAP4_S02) || \
    defined(MAP4_S03) || defined(MAP4_S04) || defined(MAP4_S05) || defined(MAP5_S00) || \
    defined(MAP6_S00) || defined(MAP6_S03)
            partCpy->type_1F = ParticleType_Rain;
            
            // Set start position.
            partCpy->position0_0.vy = sharedData_800E323C_0_s00.vy + Q12(Rng_GenerateInt(Rng_Rand16(), 0, 2));

#if defined(MAP5_S00) || defined(MAP6_S03)
            partCpy->position1_C.vy = partCpy->position0_0.vy - Q12(0.125f);
            partCpy->movement_18.vy = Q12(0.0091f);
#else
            partCpy->position1_C.vy = sharedData_800E323C_0_s00.vy;
            partCpy->movement_18.vy = Q12(0.03675f);
#endif

            // Set random start XZ position.
            sharedFunc_800D01BC_0_s00(rand, part, RAIN_XZ_SPAWN_RANGE);

            // Copy random XZ to second position.
            partCpy->position1_C.vx = partCpy->position0_0.vx;
            partCpy->position1_C.vz = partCpy->position0_0.vz;
#endif
            break;
    }

    // Step to active state.
    partCpy->stateStep_1E++;
}
