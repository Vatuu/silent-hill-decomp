
#define SNOW_XZ_SPAWN_RANGE 5
#define SNOW_Y_START_SPEED 100

/** @brief Reset function for a snow particle */
void sharedFunc_800CF9A8_0_s01(s32 arg0, s_particle* particle, u16* rand)
{
    // Local pointer required to satisfy matching -- Credit: emoose
    VECTOR3* pos = &particle->position1_0;
    
    if (arg0 == 0)
    {
        if (sharedData_800DD796_0_s01 != 0)
        {
            particle->type_1F = 0;
        }
        else
        {
            particle->type_1F = 1;
        }

        // Sets the starting Y position for particles, and is a negative value - probably a particle volume ceiling bound
        particle->position1_0.vy = sharedData_800E323C_0_s00.vy;

        // Movement offset starts directly downward
        particle->movement_18.vz = 0;
        particle->movement_18.vx = 0;
        particle->movement_18.vy = SNOW_Y_START_SPEED;

        // Sets a random starting XZ position
        sharedFunc_800D01BC_0_s00(rand, pos, SNOW_XZ_SPAWN_RANGE);

        // 2nd position is unused for snow
        particle->position2_C.vz = 0;
        particle->position2_C.vy = 0;
        particle->position2_C.vx = 0;
    }
    // Move the particle into the active state
    particle->counter_1E++;
}